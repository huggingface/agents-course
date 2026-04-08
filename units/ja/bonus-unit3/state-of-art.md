# ゲームにおけるLLM活用の最前線

この分野でどれほどの進歩が遂げられてきたかを理解するために、LLMのゲームへの統合を示す3つの技術デモと1つのリリース済みゲームを見ていきましょう。

## 🕵️‍♂️ NVIDIA と Inworld AI による Covert Protocol

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit3/covert-protocol.jpg" alt="Covert Protocol"/>

GDC 2024で発表された *Covert Protocol* は、プレイヤーが私立探偵となる技術デモです。

このデモで興味深いのは、AI駆動のNPCがプレイヤーの質問にリアルタイムで応答し、やり取りに基づいてナラティブに影響を与える点です。

このデモはUnreal Engine 5上に構築されており、NVIDIAのAvatar Cloud Engine（ACE）とInworld AIを活用して、まるで生きているかのようなキャラクターとのインタラクションを実現しています。

詳しくはこちら 👉 [Inworld AI Blog](https://inworld.ai/blog/nvidia-inworld-ai-demo-on-device-capabilities)

## 🤖 Ubisoft による NEO NPC

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit3/neo-npc.jpeg" alt="Neo NPC"/>

同じくGDC 2024で、Ubisoftは生成AIを搭載したNPCのプロトタイプ *NEO NPC* を発表しました。

これらのキャラクターは周囲の環境を認識し、過去のやり取りを記憶し、プレイヤーと意味のある会話を行うことができます。

ここでの狙いは、プレイヤーがNPCと真のインタラクションを行える、より没入感のある応答性の高いゲーム世界を作り出すことです。

詳しくはこちら 👉 [Inworld AI Blog](https://inworld.ai/blog/gdc-2024)

## ⚔️ NVIDIAのACEを搭載した Mecha BREAK

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit3/mecha-break.jpg" alt="Mecha BREAK"/>

*Mecha BREAK* は、NVIDIAのACE技術を統合してAI駆動のNPCに命を吹き込む、マルチプレイヤー対応のメカバトルゲームです。

プレイヤーは自然言語でこれらのキャラクターとやり取りでき、GPT-4oの統合により、NPCはウェブカメラを通じてプレイヤーやオブジェクトを認識することができます。この革新は、より没入感のあるインタラクティブなゲーム体験を実現するものです。

詳しくはこちら 👉 [NVIDIA Blog](https://blogs.nvidia.com/blog/digital-human-technology-mecha-break/)

## 🧛‍♂️ Proxima Enterprises の *Suck Up!*

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/bonus-unit3/suck-up.jpg" alt="Suck Up"/>

最後に、*Suck Up!* はリリース済みのゲームで、プレイヤーはヴァンパイアとなり、**AI駆動のNPCを説得して家に招き入れてもらう**ことを目指します。

各キャラクターは生成AIによって動作しており、ダイナミックで予測不可能なインタラクションが可能です。

詳しくはこちら 👉 [Suck Up! Official Website](https://www.playsuckup.com/)

## ちょっと待って…Agent はどこに？

これらのデモを見てきた後、こう思うかもしれません：「これらの例はゲームにおけるLLMの活用を示しているけれど、Agent が関わっているようには見えない。では、何が違うのか？ Agent はどのような追加の能力をもたらすのか？」

ご安心ください。それは次のセクションで学んでいきます。

---

<!-- nav -->

[⬅️ 前へ: LLM からエージェントへ](from-llm-to-agents.md) | [📚 目次](../README.md) | [次へ: ポケモン Agent を作ろう ➡️](building_your_pokemon_agent.md)
