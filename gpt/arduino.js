export class LedBuiltin {
    constructor(macAddress, mqttClient) {
        this.macAddress = macAddress
        this.mqttClient = mqttClient
    }

    on() {
        this.mqttClient.publish({
            topic: 'led-builtin/state/update', 
            device_id: this.macAddress,
            state: { value: 'on' }
        })
    }

    off() {
        this.mqttClient.publish({
            topic: 'led-builtin/state/update', 
            device_id: this.macAddress,
            state: { value: 'off' }
        })
    }
}

export class MoistureSensor {
    constructor(macAddress, mqttClient) {
        this.macAddress = macAddress
        this.state = {}
        this.mqttClient = mqttClient
        this.mqttClient.addListener({ 
            topic: 'moisture-sensor/state', 
            action: (payload)=>{
                if (payload.device_id === this.macAddress) {
                    this.state = payload.state
                }
            }
        })
    }

    sync() {
        this.mqttClient.publish({
            topic: 'moisture-sensor/state/publish', 
            device_id: this.macAddress
        })
    }
}
