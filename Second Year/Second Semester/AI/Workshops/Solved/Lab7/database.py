import numpy as np
from utils import apply_sepia
from tensorflow.keras.datasets import cifar10

def create_dataset(patch_size=16):
    (images, _), _ = cifar10.load_data() # incarcarea dataset-ului CIFAR-10
    images = images / 255.0 # Normalizam imaginile

    inputs, outputs = [], []

    for img in images:
        h, w, _ = img.shape # al treilea _ reprezinta numarul de canale (RGB)
        for i in range(0, h - patch_size, patch_size):
            for j in range(0, w - patch_size, patch_size):
                patch = img[i:i+patch_size, j:j+patch_size] # extragem un patch din imagine

                sepia_patch = apply_sepia(patch) # aplicam filtrul sepia pe patch
                inputs.append(patch.flatten()) # adaugam patch-ul normalizat la lista de intrari
                outputs.append(0)

                inputs.append(sepia_patch.flatten())
                outputs.append(1)

    outputNames = ['normal', 'sepia']

    return inputs, outputs, outputNames