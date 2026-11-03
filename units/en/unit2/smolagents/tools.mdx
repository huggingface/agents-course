<CourseFloatingBanner 
  classNames="absolute z-10 right-0 top-0"
  notebooks={[
    {label: "Google Colab", value: "https://colab.research.google.com/#fileId=https://huggingface.co/agents-course/notebooks/blob/main/unit2/smolagents/tools.ipynb"},
]} 
askForHelpUrl="http://hf.co/join/discord" />

# Tools

As we explored in [unit 1](https://huggingface.co/learn/agents-course/unit1/tools), agents use tools to perform various actions. In `smolagents`, tools are treated as **functions that an LLM can call within an agent system**.

To interact with a tool, the LLM needs an **interface description** with these key components:

- **Name**: What the tool is called
- **Tool description**: What the tool does
- **Input types and descriptions**: What arguments the tool accepts
- **Output type**: What the tool returns

For instance, while preparing for a party at Wayne Manor, Alfred needs various tools to gather information - from searching for catering services to finding party theme ideas. Here's how a simple search tool interface might look:

- **Name:** `web_search`
- **Tool description:** Searches the web for specific queries
- **Input:** `query` (string) - The search term to look up
- **Output:** String containing the search results

By using these tools, Alfred can make informed decisions and gather all the information needed for planning the perfect party.

Below, you can see an animation illustrating how a tool call is managed:

![Agentic pipeline from https://huggingface.co/docs/smolagents/conceptual_guides/react](https://huggingface.co/datasets/huggingface/documentation-images/resolve/main/transformers/Agent_ManimCE.gif)

## Tool Creation Methods

In `smolagents`, tools can be defined in two ways:
1. **Using the `@tool` decorator** for simple function-based tools
2. **Creating a subclass of `Tool`** for more complex functionality

### The `@tool` Decorator

The `@tool` decorator is the **recommended way to define simple tools**. Under the hood, smolagents will parse basic information about the function from Python. So if you name your function clearly and write a good docstring, it will be easier for the LLM to use.

Using this approach, we define a function with:

- **A clear and descriptive function name** that helps the LLM understand its purpose.
- **Type hints for both inputs and outputs** to ensure proper usage.
- **A detailed description**, including an `Args:` section where each argument is explicitly described. These descriptions provide valuable context for the LLM, so it's important to write them carefully.

#### Generating a tool that retrieves the highest-rated catering

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/smolagents/alfred-catering.jpg" alt="Alfred Catering"/>

> [!TIP]
> You can follow the code in <a href="https://huggingface.co/agents-course/notebooks/blob/main/unit2/smolagents/tools.ipynb" target="_blank">this notebook</a> that you can run using Google Colab.

Let's imagine that Alfred has already decided on the menu for the party, but now he needs help preparing food for such a large number of guests. To do so, he would like to hire a catering service and needs to identify the highest-rated options available. Alfred can leverage a tool to search for the best catering services in his area.

Below is an example of how Alfred can use the `@tool` decorator to make this happen:

```python
from smolagents import CodeAgent, InferenceClientModel, tool

# Let's pretend we have a function that fetches the highest-rated catering services.
@tool
def catering_service_tool(query: str) -> str:
    """
    This tool returns the highest-rated catering service in Gotham City.

    Args:
        query: A search term for finding catering services.
    """
    # Example list of catering services and their ratings
    services = {
        "Gotham Catering Co.": 4.9,
        "Wayne Manor Catering": 4.8,
        "Gotham City Events": 4.7,
    }

    # Find the highest rated catering service (simulating search query filtering)
    best_service = max(services, key=services.get)

    return best_service


agent = CodeAgent(tools=[catering_service_tool], model=InferenceClientModel())

# Run the agent to find the best catering service
result = agent.run(
    "Can you give me the name of the highest-rated catering service in Gotham City?"
)

print(result)   # Output: Gotham Catering Co.
```

### Defining a Tool as a Python Class

This approach involves creating a subclass of [`Tool`](https://huggingface.co/docs/smolagents/v1.8.1/en/reference/tools#smolagents.Tool).  For complex tools, we can implement a class instead of a Python function. The class wraps the function with metadata that helps the LLM understand how to use it effectively. In this class, we define:

- `name`: The tool's name.
- `description`: A description used to populate the agent's system prompt.
- `inputs`: A dictionary with keys `type` and `description`, providing information to help the Python interpreter process inputs.
- `output_type`: Specifies the expected output type.
- `forward`: The method containing the inference logic to execute.

Below, we can see an example of a tool built using `Tool` and how to integrate it within a `CodeAgent`.

#### Generating a tool to generate ideas about the superhero-themed party

Alfred's party at the mansion is a **superhero-themed event**, but he needs some creative ideas to make it truly special. As a fantastic host, he wants to surprise the guests with a unique theme.

To do this, he can use an agent that generates superhero-themed party ideas based on a given category. This way, Alfred can find the perfect party theme to wow his guests.

```python
from smolagents import Tool, CodeAgent, InferenceClientModel

class SuperheroPartyThemeTool(Tool):
    name = "superhero_party_theme_generator"
    description = """
    This tool suggests creative superhero-themed party ideas based on a category.
    It returns a unique party theme idea."""

    inputs = {
        "category": {
            "type": "string",
            "description": "The type of superhero party (e.g., 'classic heroes', 'villain masquerade', 'futuristic Gotham').",
        }
    }

    output_type = "string"

    def forward(self, category: str):
        themes = {
            "classic heroes": "Justice League Gala: Guests come dressed as their favorite DC heroes with themed cocktails like 'The Kryptonite Punch'.",
            "villain masquerade": "Gotham Rogues' Ball: A mysterious masquerade where guests dress as classic Batman villains.",
            "futuristic Gotham": "Neo-Gotham Night: A cyberpunk-style party inspired by Batman Beyond, with neon decorations and futuristic gadgets."
        }

        return themes.get(category.lower(), "Themed party idea not found. Try 'classic heroes', 'villain masquerade', or 'futuristic Gotham'.")

# Instantiate the tool
party_theme_tool = SuperheroPartyThemeTool()
agent = CodeAgent(tools=[party_theme_tool], model=InferenceClientModel())

# Run the agent to generate a party theme idea
result = agent.run(
    "What would be a good superhero party idea for a 'villain masquerade' theme?"
)

print(result)  # Output: "Gotham Rogues' Ball: A mysterious masquerade where guests dress as classic Batman villains."
```

With this tool, Alfred will be the ultimate super host, impressing his guests with a superhero-themed party they won't forget! 🦸‍♂️🦸‍♀️

## Default Toolbox

`smolagents` comes with a set of pre-built tools that can be directly injected into your agent. The [default toolbox](https://huggingface.co/docs/smolagents/guided_tour?build-a-tool=Decorate+a+function+with+%40tool#default-toolbox) includes:

- **PythonInterpreterTool**
- **FinalAnswerTool**
- **UserInputTool**
- **DuckDuckGoSearchTool**
- **GoogleSearchTool**
- **VisitWebpageTool**

Alfred could use various tools to ensure a flawless party at Wayne Manor:

- First, he could use the `DuckDuckGoSearchTool` to find creative superhero-themed party ideas.

- For catering, he'd rely on the `GoogleSearchTool` to find the highest-rated services in Gotham.

- To manage seating arrangements, Alfred could run calculations with the `PythonInterpreterTool`.

- Once everything is gathered, he'd compile the plan using the `FinalAnswerTool`.

With these tools, Alfred guarantees the party is both exceptional and seamless. 🦇💡

## Sharing and Importing Tools

One of the most powerful features of **smolagents** is its ability to share custom tools on the Hub and seamlessly integrate tools created by the community. This includes connecting with **HF Spaces** and **LangChain tools**, significantly enhancing Alfred's ability to orchestrate an unforgettable party at Wayne Manor. 🎭

With these integrations, Alfred can tap into advanced event-planning tools—whether it's adjusting the lighting for the perfect ambiance, curating the ideal playlist for the party, or coordinating with Gotham's finest caterers.

Here are examples showcasing how these functionalities can elevate the party experience:

### Sharing a Tool to the Hub

Sharing your custom tool with the community is easy! Simply upload it to your Hugging Face account using the `push_to_hub()` method.

For instance, Alfred can share his `party_theme_tool` to help others find the best catering services in Gotham. Here's how to do it:

```python
party_theme_tool.push_to_hub("{your_username}/party_theme_tool", token="<YOUR_HUGGINGFACEHUB_API_TOKEN>")
```

### Importing a Tool from the Hub

You can easily import tools created by other users using the `load_tool()` function. For example, Alfred might want to generate a promotional image for the party using AI. Instead of building a tool from scratch, he can leverage a predefined one from the community:

```python
from smolagents import load_tool, CodeAgent, InferenceClientModel

image_generation_tool = load_tool(
    "m-ric/text-to-image",
    trust_remote_code=True
)

agent = CodeAgent(
    tools=[image_generation_tool],
    model=InferenceClientModel()
)

agent.run("Generate an image of a luxurious superhero-themed party at Wayne Manor with made-up superheros.")
```

### Importing a Hugging Face Space as a Tool

You can also import a HF Space as a tool using `Tool.from_space()`. This opens up possibilities for integrating with thousands of spaces from the community for tasks from image generation to data analysis.

The tool will connect with the spaces Gradio backend using the `gradio_client`, so make sure to install it via `pip` if you don't have it already.

For the party, Alfred can use an existing HF Space for the generation of the AI-generated image to be used in the announcement (instead of the pre-built tool we mentioned before). Let's build it!

```python
from smolagents import CodeAgent, InferenceClientModel, Tool

image_generation_tool = Tool.from_space(
    "black-forest-labs/FLUX.1-schnell",
    name="image_generator",
    description="Generate an image from a prompt"
)

model = InferenceClientModel("Qwen/Qwen2.5-Coder-32B-Instruct")

agent = CodeAgent(tools=[image_generation_tool], model=model)

agent.run(
    "Improve this prompt, then generate an image of it.",
    additional_args={'user_prompt': 'A grand superhero-themed party at Wayne Manor, with Alfred overseeing a luxurious gala'}
)
```

### Importing a LangChain Tool


We'll discuss the `LangChain` framework in upcoming sections. For now, we just note that we can reuse LangChain tools in your smolagents workflow!

You can easily load LangChain tools using the `Tool.from_langchain()` method. Alfred, ever the perfectionist, is preparing for a spectacular superhero night at Wayne Manor while the Waynes are away. To make sure every detail exceeds expectations, he taps into LangChain tools to find top-tier entertainment ideas.

By using `Tool.from_langchain()`, Alfred effortlessly adds advanced search functionalities to his smolagent, enabling him to discover exclusive party ideas and services with just a few commands.

Here's how he does it:

We first need to install the `langchain` integration for `smolagents`.

```bash
pip install -U langchain-community
```

After installing the langchain integration, make sure to set your SerpAPI key.
This is required for search-based tools such as `SerpAPITool`:

```python
os.environ['SERPAPI_API_KEY'] = '...'
```

You can create a SerpAPI key [here](https://serpapi.com/)

```python
from langchain.agents import load_tools
from smolagents import CodeAgent, InferenceClientModel, Tool

search_tool = Tool.from_langchain(load_tools(["serpapi"])[0])

agent = CodeAgent(tools=[search_tool], model=model)

agent.run("Search for luxury entertainment ideas for a superhero-themed event, such as live performances and interactive experiences.")
```

### Importing a tool collection from any MCP server

`smolagents` also allows importing tools from the hundreds of MCP servers available on [glama.ai](https://glama.ai/mcp/servers) or [smithery.ai](https://smithery.ai). If you want to dive deeper about MCP, you can check our [free MCP Course](https://huggingface.co/learn/mcp-course/). 

<details>
<summary>Install mcp client</summary>

We first need to install the `mcp` integration for `smolagents`.

```bash
pip install "smolagents[mcp]"
```
</details>

The MCP servers tools can be loaded in a ToolCollection object as follow:

```python
import os
from smolagents import ToolCollection, CodeAgent
from mcp import StdioServerParameters
from smolagents import InferenceClientModel


model = InferenceClientModel("Qwen/Qwen2.5-Coder-32B-Instruct")


server_parameters = StdioServerParameters(
    command="uvx",
    args=["--quiet", "pubmedmcp@0.1.3"],
    env={"UV_PYTHON": "3.12", **os.environ},
)

with ToolCollection.from_mcp(server_parameters, trust_remote_code=True) as tool_collection:
    agent = CodeAgent(tools=[*tool_collection.tools], model=model, add_base_tools=True)
    agent.run("Please find a remedy for hangover.")
```

With this setup, Alfred can quickly discover luxurious entertainment options, ensuring Gotham's elite guests have an unforgettable experience. This tool helps him curate the perfect superhero-themed event for Wayne Manor! 🎉

## Resources

- [Tools Tutorial](https://huggingface.co/docs/smolagents/tutorials/tools) - Explore this tutorial to learn how to work with tools effectively.
- [Tools Documentation](https://huggingface.co/docs/smolagents/v1.8.1/en/reference/tools) - Comprehensive reference documentation on tools.
- [Tools Guided Tour](https://huggingface.co/docs/smolagents/v1.8.1/en/guided_tour#tools) - A step-by-step guided tour to help you build and utilize tools efficiently.
- [Building Effective Agents](https://huggingface.co/docs/smolagents/tutorials/building_good_agents) - A detailed guide on best practices for developing reliable and high-performance custom function agents.
