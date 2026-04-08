# LlamaIndex での Tool の使用

**明確な Tool のセットを定義することはパフォーマンスにとって極めて重要です。** [ユニット1](../../unit1/tools)で説明したように、明確な Tool インターフェースは LLM にとって使いやすくなります。
人間のエンジニア向けのソフトウェア API インターフェースと同様に、Tool の仕組みが理解しやすければ、より多くの価値を引き出すことができます。

LlamaIndex には**4つの主要な Tool タイプ**があります：

![Tools](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/llama-index/tools.png)

1. `FunctionTool`：任意の Python 関数を Agent が使用できる Tool に変換します。関数の動作を自動的に解析します。
2. `QueryEngineTool`：Agent がクエリエンジンを使用できるようにする Tool です。Agent はクエリエンジンの上に構築されているため、他の Agent を Tool として使用することもできます。
3. `Toolspecs`：コミュニティによって作成された Tool のセットで、Gmail などの特定のサービス向けの Tool が含まれていることが多いです。
4. `Utility Tools`：他の Tool から返される大量のデータを処理するための特別な Tool です。

以下では、それぞれについて詳しく見ていきます。

## FunctionTool の作成

> [!TIP]
> <a href="https://huggingface.co/agents-course/notebooks/blob/main/unit2/llama-index/tools.ipynb" target="_blank">こちらのノートブック</a>のコードに沿って、Google Colab で実行できます。

FunctionTool は、任意の Python 関数をラップして Agent から利用可能にするシンプルな方法を提供します。
同期関数または非同期関数を、オプションの `name` および `description` パラメータとともに渡すことができます。
name と description は、Agent が Tool をいつ、どのように使用すべきかを理解するのに役立つため、特に重要です。
以下で FunctionTool の作成方法と呼び出し方を見てみましょう。

```python
from llama_index.core.tools import FunctionTool

def get_weather(location: str) -> str:
    """指定された場所の天気を取得するのに便利です。"""
    print(f"Getting weather for {location}")
    return f"The weather in {location} is sunny"

tool = FunctionTool.from_defaults(
    get_weather,
    name="my_weather_tool",
    description="Useful for getting the weather for a given location.",
)
tool.call("New York")
```

> [!TIP]
> Function Calling を備えた Agent や LLM を使用する場合、選択される Tool（およびその Tool に対して書かれる引数）は、Tool の名前と、Tool の目的や引数の説明に強く依存します。Function Calling について詳しくは <a href="https://docs.llamaindex.ai/en/stable/examples/workflow/function_calling_agent/">Function Calling ガイド</a>をご覧ください。

## QueryEngineTool の作成

前のユニットで定義した `QueryEngine` は、`QueryEngineTool` クラスを使用して簡単に Tool に変換できます。
以下の例で、`QueryEngine` から `QueryEngineTool` を作成する方法を見てみましょう。

```python
from llama_index.core import VectorStoreIndex
from llama_index.core.tools import QueryEngineTool
from llama_index.llms.huggingface_api import HuggingFaceInferenceAPI
from llama_index.embeddings.huggingface import HuggingFaceEmbedding
from llama_index.vector_stores.chroma import ChromaVectorStore

embed_model = HuggingFaceEmbedding("BAAI/bge-small-en-v1.5")

db = chromadb.PersistentClient(path="./alfred_chroma_db")
chroma_collection = db.get_or_create_collection("alfred")
vector_store = ChromaVectorStore(chroma_collection=chroma_collection)

index = VectorStoreIndex.from_vector_store(vector_store, embed_model=embed_model)

llm = HuggingFaceInferenceAPI(model_name="Qwen/Qwen2.5-Coder-32B-Instruct")
query_engine = index.as_query_engine(llm=llm)
tool = QueryEngineTool.from_defaults(query_engine, name="some useful name", description="some useful description")
```

## Toolspecs の作成

