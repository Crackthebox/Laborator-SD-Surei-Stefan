#include <iostream>

struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void insert_beginning(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insert_end(int val) {
        Node* newNode = new Node(val);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void erase_beginning() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        size--;
    }

    void erase_end() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        size--;
    }

    Node* find_by_value(int val) {
        Node* curr = head;
        while (curr) {
            if (curr->data == val) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    Node* find_by_index(int index) {
        if (index < 0 || index >= size) return nullptr;
        Node* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr;
    }

    void insert_after(Node* node, int val) {
        if (!node) return;
        if (node == tail) {
            insert_end(val);
            return;
        }
        Node* newNode = new Node(val);
        newNode->next = node->next;
        newNode->prev = node;
        node->next->prev = newNode;
        node->next = newNode;
        size++;
    }

    void erase_node(Node* node) {
        if (!node) return;
        if (node == head) {
            erase_beginning();
            return;
        }
        if (node == tail) {
            erase_end();
            return;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size--;
    }
    
    void print() {
        Node* curr = head;
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << "\n";
    }
};

int main() {
    DoublyLinkedList list;
    list.insert_end(10);
    list.insert_end(20);
    list.insert_beginning(5);
    list.print();

    Node* target = list.find_by_index(1);
    list.insert_after(target, 15);
    list.print();

    list.erase_node(list.find_by_value(20));
    list.print();

    return 0;
}