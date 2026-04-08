

# オンボーディング：最初のステップ ⛵

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit0/time-to-onboard.jpg" alt="Time to Onboard" width="100%"/>

すべての詳細を確認したところで、さっそく始めましょう！これから4つのことを行います：

1. **Hugging Faceアカウントの作成**（まだの場合）
2. **Discordに参加して自己紹介**（恥ずかしがらずに 🤗）
3. **Hugging Face Agents Course**をHubでフォロー
4. コースについて**広める**

### ステップ1：Hugging Faceアカウントを作成する

（まだの場合は）<a href='https://huggingface.co/join' target='_blank'>こちら</a>からHugging Faceアカウントを作成してください。

### ステップ2：Discordコミュニティに参加する

👉🏻 <a href="https://discord.gg/UrrTSsSyjb" target="_blank">こちら</a>からDiscordサーバーに参加してください。

参加したら、`#introduce-yourself` チャンネルで自己紹介することを忘れずに。

コースに関するすべての質問や問い合わせは、`Hugging Face Hub` の `courses` チャンネルをご利用ください。

Discordを初めて使う方は、ベストプラクティスをまとめたDiscord 101を用意しています。[次のセクション](discord101)をご確認ください。

### ステップ3：Hugging Face Agent Courseの組織をフォローする

**Hugging Face Agents Courseの組織をフォロー**して、最新のコース教材、アップデート、お知らせを受け取りましょう。

👉 <a href="https://huggingface.co/agents-course" target="_blank">こちら</a>にアクセスして、**follow** をクリックしてください。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/communication/hf_course_follow.gif" alt="Follow" width="100%"/>

### ステップ4：コースについて広める

このコースをもっと多くの人に知ってもらうためにご協力ください！2つの方法があります：

1. ⭐ <a href="https://github.com/huggingface/agents-course" target="_blank">コースのリポジトリ</a>にスターを付けて応援してください。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/communication/please_star.gif" alt="Repo star"/>

2. 学習の旅をシェア：このコースを受講していることを**みんなに知らせましょう**！SNS投稿に使えるイラストを用意しました。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/communication/share.png">

画像は👉 [こちら](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/communication/share.png?download=true)からダウンロードできます。

### ステップ5：Ollamaでモデルをローカル実行する（クレジット制限に達した場合）

1. **Ollamaをインストールする**

    公式の手順に従ってください。<a href="https://ollama.com/download" target="_blank">こちら。</a>

2. **モデルをローカルにプルする**

    ```bash
    ollama pull qwen2:7b
    ```

    ここでは、<a href="https://ollama.com/library/qwen2:7b" target="_blank">qwen2:7bモデル</a>をプルしています。その他のモデルについては<a href="https://ollama.com/search" target="_blank">Ollamaのウェブサイト</a>をご確認ください。

3. **Ollamaをバックグラウンドで起動する（別のターミナルで）**
    ``` bash
    ollama serve
    ``` 

    「listen tcp 127.0.0.1:11434: bind: address already in use」というエラーが発生した場合は、`sudo lsof -i :11434` コマンドを使用して、このポートを現在使用しているプロセスID（PID）を特定できます。プロセスが `ollama` の場合、上記のインストールスクリプトがすでにollamaサービスを起動している可能性が高いため、このOllama起動コマンドはスキップできます。

4. **`InferenceClientModel` の代わりに `LiteLLMModel` を使用する**

   `smolagents` で `LiteLLMModel` モジュールを使用するには、`pip` コマンドでモジュールをインストールしてください。

``` bash
    pip install 'smolagents[litellm]'
```

``` python
    from smolagents import LiteLLMModel

    model = LiteLLMModel(
        model_id="ollama_chat/qwen2:7b",  # または他のOllama対応モデルを試す
        api_base="http://127.0.0.1:11434",  # デフォルトのOllamaローカルサーバー
        num_ctx=8192,
    )
```

5. **なぜこれが動作するのか？**
- Ollamaは `http://localhost:11434` でOpenAI互換APIを使用してモデルをローカルで提供します。
- `LiteLLMModel` は、OpenAIのchat/completion APIフォーマットをサポートする任意のモデルと通信できるように構築されています。
- つまり、`InferenceClientModel` を `LiteLLMModel` に置き換えるだけで、他のコード変更は不要です。シームレスなプラグアンドプレイのソリューションです。

おめでとうございます！🎉 **オンボーディングプロセスが完了しました**！これでAI Agentについて学ぶ準備が整いました。楽しんでください！

学び続けましょう、素敵なままで 🤗

---

<!-- nav -->

[⬅️ 前へ: AI エージェントコースへようこそ](introduction.md) | [📚 目次](../README.md) | [次へ: Discord 101 ➡️](discord101.md)
