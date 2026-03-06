;lungime-impara-lista-p(l1...ln) = false, daca n = 0
;				 = true, n = 1
;				 = lungime_impara-lista-p([l3...ln]), n > 1
(defun lungime-impara-lista-p (l)
  (cond
    ((null l) nil)                     
    ((null (cdr l)) t)                
      (t (lungime-impara-lista-p (cdr (cdr l)))))) 

;primele-impare = vida, daca L este vida
;		= e1 U primele-impare(e2...en), daca este-impar(e1) = True
;		= primele-impare(e2...en), altfel
(defun primele-impare-tot (l)
  (cond
    ((null l) nil)
    ((and (listp (car l)) (lungime-impara-lista-p (car l)))
     (append (car l) (primele-impare-tot (cdr l))))
    (t (primele-impare-tot (cdr l)))))
