<CourseFloatingBanner chapter={2}
  classNames="absolute z-10 right-0 top-0"
  notebooks={[
    {label: "Google Colab", value: "https://colab.research.google.com/#fileId=https%3A//huggingface.co/agents-course/notebooks/blob/main/bonus-unit2/monitoring-and-evaluating-agents.ipynb"},
]} />

# Bonus Unit 2: Observability and Evaluation of Agents

> [!TIP]
> You can follow the code in <a href="https://colab.research.google.com/#fileId=https%3A//huggingface.co/agents-course/notebooks/blob/main/bonus-unit2/monitoring-and-evaluating-agents.ipynb" target="_blank">this notebook</a> that you can run using Google Colab.

In this notebook, we will learn how to **monitor the internal steps (traces) of our AI agent** and **evaluate its performance** using open-source observability tools.

The ability to observe and evaluate an agent’s behavior is essential for:
- Debugging issues when tasks fail or produce suboptimal results
- Monitoring costs and performance in real-time
- Improving reliability and safety through continuous feedback

## Exercise Prerequisites 🏗️

Before running this notebook, please be sure you have:

🔲 📚  **Studied** [Introduction to Agents](https://huggingface.co/learn/agents-course/unit1/introduction)

🔲 📚  **Studied** [The smolagents framework](https://huggingface.co/learn/agents-course/unit2/smolagents/introduction)

## Step 0: Install the Required Libraries

We will need a few libraries that allow us to run, monitor, and evaluate our agents:


```python
%pip install langfuse 'smolagents[telemetry]' openinference-instrumentation-smolagents datasets 'smolagents[gradio]' gradio --upgrade
```

## Step 1: Instrument Your Agent

In this notebook, we will use [Langfuse](https://langfuse.com/) as our observability tool, but you can use **any other OpenTelemetry-compatible service**. The code below shows how to set environment variables for Langfuse (or any OTel endpoint) and how to instrument your smolagent.

**Note:** If you are using LlamaIndex or LangGraph, you can find documentation on instrumenting them [here](https://langfuse.com/docs/integrations/llama-index/workflows) and [here](https://langfuse.com/docs/integrations/langchain/example-python-langgraph). 

First, let's set up the Langfuse credentials as environment variables. Get your Langfuse API keys by signing up for [Langfuse Cloud](https://cloud.langfuse.com) or [self-hosting Langfuse](https://langfuse.com/self-hosting).

```python
import os
# Get keys for your project from the project settings page: https://cloud.langfuse.com
os.environ["LANGFUSE_PUBLIC_KEY"] = "pk-lf-..." 
os.environ["LANGFUSE_SECRET_KEY"] = "sk-lf-..." 
os.environ["LANGFUSE_HOST"] = "https://cloud.langfuse.com" # 🇪🇺 EU region
# os.environ["LANGFUSE_HOST"] = "https://us.cloud.langfuse.com" # 🇺🇸 US region
```
We also need to configure our Hugging Face token for inference calls.

```python
# Set your Hugging Face and other tokens/secrets as environment variable
os.environ["HF_TOKEN"] = "hf_..." 
```

With the environment variables set, we can now initialize the Langfuse client. `get_client()` initializes the Langfuse client using the credentials provided in the environment variables.

```python
from langfuse import get_client
 
langfuse = get_client()
 
# Verify connection
if langfuse.auth_check():
    print("Langfuse client is authenticated and ready!")
else:
    print("Authentication failed. Please check your credentials and host.")
```

Next, we can set up the `SmolagentsInstrumentor()` to instrument our smolagent and send traces to Langfuse.

```python
from openinference.instrumentation.smolagents import SmolagentsInstrumentor
 
SmolagentsInstrumentor().instrument()
```

## Step 2: Test Your Instrumentation

Here is a simple CodeAgent from smolagents that calculates `1+1`. We run it to confirm that the instrumentation is working correctly. If everything is set up correctly, you will see logs/spans in your observability dashboard.


```python
from smolagents import InferenceClientModel, CodeAgent

# Create a simple agent to test instrumentation
agent = CodeAgent(
    tools=[],
    model=InferenceClientModel()
)

agent.run("1+1=")
```

Check your [Langfuse Traces Dashboard](https://cloud.langfuse.com) (or your chosen observability tool) to confirm that the spans and logs have been recorded.

Example screenshot from Langfuse:

![Example trace in Langfuse](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/first-example-trace.png)

_[Link to the trace](https://cloud.langfuse.com/project/cloramnkj0002jz088vzn1ja4/traces/1b94d6888258e0998329cdb72a371155?timestamp=2025-03-10T11%3A59%3A41.743Z)_

## Step 3: Observe and Evaluate a More Complex Agent

Now that you have confirmed your instrumentation works, let's try a more complex query so we can see how advanced metrics (token usage, latency, costs, etc.) are tracked.


```python
from smolagents import (CodeAgent, DuckDuckGoSearchTool, InferenceClientModel)

search_tool = DuckDuckGoSearchTool()
agent = CodeAgent(tools=[search_tool], model=InferenceClientModel())

agent.run("How many Rubik's Cubes could you fit inside the Notre Dame Cathedral?")
```

### Trace Structure

Most observability tools record a **trace** that contains **spans**, which represent each step of your agent’s logic. Here, the trace contains the overall agent run and sub-spans for:
- The tool calls (DuckDuckGoSearchTool)
- The LLM calls (InferenceClientModel)

You can inspect these to see precisely where time is spent, how many tokens are used, and so on:

![Trace tree in Langfuse](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/trace-tree.png)

_[Link to the trace](https://cloud.langfuse.com/project/cloramnkj0002jz088vzn1ja4/traces/1ac33b89ffd5e75d4265b62900c348ed?timestamp=2025-03-07T13%3A45%3A09.149Z&display=preview)_

## Online Evaluation

In the previous section, we learned about the difference between online and offline evaluation. Now, we will see how to monitor your agent in production and evaluate it live.

### Common Metrics to Track in Production

1. **Costs** — The smolagents instrumentation captures token usage, which you can transform into approximate costs by assigning a price per token.
2. **Latency** — Observe the time it takes to complete each step, or the entire run.
3. **User Feedback** — Users can provide direct feedback (thumbs up/down) to help refine or correct the agent.
4. **LLM-as-a-Judge** — Use a separate LLM to evaluate your agent’s output in near real-time (e.g., checking for toxicity or correctness).

Below, we show examples of these metrics.

#### 1. Costs

Below is a screenshot showing usage for `Qwen2.5-Coder-32B-Instruct` calls. This is useful to see costly steps and optimize your agent. 

![Costs](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/smolagents-costs.png)

_[Link to the trace](https://cloud.langfuse.com/project/cloramnkj0002jz088vzn1ja4/traces/1ac33b89ffd5e75d4265b62900c348ed?timestamp=2025-03-07T13%3A45%3A09.149Z&display=preview)_

#### 2. Latency

We can also see how long it took to complete each step. In the example below, the entire conversation took 32 seconds, which you can break down by step. This helps you identify bottlenecks and optimize your agent.

![Latency](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/smolagents-latency.png)

_[Link to the trace](https://cloud.langfuse.com/project/cloramnkj0002jz088vzn1ja4/traces/1ac33b89ffd5e75d4265b62900c348ed?timestamp=2025-03-07T13%3A45%3A09.149Z&display=preview)_

#### 3. Additional Attributes

You may also pass additional attributes to your spans. These can include `user_id`, `tags`, `session_id`, and custom metadata. Enriching traces with these details is important for analysis, debugging, and monitoring of your application’s behavior across different users or sessions.

```python
from smolagents import (CodeAgent, DuckDuckGoSearchTool, InferenceClientModel)

search_tool = DuckDuckGoSearchTool()
agent = CodeAgent(
    tools=[search_tool],
    model=InferenceClientModel()
)

with langfuse.start_as_current_span(
    name="Smolagent-Trace",
    ) as span:
    
    # Run your application here
    response = agent.run("What is the capital of Germany?")
 
    # Pass additional attributes to the span
    span.update_trace(
        input="What is the capital of Germany?",
        output=response,
        user_id="smolagent-user-123",
        session_id="smolagent-session-123456789",
        tags=["city-question", "testing-agents"],
        metadata={"email": "user@langfuse.com"},
        )
 
# Flush events in short-lived applications
langfuse.flush()
```

![Enhancing agent runs with additional metrics](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/smolagents-attributes.png)

#### 4. User Feedback

If your agent is embedded into a user interface, you can record direct user feedback (like a thumbs-up/down in a chat UI). Below is an example using [Gradio](https://gradio.app/) to embed a chat with a simple feedback mechanism.

In the code snippet below, when a user sends a chat message, we capture the trace in Langfuse. If the user likes/dislikes the last answer, we attach a score to the trace.

```python
import gradio as gr
from smolagents import (CodeAgent, InferenceClientModel)
from langfuse import get_client

langfuse = get_client()

model = InferenceClientModel()
agent = CodeAgent(tools=[], model=model, add_base_tools=True)

trace_id = None

def respond(prompt, history):
    with langfuse.start_as_current_span(
        name="Smolagent-Trace"):
        
        # Run your application here
        output = agent.run(prompt)

        global trace_id
        trace_id = langfuse.get_current_trace_id()

    history.append({"role": "assistant", "content": str(output)})
    return history

def handle_like(data: gr.LikeData):
    # For demonstration, we map user feedback to a 1 (like) or 0 (dislike)
    if data.liked:
        langfuse.create_score(
            value=1,
            name="user-feedback",
            trace_id=trace_id
        )
    else:
        langfuse.create_score(
            value=0,
            name="user-feedback",
            trace_id=trace_id
        )

with gr.Blocks() as demo:
    chatbot = gr.Chatbot(label="Chat", type="messages")
    prompt_box = gr.Textbox(placeholder="Type your message...", label="Your message")

    # When the user presses 'Enter' on the prompt, we run 'respond'
    prompt_box.submit(
        fn=respond,
        inputs=[prompt_box, chatbot],
        outputs=chatbot
    )

    # When the user clicks a 'like' button on a message, we run 'handle_like'
    chatbot.like(handle_like, None, None)

demo.launch()
```

User feedback is then captured in your observability tool:

![User feedback is being captured in Langfuse](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/user-feedback-gradio.png)

#### 5. LLM-as-a-Judge

LLM-as-a-Judge is another way to automatically evaluate your agent's output. You can set up a separate LLM call to gauge the output’s correctness, toxicity, style, or any other criteria you care about.

**Workflow**:
1. You define an **Evaluation Template**, e.g., "Check if the text is toxic."
2. Each time your agent generates output, you pass that output to your "judge" LLM with the template.
3. The judge LLM responds with a rating or label that you log to your observability tool.

Example from Langfuse:

![LLM-as-a-Judge Evaluation Template](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/evaluator-template.png)
![LLM-as-a-Judge Evaluator](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/evaluator.png)


```python
# Example: Checking if the agent’s output is toxic or not.
from smolagents import (CodeAgent, DuckDuckGoSearchTool, InferenceClientModel)

search_tool = DuckDuckGoSearchTool()
agent = CodeAgent(tools=[search_tool], model=InferenceClientModel())

agent.run("Can eating carrots improve your vision?")
```

You can see that the answer of this example is judged as "not toxic".

![LLM-as-a-Judge Evaluation Score](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/llm-as-a-judge-score.png)

#### 6. Observability Metrics Overview

All of these metrics can be visualized together in dashboards. This enables you to quickly see how your agent performs across many sessions and helps you to track quality metrics over time.

![Observability metrics overview](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/langfuse-dashboard.png)

## Offline Evaluation

Online evaluation is essential for live feedback, but you also need **offline evaluation**—systematic checks before or during development. This helps maintain quality and reliability before rolling changes into production.

### Dataset Evaluation

In offline evaluation, you typically:
1. Have a benchmark dataset (with prompt and expected output pairs)
2. Run your agent on that dataset
3. Compare outputs to the expected results or use an additional scoring mechanism

Below, we demonstrate this approach with the [GSM8K dataset](https://huggingface.co/datasets/openai/gsm8k), which contains math questions and solutions.


```python
import pandas as pd
from datasets import load_dataset

# Fetch GSM8K from Hugging Face
dataset = load_dataset("openai/gsm8k", 'main', split='train')
df = pd.DataFrame(dataset)
print("First few rows of GSM8K dataset:")
print(df.head())
```

Next, we create a dataset entity in Langfuse to track the runs. Then, we add each item from the dataset to the system. (If you’re not using Langfuse, you might simply store these in your own database or local file for analysis.)


```python
from langfuse import get_client
langfuse = get_client()

langfuse_dataset_name = "gsm8k_dataset_huggingface"

# Create a dataset in Langfuse
langfuse.create_dataset(
    name=langfuse_dataset_name,
    description="GSM8K benchmark dataset uploaded from Huggingface",
    metadata={
        "date": "2025-03-10", 
        "type": "benchmark"
    }
)
```


```python
for idx, row in df.iterrows():
    langfuse.create_dataset_item(
        dataset_name=langfuse_dataset_name,
        input={"text": row["question"]},
        expected_output={"text": row["answer"]},
        metadata={"source_index": idx}
    )
    if idx >= 9: # Upload only the first 10 items for demonstration
        break
```

![Dataset items in Langfuse](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/example-dataset.png)

#### Running the Agent on the Dataset

We define a helper function `run_smolagent()` that:
1. Starts a Langfuse span
2. Runs our agent on the prompt
3. Records the trace ID in Langfuse

Then, we loop over each dataset item, run the agent, and link the trace to the dataset item. We can also attach a quick evaluation score if desired.


```python
from opentelemetry.trace import format_trace_id
from smolagents import (CodeAgent, InferenceClientModel, LiteLLMModel)
from langfuse import get_client
 
langfuse = get_client()


# Example: using InferenceClientModel or LiteLLMModel to access openai, anthropic, gemini, etc. models:
model = InferenceClientModel()

agent = CodeAgent(
    tools=[],
    model=model,
    add_base_tools=True
)

dataset_name = "gsm8k_dataset_huggingface"
current_run_name = "smolagent-notebook-run-01" # Identifies this specific evaluation run
 
# Assume 'run_smolagent' is your instrumented application function
def run_smolagent(question):
    with langfuse.start_as_current_generation(name="qna-llm-call") as generation:
        # Simulate LLM call
        result = agent.run(question)
 
        # Update the trace with the input and output
        generation.update_trace(
            input= question,
            output=result,
        )
 
        return result
 
dataset = langfuse.get_dataset(name=dataset_name) # Fetch your pre-populated dataset
 
for item in dataset.items:
 
    # Use the item.run() context manager
    with item.run(
        run_name=current_run_name,
        run_metadata={"model_provider": "Hugging Face", "temperature_setting": 0.7},
        run_description="Evaluation run for GSM8K dataset"
    ) as root_span: # root_span is the root span of the new trace for this item and run.
        # All subsequent langfuse operations within this block are part of this trace.
 
        # Call your application logic
        generated_answer = run_smolagent(question=item.input["text"])
 
        print(item.input)
```

You can repeat this process with different:
- Models (OpenAI GPT, local LLM, etc.)
- Tools (search vs. no search)
- Prompts (different system messages)

Then compare them side-by-side in your observability tool:

![Dataset run overview](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/dataset_runs.png)
![Dataset run comparison](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/dataset-run-comparison.png)


## Final Thoughts

In this notebook, we covered how to:
1. **Set up Observability** using smolagents + OpenTelemetry exporters
2. **Check Instrumentation** by running a simple agent
3. **Capture Detailed Metrics** (cost, latency, etc.) through an observability tools
4. **Collect User Feedback** via a Gradio interface
5. **Use LLM-as-a-Judge** to automatically evaluate outputs
6. **Perform Offline Evaluation** with a benchmark dataset

🤗 Happy coding!
