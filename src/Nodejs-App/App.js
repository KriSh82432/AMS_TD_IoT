const mqtt = require("mqtt");
const mysql = require("mysql");

const mqttBrokerUrl = "mqtt://localhost:1883";
const mqttTopic = "ams/uid";
const mqttResultTopic = "ams/uid/result";

const mysqlConfig = {
  host: "localhost",
  user: "root",
  password: "KriShna824@32",
  database: "AMSLogs",
};
const mysqlTable = "EntryLogs";

const mqttClient = mqtt.connect(mqttBrokerUrl, {
  username : "ams-v2-iot",
  password : 'KriShna824@32',
  keepalive: 60
});

mqttClient.on("connect", () => {
  console.log(`Connected to MQTT broker: ${mqttBrokerUrl}`);
  mqttClient.subscribe(mqttTopic, (err) => {
    if (err) {
      console.error(`Failed to subscribe to topic ${mqttTopic}: ${err}`);
    } else {
      console.log(`Subscribed to topic ${mqttTopic}`);
    }
  });
});

const mysqlConnection = mysql.createConnection(mysqlConfig);

mysqlConnection.connect((err) => {
  if (err) {
    console.error(`Failed to connect to MySQL server: ${err}`);
  } else {
    console.log(`Connected to MySQL server: ${mysqlConfig.host}`);
  }
});

mqttClient.on("message", (topic, message) => {
  const data = message.toString().replace(/[\n\r\s]+/g, '');
  const timestamp = Math.floor(Date.now() / 1000);
  if (topic === mqttTopic) {
    if(data.length === 8) {
      mysqlConnection.query(
        `INSERT INTO ${mysqlTable} (UID, EntryTime) VALUES (?, ?)`,
        [data, timestamp],
        (err, result) => {
          if (err) {
            console.log(data);
            console.error(`Failed to insert data into MySQL table: ${err}`);
            mqttClient.publish(mqttResultTopic, "404");
          } else {
            console.log(`Inserted data into MySQL table: ${data}`);
            mqttClient.publish(mqttResultTopic, "200");
          }
        }
      );
    } else {
      console.log(data);
      mqttClient.publish(mqttResultTopic, "402");
    }
  } else {
    mqttClient.publish(mqttResultTopic, "500");
  }
});

mqttClient.on("error", (err) => {
  console.error(`MQTT error: ${err}`);
});

mysqlConnection.on("error", (err) => {
  console.error(`MySQL error: ${err}`);
});

process.on('exit', function () {
  connection.end();
});