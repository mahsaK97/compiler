program        = statement* ;




statement      = 
exprStmt
 
|printStmt
|ifStmt
|whileStmt
 
|block

|typeDecl
|functionDecl
|returnDecl;



typeDecl = Type_KeyWord IDENTIFIER  "=" expression  ";"  ; 
Type_KeyWord= "number" | "string" | "bool" ;

functionDecl =  "function"  IDENTIFIER  "(" parameters?  ")" block ;
parameters = IDENTIFIER ( "," IDENTIFIER ) *;
returnDecl=  "return"  expression?  ";"  ;


arguments= expression ( "," expression )*;           
arrayLiteral= "["  arguments?  "]" ;

exprStmt       = expression ";" ;

printStmt      = "print" "(" expression ")" ";" ;
ifStmt         = "if" "(" expression ")" statement ( "else" statement )? ;
whileStmt      = "while" "(" expression ")" statement ;
block          = "{" statement* "}" ;



expression     = assignment ;
assignment     = IDENTIFIER "=" assignment
               | logic_or ;


logic_or       = logic_and ( "||" logic_and )* ;

logic_and      = equality ( "&&" equality )* ;
equality       = comparison ( ( "==" | "!=" ) comparison )* ;
comparison     = term ( ( "<" | ">" | "<=" | ">=" ) term )* ;

term           = factor ( ( "+" | "-" ) factor )* ;
factor         = unary ( ( "*" | "/" ) unary )* ;

unary          = ( "-" | "!" ) unary
               | call ;

call = primary ( "(" arguments?  ")" | "[" expression "]" )* ;
primary  = NUMBER |
 STRING | 
"true" |
 "false"|
 IDENTIFIER | 
"(" expression ")" |
 arrayLiteral ;

