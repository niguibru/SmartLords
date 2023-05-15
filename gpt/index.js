// Environment variables
import { config } from "dotenv"
config()
if (!process.env.OPENAI_API_KEY) {
    console.log("No OPENAI_API_KEY provided")
    process.exit()
}

// Langchain
import { OpenAI } from "langchain/llms/openai";
import { BufferMemory } from "langchain/memory";
import { LLMChain } from "langchain/chains";
import { ConversationChain } from "langchain/chains";
import { PromptTemplate } from "langchain/prompts";

import { initializeAgentExecutorWithOptions } from "langchain/agents";
import { Tool } from "langchain/tools";

class Fruitool extends Tool {
    name = "Fruit_color_tool";
    description = "the input of this shoudl only be in json format, usefull for when you need a name of a fruit based on it's color"
    async _call(input) {
        console.log(`{ input: '${input}' }`)
        if (input.toLowerCase().includes("red")) { return "Strawberry" }
        return "Melonazo"
    }
}
const tools = [
    new Fruitool()
]
const model = new OpenAI({ 
    temperature: 0
});
const executor = await initializeAgentExecutorWithOptions(tools, model, {
    agentType: "zero-shot-react-description",
})
const input = `Can you find a name of a animal with the same color than a tree in a json format?`;
console.log(input);
const result = await executor.call({ input });
console.log(result);

console.log('');
const fruit = result.output
const model2 = new OpenAI({ 
    temperature: 1
});
const memory = new BufferMemory();
const template = "Can you tell me a funny phrase about a {fruit}?";
console.log(template);
const prompt = new PromptTemplate({
  template: template,
  inputVariables: ["fruit"],
});
// const chain = new LLMChain({ llm: model, prompt: prompt });
const chain = new ConversationChain({ 
    llm: model2, 
    memory: memory, 
    prompt: prompt 
});
const res = await chain.call({ 
    fruit
});
console.log(res.response);
