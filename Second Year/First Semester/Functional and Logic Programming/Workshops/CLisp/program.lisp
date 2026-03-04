;; Returneaza T daca x este mai lunga decat y
;; lista-mai-lunga-p(x1...xn,y1...ym) = F, daca x vida
;;          		  	    = T, daca y vida
;;			            = lista_mai_lunga(x2...xn,y2..ym)
(defun lista-mai-lunga-p (l1 l2)
  (cond
    ((null l1) nil)
    ((null l2) t)
    (t (lista-mai-lunga-p (cdr l1) (cdr l2)))))


;; Funcție pentru a reuni nivelele din subarborele stang cu cel drept
;; reuneste-nivele(x1...xn,y1...ym) = x, daca y vida
;;				    = y, daca x vida
;;				    = x1 (+) y1 (+) reuneste-nivele(x2...xn, y1...ym)
(defun reuneste-nivele (lista-stanga lista-dreapta)
  (cond
    ((null lista-stanga) lista-dreapta)
    ((null lista-dreapta) lista-stanga)
    (t (cons (append (car lista-stanga) (car lista-dreapta))
             (reuneste-nivele (cdr lista-stanga) (cdr lista-dreapta))))))

;; Functie recursiva care transforma arborele in lista de nivele
;; (A (B) (C (D) (E))) -> ((A) (B C) (D E))
;; genereaza-nivele(l1...ln) = vida, daca l vida
;;			     = l1 (+) reuneste-nivele(genereaza-nivele(l2...ln),genereaza-nivele(l3...ln)
(defun genereaza-nivele (arbore)
  (cond
    ((null arbore) nil)
    (t (cons (list (car arbore))
             (reuneste-nivele 
               (genereaza-nivele (car (cdr arbore)))
               (genereaza-nivele (car (cdr (cdr arbore))))))
    )))

;; Functie pentru a gasi nivelul cu numar maxim de noduri
;; nivele: lista de nivele generata anterior
;; contor-curent: tinem minte la ce adancime a arborelui gasim cel mai mare grup de noduri 
;; nivel-best-marker: lista care reprezinta cel mai bun nivel gasit
;; noduri-best: lista de noduri de pe cel mai bun nivel
;; cauta-maxim(a1...an, cur, best, b1...bn) = [best, b], daca a vida
;;					    = cauta-maxim(a2...an, cur + 1, cur, a1), daca |a1| > best
;;					    = cauta-maxim(a2...an, cur + 1, best, b1...bn), altfel
(defun cauta-maxim (nivele nivel-curent nivel-best noduri-best)
  (cond
    ;; Cazul de baza, am terminat lista
    ((null nivele) 
     (list nivel-best noduri-best))
    
    ;; Daca lungimea nivelului curent este mai mare decat lungimea maxima gasita
    ((> (length (car nivele)) (length noduri-best))
     (cauta-maxim 
       (cdr nivele)
       (+ 1 nivel-curent)
       nivel-curent
       (car nivele)))
    
    ;; Altfel, continuam fara actualizare
    (t (cauta-maxim 
         (cdr nivele)
         (+ 1 nivel-curent)
         nivel-best
         noduri-best))))

(defun nr-noduri-doi-copii (arbore)
  (cond
    ((null arbore) 0)
    ((null (cdr arbore)) 0)
    ((and (cadr arbore) (caddr arbore))
     (+ 1
        (nr-noduri-doi-copii (cadr arbore))
        (nr-noduri-doi-copii (caddr arbore))))
    (t
     (+ (nr-noduri-doi-copii (cadr arbore))
        (nr-noduri-doi-copii (caddr arbore))))))

;; rezolvare(l1...ln) = vid, daca l vida
;;		      = cauta-maxim(genereaza-nivele(l1...ln) 0 0 [])
(defun rezolvare (arbore)
  (cond
     ((null arbore) nil)
     (t (cauta-maxim (genereaza-nivele arbore) 0 0 nil))))
