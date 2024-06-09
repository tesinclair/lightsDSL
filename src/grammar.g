root
    : '@' stat ';'
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
    | 'delay' pin val
    | 'loop' loop val
    | 'exit'
    ;
pin
    : 'pin' ('-' '{' range | INT '}')
    | 'pins' '-' array
    ;
decl
    : 'type' '{' type '}'
    | 'addressable' '{' INT '}'
    | loop
    ;
loop
    : '&' letters
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
    | '$' letters 
    ;
letters
    : letter+
    ;
letter
    : [a-zA-Z]
    ;
