#include <iostream>
#include "queue.cpp"
#include "stack.cpp"

template <typename T>
void expect(T result, T expected) {
    if (result != expected) {
        std::cout << "FAIL: " << result << " expected: " << expected << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }
}

void test_queue() {
    ArrayCircularBoundedQueue<int, 5> queue;

    queue.offer(1);
    queue.offer(2);
    queue.offer(3);
    expect(queue.size(), 3);
    expect(queue.poll(), 1);
    expect(queue.poll(), 2);
    expect(queue.poll(), 3);
    queue.debug();

    queue.offer(4);
    queue.offer(5);

    queue.debug();

    expect(queue.poll(), 4);

    expect(queue.size(), 1);

    queue.offer(6);
    queue.offer(7);
    queue.offer(8);
    queue.offer(9);
    queue.offer(10);
    queue.offer(11);

    expect(queue.poll(), 7);
    expect(queue.poll(), 8);
}

void test_stack() {
    QueuedBoundedStack<int, 5> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    expect(stack.pop(), 3);
    expect(stack.pop(), 2);
    expect(stack.size(), 1);

    stack.debug();

    stack.push(4);
    stack.debug();
    stack.push(5);
    stack.debug();
    stack.push(6);
    stack.debug();
    stack.push(7);
    stack.debug();
    stack.push(8);

    stack.debug();

    expect(stack.top(), 8);
    expect(stack.pop(), 8);

    stack.debug();
    expect(stack.size(), 4);
}

int main() {

    test_stack();

    return 0;
}


