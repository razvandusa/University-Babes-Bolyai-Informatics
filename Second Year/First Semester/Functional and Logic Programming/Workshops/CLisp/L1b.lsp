defun lista-atomi (L)
	(cond
		((null L) nil)
		((atom L) L)
		(t (cons (lista-atomi(cdr L)) (lista-atomi(car L))))
	)
)
