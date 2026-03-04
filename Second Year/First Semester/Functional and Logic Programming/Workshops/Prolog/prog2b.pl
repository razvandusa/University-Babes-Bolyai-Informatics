% Predicat care adauga Val dupa elementele 1,2,4,8,... din Lista
adauga([], _, _, _, []).

adauga([H|T], Val, Ind, Cnt, [H,Val|R]) :-
    Ind =:= Cnt, !,
    IndNou is Ind + 1,
    CntNou is Cnt * 2,
    adauga(T, Val, IndNou, CntNou, R).

adauga([H|T], Val, Ind, Cnt, [H|R]) :-
    Ind =\= Cnt,
    IndNou is Ind + 1,
    adauga(T, Val, IndNou, Cnt, R).