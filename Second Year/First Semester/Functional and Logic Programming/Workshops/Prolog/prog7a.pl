%Sa se scrie un predicat care intoarce reuniunea a doua multimi.
exista(Element, [Element|_]).

exista(Element, [_|T]) :-
    exista(Element, T).


reuniune([], Lista, Lista).

reuniune([H|T], Lista, Rezultat) :-
    exista(H, Lista), !,
    reuniune(T, Lista, Rezultat).

reuniune([H|T], Lista, [H|Rezultat]) :-
    reuniune(T, Lista, Rezultat).