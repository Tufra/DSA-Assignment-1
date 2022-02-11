//
// Created by Maxim Insapov on 11.02.2022.
//

#include <functional>

template <typename T>
class ISet {
    virtual void add(T item) = 0;
    virtual void remove(T item) = 0;
    virtual bool contains(T item) = 0;
    virtual int size() = 0;
    bool isEmpty() = 0;
};

template <typename T>
class DoubleHashSet : ISet<T> {
private:
    static const int SIZE = 1032943;
    static const int SEC_SIZE = 47737;
    T table[SIZE] = {nullptr};

    int primary_hash(T key) {
        return std::hash(key) % SIZE;
    }

    int secondary_hash(T key) {
        return SEC_SIZE - (std::hash(key) % SEC_SIZE);
    }

public:

    DoubleHashSet() = default;

    void add(T item) override {
        int hash = primary_hash(item);
        if (table[hash] == nullptr || table[hash] == item) {
            table[hash] = item;
        } else {
            for (int i = 1; i < SIZE; ++i) {
                hash = secondary_hash(item, i);
                if (table[hash] == nullptr || table[hash] == item) {
                    table[hash] = item;
                    return;
                }
            }
        }
    }

    void remove(T item) override {
        int hash = primary_hash(item);
        if (table[hash] == item) {
            table[hash] = nullptr;
        } else {
            for (int i = 1; i < SIZE; ++i) {
                hash = secondary_hash(item, i);
                if (table[hash] == item) {
                    table[hash] = nullptr;
                    return;
                }
            }
        }
    }

    bool contains(T item) override {
        int hash = primary_hash(item);
        if (table[hash] == item) {
            return true;
        } else {
            for (int i = 1; i < SIZE; ++i) {
                hash = secondary_hash(item, i);
                if (table[hash] == item) {
                    return true;
                }
            }
        }
        return false;
    }

    int size() override {
        for (int i = 0; i < ; ++i) {
            
        }
    }
};