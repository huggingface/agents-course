# Building Agentic RAG Systems

Agentic RAG (Retrieval-Augmented Generation) extends the capabilities of traditional RAG systems by combining autonomous agents with dynamic knowledge retrieval. While traditional RAG systems use an LLM to answer queries based on retrieved data, agentic RAG enables the system to intelligently control both the retrieval and generation processes, enhancing its overall efficiency and accuracy.

Traditional RAG systems face key limitations, such as relying on a single retrieval step and focusing on direct semantic similarity with the user’s query, which may overlook relevant information. Agentic RAG addresses these issues by allowing the agent to autonomously formulate search queries, critique retrieved results, and conduct multiple retrieval steps for a more tailored and comprehensive output.

## Basic Retrieval with DuckDuckGo

To get started, let's build a simple agent that can search the web using DuckDuckGo. This agent will retrieve relevant information and synthesize responses to answer user queries. With Agentic RAG, Alfred’s agent can:

* Search for the latest trends in superhero-themed parties.
* Refine search results to include luxury elements for a high-profile event.
* Synthesize the gathered information into a complete plan covering entertainment, catering, and more.

Here’s how Alfred’s agent can achieve this:

```python
from smolagents import CodeAgent, DuckDuckGoSearchTool, HfApiModel

# Initialize the search tool
search_tool = DuckDuckGoSearchTool()

# Initialize the model
model = HfApiModel()

agent = CodeAgent(
    model = model,
    tools=[search_tool]
)

# Example usage
response = agent.run(
    "Search for luxury superhero-themed party ideas, including decorations, entertainment, and catering."
)
print(response)
```

The agent will:

1. **Analyzes the Request:** Alfred’s agent identifies the key elements of the query—luxury superhero-themed party planning, with focus on decor, entertainment, and catering.
2. **Performs Retrieval:**  The agent leverages DuckDuckGo to search for the most relevant and up-to-date information, ensuring it aligns with Alfred’s refined preferences for a luxurious event.
3. **Synthesizes Information:** After gathering the results, the agent processes them into a cohesive, actionable plan for Alfred, covering all aspects of the party.
4. **Stores for Future Reference:** The agent stores the retrieved information for easy access when planning future events, optimizing efficiency in subsequent tasks.

## Custom Knowledge Base Tool

For domain-specific tasks, having a custom knowledge base can be incredibly powerful. Let's create a custom tool that allows the agent to query a vector database containing technical documentation or other specialized knowledge. By leveraging semantic search techniques, the agent can retrieve the most relevant information based on Alfred's queries.

This approach, integrating a predefined knowledge base with semantic search capabilities, provides a more context-aware and robust solution for tasks like event planning. With access to specialized knowledge, Alfred can fine-tune his party planning with precision, ensuring an unforgettable event for Gotham’s elite.

```python
from langchain.docstore.document import Document
from langchain.text_splitter import RecursiveCharacterTextSplitter
from smolagents import Tool
from langchain_community.retrievers import BM25Retriever
from smolagents import CodeAgent, HfApiModel

class PartyPlanningRetrieverTool(Tool):
    name = "party_planning_retriever"
    description = "Uses semantic search to retrieve relevant party planning ideas for Alfred’s superhero-themed party at Wayne Manor."
    inputs = {
        "query": {
            "type": "string",
            "description": "The query to perform. This should be a query related to party planning or superhero themes.",
        }
    }
    output_type = "string"

    def __init__(self, docs, **kwargs):
        super().__init__(**kwargs)
        self.retriever = BM25Retriever.from_documents(
            docs, k=5  # Retrieve the top 5 documents
        )

    def forward(self, query: str) -> str:
        assert isinstance(query, str), "Your search query must be a string"

        docs = self.retriever.invoke(
            query,
        )
        return "\nRetrieved ideas:\n" + "".join(
            [
                f"\n\n===== Idea {str(i)} =====\n" + doc.page_content
                for i, doc in enumerate(docs)
            ]
        )

# Simulate a knowledge base about party planning
party_ideas = [
    {"text": "A superhero-themed masquerade ball with luxury decor, including gold accents and velvet curtains.", "source": "Party Ideas 1"},
    {"text": "Hire a professional DJ who can play themed music for superheroes like Batman and Wonder Woman.", "source": "Entertainment Ideas"},
    {"text": "For catering, serve dishes named after superheroes, like 'The Hulk's Green Smoothie' and 'Iron Man's Power Steak.'", "source": "Catering Ideas"},
    {"text": "Decorate with iconic superhero logos and projections of Gotham and other superhero cities around the venue.", "source": "Decoration Ideas"},
    {"text": "Interactive experiences with VR where guests can engage in superhero simulations or compete in themed games.", "source": "Entertainment Ideas"}
]

source_docs = [
    Document(page_content=doc["text"], metadata={"source": doc["source"]})
    for doc in party_ideas
]

# Split the documents into smaller chunks for more efficient search
text_splitter = RecursiveCharacterTextSplitter(
    chunk_size=500,
    chunk_overlap=50,
    add_start_index=True,
    strip_whitespace=True,
    separators=["\n\n", "\n", ".", " ", ""],
)
docs_processed = text_splitter.split_documents(source_docs)

# Create the retriever tool
party_planning_retriever = PartyPlanningRetrieverTool(docs_processed)

# Initialize the agent
agent = CodeAgent(tools=[party_planning_retriever], model=HfApiModel())

# Example usage
response = agent.run(
    "Find ideas for a luxury superhero-themed party, including entertainment, catering, and decoration options."
)

print(response)
```

This enhanced agent can:
1. First check the documentation for relevant information
2. Combine insights from the knowledge base
3. Maintain conversation context through memory

## Enhanced Retrieval Capabilities

When building agentic RAG systems, the agent can employ sophisticated strategies like:

1. **Query Reformulation:** Instead of using the raw user query, the agent can craft optimized search terms that better match the target documents
2. **Multi-Step Retrieval** The agent can perform multiple searches, using initial results to inform subsequent queries
3. **Source Integration** Information can be combined from multiple sources like web search and local documentation
4. **Result Validation** Retrieved content can be analyzed for relevance and accuracy before being included in responses

Effective agentic RAG systems require careful consideration of several key aspects. The agent should select between available tools based on the query type and context. Memory systems help maintain conversation history and avoid repetitive retrievals. Having fallback strategies ensures the system can still provide value even when primary retrieval methods fail. Additionally, implementing validation steps helps ensure the accuracy and relevance of retrieved information.

## Resources

- [Agentic RAG: turbocharge your RAG with query reformulation and self-query! 🚀
](https://huggingface.co/learn/cookbook/agent_rag) - Recipe for developing an Agentic RAG system using smolagents.
