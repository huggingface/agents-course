---
# Tool とは何か？

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/whiteboard-check-2.jpg" alt="Unit 1 planning"/>

AI Agent の重要な側面のひとつは、**アクション（行動）**を実行できることです。これまで見てきたように、これは **Tool** の使用を通じて実現されます。

このセクションでは、Tool とは何か、効果的な Tool の設計方法、そしてシステムメッセージを通じて Agent に Tool を統合する方法を学びます。

Agent に適切な Tool を与え、それらの Tool がどのように機能するかを明確に記述することで、AI が達成できることを劇的に拡大できます。さっそく見ていきましょう！


## AI Tool とは何か？

**Tool とは、LLM に与えられる関数**です。この関数は**明確な目的**を果たすものでなければなりません。

以下は、AI Agent でよく使用される Tool の例です：

| Tool            | 説明                                                   |
|----------------|---------------------------------------------------------------|
| Web Search     | Agent がインターネットから最新の情報を取得できるようにします。 |
| Image Generation | テキストの説明に基づいて画像を生成します。                  |
| Retrieval      | 外部ソースから情報を取得します。                |
| API Interface  | 外部 API（GitHub、YouTube、Spotify など）と連携します。 |

これらはあくまで例であり、実際にはあらゆるユースケースに対して Tool を作成できます！

優れた Tool とは、**LLM の能力を補完する**ものであるべきです。

例えば、算術演算を行う必要がある場合、LLM に**電卓ツール**を提供することで、モデルのネイティブな能力に頼るよりも良い結果が得られます。

さらに、**LLM は学習データに基づいてプロンプトの補完を予測する**ため、その内部知識には学習時点より前の出来事しか含まれていません。したがって、Agent が最新のデータを必要とする場合、何らかの Tool を通じてそのデータを提供する必要があります。

例えば、LLM に直接（検索ツールなしで）今日の天気を尋ねると、LLM はでたらめな天気をハルシネーション（幻覚）として生成する可能性があります。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/weather.jpg" alt="Weather"/>

- Tool には以下の要素が含まれるべきです：

  - 関数が何をするかの**テキストによる説明**。
  - *Callable*（アクションを実行するもの）。
  - 型付きの*引数*。
  - （オプション）型付きの*出力*。

## Tool はどのように機能するか？

これまで見てきたように、LLM はテキスト入力のみを受け取り、テキスト出力のみを生成できます。LLM 自体が Tool を呼び出す方法はありません。Agent に Tool を提供するというのは、LLM にこれらの Tool の存在を教え、必要に応じてテキストベースの呼び出しを生成するよう指示することを意味します。

例えば、インターネットからある場所の天気を確認する Tool を提供し、LLM にパリの天気について尋ねると、LLM はこれが「天気」ツールを使用する機会だと認識します。LLM は天気データを自ら取得するのではなく、`call weather_tool('Paris')` のような Tool 呼び出しを表すテキストを生成します。

**Agent** はこのレスポンスを読み取り、Tool 呼び出しが必要であることを識別し、LLM に代わって Tool を実行し、実際の天気データを取得します。

Tool 呼び出しのステップは通常ユーザーには表示されません。Agent はそれらを新しいメッセージとして追加し、更新された会話を再び LLM に渡します。LLM はこの追加のコンテキストを処理し、ユーザーに対して自然な応答を生成します。ユーザーの視点からは、LLM が直接 Tool とやり取りしたように見えますが、実際にはバックグラウンドで Agent が実行プロセス全体を処理しています。

このプロセスについては、今後のセッションでさらに詳しく説明します。

## LLM に Tool をどのように与えるか？

完全な回答は圧倒的に感じるかもしれませんが、基本的にはシステムプロンプトを使用して、利用可能な Tool のテキスト説明をモデルに提供します：

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/Agent_system_prompt.png" alt="System prompt for tools"/>

これが機能するためには、以下の点について非常に正確かつ的確でなければなりません：

1. **Tool が何をするか**
2. **どのような入力を正確に期待するか**

これが、Tool の説明がプログラミング言語や JSON のような表現力豊かで正確な構造を使って提供されることが多い理由です。必ずしもそうする_必要_はなく、正確で一貫したフォーマットであればどんなものでも機能します。

理論的すぎると感じたら、具体的な例を通じて理解しましょう。

2つの整数を掛け算するだけの簡略化された**電卓** Tool を実装します。Python での実装は以下のようになります：

```python
def calculator(a: int, b: int) -> int:
    """2つの整数を掛け算する。"""
    return a * b
```

