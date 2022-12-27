#include "BST.h"

template <typename T>
BST<T>::BST(T val) {
    root = new Node(val);
    root->parent = nullptr;
}

template <typename T>
BST<T>::BST(BST<T>&& rhs) {

}

template <typename T>
BST<T>::BST(const BST<T>& rhs) {
    if (rhs.root == nullptr) {
        return;
    }
    copy_help(this->root, rhs.root);
}

template <typename T>
BST<T>::~BST() {
    if (root != nullptr) {
        this->clear();
    }
}

template <typename T>
void BST<T>::copy_help(Node*& head, const Node* rhs) {
    if (!rhs) {
        return;
    }
    head = new Node(rhs->data);
    copy_help(head->right, rhs->right);
    copy_help(head->left, rhs->left);
}

template <typename T>
T BST<T>::get_root_data() {
    return root->data;
}

template <typename T>
void BST<T>::insert(T val) {
    if (root == nullptr) {
        root = new Node(val);
        return;
    }
    insert_help(root, val);
}

template <typename T>
void BST<T>::insert_help(Node*& head, T val) {
    if (head == nullptr) {
        head = new Node(val);
        return;
    }
    if (val < head->data) {
        insert_help(head->left, val);
        return;
    }
    insert_help(head->right, val);
}

template <typename T>
void BST<T>::levelorder() {
    if (root != nullptr) {
        std::cout << this->root->data << " ";
        levelorder_help(this->root);
    }
}

template <typename T> 
void BST<T>::levelorder_help(Node* head) {
    if (!head) {
        return;
    }
    if (head->left != nullptr) {
        std::cout << head->left->data << " " ;
    }
    if (head->right != nullptr) {
        std::cout << head->right->data << " ";
    }
    levelorder_help(head->left);
    levelorder_help(head->right);
}

template <typename T>
typename BST<T>::Node* BST<T>::find(T val) {
    if (root == nullptr) {
        return root;
    }
    return find_help(root, val);
}

template <typename T>
typename BST<T>::Node*  BST<T>::find_help(Node* head, T val) {
    if (head == nullptr) {
        return nullptr;
    }
    if (head->data == val) {
        return head;
    }
    if (head->data > val) {
        return find_help(head->left, val);
    }
    return find_help(head->right, val);
}

template <typename T>
bool BST<T>::contains(T val) {
    return (this->find(val) != nullptr);
}

template <typename T>
std::size_t BST<T>::get_high() {
    if (root != nullptr) {
        return high_help(root);
    }
    return 0;
}

template <typename T>
std::size_t BST<T>::high_help(Node* head) {
    int high = 0;
    if (head != nullptr) {
        int r_high = high_help(head->right);
        int l_high = high_help(head->left);
        high = std::max(r_high, l_high) + 1;
    }
    return high;
}

template <typename T>
void BST<T>::clear() {
    if (this->root != nullptr) {
        clear_help(root);
    }
}

template <typename T>
void BST<T>::clear_help(Node*& head) {
    if(head != nullptr)
    {
        clear_help(head->left);
        clear_help(head->right);
        delete(head);
        if(head->left != nullptr) {
            head->left = nullptr;
        }
        if(head->right != nullptr) {
            head->right = nullptr;
        }
        head = nullptr; 
    }
}


template <typename T>
void BST<T>::preorder() {
    printPreOreder(root);
}

template <typename T>
void BST<T>::printPreOreder(Node* head) {
    if (head != nullptr) {
        std::cout << " " << head->data;
        printPreOreder(head->left);
        printPreOreder(head->right);
    }
}


template <typename T>
void BST<T>::postorder() {
    printPreOreder(root);
}

template <typename T>
void BST<T>::printpostorder(Node* head) {
    if (head != nullptr) {
        printpostorder(head->left);
        printpostorder(head->right);
        std::cout << " " << head->data;
    }
}