---
# エージェント型RAGシステムの構築

> [!TIP]
> <a href="https://huggingface.co/agents-course/notebooks/blob/main/unit2/smolagents/retrieval_agents.ipynb" target="_blank">このノートブック</a>のコードに沿って進めることができます。Google Colabで実行可能です。

検索拡張生成（RAG: Retrieval Augmented Generation）システムは、データ検索と生成モデルの機能を組み合わせて、文脈を考慮した応答を提供します。例えば、ユーザーのクエリが検索エンジンに渡され、取得された結果がクエリとともにモデルに与えられます。モデルはクエリと取得された情報に基づいて応答を生成します。

エージェント型RAG（Agentic RAG）は、従来のRAGシステムを拡張し、**自律的なエージェントと動的な知識検索を組み合わせた**ものです。

従来のRAGシステムが取得したデータに基づいてLLMでクエリに回答するのに対し、エージェント型RAGは**検索と生成の両プロセスをインテリジェントに制御**し、効率性と精度を向上させます。

従来のRAGシステムには、**単一の検索ステップに依存する**ことや、ユーザーのクエリとの直接的な意味的類似性に焦点を当てるため関連情報を見落とす可能性があるといった重要な制限があります。

エージェント型RAGは、エージェントが自律的に検索クエリを構築し、取得した結果を評価し、複数の検索ステップを実行することで、より的確で包括的な出力を実現します。

## DuckDuckGoによる基本的な検索

DuckDuckGoを使ってウェブ検索ができるシンプルなエージェントを構築しましょう。このエージェントは情報を取得し、クエリに対する回答を統合して応答を生成します。エージェント型RAGにより、アルフレッドのエージェントは以下のことが可能です：

* 最新のスーパーヒーローパーティーのトレンドを検索
* ラグジュアリーな要素を含むように結果を絞り込み
* 情報を統合して完全なプランを作成

アルフレッドのエージェントがこれを実現する方法は以下の通りです：

```python
from smolagents import CodeAgent, DuckDuckGoSearchTool, InferenceClientModel

# 検索ツールの初期化
search_tool = DuckDuckGoSearchTool()

# モデルの初期化
model = InferenceClientModel()

agent = CodeAgent(
    model=model,
    tools=[search_tool],
)

# 使用例
response = agent.run(
    "Search for luxury superhero-themed party ideas, including decorations, entertainment, and catering."
)
print(response)
```

エージェントは以下のプロセスに従います：

1. **リクエストの分析：** アルフレッドのエージェントは、クエリの主要な要素（ラグジュアリーなスーパーヒーローテーマのパーティー企画、装飾・エンターテインメント・ケータリングの重視）を特定します。
2. **検索の実行：** エージェントはDuckDuckGoを活用して、最も関連性が高く最新の情報を検索し、アルフレッドのラグジュアリーなイベントへのこだわりに合致する情報を確保します。
3. **情報の統合：** 結果を収集した後、エージェントはそれらをパーティーのあらゆる側面をカバーする、まとまりのある実行可能なプランに加工します。
4. **将来の参照用に保存：** エージェントは取得した情報を保存し、将来のイベント企画時に簡単にアクセスできるようにすることで、以降のタスクの効率を最適化します。

## カスタムナレッジベースツール

専門的なタスクには、カスタムナレッジベースが非常に有用です。技術ドキュメントや専門知識のベクトルデータベースにクエリを実行するツールを作成しましょう。セマンティック検索を使用することで、エージェントはアルフレッドのニーズに最も関連性の高い情報を見つけることができます。

ベクトルデータベースは、機械学習モデルによって作成されたテキストやその他のデータの数値表現（エンベディング）を格納します。高次元空間における類似した意味を識別することで、セマンティック検索を可能にします。

このアプローチは、事前定義された知識とセマンティック検索を組み合わせて、イベント企画のための文脈を考慮したソリューションを提供します。専門知識へのアクセスにより、アルフレッドはパーティーのあらゆる細部を完璧に仕上げることができます。

