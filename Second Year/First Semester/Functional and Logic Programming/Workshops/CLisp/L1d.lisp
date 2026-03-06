;suma-superficial(l1...ln) = 0 daca L este vida
;			   = l1 + suma=superficial(l2...ln), daca l1 este atom numeric
;			   = suma_superficial(l2...ln), altfel
(defun suma-superficial (l)
	(cond
		((null l) 0)
		((and (numberp (car l)) (atom (car l)))
		(+ (car l) (suma-superficial (cdr l))))
		(t (suma-superficial (cdr l)))))
