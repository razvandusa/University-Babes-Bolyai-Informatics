%Sa se scrie un predicat care substituie intr-o lista un element printr-o
%alta lista.
%concateneaza(L1, L2, Rez)
concateneaza([], L, L).
concateneaza([H|T], L, [H|Rez]) :-
    concateneaza(T, L, Rez).

substituie([], _, _, []).
substituie([H|T], Elem, ListaNoua, Rez) :-
    H =:= Elem, !,
    concateneaza(ListaNoua, RezT, Rez),
    substituie(T, Elem, ListaNoua, RezT).

substituie([H|T], Elem, ListaNoua, [H|RezT]) :-
    substituie(T, Elem, ListaNoua, RezT).