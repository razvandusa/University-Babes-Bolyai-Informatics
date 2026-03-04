% model matematic insereaza(l1...ln, e) = e (+) l1...ln
%                                       = l1 (+) insereaza(l2...ln)
% predicatul insereaza(E:integer, L:list, LRez:list) insereaza un element pe rand pe toate pozitiile intr-o lista
% model de flux (i, i, o)
insereaza(E, L, [E|L]).
insereaza(E, [H|T], [H|Rez]) :-
    insereaza(E, T, Rez).