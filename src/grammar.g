root
    : '@' stat ';'
    | '#' any
    ;
stat
    : 'use' '{' INT '}'
    | 'decl'  decl
    | 'set' assign
    | 'pick' var '{' var ',' INT '}'
    | 'color' assign
    | 'for' '(' range ')' '|' var ( for_params ) '|' func
    | 'run' pin
    | 'brightness' assign
    | 'delay' pin
    | 'loop' (loop)
    | 'exit'
    ;
pin
    : 'pin'
    | 'pins' '-' range
    ;
decl
    : 'type' '{' type '}'
    | 'addressable' '{' INT '}'
    | loop
    ;
loop
    : '_' letters
    ;
range
    : val ':' val
    ;
val
    : var
    | INT
    | FLOAT
    ;
for_params
    : 'step' '{' val '}'
    ;
func
    : '{' root* '}'
    ;
assign
    : var '=' expr ('|' expr)
    | pin '=' expr ('|' expr)
    ;
expr
    : var
    | INT
    | array
    | func
    ;
array
    : '{' items '}'
    ;
items
    : array
    | INT
    | color
    ;
color
    : '(' INT ',' INT ',' INT ')'
    ;
type
    : 'strip'
    ;
var
    : '$' letters
    | '$' letters ':' var
    ;
letters
    : letter+
    ;
letter
    : [a-zA-Z]
    ;
any
    : -> skip
