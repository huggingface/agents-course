

---
# ゲストストーリーのための RAG Tool の作成


あなたの信頼できるエージェント、Alfred は、世紀の豪華なガラパーティーの準備をしています。イベントを円滑に進めるため、Alfred は各ゲストの最新情報にすばやくアクセスする必要があります。カスタムデータセットを活用した Retrieval-Augmented Generation（RAG）Tool を作成して、Alfred を手助けしましょう。

## なぜガラパーティーに RAG が必要なのか？

Alfred がゲストの間を行き来しながら、各人の詳細をその場で思い出す必要がある場面を想像してください。従来の LLM ではこのタスクがうまくいかない可能性があります。その理由は：

1. ゲストリストはイベント固有のもので、モデルの学習データに含まれていない
2. ゲスト情報は頻繁に変更・更新される可能性がある
3. Alfred はメールアドレスなどの正確な詳細情報を取得する必要がある

ここで Retrieval Augmented Generation（RAG）が威力を発揮します！検索システムと LLM を組み合わせることで、Alfred はゲストに関する正確で最新の情報をオンデマンドで取得できます。

> [!TIP]
> この用途には、コースで取り上げたどのフレームワークでも使用できます。コードタブからお好みのオプションを選択してください。

## アプリケーションのセットアップ

このユニットでは、HF Space 上で構造化された Python プロジェクトとしてエージェントを開発します。このアプローチにより、異なる機能を別々のファイルに整理し、クリーンでモジュール化されたコードを維持できます。また、アプリケーションを一般公開するデプロイのような、より現実的なユースケースにも対応できます。

### プロジェクト構成

- **`tools.py`** – エージェント用の補助ツールを提供します。
- **`retriever.py`** – 知識アクセスをサポートする検索機能を実装します。
- **`app.py`** – すべてのコンポーネントを統合して完全に機能するエージェントにします。このユニットの最後のパートで完成させます。

