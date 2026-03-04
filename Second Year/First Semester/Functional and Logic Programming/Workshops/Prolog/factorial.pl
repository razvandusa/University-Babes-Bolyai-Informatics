% model matematic : fact(N) = 1, daca N = 0
%                           = N * fact(N - 1), N > 0
% predicatul fact(N:element, F:element) determina factorialul numarului N.
% model de flux : fact(i,o), fact(i, i) - determinist
fact(0, 1).
fact(N, F) :-
    N > 0,
    N1 is N - 1,
    fact(N1, F1),
    F is N * F1.
