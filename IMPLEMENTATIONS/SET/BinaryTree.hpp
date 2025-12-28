#include <iostream>
#include <stack>
#include <string>

class BinaryTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(const int &data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) { }
    };

    Node* root = nullptr;

    static Node* copyNode(const Node* other) {
        if(!other) {
            return nullptr;
        }

        Node* result = new Node(other->data);
        result->left = copyNode(other->left);
        result->right = copyNode(other->right);
        return result;
    }

    static void freeNode(Node* root) {
        if(!root) {
            return;
        }
        freeNode(root->left);
        freeNode(root->right);
        delete root;
    }
public:
    class TreePosition {
        friend class BinaryTree;
        Node** current;

    public:
        TreePosition(Node** current) : current(current) { }
        TreePosition goLeft() const {
            return TreePosition(&(*current)->left);
        }
        TreePosition goRight() const {
            return TreePosition(&(*current)->right);
        }
        int& get() {
            return (*current)->data;
        }
        int get() const {
            return (*current)->data;
        }
    };

    BinaryTree() = default;

    BinaryTree(const BinaryTree& other) {
        root = copyNode(other.root);
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if(this != &other) {
            free();
            root = copyNode(other.root);
        }
        return *this;
    }

    ~BinaryTree() {
        free();
    }

    void free() {
        freeNode(root);
        root = nullptr;
    }

    void erase(TreePosition position) {
        if(!*position.current) {
            return;
        }

        erase(position.goLeft());
        erase(position.goRight());

        delete (*position.current);
        (*position.current) = nullptr;
    }

    void add(const std::string& path, int element) {
        TreePosition current(&root);
        for(char ch : path) {
            if(!*current.current) {
                *current.current = new Node(0);
            }
            if(ch == 'L') {
                current = current.goLeft();
            } else {
                current = current.goRight();
            }
        }
        if(!*current.current) {
            *current.current = new Node(element);
        } else {
            (*current.current)->data = element;
        }
    }

    void printInOrder() const {
        printInOrder(root);
        std::cout << std::endl;
    }
private:
    static void printInOrder(Node* root) {
        if(!root) {
            return;
        }
        printInOrder(root->left);
        std::cout << root->data << " ";
        printInOrder(root->right);  
    }
};