%Sa se elimine elementul de pe pozitia a n-a a unei liste liniare.

elimina([], _, _, []).

elimina([_|T], Indice, Pozitia, Rezultat) :-
    Indice =:= Pozitia, !,
    IndiceNou is Indice + 1,
    elimina(T, IndiceNou, Pozitia, Rezultat).

elimina([H|T], Indice, Pozitia, [H|Rezultat]) :-
    IndiceNou is Indice + 1,
    elimina(T, IndiceNou, Pozitia, Rezultat).

elimina_elem(Lista, Pozitia, Rezultat) :-
    elimina(Lista, 1, Pozitia, Rezultat).