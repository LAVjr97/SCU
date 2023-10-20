Object subclass: #Node
    instanceVariableNames: 'data left right'
    classVariableNames: ''
    poolDisctionaries: ''

!Node class methodsFor: 'instance'!
data: x
    ^self new instance: x
!!

!Node methodsFor: 'access'!
data
    ^data 
!

left   
    ^left
!

right  
    ^right
!
insert: x
    data < x
        ifTrue: [left isNil    
                    ifTrue: [left := Node data: x] 
                    ifFalse: [left insert: x]]

        ifFalse: [right isNil 
                    ifTrue: [right := Node data: x] 
                    ifFalse: [right insert: x]]
!
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

Object subclass: #Tree
    instanceVariableNames: 'root'
    classVariableNames: ''
    poolDisctionaries: '' 

!Tree class methodsFor: 'instance'!
new
    ^super new instance: x
!!

!Tree methodsFor: 'initialize'!
initialize
    root := nil 
!!

!Tree methodsFor: 'access'!
root   
    ^root
!

insert: x
    root isNil 
        ifTrue: [root := Node data: x ]
        ifFalse: [root insert]
!
member: x
    |i| 
    root isNil
        ifTrue: [i := false]
        ifFalse: [root member: x]
    ^i
!!
