#ifndef BST_H
#define BST_H
#include <initializer_list>

template <typename T>
class BST {
    struct Node
    {
        Node* left;
        T data;
        Node* right;
        Node() : data{0}, left{nullptr}, right{nullptr} {}
        Node(T val) : data{val}, left{nullptr}, right{nullptr} {} 
    }*root;
public:
    BST() : root{nullptr} {}//
    BST(T);//
    BST(const BST&);//
    BST(BST&&);
    ~BST();//

public:
    void insert(T);//
    void clear();//
    void preorder();
    void postorder();
    void inorder();
    void levelorder();//
    T get_root_data();//
    std::size_t get_high();//
    void merge(const BST&);
    bool contains(T);//
    Node* find(T); //
private:
    void copy_help(Node*&,const Node*);
    void insert_help(Node*&, T); //
    void levelorder_help(Node*);//
    Node* find_help(Node*, T);//
    void clear_help(Node*&);//
    size_t high_help(Node*);//
    void printPreOreder(Node*);
    void printpostorder(Node* head);
};

#endif // BST_H