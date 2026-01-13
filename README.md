# Semantic Analyzer (C++)

A compiler-style **semantic analyzer** implemented in C++ that enforces
**mutable vs immutable variable rules**, performs **type checking**, and
detects **semantic errors** using an **AST + Visitor pattern**.

This project focuses on the **semantic analysis phase** of a compiler,
separate from parsing and code generation.

---

## ✨ Features

- ✅ Abstract Syntax Tree (AST) design
- ✅ Visitor-based semantic analysis
- ✅ Symbol table with scope handling
- ✅ Mutable vs immutable variable enforcement
- ✅ Type checking during declaration and assignment
- ✅ Detection of semantic errors:
  - Illegal modification of immutable variables
  - Uninitialized immutable variables
  - Redeclaration errors
  - Undeclared variable usage
  - Type mismatch errors

---

## 🧠 Semantic Rules Enforced

### Immutable Variables
- Must be initialized at declaration
- Cannot be reassigned after initialization

```c
const int x = 10;
x = 20;   // ❌ Semantic Error
