# Let's Fine-Tune Your Model for Function-Calling

We're now ready to fine-tune our first model for function-calling 🔥.

## How do we train our model for function-calling?

> Answer: We need **data**

A model training process can be divided into 3 steps:

1. **The model is pre-trained on a large quantity of data**. The output of that step is a **pre-trained model**. For instance, [google/gemma-2-2b](https://huggingface.co/google/gemma-2-2b). It's a base model and only knows how **to predict the next token without strong instruction following capabilities**.

2. To be useful in a chat context, the model then needs to be **fine-tuned** to follow instructions. In this step, it can be trained by model creators, the open-source community, you, or anyone. For instance, [google/gemma-2-2b-it](https://huggingface.co/google/gemma-2-2b-it) is an instruction-tuned model by the Google Team behind the Gemma project.

3. The model can then be **aligned** to the creator's preferences. For instance, a customer service chat model that must never be impolite to customers.

Usually a complete product like Gemini or Mistral **will go through all 3 steps**, whereas the models you can find on Hugging Face have completed one or more steps of this training.

In this tutorial, we will build a function-calling model based on [google/gemma-2-2b-it](https://huggingface.co/google/gemma-2-2b-it). We choose the fine-tuned model [google/gemma-2-2b-it](https://huggingface.co/google/gemma-2-2b-it) instead of the base model [google/gemma-2-2b](https://huggingface.co/google/gemma-2-2b) because the fine-tuned model has been improved for our use-case.

Starting from the pre-trained model **would require more training in order to learn instruction following, chat AND function-calling**.

By starting from the instruction-tuned model, **we minimize the amount of information that our model needs to learn**.

## LoRA (Low-Rank Adaptation of Large Language Models)

LoRA is a popular and lightweight training technique that significantly **reduces the number of trainable parameters**.

It works by **inserting a smaller number of new weights as an adapter into the model to train**. This makes training with LoRA much faster, memory-efficient, and produces smaller model weights (a few hundred MBs), which are easier to store and share.

<img src="https://huggingface.co/datasets/agents-course/course-images/resolve/main/en/unit1/blog_multi-lora-serving_LoRA.gif" alt="LoRA inference" width="50%"/>

LoRA works by adding pairs of rank decomposition matrices to Transformer layers, typically focusing on linear layers. During training, we will "freeze" the rest of the model and will only update the weights of those newly added adapters.

By doing so, the number of **parameters** that we need to train drops considerably as we only need to update the adapter's weights.

During inference, the input is passed into the adapter and the base model, or these adapter weights can be merged with the base model, resulting in no additional latency overhead.

LoRA is particularly useful for adapting **large** language models to specific tasks or domains while keeping resource requirements manageable. This helps reduce the memory **required** to train a model.

If you want to learn more about how LoRA works, you should check out this [tutorial](https://huggingface.co/learn/nlp-course/chapter11/4?fw=pt).

## Fine-Tuning a Model for Function-Calling

You can access the tutorial notebook 👉 [here](https://huggingface.co/agents-course/notebooks/blob/main/bonus-unit1/bonus-unit1.ipynb).

Then, click on [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/#fileId=https://huggingface.co/agents-course/notebooks/blob/main/bonus-unit1/bonus-unit1.ipynb) to be able to run it in a Colab Notebook.


