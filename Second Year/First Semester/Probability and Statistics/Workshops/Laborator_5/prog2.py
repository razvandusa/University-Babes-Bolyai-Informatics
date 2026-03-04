from scipy.stats import uniform
from math import log
from matplotlib.pyplot import show, hist, grid, legend, xticks, plot
from scipy.stats import expon
# functie care genereaza valori aleatoare cu distributie exponentiala
def my_exp_rand_vals(alpha,N):
    # generam N numere uniforme pe intervalul (0,1)
    U = uniform.rvs(size=N)
    # transformarea inversa pentru distributia exponentiala
    X = [-1/alpha*log(1-U[i]) for i in range(N)]
    return X

# parametrul distributiei (lambda)
alpha = 1/12

# generam 2000 de valori exponentiale
data = my_exp_rand_vals(alpha,2000) 
# histograma esantionului generat
hist(data, bins=12, density = True,range=(0,60))

# valori pe axa X pentru densitatea teoretica
x = range(60)
# densitatea exponentiala teoretica pentru comparatie
plot(x,expon.pdf(x,loc=0,scale=1/alpha),'r-')

# etichete pe axa X
xticks(range(0,60,5))
# afisam grid
grid()
show()

# probabilitatea estimata P(X >= 5) din esantion
sum([x>=5 for x in data])/len(data)

# probabilitatea teoretica P(X >= 5)
1-expon.cdf(5,loc=0,scale=1/alpha)

print("Probabilitate estimata")
print(sum([x>=5 for x in data])/len(data))
print("Probabilitate teoretica")
print(1-expon.cdf(5,loc=0,scale=1/alpha))