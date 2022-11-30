#ifndef GENERIC_HASH_MAP_H
#define GENERIC_HASH_MAP_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

const double LOAD_FACTOR = 0.75;

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
    int getSize()
    {
        return size;
    }
    int getItems()
    {
        return items;
    }


private:
    struct Node
    {
        string key;
        T value;
        Node* next;
    };

    vector<Node*> table;
    int size;
    int items;

    bool isPrime(int num);
};

//-------------Constructors & Destructor----------------//
template<typename T>
GenericHashMap<T>::GenericHashMap()
{
    int size = 11;
    int items = 0;
    
    table.resize(size);
    for (int i = 0; i < size; i++)
    {
        table[i] = nullptr;
    }
}

template<typename T>
GenericHashMap<T>::GenericHashMap(int size)
{
    int items = 0;
    table.resize(size);
    for (int i = 0; i < size; i++)
    {
        table[i] = nullptr;
    }
    this->size = size;
}

template<typename T>
GenericHashMap<T>::~GenericHashMap()
{
    delete hashTable;
}

//-------------Insert & Rehash--------------------------//
template<typename T>
void GenericHashMap<T>::insert(string key, T value)
{
    int index = hash(key);
    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    if (table[index] == NULL)
    {
        table[index] = newNode;
    }
    else
    {
        Node* temp = table[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    items++;
    if ((double)items / size >= LOAD_FACTOR)
    {
        rehash();
    }
}

//define a rehash function that makes the new size double the old size to the next highest prime number
template<typename T>
void GenericHashMap<T>::rehash()
{
    int newSize = size * 2;
    while (!isPrime(newSize))
    {
        newSize++;
    }

    vector<Node*> newTable(newSize);

    for (int i = 0; i < size; i++)
    {
        Node* temp = table[i];
        while (temp != NULL)
        {
            int index = hash(temp->key);
            Node* newNode = new Node;
            newNode->key = temp->key;
            newNode->value = temp->value;
            newNode->next = NULL;

            if (newTable[index] == NULL)
            {
                newTable[index] = newNode;
            }
            else
            {
                Node* temp2 = newTable[index];
                while (temp2->next != NULL)
                {
                    temp2 = temp2->next;
                }
                temp2->next = newNode;
            }
            temp = temp->next;
        }
    }
    table = newTable;
    size = newSize;
}

//-------------Remove----------------------------------//
template<typename T>
void GenericHashMap<T>::remove(string key)
{
    int index = hash(key);
    Node* temp = table[index];
    Node* prev = NULL;

    if (temp != NULL && temp->key == key)
    {
        table[index] = temp->next;
        delete temp;
        size--;
        return;
    }

    while (temp != NULL && temp->key != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return;
    }

    prev->next = temp->next;
    delete temp;
    size--;
}

//-------------Hash-------------------------------------//
//declare a hash function that uses double hashing for probing
template<typename T>
int GenericHashMap<T>::hash(string key)
{
    int hash = 0;
    int index = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hash = hash + (int)key[i];
    }
    index = hash % size;
    return index;
}

//-------------Get--------------------------------------//
template<typename T>
T GenericHashMap<T>::get(string key)
{
    int index = hash(key);
    Node* temp = table[index];

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}

template<typename T>
T& GenericHashMap<T>::operator[](string key)
{
    int index = hash(key);
    Node* temp = table[index];

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}

//-------------Misc--------------------------------------//
template<typename T>
bool GenericHashMap<T>::isPrime(int num)
{
    if (num == 1)
    {
        return false;
    }
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

#endif //GENERIC_HASH_MAP_H