;; functie care face suma a doua numere in reprezentare de lista, fara a converti numerele in baza 10. 
;;suma-liste(l1 l2) - l1 : lista, l2 : lista
;;model matematic : suma-liste(l11...l1n, l21...l2n,c) = null ,l1, l2 vida
;;						     = (l11+l21+c)%10 (+) suma-liste(l12...l1n, l212...l2n,l11%10+l21%10%10)
;;test : (suma-liste '(1 2 2) '(3 4 3) 0)
(defun suma-liste (l1 l2 carry)
  (cond
    ((and (null l1) (null l2)) 
     (if (> carry 0) (list carry) nil))
    ((null l1) (suma-liste (list 0) l2 carry))
    ((null l2) (suma-liste l1 (list 0) carry))
    (t (cons (mod (+ (car l1) (car l2) carry) 10)
               (suma-liste (cdr l1) (cdr l2) (truncate (+ (car l1) (car l2) carry) 10))))))
