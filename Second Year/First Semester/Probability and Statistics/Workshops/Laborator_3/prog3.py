from scipy.stats import binom
from matplotlib.pyplot import bar, hist, grid, legend, show

n = 5
p = 0.6

# a) Generam 1000 de valori aleatoare pentru X
data = binom.rvs(n, p, size=1000)

# Histograma valorilor simulate
hist(data, bins=[i - 0.5 for i in range(n+2)], density=True, rwidth=0.9,
     color='green', edgecolor='black', label='frecvente relative')

x = range(n+1)
bar(x, binom.pmf(x, n, p), width=0.85, color='red', alpha=0.6,
    edgecolor='black', label='probabilitati')

legend(loc='lower left')
grid()
show()

# Estimare empirica (din simulare)
p_empiric = sum((data > 2) & (data <= 5)) / len(data)

# Valoare teoretica
#Formula: P(2 < X <= 5) = P(X <= 5) - P(X <= 2)
p_teoretic = binom.cdf(5, n, p) - binom.cdf(2, n, p)

print(f"P_empiric(2 < X ≤ 5) = {p_empiric:.4f}")
print(f"P_teoretic(2 < X ≤ 5) = {p_teoretic:.4f}")