#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "test.h"
#include <stdexcept>
#include <string>
#include <vector>

// Set the starting capacity to 20,000, which is good in this case of needing to
// process 10,000 items. It would not be ideal in a more general case.
const int STARTING_CAPACITY = 20000;
const float LOAD_VALUE_THRESHOLD = 0.5;

template <typename Key, typename Value>
class HashTable{
    friend std::string testHashTableCapacity();

    private:
    struct Node{
        public:
        Key key;
        Value value;
    };

    std::vector<Node*> _values;
    int _capacity;
    int _size;

    public:
    HashTable(){
        _capacity = STARTING_CAPACITY;
        _size = 0;

        _values.reserve(_capacity);
        for(int i = 0; i < _capacity; i++){
            _values.push_back(nullptr);
        }
    }

    ~HashTable(){
        for(int i = 0; i < _capacity; i++){
            delete _values[i];
        }
    }

    int size(){return size;}
    int capacity(){return _capacity;}

    void insert(Key key, Value value){
        // This should never happen, but theoretically if the size is bigger
        // than the capacity we need to rehash.
        if(_size >= _capacity){
            rehash();
        }

        std::hash<Key> hashFunction;
        int index = hashFunction(key) % _capacity;

        if(_values[index] == nullptr){
            _values[index] = new Node{key, value};
            _size++;
        }else if(_values[index] != nullptr){
            // there is already an item in this slot, so we have to rehash.
            int i = 0;
            while(true){
                int newIndex = index + collisionFunction(i);
                if(_values[newIndex] == nullptr){
                    _values[index] = new Node{key, value};
                    _size++;
                    break;
                }

                if(i >= _capacity){
                    // something has probably gone wrong, it shouldn't take this long
                    throw std::runtime_error("Too much iteration while inserting into hash table");
                }

                i++;
            }
        }

        // If the load value gets too big, rehash
        if(float(_size)/_capacity > LOAD_VALUE_THRESHOLD){
            rehash();
        }
    }

    int collisionFunction(int n){
        return n;
    }

    // double
    void rehash(){
        std::vector<Node*> oldVec = _values;

        _capacity *= 2;

        _values.reserve(_capacity);
        for(int i = 0; i < _capacity; i++){
            try{
                _values.at(i) = nullptr;
            }catch(...){
                _values.push_back(nullptr);
            }
        }


        for(Node* item: _values){
            insert(item->key, item->value);
        }
    }



    Value get(Key key){
        Node* n = getPtr(key);

        Value filler;

        if(n != nullptr){
            return n->value;
        }else{
            return filler; // TODO this isn't the best
        }
    }


    Value& operator[](Key key){
        Node* n = getPtr(key);
        if(n != nullptr){
            return n->value;
        }
    }

    private:
    Node* getPtr(Key key){
        std::hash<Key> hashFunction;
        int baseIndex = hashFunction(key) % _capacity;

        int i = 0;
        while(true){
            if(i >= _capacity){
                // something has probably gone wrong
                return nullptr;
            }

            int index = baseIndex + collisionFunction(i);

            if(_values[index] != nullptr && _values[index]->key == key){
                return _values[index];
            }

            i++;
        }


        return nullptr;
    }
};


TEST(testBasicInsertAndRetreival, {
    HashTable<int, std::string> table;

    table.insert(5,"first entry");
    table.insert(8,"second entry");
    table.insert(1,"third entry");

    assert_eq(table.get(5), "first entry");
    assert_eq(table.get(8), "second entry");
    assert_eq(table.get(1), "third entry");
})


TEST(testHashTableCapacity, {
    HashTable<int, std::string> table;
    assert_eq(table._values.size(), STARTING_CAPACITY);
})

#endif
