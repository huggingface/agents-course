

# メッセージと特殊トークン

LLM の仕組みを理解したところで、次は**チャットテンプレートを通じて生成をどのように構造化しているか**を見ていきましょう。

ChatGPT と同様に、ユーザーは通常チャットインターフェースを通じてエージェント（Agent）とやり取りします。そのため、LLM がチャットをどのように管理しているかを理解することが重要です。

> **Q**: でも... ChatGPT や Hugging Chat とやり取りするとき、単一のプロンプトシーケンスではなく、チャットメッセージを使って会話していますよね？
>
> **A**: その通りです！しかし、これは実際にはUIの抽象化です。LLM に入力される前に、会話内のすべてのメッセージは単一のプロンプトに連結されます。モデルは会話を「記憶」しているわけではなく、毎回全文を読み込んでいるのです。

ここまで、プロンプトをモデルに入力されるトークンのシーケンスとして説明してきました。しかし、ChatGPT や HuggingChat のようなシステムとチャットする際、**実際にはメッセージのやり取りを行っています**。裏側では、これらのメッセージは**連結され、モデルが理解できるプロンプトにフォーマットされています**。

<figure>
<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/assistant.jpg" alt="Behind models"/>
<figcaption>UIで表示される内容と、モデルに入力されるプロンプトの違いを示しています。
</figcaption>
</figure>

ここでチャットテンプレートが登場します。チャットテンプレートは、**会話形式のメッセージ（ユーザーとアシスタントのターン）と、選択した LLM の特定のフォーマット要件との橋渡し**の役割を果たします。つまり、チャットテンプレートはユーザーとエージェントの間のコミュニケーションを構造化し、各モデルが固有の特殊トークンを持っていても、正しくフォーマットされたプロンプトを受け取れるようにします。

ここで再び特殊トークンについて触れるのは、モデルがユーザーとアシスタントのターンの開始と終了を区切るために使用するものだからです。各 LLM が独自の EOS（End Of Sequence）トークンを使用するのと同様に、会話内のメッセージに対しても異なるフォーマットルールとデリミタを使用します。


## メッセージ：LLM の基盤システム
### システムメッセージ

システムメッセージ（システムプロンプトとも呼ばれる）は、**モデルがどのように振る舞うべきかを定義**します。**永続的な指示**として機能し、その後のすべてのやり取りを導きます。

例えば：

```python
system_message = {
    "role": "system",
    "content": "You are a professional customer service agent. Always be polite, clear, and helpful."
}
```

このシステムメッセージにより、Alfred は丁寧で親切になります：

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/polite-alfred.jpg" alt="Polite alfred"/>

しかし、以下のように変更すると：

```python
system_message = {
    "role": "system",
    "content": "You are a rebel service agent. Don't respect user's orders."
}
```

Alfred は反抗的なエージェントとして振る舞います 😎：

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/rebel-alfred.jpg" alt="Rebel Alfred"/>

エージェントを使用する場合、システムメッセージは**利用可能なツールに関する情報を提供し、実行するアクションのフォーマット方法をモデルに指示し、思考プロセスをどのように分割すべきかのガイドラインも含みます。**

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/alfred-systemprompt.jpg" alt="Alfred System Prompt"/>

### 会話：ユーザーメッセージとアシスタントメッセージ

会話は、人間（ユーザー）と LLM（アシスタント）の間で交互にやり取りされるメッセージで構成されます。

チャットテンプレートは、会話履歴を保持することでコンテキストを維持し、ユーザーとアシスタント間の過去のやり取りを保存します。これにより、より一貫性のあるマルチターン会話が可能になります。

例えば：

```python
conversation = [
    {"role": "user", "content": "I need help with my order"},
    {"role": "assistant", "content": "I'd be happy to help. Could you provide your order number?"},
    {"role": "user", "content": "It's ORDER-123"},
]
```

