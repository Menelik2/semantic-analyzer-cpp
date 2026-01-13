
#pragma once
#include "ast.h"

struct ASTVisitor {
    virtual void visit(IntLiteral&) = 0;
    virtual void visit(VarExpr&) = 0;
    virtual void visit(VarDecl&) = 0;
    virtual void visit(AssignStmt&) = 0;
    virtual void visit(Block&) = 0;
};