実践的なリファレンスとして、[この HF Space](https://huggingface.co/spaces/agents-course/Unit_3_Agentic_RAG) をご覧ください。このユニットで開発する Agentic RAG がライブで動作しています。クローンして自由に実験してみてください！

以下でエージェントを直接テストできます：

🔗 **[リンクを開く](https://agents-course-unit-3-agentic-rag.hf.space)**

## データセットの概要

データセット [`agents-course/unit3-invitees`](https://huggingface.co/datasets/agents-course/unit3-invitees/) には、各ゲストについて以下のフィールドが含まれています：

- **Name**：ゲストのフルネーム
- **Relation**：ホストとの関係
- **Description**：ゲストの簡単な経歴や興味深い事実
- **Email Address**：招待状やフォローアップを送るための連絡先情報

以下はデータセットのプレビューです：
🔗 **[デモを開く](https://huggingface.co/datasets/agents-course/unit3-invitees/embed/viewer/default/train)**

> [!TIP]
> 実際のシナリオでは、このデータセットに食事の好み、プレゼントの関心事、避けるべき会話トピック、その他ホストに役立つ詳細情報を追加できます。

## ゲストブック Tool の構築

Alfred がガラパーティー中にゲスト情報をすばやく取得できるカスタム Tool を作成します。これを3つの管理しやすいステップに分けましょう：

1. データセットの読み込みと準備
2. Retriever Tool の作成
3. Alfred との Tool 統合

まずはデータセットの読み込みと準備から始めましょう！

### ステップ 1：データセットの読み込みと準備

まず、生のゲストデータを検索に最適化された形式に変換する必要があります。

<hfoptions id="agents-frameworks">
<hfoption id="smolagents">

Hugging Face の `datasets` ライブラリを使用してデータセットを読み込み、`langchain.docstore.document` モジュールの `Document` オブジェクトのリストに変換します。

```python
import datasets
from langchain_core.documents import Document

# データセットの読み込み
guest_dataset = datasets.load_dataset("agents-course/unit3-invitees", split="train")

# データセットのエントリを Document オブジェクトに変換
docs = [
    Document(
        page_content="\n".join([
            f"Name: {guest['name']}",
            f"Relation: {guest['relation']}",
            f"Description: {guest['description']}",
            f"Email: {guest['email']}"
        ]),
        metadata={"name": guest["name"]}
    )
    for guest in guest_dataset
]

```

</hfoption>
<hfoption id="llama-index">

Hugging Face の `datasets` ライブラリを使用してデータセットを読み込み、`llama_index.core.schema` モジュールの `Document` オブジェクトのリストに変換します。

```python
import datasets
from llama_index.core.schema import Document

# データセットの読み込み
guest_dataset = datasets.load_dataset("agents-course/unit3-invitees", split="train")

# データセットのエントリを Document オブジェクトに変換
docs = [
    Document(
        text="\n".join([
            f"Name: {guest_dataset['name'][i]}",
            f"Relation: {guest_dataset['relation'][i]}",
            f"Description: {guest_dataset['description'][i]}",
            f"Email: {guest_dataset['email'][i]}"
        ]),
        metadata={"name": guest_dataset['name'][i]}
    )
    for i in range(len(guest_dataset))
]
```

</hfoption>
<hfoption id="langgraph">

Hugging Face の `datasets` ライブラリを使用してデータセットを読み込み、`langchain.docstore.document` モジュールの `Document` オブジェクトのリストに変換します。

```python
import datasets
from langchain_core.documents import Document

# データセットの読み込み
guest_dataset = datasets.load_dataset("agents-course/unit3-invitees", split="train")

# データセットのエントリを Document オブジェクトに変換
docs = [
    Document(
        page_content="\n".join([
            f"Name: {guest['name']}",
            f"Relation: {guest['relation']}",
            f"Description: {guest['description']}",
            f"Email: {guest['email']}"
        ]),
        metadata={"name": guest["name"]}
    )
    for guest in guest_dataset
]
```

</hfoption>
</hfoptions>

上記のコードでは以下を行っています：
- データセットの読み込み
- 各ゲストエントリをフォーマットされたコンテンツを持つ `Document` オブジェクトに変換
- `Document` オブジェクトをリストに格納

これですべてのデータが整理された形で利用可能になり、検索の設定を始められます。

### ステップ 2：Retriever Tool の作成

次に、Alfred がゲスト情報を検索するために使用できるカスタム Tool を作成しましょう。

<hfoptions id="agents-frameworks">
<hfoption id="smolagents">

`langchain_community.retrievers` モジュールの `BM25Retriever` を使用して Retriever Tool を作成します。

> [!TIP]
> <code>BM25Retriever</code> は検索の出発点として優れていますが、より高度なセマンティック検索には、<a href="https://www.sbert.net/">sentence-transformers</a> のような埋め込みベースの Retriever の使用を検討してください。

```python
from smolagents import Tool
from langchain_community.retrievers import BM25Retriever

class GuestInfoRetrieverTool(Tool):
    name = "guest_info_retriever"
    description = "Retrieves detailed information about gala guests based on their name or relation."
    inputs = {
        "query": {
            "type": "string",
            "description": "The name or relation of the guest you want information about."
        }
    }
    output_type = "string"

    def __init__(self, docs):
        self.is_initialized = False
        self.retriever = BM25Retriever.from_documents(docs)

    def forward(self, query: str):
        results = self.retriever.invoke(query)
        if results:
            return "\n\n".join([doc.page_content for doc in results[:3]])
        else:
            return "No matching guest information found."

# ツールの初期化
guest_info_tool = GuestInfoRetrieverTool(docs)
```

この Tool をステップごとに理解しましょう：
- `name` と `description` は、エージェントがこの Tool をいつどのように使うべきかを理解するのに役立ちます
- `inputs` は Tool が期待するパラメータ（この場合は検索クエリ）を定義します
- 埋め込みを必要としない強力なテキスト検索アルゴリズムである `BM25Retriever` を使用しています
- `forward` メソッドがクエリを処理し、最も関連性の高いゲスト情報を返します

</hfoption>
<hfoption id="llama-index">

`llama_index.retrievers.bm25` モジュールの `BM25Retriever` を使用して Retriever Tool を作成します。

> [!TIP]
> <code>BM25Retriever</code> は検索の出発点として優れていますが、より高度なセマンティック検索には、<a href="https://www.sbert.net/">sentence-transformers</a> のような埋め込みベースの Retriever の使用を検討してください。

```python
from llama_index.core.tools import FunctionTool
from llama_index.retrievers.bm25 import BM25Retriever

bm25_retriever = BM25Retriever.from_defaults(nodes=docs)

def get_guest_info_retriever(query: str) -> str:
    """Retrieves detailed information about gala guests based on their name or relation."""
    results = bm25_retriever.retrieve(query)
    if results:
        return "\n\n".join([doc.text for doc in results[:3]])
    else:
        return "No matching guest information found."

# ツールの初期化
guest_info_tool = FunctionTool.from_defaults(get_guest_info_retriever)
```

この Tool をステップごとに理解しましょう。
- docstring は、エージェントがこの Tool をいつどのように使うべきかを理解するのに役立ちます
- 型デコレータは Tool が期待するパラメータ（この場合は検索クエリ）を定義します
- 埋め込みを必要としない強力なテキスト検索アルゴリズムである `BM25Retriever` を使用しています
- このメソッドがクエリを処理し、最も関連性の高いゲスト情報を返します

</hfoption>
<hfoption id="langgraph">

`langchain_community.retrievers` モジュールの `BM25Retriever` を使用して Retriever Tool を作成します。

> [!TIP]
> <code>BM25Retriever</code> は検索の出発点として優れていますが、より高度なセマンティック検索には、<a href="https://www.sbert.net/">sentence-transformers</a> のような埋め込みベースの Retriever の使用を検討してください。

```python
from langchain_community.retrievers import BM25Retriever
from langchain_core.tools import Tool

bm25_retriever = BM25Retriever.from_documents(docs)

def extract_text(query: str) -> str:
    """Retrieves detailed information about gala guests based on their name or relation."""
    results = bm25_retriever.invoke(query)
    if results:
        return "\n\n".join([doc.page_content for doc in results[:3]])
    else:
        return "No matching guest information found."

guest_info_tool = Tool(
    name="guest_info_retriever",
    func=extract_text,
    description="Retrieves detailed information about gala guests based on their name or relation."
)
```

この Tool をステップごとに理解しましょう。
- `name` と `description` は、エージェントがこの Tool をいつどのように使うべきかを理解するのに役立ちます
- 型デコレータは Tool が期待するパラメータ（この場合は検索クエリ）を定義します
- 埋め込みを必要としない強力なテキスト検索アルゴリズムである `BM25Retriever` を使用しています
- このメソッドがクエリを処理し、最も関連性の高いゲスト情報を返します


</hfoption>
</hfoptions>

### ステップ 3：Alfred との Tool 統合

最後に、エージェントを作成しカスタム Tool を装備して、すべてをまとめましょう：

<hfoptions id="agents-frameworks">
<hfoption id="smolagents">

```python
from smolagents import CodeAgent, InferenceClientModel

# Hugging Face モデルの初期化
model = InferenceClientModel()

# ゲスト情報ツールを持つガラエージェント Alfred の作成
alfred = CodeAgent(tools=[guest_info_tool], model=model)

# ガラパーティー中に Alfred が受け取る可能性のあるクエリの例
response = alfred.run("Tell me about our guest named 'Lady Ada Lovelace'.")

print("🎩 Alfred's Response:")
print(response)
```

期待される出力：

```
🎩 Alfred's Response:
Based on the information I retrieved, Lady Ada Lovelace is an esteemed mathematician and friend. She is renowned for her pioneering work in mathematics and computing, often celebrated as the first computer programmer due to her work on Charles Babbage's Analytical Engine. Her email address is ada.lovelace@example.com.
```

この最終ステップで行っていること：
- `InferenceClientModel` クラスを使用して Hugging Face モデルを初期化
- エージェント（Alfred）を Python コードを実行して問題を解決できる `CodeAgent` として作成
- Alfred に「Lady Ada Lovelace」という名前のゲストの情報を取得するよう依頼

</hfoption>
<hfoption id="llama-index">

```python
from llama_index.core.agent.workflow import AgentWorkflow
from llama_index.llms.huggingface_api import HuggingFaceInferenceAPI

# Hugging Face モデルの初期化
llm = HuggingFaceInferenceAPI(model_name="Qwen/Qwen2.5-Coder-32B-Instruct")

# ゲスト情報ツールを持つガラエージェント Alfred の作成
alfred = AgentWorkflow.from_tools_or_functions(
    [guest_info_tool],
    llm=llm,
)

# ガラパーティー中に Alfred が受け取る可能性のあるクエリの例
response = await alfred.run("Tell me about our guest named 'Lady Ada Lovelace'.")

print("🎩 Alfred's Response:")
print(response)
```

期待される出力：

```
🎩 Alfred's Response:
Lady Ada Lovelace is an esteemed mathematician and friend, renowned for her pioneering work in mathematics and computing. She is celebrated as the first computer programmer due to her work on Charles Babbage's Analytical Engine. Her email is ada.lovelace@example.com.
```

この最終ステップで行っていること：
- `HuggingFaceInferenceAPI` クラスを使用して Hugging Face モデルを初期化
- エージェント（Alfred）を、作成した Tool を含む `AgentWorkflow` として作成
- Alfred に「Lady Ada Lovelace」という名前のゲストの情報を取得するよう依頼

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

# ツールを含むチャットインターフェースの生成
llm = HuggingFaceEndpoint(
    repo_id="Qwen/Qwen2.5-Coder-32B-Instruct",
    huggingfacehub_api_token=HUGGINGFACEHUB_API_TOKEN,
)

chat = ChatHuggingFace(llm=llm, verbose=True)
tools = [guest_info_tool]
chat_with_tools = chat.bind_tools(tools)

# AgentState とエージェントグラフの生成
class AgentState(TypedDict):
    messages: Annotated[list[AnyMessage], add_messages]

def assistant(state: AgentState):
    return {
        "messages": [chat_with_tools.invoke(state["messages"])],
    }

## グラフ
builder = StateGraph(AgentState)

# ノードの定義：実際の処理を行う
builder.add_node("assistant", assistant)
builder.add_node("tools", ToolNode(tools))

# エッジの定義：制御フローの移動方法を決定する
builder.add_edge(START, "assistant")
builder.add_conditional_edges(
    "assistant",
    # 最新のメッセージがツールを必要とする場合はツールにルーティング
    # そうでなければ直接応答を提供
    tools_condition,
)
builder.add_edge("tools", "assistant")
alfred = builder.compile()

messages = [HumanMessage(content="Tell me about our guest named 'Lady Ada Lovelace'.")]
response = alfred.invoke({"messages": messages})

print("🎩 Alfred's Response:")
print(response['messages'][-1].content)
```

期待される出力：

```
🎩 Alfred's Response:
Lady Ada Lovelace is an esteemed mathematician and pioneer in computing, often celebrated as the first computer programmer due to her work on Charles Babbage's Analytical Engine.
```

この最終ステップで行っていること：
- `HuggingFaceEndpoint` クラスを使用して Hugging Face モデルを初期化し、チャットインターフェースを生成してツールを追加
- エージェント（Alfred）を、2つのノード（`assistant`、`tools`）をエッジで結合した `StateGraph` として作成
- Alfred に「Lady Ada Lovelace」という名前のゲストの情報を取得するよう依頼

</hfoption>
</hfoptions>

## インタラクションの例

ガラパーティー中の会話は次のような流れになるかもしれません：

**あなた：** 「Alfred、大使と話しているあの紳士は誰ですか？」

**Alfred：** *すばやくゲストデータベースを検索* 「あちらはニコラ・テスラ博士です。大学時代からの旧友でいらっしゃいます。最近、新しい無線エネルギー伝送システムの特許を取得され、ぜひお話ししたいとのことです。ハトに情熱をお持ちですので、それが良い話題になるかもしれません。」

```json
{
    "name": "Dr. Nikola Tesla",
    "relation": "old friend from university days",  
    "description": "Dr. Nikola Tesla is an old friend from your university days. He's recently patented a new wireless energy transmission system and would be delighted to discuss it with you. Just remember he's passionate about pigeons, so that might make for good small talk.",
    "email": "nikola.tesla@gmail.com"
}
```

## さらなる発展

Alfred がゲスト情報を取得できるようになったので、このシステムをさらに強化する方法を検討してみましょう：

1. **Retriever を改善**して、[sentence-transformers](https://www.sbert.net/) のようなより高度なアルゴリズムを使用する
2. **会話メモリを実装**して、Alfred が以前のやり取りを記憶できるようにする
3. **Web 検索と組み合わせて**、馴染みのないゲストの最新情報を取得する
4. **複数のインデックスを統合**して、検証済みのソースからより完全な情報を取得する

これで Alfred はゲストの問い合わせを難なく処理できるようになり、あなたのガラパーティーが世紀で最も洗練された素晴らしいイベントとして記憶されること間違いなしです！

> [!TIP]
> Retriever Tool を拡張して、各ゲストの興味や経歴に基づいた会話のきっかけも返すようにしてみましょう。これを実現するために Tool をどのように修正しますか？
>
> 完成したら、ゲスト Retriever Tool を <code>retriever.py</code> ファイルに実装してください。

---

<!-- nav -->

[⬅️ 前へ: エージェント用ツール](tools.md) | [📚 目次](../../README.md) | [次へ: ガラエージェントの作成 ➡️](agent.md)
