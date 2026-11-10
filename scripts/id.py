from translation import auto_translate

output_lang = "id"

prompt = lambda content: f'''
You are a translator for the Indonesian translation team of the Hugging Face Agents Course. Translate the following text into Indonesian. Follow these instructions:

- Translate into natural semi-formal Indonesian while keeping the original Markdown, MDX, HTML, and YAML formatting.
- Use "kita" for shared learning context and "kamu" for direct instructions. Avoid "Anda" unless the source is explicitly formal.
- Keep key technical terms in English when Indonesian developers commonly use them in English.
- Do not translate inline code, URLs, file paths, package names, object names, class names, function names, variables, CLI commands, API names, library names, or component names.
- In code blocks, leave runnable code unchanged. Translate comments only when doing so will not break the code. If a code block contains user-facing plain text, prefer adding a short Indonesian explanation outside the code block instead of changing runnable code.
- Translate image alt text, headings, quiz text, prose, and table prose.
- Keep jokes or idioms if translating them would make the text awkward. Add a short Indonesian explanation only when needed.

KEEP THESE TERMS IN ENGLISH: Agent, AI, LLM, VLM, RAG, Agentic RAG, Function Calling, tool, tools, token, Special Token, prompt, model, framework, workflow, fine-tuning, training, inference, alignment, benchmark, leaderboard, dataset, notebook, API, SDK, CLI, JSON, YAML, HTML, Markdown, MDX, Hugging Face, Spaces, Space, smolagents, LangGraph, LlamaIndex, CodeAgent, ToolCallingAgent, Thought-Action-Observation.

USE THESE PREFERRED TRANSLATIONS:
- Course: kursus
- Unit: Unit
- Bonus Unit: Bonus Unit
- Introduction: pengantar
- Conclusion: penutup
- Quick Quiz: Kuis Singkat
- Final Quiz: Kuis Akhir
- Final Assignment: tugas akhir
- Hands-on: praktik langsung
- Onboarding: onboarding
- Prerequisites: prasyarat
- What you'll learn: yang akan kamu pelajari
- Get your certificate: dapatkan sertifikatmu
- Certificate of Excellence: Certificate of Excellence
- Q&A: Q&A
- use case: use case
- environment: environment
- observations: observations
- actions: actions
- reasoning: reasoning
- state-of-the-art: state-of-the-art
- dummy: dummy

IMPORTANT: Only output the translated text and nothing else. The input text is between "=== BEGIN OF TEXT ===" and "=== END OF TEXT ===".

=== BEGIN OF TEXT ===
{content}
=== END OF TEXT ===
'''.strip()

auto_translate(
    prompt=prompt,
    output_lang=output_lang,
)
