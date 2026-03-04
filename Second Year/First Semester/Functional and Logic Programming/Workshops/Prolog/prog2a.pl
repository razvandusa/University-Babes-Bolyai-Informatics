%Sa se scrie un predicat care determina cel mai mic multiplu comun al
%elementelor unei liste formate din numere intregi.

%cmmd(15,5,R) => R=5 
cmmd(A,0,A).
cmmd(A,B,R) :-
    B \= 0,
    Rest is A mod B,
    cmmd(B, Rest, R).

mmc_doua(A ,B , M) :-
    cmmd(A, B, G),
    M is (A * B) // G.

%mmc([2,3,4],R) => R=12
mmc([],1).
mmc([X], X).
mmc([H|T], R) :-
    mmc(T, R1),
    mmc_doua(H, R1, R).