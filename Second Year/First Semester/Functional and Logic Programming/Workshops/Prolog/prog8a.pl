%Sa se scrie un predicat care testeaza daca o lista este multime.
exista([X|_],X).
exista([_|T],X) :-
    exista(T,X).

multime([],_).
multime([H|T],Vizitat) :-
    \+ exista(Vizitat,H),
    multime(T,[H|Vizitat]).