(defun substituie (E L1 L)
	(apply #'append
		(mapcar
			(lambda (x)
				(cond
					((equal x E) L1)
					((listp x) (list (substituie E L1 x)))
					(t (list x))
				)
			)
		L
		)
	)
)
