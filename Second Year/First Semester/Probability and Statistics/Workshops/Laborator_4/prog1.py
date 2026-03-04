from scipy.stats import bernoulli, binom
from matplotlib.pyplot import bar, show, hist, grid, legend, xticks

def mers_aleator_axa(nr_pasi, p):          # p: prob. deplasare dreapta
    pozitii = [0]                           # pozitii la fiecare pas
    for _ in range(nr_pasi):       
        x = bernoulli.rvs(p)               # 1 cu prob p, 0 altfel
        pas = 2 * x - 1                    # 0/1 -> -1/+1
        pozitii.append(pozitii[-1] + pas)  # adauga pozitia noua
    return pozitii

mers_aleator_axa(10, 0.5)

def sim_mers_aleator_axa(nr_pasi, p, nr_sim=1000):
    pozitii_finale = [mers_aleator_axa(nr_pasi, p)[-1] for _ in range(nr_sim)]
    
    bin_edges = [i + 0.5 for i in range(-nr_pasi-1, nr_pasi+1)]
    hist(pozitii_finale, bin_edges, density=True, rwidth=0.9, align='mid',
         edgecolor='black', color='green', alpha=0.3, label='frecvente relative')
    
    distributie = dict([(k - (nr_pasi - k), binom.pmf(k, nr_pasi, p))
                        for k in range(nr_pasi + 1)])
    bar(distributie.keys(), distributie.values(), width=0.6, align='center',
        edgecolor='black', color='red', alpha=0.5, label='probabilitati')
    
    xticks(range(-nr_pasi, nr_pasi + 1))
    legend(loc='upper left')
    grid()
    show()

sim_mers_aleator_axa(10, 0.5)  # simulare mers aleator axa

def sim_mers_aleator_cerc(nr_pasi, nr_pcte, p, nr_sim=1000):
    # pozitia finala modulo nr_pcte (circular)
    pozitii_finale = [mers_aleator_axa(nr_pasi, p)[-1] % nr_pcte for _ in range(nr_sim)]
    
    bin_edges = [i + 0.5 for i in range(-1, nr_pcte)]
    hist(pozitii_finale, bin_edges, density=True, rwidth=0.9, align='mid',
         edgecolor='black', color='green', alpha=0.3, label='frecvente relative')
    
    # probabilitati pe pozitii cerc
    distributie = nr_pcte * [0]
    for k in range(nr_pasi + 1):
        distributie[(k - (nr_pasi - k)) % nr_pcte] += binom.pmf(k, nr_pasi, p)

    bar(range(nr_pcte), distributie, width=0.6, align='center',
        edgecolor='black', color='red', alpha=0.5, label='probabilitati')
    
    xticks(range(nr_pcte))
    legend(loc='upper right')
    grid()
    show()

sim_mers_aleator_cerc(10, 6, 0.5, 2000)