from scipy.stats import hypergeom, geom

nr_sim = 10000

p = sum([hypergeom.pmf(k,49,6,6) for k in range(3,7)])     # Probabilitatea ca un bilet să aibă cel puțin 3 numere corecte.

# Parametrii: 49 bile total, 6 extrase, 6 alese pe bilet, k numere corecte.
# Se calculează probabilitatea de succes pentru distribuția hipergeometrică.

nr_bilete_necastigatoare = geom.rvs(p,size = nr_sim)

# Generează nr_sim valori geometrice cu probabilitatea p, reprezentând bilete necâștigătoare înainte de primul câștigător.

prob_estimata = sum([x>=10 for x in nr_bilete_necastigatoare])/nr_sim

# Estimează probabilitatea ca numărul de bilete necâștigătoare să fie cel puțin 10.

print(f'Probabilitatea estimata: {prob_estimata}')

prob_teoretica=1-geom.cdf(9,p)
print(f'Probabilitatea teoretica: {prob_teoretica}')

# Probabilitatea teoretică ca biletele necâștigătoare să fie 10 sau mai multe (1 - CDF la 9).
