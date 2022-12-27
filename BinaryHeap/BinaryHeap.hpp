#include "BinaryHeap.h"

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(int size) 
: array(size)
, currentSize{0}
{}

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const std::vector<Comparable>& rhs) 
: array(rhs.size() + 10)
, currentSize{rhs.size()}
{
    for (int i = 0; i < rhs.size(); ++i) {
        array[i + 1] = rhs[i];
    }
    this->buildHeap();
}

template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap() {
    for (int i = 1; i < this->currentSize; ++i) {
        precolDown(i);
    }
}

template <typename Comparable>
bool BinaryHeap<Comparable>::isEmpty() {
    return currentSize == 0;
}

template <typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable& rhs) {
    if (currentSize == array.size() - 1) {
        this->array.resize(array.size() * 2);
    }
    int hole = ++currentSize;
    Comparable copy = rhs;
    array[0] = std::move(copy); 
    for (; rhs <= array[hole / 2]; hole /= 2) {
        array[hole] = std::move(array[hole / 2]);
    }
    array[hole] = std::move(array[0]);
}

template <typename Comparable>
void BinaryHeap<Comparable>::insert(Comparable&& rhs) {
    if (currentSize == array.size() - 1) {
        this->array.resize(array.size() * 2);
    }
    int hole = ++currentSize;
    Comparable copy = rhs;
    array[0] = std::move(copy); 
    for (; rhs < array[hole / 2]; hole /= 2) {
        array[hole] = std::move(array[hole / 2]);
    }
    array[hole] = std::move(array[0]);
}

template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin() {
    if (isEmpty()) {
        throw;
    }
    array[1] = std::move(array[currentSize--]);
    precolDown(1);
}

template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin(Comparable& rhs) {
    if (isEmpty()) {
        throw;
    }
    rhs = array[1];
    array[1] = std::move(array[currentSize--]);
    precolDown(1);
}

template <typename Comparable>
void BinaryHeap<Comparable>::precolDown(int hole) {
    int child;
    Comparable tmp = std::move(array[hole]);
    for (; 2 * hole <= currentSize; hole = child) {
        child = hole * 2;
        if (child <= currentSize && array[child + 1] < array[child]) {
            ++child;
        }
        if (array[child] < tmp) {
            array[hole] = std::move(array[child]);
        } else {
            break;
        }
    }
    array[hole] = std::move(tmp);
}

template <typename Comparable>
void BinaryHeap<Comparable>::makeEmpty() {
    if (!currentSize) {
        return;
    }
    this->array.clear();
}