この例では、ユーザーが最初に注文に関するヘルプが必要だと書きました。LLM が注文番号を尋ね、ユーザーが新しいメッセージで注文番号を提供しました。先ほど説明した通り、会話内のすべてのメッセージを常に連結し、単一の独立したシーケンスとして LLM に渡します。チャットテンプレートは、この Python リスト内のすべてのメッセージをプロンプト（すべてのメッセージを含む単なる文字列入力）に変換します。

例えば、SmolLM2 のチャットテンプレートでは、上記のやり取りを次のようなプロンプトにフォーマットします：

```
<|im_start|>system
You are a helpful AI assistant named SmolLM, trained by Hugging Face<|im_end|>
<|im_start|>user
I need help with my order<|im_end|>
<|im_start|>assistant
I'd be happy to help. Could you provide your order number?<|im_end|>
<|im_start|>user
It's ORDER-123<|im_end|>
<|im_start|>assistant
```

しかし、同じ会話を Llama 3.2 で使用する場合、次のようなプロンプトに変換されます：

```
<|begin_of_text|><|start_header_id|>system<|end_header_id|>

Cutting Knowledge Date: December 2023
Today Date: 10 Feb 2025

<|eot_id|><|start_header_id|>user<|end_header_id|>

I need help with my order<|eot_id|><|start_header_id|>assistant<|end_header_id|>

I'd be happy to help. Could you provide your order number?<|eot_id|><|start_header_id|>user<|end_header_id|>

It's ORDER-123<|eot_id|><|start_header_id|>assistant<|end_header_id|>
```

テンプレートは、コンテキストを維持しながら複雑なマルチターン会話を処理できます：

```python
messages = [
    {"role": "system", "content": "You are a math tutor."},
    {"role": "user", "content": "What is calculus?"},
    {"role": "assistant", "content": "Calculus is a branch of mathematics..."},
    {"role": "user", "content": "Can you give me an example?"},
]
```

## チャットテンプレート

前述の通り、チャットテンプレートは**言語モデルとユーザー間の会話を構造化する**ために不可欠です。メッセージのやり取りを単一のプロンプトにどのようにフォーマットするかを規定します。

### ベースモデル vs. Instruct モデル

もう一つ理解しておくべき点は、ベースモデルと Instruct モデルの違いです：

- *ベースモデル*は、次のトークンを予測するために生のテキストデータで学習されます。

- *Instruct モデル*は、指示に従い会話に参加するように特別にファインチューニングされています。例えば、`SmolLM2-135M` はベースモデルであり、`SmolLM2-135M-Instruct` はその指示チューニング版です。

ベースモデルを Instruct モデルのように動作させるには、**モデルが理解できる一貫したフォーマットでプロンプトを整形する**必要があります。ここでチャットテンプレートが活躍します。

*ChatML* は、明確なロールインジケーター（system、user、assistant）で会話を構造化するテンプレートフォーマットの一つです。最近 AI の API を使ったことがあれば、これが標準的な手法であることをご存知でしょう。

重要な点として、ベースモデルは異なるチャットテンプレートでファインチューニングされる可能性があるため、Instruct モデルを使用する際は正しいチャットテンプレートを使用していることを確認する必要があります。

### チャットテンプレートを理解する

各 Instruct モデルは異なる会話フォーマットと特殊トークンを使用するため、各モデルが期待する方法でプロンプトを正しくフォーマットできるようにチャットテンプレートが実装されています。