`ToolSpecs` は、調和して連携する Tool のコレクションと考えてください。整備士のツールキットに車両修理のための補完的な工具が揃っているように、`ToolSpec` は特定の目的のために関連する Tool を組み合わせます。
例えば、会計 Agent の `ToolSpec` は、スプレッドシート機能、メール機能、計算ツールを統合し、財務タスクを正確かつ効率的に処理できるようにします。

<details>
<summary>Google Toolspec のインストール</summary>
<a href="./llama-hub">LlamaHub のセクション</a>で紹介したように、以下のコマンドで Google toolspec をインストールできます：

```python
pip install llama-index-tools-google
```
</details>

これで toolspec を読み込み、Tool のリストに変換できます。

```python
from llama_index.tools.google import GmailToolSpec

tool_spec = GmailToolSpec()
tool_spec_list = tool_spec.to_tool_list()
```

Tool の詳細を確認するには、各 Tool の `metadata` を見ることができます。

```python
[(tool.metadata.name, tool.metadata.description) for tool in tool_spec_list]
```

### LlamaIndex での Model Context Protocol（MCP）

LlamaIndex では、[LlamaHub の ToolSpec](https://llamahub.ai/l/tools/llama-index-tools-mcp?from=) を通じて MCP ツールを使用することもできます。
MCP サーバーを起動し、以下の実装を通じて使い始めることができます。

MCP についてより深く学びたい場合は、[無料の MCP コース](https://huggingface.co/learn/mcp-course/)をご覧ください。

<details>
<summary>MCP Toolspec のインストール</summary>
<a href="./llama-hub">LlamaHub のセクション</a>で紹介したように、以下のコマンドで MCP toolspec をインストールできます：

```python
pip install llama-index-tools-mcp
```
</details>

```python
from llama_index.tools.mcp import BasicMCPClient, McpToolSpec

# 127.0.0.1:8000 で MCP サーバーが稼働していることを前提としています。自分の MCP サーバーに接続するために mcp client を使用することもできます。
mcp_client = BasicMCPClient("http://127.0.0.1:8000/sse")
mcp_tool = McpToolSpec(client=mcp_client)

# Agent を取得
agent = await get_agent(mcp_tool)

# Agent コンテキストを作成
agent_context = Context(agent)
```

## Utility Tools

多くの場合、API を直接クエリすると**過剰な量のデータが返される**ことがあり、その一部は無関係であったり、LLM のコンテキストウィンドウをオーバーフローさせたり、使用するトークン数を不必要に増加させたりすることがあります。
以下で、2つの主要な Utility Tool について見ていきましょう。

1. `OnDemandToolLoader`：既存の LlamaIndex データローダー（BaseReader クラス）を Agent が使用できる Tool に変換します。この Tool は、データローダーから `load_data` をトリガーするために必要なすべてのパラメータと、自然言語のクエリ文字列で呼び出すことができます。実行時には、まずデータローダーからデータを読み込み、インデックスを作成し（例えばベクトルストアを使用）、そしてオンデマンドでクエリを実行します。これら3つのステップすべてが1回の Tool 呼び出しで行われます。
2. `LoadAndSearchToolSpec`：LoadAndSearchToolSpec は、既存の Tool を入力として受け取ります。Tool spec として `to_tool_list` を実装しており、この関数が呼び出されると、読み込み Tool と検索 Tool の2つが返されます。読み込み Tool の実行は内部の Tool を呼び出し、出力をインデックス化します（デフォルトではベクトルインデックスを使用）。検索 Tool の実行はクエリ文字列を入力として受け取り、内部のインデックスを呼び出します。

> [!TIP]
> Toolspecs と Utility Tools は <a href="https://llamahub.ai/">LlamaHub</a> で見つけることができます。

LlamaIndex での Agent と Tool の基本を理解したところで、次は **LlamaIndex を使って設定可能で管理しやすいワークフローを作成する方法**を見ていきましょう！

---

<!-- nav -->

[⬅️ 前へ: LlamaIndex コンポーネント](components.md) | [📚 目次](../../README.md) | [次へ: LlamaIndex: 小テスト 1 ➡️](quiz1.md)
