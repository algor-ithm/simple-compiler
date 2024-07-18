# Simple Compiler 

A simplified compiler implemented in C++ that compiles a subset of Java, called Java0, into x86 assembly language. This project was created for a Compiler Design & Construction course at Sam Houston State University to demonstrate the fundamentals of compiler design, including lexical analysis, syntax analysis, semantic analysis, and code generation.

## Overview

This project showcases a simple compiler that translates Java0 program into x86 assembly langauge, designed to run in a Linux environment. The compiler performs  lexical analysis using a table-driven deterministic finite state automaton (DFA), builds a symbol table, and performs syntax and semantic analysis using a push-down automaton (PDA) with an opeartor precedence grammar. Finally, it generates and optimizes the x86 assembly code. 

## Table of Contents

- [Project Structure](#project-structure)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
    - [Lexical Analysis](#lexical-analysis)
    - [Symbol Table](#symbol-table)
    - [Syntax and Semantic Analysis](#syntax-and-semantics-analysis)
    - [Code Generator](#code-generator)
- [Example](#example)
- [Error Detection](#error-detection)
- [Submission Code](#submission-code)
- [Dependencies](#dependencies)
- [Contributing](#contributing)

## Project Structure

## Features

- Lexical analysis using a table-driven DFA.
- Symbol table construction using a separate table-driven DFA.
- Syntax and semantic analysis using a PDA and operator precedence grammar.
- Code generation and optimization for x86 assembly langauge.
- Error detection and reporting for various syntactic and semantic errors.

## Installation

## Usage

## Implementation Details

### Lexical Analysis

The lexical analyzer (Tokenizer) reads the input source code character by character and converts it into a sequence of toekns using a table-driven deterministic finite state automoton (DFA).

### Symbol Table

The SymbolTableBuilder creates a symbol table from the token list using a separate table-driven DFA.

### Syntax and Semantic Anaylsis

The Parser performs syntax and semantic analysis using a table-drive push down automaton (PDA) and an operator precedence grammar. It goes through the token list to create the appropriate quads. 

### Code Generation

The CodeGenerator optimizes the quads and generates the correpsonding x86 assembly code. The generate code is designed  to be run in a Linux environment from the terminal. 

## Example

### Java0 Source Code (example.txt)

### Compilation and Execution

## Error Detection

The compiler includes error detection for various syntactic and semantic errors. Example error cases can be found in the `errorExamples/` directory.

## Dependencies

## Contributing

Contributions are welcome! Please fork the repository and submit pull requests.
