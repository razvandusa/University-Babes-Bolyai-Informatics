import numpy as np

# Convolutia este o operatie care aplica un filtru (sau kernel) pe o imagine pentru a extrage anumite caracteristici, cum ar fi marginile, texturile sau formele. Filtrul este o matrice de greutati care se deplaseaza peste imagine si calculeaza o suma ponderata a pixelilor din zona acoperita de filtru. Rezultatul acestei operatii este un nou set de date numit feature map, care contine informatii despre caracteristicile detectate in imagine.
class Conv2d:
    def __init__(self, in_channels, out_channels, kernel_size):
        self.filters = 0.01 * np.random.randn(out_channels, in_channels, kernel_size, kernel_size)
        self.bias = np.zeros((out_channels, 1)) # initializam bias-ul pentru fiecare filtru cu zero
        self.kernel_size = kernel_size

    def forward(self, x):
        self.x = x
        N, C, H, W = x.shape # N reprezinta numarul de imagini, C reprezinta numarul de canale, H reprezinta inaltimea imaginii, iar W reprezinta latimea imaginii
        F, _, kH, kW = self.filters.shape # F reprezinta numarul de filtre, kH reprezinta inaltimea filtrului, iar kW reprezinta latimea filtrului
        out_H = H - kH + 1 # calculam inaltimea iesirii dupa aplicarea filtrului, adica inaltimea imaginii minus inaltimea filtrului plus 1 (deoarece filtrul se poate aplica doar pana la ultima pozitie in care incape complet pe imagine)
        out_W = W - kW + 1 # calculam latimea iesirii dupa aplicarea filtrului, adica latimea imaginii minus latimea filtrului plus 1 (deoarece filtrul se poate aplica doar pana la ultima pozitie in care incape complet pe imagine)
        out = np.zeros((N, F, out_H, out_W)) # initializam matricea de iesire cu zerouri, avand dimensiunea (N, F, out_H, out_W) pentru a stoca rezultatele convolutiei pentru fiecare imagine si fiecare filtru

        for f in range(F):
            for i in range(out_H):
                for j in range(out_W):
                    out[:, f, i, j] = np.sum(
                        x[:, :, i:i+kH, j:j+kW] * self.filters[f], # aplicam filtrul pe patch-ul corespunzator din imagine, adica extragem un patch de dimensiunea filtrului din fiecare imagine si il inmultim element cu element cu filtrul
                        axis=(1, 2, 3) # sumam rezultatele pentru toate canalele, inaltimea si latimea patch-ului pentru a obtine o singura valoare pentru fiecare imagine si fiecare filtru
                    ) + self.bias[f]
        return out

    # calculam cat trebuie modificat fiecare filtru pentru a reduce eroarea de iesire, cat trebuie modificat bias-ul pentru fiecare filtru si propagam eroarea inapoi spre input pentru a fi folosita in straturile anterioare
    def backward(self, d_out, lr):
        N, C, H, W = self.x.shape
        F, _, kH, kW = self.filters.shape
        out_H, out_W = d_out.shape[2], d_out.shape[3]

        d_filters = np.zeros_like(self.filters) # cat trebuie modificat fiecare filtru
        d_bias = np.zeros_like(self.bias)
        d_x = np.zeros_like(self.x) # propagam eroare inapoi spre input

        for f in range(F):
            for i in range(out_H):
                for j in range(out_W):
                    # cat a contribuit fiecare filtru la eroarea de iesire pentru fiecare patch
                    d_filters[f] += np.sum(
                        self.x[:, :, i:i+kH, j:j+kW] * d_out[:, f, i, j][:, None, None, None], # inmultim patch-ul corespunzator din fiecare imagine cu eroarea de iesire pentru filtrul respectiv
                        axis=0 # sumam rezultatele pentru toate imaginile pentru a obtine cat trebuie modificat filtrul
                    )
                    # propagam eroarea inapoi spre input
                    d_x[:, :, i:i+kH, j:j+kW] += self.filters[f] * d_out[:, f, i, j][:, None, None, None]

                d_bias[f] = np.sum(d_out[:, f])

        # actualizam filtrele
        self.filters -= lr * d_filters
        self.bias -= lr * d_bias
        return d_x # trimitem eroarea propagata inapoi spre input pentru a fi folosita in straturile anterioare

