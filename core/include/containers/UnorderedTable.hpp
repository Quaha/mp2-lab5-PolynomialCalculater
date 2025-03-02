#include <vector>
#include <iostream>

template<class TKey, class TValue>
class UnorderedTable {
private:
	std::vector<std::pair<TKey, TValue>> data;
public:
	UnorderedTable() {};
	
    class Iterator {
    public:
        std::pair<TKey, TValue>* pntr;

        Iterator(std::pair<TKey, TValue>* obj) : pntr(obj) {}

        Iterator& operator++() {
            pntr++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            pntr--;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        Iterator operator+(int step) {
            Iterator res = *this;
            if (step > 0) {
                for (int i = 0; i < step; i++) res++;
            }
            else {
                for (int i = 0; i < -step; i++) res--;
            }
            return res;
        }

        Iterator operator-(int step) {
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
            return *pntr;
        }

        std::pair<TKey, TValue>* operator->() const {
            return pntr;
        }
    };

    Iterator begin() {
        return Iterator(&data[0]);
    }
    Iterator end() {
        return Iterator(&data[data.size()]);
    }

	Iterator insert(const TKey& key, const TValue& value) {
		data.push_back({ key, value });
		return Iterator It(&data.back());
	}

	Iterator erase(const TKey& key) {
		// Возвр it на сл. элемент
		for (auto It = data.begin(); It != data.end(); It++) {
			if (It->first == key) {
                It = data.erase(It);
                return Iterator(&(*It));
			}
		}
		return end();
	}

	Iterator find(const TKey& key) {
        // Не находит - итератор на конец
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->first == key) {
                return Iterator(&(*it));
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
		// Если ключа нет, то исключение
	}

	int size() const {
        return data.size();
	}

	bool empty() const {
        return data.empty();
	}

};