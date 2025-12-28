#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

template<typename T>
class AVL {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value, Node* left = nullptr, Node* right = nullptr) :
        data(value), left(nullptr), right(nullptr), height(1) { }
    };

    Node* root;

    void deallocate(Node* root) {
        if(!root) return;
        deallocate(root->left);
        deallocate(root->right);
        delete root;
    }

    Node* copy(Node* other) {
        if(!other) return nullptr;
        Node* newRoot = new Node(other->data);
        newRoot->height = other->height;
        newRoot->left = copy(other->left);
        newRoot->right = copy(other->right);
        return newRoot;
    }

    int getHeight(Node* root) const {
        return root ? root->height : 0;
    }

    int getBalance(Node* root) const {
        if(!root) return 0;
        return getHeight(root->left) - getHeight(root->right);
    }

    Node* rotateRight(Node* y) {
       Node* x = y->left;
       Node* T2 = x->right;

       x->right = y;
       y->left = T2;

       y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
       x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* insert(Node* root, const T& value) {
        if(!root) return new Node(value);
        if(value < root->data) {
            root->left = insert(root->left, value);
        }
        else if(value > root->data) {
            root->right = insert(root->right, value);
        } else {
            return root;
        }
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);

        if(balance > 1 && value < root->left->data) {
            return rotateRight(root);
        }
        if(balance < -1 && value > root->right->data) {
            return rotateLeft(root);
        }
        if(balance > 1 && value > root->left->data) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if(balance < -1 && value < root->right->data) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }

    Node* findMin(Node* root) {
        Node* current = root;
        while(current->left) {
            current = current->left;
        }
        return current;
    }

    Node* remove(Node* root, const T& value) {
        if(!root) return nullptr;
        if(value < root->data) {
            root->left = remove(root->left, value);
        }
        else if(value > root->data) {
            root->right = remove(root->right, value);
        } else {
            if(!root->left) {
                Node* temp = root->right;
                delete root;
                return temp;
            } 
            else if(!root->right) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* successor = findMin(root->right);
            root->data = successor->data;
            root->right = remove(root->right, successor->data);
        }

        if(!root) return root;

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);

        if(balance > 1 && getBalance(root->left) >= 0) {
            return rotateRight(root);
        }
        if(balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if(balance < -1 && getBalance(root->right) <= 0) {
            return rotateLeft(root);
        }
        if(balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }

    Node* search(Node* root, const T& value) const {
        if(!root) return nullptr;
        if(root->data == value) return root;
        if(value < root->data) {
            return search(root->left, value);
        }
        return search(root->right, value);
    }

    Node* searchParent(Node* root, const T& value) const {
        if(!root || (!root->left && !root->right)) return nullptr;

        if((root->left && root->left->data == value) ||
           (root->right && root->right->data == value))
            return root;

        if(value < root->data)
            return searchParent(root->left, value);
        else
            return searchParent(root->right, value);
    }

    size_t size(Node* root) const {
        if(!root) return 0;
        return 1 + size(root->left) + size(root->right);
    }

    size_t countLeaves(Node* root) const {
        if(!root) return 0;
        if(!root->left && !root->right) return 1;
        return countLeaves(root->left) + countLeaves(root->right);
    }

    int depth(Node* root, const T& value, int d) const {
        if(!root) return -1;
        if(root->data == value) return d;
        if(value < root->data) {
            return depth(root->left, value, d + 1);
        }
        return depth(root->right, value, d + 1);
    }

    void inorder(Node* root) const {
        if(!root) return;
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
    }

    void preorder(Node* root) const {
        if(!root) return;
        std::cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void postorder(Node* root) const {
        if(!root) return;
        postorder(root->left);
        postorder(root->right);
        std::cout << root->data << " ";
    }

    void printLeaves(Node* root) const {
        if(!root) return;

        if(!root->left && !root->right) {
            std::cout << root->data << " ";
            return;
        }
        printLeaves(root->left);
        printLeaves(root->right);
    }

    bool equals(Node* root1, Node* root2) const {
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;
        return root1->data == root2->data &&
               equals(root1->left, root2->left) &&
               equals(root1->right, root2->right);
    }

public:
    AVL() : root(nullptr) { }
    AVL(const AVL& other) : root(copy(other.root)) { }
    AVL& operator=(const AVL& other) {
        if(this != &other) {
            deallocate(root);
            root = copy(other.root);
        }
        return *this;
    }
    ~AVL() {
        deallocate(root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    bool search(const T& value) const {
        return search(root, value) != nullptr;
    }

    Node* searchParent(const T& value) const {
        if(!root || root->data == value) return nullptr;
        return searchParent(root, value);
    }

    void remove(const T& value) {
        root = remove(root, value);
    }

    size_t size() const {
        return size(root);
    }

    int height() const {
        return getHeight(root);
    }

    size_t countLeaves() const {
        return countLeaves(root);
    }

    int depth(const T& value) const {
        return depth(root, value, 0);
    }

    T min() const {
        Node* result = findMin(root);
        return result ? result->data : T();
    }

    bool isLeaf(const T& value) const {
        Node* result = search(root, value);
        return result && !result->left && !result->right;
    }

    std::vector<T> getChildren(const T& value) const {
        std::vector<T> result;
        Node* newRoot = search(root, value);
        if(!newRoot) return result;
        if(newRoot->left) {
            result.push_back(newRoot->left->data);
        } 
        if(newRoot->right) {
            result.push_back(newRoot->right->data);
        }
        return result;
    }

    size_t childrenCount(const T& value) const {
        Node* newRoot = search(root, value);
        if(!newRoot) return 0;
        size_t count = 0;
        if(newRoot->left) count++;
        if(newRoot->right) count++;

        return count;
    }

    bool equals(const AVL& other) const {
        return equals(this->root, other.root);
    }

    void printLeaves() const {
        printLeaves(root);
        std::cout << std::endl;
    }

    void inorder() const {
        inorder(root);
        std::cout << std::endl;
    }

    void preorder() const {
        preorder(root);
        std::cout << std::endl;
    }

    void postorder() const {
        postorder(root);
        std::cout << std::endl;
    }

    void DFS() const {
        preorder(root);
        std::cout << std::endl;
    }

    void BFS() const {
        if(!root) return;
        std::queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            Node* current = q.front();
            q.pop();
            std::cout << current->data << " ";
            if(current->left) {
                q.push(current->left);
            }
            if(current->right) {
                q.push(current->right);
            }
        }
    }

    void printLevels() const {
        if(!root) return;
        std::queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            size_t levelSize = q.size();
            while(levelSize--) {
                Node* current = q.front();
                q.pop();
                std::cout << current->data << " ";

                if(current->left) {
                    q.push(current->left);
                }
                if(current->right) {
                    q.push(current->right);
                }
            }
            std::cout << std::endl;
        }
    }

    class Iterator {
    private:
        std::stack<Node*> st;
        Node* current;

        void pushLeft(Node* root) {
            while(root) {
                st.push(root);
                root = root->left;
            }
        }

    public:
        Iterator(Node* root = nullptr) : current(nullptr) {
            pushLeft(root);
            ++(*this); 
        }

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            if(st.empty()) {
                current = nullptr;
                return *this;
            }

            current = st.top();
            st.pop();

            if(current->right) {
                pushLeft(current->right);
            }

            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
    };

    Iterator begin() {
        return Iterator(root);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

int main() {
    
    AVL<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(4);
    tree.insert(15);
    tree.insert(25);

    std::cout << "BFS (по нива): ";
    tree.BFS();
    std::cout << std::endl;

    std::cout << "DFS (preorder): ";
    tree.DFS();

    std::cout << "Inorder traversal: ";
    tree.inorder();

    std::cout << "Preorder traversal: ";
    tree.preorder();

    std::cout << "Postorder traversal: ";
    tree.postorder();

    std::cout << "Size: " << tree.size() << std::endl;
    std::cout << "Height: " << tree.height() << std::endl;
    std::cout << "Leaves count: " << tree.countLeaves() << std::endl;

    int val = 15;
    std::cout << "Depth of " << val << ": " << tree.depth(val) << std::endl;
    std::cout << val << (tree.isLeaf(val) ? " is a leaf" : " is not a leaf") << std::endl;

    std::cout << "Iterator (inorder): ";
    for(auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    tree.remove(20);
    tree.remove(5);

    std::cout << "BFS after removing 20 and 5: ";
    tree.BFS();
    std::cout << std::endl;

    std::cout << "Inorder: ";
    tree.inorder();

    return 0;
}