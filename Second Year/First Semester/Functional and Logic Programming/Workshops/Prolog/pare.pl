% model matematic : pare(l1...ln) = multimea vida, daca l e vida
%                                   l1 (+) pare(l2...ln), daca l1 par
%                                   pare(l2...ln), altfel
% predicatul pare(L:list, LRez:list) construieste lista LRez in care sunt introduse doar elementele pare a listei L
% model de flux : fact(i, o) - determinist
pare([],[]).
pare([H|T],[H|LRez]) :-
    H mod 2 =:= 0,
    pare(T,LRez).
pare([H|T],LRez) :-
    H mod 2 =:= 1,
    pare(T,LRez).