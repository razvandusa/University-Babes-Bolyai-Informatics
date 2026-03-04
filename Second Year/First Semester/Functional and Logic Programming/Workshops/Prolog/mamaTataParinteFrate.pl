%tata(X,Y) reprezinta relatia "Y este tatal lui X"
%mama(X,Y) reprezinta relatia "Y este mama lui X"
mama(a,b).
mama(e,b).
tata(c,d).
tata(a,d).

%parinte(X,Y) reprezinta relatia "Y este parinte lui X"
parinte(X,Y) :- mama(X,Y).
parinte(X,Y) :- tata(X,Y).

%frate(X,Y) reprezinta relatia "X este fratele lui Y"
frate(X,Y) :-
    parinte(X,Z),
    parinte(Y,Z),
    X \= Y.