この Tool は `calculator` と呼ばれ、**2つの整数を掛け算**し、以下の入力を必要とします：

- **`a`** (*int*): 整数。
- **`b`** (*int*): 整数。

Tool の出力は別の整数で、以下のように記述できます：
- (*int*): `a` と `b` の積。

これらの詳細はすべて重要です。LLM が理解できるように、Tool を説明するテキスト文字列にまとめましょう。

```text
Tool Name: calculator, Description: Multiply two integers., Arguments: a: int, b: int, Outputs: int
```

> **補足:** このテキスト説明は、*LLM に Tool について知ってほしいこと*です。

上記の文字列を LLM への入力の一部として渡すと、モデルはそれを Tool として認識し、入力として何を渡す必要があるか、出力から何を期待できるかを理解します。

追加の Tool を提供したい場合は、一貫性を保ち、常に同じフォーマットを使用する必要があります。このプロセスは脆弱になりがちで、うっかり詳細を見落としてしまうことがあります。

もっと良い方法はないでしょうか？

### Tool セクションの自動フォーマット

私たちの Tool は Python で書かれており、その実装には必要なものがすべて含まれています：

- 何をするかの説明的な名前：`calculator`
- 関数の docstring コメントによる詳しい説明：`Multiply two integers.`
- 入力とその型：関数は明確に2つの `int` を期待しています。
- 出力の型。

人々がプログラミング言語を使う理由があります。それは表現力があり、簡潔で、正確だからです。

Python のソースコードを LLM 向けの Tool の_仕様_として提供することもできますが、Tool がどのように実装されているかは重要ではありません。重要なのは、その名前、何をするか、期待する入力、提供する出力だけです。

Python のイントロスペクション機能を活用して、ソースコードから Tool の説明を自動的に構築します。必要なのは、Tool の実装が型ヒント、docstring、そして意味のある関数名を使用していることだけです。ソースコードから関連する部分を抽出するコードを書きます。

完成すれば、`calculator` 関数が Tool であることを示すために Python のデコレータを使うだけで済みます：

```python
@tool
def calculator(a: int, b: int) -> int:
    """2つの整数を掛け算する。"""
    return a * b

print(calculator.to_string())
```

関数定義の前にある `@tool` デコレータに注目してください。

次に見る実装により、`to_string()` 関数を使ってソースコードから以下のテキストを自動的に取得できるようになります：

```text
Tool Name: calculator, Description: Multiply two integers., Arguments: a: int, b: int, Outputs: int
```

ご覧のとおり、先ほど手動で書いたものとまったく同じです！

### 汎用 Tool の実装

再利用可能な汎用 `Tool` クラスを作成します。

> **注意:** この実装例は架空のものですが、ほとんどのライブラリの実際の実装に近いものです。

```python
from typing import Callable


class Tool:
    """
    再利用可能なコード（Tool）を表すクラス。

    属性:
        name (str): Tool の名前。
        description (str): Tool が何をするかのテキスト説明。
        func (callable): この Tool がラップする関数。
        arguments (list): 引数のリスト。
        outputs (str or list): ラップされた関数の戻り値の型。
    """
    def __init__(self,
                 name: str,
                 description: str,
                 func: Callable,
                 arguments: list,
                 outputs: str):
        self.name = name
        self.description = description
        self.func = func
        self.arguments = arguments
        self.outputs = outputs

    def to_string(self) -> str:
        """
        Tool の名前、説明、引数、出力を含む
        文字列表現を返す。
        """
        args_str = ", ".join([
            f"{arg_name}: {arg_type}" for arg_name, arg_type in self.arguments
        ])

        return (
            f"Tool Name: {self.name},"
            f" Description: {self.description},"
            f" Arguments: {args_str},"
            f" Outputs: {self.outputs}"
        )

    def __call__(self, *args, **kwargs):
        """
        提供された引数で基底の関数（callable）を呼び出す。
        """
        return self.func(*args, **kwargs)
```

複雑に見えるかもしれませんが、ゆっくり見ていけば何をしているか分かります。**`Tool`** クラスを定義しており、以下が含まれます：

- **`name`** (*str*): Tool の名前。
- **`description`** (*str*): Tool が何をするかの簡潔な説明。
- **`function`** (*callable*): Tool が実行する関数。
- **`arguments`** (*list*): 期待される入力パラメータ。
- **`outputs`** (*str* または *list*): Tool の期待される出力。
- **`__call__()`**: Tool インスタンスが呼び出されたときに関数を実行します。
- **`to_string()`**: Tool の属性をテキスト表現に変換します。

