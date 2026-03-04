% specificatii : adauga1(L, Rezultat) - adauga 1 dupa fiecare element par
% model de flux : (i, o)
adauga1([], []).
adauga1([H|T], [H,1|R]) :-
    0 is H mod 2, !,
    adauga1(T, R).
adauga1([H|T], [H|R]) :-
    adauga1(T, R).

/*
Cazuri de testare:
?- adauga1([2,5,6,7], R).
R = [2, 1, 5, 6, 1, 7].

?- adauga1([3,5,7], R).
R = [3, 5, 7]

?- adauga1([2,4,6], R).
R = [2, 1, 4, 1, 6, 1]

?- adauga1([], R).
R = [].
*/
