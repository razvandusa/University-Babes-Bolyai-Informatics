%Sa se scrie un predicat care elimina dintr-o lista toate elementele care
%se repeta (ex: l=[1,2,1,4,1,3,4] => l=[2,3])

numar_aparitii([], _, 0).
numar_aparitii([H|T], Elem, Contor) :-
    H =:= Elem, !,
    numar_aparitii(T, Elem, ContorPrev),
    Contor is ContorPrev + 1.
numar_aparitii([_|T], Elem, Contor) :-
    numar_aparitii(T, Elem, Contor).

elimina([], _, []).

elimina([H|T], CopieLista, [H|Rezultat]) :-
    numar_aparitii(CopieLista, H, Contor),
    Contor =:= 1, !,
    elimina(T, CopieLista, Rezultat).

elimina([_|T], CopieLista, Rezultat) :-
    elimina(T, CopieLista, Rezultat).

elimina_predicat(Lista, Rezultat) :-
    elimina(Lista, Lista, Rezultat).