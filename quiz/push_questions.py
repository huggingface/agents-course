import json
from pathlib import Path
from datasets import Dataset
from huggingface_hub import HfApi


ORG_NAME = "agents-course"


def main():
    """Push quiz questions to the Hugging Face Hub"""

    for file in Path("data").glob("*.json"):
        print(f"Processing {file}")

        with open(file, "r") as f:
            quiz_data = json.load(f)

        repo_id = f"{ORG_NAME}/{file.stem}_quiz"

        dataset = Dataset.from_list(quiz_data)

        print(f"Pushing {repo_id} to the Hugging Face Hub")

        dataset.push_to_hub(
            repo_id,
            private=True,
            commit_message=f"Update quiz questions for {file.stem}",
        )


if __name__ == "__main__":
    main()
