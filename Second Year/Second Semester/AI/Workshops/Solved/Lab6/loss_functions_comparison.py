from sklearn.datasets import load_iris
from sklearn.model_selection import cross_val_score
from sklearn.linear_model import SGDClassifier
import numpy as np

# load data
data = load_iris()
X = data.data
y = data.target

loss_functions = ['log_loss', 'hinge', 'modified_huber', 'perceptron']

for loss in loss_functions:
    model = SGDClassifier(loss=loss, max_iter=1000, random_state=42)
    scores = cross_val_score(model, X, y, cv=5)

    print(f"Loss function: {loss}")
    print("Accuracy:", scores.mean())
    print("---------------------")

# log loss cea mai potrivita (log loss este optimizata special pentru clasificare probabilistica)