
#pragma once
#include <string>
#include <vector>
#include <memory>

struct ASTVisitor;

// ===== Base Node =====
struct ASTNode {
    virtual ~ASTNode() = default;
    virtual void accept(ASTVisitor& v) = 0;
};

// ===== Expressions =====
struct Expr : ASTNode {};

struct IntLiteral : Expr {
    int value;
    explicit IntLiteral(int v) : value(v) {}
    void accept(ASTVisitor& v) override;
};

struct VarExpr : Expr {
    std::string name;
    explicit VarExpr(std::string n) : name(std::move(n)) {}
    void accept(ASTVisitor& v) override;
};

// ===== Statements =====
struct Stmt : ASTNode {};

struct VarDecl : Stmt {
    std::string name;
    std::string type;
    bool isMutable;
    std::unique_ptr<Expr> init; // nullptr if no initializer

    VarDecl(std::string n, std::string t, bool mut, std::unique_ptr<Expr> i)
        : name(std::move(n)), type(std::move(t)), isMutable(mut), init(std::move(i)) {}

    void accept(ASTVisitor& v) override;
};

struct AssignStmt : Stmt {
    std::string name;
    std::unique_ptr<Expr> value;

    AssignStmt(std::string n, std::unique_ptr<Expr> v)
        : name(std::move(n)), value(std::move(v)) {}

    void accept(ASTVisitor& v) override;
};

struct Block : Stmt {
    std::vector<std::unique_ptr<Stmt>> statements;
    void accept(ASTVisitor& v) override;
};
