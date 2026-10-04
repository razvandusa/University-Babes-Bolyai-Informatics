#In mod standard:
p = 0.7
if p >= 0.5:
    clasa = 1
else:
    clasa = 0
# clasificam exemplul in clasa 1


# Prag mai mic (ex: 0.3)
if p >= 0.3:
    clasa = 1
else:
    clasa = 0
# clasificatorul va prezice mai usor clasa pozitiva
# - cresc True Positives
# - cresc False Positives

# Prag mai mare (ex: 0.7)
if p >= 0.7:
    clasa = 1
else:
    clasa = 0
# clasificatorul va prezice mai usor clasa negativa
# - cresc False Negatives
# - cresc True Negatives

# calitatea clasificatorului pentru diferite valori ale pragului poate fi apreciata folosind:
# - accuracy = (TP + TN) / (TP + TN + FP + FN) = correct_predictions / total_predictions
# - precision = TP / (TP + FP) = how accurate the positive predictions are
# - recall = TP / (TP + FN) = the coverage of actual positive sample