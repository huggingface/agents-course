# Creating Your Gala Agent

Now that we've built all the necessary components for Alfred, it's time to bring everything together into a complete agent that can help host our extravagant gala. 

In this section, we'll combine the guest information retrieval, web search, weather information, and Hub stats tools into a single powerful agent.

## Assembling Alfred: The Complete Agent

Instead of reimplementing all the tools we've created in previous sections, we'll import them from their respective modules which we saved in the `tools.py` and `retriever.py` files.

> [!TIP]
> If you haven't implemented the tools yet, go back to the <a href="./tools">tools</a> and <a href="./invitees">retriever</a> sections to implement them, and add them to the <code>tools.py</code> and <code>retriever.py</code> files.

Let's import the necessary libraries and tools from the previous sections:

<hfoptions id="agents-frameworks">
<hfoption id="smolagents">

```python
# Import necessary libraries
import random
from smolagents import CodeAgent, InferenceClientModel

# Import our custom tools from their modules
from tools import DuckDuckGoSearchTool, WeatherInfoTool, HubStatsTool
from retriever import load_guest_dataset
```

Now, let's combine all these tools into a single agent:

```python
# Initialize the Hugging Face model
model = InferenceClientModel()

# Initialize the web search tool
search_tool = DuckDuckGoSearchTool()

# Initialize the weather tool
weather_info_tool = WeatherInfoTool()

# Initialize the Hub stats tool
hub_stats_tool = HubStatsTool()

# Load the guest dataset and initialize the guest info tool
guest_info_tool = load_guest_dataset()

# Create Alfred with all the tools
alfred = CodeAgent(
    tools=[guest_info_tool, weather_info_tool, hub_stats_tool, search_tool], 
    model=model,
    add_base_tools=True,  # Add any additional base tools
    planning_interval=3   # Enable planning every 3 steps
)
```

</hfoption>
<hfoption id="llama-index">

```python
# Import necessary libraries
from llama_index.core.agent.workflow import AgentWorkflow
from llama_index.llms.huggingface_api import HuggingFaceInferenceAPI

from tools import search_tool, weather_info_tool, hub_stats_tool
from retriever import guest_info_tool
```

Now, let's combine all these tools into a single agent:

```python
# Initialize the Hugging Face model
llm = HuggingFaceInferenceAPI(model_name="Qwen/Qwen2.5-Coder-32B-Instruct")

# Create Alfred with all the tools
alfred = AgentWorkflow.from_tools_or_functions(
    [guest_info_tool, search_tool, weather_info_tool, hub_stats_tool],
    llm=llm,
)
```

</hfoption>
<hfoption id="langgraph">

```python
from typing import TypedDict, Annotated
from langgraph.graph.message import add_messages
from langchain_core.messages import AnyMessage, HumanMessage, AIMessage
from langgraph.prebuilt import ToolNode
from langgraph.graph import START, StateGraph
from langgraph.prebuilt import tools_condition
from langchain_huggingface import HuggingFaceEndpoint, ChatHuggingFace

from tools import DuckDuckGoSearchRun, weather_info_tool, hub_stats_tool
from retriever import guest_info_tool
```

Now, let’s combine all these tools into a single agent:

```python
# Initialize the web search tool
search_tool = DuckDuckGoSearchRun()

# Generate the chat interface, including the tools
llm = HuggingFaceEndpoint(
    repo_id="Qwen/Qwen2.5-Coder-32B-Instruct",
    huggingfacehub_api_token=HUGGINGFACEHUB_API_TOKEN,
)

chat = ChatHuggingFace(llm=llm, verbose=True)
tools = [guest_info_tool, search_tool, weather_info_tool, hub_stats_tool]
chat_with_tools = chat.bind_tools(tools)

# Generate the AgentState and Agent graph
class AgentState(TypedDict):
    messages: Annotated[list[AnyMessage], add_messages]

def assistant(state: AgentState):
    return {
        "messages": [chat_with_tools.invoke(state["messages"])],
    }

## The graph
builder = StateGraph(AgentState)

# Define nodes: these do the work
builder.add_node("assistant", assistant)
builder.add_node("tools", ToolNode(tools))

# Define edges: these determine how the control flow moves
builder.add_edge(START, "assistant")
builder.add_conditional_edges(
    "assistant",
    # If the latest message requires a tool, route to tools
    # Otherwise, provide a direct response
    tools_condition,
)
builder.add_edge("tools", "assistant")
alfred = builder.compile()
```
</hfoption>
</hfoptions>

