// Environment variables
import { config } from "dotenv"
config()

export function timeout(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

import mqtt from "mqtt"

export class MqttHandler {

    constructor() {
        this.verbose = false
        this.timer
        this.client
        this.status = "Disconnected"
        this.listeners = []
    }
    
    async connect() {
        const options = {
            host: 'cdf160a295004c78ad30b866765d66da.s2.eu.hivemq.cloud',
            port: 8883,
            protocol: 'mqtts',
            username: 'smartlordsNode',
            password: process.env.HIVEMQ_PASS
        }
        this.client = mqtt.connect(options);
  
        this.client.on('connect', function () {
            if (this.verbose) console.log(`>> MQTT - Connected `)
            this.status = "Connected"
            return
        });
        
        this.client.on('error', function (error) {
            if (this.verbose) console.log(`>> MQTT - Error `) 
            if (this.verbose) console.log(`   description - ${error} `)
            this.status = "Error"
            return
        });

        let listeners = this.listeners;
        
        this.client.on('message', function (topic, payload) {
            var messageJSON = JSON.parse(payload.toString())
            if (this.verbose) console.log(`>> MQTT - Message Arrived `) 
            if (this.verbose) console.log(`   topic - ${topic} `)
            if (this.verbose) console.log(`   payload - ${payload} `) 
            listeners.find(listener => listener.topic === topic)?.action(messageJSON)
        });
  
        await timeout(1000); // wait 1 second
        
        // this.listeners.forEach((listener) => {
        //     this.client.subscribe(listener.topic);
        // });
    }
  
    addListener(listener) {
        this.listeners.push(listener)
        this.client.subscribe(listener.topic);
        if (this.verbose) console.log(`>> MQTT - Listener Added`) 
        if (this.verbose) console.log(`   topic - ${listener.topic} `) 
    }

    publish({ topic, device_id, state}) {
        let payload = JSON.stringify({ device_id, state })
        this.client.publish(topic, payload);
        if (this.verbose) console.log(`>> MQTT - Message Published`) 
        if (this.verbose) console.log(`   topic - ${topic} `) 
        if (this.verbose) console.log(`   payload - ${payload} `) 
    }
}
