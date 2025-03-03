#pragma once

#include <iostream>
#include <vector>

using std::pair;
using std::vector;

template <class TKey, class TValue>
class OrderedTable : public Container<TKey, TValue> {
protected:
    vector<pair<TKey, TValue>> data;
public:

    class Iterator : public Container<TKey, TValue>::Iterator {
    protected:

        int data_position = 0;

        Iterator(int start_position) {
            data_position = start_position;
        }

    public:

        ~Iterator() override {

        }

        std::pair<TKey, TValue&> operator*() override {
            return std::pair<TKey, TValue&>(data[data_position].first, data[data_position].second);
        }

        Iterator& operator++() override {
            ++data_position;
            if (data_position > data.size()) {
                data_position = 0;
            }
            return *this;
        }

        Iterator& operator--() override {
            --data_position;
            if (data_position < 0) {
                data_position = data.size();
            }
            return *this;
        }

        Iterator operator++(int) override {
            int prev_position = data_position;
            ++data_position;
            if (data_position > data.size()) {
                data_position = 0;
            }
            return Iterator(prev_position);
        }

        Iterator operator--(int) override {
            int prev_position = data_position;
            --data_position;
            if (data_position < 0) {
                data_position = data.size();
            }
            return Iterator(prev_position);
        }

        bool operator==(const Iterator& other) const override {
            return this->data_position == other.data_position;
        }

        bool operator!=(const Iterator& other) const override {
            return this->data_position != other.data_position;
        } 
    };

    Containter() override {

    }

    ~Container() override {

    }

    Iterator begin() const override {
        return Iterator(0);
    }

    Iterator end() const override {
        return Iterator(data.size());
    }

    Iterator insert(const TKey& key, const TValue& value) override {
        data.push_back(std::make_pair(key, value));
        int curr_pos = data.size() - 1;
        while (curr_pos > 0 && data[curr_pos - 1].first > data[curr_pos].first) {
            swap(data[curr_pos - 1], data[curr_pos]);
            --curr_pos;
        }
        return Iterator(curr_pos);
    }

    Iterator erase(const TKey& key) override {
        auto it = find(key);
        int pos = it.data_position;

        if (pos != data.size()) {
            while (pos < data.size() - 1) {
                swap(data[pos], data[pos + 1]);
                pos++;
            }

            data.pop_back();
        }

        return it;
    }

    Iterator find(const TKey& key) const override {

        int l = 0;
        int r = data.size() - 1;

        if (data[l].first >= key) {
            r = l;
        }

        if (data[r].first < key) {
            l = r;
        }

        while (r - l > 1) {
            int m = (l + r) / 2;
            if (data[m].first < key) {
                l = m;
            }
            else {
                r = m;
            }
        }

        if (data[r].first != key) {
            return end();
        }
        return Iterator(r);
    }

    int size() const override {
        return data.size();
    }

    bool empty() const override {
        return data.empty();
    }

    void clear() override {
        data.clear();
    }
};