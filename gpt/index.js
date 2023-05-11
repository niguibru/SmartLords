import { config } from "dotenv"
config()
console.log(process.env.CHATGPT_API_KEY)

import { Configuration, OpenAIApi } from "openai"

const openAIConfig = new Configuration({
    apiKey: process.env.CHATGPT_API_KEY
})
const openAIApi = new OpenAIApi(openAIConfig)
const response = await openAIApi.createChatCompletion({
    model: "gpt-3.5-turbo",
    messages: [
        {"role": "system", "content": "You are a helpful assistant."},
        {"role": "user", "content": "Hello there!"},
    ]
});
console.log(response.data.choices)
