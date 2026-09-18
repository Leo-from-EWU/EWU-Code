# Local AI Engineering Sandbox

This directory contains a learning sandbox for AI Engineering and Retrieval-Augmented Generation (RAG) fundamentals. The focus is on understanding the core mechanics using local, open-source models without relying on high-level frameworks or paid APIs.

## What this module does

This module sets up a local Python environment to experiment with text embeddings. The primary script, `test_embeddings.py`, demonstrates how to convert natural language text into high-dimensional vectors (embeddings) using a lightweight Sentence Transformer model (`BAAI/bge-small-en-v1.5`). It then calculates the mathematical similarity between these vectors.

## Setup and Execution

To run this sandbox from your macOS terminal, follow these exact commands. Make sure you are in the `EWU-Code` directory before starting.

```bash
# 1. Navigate into the AI-Engineering directory
cd AI-Engineering

# 2. Create a Python virtual environment (venv)
python3 -m venv venv

# 3. Activate the virtual environment
source venv/bin/activate

# 4. Install the required packages
pip install -r requirements.txt

# 5. Execute the embeddings test script
python test_embeddings.py

# (Optional) To deactivate the virtual environment when you are done:
deactivate
```

## The Transformation Process Explained

Understanding how text becomes a vector is key to AI search and RAG:

1. **Text**: We start with natural language sentences (e.g., "Hello world").
2. **Tokenization**: The text is broken down into smaller chunks called "tokens" (words or sub-words) and mapped to integer IDs based on the model's vocabulary.
3. **Neural Network**: These integer IDs are fed into the pre-trained neural network (Transformer model), which processes the relationships and context of the words.
4. **High-Dimensional Vector**: The network outputs a fixed-size array of floating-point numbers (the embedding). For example, `BAAI/bge-small-en-v1.5` represents any sentence as a point in a 384-dimensional space.
5. **Similarity Metric**: We compare two points in this space using a metric like **Cosine Similarity**. The closer the angle between the two vectors, the more semantically similar the original sentences are considered to be.
