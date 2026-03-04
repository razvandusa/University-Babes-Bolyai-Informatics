% model matematic : concatenare(l11...l1n, l21...l2n) = l2, daca l1 vida
%                                                     = l11 (+) concatenare(l12...l1n, l21...l2n), altfel
% predicatul concatenare(L1, L2, L3) va concatena lista L1 cu L2, iar rezultatul va fi in L3
% model de flux : concatenare(i, i, o), concatenare(o, o, i)
concatenare([], L2, L2).
concatenare([H|L1], L2, [H|L3]) :-
    concatenare(L1, L2, L3).