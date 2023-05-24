import { MqttHandler } from "./mqtt.js";
import { MoistureSensor, LedBuiltin } from "./arduino.js";

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
