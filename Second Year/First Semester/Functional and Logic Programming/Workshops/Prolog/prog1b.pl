%Sa se scrie un predicat care adauga intr-o lista dupa fiecare element par valoarea 1.

%adauga([1,2,3],R) => R = [1,2,1,3]
adauga([],[]).
adauga([H|T],[H|R]) :-
    1 is H mod 2, !,
    adauga(T,R).
adauga([H|T],[H,1|R]) :-
    0 is H mod 2,
    adauga(T,R).