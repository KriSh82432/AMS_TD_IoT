const mongoose = require('mongoose')
const mqtt = require('mqtt')
const topic ='googleSheetsTopic'
const options = {
    port:8883, 
    protocol:'mqtts',
    username:'google_sheets_project',
    password:'abcd1234A',
    host:'bdcf9197b54e48c3913243ef5378abb0.s1.eu.hivemq.cloud'
}
mongoose.connect("mongodb+srv://Riddhiman_Mongo:hello123@cluster1.b76yf.mongodb.net/MQTT?retryWrites=true&w=majority")
const model = require('./database_creator')

const client = mqtt.connect(options)

client.on('connect',()=>{
    console.log(`Connected to MQTT: ${options.host}`)
})

client.on('message',async (topic,msg)=>{
    const data = await model.findOne({
        RFID:msg.toString()
    })
    if(data){
        client.publish(topic,`Register Number: ${data.REG_NO}`);
    }
    else{

    }
});
const data = {
    Name:'Riddhiman',
    Domain:'IoT'
}
const payload = `Name: ${data.Name}\nDomain: ${data.Domain}`
client.subscribe(topic);