# Dupa convolutie avem un feature map. MaxPool reduce dimensiunea acestui feature map prin impartirea lui in patch-uri si pastrarea valorii maxime din fiecare patch. Acest lucru ajuta la reducerea numarului de parametri si la prevenirea overfitting-ului, dar pastreaza informatiile importante despre caracteristicile detectate in imagine. De exemplu, daca un filtru a detectat o margine intr-un patch, max pooling-ul va pastra aceasta informatie chiar daca pozitia exacta a marginii nu mai este cunoscuta.
# Maximul reprezinta cat de puternic a fost detectat un pattern in acea zona
class MaxPool2d:
    def __init__(self, size=2):
        self.size = size

    def forward(self, x):
        self.x = x # stocam inputul pentru a putea calcula backward-ul
        N, C, H, W = x.shape # N reprezinta numarul de imagini, C reprezinta numarul de canale, H reprezinta inaltimea imaginii, iar W reprezinta latimea imaginii
        s = self.size # dimensiunea ferestrei de pooling

        out = np.zeros((N, C, H // s, W // s)) # initializam matricea de iesire cu zerouri, avand dimensiunea (N, C, H//s, W//s) pentru a stoca rezultatele pooling-ului pentru fiecare imagine si fiecare canal

        for i in range(H // s):
            for j in range(W // s):
                patch = x[:, :, i*s:i*s+s, j*s:j*s+s] # extragem un patch de dimensiunea ferestrei de pooling din fiecare imagine pentru fiecare canal
                out[:, :, i, j] = np.max(patch, axis=(2, 3)) # aplicam functia de max pooling pe patch-ul extras, adica luam valoarea maxima din patch pentru fiecare imagine si fiecare canal si o stocam in matricea de iesire

        return out

    # Eroarea se propaga doar spre pixelul care a fost maximul
    def backward(self, d_out):
        N, C, H, W = self.x.shape
        s = self.size
        d_x = np.zeros_like(self.x) # initializam matricea de eroare pentru input cu zerouri

        for i in range(H // s):
            for j in range(W // s):
                patch = self.x[:, :, i*s:i*s+s, j*s:j*s+s] # extragem acelasi patch ca in forward pentru a identifica pozitia valorii maxime

                max_val = np.max(patch, axis=(2, 3), keepdims=True) # identificam valoarea maxima din patch pentru fiecare imagine si fiecare canal
                mask = (patch == max_val) # cream o masca care are valoarea True doar la pozitia valorii maxime din patch pentru fiecare imagine si fiecare canal

                d_x[:, :, i*s:i*s+s, j*s:j*s+s] += mask * d_out[:, :, i, j][:, :, None, None] # propagam eroarea doar la pozitia valorii maxime din patch pentru fiecare imagine si fiecare canal

        return d_x

# ReLU taie tot ce e negativ, valorile negative din feature map inseamna ca filtrul nu a detectat nimic in zona aia
class ReLU:
    def forward(self, x):
        self.x = x # stocam inputul pentru a putea calcula backward-ul
        return np.maximum(0, x) # aplicam functia de activare ReLU, adica inlocuim valorile negative cu zero

    def backward(self, d_out):
        return d_out * (self.x > 0) # gradientul trece doar unde inputul era pozitiv

class Linear:
    def __init__(self, in_features, out_features):
        self.weights = 0.01 * np.random.randn(in_features, out_features) # initializam matricea de greutati cu valori mici aleatoare
        self.bias = np.zeros((1, out_features)) # initializam bias-ul cu zero

    def forward(self, x):
        self.x = x # stocam inputul pentru a putea calcula backward-ul
        return np.dot(x, self.weights) + self.bias # aplicam transformarea liniara pe input, adica inmultim inputul cu matricea de greutati si adaugam bias-ul

    def backward(self, d_out, lr):
        d_weights = np.dot(self.x.T, d_out) # calculam gradientul pentru matricea de greutati
        d_bias = np.sum(d_out, axis=0, keepdims=True) # calculam gradientul pentru bias
        d_x = np.dot(d_out, self.weights.T) # calculam gradientul pentru input

        # actualizam matricea de greutati si bias-ul folosind gradientii calculati si rata de invatare
        self.weights -= lr * d_weights
        self.bias -= lr * d_bias

        return d_x # trimitem eroarea propagata inapoi spre input pentru a fi folosita in straturile anterioare

class CNN:
    def __init__(self, num_classes=2):
        self.conv = Conv2d(3, 8, kernel_size=3) # strat de convolutie cu 3 canale de intrare (RGB), 8 filtre si dimensiunea filtrului de 3x3
        self.relu1 = ReLU() # strat de activare ReLU
        self.pool = MaxPool2d(size=2) # strat de max pooling cu dimensiunea ferestrei de pooling de 2x2
        self.fc = Linear(8 * 7 * 7, num_classes) # strat liniar care transforma feature map-ul rezultat din stratul de pooling intr-un vector de dimensiune num_classes (numarul de clase)

    def softmax(self, x):
        exp = np.exp(x - np.max(x, axis=1, keepdims=True))
        return exp / np.sum(exp, axis=1, keepdims=True)

    def ce_loss(self, probs, labels):
        n = labels.shape[0]
        return -np.sum(np.log(probs[range(n), labels] + 1e-9)) / n

    def forward(self, x):
        x = self.conv.forward(x)
        x = self.relu1.forward(x)
        x = self.pool.forward(x)
        self.shape_before_flat = x.shape
        x = x.reshape(x.shape[0], -1)  # flatten
        x = self.fc.forward(x)
        x = self.softmax(x)
        return x

    def backward(self, probs, labels, lr):
        n = labels.shape[0]
        d_out = probs.copy()
        d_out[range(n), labels] -= 1
        d_out /= n

        d_out = self.fc.backward(d_out, lr)
        d_out = d_out.reshape(self.shape_before_flat)  # unflatten
        d_out = self.pool.backward(d_out)
        d_out = self.relu1.backward(d_out)
        self.conv.backward(d_out, lr)

    def fit(self, X, y, lr=0.01, epochs=5, batch_size=32):
        n = X.shape[0]

        for epoch in range(epochs):
            # amestecam datele la fiecare epoca
            indices = np.random.permutation(n)
            X = X[indices]
            y = y[indices]

            epoch_loss = 0
            n_batches = n // batch_size

            for i in range(0, n, batch_size):
                # decupam batch-ul curent
                X_batch = X[i:i + batch_size]
                y_batch = y[i:i + batch_size]

                # forward + backward doar pe batch
                probs = self.forward(X_batch)
                epoch_loss += self.ce_loss(probs, y_batch)
                self.backward(probs, y_batch, lr)

            print(f"Epoch {epoch + 1}, loss: {epoch_loss / n_batches:.4f}")

    def predict(self, X):
        probs = self.forward(X)
        return np.argmax(probs, axis=1)