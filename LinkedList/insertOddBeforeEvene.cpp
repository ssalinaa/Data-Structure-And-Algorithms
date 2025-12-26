#include <iostream>

struct Node {
    Node(int data, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void print(const Node* list) {
    while (list) {
        std::cout << list->data;
        if (list->next)
            std::cout << " -> ";
        list = list->next;
    }
    std::cout << '\n';
}

void freeList(Node* list) {
    while (list) {
        Node* toDel = list;
        list = list->next;
        delete toDel;
    }
}

Node* insertOddBeforeEven(Node* list)
{
    Node** curr = &list;   

    while (*curr)
    {
        if ( ((*curr)->data % 2) == 0 )
        {
            Node* newNode = new Node((*curr)->data + 1);

            newNode->next = *curr;
            *curr = newNode;

            curr = &((*curr)->next->next);
        }
        else
        {
            curr = &((*curr)->next);
        }
    }

    return list;
}

int main() {
    Node* list = new Node(8, new Node(2, new Node(10, new Node(4, nullptr))));

    list = insertOddBeforeEven(list); 

    print(list);
    freeList(list);
}