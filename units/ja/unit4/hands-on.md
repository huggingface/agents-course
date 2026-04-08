# ハンズオン

最終エージェントの作成にさらに深く取り組む準備ができたところで、レビューのために提出する方法を見ていきましょう。

## データセット

このリーダーボードで使用されるデータセットは、GAIAの**検証**セットのレベル1の問題から抽出された20問で構成されています。

選定された問題は、回答に必要なツールの数とステップ数に基づいてフィルタリングされています。

GAIAベンチマークの現在の状況を踏まえると、レベル1の問題で30%を目指すことは適切なテストだと考えています。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit4/leaderboard%20GAIA%2024%3A04%3A2025.png" alt="GAIAの現在の状況！" />

## プロセス

おそらく今あなたが考えている大きな疑問は、「どうやって提出を始めればいいのか？」でしょう。

このユニットでは、問題を取得し、採点のために回答を送信できるAPIを作成しました。
以下はルートの概要です（インタラクティブな詳細は[ライブドキュメント](https://agents-course-unit4-scoring.hf.space/docs)を参照してください）：

* **`GET /questions`**：フィルタリングされた評価問題の全リストを取得します。
* **`GET /random-question`**：リストからランダムに1問を取得します。
* **`GET /files/{task_id}`**：指定されたタスクIDに関連する特定のファイルをダウンロードします。
* **`POST /submit`**：エージェントの回答を提出し、スコアを計算してリーダーボードを更新します。

提出関数は回答を正解と**完全一致**で比較するため、プロンプトを適切に設計してください！GAIAチームがエージェント向けのプロンプト例を[こちら](https://huggingface.co/spaces/gaia-benchmark/leaderboard)で共有しています（このコースでは、提出時に「FINAL ANSWER」というテキストを含めないようにし、エージェントが回答のみを返すようにしてください）。

🎨 **テンプレートを自分流にカスタマイズしましょう！**

APIとのやり取りのプロセスを示すために、出発点として[基本テンプレート](https://huggingface.co/spaces/agents-course/Final_Assignment_Template)を用意しています。

自由に変更、追加、または完全に再構築してください。むしろ**積極的にそうすること**を推奨します！あなたのアプローチや創造性に最も合うように、好きなように修正してください。

このテンプレートを提出するには、APIが必要とする3つの情報を計算します：

* **ユーザー名：** Hugging Faceのユーザー名（ここではGradioログインを通じて取得）。提出者を識別するために使用されます。
* **コードリンク（`agent_code`）：** 検証目的でHugging Face SpaceのコードへのリンクURL（`.../tree/main`）。Spaceは公開のままにしておいてください。
* **回答（`answers`）：** 採点のためにエージェントが生成した回答のリスト（`{"task_id": ..., "submitted_answer": ...}`）。

まずはこの[テンプレート](https://huggingface.co/spaces/agents-course/Final_Assignment_Template)を自分のHugging Faceプロフィールに複製することから始めることをお勧めします。

🏆 リーダーボードは[こちら](https://huggingface.co/spaces/agents-course/Students_leaderboard)からご覧ください

*ちょっとしたお知らせ：このリーダーボードは楽しむためのものです！完全な検証なしにスコアを提出できることは承知しています。裏付けとなる公開リンクなしに高スコアの投稿が多すぎる場合は、リーダーボードの有用性を保つために、一部のエントリをレビュー、調整、または削除する必要があるかもしれません。*
リーダーボードにはあなたのSpaceのコードベースへのリンクが表示されます。このリーダーボードは受講生専用ですので、誇れるスコアを獲得した場合はSpaceを公開のままにしておいてください。
🔗 **[リンクを開く](https://agents-course-students-leaderboard.hf.space)**

---

<!-- nav -->

[⬅️ 前へ: GAIA とは？](what-is-gaia.md) | [📚 目次](../README.md) | [次へ: 次のステップ ➡️](additional-readings.md)
