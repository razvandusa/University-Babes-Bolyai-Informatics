import numpy as np
from sklearn.datasets import load_iris
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import cross_val_score

# incarcare dataset flori iris
data = load_iris()
X = data.data
y = data.target

# validare incrucisata cu 5 subseturi
model = LogisticRegression(max_iter=500)
scores = cross_val_score(model, X, y, cv=5)

print("Accuracy for each fold:", scores)
print("Mean accuracy:", scores.mean())
print("Standard deviation:", scores.std())