#pragma once

#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>

template <class TKey, class TValue>
class HashTableOA {
protected:
	struct dataCell {
		std::pair<TKey, TValue> element;
		int status = 0;
		// 0-empty 
		// 1-occupied 
		// 2-deleted

		dataCell() = default;
		dataCell(TKey key, TValue value) : element(key, value), status(1) {}
	};

	std::vector<dataCell> data;
	int amountOfElements = 0;
	int usedCells = 0;

	int getHash(const TKey& key) const {
		std::hash<TKey> hasher;
		int hash = hasher(key);
		return hash;
	}

	int hashFunction(const TKey& key) const {
		int hash = getHash(key);
		return hash % data.size();
	}

	int iteratingFunction(int pntr) const {
		return (pntr + 1) % data.size();
	}

	void rebuildTable(int newCapacity) {
		std::vector<dataCell> oldData = std::move(data);
		data.clear();
		data.resize(newCapacity);
		amountOfElements = 0;
		usedCells = 0;

		for (auto& cell : oldData) {
			if (cell.status == 1) {
				int pntr = hashFunction(cell.element.first);
				int checkedElements = 0;
				while (checkedElements != data.size()) {
					checkedElements++;
					if (data[pntr].status != 1) {
						data[pntr].status = 1;
						data[pntr].element = cell.element;
						amountOfElements++;
						usedCells++;
						break;
					}
					pntr = iteratingFunction(pntr);
				}
			}
		}
	}

	void rebuildCheck() {
		double loadFactor = double(usedCells) / double(data.size());
		if (loadFactor > 0.7) {
			int newSize = std::max(amountOfElements * 2, int(data.size() * 2));
			rebuildTable(newSize);
		}
	}

public:
	class Iterator {

		const std::vector<dataCell>* dataPntr;
		int pntr;

	public:

		Iterator(const std::vector<dataCell>* data) : dataPntr(data), pntr(0) {
			while (pntr < dataPntr->size() && (*dataPntr)[pntr].status != 1) {
				pntr++;
			}
		}
		Iterator(const std::vector<dataCell>* data, int pntr) : dataPntr(data), pntr(pntr) {}

		/*
		std::pair<TKey, TValue> operator*() {
			if (pntr == dataPntr->size()) throw std::runtime_error("Can't get value from empty iterator");
			return (*dataPntr)[pntr].element;
		}
		*/
		std::pair<TKey, TValue>& operator*() {
			if (pntr == dataPntr->size()) throw std::runtime_error("Can't get value from empty iterator");
			return const_cast<std::pair<TKey, TValue>&>((*dataPntr)[pntr].element);
		}

		const std::pair<TKey, TValue>& operator*() const {
			if (pntr == dataPntr->size()) throw std::runtime_error("Can't get value from empty iterator");
			return (*dataPntr)[pntr].element;
		}

		/*
		std::pair<TKey, TValue>* operator->() {
			if (pntr == dataPntr->size()) throw std::runtime_error("Can't get value from empty iterator");
			return &const_cast<dataCell&>((*dataPntr)[pntr]).element;
		}
		*/
		std::pair<TKey, TValue>* operator->() {
			if (pntr == dataPntr->size()) throw std::runtime_error("Can't get value from empty iterator");
			return &const_cast<std::pair<TKey, TValue>&>((*dataPntr)[pntr].element);
		}

		const std::pair<TKey, TValue>* operator->() const {
			if (pntr == dataPntr->size()) throw std::runtime_error("Can't get value from empty iterator");
			return &((*dataPntr)[pntr].element);
		}


		bool operator==(const Iterator& it) const {
			return pntr == it.pntr && dataPntr == it.dataPntr;
		}

		bool operator!=(const Iterator& it) const {
			return !(*this == it);
		}

		Iterator& operator++() {
			pntr++;
			while (pntr < dataPntr->size() && (*dataPntr)[pntr].status != 1) {
				pntr++;
			}
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		int getStatus() {
			return (*dataPntr)[pntr].status;
		}

		void changeStatus(int status) {
			const_cast<dataCell&>((*dataPntr)[pntr]).status = status;
		}
	};

	HashTableOA(int startingCapacity = 5) {
		data.resize(startingCapacity);
	}

	Iterator begin() const {
		return Iterator(&data);
	}

	Iterator end() const {
		return Iterator(&data, data.size());
	}

	Iterator insert(const TKey& key, const TValue& val) {
		if (find(key) != end()) throw std::runtime_error("Inserting element with already existing key");

		rebuildCheck();

		amountOfElements++;
		usedCells++;

		int pntr = hashFunction(key);
		int checkedElements = 0;
		while (checkedElements != data.size()) {
			checkedElements++;
			if (data[pntr].status == 0) {
				data[pntr].status = 1;
				data[pntr].element.first = key;
				data[pntr].element.second = val;
				return Iterator(&data, pntr);
			}
			pntr = iteratingFunction(pntr);
		}

		throw std::runtime_error("Something went wrong in insert function");
	}

	Iterator find(const TKey& key) const {
		int pntr = hashFunction(key);
		int checkedElements = 0;
		while (checkedElements != data.size()) {
			checkedElements++;
			if (data[pntr].status == 0) return end();
			if (data[pntr].status == 1 && data[pntr].element.first == key) {
				return Iterator(&data, pntr);
			}
			pntr = iteratingFunction(pntr);
		}
		return end();
	}

	Iterator erase(const TKey& key) {
		auto it = find(key);
		if (it == end()) return end();

		amountOfElements--;
		it.changeStatus(2);
		return ++it;
	}

	TValue& operator[](const TKey& key) {
		auto it = find(key);
		if (it != end()) {
			return (*it).second;
		}
		else {
			throw std::runtime_error("Cant access non existing element");
		}
	}

	const TValue& operator[](const TKey& key) const {
		auto it = find(key);
		if (it != end()) {
			return (*it).second;
		}
		else {
			throw std::runtime_error("Cant access non existing element");
		}
	}

	void clear() {
		data.clear();
		data.resize(5);
		amountOfElements = 0;
		usedCells = 0;
	}

	int size() const {
		return amountOfElements;
	}

	int capacity() const {
		return data.size();
	}

	bool empty() const {
		return amountOfElements == 0;
	}

	bool isExist(const TKey& key) const {
		Iterator it = find(key);
		return !(it == end());
	}
};

template <typename TKey, typename TValue>
class TestableHashTableOA : public HashTableOA<TKey, TValue> {

	int getHash(const TKey& key) const {
		return 0;
	}
};

