%Sa se construiasca lista (m, ..., n), adica multimea numerelor intregi
%din intervalul [m, n].

construire(X, X, [X]).
construire(M, N, []):-
    M > N.
construire(M, N, [M|Rez]):-
    M =< N, !,
    NewM is M + 1,
    construire(NewM, N, Rez).