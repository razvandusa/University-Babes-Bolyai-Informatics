% model matematic : fact(n) = fact_aux(n, 1, 1)
% predicatul fact(N:integer, F:integer) salveaza factorialul lui N in F apeland fact_aux(N, F, 1, 1)
% model de flux : fact(i, o) - determinist
fact(N, F) :-
    fact_aux(N, F, 1, 1).

% model matematic : fact_aux(n, i, P) = fact_aux(n, i + 1, P * (i + 1)), daca i < n
%                                     = P, altfel 
% predicatul fact_aux(N:integer, F:integer, I:integer, P:integer) calculeaza factorialul lui N si il salveaza in variabila P
% model de flux : fact_aux(i, i, i, i)
fact_aux(N, F, N, F).
fact_aux(N, F, I, P) :-
    I < N,
    I1 is I + 1,
    P1 is P * I1,
    fact_aux(N, F, I1, P1).