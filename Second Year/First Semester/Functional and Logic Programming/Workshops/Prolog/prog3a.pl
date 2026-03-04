% Sa se scrie un predicat care transforma o lista intr-o multime, in
% ordinea primei aparitii. Exemplu: [1,2,3,1,2] e transformat in [1,2,3].
exista([X|_], X) :-
    true.
exista([_|T], X) :-
    exista(T, X).

transforma([], _, []).

transforma([H|T], V, [H|Rez]) :-
    \+ exista(V, H), !,
    transforma(T, [H|V], Rez).

transforma([_|T], V, Rez) :-
    transforma(T, V, Rez).