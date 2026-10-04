from math import exp

import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, classification_report

def plotDataHistogram(x, variableName):
    n, bins, patches = plt.hist(x, 10)
    plt.title('Histogram of ' + variableName)
    plt.show()

def plot3Ddata(x1Train, x2Train, yTrain, x1Model=None, x2Model=None, yModel=None, x1Test=None, x2Test=None, yTest=None, title=None):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Use 'is not None and len() > 0' to be safe with empty lists
    if x1Train is not None and len(x1Train) > 0:
        ax.scatter(x1Train, x2Train, yTrain, c='r', marker='o', label='train data')
    if x1Model is not None and len(x1Model) > 0:
        ax.scatter(x1Model, x2Model, yModel, c='b', marker='_', label='learnt model')
    if x1Test is not None and len(x1Test) > 0:
        ax.scatter(x1Test, x2Test, yTest, c='g', marker='^', label='test data')

    ax.set_title(title)
    ax.set_xlabel("mean radius")
    ax.set_ylabel("mean texture")
    ax.set_zlabel("is benign")

    # Only show legend if at least one plot was created
    handles, labels = ax.get_legend_handles_labels()
    if labels:
        ax.legend()
    plt.show()

data = load_breast_cancer()
X = pd.DataFrame(data.data, columns=data.feature_names)[['mean radius', 'mean texture']]
y = data.target

feature1 = X['mean radius']
feature2 = X['mean texture']
plotDataHistogram(feature1, 'mean radius')
plotDataHistogram(feature2, 'mean texture')
plotDataHistogram(y, 'is benign')

# check the liniarity (to check that a linear relationship exists between the dependent variable and the independent variables.)
plot3Ddata(feature1, feature2, y, title='mean radius vs mean texture vs result (is benign)')

# split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
plot3Ddata(X_train['mean radius'], X_train['mean texture'], y_train, x1Test=X_test['mean radius'], x2Test=X_test['mean texture'], yTest=y_test, title="train and test data")

# normalize the data
mean = X_train.mean(axis=0).values
std = X_train.std(axis=0).values
X_train = (X_train.values - mean) / std
X_test = (X_test.values - mean) / std

# train the logistic regression model
class LogisticRegressionManual:
    def __init__(self, learning_rate=0.01, epochs=2000):
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.weights = None
        self.bias = None

    # sigmoid function
    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    # training the model
    def fit(self, X, y):
        n_samples, n_features = X.shape

        self.weights = np.zeros(n_features)
        self.bias = 0

        # gradient descent
        for _ in range(self.epochs):
            linear_model = np.dot(X, self.weights) + self.bias
            y_predicted = self.sigmoid(linear_model)

            dw = (1 / n_samples) * np.dot(X.T, (y_predicted - y))
            db = (1 / n_samples) * np.sum(y_predicted - y)

            # actualizare parametri
            self.weights -= self.learning_rate * dw
            self.bias -= self.learning_rate * db

            if _ % 500 == 0:
                loss = -np.mean(
                    y * np.log(y_predicted + 1e-8) +
                    (1 - y) * np.log(1 - y_predicted + 1e-8)
                )
                print(f"Epoch {_}, loss: {loss}")

    # predicție probabilitate
    def predict(self, X):
        linear_model = np.dot(X, self.weights) + self.bias
        y_predicted = self.sigmoid(linear_model)
        y_class = [1 if i > 0.5 else 0 for i in y_predicted]
        return np.array(y_class)

# train the model
model = LogisticRegressionManual(learning_rate=0.01, epochs=5000)
model.fit(X_train, y_train)

# evaluate the model's performance
predictions = model.predict(X_test)
accuracy = accuracy_score(y_test, predictions)
print('Accuracy: ', accuracy)

# preidct for mean radius = 18 and mean texture = 10
noua_leziune = np.array([[18, 10]])
noua_leziune = (noua_leziune - mean) / std
predictie = model.predict(noua_leziune)
if predictie[0] == 0:
    print("Leziunea este MALIGNĂ")
else:
    print("Leziunea este BENIGNĂ")