//
// Created by Maxim Insapov on 10.02.2022.
//

#include <iostream>

#ifndef def_queue
#include "queue.cpp"
#define def_queue
#endif

#define def_stack

template <typename T>
class IBoundedStack {
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() = 0;
    virtual void flush() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual int size() = 0;
    virtual int capacity() = 0;
};

// I decided to implement stack with O(n) pop because in stack lifetime [pop quantity] <= [push quantity]
// so in some situations pops will be more rare than pushes. In my opinion, this approach is slightly more efficient.
// Also, I wanted to make a flag that contains in which queue elements are located. I thought that it will
// be rational to avoid moving elements back to first queue, but the amount of code doubled, so I sacrificed
// some time on pops to make code more readable.


template <typename T, int array_size>
class QueuedBoundedStack : IBoundedStack<T> {
private:
    ArrayCircularBoundedQueue<T, array_size> queue1, queue2;
public:
    QueuedBoundedStack() = default;

    void push(T value) override { // O(1)
        // we just push element to the primary queue
        queue1.offer(value);
    }

    T pop() override { // O(n) worst
        // we move all elements from first queue to second except the last and then move them back
        int queue_size = queue1.size();
        for (int i = 0; i < queue_size - 1; ++i) {

            queue2.offer(queue1.poll());
        }
        T elem = queue1.poll();

        queue_size = queue2.size();
        for (int i = 0; i < queue_size; ++i) {

            queue1.offer(queue2.poll());
        }

        return elem;
    }

    T top() override { // O(n) worst
        // we shift our queue to the last element

        int queue_size = queue1.size();
        for (int i = 0; i < queue_size - 1; ++i) {

            queue1.offer(queue1.poll());
        }

        T elem = queue1.poll();

        queue1.offer(elem);
        return elem;
    }

    void flush() override {
        queue1.flush();
    }

    void debug() {
        queue1.debug();
    }

    bool isEmpty() override {
        return queue1.isEmpty();
    }

    bool isFull () override {
        return queue1.isFull();
    }

    int size() override {
        return queue1.size();
    }

    int capacity() override {
        return array_size;
    }
};
