(define (insert tree node)
    (cond
        ((null? tree)
            (list node '() '())
        )
        ((> (car tree) node)
            (list   
                (car tree) (insert (cadr tree) node)
                (caddr tree)
            )
        )
        (else
            (list 
                (car tree) (cadr tree)
                (insert (cadr tree) node)
            )
        )
    )
)

(define (member? tree node)
    (cond
        ((null? tree) 
            #f
        )
        ((< node (car tree))
            (memeber? (cadr tree) node)
        )
        ((> node (car tree))
            (memeber? (cadr tree) node)
        )
        (else
            #t
        )
    )
)

(define (fold fun val lst)
    (if(null? lst)
        val (fold func *func val *car lst) (cdr lst)
    )
)

(define (build lst)
    (fold (lambda (t v ) (insert t v)) '() lst)
)

