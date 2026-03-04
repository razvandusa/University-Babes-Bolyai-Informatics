from scipy.stats import uniform
from matplotlib.pyplot import bar, show, hist, grid, legend, xticks, yticks

# Functie pentru generarea de valori discrete pe baza distributiei date
# valori = lista valorilor posibile
# probabilitati = probabilitatile asociate valorilor
# N = numarul de valori generate
def my_rand_vals(valori, probabilitati,N): 
    X=[]
    # generam N numere uniforme pe intervalul (0,1)
    U = uniform.rvs(size=N)
    for i in range(N):
        # cautam in ce interval de probabilitate cade U[i]
        pozitie = 0 
        sum_prob = probabilitati[0]
        # avansam pana cand U[i] este acoperit de suma cumulata
        while U[i] > sum_prob:         #  U[i] <= sum_prob
            pozitie+=1
            sum_prob+=probabilitati[pozitie]      
        # adaugam valoarea corespunzatoare pozitiei gasite
        X.append(valori[pozitie])      # atunci X.append(valori[pozitie-1])
    return X

valori, probabilitati = range(4), (0.46, 0.40, 0.10, 0.04)

# generam 1000 de valori conform distributiei discrete
data = my_rand_vals(valori,probabilitati,1000)
# definim marginile bin-urilor pentru histograma
bin_edges = [i+0.5 for i in range(-1,4)]
# histograma frecventelor relative din esantion
hist(data, bin_edges, density = True, rwidth=0.9, color ='green', 
     edgecolor='black', alpha = 0.5, label='frecvente relative')

# distributia teoretica pentru comparatie
distribution = dict([(k,probabilitati[k]) for k in range(4)])
# plotam barele pentru probabilitatile teoretice
bar(distribution.keys(),distribution.values(), width=0.85,color='red',
    edgecolor='black',alpha=0.6, label='probabilitati')

# etichetele axei X
xticks(ticks=range(4),labels=("0","A","B","AB"))
# etichetele axei Y
yticks([k/100 for k in range(0,55,5)])
legend(loc='upper right')
# afisam grid pentru claritate
grid()
show()