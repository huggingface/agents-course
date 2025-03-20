# What is `LangGraph`?

`LangGraph` is a framework developed by [LangChain](https://www.langchain.com/) **to manage the control flow of applications that integrate an LLM**.

## Is `LangGraph` different from `LangChain`?

LangChain provides a standard interface to interact with models and other components, useful for retrieval, LLM calls and tools calls.
The classes from LangChain might be used in LangGraph, but do not HAVE to be used. 

The packages are different and can be used in isolation, but, in the end, all resources you will find online use both packages hand in hand.

## When should I use `LangGraph`?
### Control vs freedom

When designing AI applications, you face a fundamental trade-off between **control** and **freedom**:

- **Freedom** gives your LLM more room to be creative and tackle unexpected problems.
- **Control** allows you to ensure predictable behavior and maintain guardrails.

Code Agents, like the ones you can encounter in *smolagents*, are very free. They can call multiple tools in a single action step, create their own tools, etc. However, this behavior can make them less predictable and less controllable than a regular Agent working with JSON!

`LangGraph` is on the other end of the spectrum, it shines when you need **"Control"** on the execution of your agent. 

LangGraph is particularly valuable when you need **Control over your applications**. It gives you the tools to build an application that follows a predictable process while still leveraging the power of LLMs. 

Put simply, if your application involves a series of steps that need to be orchestrated in a specific way, with decisions being made at each junction point, **LangGraph provides the structure you need**.

As an example, let's say we want to build an LLM assistant that can answer some questions over some documents.

Since LLMs understand text the best, before being able to answer the question, you will need to convert other complex modalities (charts, tables) into text. However, that choice depends on the type of document you have!

This is a branching that I chose to represent as follow : 

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/LangGraph/flow.png" alt="Control flow"/>

> 💡 **Tip:** The left part is not an agent, as here no tool call is involved. but the right part will need to write some code to query the xls ( convert to pandas and manipulate it ).

While this branching is deterministic, you can also design branching that are conditioned on the output of an LLM making them undeterministic.

The key scenarios where LangGraph excels include:

- **Multi-step reasoning processes** that need explicit control on the flow
- **Applications requiring persistence of state** between steps
- **Systems that combine deterministic logic with AI capabilities**
- **Workflows that need human-in-the-loop interventions**
- **Complex agent architectures** with multiple components working together

In essence, whenever possible, **as a human**, design a flow of actions based on the output of each action, and decide what to execute next accordingly. In this case, LangGraph is the correct framework for you!

`LangGraph` is, in my opinion, the most production-ready agent framework on the market.

## How does LangGraph work?

At its core, `LangGraph` uses a directed graph structure to define the flow of your application:

- **Nodes** represent individual processing steps (like calling an LLM, using a tool, or making a decision).
- **Edges** define the possible transitions between steps.
- **State** is user defined and maintained and passed between nodes during execution. When deciding which node to target next, this is the current state that we look at.

We will explore those fundamental blocks more in the next chapter! 

## How is it different from regular python? Why do I need LangGraph?

You might wonder: "I could just write regular Python code with if-else statements to handle all these flows, right?" 

While technically true, LangGraph offers **some advantages** over vanilla Python for building complex systems. You could build the same application without LangGraph, but it builds easier tools and abstractions for you.

It includes states, visualization, logging (traces), built-in human-in-the-loop, and more.
