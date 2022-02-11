//
// Created by Maxim Insapov on 10.02.2022.
//

#include <iostream>

#define def_queue

template <typename T>
class ICircularBoundedQueue {
    virtual void offer(T value) = 0;
    virtual T poll() = 0;
    virtual T peek() = 0;
    virtual void flush() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual int size() = 0;
    virtual int capacity() = 0;
};


template <typename T, int array_size>
class ArrayCircularBoundedQueue : ICircularBoundedQueue<T> {
private:
    T arr[array_size] = {-1};
    int begin;
    int end;
    bool init;
    bool can_be_empty;
public:
    ArrayCircularBoundedQueue() {
        begin = 0;
        end = 0;
        init = true;
        can_be_empty = true;
    };

    void offer(T value) override { // O(1) because does not depend on size of queue
        // inserts element after "end" mark and moves "begin" if necessary

        arr[end] = value;

        if (end == begin && !init) {
            begin = (begin + 1) % array_size;
        }
        can_be_empty = false;
        end = (end + 1) % array_size;
        init = false;
    }

    T poll() override { // O(1) because does not depend on size of queue
        // returns first element if it exists and useless data otherwise
        T elem = arr[begin];

        begin = (begin + 1) % array_size;

        if (begin == end) {
            init = true;
        }
        can_be_empty = true;
        return elem;
    }

    T peek() override { // O(1) because does not depend on size of queue
        return arr[begin];
    }

    void flush() override { // O(1) because does not depend on size of queue
        // actually we don't need to erase the data we can only move marks into initial state
        begin = 0;
        end = 0;
    }

    bool isEmpty() override { // O(1) because does not depend on size of queue
        return begin == end;
    }

    bool isFull () override { // O(1) because does not depend on size of queue
        return (begin == 0 && end == array_size - 1) || (end + 1 == begin);
    }

    int size() override { // O(1) because does not depend on size of queue
        // calculates the size of queue based on position of marks
        if (end == begin) {
            return can_be_empty ? 0 : array_size;
        }

        if (end > begin) {

            return end - begin;
        } else {

            return (array_size - begin) + end;
        }
    }

    void debug() {
        // just prints array and positions of marks
        for (int i = 0; i < array_size; ++i) {
            if (i == begin) std::cout << "(begin)";
            if (i == end) std::cout << "(end)";
            std::cout << arr[i] << " ";
        }

        std::cout << std::endl;
    }

    int capacity() override { // O(1)
        return array_size;
    }
};