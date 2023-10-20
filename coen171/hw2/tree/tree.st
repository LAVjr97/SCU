Object subclass: #Node
    instanceVariableNames: 'data left right'
    classVariableNames: ''
    poolDisctionaries: ''

!Node methodsFor: 'homework'!
data
    ^data 
!

left   
    ^left
!

right  
    ^right
!

data: x
    ^self new instance: x
!

insert: anObject
    data < anObject
            ifTrue: [left isNil ifTrue: [left := Node data: anObject] ifFalse: [left insert: anObject]]
            ifFalse: [right isNil ifTrue: [right := Node data: anObject] ifFalse: [right insert: anObject]]
!

memeber: anObject
    data = anObject ifTrue: [^true].
    data > anObject ifTrue: [left isNil ifTrue: [^false] ifFalse: [ ^left memeber: anObject]].
!!

Object subclass: #Tree
    instanceVariableNames: 'root'
    classVariableNames: ''
    poolDisctionaries: '' 

!Tree methodsFor: 'homework'!
root   
    ^root
!

new
    ^super new instance: x
!

initialize
    root := nil 
!

insert: x
    root isNil ifTrue: [root := Node data: x ] ifFalse: [root insert]
!

memebr: anObject
    root isNil ifTrue: [^false] ifFalse: [^root member: x] 
!!

"
member: x
    |i| 
    root isNil
        ifTrue: [i := false]
        ifFalse: [root member: x]
    ^i"


"
memeber: x
    |i|
    x < data
        ifTrue: [left isNil 
                        ifTrue: [i := false]
                        ifFalse: [left memeber: x]]
        ifFalse: [right isNil  
                        ifTrue: [i := true]
                        ifFalse: [right member: x]]
    ^i
!!
"