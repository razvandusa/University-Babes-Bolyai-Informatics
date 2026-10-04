import numpy as np
class ANN:
    def __init__(self, features, labels, hidden):
        self.features = features # numarul de caracteristici de intrare
        self.labels = labels # numarul de clase
        self.hidden = hidden # numarul de neuroni din stratul ascuns

        self.w1_matrix = 0.01 * np.random.rand(self.features, self.hidden) # matricea de greutati pentru stratul de intrare
        self.b1_matrix = np.zeros((1, self.hidden)) # matricea de bias pentru stratul de intrare
        self.w2_matrix = 0.01 * np.random.rand(self.hidden, self.labels) # matricea de greutati pentru stratul de iesire
        self.b2_matrix = np.zeros((1, self.labels)) # matricea de

    def forward_propagation(self, features):
        z1 = np.dot(features, self.w1_matrix) + self.b1_matrix # calculam activarea pentru stratul ascuns
        z1 = np.maximum(0, z1) # aplicam functia de activare ReLU
        z2 = np.dot(z1, self.w2_matrix) + self.b2_matrix # calculam activarea pentru stratul de iesire
        exp_scores = np.exp(z2 - np.max(z2, axis=1, keepdims=True)) # aplicam functia softmax pentru a obtine probabilitatile de iesire
        z2 = exp_scores / np.sum(exp_scores, axis=1, keepdims=True)
        return z1, z2

    # cross entropy loss
    def ce_loss(self, output_true, output_computed):
        n_examples = output_true.shape[0] # numarul de exemple din setul de date
        log_probs = -np.log(output_computed[range(n_examples), output_true]) # calculam cat de sigure sunt predictiile modelului
        loss = np.sum(log_probs) / n_examples # calculam pierderea medie
        return loss

    def backward_propagation(self, features, output_true, z1, output_computed):
        n_examples = output_true.shape[0] # numarul de exemple din setul de date
        eroare2 = output_computed.copy() # copiem matricea de iesire pentru a calcula eroarea
        eroare2[range(n_examples), output_true] -= 1 # calculam eroarea pentru fiecare exemplu
        eroare2 /= n_examples # normalizam eroarea, adica facem media erorii pe toate exemplele

        gradient_w2 = np.dot(z1.T, eroare2) # calculam gradientul pentru matricea de greutati a stratului de iesire
        bias2 = np.sum(eroare2, axis=0, keepdims=True) # calculam gradientul pentru matricea de bias a stratului de iesire

        eroare1 = np.dot(eroare2, self.w2_matrix.T) # calculam eroarea pentru stratul ascuns
        eroare1[z1 <= 0] = 0 # aplicam derivata functiei de activare ReLU pentru a calcula eroarea pentru fiecare neuron din stratul ascuns

        gradient_w1 = np.dot(features.T, eroare1) # calculam gradientul pentru matricea de greutati a stratului de intrare
        bias1 = np.sum(eroare1, axis=0, keepdims=True) # calculam gradientul pentru matricea de bias a stratului de intrare

        return gradient_w1, bias1, gradient_w2, bias2

    def fit(self, features, output_corect, reg=1e-3, max_iters=1000, learning_rate=0.1):
        for i in range(max_iters):
            z1, z2 = self.forward_propagation(features)
            if i % 100 == 0:
                loss = self.ce_loss(output_corect, z2)
                reg_loss = 0.5 * reg * (np.sum(self.w1_matrix ** 2) + np.sum(self.w2_matrix ** 2)) # adaugam pierderea de regularizare pentru a preveni overfitting-ul
                print(f"Iteratia {i}, pierdere: {loss + reg_loss}")

            gradient_w1, bias1, gradient_w2, bias2 = self.backward_propagation(features, output_corect, z1, z2)
            gradient_w2 += reg * self.w2_matrix # adaugam gradientul de regularizare pentru matricea de greutati a stratului de iesire
            gradient_w1 += reg * self.w1_matrix # adaugam gradientul de regularizare pentru matricea de greutati a stratului de intrare

            self.w1_matrix -= learning_rate * gradient_w1 # actualizam matricea de greutati a stratului de intrare
            self.b1_matrix -= learning_rate * bias1 # actualizam matricea de bias
            self.w2_matrix -= learning_rate * gradient_w2 # actualizam matricea de greutati a stratului de iesire
            self.b2_matrix -= learning_rate * bias2 # actualizam matricea de bias

    def predict(self, features):
        _, output_computed = self.forward_propagation(features) # calculam iesirea modelului pentru datele de intrare
        return np.argmax(output_computed, axis=1) # returnam clasa prezisa de model pentru fiecare exemplu