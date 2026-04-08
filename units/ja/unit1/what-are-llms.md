

---
# LLM とは？

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/whiteboard-check-1.jpg" alt="Unit 1 planning"/>

前のセクションでは、各エージェント（Agent）のコアに**AIモデルが必要**であり、LLM がその目的で最も一般的に使われるAIモデルであることを学びました。

ここでは、LLM とは何か、そしてどのようにエージェントを動かしているのかを学びます。

このセクションでは、LLM の利用に関する簡潔な技術的説明を提供します。より深く学びたい場合は、<a href="https://huggingface.co/learn/nlp-course/chapter1/1" target="_blank">無料の自然言語処理コース</a>をご覧ください。

## 大規模言語モデル（LLM）とは？

LLM は、**人間の言語の理解と生成**に優れたAIモデルの一種です。膨大なテキストデータで学習されており、言語のパターン、構造、さらにはニュアンスまで学習しています。これらのモデルは通常、数百万のパラメータで構成されています。

現在のほとんどの LLM は **Transformer アーキテクチャ上に構築されています**。これは「Attention」アルゴリズムに基づくディープラーニングアーキテクチャで、2018年の Google による BERT のリリース以来、大きな注目を集めています。

<figure>
<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/transformer.jpg" alt="Transformer"/>
<figcaption>オリジナルの Transformer アーキテクチャは、左にエンコーダ、右にデコーダという構造でした。
</figcaption>
</figure>

Transformer には3つのタイプがあります：

1. **エンコーダ（Encoders）**  
   エンコーダベースの Transformer は、テキスト（または他のデータ）を入力として受け取り、そのテキストの密な表現（エンベディング）を出力します。

   - **例**: Google の BERT
   - **ユースケース**: テキスト分類、セマンティック検索、固有表現認識
   - **一般的なサイズ**: 数百万パラメータ

2. **デコーダ（Decoders）**  
   デコーダベースの Transformer は、**一度に1トークンずつ、シーケンスを完成させる新しいトークンの生成**に特化しています。

   - **例**: Meta の Llama
   - **ユースケース**: テキスト生成、チャットボット、コード生成
   - **一般的なサイズ**: 数十億（10^9）パラメータ

3. **Seq2Seq（エンコーダ・デコーダ）**  
   Sequence-to-Sequence の Transformer は、エンコーダとデコーダを_組み合わせた_ものです。エンコーダがまず入力シーケンスをコンテキスト表現に変換し、その後デコーダが出力シーケンスを生成します。

   - **例**: T5、BART
   - **ユースケース**: 翻訳、要約、言い換え
   - **一般的なサイズ**: 数百万パラメータ

大規模言語モデルにはさまざまな形態がありますが、LLM は通常、数十億のパラメータを持つデコーダベースのモデルです。以下は代表的な LLM です：

| **モデル**                          | **プロバイダー**                              |
|-----------------------------------|-------------------------------------------|
| **Deepseek-R1**                    | DeepSeek                                  |
| **GPT4**                           | OpenAI                                    |
| **Llama 3**                        | Meta (Facebook AI Research)               |
| **SmolLM2**                       | Hugging Face     |
| **Gemma**                          | Google                                    |
| **Mistral**                        | Mistral                                |

LLM の基本原理はシンプルでありながら非常に効果的です。**その目的は、前のトークンのシーケンスが与えられたとき、次のトークンを予測すること**です。「トークン」とは、LLM が扱う情報の単位です。トークンは「単語」のようなものと考えることができますが、効率上の理由から、LLM は単語全体を使用しません。

例えば、英語には推定60万語ありますが、LLM の語彙は約32,000トークン程度です（Llama 2 の場合）。トークン化は通常、組み合わせ可能なサブワード単位で動作します。

例えば、「interest」と「ing」というトークンを組み合わせて「interesting」を作ったり、「ed」を付加して「interested」を作ることができます。

以下のインタラクティブプレイグラウンドで、さまざまなトークナイザーを試すことができます：

