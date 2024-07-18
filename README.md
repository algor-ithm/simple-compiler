# Simple Compiler 

A simplified compiler implemented in C++ that compiles a subset of Java, called Java0, into x86 assembly language. This project was created for a Compiler Design & Construction course at Sam Houston State University to demonstrate the fundamentals of compiler design, including lexical analysis, syntax analysis, semantic analysis, and code generation.

## Overview

This project showcases a simple compiler that translates Java0 program into x86 assembly langauge, designed to run in a Linux environment. The compiler performs  lexical analysis using a table-driven deterministic finite state automaton (DFSA), builds a symbol table, and performs syntax and semantic analysis using a push-down automaton (PDA). Finally, it generates and optimizes the x86 assembly code. 

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


