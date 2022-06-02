#ifndef PROJETODA2_MAXHEAP_H
#define PROJETODA2_MAXHEAP_H

#include <vector>
#include <unordered_map>

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

using namespace std;

// Binary min-heap to represent integer keys of type K with values (priorities) of type V
template <class K, class V>
class MaxHeap {
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
    vector<Node> element;
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
    MaxHeap(int n, const K& notFound); // Create a min-heap for a max of n pairs (K,V) with notFound returned when empty
    int getSize();              // Return number of elements in the heap
    bool hasKey(const K& key) const;  // Heap has key?
    void insert(const K& key, const V& value);      // Insert (key, value) on the heap
    void increaseKey(const K& key, const V& value); // Increase value of key
    K removeMax(); // remove and return key with the highest value
    void print();
};

// ----------------------------------------------

// Make a value go "up the tree" until it reaches its position
template <class K, class V>
void MaxHeap<K,V>::upHeap(int i) {
    while (i>1 && element[i].value < element[PARENT(i)].value) { // while pos smaller than parent, keep swapping to upper position
        swap(i, PARENT(i));
        i = PARENT(i);
    }
}

// Make a value go "down the tree" until it reaches its position
template <class K, class V>
void MaxHeap<K,V>::downHeap(int i) {
    while (LEFT(i) <= size) { // while within heap limits
        int j = LEFT(i);
        if (RIGHT(i)<=size && element[RIGHT(i)].value < element[j].value) j = RIGHT(i); // choose smaller child
        if (element[i].value < element[j].value) break;   // node already smaller than children, stop
        swap(i, j);                    // otherwise, swap with smaller child
        i = j;
    }
}

// Swap two positions of the heap (update their positions)
template <class K, class V>
void MaxHeap<K,V>::swap(int i1, int i2) {
    Node tmp = element[i1]; element[i1] = element[i2]; element[i2] = tmp;
    pos[element[i1].key] = i1;
    pos[element[i2].key] = i2;
}

// ----------------------------------------------

// Create a min-heap for a max of n pairs (K,V) with notFound returned when empty
template <class K, class V>
MaxHeap<K,V>::MaxHeap(int n, const K& notFound) : KEY_NOT_FOUND(notFound), size(0), maxSize(n), element(n + 1) {
}

// Return number of elements in the heap
template <class K, class V>
int MaxHeap<K,V>::getSize() {
    return size;
}

// Heap has key?
template <class K, class V>
bool MaxHeap<K, V>::hasKey(const K& key) const {
    return pos.find(key) != pos.end();
}

// Insert (key, value) on the heap
template <class K, class V>
void MaxHeap<K,V>::insert(const K& key, const V& value) {
    if (size == maxSize) return; // heap is full, do nothing
    if (hasKey(key)) return;     // key already exists, do nothing
    element[++size] = {key, value};
    pos[key] = size;
    upHeap(size);
}

// Increase value of key to the indicated value
template <class K, class V>
void MaxHeap<K,V>::increaseKey(const K& key, const V& value) {
    if (!hasKey(key)) return; // key does not exist, do nothing
    int i = pos[key];
    if (value < element[i].value) return; // value would decrease, do nothing
    element[i].value = value;
    upHeap(i);
}

// remove and return key with max value
template <class K, class V>
K MaxHeap<K,V>::removeMax() {
    if (size == 0) return KEY_NOT_FOUND;
    K max = element[1].key;
    pos.erase(max);
    element[1] = element[size--];
    downHeap(1);
    return max;
}
template <class K, class V>
void MaxHeap<K,V>::print(){
    for(auto it:pos){
        printf("%d %d\n", it.first, it.second);
    }
}

#endif //PROJETODA2_MAXHEAP_H
