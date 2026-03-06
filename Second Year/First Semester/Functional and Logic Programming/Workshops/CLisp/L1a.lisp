;apare(x,l1...ln) = false, daca l1...ln este vida
;		  = true, daca x = l1
;		  = apare(x,l2...ln), altfel
(defun apare (x l)
	(cond
		((null l) nil)
		((equal x (car l)) t)
		(t (apare x (cdr l)))))

;diferenta(a1...an, b1...bm) = vida, daca A este vida
;		= diferenta(a2...am, b1...bm), daca apare(a1,b1...bm) = true
;		= [a1] U diferenta(a2...am, b1...bm)
(defun diferenta (A B)
	(cond
		((null A) nil)
		((apare (car A) B) (diferenta (cdr A) B))
		(t (cons (car A) (diferenta (cdr A) B)))))
