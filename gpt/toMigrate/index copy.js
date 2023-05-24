import { timeout, MqttHandler } from "../mqtt.js";
import { MoistureSensor, LedBuiltin } from "../arduino.js";

// MQTT
let mqttClient = new MqttHandler()
await mqttClient.connect()

class IOTDevice {
    constructor(macAddress, mqttClient) {
        this.ledBuiltin = new LedBuiltin(macAddress, mqttClient)
        this.moisture = new MoistureSensor(macAddress, mqttClient)
    }
}

let plant = new IOTDevice('44:17:93:0D:C4:73', mqttClient)
plant.ledBuiltin.off()
plant.moisture.sync()

// Express
import express from "express"
import bodyParser from "body-parser"
const app = express()
app.use(bodyParser.json())
const port = 3000
app.get('/moistureSensor', async (req, res) => {
    res.json(
        plant.moisture.state
    )
})
app.get('/', async (req, res) => {
    res.json(plant)
})
app.listen(port, () => {
    console.log(`Listening on port ${port}`)
    console.log('----------------------')
})

/*
// Arduino
const DEVICES = {
    ALL: '#',
    LED_STRIP: 'AC:0B:FB:DB:D8:70',
    MOISTURE_SENSOR1: '2C:F4:32:57:48:44',
    MOISTURE_SENSOR2: '44:17:93:0D:C4:73'
}
let ledBuiltin = new LedBuiltin(mqttClient, DEVICES.LED_STRIP)
let ledStrip = new LedStrip(mqttClient, DEVICES.LED_STRIP)
let moistureSensor = new MoistureSensor(mqttClient, DEVICES.MOISTURE_SENSOR1)
let moistureSensor2 = new MoistureSensor(mqttClient, DEVICES.MOISTURE_SENSOR2)
mqttClient.addListener({ topic: 'moisture-sensor/state', action: (payload)=>{ 
    moistureSensor2.newState(payload)
    moistureSensor.newState(payload)
}})
mqttClient.publish({
    topic: 'moisture-sensor/state/publish',
    device_id: DEVICES.ALL
})

// Express
import express from "express"
import bodyParser from "body-parser"
const app = express()
app.use(bodyParser.json())
const port = 3000
app.post('/ledBuiltin', async (req, res) => {
    const { state } = req.body
    ledBuiltin.state = state
    ledBuiltin.sync()
    res.send(state)
})
app.post('/ledStrip', async (req, res) => {
    const { state } = req.body
    ledStrip.state = state
    ledStrip.sync()
    res.send(state)
})
app.get('/moistureSensor', async (req, res) => {
    res.json(moistureSensor2.state)
})
app.get('/moistureSensor/talk', async (req, res) => {
    res.send(`Hola, la humedad de tu planta es: ${moistureSensor1.state.percent} porciento`)
})
app.get('/', async (req, res) => {
    let states = {
        ledBuiltin: ledBuiltin.state,
        ledStrip: ledStrip.state,
        moistureSensor: moistureSensor.state
    }
    console.log(states)
    res.json(states)
})
app.listen(port, () => {
    console.log(`Listening on port ${port}`)
    console.log('----------------------')
})
*/