Your agent is now ready to use!

## Using Alfred: End-to-End Examples

Now that Alfred is fully equipped with all the necessary tools, let's see how he can help with various tasks during the gala.

### Example 1: Finding Guest Information

Let's see how Alfred can help us with our guest information.

<hfoptions id="agents-frameworks">
<hfoption id="smolagents">

```python
query = "Tell me about 'Lady Ada Lovelace'"
response = alfred.run(query)

print("🎩 Alfred's Response:")
print(response)
```

Expected output:

```
🎩 Alfred's Response:
Based on the information I retrieved, Lady Ada Lovelace is an esteemed mathematician and friend. She is renowned for her pioneering work in mathematics and computing, often celebrated as the first computer programmer due to her work on Charles Babbage's Analytical Engine. Her email address is ada.lovelace@example.com.
```

</hfoption>
<hfoption id="llama-index">

```python
query = "Tell me about Lady Ada Lovelace. What's her background?"
response = await alfred.run(query)

print("🎩 Alfred's Response:")
print(response.response.blocks[0].text)
```

Expected output:

```
🎩 Alfred's Response:
Lady Ada Lovelace was an English mathematician and writer, best known for her work on Charles Babbage's Analytical Engine. She was the first to recognize that the machine had applications beyond pure calculation.
```

</hfoption>
<hfoption id="langgraph">

```python
response = alfred.invoke({"messages": "Tell me about 'Lady Ada Lovelace'"})

print("🎩 Alfred's Response:")
print(response['messages'][-1].content)
```

Expected output:

```
🎩 Alfred's Response:
Ada Lovelace, also known as Augusta Ada King, Countess of Lovelace, was an English mathematician and writer. Born on December 10, 1815, and passing away on November 27, 1852, she is renowned for her work on Charles Babbage's Analytical Engine, a proposed mechanical general-purpose computer. Ada Lovelace is celebrated as one of the first computer programmers because she created a program for the Analytical Engine in 1843. She recognized that the machine could be used for more than mere calculation, envisioning its potential in a way that few did at the time. Her contributions to the field of computer science laid the groundwork for future developments. A day in October, designated as Ada Lovelace Day, honors women's contributions to science and technology, inspired by Lovelace's pioneering work.
```

</hfoption>
</hfoptions>


### Example 2: Checking the Weather for Fireworks

Let's see how Alfred can help us with the weather.

<hfoptions id="agents-frameworks">
<hfoption id="smolagents">

```python
query = "What's the weather like in Paris tonight? Will it be suitable for our fireworks display?"
response = alfred.run(query)

print("🎩 Alfred's Response:")
print(response)
```

Expected output (will vary due to randomness):
```
🎩 Alfred's Response:
I've checked the weather in Paris for you. Currently, it's clear with a temperature of 25°C. These conditions are perfect for the fireworks display tonight. The clear skies will provide excellent visibility for the spectacular show, and the comfortable temperature will ensure the guests can enjoy the outdoor event without discomfort.
```

</hfoption>
<hfoption id="llama-index">

```python
query = "What's the weather like in Paris tonight? Will it be suitable for our fireworks display?"
response = await alfred.run(query)

print("🎩 Alfred's Response:")
print(response)
```

Expected output:

```
🎩 Alfred's Response:
The weather in Paris tonight is rainy with a temperature of 15°C. Given the rain, it may not be suitable for a fireworks display.
```

</hfoption>
<hfoption id="langgraph">

```python
response = alfred.invoke({"messages": "What's the weather like in Paris tonight? Will it be suitable for our fireworks display?"})

print("🎩 Alfred's Response:")
print(response['messages'][-1].content)
```

Expected output:

```
🎩 Alfred's Response:
The weather in Paris tonight is rainy with a temperature of 15°C, which may not be suitable for your fireworks display.
```
</hfoption>
</hfoptions>

### Example 3: Impressing AI Researchers

Let's see how Alfred can help us impress AI researchers.

<hfoptions id="agents-frameworks">
<hfoption id="smolagents">

