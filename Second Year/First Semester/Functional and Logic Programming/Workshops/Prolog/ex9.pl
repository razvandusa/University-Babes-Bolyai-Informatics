% Genereaza numere intre Start si End
% model de flux : (i, i, o)
% intre(x, y) = x, daca x = y
%             = intre(x + 1, y), altfel
intre(Start, End, Start) :-
    Start =< End.
intre(Start, End, Val) :-
    Start < End,
    StartNou is Start + 1,
    intre(StartNou, End, Val).

% Adauga un element la sfarsitul listei
% model de flux : (i, i, o)
% adauga(e, l1...ln) = e, daca lista este vida
%                    = l1 (+) adauga(e, l2...ln)
adauga_sf([], Elem, [Elem]).
adauga_sf([H|T], Elem, [H|Rezultat]) :-
    adauga_sf(T, Elem, Rezultat).

% model de flux : (i, o)
% genereaza(N, permutare) = bkt(intre(1, N), 1, intre(1, N), intre(1, N), N)
genereaza(N, Permutare) :-
    N >= 1,
    % Alegem primul numar de start [1-N].
    intre(1, N, Start),
    % Parametri: ListaCurenta, Lungime, MinCurent, MaxCurent, N, RezultatFinal
    bkt([Start], 1, Start, Start, N, Permutare).

% Am ajuns la lungimea N, ne oprim.
bkt(Lista, N, _, _, N, Lista) :- !.

% model de flux : (i, i, i, i, i, o)
% bkt(l1...ln, k, min, max, n) = l1...ln, k = n
%                              = bkt(l1...ln (+) min - 1, k + 1, min - 1, max, n), daca min > 1
%                              = bkt(l1...ln (+) max + 1, k + 1, min, max + 1, n), daca max < n
bkt(Lista, Lungime, Min, Max, N, Rezultat) :-
    Lungime < N,
    (
        % Incercam sa mergem in jos
        (
            NouVal is Min - 1,
            NouVal >= 1,
            NouMin is NouVal,
            NouMax is Max
        )
        ;
        % Incercam sa mergem in sus
        (
            NouVal is Max + 1,
            NouVal =< N,
            NouMax is NouVal,
            NouMin is Min
        )
    ),

    adauga_sf(Lista, NouVal, ListaNoua),

    NouaLungime is Lungime + 1,

    bkt(ListaNoua, NouaLungime, NouMin, NouMax, N, Rezultat).
