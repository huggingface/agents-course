# LlamaHub の紹介

**LlamaHub は、LlamaIndex 内で使用できる数百ものインテグレーション、Agent、ツールのレジストリです。**

![LlamaHub](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/llama-index/llama-hub.png)

このコースではさまざまなインテグレーションを使用しますので、まず LlamaHub の概要と、それがどのように役立つかを見ていきましょう。

必要なコンポーネントの依存関係を見つけてインストールする方法を確認しましょう。

## インストール

LlamaIndex のインストール手順は、**[LlamaHub](https://llamahub.ai/) に体系的にまとめられた概要**として公開されています。
最初は少し圧倒されるかもしれませんが、**インストールコマンドはほとんどの場合、覚えやすいフォーマット**に従っています：

```bash
pip install llama-index-{component-type}-{framework-name}
```

[Hugging Face Inference API インテグレーション](https://llamahub.ai/l/llms/llama-index-llms-huggingface-api?from=llms)を使って、LLM と Embedding コンポーネントの依存関係をインストールしてみましょう。

```bash
pip install llama-index-llms-huggingface-api llama-index-embeddings-huggingface
```

## 使い方

インストールが完了したら、使用パターンを確認しましょう。インポートパスがインストールコマンドと対応していることに気づくでしょう！
以下に、**LLM コンポーネントとしての Hugging Face Inference API の使用例**を示します。

```python
from llama_index.llms.huggingface_api import HuggingFaceInferenceAPI
import os
from dotenv import load_dotenv

# .envファイルを読み込む
load_dotenv()

# 環境変数からHF_TOKENを取得する
hf_token = os.getenv("HF_TOKEN")

llm = HuggingFaceInferenceAPI(
    model_name="Qwen/Qwen2.5-Coder-32B-Instruct",
    temperature=0.7,
    max_tokens=100,
    token=hf_token,
    provider="auto"
)

response = llm.complete("Hello, how are you?")
print(response)
# I am good, how can I help you today?
```

これで、必要なコンポーネントのインテグレーションを見つけ、インストールし、使用する方法がわかりました。
**コンポーネントについてさらに深く掘り下げて**、独自の Agent を構築するためにどのように活用できるかを見ていきましょう。

---

<!-- nav -->

[⬅️ 前へ: LlamaIndex: ワークフロー](workflows.md) | [📚 目次](../../README.md) | [次へ: LlamaIndex: 小テスト 2 ➡️](quiz2.md)
