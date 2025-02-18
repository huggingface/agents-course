# Multi-Agent Systems

Multi-agent systems enable specialized agents to collaborate on complex tasks, improving modularity, scalability, and robustness. Instead of relying on a single agent for all operations, tasks are distributed among agents with distinct capabilities.

In **smolagents**, different agents can be combined to generate Python code, call external tools, perform web searches, and more. By orchestrating these agents, we can create powerful workflows, such as:

- A **Manager Agent** that delegates tasks.  
- A **Code Interpreter Agent** that executes Python code.  
- A **Web Search Agent** that retrieves information from the internet.  

The diagram below illustrates a simple multi-agent architecture where a **Manager Agent** coordinates a **Code Interpreter Tool** and a **Web Search Agent**, which in turn utilizes tools like `Web Search` and `Visit Webpage` to gather relevant information.

<img src="https://mermaid.ink/img/pako:eNp1kc1qhTAQRl9FUiQb8wIpdNO76eKubrmFks1oRg3VSYgjpYjv3lFL_2hnMWQOJwn5sqgmelRWleUSKLAtFs09jqhtoWuYUFfFAa6QA9QDTnpzamheuhxn8pt40-6l13UtS0ddhtQXj6dbR4XUGQg6zEYasTF393KjeSDGnDJKNxzj8I_7hLW5IOSmP9CH9hv_NL-d94d4DVNg84p1EnK4qlIj5hGClySWbadT-6OdsrL02MI8sFOOVkciw8zx8kaNspxnrJQE0fXKtjBMMs3JA-MpgOQwftIE9Bzj14w-cMznI_39E9Z3p0uFoA?type=png" style='background: white;'>

## Multi-Agent Systems in Action  

A multi-agent system consists of multiple specialized agents working together under the coordination of an **Orchestrator Agent**. This approach enables complex workflows by distributing tasks among agents with distinct roles.  

For example, a **Multi-Agent RAG system** can integrate:  
- A **Web Agent** for browsing the internet.  
- A **Retriever Agent** for fetching information from knowledge bases.  
- An **Image Generation Agent** for producing visuals.  

All of these agents operate under an orchestrator that manages task delegation and interaction.  

# Solving a complex task with a multi-agent hierarchy

The reception is approaching! With your help, Alfred is now nearly finished with the preparations.

But now there's a problem: the Batmobile has disappeared. Alfred needs to find a replacement, and find it quickly.

Fortunately, a few biopics have been done on Bruce Wayne's life, so maybe Alfred could get a car left behind on one of the movie set, and re-engineer it up to modern standards, which certainly would include a full self-driving option.

But this could be anywhere in the filming locations around the world - which could be numerous.

So Alfred wants your help. Could you build an agent able to solve this task?

> 👉 Find all Batman filming locations in the world, calculate the time to transfer via cargo plane to there, and represent them on a map, with a color varying by cargo plane transfer time. Also represent some supercar factories with the same cargo plane transfer time.

Let's build this!

```python
# We first make a tool to get the cargo plane transfer time.
import math
from typing import Optional, Tuple
from smolagents import tool


@tool
def calculate_cargo_travel_time(
    origin_coords: Tuple[float, float],
    destination_coords: Tuple[float, float],
    cruising_speed_kmh: Optional[float] = 750.0,  # Average speed for cargo planes
) -> float:
    """
    Calculate the travel time for a cargo plane between two points on Earth using great-circle distance.

    Args:
        origin_coords: Tuple of (latitude, longitude) for the starting point
        destination_coords: Tuple of (latitude, longitude) for the destination
        cruising_speed_kmh: Optional cruising speed in km/h (defaults to 750 km/h for typical cargo planes)

    Returns:
        float: The estimated travel time in hours

    Example:
        >>> # Chicago (41.8781° N, 87.6298° W) to Sydney (33.8688° S, 151.2093° E)
        >>> result = calculate_cargo_travel_time((41.8781, -87.6298), (-33.8688, 151.2093))
    """

    def to_radians(degrees: float) -> float:
        return degrees * (math.pi / 180)

    # Extract coordinates
    lat1, lon1 = map(to_radians, origin_coords)
    lat2, lon2 = map(to_radians, destination_coords)

    # Earth's radius in kilometers
    EARTH_RADIUS_KM = 6371.0

    # Calculate great-circle distance using the haversine formula
    dlon = lon2 - lon1
    dlat = lat2 - lat1

    a = math.sin(dlat / 2) ** 2 + math.cos(lat1) * math.cos(lat2) * math.sin(dlon / 2) ** 2
    c = 2 * math.asin(math.sqrt(a))
    distance = EARTH_RADIUS_KM * c

    # Add 10% to account for non-direct routes and air traffic controls
    actual_distance = distance * 1.1

    # Calculate flight time
    # Add 1 hour for takeoff and landing procedures
    flight_time = (actual_distance / cruising_speed_kmh) + 1.0

    # Format the results
    return flight_time


print(calculate_cargo_travel_time((41.8781, -87.6298), (-33.8688, 151.2093)))import os
```

