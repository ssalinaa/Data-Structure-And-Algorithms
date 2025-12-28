#include <iostream>
#include <stack>

class Set {
public:
    Set() = default;
    Set(const Set& other);
    Set& operator=(const Set& other);
    ~Set();
    bool contains(int toFind) const;
    bool insert(int toAdd);
    bool remove(int toDelete);
private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        size_t subTreeSize = 1;

        static size_t getSubTreeSize(const Node* tree) {
            return tree ? tree->subTreeSize : 0;
        }
        Node(int data, Node* left = nullptr, Node* right = nullptr);
    };

    const Node* getNodeByIndex(const Node* root, size_t index) const {
        size_t leftSize = Node::getSubTreeSize(root->left);
        if(index == leftSize) {
            return root;
        }
        if(index < leftSize) {
            return getNodeByIndex(root->left, index);
        } else {
            return getNodeByIndex(root->right, index - leftSize - 1);
        }
    }

    long long getRank(const Node* root, int toRank) const {
        if(!root) {
            throw std::invalid_argument("Invalid element!");
        }
        if(root->data == toRank) {
            return Node::getSubTreeSize(root->left);
        }
        if(toRank < root->data) {
            return getRank(root->left, toRank);
        }
        long long leftSize = Node::getSubTreeSize(root->left);
        long long rightIndex = getRank(root->right, toRank);
        return leftSize + rightIndex + 1;
    }

    Node** getMin(Node** current) {
        while((*current)->left) {
            current = &(*current)->left;
        }
        return current;
    }

    Node* root = nullptr;
    void free(Node* root);
    Node* copyFrom(const Node* root);
public:
    class ConstForwardIterator {
    public:
        void pushLeft(const Set::Node* current) {
            while(current) {
                st.push(current);
                current = current->left;
            }
        }
    
        ConstForwardIterator(const Set::Node* root) {
            pushLeft(root);
        }

        ConstForwardIterator& operator++() {
            const Node* currentElement = st.top();
            st.pop();
            if(currentElement->right) {
                pushLeft(currentElement->right);
            }
            return *this;
        }

        bool operator=(const ConstForwardIterator& other) {
            return st == other.st;
        }

        bool operator!=(const ConstForwardIterator& other) {
            return st != other.st;
        }

        int operator*() const {
            return st.top()->data;
        }
    private:
        std::stack<const Node*> st;
    };

    ConstForwardIterator begin() const {
        return ConstForwardIterator(root);
    }

    ConstForwardIterator end() const {
        return ConstForwardIterator(nullptr);
    }

    int operator[](size_t index) const {
        return getNodeByIndex(root, index)->data;
    }

    long long getRank(int element) const {
        return getRank(root, element);
    }
};

Set::Set(const Set& other) {
    root = copyFrom(other.root);
}

Set& Set::operator=(const Set& other) {
    if(this != &other) {
        free(root);
        root = copyFrom(other.root);
    }
    return *this;
}

Set::~Set() {
    free(root);
    root = nullptr;
}

bool Set::contains(int toFind) const {
    Node* current = root;

    while(current) {
        if(current->data == toFind) {
            return true;
        }
        else if(toFind < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}

bool Set::insert(int toAdd) {
    Node** current = &root;

    while(*current) {
        (*current)->subTreeSize++;

        if((*current)->data == toAdd) {
            return false;
        } else if(toAdd < (*current)->data) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }
    *current = new Node(toAdd);
    return true;
}

bool Set::remove(int toDelete) {
    Node** current = &root;

    while(*current) {
        if((*current)->data == toDelete) {
            if(!(*current)->left && !(*current)->right) {
                delete* current;
                *current = nullptr;
            } else if(!(*current)->right) {
                Node* toDelete = *current;
                *current = (*current)->left;
                delete toDelete;
            } else if(!(*current)->left) {
                Node* toDelete = *current;
                *current = (*current)->right;
                delete toDelete;
            } else {
                Node** minFromRight = getMin(&(*current)->right);

                Node* toDelete = *current;
                Node* replacement = *minFromRight;

                replacement->left = toDelete->left;
                (*minFromRight) = replacement->right;

                replacement->right = toDelete->right;
                (*current) = replacement;
                delete toDelete;
            }
        } else if(toDelete < (*current)->data) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }
    return false;
}

Set::Node::Node(int data, Node* left, Node* right) : data(data), left(left), right(right) { }

void Set::free(Node* root) {
    if(!root) {
        return;
    }
    free(root->left);
    free(root->right);
    delete root;
}

Set::Node* Set::copyFrom(const Node* root) {
    if(!root) {
        return nullptr;
    }

    Node* result = new Node(root->data);
    result->left = copyFrom(root->left);
    result->right = copyFrom(root->right);

    return result;
}