from math import exp

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

# train the logistic regression model
model = LogisticRegression()
model.fit(X_train, y_train)
w0, w1, w2 = model.intercept_[0], model.coef_[0][0], model.coef_[0][1]
# print('The learnt model: f(x) = ', w0, ' + ', w1, ' * x1 + ', w2, ' * x2')

# evaluate the model's performance
y_pred = model.predict(X_test)
y_pred2 = [w0 + w1 * el1 + w2 * el2 for el1, el2 in zip(X_test['mean radius'], X_test['mean texture'])]
y_pred2 = [1 / (1 + exp(-x)) for x in y_pred2]
y_pred2 = [1 if x > 0.5 else 0 for x in y_pred2]
print('Accuracy: ', accuracy_score(y_test, y_pred))

# preidct for mean radius = 18 and mean texture = 10
noua_leziune = [[18, 10]]
predictie = model.predict(noua_leziune)
if predictie[0] == 0:
    print("Leziunea este MALIGNĂ")
else:
    print("Leziunea este BENIGNĂ")