# Function Calling のためのモデルをファインチューニングしよう

いよいよ、Function Calling のための最初のモデルをファインチューニングする準備が整いました🔥。

## Function Calling のためにモデルをどう訓練するのか？

> 答え：**データ**が必要です

モデルの訓練プロセスは3つのステップに分けられます：

1. **モデルは大量のデータで事前学習されます**。このステップの出力が**事前学習済みモデル**です。例えば、[google/gemma-2-2b](https://huggingface.co/google/gemma-2-2b) がこれにあたります。これはベースモデルであり、**強力な指示追従能力を持たずに次のトークンを予測する方法**だけを知っています。

2. チャットの文脈で有用になるためには、モデルは指示に従うように**ファインチューニング**される必要があります。このステップでは、モデルの作成者、オープンソースコミュニティ、あなた自身、または誰でも訓練を行うことができます。例えば、[google/gemma-2-2b-it](https://huggingface.co/google/gemma-2-2b-it) は、Gemma プロジェクトを率いる Google チームによる指示チューニング済みモデルです。

3. その後、モデルは作成者の好みに**アライメント（整合）**されることがあります。例えば、顧客に対して決して無礼であってはならないカスタマーサービスのチャットモデルなどです。

通常、Gemini や Mistral のような完成されたプロダクトは**3つのステップすべてを経ます**が、Hugging Face で見つかるモデルは、この訓練の1つ以上のステップを完了しています。

このチュートリアルでは、[google/gemma-2-2b-it](https://huggingface.co/google/gemma-2-2b-it) をベースに Function Calling モデルを構築します。ベースモデルの [google/gemma-2-2b](https://huggingface.co/google/gemma-2-2b) ではなく、ファインチューニング済みモデルの [google/gemma-2-2b-it](https://huggingface.co/google/gemma-2-2b-it) を選択するのは、ファインチューニング済みモデルの方が私たちのユースケースに適した改善がなされているためです。

事前学習済みモデルから始めると、**指示追従、チャット、そして Function Calling を学習するために、より多くの訓練が必要になります**。

指示チューニング済みモデルから始めることで、**モデルが学習する必要のある情報量を最小限に抑えることができます**。

## LoRA（大規模言語モデルの低ランク適応）

LoRA は、訓練可能なパラメータ数を大幅に**削減する**、人気のある軽量な訓練手法です。

LoRA は、**モデルにアダプターとして少数の新しい重みを挿入して訓練する**ことで機能します。これにより、LoRA を用いた訓練ははるかに高速でメモリ効率が良く、より小さなモデルの重み（数百MB程度）を生成するため、保存や共有が容易になります。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/blog_multi-lora-serving_LoRA.gif" alt="LoRA inference" width="50%"/>

LoRA は、Transformer の層にランク分解行列のペアを追加することで機能し、通常は線形層に焦点を当てます。訓練中は、モデルの残りの部分を「凍結」し、新しく追加されたアダプターの重みのみを更新します。

これにより、アダプターの重みだけを更新すれば済むため、訓練に必要な**パラメータ**数が大幅に減少します。

推論時には、入力はアダプターとベースモデルの両方に渡されるか、またはこれらのアダプターの重みをベースモデルにマージすることができ、追加のレイテンシオーバーヘッドは発生しません。

LoRA は、リソース要件を管理可能な範囲に保ちながら、**大規模**言語モデルを特定のタスクやドメインに適応させるのに特に有用です。これにより、モデルの訓練に**必要な**メモリを削減できます。

LoRA の仕組みについてさらに詳しく学びたい場合は、こちらの[チュートリアル](https://huggingface.co/learn/nlp-course/chapter11/4?fw=pt)をご覧ください。

## Function Calling のためのモデルのファインチューニング

チュートリアルノートブックには👉 [こちら](https://huggingface.co/agents-course/notebooks/blob/main/bonus-unit1/bonus-unit1.ipynb)からアクセスできます。

次に、[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/#fileId=https://huggingface.co/agents-course/notebooks/blob/main/bonus-unit1/bonus-unit1.ipynb) をクリックして、Colab Notebook で実行してください。

---

<!-- nav -->

[⬅️ 前へ: Function Calling とは？](what-is-function-calling.md) | [📚 目次](../README.md) | [次へ: Bonus 1 まとめ ➡️](conclusion.md)
