/*  
    Room Service  

    Serial port communication with Arduino board
    MQTT communication with ESP board
    HTTP communication with front-end Dashboard
*/

/**  MQTT  **/

const mqtt = require('mqtt');
const MQTTclient = mqtt.connect('mqtts://62d6711e8bac4a34999924c6119ec7da.s2.eu.hivemq.cloud', {
    port: 8883,
    username: 'esiot-2022-2',
    password: 'Prova123',
    rejectUnauthorized: false
});

MQTTclient.on('connect', function () {
    console.log('Connected to MQTT broker');
    MQTTclient.subscribe('Light Level');
    MQTTclient.subscribe('Movement');
});

let level = -1, movement = -1, state = -1, fromSerial;

MQTTclient.on('message', function (topic, message) {
    //console.log("Topic: " + topic + " - Message: " + message.toString());
    if (topic == "Light Level") level = message.toString();
    if (topic == "Movement") movement = message.toString();
});

MQTTclient.on('error', function (error) {
    console.log("Error: ", error);
});



/**  HTTP  **/

const express = require("express");
const app = express();

app.use(express.static("../room-dashboard"));
app.use(express.json());

const expressPort = process.env.PORT || 4000;
app.listen(expressPort, () => {
    console.log(`listening at ${expressPort}`);
});

app.get("/getValues", (req, res) => {
    res.json({ level, movement, state: new Date().getHours() >= 8 && new Date().getHours() < 19 ? "ON" : "OFF", fromSerial })
})

let remoteControl = "0";
app.get("/setSerialControl", async (req, res) => {
    remoteControl = req.query.to;
    res.end();
})

let lampControl = "0"
app.get("/setLamp", (req, res) => {
    lampControl = req.query.to;
    res.end();
})

let blindsHeight = "90"
app.get("/setBlinds", (req, res) => {
    blindsHeight = req.query.to;
    res.end();
})



/**  SERIAL PORT  **/

const { SerialPort } = require('serialport')
const { ReadlineParser } = require('@serialport/parser-readline')

const port = new SerialPort({
    path: 'COM4',
    baudRate: 9600,
})

port.setEncoding("utf-8")

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))
parser.on('data', handleData)

port.on('error', (err) => {
    console.log('Error: ', err.message)
})

function handleData(data) {
    fromSerial = data;
}

setInterval(async () => {

    state = new Date().getHours() >= 8 && new Date().getHours() < 20 ? "1" : "0";
    port.write("movement:" + movement + "\n");
    await sleep(150);
    port.write("level:" + level + "\n");
    await sleep(150);
    port.write("state:" + state + "\n");
    await sleep(150);
    port.write("remote:"+ remoteControl + "\n");
    await sleep(150);
    port.write("setLamp:"+ lampControl + "\n");
    await sleep(150);
    port.write("setBlinds:"+ blindsHeight + "\n");
    await sleep(150);
    
}, 2000)

function sleep(ms) {
    return new Promise((resolve) => {
        setTimeout(resolve, ms);
    });
}