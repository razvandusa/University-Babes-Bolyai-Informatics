% model matematic : suma(l1...ln, s) = suma(l2...ln, s + l1), daca l1 numar
%                                    = suma(l2...ln), daca l1 nu e numar
% predicatul suma(L:list, S:number) produce suma elementelor care sunt numere
% model de flux : suma(i, o) - determinist
suma([],0).
suma([H|T],S) :-
    number(H),
    !,
    suma(T,S1),
    S is S1 + H.
suma([H|T],S) :-
    is_list(H),
    !,
    suma(H,S1),
    suma(T,S2),
    S is S1 + S2.
suma([_|T],S) :-
    suma(T,S).