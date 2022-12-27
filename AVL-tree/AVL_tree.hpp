#include "AVL_tree.h"

template <typename T>
AVL<T>::Node::Node()
: left{nullptr}
, right{nullptr}
, data{}
{}

template <typename T>
AVL<T>::Node::Node(const T& val, Node* l, Node* r)
: left{l}
, right{r}
, data{val}
{}

template <typename T>
AVL<T>::AVL() 
: root{nullptr}
, number_node{0}
{}

template <typename T>
AVL<T>::AVL(const T& rhs) {
    root = new Node(rhs);
    number_node = 1;
} 

template <typename T>
AVL<T>::AVL(T&& rhs) {
    root = new Node(rhs);
    number_node = 1;
}

template <typename T>
AVL<T>::AVL(std::initializer_list<T> init)
: root{nullptr}
{
    for (auto it : init) {
        this->insert(it);
    }
}

template <typename T>
AVL<T>::AVL(const AVL<T>& rhs) {
    if (rhs.root == nullptr) { 
        this->root = nullptr;
        return;
    }
    root = copy_help(rhs.root);
}

template <typename T>  
typename AVL<T>::Node* AVL<T>::copy_help(const Node* rhs) {
    if (rhs == nullptr) { return nullptr;}
    return new Node(rhs->data, copy_help(rhs->left), copy_help(rhs->right));
}

template <typename T>
AVL<T>::AVL(AVL<T>&& rhs) {
    this->root = rhs.root;
    rhs.root = nullptr;
}

template <typename T>
AVL<T>& AVL<T>::operator=(const AVL<T>& rhs) {
    if (this->root == rhs.root) {
        return *this;
    }
    if (rhs.root == nullptr) {
        this->clear();
        this->root = nullptr;
        return *this;
    }
    this->clear();
    this->root = copy_help(rhs.root);
    return *this;
}

template <typename T>
AVL<T>& AVL<T>::operator=(AVL<T>&& rhs) {
    if (*this == &rhs) {
        return *this;
    }
    this->clear();
    this->root = rhs.root;
    rhs.root = nullptr;
    return *this;
}

template <typename T>
AVL<T>::~AVL() {
    this->clear();
}

template <typename T>
void AVL<T>::clear() {
    if (root == nullptr) {
        return;
    }
    this->clear_help(root);
    this->root = nullptr;
}

template <typename T>
void AVL<T>::clear_help(Node* t) {
    if (t == nullptr) { return; }
    clear_help(t->left);
    clear_help(t->right);
    delete t;
}

template <typename T>
int AVL<T>::node_high(Node* t) {
    if (t == nullptr) { return 0;}
    return 1 + std::max(node_high(t->left), node_high(t->right));
}

template <typename T>
int AVL<T>::balanc_factor(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return node_high(t->left) - node_high(t->right);
}

template <typename T>
void AVL<T>::get_balance(Node*& t) {
    if (t->left == nullptr && t->right == nullptr) {
        return;
    }
    int bf = balanc_factor(t);
    if (bf < -1 && t->right->left == nullptr) {
        t = left_left_rotation(t);
    }
    if (bf > 1 && t->left->right == nullptr) {
        t = right_right_rotation(t);
    }
    if (bf < -1 && t->right->left != nullptr) {
        t = left_right_rotation(t);
    }
    if (bf > 1 && t->left->right != nullptr) {
        t = right_left_rotation(t);
    }
    
}

