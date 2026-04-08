

# マルチエージェントシステム

マルチエージェントシステムは、**専門化されたエージェントが複雑なタスクで協力し合う**ことを可能にし、モジュール性、スケーラビリティ、堅牢性を向上させます。単一のエージェントに頼る代わりに、タスクはそれぞれ異なる能力を持つエージェントに分散されます。

**smolagents** では、異なるエージェントを組み合わせて Python コードの生成、外部ツールの呼び出し、Web 検索などを行うことができます。これらのエージェントをオーケストレーションすることで、強力なワークフローを構築できます。

典型的な構成には以下が含まれます：
- タスク委任のための**マネージャーエージェント**
- コード実行のための**コードインタープリターエージェント**
- 情報検索のための **Web 検索エージェント**

以下の図は、**マネージャーエージェント**が**コードインタープリターツール**と **Web 検索エージェント**を調整するシンプルなマルチエージェントアーキテクチャを示しています。Web 検索エージェントは `DuckDuckGoSearchTool` や `VisitWebpageTool` などのツールを活用して関連情報を収集します。

<img src="https://mermaid.ink/img/pako:eNp1kc1qhTAQRl9FUiQb8wIpdNO76eKubrmFks1oRg3VSYgjpYjv3lFL_2hnMWQOJwn5sqgmelRWleUSKLAtFs09jqhtoWuYUFfFAa6QA9QDTnpzamheuhxn8pt40-6l13UtS0ddhtQXj6dbR4XUGQg6zEYasTF393KjeSDGnDJKNxzj8I_7hLW5IOSmP9CH9hv_NL-d94d4DVNg84p1EnK4qlIj5hGClySWbadT-6OdsrL02MI8sFOOVkciw8zx8kaNspxnrJQE0fXKtjBMMs3JA-MpgOQwftIE9Bzj14w-cMznI_39E9Z3p0uFoA?type=png" style='background: white;'>

## マルチエージェントシステムの動作

マルチエージェントシステムは、**オーケストレーターエージェント**の調整のもとで連携する複数の専門化されたエージェントで構成されます。このアプローチにより、異なる役割を持つエージェント間でタスクを分配することで、複雑なワークフローが実現できます。

例えば、**マルチエージェント RAG システム**は以下を統合できます：
- インターネットを閲覧するための **Web エージェント**
- ナレッジベースから情報を取得するための**リトリーバーエージェント**
- ビジュアルを生成するための**画像生成エージェント**

これらすべてのエージェントは、タスクの委任とインタラクションを管理するオーケストレーターの下で動作します。

## マルチエージェント階層で複雑なタスクを解決する

> [!TIP]
> <a href="https://huggingface.co/agents-course/notebooks/blob/main/unit2/smolagents/multiagent_notebook.ipynb" target="_blank">こちらのノートブック</a>でコードを確認できます。Google Colab を使って実行可能です。

レセプションが近づいています！あなたの助けのおかげで、アルフレッドは準備をほぼ終えました。

しかし問題が発生しました：バットモービルが消えてしまったのです。アルフレッドは代わりの車を見つける必要がありますが、しかも急いで見つけなければなりません。

幸いなことに、ブルース・ウェインの人生を描いた伝記映画がいくつか制作されているので、映画のセットに残された車を手に入れて、フル自動運転オプションを含む最新の基準に合わせて改造できるかもしれません。

しかし、それは世界中の撮影ロケ地のどこにでもある可能性があり、その数は膨大かもしれません。

そこでアルフレッドはあなたの助けを求めています。このタスクを解決できるエージェントを構築できますか？

> 👉 世界中のバットマンの撮影ロケ地をすべて見つけ、そこまでの船での移送時間を計算し、船の移送時間に応じて色が変わるように地図上に表示してください。また、同じ船の移送時間でいくつかのスーパーカー工場も表示してください。

構築していきましょう！

この例ではいくつかの追加パッケージが必要なので、まずインストールしましょう：

```bash
pip install 'smolagents[litellm]' plotly geopandas shapely kaleido -q
```

### まず、貨物機の移送時間を取得するツールを作成します。

