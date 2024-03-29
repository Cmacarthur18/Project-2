#ifndef Set_h
#define Set_h
#include <string>
#include <iostream>
#include <stdio.h>
typedef std::string ItemType;  // switch to string
class Set
{
public:
    Set();
    ~Set();
    Set(const Set& other);
    Set &operator=(const Set &other);
    void dump() const;
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
private:
    int  m_items;
    struct node{
        node* next;
        node* previous;
        ItemType value;
    };
    node* head = nullptr;
    //node* tail;
    
};
void subtract(const Set& s1, const Set& s2, Set& result);
void unite(const Set& s1, const Set& s2, Set& result);
#endif /* Set_hpp */
