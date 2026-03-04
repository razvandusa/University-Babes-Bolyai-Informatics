% model matematic : member(e,l1,l2...ln) = fals, daca l e vida
%                                        = adevarat, daca l1 = e
%                                        = member(e,l2,l3...ln), altfel
% predicatul member(E:element, L:list) verifica daca elementul E apartine listei
% model de flux : member(i, i) - determinist, member(o, i) - nedeterminist
member(E,[E|_]).
member(E,[_|T]) :-
    member(E,T).