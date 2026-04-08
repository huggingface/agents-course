

# LangGraph の構成要素

LangGraph でアプリケーションを構築するには、そのコアコンポーネントを理解する必要があります。LangGraph アプリケーションを構成する基本的な構成要素を見ていきましょう。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/LangGraph/Building_blocks.png" alt="構成要素" width="70%"/>

LangGraph のアプリケーションは**エントリーポイント**から始まり、実行内容に応じて、END に到達するまでフローがある関数から別の関数へと進みます。

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/LangGraph/application.png" alt="アプリケーション"/>

## 1. State（状態）

**State** は LangGraph の中心的な概念です。アプリケーションを流れるすべての情報を表します。

```python
from typing_extensions import TypedDict

class State(TypedDict):
    graph_state: str
```

State は**ユーザー定義**であるため、意思決定プロセスに必要なすべてのデータを含むようにフィールドを慎重に設計する必要があります！

> 💡 **ヒント:** アプリケーションがステップ間で追跡する必要がある情報について、よく考えましょう。

## 2. Node（ノード）

**Node** は Python 関数です。各ノードは：
- State を入力として受け取る
- 何らかの処理を実行する
- State への更新を返す

```python
def node_1(state):
    print("---Node 1---")
    return {"graph_state": state['graph_state'] +" I am"}

def node_2(state):
    print("---Node 2---")
    return {"graph_state": state['graph_state'] +" happy!"}

def node_3(state):
    print("---Node 3---")
    return {"graph_state": state['graph_state'] +" sad!"}
```

例えば、Node には以下のようなものを含めることができます：
- **LLM 呼び出し**：テキストの生成や意思決定
- **Tool 呼び出し**：外部システムとの連携
- **条件分岐ロジック**：次のステップの決定
- **人間の介入**：ユーザーからの入力取得

> 💡 **情報:** ワークフロー全体に必要な START や END などのノードは、LangGraph に最初から用意されています。


## 3. Edge（エッジ）

**Edge** はノード同士を接続し、グラフ内の可能な経路を定義します：

```python
import random
from typing import Literal

def decide_mood(state) -> Literal["node_2", "node_3"]:
    
    # 多くの場合、次に訪問するノードの決定にstateを使用します
    user_input = state['graph_state'] 
    
    # ここでは、ノード2と3を50/50で分岐させます
    if random.random() < 0.5:

        # 50%の確率でNode 2を返す
        return "node_2"
    
    # 50%の確率でNode 3を返す
    return "node_3"
```

Edge には以下の種類があります：
- **直接エッジ**：常にノード A からノード B へ進む
- **条件付きエッジ**：現在の State に基づいて次のノードを選択する

## 4. StateGraph

**StateGraph** は、エージェントのワークフロー全体を保持するコンテナです：

```python
from IPython.display import Image, display
from langgraph.graph import StateGraph, START, END

# グラフの構築
builder = StateGraph(State)
builder.add_node("node_1", node_1)
builder.add_node("node_2", node_2)
builder.add_node("node_3", node_3)

# ロジックの定義
builder.add_edge(START, "node_1")
builder.add_conditional_edges("node_1", decide_mood)
builder.add_edge("node_2", END)
builder.add_edge("node_3", END)

# コンパイル
graph = builder.compile()
```

これを可視化することもできます！
```python
# 表示
display(Image(graph.get_graph().draw_mermaid_png()))
```
<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit2/LangGraph/basic_graph.jpeg" alt="グラフの可視化"/>

そして最も重要なのは、実行できることです：
```python
graph.invoke({"graph_state" : "Hi, this is Lance."})
```
出力：
```
---Node 1---
---Node 3---
{'graph_state': 'Hi, this is Lance. I am sad!'}
```

## 次のステップ

次のセクションでは、これらの概念を実践に移し、最初のグラフを構築します。このグラフでは、Alfred がメールを受け取り、分類し、正当なメールであれば予備的な返信を作成します。

---

<!-- nav -->

[⬅️ 前へ: LangGraph とは？](when_to_use_langgraph.md) | [📚 目次](../../README.md) | [次へ: 初めての LangGraph ➡️](first_graph.md)
