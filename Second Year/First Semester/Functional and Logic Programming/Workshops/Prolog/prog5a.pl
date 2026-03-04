%Sa se scrie un predicat care sterge toate aparitiile unui anumit atom
%dintr-o lista.

sterge([],_,[]).

sterge([H|T], Atom, Rezultat) :-
    H =:= Atom, !,
    sterge(T, Atom, Rezultat).

sterge([H|T], Atom, [H|Rezultat]) :-
    H =\= Atom,
    sterge(T, Atom, Rezultat).