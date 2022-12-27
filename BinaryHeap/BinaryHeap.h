#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <vector>
template <typename Comparable>
class BinaryHeap {
public:
    explicit BinaryHeap(int size = 100);
    explicit BinaryHeap(const std::vector<Comparable>&);

public:

    bool isEmpty();
    const Comparable& findMin() const;
    void insert(const Comparable&);
    void insert(Comparable&&);
    void deleteMin();
    void deleteMin(Comparable&);
    void makeEmpty();   

private:
    std::vector<Comparable> array;
    size_t currentSize;
private:
    void buildHeap();
    void precolDown(int);
};

#endif // BINARYHEAP_H