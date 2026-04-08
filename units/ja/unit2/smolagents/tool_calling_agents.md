

# アクションをコードスニペットまたは JSON blob として記述する

> [!TIP]
> Google Colab で実行できる<a href="https://huggingface.co/agents-course/notebooks/blob/main/unit2/smolagents/tool_calling_agents.ipynb" target="_blank">このノートブック</a>のコードに沿って学習できます。

Tool Calling Agent は、`smolagents` で利用可能な2番目のタイプのエージェントです。Python スニペットを使用する Code Agent とは異なり、これらのエージェントは **LLM プロバイダーに組み込まれた Tool Calling 機能を使用** して、**JSON 構造** としてツール呼び出しを生成します。これは OpenAI、Anthropic、その他多くのプロバイダーが採用する標準的なアプローチです。

例を見てみましょう。Alfred がケータリングサービスやパーティーのアイデアを検索したい場合、`CodeAgent` は次のような Python コードを生成して実行します：

```python
for query in [
    "Best catering services in Gotham City", 
    "Party theme ideas for superheroes"
]:
    print(web_search(f"Search for: {query}"))
```

一方、`ToolCallingAgent` は次のような JSON 構造を生成します：

```python
[
    {"name": "web_search", "arguments": "Best catering services in Gotham City"},
    {"name": "web_search", "arguments": "Party theme ideas for superheroes"}
]
```

この JSON blob がツール呼び出しの実行に使用されます。

`smolagents` は[全体的なパフォーマンスが優れている](https://huggingface.co/papers/2402.01030)ため主に `CodeAgents` に重点を置いていますが、`ToolCallingAgents` は変数の扱いや複雑なツール呼び出しを必要としないシンプルなシステムには効果的です。

![Code vs JSON Actions](https://huggingface.co/datasets/huggingface/documentation-images/resolve/main/transformers/code_vs_json_actions.png)  

## Tool Calling Agent の仕組み  

Tool Calling Agent は、Code Agent と同じマルチステップのワークフローに従います（詳細は[前のセクション](./code_agents)を参照してください）。

重要な違いは **アクションの構造化方法** にあります。実行可能なコードの代わりに、**ツール名と引数を指定する JSON オブジェクトを生成** します。システムはこれらの **指示をパース** して、適切なツールを実行します。

## 例：Tool Calling Agent の実行  

Alfred がパーティーの準備を始めた前回の例を再度取り上げますが、今回は `ToolCallingAgent` を使って違いを確認します。Code Agent の例と同様に、DuckDuckGo を使ってウェブ検索できるエージェントを構築します。異なるのはエージェントのタイプだけで、フレームワークがそれ以外のすべてを処理します：

```python
from smolagents import ToolCallingAgent, WebSearchTool, InferenceClientModel

agent = ToolCallingAgent(tools=[WebSearchTool()], model=InferenceClientModel())

agent.run("Search for the best music recommendations for a party at the Wayne's mansion.")
```

エージェントのトレースを確認すると、`Executing parsed code:` の代わりに次のような出力が表示されます：

```text
╭─────────────────────────────────────────────────────────────────────────────────────────────────────────────────╮
│ Calling tool: 'web_search' with arguments: {'query': "best music recommendations for a party at Wayne's         │
│ mansion"}                                                                                                       │
╰─────────────────────────────────────────────────────────────────────────────────────────────────────────────────╯
```  

エージェントは構造化されたツール呼び出しを生成し、システムがそれを処理して出力を生成します。`CodeAgent` のようにコードを直接実行するわけではありません。

これで両方のエージェントタイプを理解できたので、ニーズに合ったものを選択できます。Alfred のパーティーを成功させるために、`smolagents` の探索を続けましょう！🎉

## リソース

- [ToolCallingAgent ドキュメント](https://huggingface.co/docs/smolagents/v1.8.1/en/reference/agents#smolagents.ToolCallingAgent) - ToolCallingAgent の公式ドキュメント

---

<!-- nav -->

[⬅️ 前へ: smolagents: 小テスト 1](quiz1.md) | [📚 目次](../../README.md) | [次へ: コードエージェントの構築 ➡️](code_agents.md)
