import numpy as np
import pandas as pd
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# 1. Load dataset
data = load_iris()

X = data.data  # 4 features (sepal length, sepal width, petal length, petal width)
y = data.target  # 3 classes (setosa, versicolor, virginica)

# 2. split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 3. normalizare
mean = X_train.mean(axis=0)
std = X_train.std(axis=0)

X_train = (X_train - mean) / std
X_test = (X_test - mean) / std

# 4. Softmax Regression (from scratch)
class SoftmaxRegression:
    def __init__(self, lr=0.1, epochs=5000):
        self.lr = lr
        self.epochs = epochs

    def softmax(self, z):
        exp_z = np.exp(z - np.max(z, axis=1, keepdims=True))
        return exp_z / np.sum(exp_z, axis=1, keepdims=True)

    def one_hot(self, y, num_classes):
        one_hot = np.zeros((len(y), num_classes))
        one_hot[np.arange(len(y)), y] = 1
        return one_hot

    def fit(self, X, y):
        n_samples, n_features = X.shape
        n_classes = len(np.unique(y))

        # f1(x) = w11 * x + w21 * x + w31 * x + w41 * x + b1 regresor pentru setosa
        # f2(x) = w12 * x + w22 * x + w32 * x + w42 * x + b2 regresor pentru versicolor
        # f3(x) = w13 * x + w23 * x + w33 * x + w43 * x + b3 regresor pentru virginica
        self.W = np.zeros((n_features, n_classes))
        self.b = np.zeros((1, n_classes))

        y_encoded = self.one_hot(y, n_classes)

        for _ in range(self.epochs):
            linear = np.dot(X, self.W) + self.b
            probs = self.softmax(linear)

            dw = (1 / n_samples) * np.dot(X.T, (probs - y_encoded))
            db = (1 / n_samples) * np.sum(probs - y_encoded, axis=0, keepdims=True)

            self.W -= self.lr * dw
            self.b -= self.lr * db

    def predict(self, X):
        linear = np.dot(X, self.W) + self.b
        probs = self.softmax(linear)
        return np.argmax(probs, axis=1)


# 5. training
model = SoftmaxRegression(lr=0.1, epochs=5000)
model.fit(X_train, y_train)

# 6. evaluation
pred = model.predict(X_test)
print("Accuracy:", accuracy_score(y_test, pred))


# 7. predict for given flower
# sepal length = 5.35
# sepal width = 3.85
# petal length = 1.25
# petal width = 0.4

flower = np.array([[5.35, 3.85, 1.25, 0.4]])
flower = (flower - mean) / std

prediction = model.predict(flower)

species = ["setosa", "versicolor", "virginica"]

print("Specia prezisă:", species[prediction[0]])