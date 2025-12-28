#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>

template<typename T>
class GeneralTree {
private:
    struct Node {
        T data;
        std::vector<Node*> children;

        Node(const T& data) : data(data) { }
    };

    Node* root;

    void deallocate(Node* root) {
        if(!root) return;
        for(Node* child : root->children) {
            deallocate(child);
        }
        delete root;
    }

    Node* copy(Node* other) {
        if(!other) return nullptr;
        Node* newRoot = new Node(other->data);
        for(Node* child : other->children) {
            newRoot->children.push_back(copy(child));
        }
        return newRoot;
    }

    Node* search(Node* root, const T& value) const {
        if(!root) return nullptr;
        if(root->data == value) return root;
        for(Node* child : root->children) {
            if(Node* result = search(child, value)) return result;
        }
        return nullptr;
    }

    Node* searchParent(Node* root, const T& value) const {
        if(!root) return nullptr;
        for(Node* child : root->children) {
            if(child->data == value) {
                return root;
            }
            if(Node* result = searchParent(child, value)) return result;
        }
        return nullptr;
    }

    size_t size(Node* root) const {
        if(!root) return 0;
        size_t count = 1;
        for(Node* child : root->children) {
            count += size(child);
        }
        return count;
    }

    int height(Node* root) const {
        if(!root) return -1;
        int maxHeight = -1;
        for(Node* child : root->children) {
            maxHeight = std::max(maxHeight, height(child));
        }
        return maxHeight + 1;
    }

    size_t countLeaves(Node* root) const {
        if(!root) return 0;
        if(root->children.empty()) return 1;
        size_t sum = 0;
        for(Node* child : root->children) {
            sum += countLeaves(child);
        }
        return sum;
    }

    int depth(Node* root, const T& value, int d) const {
        if(!root) return -1;
        if(root->data == value) return d;
        for(Node* child : root->children) {
            int result = depth(child, value, d + 1);
            if(result != -1) return result;
        }
        return -1;
    }

    void DFS(Node* root) const {
        if(!root) return;
        std::cout << root->data << " ";
        for(Node* child : root->children) {
            DFS(child);
        }
    } 

    bool remove(Node* root, const T& value) {
        if(!root) return false;
        for(auto it = root->children.begin(); it != root->children.end(); ++it) {
            if((*it)->data == value) {
                deallocate(*it);
                root->children.erase(it);
                return true;
            }
        }
        for(Node* child : root->children) {
            if(remove(child, value)) return true;
        }
        return false;
    }

    bool equals(Node* root1, Node* root2) const {
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;
        if(root1->data != root2->data) return false;
        if(root1->children.size() != root2->children.size()) return false;

        for (size_t i = 0; i < root1->children.size(); i++)
        {
            if(!equals(root1->children[i], root2->children[i])) return false;
        }
        return true;
    }

    void printLeaves(Node* root) const {
        if(!root) return;
        if(root->children.empty()) {
            std::cout << root->data << " ";
        }
        for(Node* child : root->children) {
            printLeaves(child);
        }
    }

public:
    GeneralTree() : root(nullptr) { }
    explicit GeneralTree(const T& value) : root(new Node(value)) { }
    GeneralTree(const GeneralTree& other) : root(copy(other.root)) { }
    GeneralTree& operator=(const GeneralTree& other) {
        if(this != &other) {
            deallocate(root);
            root = copy(other.root);
        }
        return *this;
    }
    ~GeneralTree() {
        deallocate(root);
    }

    bool isEmpty() {
        return root == nullptr;
    }

    void setRoot(const T& value) {
        deallocate(root);
        root = new Node(value);
    }

    Node* getRoot() const {
        return root;
    }

    bool addChild(Node* root, const T& value) {
        if(!root) return false;
        root->children.push_back(new Node(value));
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
        return root && root->children.empty();
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

        for(Node* child : newRoot->children) {
            result.push_back(child->data);
        }
        return result;
    }

    size_t childrenCount(Node* root) const {
        return root ? root->children.size() : 0;
    }

    bool remove(const T& value) {
        if(!root) return false;
        if(root->data == value) {
            deallocate(root);
            root = nullptr;
            return true;
        }
        return remove(root, value);
    }

    bool equals(const GeneralTree& other) const {
        return equals(this->root, other.root);
    }

    void DFS() const {
        DFS(root);
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
            for(Node* child : current->children) {
                q.push(child);
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
                for(Node* child : current->children) {
                    q.push(child);
                }
            }
            std::cout << std::endl;
        }
    }

    void printLeaves() const {
        printLeaves(root);
        std::cout << std::endl;
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
            for(auto it = current->children.rbegin();
                it != current->children.rend(); ++it) {
                st.push(*it);
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

    Iterator rbegin() {
        return Iterator(root);
    }

    Iterator rend() {
        return Iterator(nullptr);
    }
};  

int main() {
    GeneralTree<std::string> tree("A");

    auto root = tree.getRoot();
    tree.addChild(root, "B");
    tree.addChild(root, "C");
    tree.addChild(root, "D");
    tree.addChild(root->children[0], "E");
    tree.addChild(root->children[0], "F");

    std::cout << "DFS:" << std::endl;
    tree.DFS();

    std::cout << "\nBFS:" << std::endl;
    tree.BFS();

    std::cout << "\nLevels:" << std::endl;
    tree.printLevels();

    std::cout << "Leaves: ";
    tree.printLeaves();

    std::cout << "\nSize: " << tree.size() << std::endl;
    std::cout << "Height: " << tree.height() << std::endl;
    std::cout << "Leaves: " << tree.countLeaves() << std::endl;
    std::cout << "Depth of F: " << tree.depth("F") << std::endl;

     std::cout << "Searching for E: " 
              << (tree.search("E") ? "found" : "not found") << std::endl;

    auto parentE = tree.searchParent("E");
    if(parentE)
        std::cout << "Parent of E: " << parentE->data << std::endl;

    auto childrenB = tree.getChildren("B");
    std::cout << "Children of B: ";
    for(auto& c : childrenB) std::cout << c << " ";
    std::cout << std::endl;

    std::cout << "B has " << tree.childrenCount(tree.search("B")) << " children" << std::endl;

    tree.remove("C");
    std::cout << "After removing C, BFS: ";
    tree.BFS();

    GeneralTree<std::string> tree2("A");
    tree2.addChild(tree2.getRoot(), "B");
    tree2.addChild(tree2.getRoot(), "D");
    tree2.addChild(tree2.getRoot()->children[0], "E");
    tree2.addChild(tree2.getRoot()->children[0], "F");

    std::cout << "tree == tree2? " 
              << (tree.equals(tree2) ? "yes" : "no") << std::endl;

    std::cout << "DFS using iterator: ";
    for(auto it = tree.rbegin(); it != tree.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
