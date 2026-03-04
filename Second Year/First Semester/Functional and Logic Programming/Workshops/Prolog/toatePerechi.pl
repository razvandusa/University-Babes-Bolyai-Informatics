% model matematic : pereche(e,l1...ln) = (e,l1), e < l1
%                                      = pereche(e,l2...ln)
% predicatul pereche(E:integer, L:list, LRez:list) produce perechile 
% in ordine crescatoare intre elementul e si elementele listei 
% model de flux : pereche(i, i, o) - determinist
pereche(E,[H|_],[E,H]) :-
    E < H.
pereche(E,[_|T],LRez) :-
    pereche(E,T,LRez).

perechi([H|T],P) :-
    pereche(H,T,P).
perechi([_|T],P) :-
    perechi(T,P).

toatePerechi(L,LRez) :-
    findall(X,perechi(L,X),LRez).