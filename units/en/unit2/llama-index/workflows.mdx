# Creating agentic workflows in LlamaIndex

A workflow in LlamaIndex provides a structured way to organize your code into sequential and manageable steps.

Such a workflow is created by defining `Steps` which are triggered by `Events`, and themselves emit `Events` to trigger further steps.
Let's take a look at Alfred showing a LlamaIndex workflow for a RAG task.

![Workflow Schematic](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/llama-index/workflows.png)

**Workflows offer several key benefits:**

- Clear organization of code into discrete steps
- Event-driven architecture for flexible control flow
- Type-safe communication between steps
- Built-in state management
- Support for both simple and complex agent interactions

As you might have guessed, **workflows strike a great balance between the autonomy of agents while maintaining control over the overall workflow.**

So, let's learn how to create a workflow ourselves!

## Creating Workflows

<Tip>
You can follow the code in <a href="https://huggingface.co/agents-course/notebooks/blob/main/unit2/llama-index/workflows.ipynb" target="_blank">this notebook</a> that you can run using Google Colab.
</Tip>

### Basic Workflow Creation

<details>
<summary>Install the Workflow package</summary>
As introduced in the <a href="./llama-hub">section on the LlamaHub</a>, we can install the Workflow package with the following command:

```python
pip install llama-index-utils-workflow
```
</details>

We can create a single-step workflow by defining a class that inherits from `Workflow` and decorating your functions with `@step`.
We will also need to add `StartEvent` and `StopEvent`, which are special events that are used to indicate the start and end of the workflow.

```python
from llama_index.core.workflow import StartEvent, StopEvent, Workflow, step

class MyWorkflow(Workflow):
    @step
    async def my_step(self, ev: StartEvent) -> StopEvent:
        # do something here
        return StopEvent(result="Hello, world!")


w = MyWorkflow(timeout=10, verbose=False)
result = await w.run()
```

As you can see, we can now run the workflow by calling `w.run()`.

### Connecting Multiple Steps

To connect multiple steps, we **create custom events that carry data between steps.**
To do so, we need to add an `Event` that is passed between the steps and transfers the output of the first step to the second step.

```python
from llama_index.core.workflow import Event

class ProcessingEvent(Event):
    intermediate_result: str

class MultiStepWorkflow(Workflow):
    @step
    async def step_one(self, ev: StartEvent) -> ProcessingEvent:
        # Process initial data
        return ProcessingEvent(intermediate_result="Step 1 complete")

    @step
    async def step_two(self, ev: ProcessingEvent) -> StopEvent:
        # Use the intermediate result
        final_result = f"Finished processing: {ev.intermediate_result}"
        return StopEvent(result=final_result)

w = MultiStepWorkflow(timeout=10, verbose=False)
result = await w.run()
result
```

The type hinting is important here, as it ensures that the workflow is executed correctly. Let's complicate things a bit more!

### Loops and Branches

The type hinting is the most powerful part of workflows because it allows us to create branches, loops, and joins to facilitate more complex workflows.

Let's show an example of **creating a loop** by using the union operator `|`.
In the example below, we see that the `LoopEvent` is taken as input for the step and can also be returned as output.

```python
from llama_index.core.workflow import Event
import random


class ProcessingEvent(Event):
    intermediate_result: str


class LoopEvent(Event):
    loop_output: str


class MultiStepWorkflow(Workflow):
    @step
    async def step_one(self, ev: StartEvent | LoopEvent) -> ProcessingEvent | LoopEvent:
        if random.randint(0, 1) == 0:
            print("Bad thing happened")
            return LoopEvent(loop_output="Back to step one.")
        else:
            print("Good thing happened")
            return ProcessingEvent(intermediate_result="First step complete.")

    @step
    async def step_two(self, ev: ProcessingEvent) -> StopEvent:
        # Use the intermediate result
        final_result = f"Finished processing: {ev.intermediate_result}"
        return StopEvent(result=final_result)


w = MultiStepWorkflow(verbose=False)
result = await w.run()
result
```

### Drawing Workflows

We can also draw workflows. Let's use the `draw_all_possible_flows` function to draw the workflow. This stores the workflow in an HTML file.

```python
from llama_index.utils.workflow import draw_all_possible_flows

w = ... # as defined in the previous section
draw_all_possible_flows(w, "flow.html")
```

![workflow drawing](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/llama-index/workflow-draw.png)

There is one last cool trick that we will cover in the course, which is the ability to add state to the workflow.

