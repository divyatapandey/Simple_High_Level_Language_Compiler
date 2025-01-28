# Mini Compiler: Lexical Analysis, Parsing, and Code Generation

This project is a mini compiler implemented in C++ that simulates the core functionalities of a compiler pipeline, including **Lexical Analysis**, **Parsing**, and **Code Generation**. It supports a subset of programming language constructs like variable declarations, assignments, and conditional statements.

---

## Features

### 1. Lexical Analysis
- Tokenizes source code into meaningful components (keywords, literals, identifiers, operators, punctuation).
- Utilizes **regular expressions** for efficient pattern matching.

### 2. Parsing
- Constructs an **Abstract Syntax Tree (AST)** to represent the hierarchical structure of the code.
- Supports:
  - Variable declarations (`int a;`)
  - Assignments (`a = 10;`)
  - Conditional statements (`if(a == 10)`).

### 3. Code Generation
- Converts the AST into a simple assembly-like instruction set for execution simulation.
- Example:
  ```assembly
  DECLARE a
  LOAD 10
  STORE a
  IF a == 10 THEN
### How It Works
Input Source Code:
```bash
int a;
int b;
a = 10;
if (a == 10) {
    b = a + 1;
}
```
output:
```bash
[KEYWORD int]
[IDENTIFIER a]
[PUNCTUATION ;]
[KEYWORD int]
[IDENTIFIER b]
[PUNCTUATION ;]
[IDENTIFIER a]
[OPERATOR =]
[LITERAL 10]
[PUNCTUATION ;]
[KEYWORD if]
[PUNCTUATION (]
[IDENTIFIER a]
[OPERATOR ==]
[LITERAL 10]
[PUNCTUATION )]
[PUNCTUATION {]
[IDENTIFIER b]
[OPERATOR =]
[IDENTIFIER a]
[OPERATOR +]
[LITERAL 1]
[PUNCTUATION ;]
[PUNCTUATION }]
  Declaration:a
  Declaration:b
  Assignment:a
  Value:10
  Value:10
  Conditional:
  Condition:a == 10
  Condition:a == 10
  Assignment:b
  Value:a
  Value:a
DECLAREa
DECLAREb
LOAD10
STOREa
IFa == 10THEN
LOADa
STOREb
```
