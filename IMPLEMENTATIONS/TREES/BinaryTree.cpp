#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    Node* copy(Node* other) {
        if (!other) return nullptr;
        Node* newNode = new Node(other->data);
        newNode->left = copy(other->left);
        newNode->right = copy(other->right);
        return newNode;
    }

public:
    BinaryTree() : root(nullptr) {}
    BinaryTree(const BinaryTree& other) : root(copy(other.root)) {}
    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            destroy(root);
            root = copy(other.root);
        }
        return *this;
    }
    ~BinaryTree() { destroy(root); }

    Node* getRoot() const { return root; }
    void setRoot(Node* node) { destroy(root); root = node; }

    void insert(const T& value) {
        Node* newNode = new Node(value);
        if (!root) {
            root = newNode;
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (!current->left) {
                current->left = newNode;
                return;
            } else {
                q.push(current->left);
            }

            if (!current->right) {
                current->right = newNode;
                return;
            } else {
                q.push(current->right);
            }
        }
    }

    // ===== Search =====
    bool search(Node* node, const T& value) const {
        if (!node) return false;
        if (node->data == value) return true;
        return search(node->left, value) || search(node->right, value);
    }

    bool search(const T& value) const {
        return search(root, value);
    }

    // ===== Remove (премахва първия възел с дадена стойност) =====
    bool remove(Node* parent, Node* node, const T& value) {
        if (!node) return false;
        if (node->data == value) {
            if (parent) {
                if (parent->left == node) parent->left = nullptr;
                else if (parent->right == node) parent->right = nullptr;
            } else {
                root = nullptr; // изтриване на root
            }
            destroy(node);
            return true;
        }
        return remove(node, node->left, value) || remove(node, node->right, value);
    }

    bool remove(const T& value) {
        return remove(nullptr, root, value);
    }

    // ===== Размер, височина, листа =====
    size_t size() const {
        std::function<size_t(Node*)> f = [&](Node* n) {
            if (!n) return size_t(0);
            return 1 + f(n->left) + f(n->right);
        };
        return f(root);
    }

    int height() const {
        std::function<int(Node*)> f = [&](Node* n) {
            if (!n) return -1;
            return 1 + std::max(f(n->left), f(n->right));
        };
        return f(root);
    }

    size_t countLeaves() const {
        std::function<size_t(Node*)> f = [&](Node* n) {
            if (!n) return 0;
            if (!n->left && !n->right) return 1;
            return f(n->left) + f(n->right);
        };
        return f(root);
    }

    int depth(const T& value) const {
        int result = -1;
        std::function<bool(Node*, int)> f = [&](Node* n, int current) {
            if (!n) return false;
            if (n->data == value) { result = current; return true; }
            return f(n->left, current + 1) || f(n->right, current + 1);
        };
        f(root, 0);
        return result;
    }

    // ===== Print функции =====
    void printInorder(Node* node) const {
        if (!node) return;
        printInorder(node->left);
        std::cout << node->data << " ";
        printInorder(node->right);
    }

    void printInorder() const { printInorder(root); std::cout << std::endl; }

    void printPreorder(Node* node) const {
        if (!node) return;
        std::cout << node->data << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }

    void printPreorder() const { printPreorder(root); std::cout << std::endl; }

    void printPostorder(Node* node) const {
        if (!node) return;
        printPostorder(node->left);
        printPostorder(node->right);
        std::cout << node->data << " ";
    }

    void printPostorder() const { printPostorder(root); std::cout << std::endl; }

    void printBFS() const {
        if (!root) return;
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* node = q.front(); q.pop();
            std::cout << node->data << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        std::cout << std::endl;
    }

    // ===== Iterator (preorder) =====
    class iterator {
    private:
        std::stack<Node*> stk;
    public:
        iterator(Node* root) { if (root) stk.push(root); }
        bool operator!=(const iterator& other) const { return stk != other.stk; }
        T& operator*() { return stk.top()->data; }
        iterator& operator++() {
            Node* node = stk.top(); stk.pop();
            if (node->right) stk.push(node->right);
            if (node->left) stk.push(node->left);
            return *this;
        }
    };

    iterator begin() { return iterator(root); }
    iterator end() { return iterator(nullptr); }
};

int main() {
    BinaryTree<int> tree;

    tree.insert(1); // root
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    std::cout << "Preorder: ";
    tree.printPreorder();

    std::cout << "BFS: ";
    tree.printBFS();

    std::cout << "Size: " << tree.size() << std::endl;
    std::cout << "Height: " << tree.height() << std::endl;
    std::cout << "Leaves: " << tree.countLeaves() << std::endl;
    std::cout << "Depth of 5: " << tree.depth(5) << std::endl;

    tree.remove(3);
    std::cout << "After removing 3, BFS: ";
    tree.printBFS();

    std::cout << "Preorder via iterator: ";
    for (auto& x : tree) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}
