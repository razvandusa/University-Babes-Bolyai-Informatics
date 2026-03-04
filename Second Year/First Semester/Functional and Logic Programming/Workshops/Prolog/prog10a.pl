interclasare([], _, _, _, []).

interclasare([H|T], Element, Curent, Indice, [H,Element|Rez]) :-
    Indice =:= Curent, !,
    CurentNou is Curent + 1,
    interclasare(T, Element, CurentNou, Indice, Rez).

interclasare([H|T], Element, Curent, Indice, [H|Rez]) :-
    CurentNou is Curent + 1,
    interclasare(T, Element, CurentNou, Indice, Rez). 

exec(Lista, Element, N, Rez) :-
    interclasare(Lista, Element, 1, N, Rez).