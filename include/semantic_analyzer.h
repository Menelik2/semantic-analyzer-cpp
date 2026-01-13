
#pragma once
#include "visitor.h"
#include "symbol_table.h"
#include <stdexcept>

class SemanticAnalyzer : public ASTVisitor {
    SymbolTable table;
    std::string lastExprType;

public:
    void visit(IntLiteral&) override {
        lastExprType = "int";
    }

    void visit(VarExpr& e) override {
        Symbol* sym = table.lookup(e.name);
        if (!sym)
            throw std::runtime_error("Use of undeclared variable '" + e.name + "'");
        lastExprType = sym->type;
    }

    void visit(VarDecl& d) override {
        if (!d.isMutable && !d.init)
            throw std::runtime_error(
                "Immutable variable '" + d.name + "' must be initialized"
            );

        bool initialized = false;
        if (d.init) {
            d.init->accept(*this);
            if (lastExprType != d.type)
                throw std::runtime_error("Type mismatch in initialization of '" + d.name + "'");
            initialized = true;
        }

        table.declare({
            d.name,
            d.type,
            d.isMutable ? Mutability::MUTABLE : Mutability::IMMUTABLE,
            initialized
        });
    }

    void visit(AssignStmt& a) override {
        Symbol* sym = table.lookup(a.name);
        if (!sym)
            throw std::runtime_error("Assignment to undeclared variable '" + a.name + "'");

        if (sym->mutability == Mutability::IMMUTABLE && sym->initialized)
            throw std::runtime_error(
                "Cannot modify immutable variable '" + a.name + "'"
            );

        a.value->accept(*this);
        if (lastExprType != sym->type)
            throw std::runtime_error("Type mismatch in assignment to '" + a.name + "'");

        sym->initialized = true;
    }

    void visit(Block& b) override {
        table.enterScope();
        for (auto& stmt : b.statements)
            stmt->accept(*this);
        table.exitScope();
    }
};
