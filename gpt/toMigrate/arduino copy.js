export class MoistureSensor {
    constructor(mqttClient, deviceId) {
        this.mqttCli = mqttClient
        this.deviceId = deviceId
        this.state
    }

    newState(payload) {
        if (payload.device_id === this.deviceId) {
            // console.log(`>> Moisture - Message Arrived `) 
            // console.log(`   This deviceId - ${this.deviceId} `) 
            // console.log(`   device_Id - ${payload.device_id} `) 
            // console.log(`   value - ${payload.state.value} `) 
            // console.log(`   percent - ${payload.state.percent} `)
            this.state = payload.state
        }
    }

    // sync() {
    //     // this.mqttCli.addListener({ topic: 'moisture-sensor/state', action: (payload)=>{ 
    //     //     console.log(`>> Moisture - Message Arrived `) 
    //     //     console.log(`   This deviceId - ${this.deviceId} `) 
    //     //     console.log(`   device_Id - ${payload.device_id} `) 
    //     //     console.log(`   value - ${payload.state.value} `) 
    //     //     console.log(`   percent - ${payload.state.percent} `)
    //     //     if (payload.device_id === this.deviceId) {
    //     //         this.state = payload.state
    //     //     }
    //     // }})
    //     // this.mqttCli.publish({
    //     //     topic: 'moisture-sensor/state/publish',
    //     //     device_id: this.deviceId
    //     // })
    // }
}

export class LedBuiltin {
    constructor(mqttClient, deviceId) {
        this.mqttCli = mqttClient
        this.deviceId = deviceId
        this.state = {
            "value": "off",
        }
        this.sync()
    }

    sync() {
        this.mqttCli.publish({
            topic: 'led-builtin/state/update', 
            device_id: this.deviceId,
            state: this.state
        })
    }
}

export class LedStrip {
    constructor(mqttClient, deviceId) {
        this.mqttCli = mqttClient
        this.deviceId = deviceId
        this.state = {
            "value": "off",
            "color": "rainbow",
            "start": 1,
            "end": 29
        }
        this.sync()
    }

    sync() {
        this.mqttCli.publish({
            topic: 'led-strip/state/update', 
            device_id: this.deviceId,
            state: this.state
        })
    }
}
