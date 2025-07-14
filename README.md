# Lexer

## Compile 
`gcc run.c -o main`

## Output

```bash
➜ Lexer git:(master) .\main.exe
Lexing the following source code:
---
int myVar = 10 + 5;
if (myVar > 10) {
  else x = 20;
}
another_var = 1 * 2 / 3;
// This is a comment, lexer ignores it for now
int _test = 100;
invalid@char
---

Token: [Type: KEYWORD_INT, Lexeme: "int", Line: 1, Column: 1]  
Token: [Type: IDENTIFIER, Lexeme: "myVar", Line: 1, Column: 5] 
Token: [Type: ASSIGN, Lexeme: "=", Line: 1, Column: 11]        
Token: [Type: NUMBER, Lexeme: "10", Line: 1, Column: 13]       
Token: [Type: PLUS, Lexeme: "+", Line: 1, Column: 16]
Token: [Type: NUMBER, Lexeme: "5", Line: 1, Column: 18]        
Lexical Error: Unknown character ';' at line 1, column 19      
Token: [Type: UNKNOWN, Lexeme: ";", Line: 1, Column: 19]       
Token: [Type: KEYWORD_IF, Lexeme: "if", Line: 2, Column: 1]    
Lexical Error: Unknown character '(' at line 2, column 4       
Token: [Type: UNKNOWN, Lexeme: "(", Line: 2, Column: 4]        
Token: [Type: IDENTIFIER, Lexeme: "myVar", Line: 2, Column: 5] 
Lexical Error: Unknown character '>' at line 2, column 11      
Token: [Type: UNKNOWN, Lexeme: ">", Line: 2, Column: 11]       
Token: [Type: NUMBER, Lexeme: "10", Line: 2, Column: 13]       
Lexical Error: Unknown character ')' at line 2, column 15      
Token: [Type: UNKNOWN, Lexeme: ")", Line: 2, Column: 15]       
Lexical Error: Unknown character '{' at line 2, column 17      
Token: [Type: UNKNOWN, Lexeme: "{", Line: 2, Column: 17]       
Token: [Type: KEYWORD_ELSE, Lexeme: "else", Line: 3, Column: 3]
Token: [Type: IDENTIFIER, Lexeme: "x", Line: 3, Column: 8]
Token: [Type: ASSIGN, Lexeme: "=", Line: 3, Column: 10]
Token: [Type: NUMBER, Lexeme: "20", Line: 3, Column: 12]
Lexical Error: Unknown character ';' at line 3, column 14
Token: [Type: UNKNOWN, Lexeme: ";", Line: 3, Column: 14]
Lexical Error: Unknown character '}' at line 4, column 1
Token: [Type: UNKNOWN, Lexeme: "}", Line: 4, Column: 1]
Token: [Type: IDENTIFIER, Lexeme: "another_var", Line: 5, Column: 1]
Token: [Type: ASSIGN, Lexeme: "=", Line: 5, Column: 13]
Token: [Type: NUMBER, Lexeme: "1", Line: 5, Column: 15]
Token: [Type: MULTIPLY, Lexeme: "*", Line: 5, Column: 17]
Token: [Type: NUMBER, Lexeme: "2", Line: 5, Column: 19]
Token: [Type: DIVIDE, Lexeme: "/", Line: 5, Column: 21]
Token: [Type: NUMBER, Lexeme: "3", Line: 5, Column: 23]
Lexical Error: Unknown character ';' at line 5, column 24
Token: [Type: UNKNOWN, Lexeme: ";", Line: 5, Column: 24]
Token: [Type: DIVIDE, Lexeme: "/", Line: 6, Column: 1]
Token: [Type: DIVIDE, Lexeme: "/", Line: 6, Column: 2]
Token: [Type: IDENTIFIER, Lexeme: "This", Line: 6, Column: 4]
Token: [Type: IDENTIFIER, Lexeme: "is", Line: 6, Column: 9]
Token: [Type: IDENTIFIER, Lexeme: "a", Line: 6, Column: 12]
Token: [Type: IDENTIFIER, Lexeme: "comment", Line: 6, Column: 14]
Lexical Error: Unknown character ',' at line 6, column 21
Token: [Type: UNKNOWN, Lexeme: ",", Line: 6, Column: 21]
Token: [Type: IDENTIFIER, Lexeme: "lexer", Line: 6, Column: 23]
Token: [Type: IDENTIFIER, Lexeme: "ignores", Line: 6, Column: 29]
Token: [Type: IDENTIFIER, Lexeme: "it", Line: 6, Column: 37]
Token: [Type: IDENTIFIER, Lexeme: "for", Line: 6, Column: 40]
Token: [Type: IDENTIFIER, Lexeme: "now", Line: 6, Column: 44]
Token: [Type: KEYWORD_INT, Lexeme: "int", Line: 7, Column: 1]
Token: [Type: IDENTIFIER, Lexeme: "_test", Line: 7, Column: 5]
Token: [Type: ASSIGN, Lexeme: "=", Line: 7, Column: 11]
Token: [Type: NUMBER, Lexeme: "100", Line: 7, Column: 13]
Lexical Error: Unknown character ';' at line 7, column 16
Token: [Type: UNKNOWN, Lexeme: ";", Line: 7, Column: 16]
Token: [Type: IDENTIFIER, Lexeme: "invalid", Line: 8, Column: 1]
Lexical Error: Unknown character '@' at line 8, column 8
Token: [Type: UNKNOWN, Lexeme: "@", Line: 8, Column: 8]
Token: [Type: IDENTIFIER, Lexeme: "char", Line: 8, Column: 9]
Token: [Type: EOF, Lexeme: "EOF", Line: 8, Column: 13]
```