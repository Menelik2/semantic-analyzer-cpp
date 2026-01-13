
// ast.cpp
#include "ast.h"
#include "visitor.h"

void IntLiteral::accept(ASTVisitor& v) { v.visit(*this); }
void VarExpr::accept(ASTVisitor& v)    { v.visit(*this); }
void VarDecl::accept(ASTVisitor& v)    { v.visit(*this); }
void AssignStmt::accept(ASTVisitor& v) { v.visit(*this); }
void Block::accept(ASTVisitor& v)       { v.visit(*this); }
