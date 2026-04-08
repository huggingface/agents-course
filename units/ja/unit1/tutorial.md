

---
# smolagents を使って最初のエージェントを作ろう

前のセクションでは、Python コードを使ってゼロからエージェント（Agent）を作成する方法を学び、**そのプロセスがいかに手間のかかるものであるかを実感しました**。幸いなことに、多くのエージェントライブラリが**面倒な作業の大部分を肩代わりしてくれる**ため、この作業を大幅に簡素化できます。

このチュートリアルでは、画像生成、Web 検索、タイムゾーンの確認など、さまざまなアクションを実行できる**最初のエージェントを作成します**！

また、作成したエージェントを **Hugging Face Space に公開して、友人や同僚と共有する**こともできます。

さっそく始めましょう！


## smolagents とは？

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/smolagents.png" alt="smolagents"/>

このエージェントを作成するために、`smolagents` というライブラリを使用します。これは**エージェントを簡単に開発するためのフレームワークを提供する**ライブラリです。

この軽量ライブラリはシンプルさを重視して設計されていますが、エージェント構築の複雑さの多くを抽象化してくれるため、エージェントの動作設計に集中できます。

smolagents については次のユニットでさらに深く掘り下げます。それまでの間、こちらの<a href="https://huggingface.co/blog/smolagents" target="_blank">ブログ記事</a>やライブラリの <a href="https://github.com/huggingface/smolagents" target="_blank">GitHub リポジトリ</a>もぜひご覧ください。

簡単に言うと、`smolagents` は **CodeAgent** に焦点を当てたライブラリです。CodeAgent とは、コードブロックを通じて**「アクション（Actions）」**を実行し、そのコードを実行することで結果を**「観察（Observes）」**するエージェントです。

これから作るもののサンプルをご覧ください！

エージェントに**画像生成ツール**を与え、猫の画像を生成するよう依頼しました。

`smolagents` 内部のエージェントは、**先ほど自作したカスタムエージェントと同じ動作**をします。**最終的な回答に到達するまで、思考・行動・観察のサイクルを繰り返します**：

