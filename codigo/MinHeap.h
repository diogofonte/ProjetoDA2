#ifndef FEUP_DA_AGENCIADEVIAGENS_MINHEAP_H
#define FEUP_DA_AGENCIADEVIAGENS_MINHEAP_H

#include <vector>
#include <unordered_map>

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

using namespace std;

// Binary min-heap to represent integer keys of type K with values (priorities) of type V
template <class K, class V>
class MinHeap {
    /**
     * Elemento da Heap
     * constituído por um par(chave, valor)
     */
    struct Node {
        K key;
        V value;
    };

    /**
     * Número de elementos na Heap
     */
    int size;
    /**
     * Número máximo de elementos na Heap (capacidade)
     */
    int maxSize;
    /**
     * Lista de elementos da Heap
     */
    vector<Node> elements;
    /**
     * Mapa com uma chave e a respetiva posição na lista de elementos
     */
    unordered_map<K, int> pos;
    /**
     * Chave para erro
     */
    const K KEY_NOT_FOUND;

    void upHeap(int i);
    void downHeap(int i);
    void swap(int i1, int i2);

public:
    MinHeap(int n, const K& notFound); // Create a min-heap for a max of n pairs (K,V) with notFound returned when empty
    int getSize();              // Return number of elements in the heap
    bool hasKey(const K& key);  // Heap has key?
    void insert(const K& key, const V& value);      // Insert (key, value) on the heap
    void decreaseKey(const K& key, const V& value); // Decrease value of key
    K removeMin(); // remove and return key with smaller value
};

// ----------------------------------------------

// Make a value go "up the tree" until it reaches its position
template <class K, class V>
void MinHeap<K,V>::upHeap(int i) {
    while (i>1 && elements[i].value < elements[PARENT(i)].value) { // while pos smaller than parent, keep swapping to upper position
        swap(i, PARENT(i));
        i = PARENT(i);
    }
}

// Make a value go "down the tree" until it reaches its position
template <class K, class V>
void MinHeap<K,V>::downHeap(int i) {
    while (LEFT(i) <= size) { // while within heap limits
        int j = LEFT(i);
        if (RIGHT(i)<=size && elements[RIGHT(i)].value < elements[j].value) j = RIGHT(i); // choose smaller child
        if (elements[i].value < elements[j].value) break;   // node already smaller than children, stop
        swap(i, j);                    // otherwise, swap with smaller child
        i = j;
    }
}

// Swap two positions of the heap (update their positions)
template <class K, class V>
void MinHeap<K,V>::swap(int i1, int i2) {
    Node tmp = elements[i1]; elements[i1] = elements[i2]; elements[i2] = tmp;
    pos[elements[i1].key] = i1;
    pos[elements[i2].key] = i2;
}

// ----------------------------------------------

// Create a min-heap for a max of n pairs (K,V) with notFound returned when empty
template <class K, class V>
MinHeap<K,V>::MinHeap(int n, const K& notFound) : KEY_NOT_FOUND(notFound), size(0), maxSize(n), elements(n + 1) {
}

// Return number of elements in the heap
template <class K, class V>
int MinHeap<K,V>::getSize() {
    return size;
}

// Heap has key?
template <class K, class V>
bool MinHeap<K, V>::hasKey(const K& key) {
    return pos.find(key) != pos.end();
}

// Insert (key, value) on the heap
template <class K, class V>
void MinHeap<K,V>::insert(const K& key, const V& value) {
    if (size == maxSize) return; // heap is full, do nothing
    if (hasKey(key)) return;     // key already exists, do nothing
    elements[++size] = {key, value};
    pos[key] = size;
    upHeap(size);
}

// Decrease value of key to the indicated value
template <class K, class V>
void MinHeap<K,V>::decreaseKey(const K& key, const V& value) {
    if (!hasKey(key)) return; // key does not exist, do nothing
    int i = pos[key];
    if (value > elements[i].value) return; // value would increase, do nothing
    elements[i].value = value;
    upHeap(i);
}

// remove and return key with smaller value
template <class K, class V>
K MinHeap<K,V>::removeMin() {
    if (size == 0) return KEY_NOT_FOUND;
    K min = elements[1].key;
    pos.erase(min);
    elements[1] = elements[size--];
    downHeap(1);
    return min;
}

#endif //FEUP_DA_AGENCIADEVIAGENS_MINHEAP_H
