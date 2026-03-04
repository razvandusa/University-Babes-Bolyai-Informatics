(defun insereaza (L a poz)
	(cond
		((null L) nil)
		((evenp poz) (cons (car L) (cons a (insereaza (cdr L) a (+ poz 1)))))
		(t (cons (car L) (insereaza (cdr L) a (+ poz 1))))
	)
)

(defun insereaza-dupa-pozitii-pare (L a)
	(insereaza L a 1)
)
