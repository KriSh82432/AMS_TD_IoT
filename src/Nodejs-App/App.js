const mqtt = require("mqtt");

const client = mqtt.connect('mqtt://localhost:1883', {
  username: 'krishna',
  password: 'KriShna824@32'
});

client.on("connect", () => {
  console.log("Connected to MQTT broker");
  client.subscribe("test");
});

client.on("message", (topic, message) => {
  console.log(`Received message on topic "${topic}": ${message}`);
});

client.on("error", (error) => {
  console.error("MQTT client error:", error);
});