```python
from PIL import Image
from smolagents import CodeAgent, DuckDuckGoSearchTool, OpenAIServerModel, VisitWebpageTool

model = OpenAIServerModel(model_id="gpt-4o")
```

We can start with creating a baseline, simple agent to give us a simple report.

```python
task = """Find all Batman filming locations in the world, calculate the time to transfer via cargo plane to here (we're in Gotham, 40.7128° N, 74.0060° W), and return them to me as a pandas dataframe.
Also give me some supercar factories with the same cargo plane transfer time."""
```

```python
import pandas as pd

agent = CodeAgent(
    model=model,
    tools=[DuckDuckGoSearchTool(), VisitWebpageTool(), calculate_cargo_travel_time],
    additional_authorized_imports=["pandas"],
    max_steps=20,
)

result = agent.run(task)result
```

We could already improve this a bit by throwing in some dedicated planning steps, and adding more prompting.

```python
agent.planning_interval = 4

detailed_report = agent.run(f"""
You're an expert analyst. You make comprehensive reports after visiting many websites.
Don't hesitate to search for many queries at once in a for loop.
For each data point that you find, visit the source url to confirm numbers.

{task}
""")

print(detailed_report)
```

```python
detailed_report
```

Thanks to these quick changes, we obtained a much more concise report by simply providing our agent a detailed prompt, and giving it planning capabilities!

💸 But as you can see, the context window is quickly filling up. So **if we ask our agent to combine the results of detailed search with another, it will be slower and quickly ramp up tokens and costs**.

➡️ We need to improve the structure of our system.
## ✌️ Splitting the task between two agents

Multi-agent structures allow to separate memories between different sub-tasks, with two great benefits:
- Each agent is more focused on its core task, thus more performant
- Separating memories reduces the count of input tokens at each step, thus reducing latency and cost.

Let's create a team with a dedicated web search agent, managed by another agent.

The manager agent should have plotting capabilities to redact its final report: so let us give it access to additional imports, including `matplotlib`, and `geopandas` + `shapely` for spatial plotting.

```python
!pip install matplotlib geopandas shapely -q

model = OpenAIServerModel("gpt-4o")

web_agent = CodeAgent(
    model=model,
    tools=[DuckDuckGoSearchTool(), VisitWebpageTool(), calculate_cargo_travel_time],
    name="web_agent",
    description="Browses the web to find information",
    verbosity_level=1,
    max_steps=10,
)
```

The manager agent will need to do some mental heavy lifting.

So we give it a stronger model, and add a `planning_interval` to the mix.

```python
from smolagents.utils import encode_image_base64, make_image_url

model = OpenAIServerModel("o1")

def check_reasoning_and_plot(final_answer, agent_memory):
    final_answer
    multimodal_model = OpenAIServerModel("gpt-4o")
    filepath = "saved_map.png"
    assert os.path.exists(filepath), "Make sure to save the plot under saved_map.png!"
    image = Image.open(filepath)
    prompt = (
        f"Here is a user-given task and the agent steps: {agent_memory.get_succinct_steps()}. Now here is the plot that was made."
        "Please check that the reasoning process and plot are correct: do they correctly answer the given task?"
        "First list 3 reasons why yes/no, then write your final decision: PASS in caps lock if it is satisfactory, FAIL if it is not."
        "Don't be harsh: if the plot mostly solves the task, it should pass."
        "But if any data was hallucinated/invented, you should refuse it. Also to pass, a plot should be made using px.scatter_map and not any other method (scatter_map looks nicer)."
    )
    messages = [
        {
            "role": "user",
            "content": [
                {
                    "type": "text",
                    "text": prompt,
                },
                {"type": "image_url", "image_url": {"url": make_image_url(encode_image_base64(image))}},
            ],
        }
    ]
    output = multimodal_model(messages).content
    print("Feedback: ", output)
    if "FAIL" in output:
        raise Exception(output)
    return True


manager_agent = CodeAgent(
    model=model,
    tools=[],
    managed_agents=[web_agent],
    additional_authorized_imports=["geopandas", "plotly", "shapely", "json", "pandas", "numpy"],
    planning_interval=4,
    verbosity_level=2,
    final_answer_checks=[check_reasoning_and_plot],
    max_steps=10,
)
```

