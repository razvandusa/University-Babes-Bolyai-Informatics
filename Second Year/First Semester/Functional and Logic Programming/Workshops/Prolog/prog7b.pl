%Sa se scrie un predicat care, primind o lista, intoarce multimea
%tuturor perechilor din lista. De ex, cu [a, b, c, d] va produce
%[[a, b], [a, c], [a, d], [b, c], [b, d], [c, d]].
crearePerechiElement(_, _, _, [], []).

crearePerechiElement(PozitieCurenta, PozitieElement, Element, [_|T], Rezultat) :-
    PozitieCurenta =:= PozitieElement, !,
    PozitieCurentaNoua is PozitieCurenta + 1,
    crearePerechiElement(PozitieCurentaNoua, PozitieElement, Element, T, Rezultat).

crearePerechiElement(PozitieCurenta, PozitieElement, Element, [H|T], [[Element,H]|Rezultat]) :-
    PozitieCurentaNoua is PozitieCurenta + 1,
    crearePerechiElement(PozitieCurentaNoua, PozitieElement, Element, T, Rezultat).

dimensiuneLista([], 0).

dimensiuneLista([_|T], Dimensiune) :-
    dimensiuneLista(T, PrevDimensiune),
    Dimensiune is PrevDimensiune + 1.

crearePerechiLista([], [], _, _).
crearePerechiLista([H|T], Lista, [Rez|Rezultat], PozitieCurenta ,Dimensiune) :-
    PozitieCurenta =< Dimensiune,
    crearePerechiElement(1, PozitieCurenta, H, Lista, Rez),
    PozitieCurentaNoua is PozitieCurenta + 1,
    crearePerechiLista(T, Lista, Rezultat, PozitieCurentaNoua, Dimensiune).
crearePerechiLista(_, _, [], PozitieCurenta, Dimensiune) :-
    PozitieCurenta > Dimensiune.

perechiLista(L, Rezultat) :-
    dimensiuneLista(L, Dim),
    crearePerechiLista(L, L, Rezultat, 1, Dim).