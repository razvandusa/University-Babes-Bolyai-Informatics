%Sa se scrie un predicat care elimina primele 3 aparitii ale unui element
%intr-o lista. Daca elementul apare mai putin de 3 ori, se va elimina de
%cate ori apare.

eliminareElement([], _, _, []).

eliminareElement([H|T], Cnt, Element, Rezultat) :-
    Element = H,
    Cnt < 3, !,
    Cnt1 is Cnt + 1,
    eliminareElement(T, Cnt1, Element, Rezultat).

eliminareElement([H|T], Cnt, Element, [H|Rezultat]) :-
    eliminareElement(T, Cnt, Element, Rezultat).

eliminare(Lista, Element, Rezultat) :-
    eliminareElement(Lista, 0, Element, Rezultat).