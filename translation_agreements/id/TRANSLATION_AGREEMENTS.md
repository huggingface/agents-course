## Indonesian translation agreement

This document is the working agreement for the Indonesian translation of the Hugging Face Agents Course.

## Process

1. Translate by unit or by a clearly bounded section. Keep the structure and file names identical to `units/en`.
2. Keep discussions, commit messages, and pull request text in English so upstream maintainers can review the work.
3. Use AI-assisted translation if useful, but always review the final text manually. The course should read like Indonesian technical writing, not like raw machine translation.
4. Keep the glossary updated when a recurring term needs a stable treatment.
5. Preserve Markdown, MDX, HTML, links, image paths, imports, frontmatter, and code fences.

## Style

1. Use natural semi-formal Indonesian. Prefer `kita` for shared learning context and `kamu` for direct instructions.
2. Do not use `Anda` unless the original context is explicitly formal.
3. Keep key technical terms in English, especially terms that Indonesian developers commonly use in English.
4. Avoid stiff literal translations. For example, prefer `mari kita lihat cara kerjanya` over `mari kita menyelami`.
5. Keep jokes or idioms when translating them would make them awkward. Add a short explanation only if needed.
6. Translate image alt text, headings, quiz text, and prose.
7. Do not translate URLs, file paths, package names, object names, class names, function names, variables, CLI commands, API names, library names, or inline code.
8. In code blocks, keep the code unchanged. Translate comments only when doing so will not break the code. For examples that contain plain user-facing text, add a translated explanation outside the code block rather than changing runnable code.

## Terms to keep in English

| English term | Indonesian treatment | Notes |
|---|---|---|
| Agent | Agent | Keep capitalized when it names the concept. |
| AI | AI | Do not translate to `kecerdasan buatan` unless the sentence explicitly defines AI. |
| LLM | LLM | First mention may be `LLM (Large Language Model)`. |
| VLM | VLM | First mention may be `VLM (Vision Language Model)`. |
| RAG | RAG | First mention may be `RAG (Retrieval-Augmented Generation)`. |
| Agentic RAG | Agentic RAG | Keep as a technical term. |
| Function Calling | Function Calling | Keep the capitalization used by the source. |
| tool, tools | tool, tools | Use English, especially in course concepts and API contexts. |
| Token, Special Token | token, Special Token | `token` can be lowercase in prose. |
| prompt | prompt | Use `prompt`, not `perintah`, unless the context is general prose. |
| model | model | Keep in English. |
| framework | framework | Keep in English. |
| workflow | workflow | Keep in English. |
| fine-tuning | fine-tuning | Keep in English. |
| training | training | Keep in English. |
| inference | inference | Keep in English. |
| alignment | alignment | Keep in English. |
| benchmark | benchmark | Keep in English. |
| leaderboard | leaderboard | Keep in English. |
| dataset | dataset | Keep in English. |
| notebook | notebook | Keep in English. |
| API, SDK, CLI | API, SDK, CLI | Keep in English. |
| JSON, YAML, HTML, Markdown, MDX | JSON, YAML, HTML, Markdown, MDX | Keep in English. |
| Hugging Face, Spaces, Space | Hugging Face, Spaces, Space | Keep product names unchanged. |
| smolagents | smolagents | Keep lowercase as in source. |
| LangGraph | LangGraph | Product/library name. |
| LlamaIndex | LlamaIndex | Product/library name. |
| CodeAgent | CodeAgent | Class/concept name. |
| ToolCallingAgent | ToolCallingAgent | Class/concept name. |
| Thought-Action-Observation | Thought-Action-Observation | Keep the cycle name in English. |

## Preferred translations

| English term | Indonesian translation |
|---|---|
| Course | kursus |
| Unit | Unit |
| Bonus Unit | Bonus Unit |
| Introduction | pengantar |
| Conclusion | penutup |
| Quick Quiz | Kuis Singkat |
| Final Quiz | Kuis Akhir |
| Final Assignment | tugas akhir |
| Hands-on | praktik langsung |
| Onboarding | onboarding |
| Prerequisites | prasyarat |
| What you'll learn | yang akan kamu pelajari |
| Get your certificate | dapatkan sertifikatmu |
| Certificate of Excellence | Certificate of Excellence |
| Q&A | Q&A |
| use case | use case |
| environment | environment |
| observations | observations |
| actions | actions |
| reasoning | reasoning |
| state-of-the-art | state-of-the-art |
| dummy | dummy |

## Review checklist

1. The translated file keeps the same MDX structure as the English source.
2. Links, paths, imports, component names, and code identifiers are unchanged.
3. Headings and navigation titles are translated naturally.
4. Technical terms follow the glossary.
5. The text does not sound like literal English word order.
6. There are no accidental translations inside runnable code.
7. There are no extra explanations from the translator outside the course content.
