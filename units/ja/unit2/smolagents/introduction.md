

# `smolagents` 入門

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/smolagents/thumbnail.jpg" alt="Unit 2.1 サムネイル"/>

このモジュールへようこそ。ここでは、軽量なAIエージェント構築フレームワークを提供する [`smolagents`](https://github.com/huggingface/smolagents) ライブラリを使って、**効果的なエージェントを構築する方法**を学びます。

`smolagents` は Hugging Face のライブラリです。ぜひ smolagents の[リポジトリ](https://github.com/huggingface/smolagents)に**スター**をつけてご支援ください：
<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/smolagents/star_smolagents.gif" alt="smolagents にスターをつける"/>

## モジュール概要

このモジュールでは、`smolagents` を使ったインテリジェントなエージェント構築に関する主要な概念と実践的な戦略を包括的に解説します。

多くのオープンソースフレームワークが利用可能な中、`smolagents` を有力な選択肢とするコンポーネントや機能を理解すること、あるいは他のソリューションがより適している場合を見極めることが重要です。

ソフトウェア開発タスク向けの Code Agent、モジュール式で関数駆動型のワークフローを構築する Tool Calling Agent、情報にアクセスして統合する Retrieval Agent など、重要なエージェントタイプを探索します。

さらに、複数エージェントのオーケストレーション、ビジョン機能やウェブブラウジングの統合についても取り上げ、動的でコンテキストを理解するアプリケーションの新たな可能性を開きます。

このユニットでは、Unit 1 に登場したエージェントの Alfred が再登場します。今回、彼は内部の仕組みに `smolagents` フレームワークを使用しています。Wayne 家 🦇 が不在の間、Wayne Manor でパーティーを準備する Alfred と一緒に、このフレームワークの主要な概念を探っていきましょう。Alfred にはやることがたくさんあります。彼がどのように `smolagents` を使ってこれらのタスクをこなしていくのか、その旅路をご覧ください！

> [!TIP]
> このユニットでは、`smolagents` ライブラリを使った AI エージェントの構築方法を学びます。構築するエージェントは、データの検索、コードの実行、ウェブページとのインタラクションが可能です。また、複数のエージェントを組み合わせてより強力なシステムを作る方法も学びます。

![エージェントの Alfred](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/this-is-alfred.jpg)

## コンテンツ

この `smolagents` ユニットでは、以下の内容をカバーします：

### 1️⃣ [なぜ smolagents を使うのか](./why_use_smolagents)

`smolagents` は、アプリケーション開発に利用できる多くのオープンソースエージェントフレームワークの一つです。代替として `LlamaIndex` や `LangGraph` があり、これらは本コースの他のモジュールでも取り上げています。`smolagents` には特定のユースケースに最適となりうるいくつかの主要な特徴がありますが、フレームワーク選定時には常にすべての選択肢を検討すべきです。`smolagents` を使用するメリットとデメリットを探り、プロジェクトの要件に基づいて適切な判断ができるようにします。

### 2️⃣ [CodeAgents](./code_agents)

`CodeAgents` は `smolagents` における主要なエージェントタイプです。JSON やテキストを生成する代わりに、これらのエージェントはアクションを実行するための Python コードを生成します。このモジュールでは、その目的、機能、動作の仕組みを、実践的な例を交えて紹介します。

### 3️⃣ [ToolCallingAgents](./tool_calling_agents)

`ToolCallingAgents` は `smolagents` がサポートする第二のエージェントタイプです。Python コードを生成する `CodeAgents` とは異なり、これらのエージェントはシステムがパースして解釈し実行する JSON/テキストブロブに依存します。このモジュールでは、その機能、`CodeAgents` との主な違いを解説し、使い方を示す例を提供します。

### 4️⃣ [Tools](./tools)

Unit 1 で見たように、Tool はエージェントシステム内で LLM が使用できる関数であり、エージェントの振る舞いを構成する基本的なビルディングブロックです。このモジュールでは、Tool の作成方法、構造、`Tool` クラスや `@tool` デコレータを使ったさまざまな実装方法を取り上げます。また、デフォルトのツールボックス、コミュニティとの Tool 共有方法、コミュニティが提供する Tool をエージェントで読み込んで使用する方法についても学びます。

### 5️⃣ [Retrieval Agents](./retrieval_agents)

Retrieval Agent は、モデルがナレッジベースにアクセスし、複数のソースから情報を検索、統合、取得することを可能にします。効率的な検索のためにベクトルストアを活用し、**RAG（Retrieval-Augmented Generation）** パターンを実装します。これらのエージェントは、メモリシステムを通じて会話のコンテキストを維持しながら、ウェブ検索とカスタムナレッジベースを統合する際に特に有用です。このモジュールでは、堅牢な情報検索のためのフォールバックメカニズムを含む実装戦略を探ります。

### 6️⃣ [マルチエージェントシステム](./multi_agent_systems)

複数のエージェントを効果的にオーケストレーションすることは、強力なマルチエージェントシステムを構築するために不可欠です。ウェブ検索エージェントとコード実行エージェントなど、異なる能力を持つエージェントを組み合わせることで、より高度なソリューションを作成できます。このモジュールでは、効率性と信頼性を最大化するためのマルチエージェントシステムの設計、実装、管理に焦点を当てます。

### 7️⃣ [ビジョンエージェントとブラウザエージェント](./vision_agents)

ビジョンエージェントは、**VLM（Vision-Language Models）** を組み込むことで従来のエージェント機能を拡張し、視覚情報の処理と解釈を可能にします。このモジュールでは、VLM を活用したエージェントの設計と統合方法を探り、画像ベースの推論、視覚データ分析、マルチモーダルインタラクションなどの高度な機能を実現します。また、ビジョンエージェントを使ってウェブをブラウズし情報を抽出するブラウザエージェントも構築します。

## リソース

- [smolagents ドキュメント](https://huggingface.co/docs/smolagents) - smolagents ライブラリの公式ドキュメント
- [Building Effective Agents](https://www.anthropic.com/research/building-effective-agents) - エージェントアーキテクチャに関する研究論文
- [Agent Guidelines](https://huggingface.co/docs/smolagents/tutorials/building_good_agents) - 信頼性の高いエージェント構築のベストプラクティス
- [LangGraph Agents](https://langchain-ai.github.io/langgraph/) - エージェント実装の追加例
- [Function Calling Guide](https://platform.openai.com/docs/guides/function-calling) - LLM における Function Calling の理解
- [RAG Best Practices](https://www.pinecone.io/learn/retrieval-augmented-generation/) - 効果的な RAG 実装ガイド

---

<!-- nav -->

[⬅️ 前へ: フレームワーク入門](../introduction.md) | [📚 目次](../../README.md) | [次へ: smolagents を使う理由 ➡️](why_use_smolagents.md)