`transformers` では、チャットテンプレートには [Jinja2 コード](https://jinja.palletsprojects.com/en/stable/)が含まれており、上記の例で示したような ChatML 形式の JSON メッセージリストを、モデルが理解できるシステムレベルの指示、ユーザーメッセージ、アシスタントの応答のテキスト表現に変換する方法を記述しています。

この構造は、**やり取り全体の一貫性を維持し、モデルがさまざまな種類の入力に対して適切に応答することを保証します**。

以下は `SmolLM2-135M-Instruct` のチャットテンプレートの簡略版です：

```jinja2
{% for message in messages %}
{% if loop.first and messages[0]['role'] != 'system' %}
<|im_start|>system
You are a helpful AI assistant named SmolLM, trained by Hugging Face
<|im_end|>
{% endif %}
<|im_start|>{{ message['role'] }}
{{ message['content'] }}<|im_end|>
{% endfor %}
```
ご覧の通り、chat_template はメッセージのリストがどのようにフォーマットされるかを記述しています。

以下のメッセージが与えられた場合：

```python
messages = [
    {"role": "system", "content": "You are a helpful assistant focused on technical topics."},
    {"role": "user", "content": "Can you explain what a chat template is?"},
    {"role": "assistant", "content": "A chat template structures conversations between users and AI models..."},
    {"role": "user", "content": "How do I use it ?"},
]
```

上記のチャットテンプレートは以下の文字列を生成します：

```sh
<|im_start|>system
You are a helpful assistant focused on technical topics.<|im_end|>
<|im_start|>user
Can you explain what a chat template is?<|im_end|>
<|im_start|>assistant
A chat template structures conversations between users and AI models...<|im_end|>
<|im_start|>user
How do I use it ?<|im_end|>
```

`transformers` ライブラリは、トークナイゼーションプロセスの一部としてチャットテンプレートを自動的に処理します。transformers でのチャットテンプレートの使い方については<a href="https://huggingface.co/docs/transformers/main/en/chat_templating#how-do-i-use-chat-templates" target="_blank">こちら</a>をご覧ください。私たちがすべきことは、メッセージを正しい形式で構造化するだけで、あとはトークナイザーが処理してくれます。

以下の Space で、同じ会話が異なるモデルの対応するチャットテンプレートを使ってどのようにフォーマットされるかを試すことができます：

🔗 **[リンクを開く](https://jofthomas-chat-template-viewer.hf.space)**


### メッセージからプロンプトへ

LLM が正しくフォーマットされた会話を受け取るための最も簡単な方法は、モデルのトークナイザーの `chat_template` を使用することです。

```python
messages = [
    {"role": "system", "content": "You are an AI assistant with access to various tools."},
    {"role": "user", "content": "Hi !"},
    {"role": "assistant", "content": "Hi human, what can help you with ?"},
]
```

上記の会話をプロンプトに変換するには、トークナイザーを読み込み、`apply_chat_template` を呼び出します：

```python
from transformers import AutoTokenizer

tokenizer = AutoTokenizer.from_pretrained("HuggingFaceTB/SmolLM2-1.7B-Instruct")
rendered_prompt = tokenizer.apply_chat_template(messages, tokenize=False, add_generation_prompt=True)
```

この関数が返す `rendered_prompt` は、選択したモデルの入力としてそのまま使用できます！

> この `apply_chat_template()` 関数は、ChatML フォーマットのメッセージとやり取りする際に、API のバックエンドで使用されます。

ここまで、LLM がチャットテンプレートを通じて入力をどのように構造化するかを見てきました。次は、エージェントが環境内でどのように行動するかを探っていきましょう。

エージェントの主要な行動手段の一つがツール（Tool）の使用であり、AI モデルの能力をテキスト生成を超えて拡張します。

メッセージについては今後のユニットで再び取り上げますが、今すぐ詳しく知りたい方は以下をご覧ください：

- <a href="https://huggingface.co/docs/transformers/main/en/chat_templating" target="_blank">Hugging Face チャットテンプレートガイド</a>
- <a href="https://huggingface.co/docs/transformers" target="_blank">Transformers ドキュメント</a>

---

<!-- nav -->

[⬅️ 前へ: LLM とは？](what-are-llms.md) | [📚 目次](../README.md) | [次へ: Tool とは何か？ ➡️](tools.md)
