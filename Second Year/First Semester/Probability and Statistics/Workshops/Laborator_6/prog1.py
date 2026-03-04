from matplotlib.pyplot import hist, show, plot
from scipy.stats import expon, randint
from numpy import floor, mean
media = 2
timpi = expon.rvs(scale = media, size = 10000)
hist(timpi, [k for k in range(0,11)], density=True)
plot(range(0,11), [k for k in (expon.pdf([x for x in range(0,11)], scale=media))])
show()

suma = 0.0
contor = 0
for t in timpi:
    suma += randint.rvs(1,11) - floor(t) >= 5
    contor += 1
print("Probabilitatea = ", (suma/contor))