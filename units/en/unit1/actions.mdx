# Actions:  Enabling the Agent to Engage with Its Environment

<Tip>
 In this section, we explore the concrete steps an AI agent takes to interact with its environment. 

 We’ll cover how actions are represented (using JSON or code), the importance of the stop and parse approach, and introduce different types of agents.
</Tip>

Actions are the concrete steps an **AI agent takes to interact with its environment**. 

Whether it’s browsing the web for information or controlling a physical device, each action is a deliberate operation executed by the agent. 

For example, an agent assisting with customer service might retrieve customer data, offer support articles, or transfer issues to a human representative.

## Types of Agent Actions

There are multiple types of Agents that take actions differently:

| Type of Agent          | Description                                                                                      |
|------------------------|--------------------------------------------------------------------------------------------------|
| JSON Agent             | The Action to take is specified in JSON format.                                                  |
| Code Agent             | The Agent writes a code block that is interpreted externally.                                    |
| Function-calling Agent | It is a subcategory of the JSON Agent which has been fine-tuned to generate a new message for each action. |

Actions themselves can serve many purposes:

| Type of Action           | Description                                                                              |
|--------------------------|------------------------------------------------------------------------------------------|
| Information Gathering    | Performing web searches, querying databases, or retrieving documents.                    |
| Tool Usage               | Making API calls, running calculations, and executing code.                              |
| Environment Interaction  | Manipulating digital interfaces or controlling physical devices.                         |
| Communication            | Engaging with users via chat or collaborating with other agents.                         |

One crucial part of an agent is the **ability to STOP generating new tokens when an action is complete**, and that is true for all formats of Agent: JSON, code, or function-calling. This prevents unintended output and ensures that the agent’s response is clear and precise.

The LLM only handles text and uses it to describe the action it wants to take and the parameters to supply to the tool.

## The Stop and Parse Approach

One key method for implementing actions is the **stop and parse approach**. This method ensures that the agent’s output is structured and predictable:

1. **Generation in a Structured Format**:

The agent outputs its intended action in a clear, predetermined format (JSON or code).

2. **Halting Further Generation**:

Once the action is complete, **the agent stops generating additional tokens**. This prevents extra or erroneous output.

3. **Parsing the Output**:

An external parser reads the formatted action, determines which Tool to call, and extracts the required parameters.

For example, an agent needing to check the weather might output:


```json
Thought: I need to check the current weather for New York.
Action :
{
  "action": "get_weather",
  "action_input": {"location": "New York"}
}
```
The framework can then easily parse the name of the function to call and the arguments to apply.

This clear, machine-readable format minimizes errors and enables external tools to accurately process the agent’s command.

Note: Function-calling agents operate similarly by structuring each action so that a designated function is invoked with the correct arguments.
We'll dive deeper into those types of Agents in a future Unit.

## Code Agents

An alternative approach is using *Code Agents*.
The idea is: **instead of outputting a simple JSON object**, a Code Agent generates an **executable code block—typically in a high-level language like Python**. 

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/code-vs-json-actions.png" alt="Code Agents" />

This approach offers several advantages:

- **Expressiveness:** Code can naturally represent complex logic, including loops, conditionals, and nested functions, providing greater flexibility than JSON.
- **Modularity and Reusability:** Generated code can include functions and modules that are reusable across different actions or tasks.
- **Enhanced Debuggability:** With a well-defined programming syntax, code errors are often easier to detect and correct.
- **Direct Integration:** Code Agents can integrate directly with external libraries and APIs, enabling more complex operations such as data processing or real-time decision making.

For example, a Code Agent tasked with fetching the weather might generate the following Python snippet:

```python
# Code Agent Example: Retrieve Weather Information
def get_weather(city):
    import requests
    api_url = f"https://api.weather.com/v1/location/{city}?apiKey=YOUR_API_KEY"
    response = requests.get(api_url)
    if response.status_code == 200:
        data = response.json()
        return data.get("weather", "No weather information available")
    else:
        return "Error: Unable to fetch weather data."

# Execute the function and prepare the final answer
result = get_weather("New York")
final_answer = f"The current weather in New York is: {result}"
print(final_answer)
```

In this example, the Code Agent:

- Retrieves weather data **via an API call**,
- Processes the response,
- And uses the print() function to output a final answer.

This method **also follows the stop and parse approach** by clearly delimiting the code block and signaling when execution is complete (here, by printing the final_answer).

---

We learned that Actions bridge an agent's internal reasoning and its real-world interactions by executing clear, structured tasks—whether through JSON, code, or function calls.

This deliberate execution ensures that each action is precise and ready for external processing via the stop and parse approach. In the next section, we will explore Observations to see how agents capture and integrate feedback from their environment.

After this, we will **finally be ready to build our first Agent!**






