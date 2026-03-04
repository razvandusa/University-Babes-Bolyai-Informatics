%Sa se elimine toate aparitiile elementului maxim dintr-o lista de numere
%intregi.

maxim([], 0).
maxim([X], X).
maxim([H|T], Max) :-
    maxim(T, MaxC),
    (H > MaxC -> Max = H ; Max = MaxC).

eliminare_element([], _, []).

eliminare_element([H|T], Element, Rezultat) :-
    H =:= Element, !,
    eliminare_element(T, Element, Rezultat).

eliminare_element([H|T], Element, [H|Rezultat]) :-
    eliminare_element(T, Element, Rezultat).

eliminare_max(Lista, Rezultat) :-
    maxim(Lista, Max),
    eliminare_element(Lista, Max, Rezultat).