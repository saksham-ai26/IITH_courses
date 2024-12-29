import re
import pandas as pd
import numpy as np
from sklearn.metrics.pairwise import cosine_similarity

#1 

# Read the contents of the text files
with open('Doc1.txt', 'r') as file:
    doc1 = file.read()

with open('Doc2.txt', 'r') as file:
    doc2 = file.read()

with open('Doc3.txt', 'r') as file:
    doc3 = file.read()

with open('Doc4.txt', 'r') as file:
    doc4 = file.read()

#a
# Tokenization
doc1_tokens = re.sub(r'[^\w\s]', '', doc1).lower().split()
doc2_tokens = re.sub(r'[^\w\s]', '', doc2).lower().split()
doc3_tokens = re.sub(r'[^\w\s]', '', doc3).lower().split()
doc4_tokens = re.sub(r'[^\w\s]', '', doc4).lower().split()

#b
# Vocabulary building
vocabulary = set(doc1_tokens + doc2_tokens + doc3_tokens + doc4_tokens)

# Print the total number of words in the vocabulary
print("Vocabulary size: ", len(vocabulary))

#2
#a
# Create frequency dictionaries for each review
doc1_freq = {token: doc1_tokens.count(token) for token in vocabulary}
doc2_freq = {token: doc2_tokens.count(token) for token in vocabulary}
doc3_freq = {token: doc3_tokens.count(token) for token in vocabulary}
doc4_freq = {token: doc4_tokens.count(token) for token in vocabulary}

#b
# Create a DataFrame from the frequency dictionaries
data = [doc1_freq, doc2_freq, doc3_freq, doc4_freq]
df = pd.DataFrame(data, columns=vocabulary)

# Convert the DataFrame into a NumPy array
vectors = df.values

#3
# Calculate the cosine similarity between vectors (reviews)
similarity = cosine_similarity(vectors)

# Convert the similarity matrix into a DataFrame for better visualization
similarity_df = pd.DataFrame(similarity, columns=df.index, index=df.index)


# Calculate the similarity between all pairs of reviews (vectors)
similarity = np.zeros((len(vectors), len(vectors)))

for i in range(len(vectors)):
    for j in range(len(vectors)):
        dot_product = np.dot(vectors[i], vectors[j])
        norm_product = np.linalg.norm(vectors[i]) * np.linalg.norm(vectors[j])
        similarity[i][j] = dot_product / norm_product

# Create a similarity DataFrame for better visualization
similarity_df = pd.DataFrame(similarity, columns=df.index, index=df.index)
max=0

for i in range(len(similarity_df)):
    for j in range(len(similarity_df)):
        if i == j:
            similarity_df.iloc[i, j] = 0

# Calculating the top 3 most similar pairs of reviews
max1=similarity_df.max().max()
similarity_df[similarity_df == max1] = 0
max2=similarity_df.max().max()
b=similarity_df.loc[similarity_df.max() == max2]
similarity_df[similarity_df == max2] = 0
max3=similarity_df.max().max()
c=similarity_df.loc[similarity_df.max() == max3]

df2 = pd.DataFrame([('(Item 1 , Item 2)',max1),('(Item 1 , Item 3)',max2),('(Item 2 , Item 3)',max3)],columns=['Item Pairs','Similarity']) # Create a DataFrame from the frequency dictionaries
print(df2)







        