```python
query = "One of our guests is from Qwen. What can you tell me about their most popular model?"
response = alfred.run(query)

print("🎩 Alfred's Response:")
print(response)
```

Expected output:

```
🎩 Alfred's Response:
The most popular Qwen model is Qwen/Qwen2.5-VL-7B-Instruct with 3,313,345 downloads.
```
</hfoption>
<hfoption id="llama-index">

```python
query = "One of our guests is from Google. What can you tell me about their most popular model?"
response = await alfred.run(query)

print("🎩 Alfred's Response:")
print(response)
```

Expected output:

```
🎩 Alfred's Response:
The most popular model by Google on the Hugging Face Hub is google/electra-base-discriminator, with 28,546,752 downloads.
```

</hfoption>
<hfoption id="langgraph">

```python
response = alfred.invoke({"messages": "One of our guests is from Qwen. What can you tell me about their most popular model?"})

print("🎩 Alfred's Response:")
print(response['messages'][-1].content)
```

Expected output:

```
🎩 Alfred's Response:
The most downloaded model by Qwen is Qwen/Qwen2.5-VL-7B-Instruct with 3,313,345 downloads.
```
</hfoption>
</hfoptions>

### Example 4: Combining Multiple Tools

Let's see how Alfred can help us prepare for a conversation with Dr. Nikola Tesla.

<hfoptions id="agents-frameworks">
<hfoption id="smolagents">

```python
query = "I need to speak with Dr. Nikola Tesla about recent advancements in wireless energy. Can you help me prepare for this conversation?"
response = alfred.run(query)

print("🎩 Alfred's Response:")
print(response)
```

Expected output:

```
🎩 Alfred's Response:
I've gathered information to help you prepare for your conversation with Dr. Nikola Tesla.

Guest Information:
Name: Dr. Nikola Tesla
Relation: old friend from university days
Description: Dr. Nikola Tesla is an old friend from your university days. He's recently patented a new wireless energy transmission system and would be delighted to discuss it with you. Just remember he's passionate about pigeons, so that might make for good small talk.
Email: nikola.tesla@gmail.com

Recent Advancements in Wireless Energy:
Based on my web search, here are some recent developments in wireless energy transmission:
1. Researchers have made progress in long-range wireless power transmission using focused electromagnetic waves
2. Several companies are developing resonant inductive coupling technologies for consumer electronics
3. There are new applications in electric vehicle charging without physical connections

Conversation Starters:
1. "I'd love to hear about your new patent on wireless energy transmission. How does it compare to your original concepts from our university days?"
2. "Have you seen the recent developments in resonant inductive coupling for consumer electronics? What do you think of their approach?"
3. "How are your pigeons doing? I remember your fascination with them."

This should give you plenty to discuss with Dr. Tesla while demonstrating your knowledge of his interests and recent developments in his field.
```

</hfoption>
<hfoption id="llama-index">

```python
query = "I need to speak with Dr. Nikola Tesla about recent advancements in wireless energy. Can you help me prepare for this conversation?"
response = await alfred.run(query)

print("🎩 Alfred's Response:")
print(response)
```

Expected output:

```
🎩 Alfred's Response:
Here are some recent advancements in wireless energy that you might find useful for your conversation with Dr. Nikola Tesla:

1. **Advancements and Challenges in Wireless Power Transfer**: This article discusses the evolution of wireless power transfer (WPT) from conventional wired methods to modern applications, including solar space power stations. It highlights the initial focus on microwave technology and the current demand for WPT due to the rise of electric devices.

2. **Recent Advances in Wireless Energy Transfer Technologies for Body-Interfaced Electronics**: This article explores wireless energy transfer (WET) as a solution for powering body-interfaced electronics without the need for batteries or lead wires. It discusses the advantages and potential applications of WET in this context.

3. **Wireless Power Transfer and Energy Harvesting: Current Status and Future Trends**: This article provides an overview of recent advances in wireless power supply methods, including energy harvesting and wireless power transfer. It presents several promising applications and discusses future trends in the field.

4. **Wireless Power Transfer: Applications, Challenges, Barriers, and the
```

</hfoption>
<hfoption id="langgraph">

```python
response = alfred.invoke({"messages":"I need to speak with 'Dr. Nikola Tesla' about recent advancements in wireless energy. Can you help me prepare for this conversation?"})

print("🎩 Alfred's Response:")
print(response['messages'][-1].content)
```

