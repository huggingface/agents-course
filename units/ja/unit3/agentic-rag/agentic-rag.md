

---
# エージェント型 RAG（Agentic Retrieval Augmented Generation）

このユニットでは、エージェント型 RAG（Agentic RAG）を使って、Alfred が素晴らしいガラパーティーの準備をする方法を見ていきます。

> [!TIP]
> 前のユニットで RAG（Retrieval Augmented Generation）とエージェント型 RAG についてはすでに説明していますので、概念をご存知の方は先に進んでいただいて構いません。

LLM は膨大なデータで学習され、一般的な知識を習得しています。
しかし、LLM が持つ世界知識は、必ずしも関連性が高く最新の情報とは限りません。
**RAG は、あなたのデータから関連情報を検索・取得し、それを LLM に渡すことでこの問題を解決します。**

![RAG](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/llama-index/rag.png)

では、Alfred の仕事の流れを考えてみましょう：

1. Alfred にガラパーティーの企画を手伝うよう依頼しました
2. Alfred は最新のニュースや天気情報を調べる必要があります
3. Alfred はゲスト情報を整理・検索する必要があります

Alfred が家庭内の情報を検索して役に立つのと同じように、あらゆるエージェントには関連データを見つけて理解する方法が必要です。
**エージェント型 RAG は、エージェントを使ってデータに関する質問に答えるための強力な手法です。** Alfred にさまざまなツールを渡して、質問への回答を手助けすることができます。
ただし、ドキュメントに基づいて自動的に回答するのではなく、Alfred は他の任意のツールやフローを使って質問に答えるかどうかを自ら判断できます。

![Agentic RAG](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/llama-index/agentic-rag.png)

それでは、**エージェント型 RAG ワークフローの構築を始めましょう！**

まず、招待客の最新情報を取得するための RAG ツールを作成します。次に、Web 検索、天気情報の取得、Hugging Face Hub のモデルダウンロード統計のためのツールを開発します。最後に、すべてを統合してエージェント型 RAG エージェントを完成させます！

---

<!-- nav -->

[⬅️ 前へ: Agentic RAG 入門](introduction.md) | [📚 目次](../../README.md) | [次へ: エージェント用ツール ➡️](tools.md)