```python
import math
from typing import Optional, Tuple

from smolagents import tool


@tool
def calculate_cargo_travel_time(
    origin_coords: Tuple[float, float],
    destination_coords: Tuple[float, float],
    cruising_speed_kmh: Optional[float] = 750.0,  # 貨物機の平均速度
) -> float:
    """
    大圏距離を使用して、地球上の2点間の貨物機の移動時間を計算します。

    Args:
        origin_coords: 出発地の（緯度、経度）のタプル
        destination_coords: 目的地の（緯度、経度）のタプル
        cruising_speed_kmh: 巡航速度（km/h）（オプション、デフォルトは一般的な貨物機の750 km/h）

    Returns:
        float: 推定移動時間（時間単位）

    Example:
        >>> # シカゴ（北緯41.8781°、西経87.6298°）からシドニー（南緯33.8688°、東経151.2093°）
        >>> result = calculate_cargo_travel_time((41.8781, -87.6298), (-33.8688, 151.2093))
    """

    def to_radians(degrees: float) -> float:
        return degrees * (math.pi / 180)

    # 座標を抽出
    lat1, lon1 = map(to_radians, origin_coords)
    lat2, lon2 = map(to_radians, destination_coords)

    # 地球の半径（キロメートル）
    EARTH_RADIUS_KM = 6371.0

    # ハバーサインの公式を使用して大圏距離を計算
    dlon = lon2 - lon1
    dlat = lat2 - lat1

    a = (
        math.sin(dlat / 2) ** 2
        + math.cos(lat1) * math.cos(lat2) * math.sin(dlon / 2) ** 2
    )
    c = 2 * math.asin(math.sqrt(a))
    distance = EARTH_RADIUS_KM * c

    # 非直行ルートと航空管制を考慮して10%加算
    actual_distance = distance * 1.1

    # 飛行時間を計算
    # 離着陸手順のために1時間を追加
    flight_time = (actual_distance / cruising_speed_kmh) + 1.0

    # 結果をフォーマット
    return round(flight_time, 2)


print(calculate_cargo_travel_time((41.8781, -87.6298), (-33.8688, 151.2093)))
```

### エージェントのセットアップ