[![動画を視聴](https://img.youtube.com/vi/PQDKcWiuln4/maxresdefault.jpg)](https://www.youtube.com/watch?v=PQDKcWiuln4)

▶ **[動画を視聴](https://www.youtube.com/watch?v=PQDKcWiuln4)**

ワクワクしませんか？

## エージェントを構築しよう！

まず、この Space を複製してください：<a href="https://huggingface.co/spaces/agents-course/First_agent_template" target="_blank">https://huggingface.co/spaces/agents-course/First_agent_template</a>
> このテンプレートを作成してくれた <a href="https://huggingface.co/m-ric" target="_blank">Aymeric</a> に感謝します！🙌


Space を複製するとは、**自分のプロフィールにローカルコピーを作成する**ということです：
<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/duplicate-space.gif" alt="Duplicate"/>

Space を複製したら、エージェントがモデル API にアクセスできるように Hugging Face API トークンを追加する必要があります：

1. まず、推論（inference）の権限を持つ Hugging Face トークンを [https://hf.co/settings/tokens](https://hf.co/settings/tokens) から取得してください（まだお持ちでない場合）
2. 複製した Space に移動し、**Settings** タブをクリックします
3. **Variables and Secrets** セクションまでスクロールし、**New Secret** をクリックします
4. 名前を `HF_TOKEN` としてシークレットを作成し、トークンの値を貼り付けます
5. **Save** をクリックしてトークンを安全に保存します

このレッスンを通じて、変更が必要なファイルは（現在未完成の）**「app.py」**のみです。テンプレートの[オリジナルはこちら](https://huggingface.co/spaces/agents-course/First_agent_template/blob/main/app.py)で確認できます。自分のコピーを見つけるには、Space のコピーに移動し、`Files` タブをクリックしてからディレクトリ一覧の `app.py` をクリックしてください。

コードを一緒に見ていきましょう：

- ファイルはシンプルですが必要なライブラリのインポートから始まります

```python
from smolagents import CodeAgent, DuckDuckGoSearchTool, FinalAnswerTool, InferenceClientModel, load_tool, tool
import datetime
import requests
import pytz
import yaml
```

先述の通り、**smolagents** の **CodeAgent** クラスを直接使用します。


### ツール（Tools）

次はツールについてです！ツールについて復習したい場合は、コースの [Tools](tools) セクションに戻ってご確認ください。

```python
@tool
def my_custom_tool(arg1:str, arg2:int)-> str: # 戻り値の型を指定することが重要です
    # ツールの説明 / 引数の説明はこのフォーマットを維持してください。ツール自体は自由に変更できます
    """A tool that does nothing yet 
    Args:
        arg1: the first argument
        arg2: the second argument
    """
    return "What magic will you build ?"

@tool
def get_current_time_in_timezone(timezone: str) -> str:
    """A tool that fetches the current local time in a specified timezone.
    Args:
        timezone: A string representing a valid timezone (e.g., 'America/New_York').
    """
    try:
        # タイムゾーンオブジェクトを作成
        tz = pytz.timezone(timezone)
        # そのタイムゾーンの現在時刻を取得
        local_time = datetime.datetime.now(tz).strftime("%Y-%m-%d %H:%M:%S")
        return f"The current local time in {timezone} is: {local_time}"
    except Exception as e:
        return f"Error fetching time for timezone '{timezone}': {str(e)}"
```


このセクションで皆さんに作っていただきたいのがツールです！ここでは2つの例を用意しました：

1. **動作しないダミーツール** — これを変更して何か便利なものを作ってみてください。
2. **実際に動作するツール** — 世界のどこかの現在時刻を取得します。

ツールを定義する際に重要なのは：

1. `get_current_time_in_timezone(timezone: str) -> str:` のように、関数の入力型と出力型を指定すること
2. **適切にフォーマットされた docstring** を記述すること。`smolagents` はすべての引数に **docstring 内のテキスト説明**があることを期待しています。

### エージェント（Agent）

LLM エンジンとして [`Qwen/Qwen2.5-Coder-32B-Instruct`](https://huggingface.co/Qwen/Qwen2.5-Coder-32B-Instruct) を使用します。これは非常に優秀なモデルで、サーバーレス API を通じてアクセスします。

```python
final_answer = FinalAnswerTool()
model = InferenceClientModel(
    max_tokens=2096,
    temperature=0.5,
    model_id='Qwen/Qwen2.5-Coder-32B-Instruct',
    custom_role_conversions=None,
)

with open("prompts.yaml", 'r') as stream:
    prompt_templates = yaml.safe_load(stream)
    
# CodeAgent を作成
agent = CodeAgent(
    model=model,
    tools=[final_answer], # ここにツールを追加してください（final_answer は削除しないでください）
    max_steps=6,
    verbosity_level=1,
    grammar=None,
    planning_interval=None,
    name=None,
    description=None,
    prompt_templates=prompt_templates
)

GradioUI(agent).launch()
```

このエージェントは、以前のセクションで見た `InferenceClient` を **InferenceClientModel** クラスの内部で使用しています！

フレームワークについてはユニット2でより詳細な例を紹介します。今の段階では、エージェントの `tools` パラメータを使って**ツールリストに新しいツールを追加する**ことに集中してください。

例えば、コードの最初の行でインポートされている `DuckDuckGoSearchTool` を使うこともできますし、コードの後半で Hub からロードされている `image_generation_tool` を調べてみることもできます。

**ツールを追加すると、エージェントに新しい能力が加わります**。ぜひ創造力を発揮してみてください！

### システムプロンプト

エージェントのシステムプロンプトは別の `prompts.yaml` ファイルに格納されています。このファイルには、エージェントの動作をガイドする事前定義された指示が含まれています。

プロンプトを YAML ファイルに格納することで、異なるエージェントやユースケース間で簡単にカスタマイズや再利用ができます。

`prompts.yaml` ファイルの場所とプロジェクト内での構成については、[Space のファイル構造](https://huggingface.co/spaces/agents-course/First_agent_template/tree/main)をご確認ください。

完成版の「app.py」：

```python
from smolagents import CodeAgent, DuckDuckGoSearchTool, InferenceClientModel, load_tool, tool
import datetime
import requests
import pytz
import yaml
from tools.final_answer import FinalAnswerTool

from Gradio_UI import GradioUI

# 以下は何もしないツールの例です。あなたの創造力で驚かせてください！
@tool
def my_custom_tool(arg1:str, arg2:int)-> str: # 戻り値の型を指定することが重要です
    # ツールの説明 / 引数の説明はこのフォーマットを維持してください。ツール自体は自由に変更できます
    """A tool that does nothing yet 
    Args:
        arg1: the first argument
        arg2: the second argument
    """
    return "What magic will you build ?"

@tool
def get_current_time_in_timezone(timezone: str) -> str:
    """A tool that fetches the current local time in a specified timezone.
    Args:
        timezone: A string representing a valid timezone (e.g., 'America/New_York').
    """
    try:
        # タイムゾーンオブジェクトを作成
        tz = pytz.timezone(timezone)
        # そのタイムゾーンの現在時刻を取得
        local_time = datetime.datetime.now(tz).strftime("%Y-%m-%d %H:%M:%S")
        return f"The current local time in {timezone} is: {local_time}"
    except Exception as e:
        return f"Error fetching time for timezone '{timezone}': {str(e)}"


final_answer = FinalAnswerTool()
model = InferenceClientModel(
    max_tokens=2096,
    temperature=0.5,
    model_id='Qwen/Qwen2.5-Coder-32B-Instruct',
    custom_role_conversions=None,
)


# Hub からツールをインポート
image_generation_tool = load_tool("agents-course/text-to-image", trust_remote_code=True)

# prompts.yaml ファイルからシステムプロンプトを読み込み
with open("prompts.yaml", 'r') as stream:
    prompt_templates = yaml.safe_load(stream)
    
agent = CodeAgent(
    model=model,
    tools=[final_answer], # ここにツールを追加してください（final_answer は削除しないでください）
    max_steps=6,
    verbosity_level=1,
    grammar=None,
    planning_interval=None,
    name=None,
    description=None,
    prompt_templates=prompt_templates # システムプロンプトを CodeAgent に渡す
)


GradioUI(agent).launch()
```

**目標**は、Space とエージェントに慣れることです。

現在、テンプレートのエージェントは**ツールを一切使用していないため、用意されているツールを追加したり、自分でオリジナルのツールを作成してみてください！**

皆さんの素晴らしいエージェントの成果を Discord チャンネル **#agents-course-showcase** でお待ちしています！


---
おめでとうございます、最初のエージェントが完成しました！ぜひ友人や同僚にシェアしてみてください。

初めての挑戦ですので、少しバグがあったり動作が遅かったりしても全く問題ありません。今後のユニットでは、さらに優れたエージェントの構築方法を学んでいきます。

学ぶ最良の方法は実際に試すことです。ぜひアップデートしたり、ツールを追加したり、別のモデルを試したりしてみてください。

次のセクションでは、最終クイズに回答して修了証を取得します！

---

<!-- nav -->

[⬅️ 前へ: ダミーエージェントライブラリ](dummy-agent-library.md) | [📚 目次](../README.md) | [次へ: Unit 1 クイズ ➡️](final-quiz.md)
