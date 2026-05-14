#include <iostream>
#include <stdexcept>

class MyVector {
private:
    int* arr;
    int capacity;
    int current_size;

public:
    MyVector() {
        capacity = 1;
        current_size = 0;
        arr = new int[capacity];
    }

    ~MyVector() {
        delete[] arr;
    }

    void init() {
        delete[] arr;
        capacity = 1;
        current_size = 0;
        arr = new int[capacity];
    }

    void push_back(int value) {
        if (current_size == capacity) {
            capacity *= 2;
            int* temp = new int[capacity];
            
            for (int i = 0; i < current_size; i++) {
                temp[i] = arr[i];
            }
            
            delete[] arr;
            arr = temp;
        }
        arr[current_size] = value;
        current_size++;
    }

    void pop_back() {
        if (current_size > 0) {
            current_size--;
        }
    }

    int get_size() const {
        return current_size;
    }
};