このクラスを使って、以下のようなコードで Tool を作成できます：

```python
calculator_tool = Tool(
    "calculator",                   # 名前
    "Multiply two integers.",       # 説明
    calculator,                     # 呼び出す関数
    [("a", "int"), ("b", "int")],   # 入力（名前と型）
    "int",                          # 出力
)
```

しかし、Python の `inspect` モジュールを使えば、すべての情報を自動的に取得できます！これが `@tool` デコレータの役割です。

> 興味がある方は、以下のセクションを展開してデコレータの実装を確認できます。

<details>
<summary> デコレータのコード</summary>

```python
import inspect

def tool(func):
    """
    指定された関数から Tool インスタンスを作成するデコレータ。
    """
    # 関数のシグネチャを取得
    signature = inspect.signature(func)

    # 入力の (パラメータ名, パラメータアノテーション) ペアを抽出
    arguments = []
    for param in signature.parameters.values():
        annotation_name = (
            param.annotation.__name__
            if hasattr(param.annotation, '__name__')
            else str(param.annotation)
        )
        arguments.append((param.name, annotation_name))

    # 戻り値のアノテーションを決定
    return_annotation = signature.return_annotation
    if return_annotation is inspect._empty:
        outputs = "No return annotation"
    else:
        outputs = (
            return_annotation.__name__
            if hasattr(return_annotation, '__name__')
            else str(return_annotation)
        )

    # 関数の docstring を説明として使用（None の場合はデフォルト値）
    description = func.__doc__ or "No description provided."

    # 関数名が Tool 名になる
    name = func.__name__

    # 新しい Tool インスタンスを返す
    return Tool(
        name=name,
        description=description,
        func=func,
        arguments=arguments,
        outputs=outputs
    )
```

</details>

改めて確認すると、このデコレータを使えば以下のように Tool を実装できます：

```python
@tool
def calculator(a: int, b: int) -> int:
    """2つの整数を掛け算する。"""
    return a * b

print(calculator.to_string())
```

そして、`Tool` の `to_string` メソッドを使って、LLM の Tool 説明として使用できるテキストを自動的に取得できます：

```text
Tool Name: calculator, Description: Multiply two integers., Arguments: a: int, b: int, Outputs: int
```

この説明はシステムプロンプトに**注入**されます。このセクションの冒頭の例を使うと、`tools_description` を置き換えた後は以下のようになります：

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/Agent_system_prompt_tools.png" alt="System prompt for tools"/>

[Actions](actions) セクションでは、Agent がここで作成した Tool をどのように**呼び出す**かについてさらに学びます。

### Model Context Protocol（MCP）：統一された Tool インターフェース

Model Context Protocol（MCP）は、アプリケーションが **LLM に Tool を提供する方法を標準化する**オープンプロトコルです。
MCP は以下を提供します：

- LLM が直接接続できる、増え続けるビルド済みインテグレーションのリスト
- LLM プロバイダーやベンダーを柔軟に切り替える機能
- インフラストラクチャ内でデータを保護するためのベストプラクティス

これは、**MCP を実装しているフレームワークであれば、プロトコル内で定義された Tool を活用できる**ことを意味し、フレームワークごとに同じ Tool インターフェースを再実装する必要がなくなります。

MCP についてさらに深く学びたい場合は、[無料の MCP コース](https://huggingface.co/learn/mcp-course/)をご覧ください。

---

Tool は AI Agent の能力を向上させる上で重要な役割を果たします。

まとめとして、以下を学びました：

- *Tool とは何か*：計算の実行や外部データへのアクセスなど、LLM に追加の能力を与える関数。

- *Tool の定義方法*：明確なテキスト説明、入力、出力、および callable な関数を提供すること。

- *Tool が不可欠な理由*：静的なモデル学習の限界を克服し、リアルタイムのタスクを処理し、専門的なアクションを実行できるようにすること。

次は [Agent のワークフロー](agent-steps-and-structure) に進みましょう。そこでは、Agent がどのように観察し、思考し、行動するかを見ていきます。これは**ここまで学んだすべてのことを統合**し、独自の完全に機能する AI Agent を作成するための基盤を築きます。

その前に、もうひとつ短いクイズの時間です！
---

---

<!-- nav -->

[⬅️ 前へ: メッセージと特殊トークン](messages-and-special-tokens.md) | [📚 目次](../README.md) | [次へ: 思考・行動・観察サイクル ➡️](agent-steps-and-structure.md)
