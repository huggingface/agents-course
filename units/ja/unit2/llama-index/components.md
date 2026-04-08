# LlamaIndex のコンポーネントとは？

Unit 1 で紹介した、私たちの頼れる執事エージェント、Alfred を覚えていますか？
Alfred が効果的に私たちをサポートするためには、リクエストを理解し、**関連する情報を準備・検索・活用してタスクを完了する**必要があります。
ここで LlamaIndex のコンポーネントが登場します。

LlamaIndex には多くのコンポーネントがありますが、**ここでは特に `QueryEngine` コンポーネントに焦点を当てます。**
なぜでしょうか？それは、エージェントの RAG（Retrieval-Augmented Generation）ツールとして使用できるからです。

では、RAG とは何でしょうか？LLM は汎用的な知識を学習するために膨大なデータで訓練されています。
しかし、関連性のある最新のデータでは訓練されていない場合があります。
RAG は、あなたのデータから関連情報を検索・取得し、それを LLM に提供することでこの問題を解決します。

![RAG](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/llama-index/rag.png)

それでは、Alfred がどのように機能するか考えてみましょう：

1. あなたは Alfred にディナーパーティーの計画を手伝ってもらいます
2. Alfred はあなたのカレンダー、食事の好み、過去に成功したメニューを確認する必要があります
3. `QueryEngine` が Alfred にこれらの情報を見つけ、ディナーパーティーの計画に活用する手助けをします

これにより、`QueryEngine` は LlamaIndex における**エージェント型 RAG ワークフローを構築するための重要なコンポーネント**となります。
Alfred が役立つために家庭の情報を検索する必要があるように、どのエージェントにも関連データを見つけて理解する方法が必要です。
`QueryEngine` はまさにこの機能を提供します。

それでは、コンポーネントについてもう少し深く掘り下げ、**コンポーネントを組み合わせて RAG パイプラインを作成する方法**を見ていきましょう。

## コンポーネントを使った RAG パイプラインの作成

> [!TIP]
> <a href="https://huggingface.co/agents-course/notebooks/blob/main/unit2/llama-index/components.ipynb" target="_blank">こちらのノートブック</a>のコードに沿って進めることができます。Google Colab を使って実行できます。

RAG には 5 つの重要なステージがあり、これらは構築するほとんどの大規模アプリケーションの一部となります：

1. **Loading（読み込み）**: データが存在する場所（テキストファイル、PDF、ウェブサイト、データベース、API など）からワークフローにデータを取り込むことを指します。LlamaHub は数百のインテグレーションを提供しています。
2. **Indexing（インデックス作成）**: データをクエリ可能にするデータ構造を作成することを意味します。LLM の場合、ほぼ常にベクトル埋め込み（データの意味を数値で表現したもの）の作成を意味します。インデックス作成には、プロパティに基づいて文脈的に関連するデータを正確に見つけやすくするための、さまざまなメタデータ戦略も含まれます。
3. **Storing（保存）**: データのインデックスが作成されたら、再インデックスを避けるために、インデックスやその他のメタデータを保存する必要があります。
4. **Querying（クエリ）**: どのインデックス戦略に対しても、LLM と LlamaIndex のデータ構造を活用する多くの方法があります。サブクエリ、マルチステップクエリ、ハイブリッド戦略などが含まれます。
5. **Evaluation（評価）**: あらゆるフローにおける重要なステップは、他の戦略と比較して、または変更を加えた際に、どの程度効果的かを確認することです。評価は、クエリに対する応答がどれだけ正確で、忠実で、高速であるかの客観的な指標を提供します。

次に、コンポーネントを使ってこれらのステージを再現する方法を見ていきましょう。

### ドキュメントの読み込みと埋め込み

前述のとおり、LlamaIndex は独自のデータの上で動作できますが、**データにアクセスする前に、まずそれを読み込む必要があります。**
LlamaIndex にデータを読み込む主な方法は 3 つあります：

1. `SimpleDirectoryReader`: ローカルディレクトリからさまざまなファイル形式を読み込む組み込みローダー。
2. `LlamaParse`: LlamaIndex 公式の PDF パース用ツールで、マネージド API として利用可能。
3. `LlamaHub`: あらゆるソースからデータを取り込むための数百のデータ読み込みライブラリのレジストリ。

> [!TIP]
> より複雑なデータソースについては、<a href="https://docs.llamaindex.ai/en/stable/module_guides/loading/connector/">LlamaHub</a> のローダーや <a href="https://github.com/run-llama/llama_cloud_services/blob/main/parse.md">LlamaParse</a> パーサーに慣れておくとよいでしょう。

