% model matematic : adaug(e,l1,l2...ln) = e daca l este vida
%                                       = l1 (+) adaug(e,l2,l3...ln), altfel
% predicatul adaug(E:element, L:list, LRez:list) adauga elementul E la sfarsitul unei liste
% model de flux : adaug(i, i, o) - determinist
adaug(E, [], [E]).
adaug(E, [H|T], [H|LRez]) :-
    adaug(E, T, LRez).