#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void detectAndAnalyzeCycle(ListNode* head) {
    ListNode *slow = head;
    ListNode *fast = head;
    bool hasCycle = false;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }

    if (!hasCycle) {
        std::cout << "No cycle detected.\n";
        return;
    }

    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    std::cout << "Cycle starts at node with value: " << slow->val << "\n";

    int cycleLength = 1;
    ListNode* curr = slow->next;
    while (curr != slow) {
        cycleLength++;
        curr = curr->next;
    }

    std::cout << "Cycle length: " << cycleLength << "\n";
}

int main() {
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    ListNode* n4 = new ListNode(4);
    ListNode* n5 = new ListNode(5);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n3; 

    detectAndAnalyzeCycle(n1);

    return 0;
}