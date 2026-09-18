"""
test_embeddings.py

A beginner-friendly script to demonstrate how text embeddings work.
We will load a local, open-source model, encode some sentences into vectors,
and compute cosine similarity to see how mathematically "close" they are.
"""

import numpy as np
from sentence_transformers import SentenceTransformer, util

# 1. Load the Embedding Model
print("Loading the model: BAAI/bge-small-en-v1.5 ...")
# This will download the model to your local cache if not already present.
# It runs entirely locally on your machine, requiring no API keys.
model = SentenceTransformer("BAAI/bge-small-en-v1.5")
print("Model loaded successfully!\n")

# 2. Define Sample Sentences
# Sentences 1 and 2 are semantically similar.
sentence_1 = "I am learning how to build AI applications locally."
sentence_2 = "Studying artificial intelligence development on my own machine."
# Sentence 3 is distinct/unrelated.
sentence_3 = "The secret to a good pasta sauce is fresh tomatoes and garlic."

sentences = [sentence_1, sentence_2, sentence_3]

# 3. Compute Vector Embeddings
print("Generating vector embeddings for the sentences...")
# .encode() converts the text into numerical arrays (vectors).
embeddings = model.encode(sentences)
print("Embeddings generated!\n")

# --- Analysis & Output ---

# Print 1: The shape and dimension of the generated embeddings
# Expected shape: (number_of_sentences, embedding_dimension) -> (3, 384) for BGE-small
print(f"1. Embeddings shape: {embeddings.shape}")
print(f"   (We have {embeddings.shape[0]} sentences, each represented by {embeddings.shape[1]} dimensions)\n")

# Print 2: The first 5 float values of the first embedding vector (Sentence 1)
print("2. First 5 float values of Sentence 1's embedding:")
print(f"   {embeddings[0][:5]}\n")

# Print 3: Cosine similarity scores
print("3. Cosine Similarity Scores:")
# We use util.cos_sim to compute the cosine similarity (angle) between vectors.
# A score closer to 1 means more similar; closer to 0 means less similar.

# Compare Sentence 1 vs 2 (Similar)
sim_1_2 = util.cos_sim(embeddings[0], embeddings[1]).item()
print(f"   Sentence 1 vs Sentence 2 (Similar)  : {sim_1_2:.4f}")

# Compare Sentence 1 vs 3 (Unrelated)
sim_1_3 = util.cos_sim(embeddings[0], embeddings[2]).item()
print(f"   Sentence 1 vs Sentence 3 (Unrelated): {sim_1_3:.4f}")

print("\nScript completed successfully!")