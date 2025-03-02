#pragma once

#include "includes.hpp"

#include "PrefixTree.hpp"
#include "Data.hpp"

using function_type = std::function<Data(const std::vector<Data>&)>;

class MemoryManager {
public:
    PrefixTree<Data> program_data; // [name of variable] = real or polynomial Data
    PrefixTree<shared_ptr<function_type>> function_data; // [name of function] = function object
    PrefixTree<int> objects_priority; // [name of object] = function priority
};

extern unique_ptr<MemoryManager> global_memory;