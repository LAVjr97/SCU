partition([], [], [], _).
partition([H|X], [H|Y], Z, P) :- H < P, partition(X, Y, Z, P) 
partition([H|X], Y, [H|Z], P) :- H >= P, partition(X, Y, Z, P)

quicksort([], []).
quicksort([H|X], Y) :- partition(X, L, R, H), quicksort(L, Lsort), quicksort(R, Rsort,), append(Lsort, [H|Rsort], Y). 