この例では、カスタムナレッジベースからパーティー企画のアイデアを取得するツールを作成します。ナレッジベースを検索して上位の結果を返すためにBM25リトリーバーを使用し、より効率的な検索のためにドキュメントを小さなチャンクに分割する`RecursiveCharacterTextSplitter`を使用します。

```python
from langchain_community.docstore.document import Document
from langchain_text_splitters import RecursiveCharacterTextSplitter
from smolagents import Tool
from langchain_community.retrievers import BM25Retriever
from smolagents import CodeAgent, InferenceClientModel

class PartyPlanningRetrieverTool(Tool):
    name = "party_planning_retriever"
    description = "Uses semantic search to retrieve relevant party planning ideas for Alfred's superhero-themed party at Wayne Manor."
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
            docs, k=5  # 上位5件のドキュメントを取得
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

# パーティー企画に関するナレッジベースをシミュレート
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

# より効率的な検索のためにドキュメントを小さなチャンクに分割
text_splitter = RecursiveCharacterTextSplitter(
    chunk_size=500,
    chunk_overlap=50,
    add_start_index=True,
    strip_whitespace=True,
    separators=["\n\n", "\n", ".", " ", ""],
)
docs_processed = text_splitter.split_documents(source_docs)

# リトリーバーツールの作成
party_planning_retriever = PartyPlanningRetrieverTool(docs_processed)

# エージェントの初期化
agent = CodeAgent(tools=[party_planning_retriever], model=InferenceClientModel())

# 使用例
response = agent.run(
    "Find ideas for a luxury superhero-themed party, including entertainment, catering, and decoration options."
)

print(response)
```

この強化されたエージェントは以下のことが可能です：
1. まずドキュメントから関連情報を確認
2. ナレッジベースからの知見を統合
3. メモリ内で会話のコンテキストを維持

## 高度な検索機能

エージェント型RAGシステムを構築する際、エージェントは以下のような高度な戦略を採用できます：

1. **クエリの再構築（Query Reformulation）：** 生のユーザークエリをそのまま使用する代わりに、エージェントが対象ドキュメントにより適合する最適化された検索語を作成できます
2. **クエリの分解（Query Decomposition）：** ユーザークエリを直接使用する代わりに、クエリに複数の情報が含まれている場合、複数のクエリに分解できます
3. **クエリの拡張（Query Expansion）：** クエリの再構築と似ていますが、クエリを複数の表現で言い換えて、それらすべてで検索を行います
4. **リランキング（Reranking）：** Cross-Encoderを使用して、取得したドキュメントと検索クエリ間のより包括的で意味的な関連性スコアを付与します
5. **多段階検索（Multi-Step Retrieval）：** エージェントが複数の検索を実行し、最初の結果を基に後続のクエリを調整できます
6. **ソースの統合（Source Integration）：** ウェブ検索やローカルドキュメントなど、複数のソースからの情報を統合できます
7. **結果の検証（Result Validation）：** 取得したコンテンツを応答に含める前に、関連性と正確性を分析できます

効果的なエージェント型RAGシステムには、いくつかの重要な側面を慎重に検討する必要があります。エージェントは**クエリの種類とコンテキストに基づいて、利用可能なツールから適切なものを選択すべき**です。メモリシステムは会話履歴を維持し、重複した検索を回避するのに役立ちます。フォールバック戦略を持つことで、主要な検索方法が失敗した場合でもシステムが価値を提供できるようになります。さらに、検証ステップを実装することで、取得した情報の正確性と関連性を確保できます。

## リソース

- [Agentic RAG: turbocharge your RAG with query reformulation and self-query! 🚀](https://huggingface.co/learn/cookbook/agent_rag) - smolagentsを使用したエージェント型RAGシステム開発のレシピ。

---

<!-- nav -->

[⬅️ 前へ: コードエージェントの構築](code_agents.md) | [📚 目次](../../README.md) | [次へ: マルチエージェント ➡️](multi_agent_systems.md)
