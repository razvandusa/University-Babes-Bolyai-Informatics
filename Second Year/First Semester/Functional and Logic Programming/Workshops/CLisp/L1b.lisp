;deep-invers(l1...ln) = vida, daca L = vida
;		      = l, daca L este atom
;		      = deep-invers(l2...ln) (+) deep-invers(l1)
(defun deep-invers (l)
	(cond
		((null l) nil)
		((atom l) l)
		(t (append (deep-invers (cdr l))
			(list (deep-invers (car l)))))))