**データを読み込む最も簡単な方法は `SimpleDirectoryReader` を使うことです。**
この汎用コンポーネントは、フォルダからさまざまなファイル形式を読み込み、LlamaIndex が扱える `Document` オブジェクトに変換できます。
`SimpleDirectoryReader` を使ってフォルダからデータを読み込む方法を見てみましょう。

```python
from llama_index.core import SimpleDirectoryReader

reader = SimpleDirectoryReader(input_dir="path/to/directory")
documents = reader.load_data()
```

ドキュメントを読み込んだ後、`Node` オブジェクトと呼ばれるより小さな断片に分割する必要があります。
`Node` は、元のドキュメントから切り出されたテキストの塊で、AI が扱いやすいサイズになっています。元の `Document` オブジェクトへの参照は保持されます。

`IngestionPipeline` は、2 つの主要な変換を通じてこれらのノードを作成するのに役立ちます。
1. `SentenceSplitter` は、自然な文の区切りでドキュメントを扱いやすいチャンクに分割します。
2. `HuggingFaceEmbedding` は、各チャンクを数値埋め込み（意味を AI が効率的に処理できる形で捉えたベクトル表現）に変換します。

このプロセスにより、検索や分析に適した形でドキュメントを整理できます。

```python
from llama_index.core import Document
from llama_index.embeddings.huggingface import HuggingFaceEmbedding
from llama_index.core.node_parser import SentenceSplitter
from llama_index.core.ingestion import IngestionPipeline

# 変換処理を含むパイプラインを作成
pipeline = IngestionPipeline(
    transformations=[
        SentenceSplitter(chunk_overlap=0),
        HuggingFaceEmbedding(model_name="BAAI/bge-small-en-v1.5"),
    ]
)

nodes = await pipeline.arun(documents=[Document.example()])
```


### ドキュメントの保存とインデックス作成

`Node` オブジェクトを作成したら、検索可能にするためにインデックスを作成する必要がありますが、その前にデータを保存する場所が必要です。

インジェスションパイプラインを使用しているため、パイプラインにベクトルストアを直接接続してデータを格納できます。
ここでは、ドキュメントの保存に `Chroma` を使用します。

<details>
<summary>ChromaDB のインストール</summary>

<a href="./llama-hub">LlamaHub のセクション</a>で紹介したように、以下のコマンドで ChromaDB ベクトルストアをインストールできます：

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
> さまざまなベクトルストアの概要は <a href="https://docs.llamaindex.ai/en/stable/module_guides/storing/vector_stores/">LlamaIndex のドキュメント</a>で確認できます。


ここでベクトル埋め込みが活躍します。クエリとノードの両方を同じベクトル空間に埋め込むことで、関連する一致を見つけることができます。
`VectorStoreIndex` はこの処理を自動的に行い、一貫性を確保するためにインジェスション時と同じ埋め込みモデルを使用します。

ベクトルストアと埋め込みからこのインデックスを作成する方法を見てみましょう：

```python
from llama_index.core import VectorStoreIndex
from llama_index.embeddings.huggingface import HuggingFaceEmbedding

embed_model = HuggingFaceEmbedding(model_name="BAAI/bge-small-en-v1.5")
index = VectorStoreIndex.from_vector_store(vector_store, embed_model=embed_model)
```

すべての情報は `ChromaVectorStore` オブジェクトと指定されたディレクトリパスに自動的に永続化されます。

素晴らしい！インデックスの保存と読み込みが簡単にできるようになったので、さまざまな方法でクエリを実行する方法を見ていきましょう。

### プロンプトと LLM を使った VectorStoreIndex のクエリ

インデックスにクエリを実行する前に、クエリインターフェースに変換する必要があります。最も一般的な変換オプションは以下の通りです：

- `as_retriever`: 基本的なドキュメント検索用。類似度スコア付きの `NodeWithScore` オブジェクトのリストを返します
- `as_query_engine`: 単一の質問応答インタラクション用。テキストの応答を返します
- `as_chat_engine`: 複数メッセージにわたってメモリを維持する会話型インタラクション用。チャット履歴とインデックスされたコンテキストを使用してテキストの応答を返します

エージェント的なインタラクションではより一般的なため、ここではクエリエンジンに焦点を当てます。
応答に使用する LLM もクエリエンジンに渡します。