### State Management

State management is useful when you want to keep track of the state of the workflow, so that every step has access to the same state.
We can do this by using the `Context` type hint on top of a parameter in the step function.

```python
from llama_index.core.workflow import Context, StartEvent, StopEvent


@step
async def query(self, ctx: Context, ev: StartEvent) -> StopEvent:
    # store query in the context
    await ctx.set("query", "What is the capital of France?")

    # do something with context and event
    val = ...

    # retrieve query from the context
    query = await ctx.get("query")

    return StopEvent(result=val)
```

Great! Now you know how to create basic workflows in LlamaIndex!

<Tip>There are some more complex nuances to workflows, which you can learn about in <a href="https://docs.llamaindex.ai/en/stable/understanding/workflows/">the LlamaIndex documentation</a>.</Tip>

However, there is another way to create workflows, which relies on the `AgentWorkflow` class. Let's take a look at how we can use this to create a multi-agent workflow.

## Automating workflows with Multi-Agent Workflows

Instead of manual workflow creation, we can use the **`AgentWorkflow` class to create a multi-agent workflow**.
The `AgentWorkflow` uses Workflow Agents to allow you to create a system of one or more agents that can collaborate and hand off tasks to each other based on their specialized capabilities.
This enables building complex agent systems where different agents handle different aspects of a task.
Instead of importing classes from `llama_index.core.agent`, we will import the agent classes from `llama_index.core.agent.workflow`.
One agent must be designated as the root agent in the `AgentWorkflow` constructor.
When a user message comes in, it is first routed to the root agent.

Each agent can then:

- Handle the request directly using their tools
- Handoff to another agent better suited for the task
- Return a response to the user

Let's see how to create a multi-agent workflow.

```python
from llama_index.core.agent.workflow import AgentWorkflow, ReActAgent
from llama_index.llms.huggingface_api import HuggingFaceInferenceAPI

# Define some tools
def add(a: int, b: int) -> int:
    """Add two numbers."""
    return a + b

def multiply(a: int, b: int) -> int:
    """Multiply two numbers."""
    return a * b

llm = HuggingFaceInferenceAPI(model_name="Qwen/Qwen2.5-Coder-32B-Instruct")

# we can pass functions directly without FunctionTool -- the fn/docstring are parsed for the name/description
multiply_agent = ReActAgent(
    name="multiply_agent",
    description="Is able to multiply two integers",
    system_prompt="A helpful assistant that can use a tool to multiply numbers.",
    tools=[multiply],
    llm=llm,
)

addition_agent = ReActAgent(
    name="add_agent",
    description="Is able to add two integers",
    system_prompt="A helpful assistant that can use a tool to add numbers.",
    tools=[add],
    llm=llm,
)

# Create the workflow
workflow = AgentWorkflow(
    agents=[multiply_agent, addition_agent],
    root_agent="multiply_agent",
)

# Run the system
response = await workflow.run(user_msg="Can you add 5 and 3?")
```

Agent tools can also modify the workflow state we mentioned earlier. Before starting the workflow, we can provide an initial state dict that will be available to all agents.
The state is stored in the state key of the workflow context. It will be injected into the state_prompt which augments each new user message.

Let's inject a counter to count function calls by modifying the previous example:

```python
from llama_index.core.workflow import Context

# Define some tools
async def add(ctx: Context, a: int, b: int) -> int:
    """Add two numbers."""
    # update our count
    cur_state = await ctx.get("state")
    cur_state["num_fn_calls"] += 1
    await ctx.set("state", cur_state)

    return a + b

async def multiply(ctx: Context, a: int, b: int) -> int:
    """Multiply two numbers."""
    # update our count
    cur_state = await ctx.get("state")
    cur_state["num_fn_calls"] += 1
    await ctx.set("state", cur_state)

    return a * b

...

workflow = AgentWorkflow(
    agents=[multiply_agent, addition_agent],
    root_agent="multiply_agent"
    initial_state={"num_fn_calls": 0},
    state_prompt="Current state: {state}. User message: {msg}",
)

# run the workflow with context
ctx = Context(workflow)
response = await workflow.run(user_msg="Can you add 5 and 3?", ctx=ctx)

# pull out and inspect the state
state = await ctx.get("state")
print(state["num_fn_calls"])
```

Congratulations! You have now mastered the basics of Agents in LlamaIndex! 🎉

Let's continue with one final quiz to solidify your knowledge! 🚀