Let us inspect what this team looks like:

```python
manager_agent.visualize()
```

This will generate something like this, helping us understanding the underlying structure:

```python
CodeAgent | o1
├── ✅ Authorized imports: ['geopandas', 'plotly', 'shapely', 'json', 'pandas', 'numpy']
├── 🛠️ Tools:
│   ┏━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
│   ┃ Name         ┃ Description                                   ┃ Arguments                                    ┃
│   ┡━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩
│   │ final_answer │ Provides a final answer to the given problem. │ answer (`any`): The final answer to the      │
│   │              │                                               │ problem                                      │
│   └──────────────┴───────────────────────────────────────────────┴──────────────────────────────────────────────┘
└── 🤖 Managed agents:
    └── web_agent | CodeAgent | gpt-4o
        ├── ✅ Authorized imports: []
        ├── 📝 Description: Browses the web to find information
        └── 🛠️ Tools:
            ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
            ┃ Name                        ┃ Description                       ┃ Arguments                         ┃
            ┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩
            │ web_search                  │ Performs a duckduckgo web search  │ query (`string`): The search      │
            │                             │ based on your query (think a      │ query to perform.                 │
            │                             │ Google search) then returns the   │                                   │
            │                             │ top search results.               │                                   │
            │ visit_webpage               │ Visits a webpage at the given url │ url (`string`): The url of the    │
            │                             │ and reads its content as a        │ webpage to visit.                 │
            │                             │ markdown string. Use this to      │                                   │
            │                             │ browse webpages.                  │                                   │
            │ calculate_cargo_travel_time │ Calculate the travel time for a   │ origin_coords (`array`): Tuple of │
            │                             │ cargo plane between two points on │ (latitude, longitude) for the     │
            │                             │ Earth using great-circle          │ starting point                    │
            │                             │ distance.                         │ destination_coords (`array`):     │
            │                             │                                   │ Tuple of (latitude, longitude)    │
            │                             │                                   │ for the destination               │
            │                             │                                   │ cruising_speed_kmh (`number`):    │
            │                             │                                   │ Optional cruising speed in km/h   │
            │                             │                                   │ (defaults to 750 km/h for typical │
            │                             │                                   │ cargo planes)                     │
            │ final_answer                │ Provides a final answer to the    │ answer (`any`): The final answer  │
            │                             │ given problem.                    │ to the problem                    │
            └─────────────────────────────┴───────────────────────────────────┴───────────────────────────────────┘
```

```python
manager_agent.run(f"""
{task}
Represent this as spatial map of the world, with the locations represented as scatter points proportional in size to the travel time, and save it to saved_map.png!

Here's an example of how to plot and return a map:
import plotly.express as px
df = px.data.carshare()
fig = px.scatter_map(df, lat="centroid_lat", lon="centroid_lon", text="name", color="peak_hour", size="car_hours",
     color_continuous_scale=px.colors.sequential.Magma, size_max=15, zoom=10)
fig.show()
fig.write_image("saved_image.png")
final_answer(fig)
""")
```

I don't know how that went in your run, but in mine, the manager agent masterfully divided tasks given to the web agent in `1. Search for Batman filming locations`, then `2. Find supercar factories`, before aggregating the lists and plotting the map.

Let's see what the map looks like by inspecting it directly from the agent state:


```python
manager_agent.python_executor.state["fig"]
```

## Adding telemetry

TODO

## Resources

- [Multi-Agent Systems](https://huggingface.co/docs/smolagents/main/en/examples/multiagents) – Overview of multi-agent systems.  
- [What is Agentic RAG?](https://weaviate.io/blog/what-is-agentic-rag) – Introduction to Agentic RAG.  
- [Multi-Agent RAG System 🤖🤝🤖 Recipe](https://huggingface.co/learn/cookbook/multiagent_rag_system) – Step-by-step guide to building a multi-agent RAG system.  
