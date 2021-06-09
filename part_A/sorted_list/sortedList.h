#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include "sortedList.h"
#include <iostream>
#include <stdexcept>



template <class T>
class SortedList {
private:
    struct Node {
        T item;
        struct Node* next;
    };
    Node* first_node;
    SortedList& concatinate_list(const SortedList& list2);
    void clear();


public:
    SortedList();
    ~SortedList();
    SortedList(const SortedList&);
    SortedList& operator=(const SortedList&); 

    class Iterator;
    Iterator begin() const;
    Iterator end() const;

    void insert(const T& element);
    void remove(Iterator it);
    int length() const;

};


template <class T>
class SortedList<T>::Iterator {
private:
    const SortedList<T>* sorted_list;
    int index;
    Iterator(const SortedList<T>* sorted_list, int index);
    Node* getNodePtr();
    friend class SortedList;

public:
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    ~Iterator() = default;
    Iterator& operator++();
    bool operator==(const Iterator&) const;
    const T& operator*();

};



///////////////////// ITERATOR ///////////////////

template <class T>
SortedList<T>::Iterator::Iterator(const SortedList* sorted_list, int index) :
    sorted_list(sorted_list), index(index) {
        //assert(index >= 0);
}

template <class T>
typename SortedList<T>::Node* SortedList<T>::Iterator::getNodePtr() {
    Node* current_node = this->sorted_list->first_node;
    for (int j=1; j<=this->index; j++) {
        current_node = current_node->next; 
    }
    return current_node;
}

template <class T>
typename SortedList<T>::Iterator& SortedList<T>::Iterator::operator++() {
    if (this->index >= this->sorted_list->length() - 1) {
        throw std::out_of_range("bla");
    }
    this->index++; 
    return *this;
}

template <class T>
bool SortedList<T>::Iterator::operator==(const SortedList::Iterator& it) const {
    return this->index == it.index;
}

template <class T>
const T& SortedList<T>::Iterator::operator*() {
    return this->getNodePtr()->item;
}



///////////////////////////////////////////////////////////////////

template <class T>
SortedList<T>& SortedList<T>::concatinate_list(const SortedList<T>& list2) {
    Iterator i = list2.begin();
    do {
        this->insert(*i);
        ++i;
    } while (!(i==list2.end()));
    return *this;
}

template <class T>
void SortedList<T>::clear() {
    while (this->length() > 0) {
        this->remove(this->end());
    }
}

template <class T>
SortedList<T>::SortedList() :
    first_node(NULL) {
}

template <class T>
SortedList<T>::~SortedList() {
    this->clear();
}

template <class T>
SortedList<T>::SortedList(const SortedList& sorted_list_original) :
    first_node(NULL) {
    this->concatinate_list(sorted_list_original);
}


template <class T>
SortedList<T>& SortedList<T>::operator=(const SortedList<T>& sorted_list_original) {
    if (this == &sorted_list_original) {
        return *this;
    }
    this->clear();
    this->concatinate_list(sorted_list_original);
    return *this;
}

template <class T>
typename SortedList<T>::Iterator SortedList<T>::begin() const {
    return Iterator(this, 0);
}

template <class T>
typename SortedList<T>::Iterator SortedList<T>::end() const {
    return Iterator(this, this->length()-1);
}

template <class T>
void SortedList<T>::remove(Iterator it) {
    Node* node =  it.getNodePtr();
    if (node == this->first_node) {
        this->first_node = node->next;
    }
    else {
        Iterator(this, it.index-1).getNodePtr()->next = node->next; // potential mem leak
    }
    delete node;
}


template <class T>
int SortedList<T>::length() const {
    int num_items = 0;
    Node* curr_node = this->first_node;
    while (curr_node != NULL) {
        num_items++;
        curr_node = curr_node->next;
    }
    return num_items;
}
using std::cout;
using std::endl;
template <class T>
void SortedList<T>::insert(const T& element) {
    Node* new_node = new Node;
    new_node->item = element;
    if (this->length() == 0) {
        new_node->next = NULL;
        first_node = new_node;
        return;
    }
    Iterator i = this->begin();
    do {
        if (element < *i) {
            if (i==this->begin()) {
                new_node->next = i.getNodePtr();
                this->first_node = new_node;
                return;
            }
            new_node->next = i.getNodePtr();
            Iterator(this, i.index-1).getNodePtr()->next = new_node;
            return;
        }
        if (!(i == this->end())) {
            ++i;
        }
    } while (!(i==this->end()));
    new_node->next = NULL;
    i.getNodePtr()->next = new_node;
}
#endif // SORTED_LIST_H
