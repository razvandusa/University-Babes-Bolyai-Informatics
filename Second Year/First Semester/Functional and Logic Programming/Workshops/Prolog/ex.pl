%Sa se scrie un predicat care determina cel mai mic multiplu comun al
%elementelor unei liste formate din numere intregi.

%model matematic : cmmdc(x, y) = cmmdc(y, x%y), daca y != 0
%                              = x, daca y = 0
%model flux : (i, i, o)
%cmmdc(A - numar intreg, B - numar intreg, R - numar intreg)
%A = primul numar din perechea careia vrem sa ii aflam cmmdc
%B = al doilea numar din perechea careia vrem sa ii aflam cmmdc
%R = cmmdc-ul perechii
cmmdc(A,0,A).
cmmdc(A,B,R) :-
    B \= 0,
    Rest is A mod B,
    cmmdc(B, Rest, R).

%model matematic : cmmmc_doua(x,y) = x * y / cmmdc(x,y)
%model flux : (i, i, o)
%cmmmc_doua(A - numar intreg, B - numar intreg, M - numar intreg)
%A = primul numar din perechea careia vrem sa ii aflam cmmmc
%B = al doilea numar din perechea careia vrem sa ii aflam cmmmc
%M = cmmmc-ul perechii
cmmmc_doua(A ,B , M) :-
    cmmdc(A, B, G),
    M is (A * B) // G.

%model matematic : cmmmc(x1...xn) = cmmmc_doua(x1,cmmmc(x2...xn)), daca n > 1
%                                 = x1, daca n=1
%model flux : (i, o)
%cmmmc(L - lista, R - numar intreg)
%L = lista cu numerele pentru care vrem sa aflam cmmmc-ul
%R = cmmmc-ul perechii
cmmmc([],1).
cmmmc([X], X).
cmmmc([H|T], R) :-
    cmmmc(T, R1),
    cmmmc_doua(H, R1, R).

%caz de testare
%cmmmc([1,2,3,4],R) => R = 12
%cmmmc([0,2,3],R) => R = 0
%cmmmc([],R) => R = 1
%cmmmc([69],R) => R = 69
