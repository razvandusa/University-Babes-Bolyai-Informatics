% model matematic : elimin(e, l1...ln) = l2...ln, l1 = e
%                                        l1 (+) elimin(e, l2...ln)
% predicatul elimin(E:integer, L:list, R:list) sterge un element, pe rand de pe toate pozitiile pe care acesta apare intr-o lista
% model de flux : (i, i, o)
elimin(E, [H|L], L) :-
    E =:= H.
elimin(E, [H|L], [H|R]) :-
    elimin(E, L, R).