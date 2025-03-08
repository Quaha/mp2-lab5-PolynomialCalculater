#pragma once

#include "includes.hpp"

#include "PrefixTree.hpp"
#include "Data.hpp"

#include "OrderedTable.hpp"

using function_type = std::function<Data(const std::vector<Data>&)>;

#define MemoryType OrderedTable

class MemoryManager {
public:
    MemoryType<string, Data> program_data; // [name of variable] = real or polynomial Data

    MemoryType<string, shared_ptr<function_type>> function_data; // [name of function] = function object
    MemoryType<string, int> objects_priority; // [name of object] = function priority
};

extern unique_ptr<MemoryManager> global_memory;