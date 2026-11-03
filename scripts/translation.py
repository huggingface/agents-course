import os
import sys
import re
from huggingface_hub import InferenceClient

# Get the directory containing the current script
script_dir = os.path.dirname(os.path.abspath(__file__))
default_inp_dir = os.path.join(script_dir, '..', 'units/en')
default_model = "deepseek-ai/DeepSeek-R1"
default_client = InferenceClient(
	provider="together",
    # api_key is read from the environment
)

def auto_translate(
    output_lang: str,
    prompt: callable,
    inp_dir: str = default_inp_dir,
    model: str = default_model,
    client: InferenceClient = default_client
):
    get_output_path = lambda x: x.replace('/en', f'/{output_lang}')
    escape_special_tokens = lambda x: x.replace('<think>', '<%%think%%>').replace('</think>', '<%%/think%%>')
    unescape_special_tokens = lambda x: x.replace('<%%think%%>', '<think>').replace('<%%/think%%>', '</think>')

    # Get the list of all files in the directory, recursively
    inp_files: list[str] = []
    print('Collecting files...')
    for root, dirs, files in os.walk(inp_dir):
        for file in files:
            if file.endswith('.mdx') or file == "_toctree.yml":
                fname = os.path.join(root, file)
                print('  +', fname)
                inp_files.append(fname)

    def write_out_file(fpath: str, content: str):
        base_path = os.path.dirname(fpath)
        os.makedirs(base_path, exist_ok=True)
        with open(fpath, 'w', encoding='utf-8') as f:
            f.write(content)

    # Read the content of the file and process
    for i, inp_file in enumerate(inp_files):
        out_file = get_output_path(inp_file)
        if os.path.exists(out_file):
            print(f'[{i+1}/{len(inp_files)}] Skipping file: {inp_file}')
            continue
        with open(inp_file, 'r', encoding='utf-8') as f:
            content: str = f.read()
            content = escape_special_tokens(content)
            if content.strip() == "":
                print(f'[{i+1}/{len(inp_files)}] Skipping empty file: {inp_file}')
                write_out_file(out_file, "")
                continue

            print(f'[{i+1}/{len(inp_files)}] Processing file: {inp_file}')
            stream = client.chat.completions.create(
                model=model,
                temperature=0.0,
                messages=[
                    {"role": "user", "content": prompt(content)},
                ],
                stream=True,
            )
            final_text = ""
            for chunk in stream:
                print(chunk.choices[0].delta.content, end="")
                sys.stdout.flush()
                final_text += chunk.choices[0].delta.content
            # Optionally filter <think>...</think> reasoning process
            final_text = final_text.split('</think>').pop().strip()
            # Write the output to the file
            final_text = unescape_special_tokens(final_text)
            write_out_file(out_file, final_text)
            print()
            print(f'  -> Translated to: {out_file}')
            print("--" * 20)
            #break
