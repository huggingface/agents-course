

# Pokémon バトルエージェントを起動しよう

いよいよバトルの時間です！⚡️

## **配信エージェントとバトルしよう！**

自分でエージェントを作るのは面倒だけど、ポケモンにおけるエージェントのバトル能力に興味がある方へ。[Twitch](https://www.twitch.tv/jofthomas) で自動配信ライブストリームを公開しています。

🔗 **[リンクを開く](https://jofthomas-twitch-streaming.hf.space)**


配信中のエージェントとバトルするには：

手順：
1.  **Pokémon Showdown Space** にアクセスします：[こちらのリンク](https://huggingface.co/spaces/Jofthomas/Pokemon_showdown)
2.  **名前を選択**します（右上隅）。
3.  **現在のエージェントのユーザー名**を確認します。以下をチェックしてください：
    * **配信画面**：[こちらのリンク](https://www.twitch.tv/jofthomas)
4.  Showdown Space でそのユーザー名を**検索**し、**バトル招待を送信**します。

*注意：* オンラインのエージェントは一度に1体のみです！正しい名前を確認してください。



## Pokémon バトルエージェントチャレンジャー

前のセクションで自分の Pokémon バトルエージェントを作成した方は、きっとこう思っているでしょう：**他のエージェントとどうやって対戦できるの？** 確認してみましょう！

この目的のために専用の [Hugging Face Space](https://huggingface.co/spaces/PShowdown/pokemon_agents) を構築しました：

🔗 **[リンクを開く](https://pshowdown-pokemon-agents.hf.space)**

この Space は独自の **Pokémon Showdown サーバー**に接続されており、あなたのエージェントが AI 搭載の壮大なバトルで他のエージェントと対戦できます。

### エージェントの起動方法

以下の手順に従って、アリーナにエージェントを送り出しましょう：

1. **Space を複製する**  
   Space の右上メニューにある三点ボタンをクリックし、「Duplicate this Space」を選択します。

2. **`agent.py` にエージェントのコードを追加する**  
   ファイルを開き、エージェントの実装を貼り付けます。この[サンプル](https://huggingface.co/spaces/PShowdown/pokemon_agents/blob/main/agents.py)を参考にするか、[プロジェクト構成](https://huggingface.co/spaces/PShowdown/pokemon_agents/tree/main)を確認してください。

3. **`app.py` にエージェントを登録する**  
   ドロップダウンメニューにエージェントの名前とロジックを追加します。[こちらのコードスニペット](https://huggingface.co/spaces/PShowdown/pokemon_agents/blob/main/app.py)を参考にしてください。

4. **エージェントを選択する**  
   追加すると、「Select Agent」ドロップダウンメニューにエージェントが表示されます。リストから選択しましょう！✅

5. **Pokémon Showdown のユーザー名を入力する**  
   ユーザー名が iframe 内の **「Choose name」** 入力欄に表示されているものと一致していることを確認してください。公式アカウントで接続することもできます。

6. **「Send Battle Invitation」をクリックする**  
   エージェントが選択した対戦相手に招待を送信します。画面上に表示されるはずです！

7. **バトルを承諾して戦いを楽しもう！**  
   バトル開始です！最も賢いエージェントが勝利しますように。

自分の作品が実際に動くところを見る準備はできましたか？AI 対決の幕開けです！🥊

---

<!-- nav -->

[⬅️ 前へ: ポケモン Agent を作ろう](building_your_pokemon_agent.md) | [📚 目次](../README.md) | [次へ: Bonus 3 まとめ ➡️](conclusion.md)
