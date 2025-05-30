def sortare(lista,*,key = None):
    if key is None:
        key = lambda piesa : (piesa.regizor, piesa.titlu)
    for i in range(0,len(lista)):
        for j in range(i+1,len(lista)):
            if key(lista[i]) > key(lista[j]):
                lista[i], lista[j] = lista[j], lista[i]