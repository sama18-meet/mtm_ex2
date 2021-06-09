#include "sortedList.h"
#include <iostream>
#include <stdexcept>


///////////////////// ITERATOR ///////////////////

template <class T>
SortedList<T>::SortedList() :
    first_node(NULL), size(0) {
}

template <class T>
SortedList<T>::Iterator::Iterator(const SortedList* sorted_list, int index) :
    sorted_list(sorted_list), index(index) {
}

template <class T>
typename SortedList<T>::Iterator& SortedList<T>::Iterator::operator++() {
    if (this->index >= this->sorted_list->size - 1) {
        throw std::out_of_range();
    }
    this->index++; 
    return *this;
}

template <class T>
bool SortedList<T>::Iterator::operator==(const SortedList::Iterator& it) const {
    assert(this->sorted_list == it.sorted_list);
    return this->index == it.index;
}

template <class T>
const T& SortedList<T>::Iterator::operator*() {
    return this->getNode()->item;
}

template <class T>
Node<T> SortedList<T>::Iterator::getNode() {
    Node<T>* current_node = this->sorted_list->first_node;
    for (int j=1; j<=this->idx; j++) {
        current_node = current_node->next; 
    }
    return current_node;
}


template <class T>
void SortedList<T>::remove(Iterator it) {
    Node<T> node =  it.getNode();
    Node<T> previous_node = Iterator(this, it.index-1).getNode(); // potential mem leak
    previous_node.next = node.next;
    delete node;
}


template <class T>
int SortedList<T>::length() {
    return end().index;
}


///////////////////////////////////////////////////////////////////


template <class T>
typename SortedList<T>::Iterator SortedList<T>::begin() const {
    return Iterator(this, 0);
}


template <class T>
typename SortedList<T>::Iterator SortedList<T>::end() const {
    return Iterator(this, size-1);
}


template <class T>
void SortedList<T>::insert(const T& element) {
    Node<T>* new_node = new Node<T>;
    new_node->item = element;
    Node<T>* previous_node = NULL;
    if (size == 0) {
        new_node->next = NULL;
        first_node = new_node;
    }
    Iterator i = this->begin();
    do {
        if (element < *i) {
            if (i==this->begin()) {
                this->first_node = new_node;
                new_node->next = i.getNode();
                return;
            }
            new_node->next = i.getNode();
            previous_node->next = new_node;
            return;
        }
        previous_node = i.getNode();
        ++i;
    } while (!(i==this->end()));
    new_node->next = NULL;
    i.getNode()->next = new_node;
}
