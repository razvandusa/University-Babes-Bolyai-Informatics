% model matematic : inversa(l1...ln) = multimea vida, daca l e vida
%                                      inversa(l2...ln) (+) l1, altfel
% predicatul inversa(L:list, LRez:list) construieste inversa listei LRez in L
% model de flux : fact(i, o) - determinist
inversa([],[]).
inversa([H|T],LRez) :-
    inversa(T,L),
    adauga(H,L,LRez).

% model matematic : adauga(e,l1,l2...ln) = e, daca l e vida
%                                       = l1 (+) adauga(e,l2,l3...ln), altfel
% predicatul adauga(E:integer, L:list, LRez:list) adauga elementul E la sfarsitul
% listei L si salveaza rezultatul in LRez
% model de flux : adauga(i, i, o)
adauga(E, [], [E]).
adauga(E ,[H|T] ,[H|LRez]) :-
    adauga(E, T, LRez).