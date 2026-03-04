% model matematic combinari(l1...ln, k) = l1, daca k = 1
%                                         combinari(l2...ln, k)
%                                         l1 (+) combinari(l2...ln, k-1), daca k > 1
% predicatul comb(L:list, k:integer, C:list) determina toate combinarile cu k elemente dintr-o multime nevida reprezentata sub forma unei liste
% si salveaza fiecare submultime in C
% model de flux : (i, i, o) nedeterminist
comb([H|_], 1, [H]).
comb([H|T], K, [H|C]) :-
    K > 1,
    K1 is K - 1,
    comb(T, K1, C).
comb([_|L], K, C) :-
    comb(L, K, C).