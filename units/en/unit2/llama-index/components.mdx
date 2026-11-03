# What are components in LlamaIndex?

Remember Alfred, our helpful butler agent from Unit 1?
To assist us effectively, Alfred needs to understand our requests and **prepare, find and use relevant information to help complete tasks.**
This is where LlamaIndex's components come in.

While LlamaIndex has many components, **we'll focus specifically on the `QueryEngine` component.**
Why? Because it can be used as a Retrieval-Augmented Generation (RAG) tool for an agent.

So, what is RAG? LLMs are trained on enormous bodies of data to learn general knowledge.
However, they may not be trained on relevant and up-to-date data.
RAG solves this problem by finding and retrieving relevant information from your data and giving that to the LLM.

![RAG](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/llama-index/rag.png)

Now, think about how Alfred works:

1. You ask Alfred to help plan a dinner party
2. Alfred needs to check your calendar, dietary preferences, and past successful menus
3. The `QueryEngine` helps Alfred find this information and use it to plan the dinner party

This makes the `QueryEngine` **a key component for building agentic RAG workflows** in LlamaIndex.
Just as Alfred needs to search through your household information to be helpful, any agent needs a way to find and understand relevant data.
The `QueryEngine` provides exactly this capability.

Now, let's dive a bit deeper into the components and see how you can **combine components to create a RAG pipeline.**

## Creating a RAG pipeline using components

> [!TIP]
> You can follow the code in <a href="https://huggingface.co/agents-course/notebooks/blob/main/unit2/llama-index/components.ipynb" target="_blank">this notebook</a> that you can run using Google Colab.

There are five key stages within RAG, which in turn will be a part of most larger applications you build. These are:

1. **Loading**: this refers to getting your data from where it lives -- whether it's text files, PDFs, another website, a database, or an API -- into your workflow. LlamaHub provides hundreds of integrations to choose from.
2. **Indexing**: this means creating a data structure that allows for querying the data. For LLMs, this nearly always means creating vector embeddings. Which are numerical representations of the meaning of the data. Indexing can also refer to numerous other metadata strategies to make it easy to accurately find contextually relevant data based on properties.
3. **Storing**: once your data is indexed you will want to store your index, as well as other metadata, to avoid having to re-index it.
4. **Querying**: for any given indexing strategy there are many ways you can utilize LLMs and LlamaIndex data structures to query, including sub-queries, multi-step queries and hybrid strategies.
5. **Evaluation**: a critical step in any flow is checking how effective it is relative to other strategies, or when you make changes. Evaluation provides objective measures of how accurate, faithful and fast your responses to queries are.

Next, let's see how we can reproduce these stages using components.

### Loading and embedding documents

As mentioned before, LlamaIndex can work on top of your own data, however, **before accessing data, we need to load it.**
There are three main ways to load data into LlamaIndex:

1. `SimpleDirectoryReader`: A built-in loader for various file types from a local directory.
2. `LlamaParse`: LlamaParse, LlamaIndex's official tool for PDF parsing, available as a managed API.
3. `LlamaHub`: A registry of hundreds of data-loading libraries to ingest data from any source.

> [!TIP]
> Get familiar with <a href="https://docs.llamaindex.ai/en/stable/module_guides/loading/connector/">LlamaHub</a> loaders and <a href="https://github.com/run-llama/llama_cloud_services/blob/main/parse.md">LlamaParse</a> parser for more complex data sources.

**The simplest way to load data is with `SimpleDirectoryReader`.**
This versatile component can load various file types from a folder and convert them into `Document` objects that LlamaIndex can work with.
Let's see how we can use `SimpleDirectoryReader` to load data from a folder.

```python
from llama_index.core import SimpleDirectoryReader

reader = SimpleDirectoryReader(input_dir="path/to/directory")
documents = reader.load_data()
```

After loading our documents, we need to break them into smaller pieces called `Node` objects.
A `Node` is just a chunk of text from the original document that's easier for the AI to work with, while it still has references to the original `Document` object.

The `IngestionPipeline` helps us create these nodes through two key transformations.
1. `SentenceSplitter` breaks down documents into manageable chunks by splitting them at natural sentence boundaries.
2. `HuggingFaceEmbedding` converts each chunk into numerical embeddings - vector representations that capture the semantic meaning in a way AI can process efficiently.

This process helps us organise our documents in a way that's more useful for searching and analysis.

```python
from llama_index.core import Document
from llama_index.embeddings.huggingface import HuggingFaceEmbedding
from llama_index.core.node_parser import SentenceSplitter
from llama_index.core.ingestion import IngestionPipeline

# create the pipeline with transformations
pipeline = IngestionPipeline(
    transformations=[
        SentenceSplitter(chunk_overlap=0),
        HuggingFaceEmbedding(model_name="BAAI/bge-small-en-v1.5"),
    ]
)

nodes = await pipeline.arun(documents=[Document.example()])
```


### Storing and indexing documents

After creating our `Node` objects we need to index them to make them searchable, but before we can do that, we need a place to store our data.

Since we are using an ingestion pipeline, we can directly attach a vector store to the pipeline to populate it.
In this case, we will use `Chroma` to store our documents.

<details>
<summary>Install ChromaDB</summary>

As introduced in the <a href="./llama-hub">section on the LlamaHub</a>, we can install the ChromaDB vector store with the following command:

```bash
pip install llama-index-vector-stores-chroma
```
</details>

```python
import chromadb
from llama_index.vector_stores.chroma import ChromaVectorStore

db = chromadb.PersistentClient(path="./alfred_chroma_db")
chroma_collection = db.get_or_create_collection("alfred")
vector_store = ChromaVectorStore(chroma_collection=chroma_collection)

pipeline = IngestionPipeline(
    transformations=[
        SentenceSplitter(chunk_size=25, chunk_overlap=0),
        HuggingFaceEmbedding(model_name="BAAI/bge-small-en-v1.5"),
    ],
    vector_store=vector_store,
)
```

