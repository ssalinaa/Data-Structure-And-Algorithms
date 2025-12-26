#include <iostream>
#include <stack>

struct Node {
        int data;
        Node* next;
        Node() : data(0), next(nullptr) { }
        Node(int data) : data(data), next(nullptr) { }
        Node(int data, Node* next) : data(data), next(next) { }
};  

class Solution {
public:
    bool isPalindrome(Node* head) {
        if(!head || !head->next) return true;

        std::stack<int> st;
        Node* current = head;
        while(current) {
            st.push(current->data);
            current = current->next;
        }

        while(!st.empty()) {
            if(st.top() != head->data) {
                return false;
            }
            st.pop();
            head = head->next;
        }
        return true;
    }
private:
    Node* head;
};

int main() {   
    Solution solution;
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(2);
    head1->next->next->next = new Node(1);

    Node* head2 = new Node(1);
    head2->next = new Node(2);

    std::cout << "Is palindrome? " << std::boolalpha << solution.isPalindrome(head1) << std::endl;
    std::cout << "Is palindrome? " << std::boolalpha << solution.isPalindrome(head2) << std::endl;
    
    return 0;
}