% Genereaza numere intre Start si End
% model de flux : (i, i, o)
intre(Start, End, Start) :- 
    Start =< End.
intre(Start, End, Val) :- 
    Start < End,
    StartNou is Start + 1,
    intre(StartNou, End, Val).

% Adauga un element la sfarsitul listei
% model de flux : (i, i, o)
adauga_sf([], Elem, [Elem]).
adauga_sf([H|T], Elem, [H|Rezultat]) :-
    adauga_sf(T, Elem, Rezultat).

% model de flux : (i, o)
genereaza(N, Permutare) :-
    N >= 1,
    % Alegem primul numar de start [1-N].
    intre(1, N, Start),
    % Parametri: ListaCurenta, Lungime, MinCurent, MaxCurent, N, RezultatFinal
    bkt([Start], 1, Start, Start, N, Permutare).

% Am ajuns la lungimea N, ne oprim.
bkt(Lista, N, _, _, N, Lista) :- !.

% model de flux : (i, i, i, i, i, o)
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