🔗 **[リンクを開く](https://agents-course-the-tokenizer-playground.static.hf.space)**

各 LLM には、モデル固有の**特殊トークン**があります。LLM はこれらのトークンを使用して、生成の構造化されたコンポーネントの開始と終了を示します。例えば、シーケンス、メッセージ、または応答の開始や終了を示すために使われます。また、モデルに渡す入力プロンプトも特殊トークンで構造化されます。その中で最も重要なのが**シーケンス終了トークン**（EOS: End of Sequence）です。

特殊トークンの形式は、モデルプロバイダーによって大きく異なります。

以下の表は、特殊トークンの多様性を示しています。

<table>
  <thead>
    <tr>
      <th><strong>モデル</strong></th>
      <th><strong>プロバイダー</strong></th>
      <th><strong>EOS トークン</strong></th>
      <th><strong>機能</strong></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>GPT4</strong></td>
      <td>OpenAI</td>
      <td><code>&lt;|endoftext|&gt;</code></td>
      <td>メッセージテキストの終了</td>
    </tr>
    <tr>
      <td><strong>Llama 3</strong></td>
      <td>Meta (Facebook AI Research)</td>
      <td><code>&lt;|eot_id|&gt;</code></td>
      <td>シーケンスの終了</td>
    </tr>
    <tr>
      <td><strong>Deepseek-R1</strong></td>
      <td>DeepSeek</td>
      <td><code>&lt;|end_of_sentence|&gt;</code></td>
      <td>メッセージテキストの終了</td>
    </tr>
    <tr>
      <td><strong>SmolLM2</strong></td>
      <td>Hugging Face</td>
      <td><code>&lt;|im_end|&gt;</code></td>
      <td>指示またはメッセージの終了</td>
    </tr>
    <tr>
      <td><strong>Gemma</strong></td>
      <td>Google</td>
      <td><code>&lt;end_of_turn&gt;</code></td>
      <td>会話ターンの終了</td>
    </tr>
  </tbody>
</table>

> [!TIP]
> これらの特殊トークンを暗記する必要はありませんが、その多様性と LLM のテキスト生成における役割を理解することが重要です。特殊トークンについてさらに知りたい場合は、Hub リポジトリでモデルの設定を確認できます。例えば、SmolLM2 モデルの特殊トークンは <a href="https://huggingface.co/HuggingFaceTB/SmolLM2-135M-Instruct/blob/main/tokenizer_config.json">tokenizer_config.json</a> で確認できます。

## 次トークン予測を理解する

LLM は**自己回帰的（autoregressive）**であると言われます。これは、**1回のパスの出力が次のパスの入力になる**ことを意味します。このループは、モデルが次のトークンとして EOS トークンを予測するまで続き、その時点でモデルは停止できます。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/AutoregressionSchema.gif" alt="自己回帰デコーディングの視覚的GIF" width="60%">

言い換えると、LLM は EOS に到達するまでテキストをデコードします。では、1回のデコーディングループでは何が起きているのでしょうか？

エージェントを学ぶ目的においては完全なプロセスはかなり技術的になりますが、概要を簡単に説明します：

- 入力テキストが**トークン化**されると、モデルは入力シーケンス内の各トークンの意味と位置に関する情報を捉えた表現を計算します。
- この表現がモデルに入力され、モデルは語彙内の各トークンがシーケンスの次のトークンとなる可能性を順位付けするスコアを出力します。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/DecodingFinal.gif" alt="デコーディングの視覚的GIF" width="60%">

これらのスコアに基づいて、文を完成させるトークンを選択するための複数の戦略があります。

- 最も簡単なデコーディング戦略は、常に最大スコアのトークンを選択することです。

以下の Space で SmolLM2 のデコーディングプロセスを実際に試すことができます（このモデルでは **EOS** トークンは **<|im_end|>** であることを覚えておいてください）：

🔗 **[リンクを開く](https://agents-course-decoding-visualizer.hf.space)**

- さらに高度なデコーディング戦略もあります。例えば、*ビームサーチ*は複数の候補シーケンスを探索し、個々のトークンのスコアが低くても、合計スコアが最大となるシーケンスを見つけます。

🔗 **[リンクを開く](https://agents-course-beam-search-visualizer.hf.space)**

デコーディングについてさらに知りたい場合は、[NLP コース](https://huggingface.co/learn/nlp-course)をご覧ください。

## Attention こそすべて

Transformer アーキテクチャの重要な側面は **Attention** です。次の単語を予測する際、文中のすべての単語が同じ重要度を持つわけではありません。*「The capital of France is ...」*という文では、「France」と「capital」が最も重要な意味を持ちます。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/AttentionSceneFinal.gif" alt="Attentionの視覚的GIF" width="60%">
次のトークンを予測するために最も関連性の高い単語を特定するこのプロセスは、非常に効果的であることが証明されています。

LLM の基本原理—次のトークンを予測すること—は GPT-2 以来一貫していますが、ニューラルネットワークのスケーリングと、より長いシーケンスに対して Attention メカニズムを機能させることにおいて、大きな進歩がありました。

LLM を使ったことがあれば、*コンテキスト長*という用語をご存知でしょう。これは LLM が処理できるトークンの最大数、つまり最大の _Attention スパン_ を指します。

## LLM へのプロンプティングは重要

LLM の唯一の仕事は、すべての入力トークンを見て、どのトークンが「重要」かを選びながら次のトークンを予測することです。そのため、入力シーケンスの表現は非常に重要です。

LLM に与える入力シーケンスは_プロンプト_と呼ばれます。プロンプトを慎重に設計することで、**LLM の生成を望ましい出力に導く**ことが容易になります。

## LLM はどのように学習されるのか？

LLM は大規模なテキストデータセットで学習され、自己教師あり学習またはマスク言語モデリングの目的関数を通じて、シーケンス内の次の単語を予測することを学びます。

この教師なし学習から、モデルは言語の構造と**テキストの根底にあるパターンを学習し、未知のデータへの汎化**を可能にします。

この最初の_事前学習_の後、LLM は教師あり学習の目的関数でファインチューニングし、特定のタスクを実行できるようになります。例えば、会話構造やツール利用のために学習されるモデルもあれば、分類やコード生成に特化するモデルもあります。

## LLM をどのように使えるのか？

主に2つの選択肢があります：

1. **ローカルで実行する**（十分なハードウェアがある場合）。

2. **クラウド/API を使用する**（例：Hugging Face Serverless Inference API 経由）。

このコースでは、主に Hugging Face Hub 上の API 経由でモデルを使用します。後のセクションでは、お手持ちのハードウェアでこれらのモデルをローカル実行する方法も探ります。


## AI エージェントにおいて LLM はどのように使われるのか？

LLM は AI エージェントの重要なコンポーネントであり、**人間の言語を理解し生成するための基盤**を提供します。

ユーザーの指示を解釈し、会話のコンテキストを維持し、計画を定義し、使用するツールを決定することができます。

これらのステップについては、このユニットでより詳しく探りますが、今のところ理解すべきことは、LLM が**エージェントの頭脳**であるということです。

---

たくさんの情報がありましたね！LLM とは何か、どのように機能するか、そして AI エージェントを動かす上での役割について基礎を学びました。

言語モデルと自然言語処理のさらに深い世界に飛び込みたい方は、<a href="https://huggingface.co/learn/nlp-course/chapter1/1" target="_blank">無料の NLP コース</a>をぜひご覧ください。

LLM の仕組みを理解したところで、次は**LLM が会話のコンテキストでどのように生成を構造化するか**を見ていきましょう。

<a href="https://huggingface.co/agents-course/notebooks/blob/main/unit1/dummy_agent_library.ipynb" target="_blank">このノートブック</a>を実行するには、<a href="https://hf.co/settings/tokens" target="_blank">https://hf.co/settings/tokens</a> から取得できる **Hugging Face トークンが必要**です。

Jupyter Notebook の実行方法の詳細については、<a href="https://huggingface.co/docs/hub/notebooks">Hugging Face Hub の Jupyter Notebooks</a> をご覧ください。

また、<a href="https://huggingface.co/meta-llama/Llama-3.2-3B-Instruct" target="_blank">Meta Llama モデル</a>へのアクセスをリクエストする必要があります。

---

<!-- nav -->

[⬅️ 前へ: 小テスト 1](quiz1.md) | [📚 目次](../README.md) | [次へ: メッセージと特殊トークン ➡️](messages-and-special-tokens.md)