Expected output:

```
Based on the provided information, here are key points to prepare for the conversation with 'Dr. Nikola Tesla' about recent advancements in wireless energy:\n1. **Wireless Power Transmission (WPT):** Discuss how WPT revolutionizes energy transfer by eliminating the need for cords and leveraging mechanisms like inductive and resonant coupling.\n2. **Advancements in Wireless Charging:** Highlight improvements in efficiency, faster charging speeds, and the rise of Qi/Qi2 certified wireless charging solutions.\n3. **5G-Advanced Innovations and NearLink Wireless Protocol:** Mention these as developments that enhance speed, security, and efficiency in wireless networks, which can support advanced wireless energy technologies.\n4. **AI and ML at the Edge:** Talk about how AI and machine learning will rely on wireless networks to bring intelligence to the edge, enhancing automation and intelligence in smart homes and buildings.\n5. **Matter, Thread, and Security Advancements:** Discuss these as key innovations that drive connectivity, efficiency, and security in IoT devices and systems.\n6. **Breakthroughs in Wireless Charging Technology:** Include any recent breakthroughs or studies, such as the one from Incheon National University, to substantiate the advancements in wireless charging.
```
</hfoption>
</hfoptions>

## Advanced Features: Conversation Memory

To make Alfred even more helpful during the gala, we can enable conversation memory so he remembers previous interactions:

<hfoptions id="agents-frameworks">
<hfoption id="smolagents">

```python
# Create Alfred with conversation memory
alfred_with_memory = CodeAgent(
    tools=[guest_info_tool, weather_info_tool, hub_stats_tool, search_tool], 
    model=model,
    add_base_tools=True,
    planning_interval=3
)

# First interaction
response1 = alfred_with_memory.run("Tell me about Lady Ada Lovelace.")
print("🎩 Alfred's First Response:")
print(response1)

# Second interaction (referencing the first)
response2 = alfred_with_memory.run("What projects is she currently working on?", reset=False)
print("🎩 Alfred's Second Response:")
print(response2)
```

</hfoption>
<hfoption id="llama-index">

```python
from llama_index.core.workflow import Context

alfred = AgentWorkflow.from_tools_or_functions(
    [guest_info_tool, search_tool, weather_info_tool, hub_stats_tool],
    llm=llm
)

# Remembering state
ctx = Context(alfred)

# First interaction
response1 = await alfred.run("Tell me about Lady Ada Lovelace.", ctx=ctx)
print("🎩 Alfred's First Response:")
print(response1)

# Second interaction (referencing the first)
response2 = await alfred.run("What projects is she currently working on?", ctx=ctx)
print("🎩 Alfred's Second Response:")
print(response2)
```

</hfoption>
<hfoption id="langgraph">

```python
# First interaction
response = alfred.invoke({"messages": [HumanMessage(content="Tell me about 'Lady Ada Lovelace'. What's her background and how is she related to me?")]})


print("🎩 Alfred's Response:")
print(response['messages'][-1].content)
print()

# Second interaction (referencing the first)
response = alfred.invoke({"messages": response["messages"] + [HumanMessage(content="What projects is she currently working on?")]})

print("🎩 Alfred's Response:")
print(response['messages'][-1].content)
```

</hfoption>
</hfoptions>

Notice that none of these three agent approaches directly couple memory with the agent. Is there a specific reason for this design choice 🧐?
* smolagents: Memory is not preserved across different execution runs, you must explicitly state it using `reset=False`.
* LlamaIndex: Requires explicitly adding a context object for memory management within a run.
* LangGraph: Offers options to retrieve previous messages or utilize a dedicated [MemorySaver](https://langchain-ai.github.io/langgraph/tutorials/introduction/#part-3-adding-memory-to-the-chatbot) component.

## Conclusion

Congratulations! You've successfully built Alfred, a sophisticated agent equipped with multiple tools to help host the most extravagant gala of the century. Alfred can now:

1. Retrieve detailed information about guests
2. Check weather conditions for planning outdoor activities
3. Provide insights about influential AI builders and their models
4. Search the web for the latest information
5. Maintain conversation context with memory

With these capabilities, Alfred is ready to ensure your gala is a resounding success, impressing guests with personalized attention and up-to-date information.
