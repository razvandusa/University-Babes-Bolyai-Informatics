% specificatii : apartine(Element, Lista) - adevarat daca Element se afla in Lista
% model de flux : (i, i)
apartine(E, [E|_]).
apartine(E, [_|T]) :-
    apartine(E, T).

% specificatii : diferenta(L1, L2, Rezultat) - Rezultat = elementele din L1 care NU apar in L2
% model de flux : (i, i, o)
diferenta([], _, []).
diferenta([H|T], L2, R) :-
    apartine(H, L2), !,
    diferenta(T, L2, R).
diferenta([H|T], L2, [H|R]) :-
    diferenta(T, L2, R).

/*
Cazuri de testare:
?- diferenta([1,2,3,4,5], [2,4,6], R).
R = [1, 3, 5].

?- diferenta([a,b,c], [b], R).
R = [a, c].
*/
