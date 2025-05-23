# AI Agent Observability and Evaluation

## 🔎 What is Observability?

Observability is about understanding what's happening inside your AI agent by looking at external signals like logs, metrics, and traces. For AI agents, this means tracking actions, tool usage, model calls, and responses to debug and improve agent performance.

![Observability dashboard](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/langfuse-dashboard.png)

## 🔭 Why Agent Observability Matters

Without observability, AI agents are "black boxes." Observability tools make agents transparent, enabling you to:

- Understand costs and accuracy trade-offs
- Measure latency
- Detect harmful language & prompt injection
- Monitor user feedback

In other words, it makes your demo agent ready for production!

## 🔨 Observability Tools

Common observability tools for AI agents include platforms like [Langfuse](https://langfuse.com) and [Arize](https://www.arize.com). These tools help collect detailed traces and offer dashboards to monitor metrics in real-time, making it easy to detect problems and optimize performance.

Observability tools vary widely in their features and capabilities. Some tools are open source, benefiting from large communities that shape their roadmaps and extensive integrations. Additionally, certain tools specialize in specific aspects of LLMOps—such as observability, evaluations, or prompt management—while others are designed to cover the entire LLMOps workflow. We encourage you to explore the documentation of different options to pick a solution that works well for you.

Many agent frameworks such as [smolagents](https://huggingface.co/docs/smolagents/v1.12.0/en/index) use the [OpenTelemetry](https://opentelemetry.io/docs/) standard to expose metadata to the observability tools. In addition to this, observability tools build custom instrumentations to allow for more flexibility in the fast moving world of LLMs. You should check the documentation of the tool you are using to see what is supported.

## 🔬Traces and Spans

Observability tools usually represent agent runs as traces and spans.

- **Traces** represent a complete agent task from start to finish (like handling a user query).
- **Spans** are individual steps within the trace (like calling a language model or retrieving data).

![Example of a smolagent trace in Langfuse](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/trace-tree.png)

## 📊 Key Metrics to Monitor

Here are some of the most common metrics that observability tools monitor:

**Latency:** How quickly does the agent respond? Long waiting times negatively impact user experience. You should measure latency for tasks and individual steps by tracing agent runs. For example, an agent that takes 20 seconds for all model calls could be accelerated by using a faster model or by running model calls in parallel.

**Costs:** What’s the expense per agent run? AI agents rely on LLM calls billed per token or external APIs. Frequent tool usage or multiple prompts can rapidly increase costs. For instance, if an agent calls an LLM five times for marginal quality improvement, you must assess if the cost is justified or if you could reduce the number of calls or use a cheaper model. Real-time monitoring can also help identify unexpected spikes (e.g., bugs causing excessive API loops).

**Request Errors:** How many requests did the agent fail? This can include API errors or failed tool calls. To make your agent more robust against these in production, you can then set up fallbacks or retries. E.g. if LLM provider A is down, you switch to LLM provider B as backup.

**User Feedback:** Implementing direct user evaluations provide valuable insights. This can include explicit ratings (👍thumbs-up/👎down, ⭐1-5 stars) or textual comments. Consistent negative feedback should alert you as this is a sign that the agent is not working as expected. 

**Implicit User Feedback:** User behaviors provide indirect feedback even without explicit ratings. This can include immediate question rephrasing, repeated queries or clicking a retry button. E.g. if you see that users repeatedly ask the same question, this is a sign that the agent is not working as expected.

**Accuracy:** How frequently does the agent produce correct or desirable outputs? Accuracy definitions vary (e.g., problem-solving correctness, information retrieval accuracy, user satisfaction). The first step is to define what success looks like for your agent. You can track accuracy via automated checks, evaluation scores, or task completion labels. For example, marking traces as "succeeded" or "failed". 

**Automated Evaluation Metrics:** You can also set up automated evals. For instance, you can use an LLM to score the output of the agent e.g. if it is helpful, accurate, or not. There are also several open source libraries that help you to score different aspects of the agent. E.g. [RAGAS](https://docs.ragas.io/) for RAG agents or [LLM Guard](https://llm-guard.com/) to detect harmful language or prompt injection. 

In practice, a combination of these metrics gives the best coverage of an AI agent’s health. In this chapters [example notebook](https://colab.research.google.com/#fileId=https://huggingface.co/agents-course/notebooks/blob/main/bonus-unit2/monitoring-and-evaluating-agents.ipynb), we'll show you how these metrics looks in real examples but first, we'll learn how a typical evaluation workflow looks like.

## 👍 Evaluating AI Agents

Observability gives us metrics, but evaluation is the process of analyzing that data (and performing tests) to determine how well an AI agent is performing and how it can be improved. In other words, once you have those traces and metrics, how do you use them to judge the agent and make decisions? 

Regular evaluation is important because AI agents are often non-deterministic and can evolve (through updates or drifting model behavior) – without evaluation, you wouldn’t know if your “smart agent” is actually doing its job well or if it’s regressed.

There are two categories of evaluations for AI agents: **online evaluation** and **offline evaluation**. Both are valuable, and they complement each other. We usually begin with offline evaluation, as this is the minimum necessary step before deploying any agent.

### 🥷 Offline Evaluation

![Dataset items in Langfuse](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit2/example-dataset.png)

This involves evaluating the agent in a controlled setting, typically using test datasets, not live user queries. You use curated datasets where you know what the expected output or correct behavior is, and then run your agent on those. 

For instance, if you built a math word-problem agent, you might have a [test dataset](https://huggingface.co/datasets/gsm8k) of 100 problems with known answers. Offline evaluation is often done during development (and can be part of CI/CD pipelines) to check improvements or guard against regressions. The benefit is that it’s **repeatable and you can get clear accuracy metrics since you have ground truth**. You might also simulate user queries and measure the agent’s responses against ideal answers or use automated metrics as described above. 

The key challenge with offline eval is ensuring your test dataset is comprehensive and stays relevant – the agent might perform well on a fixed test set but encounter very different queries in production. Therefore, you should keep test sets updated with new edge cases and examples that reflect real-world scenarios​. A mix of small “smoke test” cases and larger evaluation sets is useful: small sets for quick checks and larger ones for broader performance metrics​.

### 🔄 Online Evaluation 

This refers to evaluating the agent in a live, real-world environment, i.e. during actual usage in production. Online evaluation involves monitoring the agent’s performance on real user interactions and analyzing outcomes continuously. 

For example, you might track success rates, user satisfaction scores, or other metrics on live traffic. The advantage of online evaluation is that it **captures things you might not anticipate in a lab setting** – you can observe model drift over time (if the agent’s effectiveness degrades as input patterns shift) and catch unexpected queries or situations that weren’t in your test data​. It provides a true picture of how the agent behaves in the wild. 

Online evaluation often involves collecting implicit and explicit user feedback, as discussed, and possibly running shadow tests or A/B tests (where a new version of the agent runs in parallel to compare against the old). The challenge is that it can be tricky to get reliable labels or scores for live interactions – you might rely on user feedback or downstream metrics (like did the user click the result). 

### 🤝 Combining the two

In practice, successful AI agent evaluation blends **online** and **offline** methods​. You might run regular offline benchmarks to quantitatively score your agent on defined tasks and continuously monitor live usage to catch things the benchmarks miss. For example, offline tests can catch if a code-generation agent’s success rate on a known set of problems is improving, while online monitoring might alert you that users have started asking a new category of question that the agent struggles with. Combining both gives a more robust picture. 

In fact, many teams adopt a loop: _offline evaluation → deploy new agent version → monitor online metrics and collect new failure examples → add those examples to offline test set → iterate_. This way, evaluation is continuous and ever-improving.

## 🧑‍💻 Lets see how this works in practice

In the next section, we'll see examples of how we can use observability tools to monitor and evaluate our agent.


