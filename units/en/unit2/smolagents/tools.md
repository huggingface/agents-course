# Tools  

As we explored in unit 1, agents use tools to perform various actions. In `smolagents`, tools are treated as functions that an LLM can call within an agent system. To interact with a tool, the LLM needs an **interface description**, which includes the following components:  

- **Name**  
- **Tool description**  
- **Input types and their descriptions**  
- **Output type**  

For instance, Alfred, preparing for a party at Wayne Manor, may need to utilize several tools to gather information. This could involve searching for catering services, finding superhero party theme ideas, or identifying the best entertainment options for the guests. To do this, he can use the `web_search` tool. The interface for this tool might look like the following:

- **Name:** `web_search`
- **Tool description:** A tool that allows searching the web for specific queries.
- **Input types and their descriptions:** `arguments` (a string representing the search query)
- **Output type:** A string representing the search results.

By using these tools, the agent can make informed decisions and gather relevant information for any aspect of the party planning.

Below, you can see an animation illustrating how a tool call is managed:

![Agentic pipeline from https://huggingface.co/docs/smolagents/conceptual_guides/react](https://huggingface.co/datasets/huggingface/documentation-images/resolve/main/transformers/Agent_ManimCE.gif)

## General Structure  

In `smolagents`, tools can be defined in two ways:  
1. **Using the `@tool` decorator** to define a function-based tool. 
2. **Creating a subclass of `Tool`**, which provides useful methods.    

### <code>@tool</code> Decorator  

The `@tool` decorator is the recommended way to define simple tools. Under the hood, smolagents will parse basic information about the function from Python. So if you name you function clearly and a good docstring, it will be easier for the LLM to use. Using this approach, we define a function with:  

- **A clear and descriptive function name** that helps the LLM understand its purpose.  
- **Type hints for both inputs and outputs** to ensure proper usage.  
- **A detailed description**, including an `Args:` section where each argument is explicitly described. These descriptions provide valuable context for the LLM, so it's important to write them carefully.  

#### Generating a tool that retrieves the highest-rated catering

Let's imagine that Alfred has already decided on the menu for the party, but now he needs help preparing food for such a large number of guests. To do so, he would like to hire a catering service and needs to identify the highest-rated options available. Alfred can leverage a tool to search for the best catering services in his area. Below is an example of how Alfred can use the `@tool` decorator to make this happen:

```python
from smolagents import CodeAgent, HfApiModel, tool

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


agent = CodeAgent(tools=[catering_service_tool], model=HfApiModel())

# Run the agent to find the best catering service
result = agent.run(
    "Can you give me the name of the highest-rated catering service in Gotham City?"
)

print(result)   # Output: Gotham Catering Co.
```

### Defining a Tool as a Python Class  

This approach involves creating a subclass of [`Tool`](https://huggingface.co/docs/smolagents/v1.8.1/en/reference/tools#smolagents.Tool).  For complex tools, we can implement a class instead of a Python function. The class wraps the function with metadata that helps the LLM understand how to use it effectively. In this class, we define:  

- `name`: The tool’s name.  
- `description`: A description used to populate the agent's system prompt.  
- `inputs`: A dictionary with keys `type` and `description`, providing information to help the Python interpreter process inputs.  
- `output_type`: Specifies the expected output type.  
- `forward`: The method containing the inference logic to execute.

Below, we can see an example of a tool built using `Tool` and to integrate it within a `CodeAgent`.

#### Generating a tool to generate ideas about the superhero-themed party

Alfred's party at the mansion is a **superhero-themed event**, but he needs some creative ideas to make it truly special. As a fantastic host, he wants to surprise the guests with a unique theme. To do this, he can use an agent that generates superhero-themed party ideas based on a given category. This way, Alfred can find the perfect party theme to wow his guests.

```python
from smolagents import Tool, CodeAgent, HfApiModel

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
agent = CodeAgent(tools=[party_theme_tool], model=HfApiModel())

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

Alfred could use various tools to ensure a flawless party at Wayne Manor. First, he could use the `DuckDuckGoSearchTool` to find creative superhero-themed party ideas. For catering, he'd rely on the `GoogleSearchTool` to find the highest-rated services in Gotham. To manage seating arrangements, Alfred could run calculations with the `PythonInterpreterTool`. Once everything is gathered, he'd compile the plan using the `FinalAnswerTool`. Lastly, the `VisitWebpageTool` would keep him updated on any changes, ensuring a smooth event. With these tools, Alfred guarantees the party is both exceptional and seamless. 🦇💡

## Sharing and Importing Tools

One of the most powerful features of **smolagents** is its ability to share custom tools on the Hub and seamlessly integrate tools created by the community. This includes connecting with **HF Spaces** and **LangChain tools**, significantly enhancing Alfred’s ability to orchestrate an unforgettable party at Wayne Manor. 🎭 

With these integrations, Alfred can tap into advanced event-planning tools—whether it’s adjusting the lighting for the perfect ambiance, curating the ideal playlist for the party, or coordinating with Gotham’s finest caterers.  

Here are examples showcasing how these functionalities can elevate the party experience:

### Sharing a Tool to the Hub

Sharing your custom tool with the community is easy! Simply upload it to your Hugging Face account using the `push_to_hub()` method.

For instance, Alfred can share his `catering_service_tool` to help others find the best catering services in Gotham. Here’s how to do it:

```python
party_theme_tool.push_to_hub("{your_username}/catering_service_tool", token="<YOUR_HUGGINGFACEHUB_API_TOKEN>")
```

### Importing a Tool from the Hub

You can easily import tools created by other users using the `load_tool()` function. For example, Alfred might want to generate a promotional image for the party using AI. Instead of building a tool from scratch, he can leverage a predefined one from the community: 

```python
from smolagents import load_tool, CodeAgent, HfApiModel

image_generation_tool = load_tool(
    "m-ric/text-to-image",
    trust_remote_code=True
)

agent = CodeAgent(
    tools=[image_generation_tool],
    model=HfApiModel()
)

agent.run("Generate an image of a luxurious superhero-themed party at Wayne Manor with made-up superheros.")
```

### Importing a Hugging Face Space as a Tool

You can also import a HF Space as a tool using `Tool.from_space()`. This opens up possibilities for integrating with thousands of spaces from the community for tasks from image generation to data analysis. The tool will connect with the spaces Gradio backend using the `gradio_client`, so make sure to install it via `pip` if you don't have it already. For the party, Alfred can also use a HF Space directly for the geneation of the previous annoucement AI-generated image. Let's build it!

```python
from smolagents import CodeAgent, HfApiModel, Tool

image_generation_tool = Tool.from_space(
    "black-forest-labs/FLUX.1-schnell",
    name="image_generator",
    description="Generate an image from a prompt"
)

model = HfApiModel("Qwen/Qwen2.5-Coder-32B-Instruct")

agent = CodeAgent(tools=[image_generation_tool], model=model)

agent.run(
    "Improve this prompt, then generate an image of it.", 
    additional_args={'user_prompt': 'A grand superhero-themed party at Wayne Manor, with Alfred overseeing a luxurious gala'}
)
```

### Importing a LangChain Tool

You can easily load LangChain tools using the `Tool.from_langchain()` method. Alfred, ever the perfectionist, is preparing for a spectacular superhero night at Wayne Manor while the Waynes are away. To make sure every detail exceeds expectations, he taps into LangChain tools to find top-tier entertainment ideas.

By using `Tool.from_langchain()`, Alfred effortlessly adds advanced search functionalities to his smolagent, enabling him to discover exclusive party ideas and services with just a few commands.

Here’s how he does it:

```python
from langchain.agents import load_tools
from smolagents import CodeAgent, HfApiModel, Tool

search_tool = Tool.from_langchain(load_tools(["serpapi"])[0])

agent = CodeAgent(tools=[search_tool], model=model)

agent.run("Search for luxury entertainment ideas for a superhero-themed event, such as live performances and interactive experiences.")
```

With this setup, Alfred can quickly discover luxurious entertainment options, ensuring Gotham’s elite guests have an unforgettable experience. This tool helps him curate the perfect superhero-themed event for Wayne Manor! 🎉

## Resources

- [Tools Tutorial](https://huggingface.co/docs/smolagents/tutorials/tools) - Explore this tutorial to learn how to work with tools effectively.
- [Tools Documentation](https://huggingface.co/docs/smolagents/v1.8.1/en/reference/tools) - Comprehensive reference documentation on tools.
- [Tools Guided Tour](https://huggingface.co/docs/smolagents/v1.8.1/en/guided_tour#tools) - A step-by-step guided tour to help you build and utilize tools efficiently.
- [Building Effective Agents](https://huggingface.co/docs/smolagents/tutorials/building_good_agents) - A detailed guide on best practices for developing reliable and high-performance custom function agents.