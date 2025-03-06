#include <iostream>

template <class TKey, class TValue> class Container {
public:
    class Iterator {
    public:
        virtual ~Iterator() = default;

        virtual std::pair<TKey, TValue&> operator*() = 0;

        virtual Iterator& operator++() = 0;
        virtual Iterator& operator--() = 0;

        virtual Iterator operator++(int) = 0;
        virtual Iterator operator--(int) = 0;

        virtual bool operator==(const Iterator& other) const = 0;
        virtual bool operator!=(const Iterator& other) const = 0;
    };

    virtual Container() = 0;
    virtual ~Container() = 0;

    virtual Iterator begin() const = 0;
    virtual Iterator end() const = 0;

    virtual Iterator insert(const TKey& key, const TValue& value) = 0;
    virtual Iterator erase(const TKey& key) = 0;
    virtual Iterator find(const TKey& key) const = 0;

    virtual int size() const = 0;
    virtual bool empty() const = 0;

    virtual void clear() = 0;

    bool isExist(const TKey& key) const {
        return this->find(key) != this->end();
    }

    TValue& operator[](const TKey& key) {
        if (!this->isExist(key)) {
            this->insert(key, TValue());
        }
        return (*this->find(key)).second;
    }

    const TValue& operator[](const TKey& key) const {
        if (!this->isExist(key)) {
            throw std::out_of_range("ERROR: Incorrect key!");
        }
        return (*this->find(key)).second;
    }
};
