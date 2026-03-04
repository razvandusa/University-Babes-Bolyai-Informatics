% candidat(A:integer, B:integer, C:integer)
% model matematic : 1. candidat(a, b) = a, daca a <= b
%                   2. candidat(a + 1, b)
% model de flux : candidat(i, i ,o)
candidat(A, B, A) :-
    A =< B.
candidat(A, B, C) :-
    A < B,
    A1 is A + 1,
    candidat(A1, B, C).

% submultime(N:integer, LG: integer, S:integer, A:integer, B:integer, Col:list, Rez:list)
% model matematic : submultime(n, lg, s, a, b, col) = col, lg = n, s % 2 = 0
%                               = submultime(n, lg + 1, s + c, a, b, c (+) col), c = candidat(a, b)
% model de flux : submultime(i, i, i, i, i, o) - determinist
submultime(N, N, S, _, _, Col, Col) :-
    S mod 2 =:= 0.

submultime(N, LG, S, A, B, [H|Col], Rez) :-
    LG =< N,
    candidat(A, B, C),
    C < H,
    S1 is S + C,
    LG1 is LG + 1,
    submultime(N, LG1, S1, A, B, [C|[H|Col]], Rez).

% submultime(N:integer, A:integer, B:integer, Rez:list)
% model matematic : submultime(n, a, b) = submultime(n, 1, c, a, b, [c]), c = candidat(a, b)
% model de flux : submultime(i, i, i, o) - nedeterminist 
submultime_main(N, A, B, Rez) :-
    candidat(A, B, C),
    submultime(N, 1, C, A, B, [C], Rez).

% submultime(N:integer, A:integer, B:integer, L:list)
% model matematic : submultime(n, a, b) = U submultime(n, a, b)
% model de flux : submultime(i, i, i, o) - determinist
submultime_main_main(N, A, B, L) :-
    findall(Rez ,submultime_main(N, A, B, Rez), L).