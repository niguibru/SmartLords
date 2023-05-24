// Environment variables
import { config } from "dotenv"
config()
if (!process.env.OPENAI_API_KEY) {
    console.log("No OPENAI_API_KEY provided")
    process.exit()
}

// OpenAIApi
import { Configuration, OpenAIApi } from "openai"
const openAIConfig = new Configuration({
    apiKey: process.env.CHATGPT_API_KEY
})
const openAIApi = new OpenAIApi(openAIConfig)

// Express
import express from "express"
import bodyParser from "body-parser"
const app = express()
app.use(bodyParser.json())
const port = 3000
const messages = [
    {"role": "system", "content": "You are a helpful assistant."}
]
app.post('/', async (req, res) => {
    const { message } = req.body
    messages.push({"role": "user", "content": message},)
    const response = await openAIApi.createChatCompletion({
        model: "gpt-3.5-turbo", // "gpt-4"
        messages
    });
    const assistantMessage = response.data.choices[0].message
    messages.push(assistantMessage)
    res.send(assistantMessage)
})
app.listen(port, () => {
    console.log(`Listening on port ${port}`)
})
