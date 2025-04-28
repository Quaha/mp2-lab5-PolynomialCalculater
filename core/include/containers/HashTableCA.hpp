#pragma once

#include <vector>
#include <functional>
#include <iostream>

template <class TKey, class TValue> class HashTableCA {
protected:

    std::vector<std::vector<std::pair<TKey, TValue>>> data;

    int count_of_elements = 0;
    int capacity;

    size_t getHash(const TKey& key, int MOD = 0) const {
        std::hash<TKey> hasher;
        if (MOD <= 0) {
            return hasher(key) % capacity;
        }
        return hasher(key) % MOD;
    }

    void rebuild(int new_capacity) {

        std::vector<std::vector<std::pair<TKey, TValue>>> new_data(new_capacity);

        for (auto data_element : *this) {
            size_t cell_pos = getHash(data_element.first, new_capacity);
            new_data[cell_pos].push_back(data_element);
        }

        capacity = new_capacity;
        data = new_data;
    }

public:
    class Iterator {
    protected:

        int cell_position = 0;
        int data_position = 0;
        HashTableCA<TKey, TValue>* container;

        Iterator(int cell_position, int start_position, HashTableCA<TKey, TValue>* container) :
            cell_position(cell_position),
            data_position(start_position),
            container(container)
        {}

    public:

        std::pair<const TKey&, TValue&> operator*() {
            return {container->data[cell_position][data_position].first,
                    container->data[cell_position][data_position].second};
        }

        const std::pair<const TKey&, const TValue&> operator*() const {
            return {container->data[cell_position][data_position].first,
                    container->data[cell_position][data_position].second};
        }

        std::pair<TKey, TValue>* operator->() const {
            return &container->data[cell_position][data_position];
        }

        Iterator& operator++() {
            ++data_position;
            if (data_position >= container->data[cell_position].size()) {
                data_position = 0;

                ++cell_position;
                while (cell_position < container->capacity && container->data[cell_position].empty()) {
                    ++cell_position;
                }
            }
            return *this;
        }

        Iterator& operator--() {
            --data_position;
            if (data_position < 0) {
                --cell_position;
                while (cell_position >= 0 && container->data[cell_position].empty()) {
                    --cell_position;
                }

                if (cell_position < 0) {
                    cell_position = capacity;
                    data_position = 0;
                }
                else {
                    data_position = container->data[cell_position].size() - 1;
                }
            }
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return this->data_position == other.data_position &&
                   this->cell_position == other.cell_position;
        }

        bool operator!=(const Iterator& other) const {
            return this->data_position != other.data_position ||
                   this->cell_position != other.cell_position;
        }

        friend class HashTableCA;
    };

protected:
    Iterator makeIterator(int cell_pos, int data_pos) const {
        return Iterator(cell_pos, data_pos, const_cast<HashTableCA<TKey, TValue>*>(this));
    }
public:


    HashTableCA() {
        capacity = 5;
        data.resize(capacity);
    }

    ~HashTableCA() {

    }

    Iterator begin() const {
        int first_cell = 0;
        while (first_cell < capacity && data[first_cell].empty()) {
            first_cell++;
        }
        return makeIterator(first_cell, 0);
    }

    Iterator end() const {
        return makeIterator(capacity, 0);
    }

    Iterator insert(const TKey& key, const TValue& value) {

        auto it = find(key);

        if (it != end()) {
            return it;
        }

        count_of_elements++;

        int cell_pos = getHash(key);
        int data_pos = data[cell_pos].size();

        data[cell_pos].push_back(std::make_pair(key, value));

        if (count_of_elements * 2 > capacity) {
            rebuild(capacity * 2);
        }


        return find(key);
    }

    Iterator erase(const TKey& key) {
        Iterator it = find(key);

        if (it != this->end()) {
            int cell_pos = it.cell_position;
            int data_pos = it.data_position;

            count_of_elements--;

            std::swap(data[cell_pos][data_pos], data[cell_pos].back());
            data[cell_pos].pop_back();

            if (data_pos == data[cell_pos].size()) {
                ++it;
            }
        }
        return it;
    }

    Iterator find(const TKey& key) const {

        if (this->empty()) {
            return this->end();
        }

        int cell_pos = getHash(key);
        int data_pos = 0;
        while (data_pos < data[cell_pos].size() && data[cell_pos][data_pos].first != key) {
            data_pos++;
        }

        if (data_pos == data[cell_pos].size()) {
            return end();
        }

        return makeIterator(cell_pos, data_pos);
    }

    bool isExist(const TKey& key) const {
        return this->find(key) != this->end();
    }

    TValue& operator[](const TKey& key) {
        if (!this->isExist(key)) {
            throw std::runtime_error("No such key in table");
        }
        return (*this->find(key)).second;
    }

    const TValue& operator[](const TKey& key) const {
        if (!this->isExist(key)) {
            throw std::runtime_error("No such key in table");
        }
        return (*this->find(key)).second;
    }

    size_t size() const {
        return count_of_elements;
    }

    bool empty() const {
        return count_of_elements == 0;
    }

    void clear() {
        data.clear();

        count_of_elements = 0;
        data.resize(capacity);
    }
};

template <typename TKey, typename TValue>
class TestableHashTableCA : public HashTableCA<TKey, TValue> {

    size_t getHash(const TKey& key, int MOD = 0) const {
        return 0;
    }
};