> [!TIP]
> An overview of the different vector stores can be found in the <a href="https://docs.llamaindex.ai/en/stable/module_guides/storing/vector_stores/">LlamaIndex documentation</a>.


This is where vector embeddings come in - by embedding both the query and nodes in the same vector space, we can find relevant matches.
The `VectorStoreIndex` handles this for us, using the same embedding model we used during ingestion to ensure consistency.

Let's see how to create this index from our vector store and embeddings:

```python
from llama_index.core import VectorStoreIndex
from llama_index.embeddings.huggingface import HuggingFaceEmbedding

embed_model = HuggingFaceEmbedding(model_name="BAAI/bge-small-en-v1.5")
index = VectorStoreIndex.from_vector_store(vector_store, embed_model=embed_model)
```

All information is automatically persisted within the `ChromaVectorStore` object and the passed directory path.

Great! Now that we can save and load our index easily, let's explore how to query it in different ways.

### Querying a VectorStoreIndex with prompts and LLMs

Before we can query our index, we need to convert it to a query interface. The most common conversion options are:

- `as_retriever`: For basic document retrieval, returning a list of `NodeWithScore` objects with similarity scores
- `as_query_engine`: For single question-answer interactions, returning a written response
- `as_chat_engine`: For conversational interactions that maintain memory across multiple messages, returning a written response using chat history and indexed context

We'll focus on the query engine since it is more common for agent-like interactions.
We also pass in an LLM to the query engine to use for the response.

```python
from llama_index.llms.huggingface_api import HuggingFaceInferenceAPI

llm = HuggingFaceInferenceAPI(model_name="Qwen/Qwen2.5-Coder-32B-Instruct")
query_engine = index.as_query_engine(
    llm=llm,
    response_mode="tree_summarize",
)
query_engine.query("What is the meaning of life?")
# The meaning of life is 42
```

### Response Processing

Under the hood, the query engine doesn't only use the LLM to answer the question but also uses a `ResponseSynthesizer` as a strategy to process the response.
Once again, this is fully customisable but there are three main strategies that work well out of the box:

- `refine`: create and refine an answer by sequentially going through each retrieved text chunk. This makes a separate LLM call per Node/retrieved chunk.
- `compact` (default): similar to refining but concatenating the chunks beforehand, resulting in fewer LLM calls.
- `tree_summarize`: create a detailed answer by going through each retrieved text chunk and creating a tree structure of the answer.

> [!TIP]
> Take fine-grained control of your query workflows with the <a href="https://docs.llamaindex.ai/en/stable/module_guides/deploying/query_engine/usage_pattern/#low-level-composition-api">low-level composition API</a>. This API lets you customize and fine-tune every step of the query process to match your exact needs, which also pairs great with <a href="https://docs.llamaindex.ai/en/stable/module_guides/workflow/">Workflows</a>

The language model won't always perform in predictable ways, so we can't be sure that the answer we get is always correct. We can deal with this by **evaluating the quality of the answer**.

### Evaluation and observability

LlamaIndex provides **built-in evaluation tools to assess response quality.**
These evaluators leverage LLMs to analyze responses across different dimensions.
Let's look at the three main evaluators available:

- `FaithfulnessEvaluator`: Evaluates the faithfulness of the answer by checking if the answer is supported by the context.
- `AnswerRelevancyEvaluator`: Evaluate the relevance of the answer by checking if the answer is relevant to the question.
- `CorrectnessEvaluator`: Evaluate the correctness of the answer by checking if the answer is correct.

> [!TIP]
> Want to learn more about agent observability and evaluation? Continue your journey with the <a href="https://huggingface.co/learn/agents-course/bonus-unit2/introduction">Bonus Unit 2</a>.

```python
from llama_index.core.evaluation import FaithfulnessEvaluator

query_engine = # from the previous section
llm = # from the previous section

# query index
evaluator = FaithfulnessEvaluator(llm=llm)
response = query_engine.query(
    "What battles took place in New York City in the American Revolution?"
)
eval_result = evaluator.evaluate_response(response=response)
eval_result.passing
```

Even without direct evaluation, we can **gain insights into how our system is performing through observability.**
This is especially useful when we are building more complex workflows and want to understand how each component is performing.

<details>
<summary>Install LlamaTrace</summary>

As introduced in the <a href="./llama-hub">section on the LlamaHub</a>, we can install the LlamaTrace callback from Arize Phoenix with the following command:

```bash
pip install -U llama-index-callbacks-arize-phoenix
```

Additionally, we need to set the `PHOENIX_API_KEY` environment variable to our LlamaTrace API key. We can get this by:
- Creating an account at [LlamaTrace](https://llamatrace.com/login)
- Generating an API key in your account settings
- Using the API key in the code below to enable tracing

</details>

```python
import llama_index
import os

PHOENIX_API_KEY = "<PHOENIX_API_KEY>"
os.environ["OTEL_EXPORTER_OTLP_HEADERS"] = f"api_key={PHOENIX_API_KEY}"
llama_index.core.set_global_handler(
    "arize_phoenix",
    endpoint="https://llamatrace.com/v1/traces"
)
```

> [!TIP]
> Want to learn more about components and how to use them? Continue your journey with the <a href="https://docs.llamaindex.ai/en/stable/module_guides/">Components Guides</a> or the <a href="https://docs.llamaindex.ai/en/stable/understanding/rag/">Guide on RAG</a>.

We have seen how to use components to create a `QueryEngine`. Now, let's see how we can **use the `QueryEngine` as a tool for an agent!**
