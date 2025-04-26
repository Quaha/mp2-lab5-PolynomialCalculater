#pragma once

#include "includes.hpp"

template<class TKey, class TValue>
class UnorderedTable {
protected:

	std::vector<std::pair<TKey, TValue>> data;

public:
	
    UnorderedTable() = default;
	
    class Iterator {
    public:
        
        std::pair<TKey, TValue>* pntr; 
        const std::pair<TKey, TValue>* constPntr;

        // Added something related to const iterator, but idk why we need this
        Iterator() = default;
        Iterator(std::nullptr_t) : pntr(nullptr) {}
        Iterator(std::pair<TKey, TValue>* obj) : pntr(obj) {}
        Iterator(const std::pair<TKey, TValue>* obj) : pntr(const_cast<std::pair<TKey, TValue>*>(obj)) {}

        Iterator& operator++() {
            if (pntr) ++pntr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            if (pntr) --pntr;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        Iterator operator+(int step) const {
            Iterator res = *this;
            if (pntr) {
                if (step > 0) {
                    for (int i = 0; i < step; i++) ++res;
                }
                else {
                    for (int i = 0; i < -step; i++) --res;
                }
            }
            return res;
        }

        Iterator operator-(int step) const {
            return *this + (-step);
        }

        Iterator& operator+=(int step) {
            *this = *this + step;
            return *this;
        }

        Iterator& operator-=(int step) {
            *this = *this - step;
            return *this;
        }

        bool operator==(const Iterator& it) const {
            return pntr == it.pntr;
        }

        bool operator!=(const Iterator& it) const {
            return pntr != it.pntr;
        }

        std::pair<TKey, TValue>& operator*() const {
            if (!pntr) throw std::runtime_error("Dereferencing null iterator");
            return *pntr;
        }

        std::pair<TKey, TValue>* operator->() const {
            if (!pntr) throw std::runtime_error("Accessing through null iterator");
            return pntr;
        }
    };

    Iterator begin() const {
        if (data.empty()) {
            return Iterator(nullptr);
        }
        return Iterator(&data[0]); 
    }

    Iterator end() const {
        if (data.empty()) {
            return Iterator(nullptr);
        }
        return Iterator(data.data() + data.size());
    }

    Iterator begin() {
        if (data.empty()) {
            return Iterator(nullptr);
        }
        return Iterator(&data[0]);
    }

    Iterator end() {
        if (data.empty()) {
            return Iterator(nullptr);
        }
        return Iterator(data.data() + data.size());
    }


	Iterator insert(const TKey& key, const TValue& value) {
		data.push_back({ key, value });
		return Iterator(&data.back());
	}

    Iterator erase(const TKey& key) {
        for (auto It = data.begin(); It != data.end(); It++) {
            if (It->first == key) {
                It = data.erase(It); 
                if (It == data.end()) {
                    return end(); 
                }
                return Iterator(&(*It));
            }
        }
        return end();
    }

	Iterator find(const TKey& key) const {
        for (auto It = data.begin(); It != data.end(); It++) {
            if (It->first == key) {
                return Iterator(&(*It));
            }
        }
        return end();
    }

	TValue& operator[](const TKey& key) {
        for (auto& pair : data) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::runtime_error("No such key in table");
	}

    const TValue& operator[](const TKey& key) const {
        for (auto& pair : data) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::runtime_error("No such key in table");
    }

	size_t size() const {
        return data.size();
	}

	bool empty() const {
        return data.empty();
	}

    void clear() {
        data.clear();
    }

    bool isExist(const TKey& key) const{
        return find(key) != end();
    }
};