template <typename T>
typename AVL<T>::Node* AVL<T>::left_left_rotation(Node*& t) {
    Node* tmp = t->right;
    Node* tmp_2 = tmp->left;
    tmp->left = t;
    t->right = tmp_2;
    return tmp;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::right_right_rotation(Node*& t) {
    Node* tmp = t->left;
    Node* tmp_2 = tmp->right;
    tmp->right = t;
    t->left = tmp_2;
    return tmp;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::right_left_rotation(Node*& t) {
    t->right = right_right_rotation(t->right);
    return left_left_rotation(t);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::left_right_rotation(Node*& t) {
    t->left = left_left_rotation(t->left);
    return right_right_rotation(t);
}

template <typename T>
void AVL<T>::insert(const T& rhs) {
    if (root == nullptr) {
        root = new Node(rhs);
        ++this->number_node;
        return;
    }
    this->insert_help(root, rhs);        
}

template <typename T>
void AVL<T>::insert(T&& rhs) {
    if (root == nullptr) {
        root = new Node(rhs);
        ++this->number_node;
        return;
    }
    this->insert_help(root, rhs);        
}

template <typename T>
void AVL<T>::insert_help(Node*& t, const T& rhs) {
    if (t == nullptr) {
        t = new Node(rhs);
        ++this->number_node;
    }
    if (t->data > rhs) {
        insert_help(t->left, rhs);
    } else if (t->data < rhs) {
        insert_help(t->right, rhs);
    }
    int bf = balanc_factor(root);
    if (bf < -1 || bf > 1) {
        get_balance(t);
    }
}


template <typename T>
typename AVL<T>::Node* AVL<T>::find(const T& rhs) {
    if (root == nullptr) {
        return nullptr;
    }
    return find_help(root, rhs);
}



template <typename T>
typename AVL<T>::Node* AVL<T>::find(T&& rhs) {
    if (root == nullptr) {
        return nullptr;
    }
    return find_help(root, rhs);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::find_help(Node* t, const T& rhs) {
    if (t == nullptr) {
        return nullptr;
    }
    if (t->data == rhs) {
        return t;
    } else if (t->data > rhs) {
        return find_help(t->left, rhs);
    } else if (t->data < rhs) {
        return find_help(t->right, rhs);
    }
    return nullptr;
}

template <typename T>
bool AVL<T>::contains(const T& rhs)  {
    return this->find(rhs) != nullptr;
}

template <typename T>
bool AVL<T>::contains(T&& rhs)  {
    return this->find(rhs) != nullptr;
}

template <typename T>
void AVL<T>::preorder() {
    if (root == nullptr) {
        return;
    }
    preorder_help(root);
}

template <typename T>
void AVL<T>::preorder_help(Node* t) {
    if (t == nullptr) {
        return;
    }
    std::cout << t->data << " ";
    preorder_help(t->left);
    preorder_help(t->right);
}

template <typename T>
void AVL<T>::postorder() {
    if (root == nullptr) {
        return ;
    }
    this->postorder_help(root);
}

template <typename T>
void AVL<T>::postorder_help(Node* t) {
    if (t == nullptr) {
        return ;
    }
    postorder_help(t->left);
    postorder_help(t->right);
    std::cout << t->data << " ";
}

template <typename T>
void AVL<T>::inorder() {
    if (root == nullptr) {
        return ;
    }
    this->inorder_help(root);
}

template <typename T>
void AVL<T>::inorder_help(Node* t) {
    if (t == nullptr) {
        return ;
    }
    inorder_help(t->left);
    std::cout << t->data << " ";
    inorder_help(t->right);
}


template <typename T>
void AVL<T>::levelorder() {
    if (root == nullptr) {
        return ;
    }
    int high = node_high(root);
    for (int i = 0; i < high; ++i) {
        levelorder_help(root, i);
    }
}

template <typename T>
void AVL<T>::levelorder_help(Node* t, int h) {
    if (t == nullptr) {
        return ;
    }
    if (h == 0) {
        std::cout << t->data << " ";
    } else {
        levelorder_help(t->left, h - 1);
        levelorder_help(t->right, h - 1);
    }
}

template <typename T>
int AVL<T>::number_of_nodes() const {
    return this->number_node;
}

template <typename T>
T AVL<T>::get_root_data() {
    return this->root->data;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::find_min() const {
    return find_min_help(root);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::find_max() const {
    return find_max_help(root);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::find_max_help(Node* t) const {
    if (t == nullptr) {
        return nullptr;
    }
    if (t->right == nullptr) {
        return t;
    }
    return find_max_help(t->right);
}


template <typename T>
typename AVL<T>::Node* AVL<T>::find_min_help(Node* t) const {
    if (t == nullptr) {
        return nullptr;
    }
    if (t->left == nullptr) {
        return t;
    }
    return find_min_help(t->left);
}

template <typename T>
void AVL<T>::erase(const T& rhs) {
    if (rhs == root->data) {    
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
            return;
        }
        this->erase_root(root); 
        int bf = balanc_factor(root);
        if (bf < -1 || bf > 1) {
            get_balance(root);
        } 
        return;
    }
    if (this->find(rhs) == nullptr) {
        throw std::invalid_argument("Invalid argument!");
    }
    this->erase_help(root, rhs);
    int bf = balanc_factor(root);
    if (bf < -1 || bf > 1) {
        get_balance(root);
    } 
}

template <typename T>
void AVL<T>::erase(T&& rhs) {
    if (rhs == root->data) {    
        if ((root->left == nullptr) && (root->right == nullptr)) {
            delete root;
            root = nullptr;
            return;
        }
        this->erase_root(root); 
        int bf = balanc_factor(root);
        if (bf < -1 || bf > 1) {
            get_balance(root);
        } 
        return;
    }
    if (this->find(rhs) == nullptr) {
        throw std::invalid_argument("Invalid argument!!!!!");
    }
    this->erase_help(root, rhs);
    int bf = balanc_factor(root);
    if (bf < -1 || bf > 1) {
        get_balance(root);
    } 
}

template <typename T>
void AVL<T>::erase_root(Node*& rhs) {
    if ((rhs->left != nullptr) && (rhs->right == nullptr)) {
        Node* del = rhs;
        rhs->left->right = rhs->right;
        rhs = rhs->left;
        delete del;
        del = nullptr;
    } else if ((rhs->left == nullptr) && (rhs->right != nullptr)) {
        Node* del = rhs;
        rhs->right->left = rhs->left;
        rhs = rhs->right;
        delete del;
        del = nullptr;
    } else {
        Node* del = rhs;
        rhs->right->left = rhs->left;
        rhs = rhs->right;
        delete del;
        del = nullptr;
    }
}

template <typename T>
void AVL<T>::erase_help(Node*& t, const T& rhs) {
    if (t == nullptr) {
        return;
    }
    if (rhs < t->data) {
        erase_help(t->left, rhs);
    } else if (rhs > t->data) {
        erase_help(t->right, rhs);
    } else if (t->left != nullptr && t->right != nullptr) {
        t->data = find_min()->data;
        erase_help(t->right, t->data);
    } else {
        Node* del = t;
        t = (t->left == nullptr) ? t->right : t->left;
        delete del;
        del = nullptr;
    }

}

template <typename T>
void AVL<T>::merge(const AVL<T>& rhs) {
    if (rhs.root == nullptr) {
        return;
    }
    this->merge_help(root, rhs.root);   
}

template <typename T>
void AVL<T>::merge_help(Node*& t, Node* rhs) {
    if (rhs == nullptr) {
        return;
    }
    if (t == nullptr) {
        t = new Node(rhs->data);
    }
    merge_help(t, rhs->left);
    insert_help(t, rhs->data);
    merge_help(t, rhs->right);
    insert_help(t, rhs->data);
}