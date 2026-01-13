#pragma once
#include <string>

enum class Mutability { MUTABLE, IMMUTABLE };

struct Symbol {
    std::string name;
    std::string type;
    Mutability mutability;
    bool initialized;
};

