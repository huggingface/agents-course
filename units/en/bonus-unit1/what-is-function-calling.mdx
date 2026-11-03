# What is Function Calling?

Function-calling is a **way for an LLM to take actions on its environment**. It was first [introduced in GPT-4](https://openai.com/index/function-calling-and-other-api-updates/), and was later reproduced in other models.

Just like the tools of an Agent, function-calling gives the model the capacity to **take an action on its environment**. However, the function calling capacity **is learned by the model**, and relies **less on prompting than other agents techniques**.

During Unit 1, the Agent **didn't learn to use the Tools**, we just provided the list, and we relied on the fact that the model **was able to generalize on defining a plan using these Tools**. 

While here, **with function-calling, the Agent is fine-tuned (trained) to use Tools**.

## How does the model "learn" to take an action?

In Unit 1, we explored the general workflow of an agent. Once the user has given some tools to the agent and prompted it with a query, the model will cycle through:

1. *Think* : What action(s) do I need to take in order to fulfill the objective.
2. *Act* : Format the action with the correct parameter and stop the generation.
3. *Observe* : Get back the result from the execution.

In a "typical" conversation with a model through an API, the conversation will alternate between user and assistant messages like this:

```python
conversation = [
    {"role": "user", "content": "I need help with my order"},
    {"role": "assistant", "content": "I'd be happy to help. Could you provide your order number?"},
    {"role": "user", "content": "It's ORDER-123"},
]
```

Function-calling brings **new roles to the conversation**! 

1. One new role for an **Action** 
2. One new role for an **Observation** 

If we take the [Mistral API](https://docs.mistral.ai/capabilities/function_calling/) as an example, it would look like this:

```python
conversation = [
    {
        "role": "user",
        "content": "What's the status of my transaction T1001?"
    },
    {
        "role": "assistant",
        "content": "",
        "function_call": {
            "name": "retrieve_payment_status",
            "arguments": "{\"transaction_id\": \"T1001\"}"
        }
    },
    {
        "role": "tool",
        "name": "retrieve_payment_status",
        "content": "{\"status\": \"Paid\"}"
    },
    {
        "role": "assistant",
        "content": "Your transaction T1001 has been successfully paid."
    }
]
```

> ... But you said there's a new role for function calls?

**Yes and no**, in this case and in a lot of other APIs, the model formats the action to take as an "assistant" message. The chat template will then represent this as **special tokens** for function-calling.

- `[AVAILABLE_TOOLS]` – Start the list of available tools  
- `[/AVAILABLE_TOOLS]` – End the list of available tools  
- `[TOOL_CALLS]` – Make a call to a tool (i.e., take an "Action")  
- `[TOOL_RESULTS]` – "Observe" the result of the action  
- `[/TOOL_RESULTS]` – End of the observation (i.e., the model can decode again)

We'll talk again about function-calling in this course, but if you want to dive deeper you can check [this excellent documentation section](https://docs.mistral.ai/capabilities/function_calling/).

---
Now that we learned what function-calling is and how it works, let's **add some function-calling capabilities to a model that does not have those capacities yet**: [google/gemma-2-2b-it](https://huggingface.co/google/gemma-2-2b-it), by appending some new special tokens to the model.

To be able to do that, **we need first to understand fine-tuning and LoRA**. 
