#pragma once

#include "includes.hpp"

//#include "PrefixTree.hpp"
#include "Data.hpp"

#include "OrderedTable.hpp"
#include "UnorderedTable.hpp"

using function_type = std::function<Data(const std::vector<Data>&)>;

class BaseMemoryManager {
public:
    virtual ~BaseMemoryManager() = default;

    virtual Data getVariable(const string& name) const = 0;
    virtual void setVariable(const string& name, const Data& value) = 0;
    virtual bool isVariableExists(const string& name) const = 0;

    virtual shared_ptr<function_type> getFunction(const string& name) const = 0;
    virtual void setFunction(const string& name, shared_ptr<function_type> function) = 0;
    virtual bool isFunctionExists(const string& name) const = 0;

    virtual int getPriority(const string& name) const = 0;
    virtual void setPriority(const string& name, int priority) = 0;
};

template<template<typename, typename> class MemoryType>
class MemoryManager: public BaseMemoryManager {
public:

    MemoryType<string, Data> program_data; // [name of variable] = real or polynomial Data

    MemoryType<string, shared_ptr<function_type>> function_data; // [name of function] = function object
    MemoryType<string, int> objects_priority; // [name of object] = function priority

    Data getVariable(const string& name) const override {
        return program_data[name];
    }

    void setVariable(const string& name, const Data& value) override {
        program_data.insert(name, value);
    }

    bool isVariableExists(const string& name) const override{
        return program_data.isExist(name);
    }

    shared_ptr<function_type> getFunction(const string& name) const override {
        return function_data[name];
    }

    bool isFunctionExists(const string& name) const override {
        return function_data.isExist(name);
    }

    void setFunction(const string& name, shared_ptr<function_type> function) override {
        function_data.insert(name, function);
    }

    int getPriority(const string& name) const override {
        return objects_priority[name];
    }

    void setPriority(const string& name, int priority) override {
        objects_priority.insert(name, priority);
    }
};

extern unique_ptr<BaseMemoryManager> global_memory;

void initMemory(size_t container_id);