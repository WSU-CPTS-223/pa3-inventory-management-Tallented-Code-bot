#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H
#include "test.h"
#include <string>

const int NUM_DATA_SLOTS = 5;


template<typename Key, typename Value> class BPlusTree{
    private:

    class Node{
        public:
        bool isLeaf;
        Node* next; // for leaf nodes only
        Key keys[NUM_DATA_SLOTS];
        Value values[NUM_DATA_SLOTS];
        Node* pointers[NUM_DATA_SLOTS + 1];
        int numItems;
        Node* parent;

        Node(){
            isLeaf = true;
            next = nullptr;
            parent = nullptr;
            numItems = 0;
        }

        ~Node(){
            for (int i = 0; i < numItems; i++){
                delete pointers[i];
            }
        }

        // Insert an item in a sorted array in the correct position.
        // Assumes the array is of size NUM_DATA_SLOTS.
        //
        // The function returns the index inserted into, or -1 if the insert
        // failed.
        template <typename T>
        int insertInOrder(T arr[], T item, int len){
            // If length is too big, insert fails.
            if(len >= NUM_DATA_SLOTS){return -1;}

            int indexToInsertInto = 0;
            for(int i = 0; i < len; i++){
                if(item > arr[i]){
                    indexToInsertInto += 1;
                }
            }

            insert(arr, item, indexToInsertInto, len);

            return indexToInsertInto;
        }

        // Insert an item in an array in a given position.
        // Assumes the array is of size NUM_DATA_SLOTS.
        template <typename T>
        void insert(T arr[], T item, int index, int len){
            if(len >= NUM_DATA_SLOTS){return;}
            if(index > len){return;}

            for(int i = len - 1; i >= index; i--){
                arr[i + 1] = arr[i];
            }

            arr[index] = item;
        }

        bool isFull(){ return numItems >= NUM_DATA_SLOTS; }
    };


    // test functions
    friend std::string testInsertInOrder();
    friend std::string testInsert();


    Node* _root;
    int _size;

    public:
    BPlusTree(){
        _root = new Node;
        _size = 0;
    }

    ~BPlusTree(){
        delete _root;
    }

    int size(){return _size;}



    void insertKeyValue(Node* node, Key key, Value value){
        // You can't insert a key/value pair to a non-leaf node.
        if(!node->isLeaf){return;} // TODO should it throw an error?

        // the simple case: just add the key and value
        if(!node->isFull()){
            node->keys[node->numItems] = key;
            node->values[node->numItems] = value;
            node->numItems += 1;
            return;
        }

        // complicated case: we have to split the node
        Node* newNode = new Node;
        newNode->isLeaf = true;
        newNode->next = node->next;
        node->next = newNode;

        // move half of items to new node
        int offset = (node->numItems / 2);
        for(int i = node->numItems / 2; i < node->numItems; i++){
            newNode->keys[i - offset] = node->keys[i];
            newNode->values[i - offset] = node->values[i];
            newNode->numItems += 1;
            node->numItems -= 1;
        }

        // if this node is the root, we have to do some additional work here, to
        // create a new intermedate node to be the new root.
        if(node->parent == nullptr){
            Node* newRoot = new Node;
            newRoot->isLeaf = false;
            newRoot->keys[0] = newNode->keys[0];
            newRoot->pointers[0] = node;
            newRoot->pointers[1] = newNode;
            node->parent = newRoot;
            newNode->parent = newRoot;

            _root = newRoot;
        }else{
            newNode->parent = node->parent;

            insertKey(node->parent, newNode->keys[0], newNode);
        }
    }

    void insertKey(Node* node, Key key, Node* newChild){
        // Only for intermediate nodes
        if(node->isLeaf){return;}

        // simple case: just add the key and value
        if(!node->isFull()){
            int index = node->insertInOrder(node->keys, key, node->numItems);
            node->insertInOrder(node->pointers, newChild, node->numItems);
            node->numItems += 1;
        }
    }

    void insert(Key key, Value value){
        Node* nodeToInsertInto = findNodeToInsertInto(key);

        // if the node is full, we have to split it
        if(nodeToInsertInto->isFull()){

        }


    }

    private:
    Node* findNodeToInsertInto(Key key){
        if(_root->isLeaf){
            return _root;
        }

        Node* currentNode = _root;

        while(true){
            int numItems = currentNode->numItems;
            if(currentNode->isLeaf){
                return currentNode;
            }

            if(key < currentNode->keys[0]){
                currentNode = currentNode->pointers[0];
                continue;
            }
            if(key > currentNode->keys[numItems - 1]){
                currentNode = currentNode->pointers[numItems];
                continue;
            }

            for(int i = 0; i < numItems - 1; i++){
                if(key > currentNode->keys[i] && key < currentNode->keys[i + 1]){
                    currentNode = currentNode->pointers[i + 1];
                    break;
                }
            }
        }
    }

    friend std::string testFindNodeToInsertInto();



};

TEST(testFindNodeToInsertInto, {
    BPlusTree<int, int> tree;

    BPlusTree<int,int>::Node* node = tree.findNodeToInsertInto(10);
    assert(node == tree._root);
    assert(node->isLeaf);

})

/// Test inserting into an array
TEST(testInsertInOrder, {
    int arr[NUM_DATA_SLOTS] = {5, 10, 20};

    BPlusTree<int, int>::Node n;
    int index1 = n.insertInOrder(arr, 7, 3);

    // inserts into index 1
    assert_eq(index1, 1);

    assert_eq(arr[0], 5);
    assert_eq(arr[1], 7);
    assert_eq(arr[2], 10);
    assert_eq(arr[3], 20);


    int index2  = n.insertInOrder(arr, 25, 4);

    // inserts into index 4
    assert_eq(index2, 4);


    assert_eq(arr[0], 5);
    assert_eq(arr[1], 7);
    assert_eq(arr[2], 10);
    assert_eq(arr[3], 20);
    assert_eq(arr[4], 25);

    int index3 = n.insertInOrder(arr, 2, 5);

    // no insert, so returns -1
    assert_eq(index3, -1);

    // no change in array, as it is full
    assert_eq(arr[0], 5);
    assert_eq(arr[1], 7);
    assert_eq(arr[2], 10);
    assert_eq(arr[3], 20);
    assert_eq(arr[4], 25);
})

TEST(testInsert, {
    int arr[NUM_DATA_SLOTS] = {5, 10, 20};
    BPlusTree<int, int>::Node n;

    n.insert(arr, 21, 9, 3); // should fail

    n.insert(arr, 7, 1, 3);
    assert_eq(arr[1], 7);


    n.insert(arr, 99, 1, 4);
    assert_eq(arr[1], 99);


    n.insert(arr, 77, 1, 5);
    assert_eq(arr[1], 99); // list too big, insert fails.
})

TEST(testInsertKeyValue, {

})

#endif
