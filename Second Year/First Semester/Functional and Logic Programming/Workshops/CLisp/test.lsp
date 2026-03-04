;;perechi(e, l1...ln) = multimea vida, daca l = multimea vida
;;			(e, l1) (+) perechi(e, l2...ln), altfel
(DEFUN PERECHI(E L)
	(COND
		((NULL L) NIL)
		(T (CONS (LIST E (CAR L)) (PERECHI E (CDR L))))
	)
)