```python
from llama_index.llms.huggingface_api import HuggingFaceInferenceAPI

llm = HuggingFaceInferenceAPI(model_name="Qwen/Qwen2.5-Coder-32B-Instruct")
query_engine = index.as_query_engine(
    llm=llm,
    response_mode="tree_summarize",
)
query_engine.query("What is the meaning of life?")
# 人生の意味は42です
```

### レスポンス処理

内部的には、クエリエンジンは質問に答えるために LLM を使うだけでなく、レスポンスを処理する戦略として `ResponseSynthesizer` も使用しています。
これも完全にカスタマイズ可能ですが、すぐに使える 3 つの主要な戦略があります：

- `refine`: 取得した各テキストチャンクを順番に処理して回答を作成・改善します。Node/取得チャンクごとに個別の LLM 呼び出しを行います。
- `compact`（デフォルト）: refine と似ていますが、チャンクを事前に結合するため、LLM 呼び出し回数が少なくなります。
- `tree_summarize`: 取得した各テキストチャンクを処理し、回答のツリー構造を作成して詳細な回答を生成します。

> [!TIP]
> <a href="https://docs.llamaindex.ai/en/stable/module_guides/deploying/query_engine/usage_pattern/#low-level-composition-api">低レベル合成 API</a> でクエリワークフローをきめ細かく制御できます。この API を使えば、クエリプロセスの各ステップを正確なニーズに合わせてカスタマイズ・微調整でき、<a href="https://docs.llamaindex.ai/en/stable/module_guides/workflow/">Workflows</a> との相性も抜群です。

言語モデルは常に予測可能な動作をするとは限らないため、得られる回答が常に正しいとは限りません。これに対処するには、**回答の品質を評価する**ことが重要です。

### 評価と可観測性

LlamaIndex は**レスポンス品質を評価するための組み込み評価ツール**を提供しています。
これらの評価器は LLM を活用して、さまざまな観点からレスポンスを分析します。
利用可能な 3 つの主要な評価器を見てみましょう：

- `FaithfulnessEvaluator`: 回答がコンテキストによって裏付けられているかを確認し、回答の忠実性を評価します。
- `AnswerRelevancyEvaluator`: 回答が質問に関連しているかを確認し、回答の関連性を評価します。
- `CorrectnessEvaluator`: 回答が正しいかを確認し、回答の正確性を評価します。

> [!TIP]
> エージェントの可観測性と評価についてもっと学びたいですか？<a href="https://huggingface.co/learn/agents-course/bonus-unit2/introduction">ボーナス Unit 2</a> で学習を続けましょう。

```python
from llama_index.core.evaluation import FaithfulnessEvaluator

query_engine = # 前のセクションから
llm = # 前のセクションから

# インデックスにクエリ
evaluator = FaithfulnessEvaluator(llm=llm)
response = query_engine.query(
    "What battles took place in New York City in the American Revolution?"
)
eval_result = evaluator.evaluate_response(response=response)
eval_result.passing
```

直接的な評価がなくても、**可観測性を通じてシステムのパフォーマンスに関する洞察を得ることができます。**
これは、より複雑なワークフローを構築する際に、各コンポーネントがどのように機能しているかを理解するのに特に有用です。

<details>
<summary>LlamaTrace のインストール</summary>

<a href="./llama-hub">LlamaHub のセクション</a>で紹介したように、以下のコマンドで Arize Phoenix の LlamaTrace コールバックをインストールできます：

```bash
pip install -U llama-index-callbacks-arize-phoenix
```

さらに、`PHOENIX_API_KEY` 環境変数に LlamaTrace の API キーを設定する必要があります。以下の手順で取得できます：
- [LlamaTrace](https://llamatrace.com/login) でアカウントを作成
- アカウント設定で API キーを生成
- 以下のコードでその API キーを使用してトレーシングを有効化

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
> コンポーネントとその使い方についてもっと学びたいですか？<a href="https://docs.llamaindex.ai/en/stable/module_guides/">コンポーネントガイド</a>や <a href="https://docs.llamaindex.ai/en/stable/understanding/rag/">RAG ガイド</a>で学習を続けましょう。

ここまでで、コンポーネントを使って `QueryEngine` を作成する方法を見てきました。次は、**`QueryEngine` をエージェントのツールとして使用する方法**を見ていきましょう！

---

<!-- nav -->

[⬅️ 前へ: LlamaIndex 入門](introduction.md) | [📚 目次](../../README.md) | [次へ: LlamaIndex: Tool ➡️](tools.md)
