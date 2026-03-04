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

%toti(X, L) reprezinta relatia "X este frate cu cei din lista L"
toti(X, L) :-
    %findall are urmatoarele argumente:
    %primul argument care specifica argumentul care trebuie colectat in lista
    %al doilea argument care specifica predicatul de rezolvat
    %al treilea argument care specifica lista in care se vor colecta solutiile
    findall(Y,frate(X,Y),L).