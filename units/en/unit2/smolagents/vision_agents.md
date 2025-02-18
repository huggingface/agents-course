# Vision Agents with SmolAgents

Empowering agents with visual capabilities is crucial for solving tasks that require more than text processing. Many real-world challenges, such as web browsing or document understanding, involve analyzing rich visual content. Fortunately, `smolagents` provides built-in support for vision.

## How to Interact with a Vision Agent

There are two main approaches to provide visual input:

### 1. Providing Images at the Start

In this approach, images are passed at the beginning and stored as `task_images` alongside the task prompt. The agent processes these images throughout its execution.

#### **Use Case Example**
A possible application is **document understanding**, where agents analyze long documents containing both text and visual elements, such as graphs or tables.

```python
model_id = "Qwen/Qwen2.5-VL-72B-Instruct"  # Update with preferred VLM
model = HfApiModel(model_id)

# Instantiate the agent
agent = CodeAgent(
    tools=[],
    model=model,
    max_steps=20,
    verbosity_level=2
)

# Run the agent with a manufacturing quality check task
response = agent.run(
    "Inspect these product images for any visual defects or inconsistencies.",
    images=[image_1, image_2]
)
```

### 2. Dynamic Image Retrieval

In this approach, images are dynamically allocated into the agent's memory during its execution. Agents in smolagents are based on the `MultiStepAgent` class, an abstraction of the ReAct framework. This class operates in a structured cycle where existing variables and knowledge are logged at different stages:

1. **SystemPromptStep:** Stores the system prompt.  
2. **TaskStep:** Logs the user query and any provided input.  
3. **ActionStep:** Captures logs from the agent's actions and results.

This structured approach allows agents to incorporate visual information dynamically and respond adaptively to evolving tasks. Below is a diagram illustrating the dynamic workflow process and how different steps integrate within the agent lifecycle.

![Dynamic image retrieval](https://huggingface.co/datasets/huggingface/documentation-images/resolve/main/blog/smolagents-can-see/diagram_adding_vlms_smolagents.png)

```python
agent = CodeAgent(
    tools=[],
    model=model,
    step_callbacks = [save_screenshot], # This callback triggers at the end of each step
    max_steps=20,
    verbosity_level=2
)
```

## Further Reading

* [We just gave sight to smolagents](https://huggingface.co/blog/smolagents-can-see)