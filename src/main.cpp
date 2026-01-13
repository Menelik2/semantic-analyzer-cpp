#include "semantic_analyzer.h"
#include <memory>

int main() {
    Block program;

    program.statements.push_back(
        std::make_unique<VarDecl>(
            "x", "int", false,
            std::make_unique<IntLiteral>(10)
        )
    );

    program.statements.push_back(
        std::make_unique<AssignStmt>(
            "x", std::make_unique<IntLiteral>(20)
        )
    );

    SemanticAnalyzer analyzer;
    program.accept(analyzer);
}

