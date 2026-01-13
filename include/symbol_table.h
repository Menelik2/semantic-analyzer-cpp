
#pragma once
#include "symbol.h"
#include <unordered_map>
#include <stack>
#include <stdexcept>

class SymbolTable {
    std::stack<std::unordered_map<std::string, Symbol>> scopes;

public:
    SymbolTable() { enterScope(); }

    void enterScope() { scopes.push({}); }
    void exitScope()  { scopes.pop(); }

    void declare(const Symbol& sym) {
        auto& scope = scopes.top();
        if (scope.count(sym.name))
            throw std::runtime_error("Redeclaration of '" + sym.name + "'");
        scope[sym.name] = sym;
    }

    Symbol* lookup(const std::string& name) {
        auto temp = scopes;
        while (!temp.empty()) {
            auto& s = temp.top();
            if (s.count(name)) return &s[name];
            temp.pop();
        }
        return nullptr;
    }
};
