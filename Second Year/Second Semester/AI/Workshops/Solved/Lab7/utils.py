import itertools
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
import numpy as np

def apply_sepia(img):
    sepia_filter = np.array([[0.272, 0.534, 0.131],
                             [0.349, 0.686, 0.168],
                             [0.393, 0.769, 0.189]])
    sepia_img = img.dot(sepia_filter.T) # T reprezinta transpusa matricei
    sepia_img = np.minimum(sepia_img, 1.0) # normalizam valorile intre [0,1] pentru a evita depasirea valorii maxime a pixelilor
    return sepia_img

def split_data(inputs, outputs):
    indexes = [i for i in range(len(inputs))]
    train_indexes = np.random.choice(indexes, int(0.8 * len(indexes)), replace=False) # selectam 80% din date pentru antrenament
    validation_indexes = [i for i in indexes if i not in train_indexes]

    train_inputs = [inputs[i] for i in train_indexes]
    train_outputs = [outputs[i] for i in train_indexes]
    validation_inputs = [inputs[i] for i in validation_indexes]
    validation_outputs = [outputs[i] for i in validation_indexes]

    return train_inputs, train_outputs, validation_inputs, validation_outputs

def plot_confusion_matrix(cm, classNames, title):
    plt.figure()
    plt.imshow(cm, interpolation='nearest', cmap='Blues')
    plt.title('Confusion Matrix ' + title)
    plt.colorbar()
    tick_marks = np.arange(len(classNames))
    plt.xticks(tick_marks, classNames, rotation=45)
    plt.yticks(tick_marks, classNames)
    text_format = 'd'
    thresh = cm.max() / 2.
    for row, column in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        plt.text(column, row, format(cm[row, column], text_format),
                 horizontalalignment="center",
                 color="white" if cm[row, column] > thresh else "black")
    plt.ylabel('True label')
    plt.xlabel('Predicted label')
    plt.tight_layout()
    plt.show()

def eval_multi_class(real_outputs, computed_outputs, outputs_names):
    conf_matrix = confusion_matrix(real_outputs, computed_outputs)
    accuracy = sum([conf_matrix[i][i] for i in range(len(outputs_names))]) / len(real_outputs)
    precision = {}
    rec = {}
    for i in range(len(outputs_names)):
        col_sum = sum([conf_matrix[j][i] for j in range(len(outputs_names))])
        row_sum = sum([conf_matrix[i][j] for j in range(len(outputs_names))])

        precision[outputs_names[i]] = conf_matrix[i][i] / col_sum if col_sum != 0 else 0
        rec[outputs_names[i]] = conf_matrix[i][i] / row_sum if row_sum != 0 else 0
    return accuracy, precision, rec, conf_matrix