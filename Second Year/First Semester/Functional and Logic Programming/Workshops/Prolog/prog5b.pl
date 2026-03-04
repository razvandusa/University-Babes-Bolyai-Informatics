%Definiti un predicat care, dintr-o lista de atomi, produce o lista de
%perechi (atom n), unde atom apare in lista initiala de n ori. De ex:
%numar([1, 2, 1, 2, 1, 3, 1], X) va produce X = [[1, 4], [2, 2], [3, 1]].
numar_aparitii([], _, 0).
numar_aparitii([H|T], Element, Count) :-
    H =:= Element, !,
    numar_aparitii(T, Element, PrevCount),
    Count is PrevCount + 1.
numar_aparitii([_|T], Element, Count) :-
    numar_aparitii(T, Element, Count).

exista(X,[X|_]).
exista(X,[_|T]) :-
    exista(X,T).

produce_lista([], _, [], _).

produce_lista([H|T], CopieLista, Rezultat, Vizitat) :-
    exista(H, Vizitat), !,
    produce_lista(T, CopieLista, Rezultat, Vizitat).

produce_lista([H|T], CopieLista, [[H,Cnt]|Rezultat], Vizitat) :-
    numar_aparitii(CopieLista, H, Cnt),
    produce_lista(T, CopieLista, Rezultat, [H|Vizitat]).