モデルプロバイダーには、[Hub 上の新しい推論プロバイダー](https://huggingface.co/blog/inference-providers)の一つである Together AI を使用します！

`GoogleSearchTool` は [Serper API](https://serper.dev) を使用して Web 検索を行うため、環境変数 `SERPAPI_API_KEY` を設定して `provider="serpapi"` を渡すか、`SERPER_API_KEY` を設定して `provider=serper` を渡す必要があります。

Serp API プロバイダーが設定されていない場合は `DuckDuckGoSearchTool` を使用できますが、レート制限があることに注意してください。

```python
import os
from PIL import Image
from smolagents import CodeAgent, GoogleSearchTool, InferenceClientModel, VisitWebpageTool

model = InferenceClientModel(model_id="Qwen/Qwen2.5-Coder-32B-Instruct", provider="together")
```

まず、シンプルなレポートを出力するベースラインとして、単純なエージェントを作成します。

```python
task = """Find all Batman filming locations in the world, calculate the time to transfer via cargo plane to here (we're in Gotham, 40.7128° N, 74.0060° W), and return them to me as a pandas dataframe.
Also give me some supercar factories with the same cargo plane transfer time."""
```

```python
agent = CodeAgent(
    model=model,
    tools=[GoogleSearchTool("serper"), VisitWebpageTool(), calculate_cargo_travel_time],
    additional_authorized_imports=["pandas"],
    max_steps=20,
)
```

```python
result = agent.run(task)
```

```python
result
```

この例では、以下のような出力が生成されます：

```python
|  | Location                                             | Travel Time to Gotham (hours) |
|--|------------------------------------------------------|------------------------------|
| 0  | Necropolis Cemetery, Glasgow, Scotland, UK         | 8.60                         |
| 1  | St. George's Hall, Liverpool, England, UK         | 8.81                         |
| 2  | Two Temple Place, London, England, UK             | 9.17                         |
| 3  | Wollaton Hall, Nottingham, England, UK           | 9.00                         |
| 4  | Knebworth House, Knebworth, Hertfordshire, UK    | 9.15                         |
| 5  | Acton Lane Power Station, Acton Lane, Acton, UK  | 9.16                         |
| 6  | Queensboro Bridge, New York City, USA            | 1.01                         |
| 7  | Wall Street, New York City, USA                  | 1.00                         |
| 8  | Mehrangarh Fort, Jodhpur, Rajasthan, India       | 18.34                        |
| 9  | Turda Gorge, Turda, Romania                      | 11.89                        |
| 10 | Chicago, USA                                     | 2.68                         |
| 11 | Hong Kong, China                                 | 19.99                        |
| 12 | Cardington Studios, Northamptonshire, UK        | 9.10                         |
| 13 | Warner Bros. Leavesden Studios, Hertfordshire, UK | 9.13                         |
| 14 | Westwood, Los Angeles, CA, USA                  | 6.79                         |
| 15 | Woking, UK (McLaren)                             | 9.13                         |
```

専用のプランニングステップを追加し、プロンプトを充実させることで、これをさらに改善できます。

プランニングステップにより、エージェントは先を見通して次のステップを計画できるようになり、より複雑なタスクに有用です。

```python
agent.planning_interval = 4

detailed_report = agent.run(f"""
You're an expert analyst. You make comprehensive reports after visiting many websites.
Don't hesitate to search for many queries at once in a for loop.
For each data point that you find, visit the source url to confirm numbers.

{task}
""")

print(detailed_report)
```

```python
detailed_report
```

この例では、以下のような出力が生成されます：

```python
|  | Location                                         | Travel Time (hours) |
|--|--------------------------------------------------|---------------------|
| 0  | Bridge of Sighs, Glasgow Necropolis, Glasgow, UK | 8.6                 |
| 1  | Wishart Street, Glasgow, Scotland, UK         | 8.6                 |
```


これらの簡単な変更のおかげで、エージェントに詳細なプロンプトを提供し、プランニング機能を付与するだけで、はるかに簡潔なレポートが得られました！

モデルのコンテキストウィンドウはすぐにいっぱいになります。そのため、**詳細な検索の結果を別の検索と組み合わせるようエージェントに依頼すると、処理が遅くなり、トークンとコストが急速に増加します**。

➡️ システムの構造を改善する必要があります。

### ✌️ タスクを2つのエージェントに分割する

マルチエージェント構造では、異なるサブタスク間でメモリを分離でき、2つの大きなメリットがあります：
- 各エージェントがコアタスクにより集中でき、パフォーマンスが向上する
- メモリの分離により各ステップの入力トークン数が削減され、レイテンシとコストが低下する

専用の Web 検索エージェントを持つチームを作成し、別のエージェントで管理しましょう。

マネージャーエージェントには最終レポートを作成するためのプロット機能が必要です。そこで、`plotly` や、空間プロット用の `geopandas` + `shapely` を含む追加インポートへのアクセスを付与します。

```python
model = InferenceClientModel(
    "Qwen/Qwen2.5-Coder-32B-Instruct", provider="together", max_tokens=8096
)

web_agent = CodeAgent(
    model=model,
    tools=[
        GoogleSearchTool(provider="serper"),
        VisitWebpageTool(),
        calculate_cargo_travel_time,
    ],
    name="web_agent",
    description="Browses the web to find information",
    verbosity_level=0,
    max_steps=10,
)
```

マネージャーエージェントにはかなりの思考力が必要です。

そこで、より強力なモデル [DeepSeek-R1](https://huggingface.co/deepseek-ai/DeepSeek-R1) を使用し、`planning_interval` も追加します。

```python
from smolagents.utils import encode_image_base64, make_image_url
from smolagents import OpenAIServerModel


def check_reasoning_and_plot(final_answer, agent_memory):
    multimodal_model = OpenAIServerModel("gpt-4o", max_tokens=8096)
    filepath = "saved_map.png"
    assert os.path.exists(filepath), "Make sure to save the plot under saved_map.png!"
    image = Image.open(filepath)
    prompt = (
        f"Here is a user-given task and the agent steps: {agent_memory.get_succinct_steps()}. Now here is the plot that was made."
        "Please check that the reasoning process and plot are correct: do they correctly answer the given task?"
        "First list reasons why yes/no, then write your final decision: PASS in caps lock if it is satisfactory, FAIL if it is not."
        "Don't be harsh: if the plot mostly solves the task, it should pass."
        "To pass, a plot should be made using px.scatter_map and not any other method (scatter_map looks nicer)."
    )
    messages = [
        {
            "role": "user",
            "content": [
                {
                    "type": "text",
                    "text": prompt,
                },
                {
                    "type": "image_url",
                    "image_url": {"url": make_image_url(encode_image_base64(image))},
                },
            ],
        }
    ]
    output = multimodal_model(messages).content
    print("Feedback: ", output)
    if "FAIL" in output:
        raise Exception(output)
    return True


manager_agent = CodeAgent(
    model=InferenceClientModel("deepseek-ai/DeepSeek-R1", provider="together", max_tokens=8096),
    tools=[calculate_cargo_travel_time],
    managed_agents=[web_agent],
    additional_authorized_imports=[
        "geopandas",
        "plotly",
        "shapely",
        "json",
        "pandas",
        "numpy",
    ],
    planning_interval=5,
    verbosity_level=2,
    final_answer_checks=[check_reasoning_and_plot],
    max_steps=15,
)
```

このチームの構造を確認しましょう：

```python
manager_agent.visualize()
```

以下のような出力が生成され、エージェント間の構造と使用されるツールの関係を理解するのに役立ちます：

```python
CodeAgent | deepseek-ai/DeepSeek-R1
├── ✅ Authorized imports: ['geopandas', 'plotly', 'shapely', 'json', 'pandas', 'numpy']
├── 🛠️ Tools:
│   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
│   ┃ Name                        ┃ Description                           ┃ Arguments                             ┃
│   ┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩
│   │ calculate_cargo_travel_time │ Calculate the travel time for a cargo │ origin_coords (`array`): Tuple of     │
│   │                             │ plane between two points on Earth     │ (latitude, longitude) for the         │
│   │                             │ using great-circle distance.          │ starting point                        │
│   │                             │                                       │ destination_coords (`array`): Tuple   │
│   │                             │                                       │ of (latitude, longitude) for the      │
│   │                             │                                       │ destination                           │
│   │                             │                                       │ cruising_speed_kmh (`number`):        │
│   │                             │                                       │ Optional cruising speed in km/h       │
│   │                             │                                       │ (defaults to 750 km/h for typical     │
│   │                             │                                       │ cargo planes)                         │
│   │ final_answer                │ Provides a final answer to the given  │ answer (`any`): The final answer to   │
│   │                             │ problem.                              │ the problem                           │
│   └─────────────────────────────┴───────────────────────────────────────┴───────────────────────────────────────┘
└── 🤖 Managed agents:
    └── web_agent | CodeAgent | Qwen/Qwen2.5-Coder-32B-Instruct
        ├── ✅ Authorized imports: []
        ├── 📝 Description: Browses the web to find information
        └── 🛠️ Tools:
            ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
            ┃ Name                        ┃ Description                       ┃ Arguments                         ┃
            ┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩
            │ web_search                  │ Performs a google web search for  │ query (`string`): The search      │
            │                             │ your query then returns a string  │ query to perform.                 │
            │                             │ of the top search results.        │ filter_year (`integer`):          │
            │                             │                                   │ Optionally restrict results to a  │
            │                             │                                   │ certain year                      │
            │ visit_webpage               │ Visits a webpage at the given url │ url (`string`): The url of the    │
            │                             │ and reads its content as a        │ webpage to visit.                 │
            │                             │ markdown string. Use this to      │                                   │
            │                             │ browse webpages.                  │                                   │
            │ calculate_cargo_travel_time │ Calculate the travel time for a   │ origin_coords (`array`): Tuple of │
            │                             │ cargo plane between two points on │ (latitude, longitude) for the     │
            │                             │ Earth using great-circle          │ starting point                    │
            │                             │ distance.                         │ destination_coords (`array`):     │
            │                             │                                   │ Tuple of (latitude, longitude)    │
            │                             │                                   │ for the destination               │
            │                             │                                   │ cruising_speed_kmh (`number`):    │
            │                             │                                   │ Optional cruising speed in km/h   │
            │                             │                                   │ (defaults to 750 km/h for typical │
            │                             │                                   │ cargo planes)                     │
            │ final_answer                │ Provides a final answer to the    │ answer (`any`): The final answer  │
            │                             │ given problem.                    │ to the problem                    │
            └─────────────────────────────┴───────────────────────────────────┴───────────────────────────────────┘
```

```python
manager_agent.run("""
Find all Batman filming locations in the world, calculate the time to transfer via cargo plane to here (we're in Gotham, 40.7128° N, 74.0060° W).
Also give me some supercar factories with the same cargo plane transfer time. You need at least 6 points in total.
Represent this as spatial map of the world, with the locations represented as scatter points with a color that depends on the travel time, and save it to saved_map.png!

Here's an example of how to plot and return a map:
import plotly.express as px
df = px.data.carshare()
fig = px.scatter_map(df, lat="centroid_lat", lon="centroid_lon", text="name", color="peak_hour", size=100,
     color_continuous_scale=px.colors.sequential.Magma, size_max=15, zoom=1)
fig.show()
fig.write_image("saved_image.png")
final_answer(fig)

Never try to process strings using code: when you have a string to read, just print it and you'll see it.
""")
```

あなたの実行結果がどうなったかはわかりませんが、私の場合、マネージャーエージェントは Web エージェントに与えるタスクを巧みに分割し、まず `1. バットマンの撮影ロケ地を検索`、次に `2. スーパーカー工場を検索` と進め、その後リストを集約して地図をプロットしました。

エージェントの状態から直接確認して、地図がどのようになったか見てみましょう：

```python
manager_agent.python_executor.state["fig"]
```

以下の地図が出力されます：

![マルチエージェントシステムの出力マップ例](https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/smolagents/output_map.png)

## リソース

- [マルチエージェントシステム](https://huggingface.co/docs/smolagents/main/en/examples/multiagents) – マルチエージェントシステムの概要。
- [Agentic RAG とは？](https://weaviate.io/blog/what-is-agentic-rag) – Agentic RAG の紹介。
- [マルチエージェント RAG システム 🤖🤝🤖 レシピ](https://huggingface.co/learn/cookbook/multiagent_rag_system) – マルチエージェント RAG システム構築のステップバイステップガイド。

---

<!-- nav -->

[⬅️ 前へ: エージェント型RAG](retrieval_agents.md) | [📚 目次](../../README.md) | [次へ: ビジョン Agent ➡️](vision_agents.md)
