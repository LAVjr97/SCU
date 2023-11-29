insert(X, empty, node(empty,X,empty)).
insert(X, node(L,X,R), node(L,X,R)).
insert(X, node(L,Y,R), node(T,Y,R)) :- X < Y, insert(X,L,T).
insert(X, node(L,Y,R), node(L,Y,T)) :- X > Y, insert(X,R,T).

exists(X, node(_,X,_)).
exists(X, node(L,Y,_)) :- X < Y, exists(X,L).
exists(X, node(_,Y,R)) :- X > Y, exists(X,R).

?- insert(10, empty,T1), insert(30, T1, T2), insert(40, T2, T3), insert(20, T3, T4), exists (20,T4).
identify a church numeral & boolean (don't need to evaluate) 