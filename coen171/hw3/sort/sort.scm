(define (filter f lst)
    (cond 
        ((null? lst) 
            lst)
        )
        ((f(car lst)) (cons(car lst)(filter f (cdr lst))))
        (else
            (filter f (cdr lst))
        )
)

(define (quicksort lst)
    (cond
        (null? lst
            ('())
        )
        (else
            (let*(
                head (car lst)
                tail (cdr lst)
                (below (lambda (x) (< x head)))
                (above (lambda (y) (>= y head)))
                )
            (append(quicksort(filter below tail)) (cons h (quicksort(filter above tail))))
            )
        )
    )
)