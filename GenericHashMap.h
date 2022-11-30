#ifndef GENERIC_HASH_MAP_H
#define GENERIC_HASH_MAP_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
class GenericHashMap
{
public:
    //Constructors & Destructor
    GenericHashMap();
    GenericHashMap(int size);
    ~GenericHashMap();

    void insert(string key, T value);
    void rehash();
    void remove(string key);
    int hash(string key);

    T get(string key);
    T& operator[](string key);
    
    void print();

    //Getters
    int getSize();
    int getCapacity();


private:
    struct Node
    {
        string key;
        T value;
        Node* next;
    };

    vector<Node*> table;
    int size;
    int capacity;
};

template<typename T>
GenericHashMap<T>::GenericHashMap()
{
    //default size
    int size = 100;
    //create the vector
    vector<T> hashTable(size);
}

//define the constructor
template<typename T>
GenericHashMap<T>::GenericHashMap(int size)
{
    //create the vector
    vector<T> hashTable(size);
}

//define the destructor
template<typename T>
GenericHashMap<T>::~GenericHashMap()
{
    //delete the vector
    delete hashTable;
}


#endif //GENERIC_HASH_MAP_H