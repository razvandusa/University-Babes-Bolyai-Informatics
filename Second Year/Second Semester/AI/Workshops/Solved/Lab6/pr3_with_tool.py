import numpy as np
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, classification_report

# 1. Load dataset
data = load_iris()

X = data.data        # features
y = data.target      # classes: 0=setosa, 1=versicolor, 2=virginica

# 2. Split into train and test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 3. Create and train logistic regression model
model = LogisticRegression(max_iter=500)
model.fit(X_train, y_train)

# 4. Evaluate the model
predictions = model.predict(X_test)

accuracy = accuracy_score(y_test, predictions)
print("Accuracy:", accuracy)

# 5. Predict species for a new flower
new_flower = np.array([[5.35, 3.85, 1.25, 0.4]])
prediction = model.predict(new_flower)
species = data.target_names
print("Predicted species:", species[prediction[0]])