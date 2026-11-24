# Context-Free Grammar Notes

## Basics
- `S` <- head symbol
- `EXPR` <- expression
- `STM` <- statement
- `ARM` <- arithmetic

In this document, things inside `[]` are optional/conditional (not required). A **digit** is any number of any size.

## S, EXPR, STM, ARM

Head symbols is a token types and their keywords are as follows:
- **param:** `'int'`, `'string'`, `'void'`
- **cond:** `'if'`, `'else if'`, `'else'`
- **loop:** `'loop'`, `'for'`, `'while'`
- **bopen:** `'{'`, `'('`
- **bclose:** `'}'`, `')'`
- **ret:** `'ret'`
- **semi:** `';'`

Param, bopen, bclose, ret and semi are terminal tokens meaning nothing further can be created from them. Cond and loop are non terminal meaning they can be expanded.



**Expressions (`EXPR`)** are always inside `(` and `)`. Valid expressions are digits separated by a conditional operator.
- Conditional operators are the same that are used in every language. For example `==`, `>=`, `<`, and `!=`.

**Statements (`STM`)** are always inside `{` and `}`. Every statement ends with a `;` character. Statements are made of one or more constructs: `'assign'`, `'conditional'`, `'multi-conditional'`, `'conditional-else'`, `'loop'`, `'call'`, and `'return'`. Productions can in turn contain more statements and expressions inside them.

**Arithmetics (`ARM`)** are a sub-form of statements. They are made of digits separated by arithmetic operators such as `+`, `-`, `*`, and `/`.
- Shorthand forms are also provided: `digit++`, `digit--`, and `digit**`.
- `digit++` and `digit--` increment and decrement by one, while `digit**` multiplies a value by itself.

## Productions

### Assign
`S` is a type keyword such as `int` or `string`:
- `S -> id: name : value: ( digit || name || void ) ;`
- Valid single digits are `0` through `9` (where specified). Names must be initialized before use, and `void` means assigning with only a type and identifier, defaulting to `0`.

### Conditional, Multi-Conditional, Conditional-Else
`S` is a conditional keyword (`if`, `else if`, or `else`):
- `S -> if ( EXPR ) { STM ; }`
- `S -> if ( EXPR ) { STM ; } else { STM ; }`
- `S -> if ( EXPR ) { STM ; } else if ( EXPR ) { STM ; }`
- `S -> if ( EXPR ) { STM ; } else if ( EXPR ) { STM ; } else { STM ; }`

In `if () {} else if () {} else {}`, the final `else` branch runs if none of the preceding conditions are true.

### Loop
`S` is a loop keyword (`loop`, `for`, or `while`):
- `S -> loop ( digit ) { STM ; }`
- `S -> for ( ['assign', 'digit'] ; EXPR ; ARM ) { STM ; }`
- `S -> while ( EXPR, ARM, DIGIT ) { STM ; }`

### Call
`S` is an identifier followed by `()`:
- `S -> id ( ['digit', 'ARM', 'void'] ) ;`

A call must be defined before it is used. To define a call, `S` uses the `const` keyword:
- `S -> type id:name = ( ['type id:name', 'void'] ) => { STM ; }`

### Return
`S` is the `ret` keyword:
- `S -> ret ;`
- `S -> ret digit ;`
