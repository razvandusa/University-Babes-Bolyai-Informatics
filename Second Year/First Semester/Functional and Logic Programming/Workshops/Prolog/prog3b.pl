% Sa se scrie o functie care descompune o lista de numere intr-o lista de
% forma [ lista-de-numere-pare lista-de-numere-impare] (deci lista cu doua
% elemente care sunt liste de intregi), si va intoarce si numarul
% elementelor pare si impare.

lista_para([],[]).
lista_para([H|T], [H|Rez]) :-
    0 is H mod 2,
    lista_para(T, Rez).
lista_para([H|T], Rez) :-
    1 is H mod 2,
    lista_para(T, Rez).

lista_impara([],[]).
lista_impara([H|T], [H|Rez]) :-
    1 is H mod 2,
    lista_impara(T, Rez).
lista_impara([H|T], Rez) :-
    0 is H mod 2,
    lista_impara(T, Rez).

numara_elemente([], 0).
numara_elemente([_|T], Cnt) :-
    numara_elemente(T, CntNou),
    Cnt is CntNou + 1.

descompune(Lista, [ListePare, ListeImpare], NrPare, NrImpare) :-
    lista_para(Lista, ListePare),
    lista_impara(Lista, ListeImpare),
    numara_elemente(ListePare, NrPare),
    numara_elemente(ListeImpare, NrImpare).