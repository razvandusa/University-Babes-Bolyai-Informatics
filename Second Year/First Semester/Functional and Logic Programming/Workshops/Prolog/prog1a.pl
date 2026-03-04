%Sa se scrie un predicat care intoarce diferenta a doua multimi.

%exista(X, L) => verifica daca X este in L
exista(_, []) :- 
    false.
exista(X, [X|L]) :-
    true.
exista(X, [_|T]) :-
    exista(X,T).
%diferenta(A, B, D) => D = elementele din A care nu apar in B
diferenta([], _, []).
diferenta([H|T], B, R) :-
    exista(H,B), !,
    diferenta(T, B, R).
diferenta([H|T], B, [H|R]) :-
    \+ exista(H,B),
    diferenta(T, B, R).