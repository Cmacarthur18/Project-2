//
//  Set.cpp
//  Project 2
//
//  Created by Chet MacArthur on 1/23/19.
//  Copyright © 2019 Chet MacArthur. All rights reserved.
//

#include "Set.h"

Set::Set(){
    m_items= 0; // creates a empty list
    head = nullptr;
}

Set::~Set(){
    node *p = head;
    while(p != nullptr)
    {
        node* n = p->next;
        delete p;
        p = n;
    }
    m_items = 0;
}

Set::Set(const Set& other){
    Set temp1; // we want to load other into a temp class so we cn modify it
    node* trav = other.head;
    int i = 0;
    ItemType value;
    while(trav != nullptr )
    {
        other.get(i,value); // get the value
        temp1.insert(value); // insert it
        trav = trav->next;
        i++;
    }
    m_items = other.m_items;
    this->swap(temp1); // swap the current set with the one we inserte dvalues into
}

Set& Set::operator= (const Set &other){
    if(this == &other)
        return *this;
    Set temp1; // we want to load other into a temp class so we cn modify it
    node* trav = other.head;
    int i = 0;
    while(trav != nullptr )
    {
        ItemType inserter;
        other.get(i,inserter);
        temp1.insert(inserter);
        trav = trav->next;
        i++;
    }
    m_items = other.m_items;
    this->swap(temp1); // swap with temp
    return *this;
}

void Set:: dump() const{
    std::cerr << "====================" << std::endl;
    node *trav = head;
    for(int i = 0 ; i< m_items; i++){
        if( trav->previous == nullptr && trav->next == nullptr)
            std::cerr << "Previous0:"<< trav->previous << " | Value: " << trav->value << " | Next is: " <<trav->next<< std::endl;
        else if( trav->previous == nullptr && trav->next != nullptr)
            std::cerr << "Previous0:"<< trav->previous << " | Value: " << trav->value << " | Next is: " <<trav->next->value<< std::endl;
        else if( trav->next == nullptr)
            std::cerr << "Previous1:"<< trav->previous->value << " | Value: " << trav->value << " | Next is: " <<trav->next<< std::endl;
        else
            std::cerr << "Previous2:"<< trav->previous->value << " | Value: " << trav->value << " | Next is: " <<trav->next->value<< std::endl;
        trav = trav->next;
    }
}

bool Set:: empty() const{
    if(m_items == 0)
        return true;
    return false;
}

int Set::size() const{
    return m_items; // return the number of items in the linked list
}

bool Set::insert(const ItemType& value){ // insert in order
    
    
    node *trav = head; // makes a temp node to go through the linked list
    for(int i = 0 ; i< m_items; i++){
        if(trav->value == value){ // check to see if the value is already in the linked list
            return false;
        }
        trav = trav->next;
    }
    if(head == nullptr || value < head->value){ // if it is either the first node or that the value being passed in is less than the first node.
        node* newNode = new node;
        newNode-> previous = nullptr;
        newNode-> value = value;
        newNode->next = head;
        if(head != nullptr) // if there is more tha one items in the set we can assign the previous value to something other than null ptr
            head->previous = newNode;
        m_items++;
        head = newNode;
        return true;
    }else{
        node* p = head;
        for(int i = 0; i != size(); i++){
            if(value > p->value && i == (size()-1) ){ //if the element to add belongs at the very end b/v value is bigger than the last one
                node* newNode = new node;
                newNode->value = value;
                newNode->previous = p;
                newNode->next = nullptr; // when its at the end the next will be nullptr
                p->next = newNode;
                m_items++;
                return true;
            }
            if( value > p->value && value < p->next->value && ( 0<i < (size()-1)) ){ // if the element belongs in the middle, inbetween two nodes
                node* newNode = new node;
                newNode->value = value;
                newNode -> next = p->next;
                newNode->previous = p;
                p->next->previous= newNode;
                p->next = newNode;
                m_items++;
                return true;
            }
            p=p->next; // go to the next element in the linked list
        }
    }
    return false;
}

bool Set:: contains(const ItemType &value) const{
    node *trav = head;
    for(int i = 0 ; i< m_items; i++){
        if(trav->value == value) // if the value equals the one given return true
            return true;
        trav = trav->next; // move to the next node
    }
    return false;
}

bool Set:: erase(const ItemType &value){
    if(head == nullptr)
        return false;
    if(head->value == value){ // if the value passed in is the first value in the linked list remove it
        node* Killme = head;
        head = Killme->next;
        Killme->previous = nullptr;
        delete Killme;
        m_items--;
        return true;
    }
    node *p = head;
    while(p!= nullptr){ // if the value is anywhere else in the linked list
        if(p->next!= nullptr && p->next->value == value)
            break;
        p = p->next;
    }
    if(p!=nullptr){ // if the node to kill is not the first element we will need to adjust pointers for the node differently
        node* Killme = p->next;
        p->next= Killme->next;
        if(Killme->next != nullptr)
            Killme->next->previous = p;
        delete Killme;
        m_items--;
        return true;
    }
    
    return false;
}

void Set:: swap(Set &other){
    node *temp =other.head; // swap the head pointers
    other.head = head;
    head = temp;
    int tempSize = other.m_items; // swap number of items
    other.m_items = m_items;
    m_items = tempSize;
}

bool Set::get(int pos, ItemType &value) const{ // since it was inserted in order, get is straightforeward
    node* trav = head;
    if(pos < 0 || pos > size())
        return false;
    for(int i = 0; i != size() ; i++){
        if(i == pos){
            value = trav->value;
            return true;
        }
        trav = trav->next;
    }
    return false;
}

void unite(const Set& s1, const Set& s2, Set& result){
    Set temp;
    temp = s2; // make a set equal to s2
    for(int i = 0; i != s1.size(); i++){ // insert s1 into temp and only the items not already in temp will be inserted based purley on how insert works
        ItemType value;
        s1.get(i,value);
        temp.insert(value);
    }
    result = temp;
}

void subtract(const Set& s1, const Set& s2, Set& result){ //** why does the assignment not work here
    Set temp; // make a temporary set
    temp = s1; // set first temp set to s1
    Set temp1;  // make another temporary set class and set it equal to s1
    temp1 = temp;
    for(int i = 0; i < temp.size(); i++){ // go through temp
        ItemType value;
        temp.get(i, value); // get each vlue of temp
        for(int j = 0; j < s2.size(); j++){ // loop through s2
            ItemType value1;
            s2.get(j, value1);
            if(value == value1){ // if any values match from s1 and s2
                temp1.erase(value); // erase it from temp 1
            }
        }
    }
    result = temp1; //assign temp1 to result
}
