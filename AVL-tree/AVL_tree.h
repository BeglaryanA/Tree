#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <initializer_list>
#include <cstddef>
#include <iostream>

template <typename T>
class AVL {
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node();
        Node(const T&, Node* l = nullptr, Node* r = nullptr);
    }*root;
    size_t number_node;

public:
    AVL();
    AVL(const T&);
    AVL(T&&);
    AVL(const AVL&);
    AVL(AVL&&);
    AVL(std::initializer_list<T>);
    ~AVL();
public:
    AVL& operator=(const AVL&);
    AVL& operator=(AVL&&);

public:
    void insert(const T&);
    void insert(T&&);
    void erase(const T&);
    void erase(T&&);
    Node* find(const T&);
    Node* find(T&&);
    int number_of_nodes() const;
    void clear();
    void preorder();
    void postorder();
    void inorder();
    void levelorder();
    T get_root_data();
    void merge(const AVL&);
    bool contains(const T&);
    bool contains(T&&);
    Node* find_min() const;
    Node* find_max() const;
private:
    Node* find_min_help(Node*) const;
    Node* find_max_help(Node*) const;
private: // copy, balanc
    Node* copy_help(const Node*);
    void get_balance(Node*&);
    int balanc_factor(Node*);
private: // rotates
    Node* left_left_rotation(Node*&);
    Node* right_right_rotation(Node*&);
    Node* left_right_rotation(Node*&);
    Node* right_left_rotation(Node*&);
private: // insert, erase
    void erase_help(Node*&, const T&);
    void erase_root(Node*&);
    int node_high(Node*);
    void insert_help(Node*&, const T&);
private:  // traversal
    void postorder_help(Node*);
    void preorder_help(Node*);
    void inorder_help(Node*);
    void levelorder_help(Node*, int);
private:  //find, clear helpers
    Node* find_help(Node*, const  T&);
    void clear_help(Node*);
private:
    void merge_help(Node*&, Node*);
};

#endif  //AVL_TREE_H