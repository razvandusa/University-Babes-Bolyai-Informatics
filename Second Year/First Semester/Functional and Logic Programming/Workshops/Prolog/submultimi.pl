% model matematic : submultimi(l1...ln) = multimea vida, daca l este vida
%                                       = l1 (+) submultimi(l2...ln)
%                                         submultimi(l2...ln)
% predicatul submultimi(L:list, Rez:list) genereaza multimea tuturor submultimilor listei L si pune rezultatul in lista Rez
% model de flux : submultimi(i, o), nedeterminist
submultimi([], []).
submultimi([H|L], [H|Rez]) :-
    submultimi(L, Rez).
submultimi([_|T], Rez) :-
    submultimi(T, Rez).

toateSubmultimi(L, LRez) :-
    findall(S, submultimi(L, S), LRez).