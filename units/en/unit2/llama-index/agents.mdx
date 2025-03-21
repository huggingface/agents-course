# Using Agents in LlamaIndex

Remember Alfred, our helpful butler agent from earlier? Well, he's about to get an upgrade!
Now that we understand the tools available in LlamaIndex, we can give Alfred new capabilities to serve us better.

But before we continue, let's remind ourselves what makes an agent like Alfred tick.
Back in Unit 1, we learned that:

> An Agent is a system that leverages an AI model to interact with its environment to achieve a user-defined objective. It combines reasoning, planning, and action execution (often via external tools) to fulfil tasks.

LlamaIndex supports **three main types of reasoning agents:**

![Agents](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/llama-index/agents.png)

1. `Function Calling Agents` - These work with AI models that can call specific functions.
2. `ReAct Agents` - These can work with any AI that does chat or text endpoint and deal with complex reasoning tasks.
3. `Advanced Custom Agents` - These use more complex methods to deal with more complex tasks and workflows.

<Tip>Find more information on advanced agents on <a href="https://github.com/run-llama/llama_index/blob/main/llama-index-core/llama_index/core/agent/workflow/base_agent.py">BaseWorkflowAgent</a></Tip>

## Initialising Agents

<Tip>
You can follow the code in <a href="https://huggingface.co/agents-course/notebooks/blob/main/unit2/llama-index/agents.ipynb" target="_blank">this notebook</a> that you can run using Google Colab.
</Tip>

To create an agent, we start by providing it with a **set of functions/tools that define its capabilities**.
Let's look at how to create an agent with some basic tools. As of this writing, the agent will automatically use the function calling API (if available), or a standard ReAct agent loop.

LLMs that support a tools/functions API are relatively new, but they provide a powerful way to call tools by avoiding specific prompting and allowing the LLM to create tool calls based on provided schemas.

ReAct agents are also good at complex reasoning tasks and can work with any LLM that has chat or text completion capabilities. They are more verbose, and show the reasoning behind certain actions that they take.

```python
from llama_index.llms.huggingface_api import HuggingFaceInferenceAPI
from llama_index.core.agent.workflow import AgentWorkflow
from llama_index.core.tools import FunctionTool

# define sample Tool -- type annotations, function names, and docstrings, are all included in parsed schemas!
def multiply(a: int, b: int) -> int:
    """Multiplies two integers and returns the resulting integer"""
    return a * b

# initialize llm
llm = HuggingFaceInferenceAPI(model_name="Qwen/Qwen2.5-Coder-32B-Instruct")

# initialize agent
agent = AgentWorkflow.from_tools_or_functions(
    [FunctionTool.from_defaults(multiply)],
    llm=llm
)
```

**Agents are stateless by default**, add remembering past interactions is opt-in using a `Context` object
This might be useful if you want to use an agent that needs to remember previous interactions, like a chatbot that maintains context across multiple messages or a task manager that needs to track progress over time.

```python
# stateless
response = await agent.run("What is 2 times 2?")

# remembering state
from llama_index.core.workflow import Context

ctx = Context(agent)

response = await agent.run("My name is Bob.", ctx=ctx)
response = await agent.run("What was my name again?", ctx=ctx)
```

You'll notice that agents in `LlamaIndex` are async because they use Python's `await` operator. If you are new to async code in Python, or need a refresher, they have an [excellent async guide](https://docs.llamaindex.ai/en/stable/getting_started/async_python/).

Now we've gotten the basics, let's take a look at how we can use more complex tools in our agents.

## Creating RAG Agents with QueryEngineTools

**Agentic RAG is a powerful way to use agents to answer questions about your data.** We can pass various tools to Alfred to help him answer questions.
However, instead of answering the question on top of documents automatically, Alfred can decide to use any other tool or flow to answer the question.

![Agentic RAG](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/llama-index/agentic-rag.png)

It is easy to **wrap `QueryEngine` as a tool** for an agent.
When doing so, we need to **define a name and description**. The LLM will use this information to correctly use the tool.
Let's see how to load in a `QueryEngineTool` using the `QueryEngine` we created in the [component section](components).

```python
from llama_index.core.tools import QueryEngineTool

query_engine = index.as_query_engine(llm=llm, similarity_top_k=3) # as shown in the Components in LlamaIndex section

query_engine_tool = QueryEngineTool.from_defaults(
    query_engine=query_engine,
    name="name",
    description="a specific description",
    return_direct=False,
)
query_engine_agent = AgentWorkflow.from_tools_or_functions(
    [query_engine_tool],
    llm=llm,
    system_prompt="You are a helpful assistant that has access to a database containing persona descriptions. "
)
```

## Creating Multi-agent systems

The `AgentWorkflow` class also directly supports multi-agent systems. By giving each agent a name and description, the system maintains a single active speaker, with each agent having the ability to hand off to another agent.

By narrowing the scope of each agent, we can help increase their general accuracy when responding to user messages.

**Agents in LlamaIndex can also directly be used as tools** for other agents, for more complex and custom scenarios.

```python
from llama_index.core.agent.workflow import (
    AgentWorkflow,
    FunctionAgent,
    ReActAgent,
)

# Define some tools
def add(a: int, b: int) -> int:
    """Add two numbers."""
    return a + b


def subtract(a: int, b: int) -> int:
    """Subtract two numbers."""
    return a - b


# Create agent configs
# NOTE: we can use FunctionAgent or ReActAgent here.
# FunctionAgent works for LLMs with a function calling API.
# ReActAgent works for any LLM.
calculator_agent = ReActAgent(
    name="calculator",
    description="Performs basic arithmetic operations",
    system_prompt="You are a calculator assistant. Use your tools for any math operation.",
    tools=[add, subtract],
    llm=llm,
)

query_agent = ReActAgent(
    name="info_lookup",
    description="Looks up information about XYZ",
    system_prompt="Use your tool to query a RAG system to answer information about XYZ",
    tools=[query_engine_tool],
    llm=llm
)

# Create and run the workflow
agent = AgentWorkflow(
    agents=[calculator_agent, query_agent], root_agent="calculator"
)

# Run the system
response = await agent.run(user_msg="Can you add 5 and 3?")
```

<Tip>Haven't learned enough yet? There is a lot more to discover about agents and tools in LlamaIndex within the <a href="https://docs.llamaindex.ai/en/stable/examples/agent/agent_workflow_basic/">AgentWorkflow Basic Introduction</a> or the <a href="https://docs.llamaindex.ai/en/stable/understanding/agent/">Agent Learning Guide</a>, where you can read more about streaming, context serialization, and human-in-the-loop!</Tip>

Now that we understand the basics of agents and tools in LlamaIndex, let's see how we can use LlamaIndex to **create configurable and manageable workflows!**
