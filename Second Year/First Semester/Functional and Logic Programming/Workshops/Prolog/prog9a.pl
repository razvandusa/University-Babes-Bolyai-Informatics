%Sa se scrie un predicat care intoarce intersectia a doua multimi.
exista(X, [X|_]).
exista(X, [_|T]) :-
    exista(X, T).

intersectia([], _, []).
intersectia(_, [], []).
intersectia([], [], []).
intersectia([H|T], Lista, [H|Rez]) :-
    exista(H, Lista), !,
    intersectia(T, Lista, Rez).
intersectia([_|T], Lista, Rez) :-
    intersectia(T, Lista, Rez).
