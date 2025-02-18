# Agentic Frameworks

After introducing the core concepts behind agents, we'll explore different agentic frameworks that can be used to build powerful agentic applications. Let's dive in! 🕵

## When to Use an Agentic Framework

An agentic framework is not always needed when building an application around LLMs. They provide flexibility in the workflow to efficiently solve a specific task, but they're not always necessary. Sometimes, predefined workflows are sufficient to fulfill user requests, and there is no real need for an agentic framework. If the approach to build an agent is simple, like a chain of prompts, using plain code may be enough. The advantage is that the developer will have full control and understanding of their system without abstractions.

However, when the workflow becomes more complex, such as letting an LLM call functions or using multiple agents, these abstractions start to become helpful.

Considering these ideas, we can already identify the need for some features:

* An LLM engine powering the system.
* A list of tools the agent can access.
* A parser for extracting tool calls from the LLM output.
* A system prompt synced with the parser.
* A memory system.
* Error logging and retry mechanisms to control LLM mistakes.

## Agentic Frameworks Units

| Framework  | Description | Unit Author |
|------------|----------------|----------------|
| [smolagents](./smolagents/introduction) | Agents framework developed by Hugging Face. | Sergio Paniego - [HF](https://huggingface.co/burtenshaw) - [X](https://x.com/ben_burtenshaw) - [Linkedin](https://www.linkedin.com/in/ben-burtenshaw/) |
