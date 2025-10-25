#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H
#include "test.h"
#include <string>

const int NUM_DATA_SLOTS = 5;

template<typename Key, typename Value> class BPlusTree{
    private:
    class Node{
        public:
        int numItems;
        bool isLeaf();
    };
    class LeafNode : Node{
        public:
        Value values[NUM_DATA_SLOTS];
        Key keys[NUM_DATA_SLOTS];
        LeafNode* next;
        bool isLeaf(){return true;}
    };
    class IntermediateNode: Node{
        public:
        Key keys[NUM_DATA_SLOTS];
        Node* pointers[NUM_DATA_SLOTS + 1];
        bool isLeaf(){return false;}
    };

    Node* _root;
    int _size;

    public:
    BPlusTree(){
        _root = nullptr;
        _size = 0;
    }

    int size(){return _size;}


    void insert(Key key, Value value){

    }

    private:
    Node* findNodeToInsertInto(Key key){
        if(_root->isLeaf()){
            return _root;
        }

        Node* currentNode = _root;
        while (true){
            int len = currentNode->numItems;
            for(int i = 0; i < len; i++){
                if(currentNode->isLeaf()){
                    break;
                }
                IntermediateNode* currentNode = currentNode;

                if(i == 0 && key < currentNode->keys[i]){
                   currentNode = currentNode->pointers[0];
                   continue;
                }
                if(i == len - 1 && key > currentNode->keys[i]){
                    currentNode = currentNode->pointers[len];
                    continue;
                }
                if(i < len - 1 && key > currentNode->keys[i] && key < currentNode->keys[i + 1]){
                    currentNode = currentNode->pointers[i + 1];
                    continue;
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

})


#endif
