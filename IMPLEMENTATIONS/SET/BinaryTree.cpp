#include <iostream>
#include <queue>
#include <stack>

template<typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& data, Node* left = nullptr, Node* right = nullptr) : 
        data(data), left(left), right(right) { }
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
        newRoot->left = copy(other->left);
        newRoot->right = copy(other->right);
        return newRoot;
    }

    Node* search(Node* root, const T& value) const {
        if(!root) return nullptr;
        if(root->data == value) return root;
        if(Node* result = search(root->left, value)) return result;
        return search(root->right, value);
    }

    Node* searchParent(Node* root, const T& value) const {
        if(!root) return nullptr;
        if((root->left && root->left->data == value) ||
           (root->right && root->right->data == value)) {
            return root;
        }
        if(Node* result = searchParent(root->left, value)) return result;
        return searchParent(root->right, value);
    }

    size_t size(Node* root) const {
        if(!root) return 0;
        return 1 + size(root->left) + size(root->right);
    }

    int height(Node* root) const {
        if(!root) return -1;
        return 1 + std::max(height(root->left), height(root->right));
    }

    size_t countLeaves(Node* root) const {
        if(!root) return 0;
        if(!root->left && !root->right) return 1;
        return countLeaves(root->left) + countLeaves(root->right);
    }

    int depth(Node* root, const T& value, int d) const {
        if(!root) return -1;
        if(root->data == value) return d;
        int leftDepth = depth(root->left, value, d + 1);
        if(leftDepth != -1) return leftDepth;
        return depth(root->right, value, d + 1);
    }

    bool remove(Node*& root, const T& value) {
        if(!root) return false;
        if(root->data == value) {
            deallocate(root);
            root = nullptr;
            return true;
        }

        return remove(root->left, value) || remove(root->right, value);
    }

    bool equals(Node* root1, Node* root2) {
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;
        return root1->data == root2->data &&
        equals(root1->left, root2->left) && 
        equals(root1->right, root2->right);
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

public:
    BinaryTree() : root(nullptr) { }
    explicit BinaryTree(const T& value) : root(new Node(value)) { }
    BinaryTree(const BinaryTree& other) : root(copy(other.root)) { }
    BinaryTree& operator=(const BinaryTree& other) {
        if(this != &other) {
            deallocate(root);
            root = copy(other.root);
        }
        return *this;
    }
    ~BinaryTree() {
        deallocate(root);
    }
    
    bool isEmpty() const {
        return root == nullptr;
    }

    void setRoot(const T& value) {
        deallocate(root);
        root = new Node(value);
    }

    Node* getRoot() const {
        return root;
    }

    bool addLeft(Node* root, const T& value) {
        if(!root || root->left) return false;
        root->left = new Node(value);
        return true;
    }

    bool addRight(Node* root, const T& value) {
        if(!root || root->right) return false;
        root->right = new Node(value);
        return true;
    }

    size_t size() const {
        return size(root);
    }

    int height() const {
        return height(root);
    }

    size_t countLeaves() const {
        return countLeaves(root);
    }

    bool isLeaf(Node* root) const {
        if(!root) return false;
        return root->left == nullptr && root->right == nullptr;
    }

    int depth(const T& value) const {
        return depth(root, value, 0);
    }

    Node* search(const T& value) const {
        return search(root, value);
    }

    Node* searchParent(const T& value) const {
        if(!root || root->data == value) return nullptr;
        return searchParent(root, value);
    }

    std::vector<T> getChildren(const T& value) const {
        std::vector<T> result;
        Node* newRoot = search(value);
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

    bool remove(const T& value) {
        return remove(root, value);
    }

    bool equals(const BinaryTree& other) const {
        return equals(this->root, other.root);
    }

    void printLeaves() const {
        printLeaves(root);
        std::cout << std::endl;
    }

    void preorder(Node* root) const {
        if(!root) return;
        std::cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void inorder(Node* root) const {
        if(!root) return;
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
    }

    void postorder(Node* root) const {
        if(!root) return;
        postorder(root->left);
        postorder(root->right);
        std::cout << root->data << " ";
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
        std::cout << std::endl;
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
    public:
        Iterator(Node* root = nullptr) {
            if(root) {
                st.push(root);
            }
        }

        T& operator*() {
            return st.top()->data;
        }

        Iterator& operator++() {
            Node* current = st.top();
            st.pop();

            if(current->right) {
                st.push(current->right);
            }
            if(current->left) {
                st.push(current->left);
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return st != other.st;
        }

        bool operator==(const Iterator& other) const {
            return st == other.st;
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
    BinaryTree<std::string> tree("A");

    auto root = tree.getRoot();

    tree.addLeft(root, "B");
    tree.addRight(root, "C");
    tree.addLeft(root->left, "D");
    tree.addRight(root->left, "E");
    tree.addLeft(root->right, "F");
    tree.addRight(root->right, "G");

    std::cout << "DFS (preorder): ";
    tree.DFS();

    std::cout << "BFS: ";
    tree.BFS();

    std::cout << "Size: " << tree.size() << std::endl;
    std::cout << "Height: " << tree.height() << std::endl;

    auto nodeE = tree.search("E");
    if(nodeE && tree.isLeaf(nodeE)) {
        std::cout << "E is a leaf" << std::endl;
    }

    std::cout << "Leaves: ";
    tree.printLeaves();

    auto nodeB = tree.search("B");
    std::cout << "Children of B: ";
    for(const auto& c : tree.getChildren("B"))
        std::cout << c << " ";
    std::cout << std::endl;

    std::cout << "B has " << tree.childrenCount(nodeB->data) << " children" << std::endl;

    std::cout << "Search E: "
              << (tree.search("E") ? "found" : "not found") << std::endl;

    std::cout << "Search X: "
              << (tree.search("X") ? "found" : "not found") << std::endl;

    std::cout << "Iterator DFS: ";
    for(auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    tree.remove("G");
    std::cout << "After removing G (BFS): ";
    tree.BFS();

    tree.remove("B");
    std::cout << "After removing B (BFS): ";
    tree.BFS();

    tree.remove("A");
    std::cout << "After removing root A: ";
    tree.BFS();   

    std::cout << "Tree empty? "
              << (tree.isEmpty() ? "yes" : "no") << std::endl;

    return 0;
}
