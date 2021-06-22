#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include "sortedList.h"
#include <iostream>
#include <stdexcept>
#include <algorithm> 
using std::endl;


/**
 * Main class of SortedList.It contains a Node struct that holds the elemnts. It also contains
 * a const iterator for this list.This const iterator has his own class. 
 * 
 * Thw following functions are available : 
 * 
 *  SortedList          -Construct a new Sorted List object.
 * 
 *  ~SortedList         -Destroy the sorted List object.
 *
 *  SortedList          -Copy construct Sorted List object. 
 *
 *  const_iterator      -Construct a new const_iterator object
 *
 *  getNodePtr          -Returns a pointer to the node that the const iterator has it's index. 
 *
 *  operator++          -prefix: promotes the iterator first.
 *  operator==          -checks if the two const iterators have the same indexes, which means if the const 
 *                       iterators are on the same node. 
 * 
 *  operator*           -return the item in nide struct.  
 *
 *  begin               -return a const iterator to the first node in the sorted list. 
 *
 *  end                 -return a const iterator to what is after the last node in the sorted list.
 *
 *  operator=           -list2=list 1 : puts list1 in list 2 . 
 *
 *  lenght              -Return a field called len in our sorted list class, that's being updated with every
 *                       insert and remove.
 *
 *  insert              -Creates a new node and adds it to the sorted list, puts the elemnt
 *                       in node's item and updates sorted list's lenght. 
 *
 *  remove              -Removes a specific node from our sorted list and updates the nes sorted list's lenght.
 *
 *  filter              -Returns a new sorted list that has the only elemnts that go with the condition giving by predicate. 
 *
 *  apply               -We apply the func we recieve on every element in our node, 
 *                       and returns a new sorted list with fun being applied to all elements. 
 *
 *  concatinate_list    -concatinate to sorted list in a row.  
 *  clear               -Clears the sorted list by removing every node.   
 * 
 */

template <class T>
class SortedList {
private:
    struct Node {
        T item;
        struct Node* next;
        /**
         * Node : Construct a new Node object
         * 
         * @param item - the elemnt in the node.
         * @param next - pointer to the next node in our sorted list.
         */
        Node(T item,Node* next ):  item(item), next(next) {}; 
        
    };
    Node* first_node;
    int len;
    SortedList& concatinate_list(const SortedList& list2);
    void clear();

public:
    SortedList();
    ~SortedList();
    SortedList(const SortedList&);
    SortedList& operator=(const SortedList&);
    
    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

    int length() const;
    void insert(const T& element);
    void remove(const_iterator it);
    template <class Predicate>
    SortedList filter(Predicate function);
    template <class function>
    SortedList apply(function func);
};


template <class T>
class SortedList<T>::const_iterator {
private:
    const SortedList<T>* sorted_list;
    int index;
    const_iterator(const SortedList<T>* sorted_list, int index);
    Node* getNodePtr();
    friend class SortedList;

public:
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;
    ~const_iterator() = default;
    const_iterator& operator++();
    bool operator==(const const_iterator&) const;
    const T& operator*();
};

///////////////////////////////////////////////////////////////////////
/**
 * SortedList : Construct a new Sorted List object.
 */ 
template <class T>
SortedList<T>::SortedList() :first_node(NULL),len(0){}

/**
 * ~SortedList: Destroy the sorted List object.
 */
template <class T>
SortedList<T>::~SortedList() {
    this->clear();
}

/**
 * SortedList : Copy construct Sorted List object. 
 * 
 * @param sorted_list_original - 
 *  the sorted list we want to copy.
 */
template <class T>
SortedList<T>::SortedList(const SortedList& sorted_list_original) :
    first_node(NULL), len(0) {
    this->concatinate_list(sorted_list_original);
}

//////////////////////////// const_iterator ////////////////////////////////////////////////////////

/**
 * const_iterator : Construct a new const_iterator object
 * 
 * @param sorted_list - the list wa want to construct a const iterator to.
 * @param index - the index of the const iterator. 
 */
template <class T>
SortedList<T>::const_iterator::const_iterator(const SortedList* sorted_list, int index) :
    sorted_list(sorted_list), index(index) {}


/**
 * getNodePtr : Returns a pointer to the node that the const iterator has it's index. 
 * 
 * @return pointer to the node that the const iterator has it's index. 
 */
template <class T>
typename SortedList<T>::Node* SortedList<T>::const_iterator::getNodePtr() {
    Node* current_node = this->sorted_list->first_node;
    for (int j=0; j<this->index; j++) {
        current_node = current_node->next; 
    }
    return current_node;
}

/**
 * operator++ : prefix -  promotes the iterator first.
 * 
 * @return The new const_iterator, which has been promoted.  
 */
template <class T>
typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++() {
    if (this->index > this->sorted_list->len) { 
        throw std::out_of_range("bla");
    }
    this->index++; 
    return *this;
}

/**
 * operator== : checks if the two const iterators have the same indexes, which means if the const 
 *              iterators are on the same node. 
 * 
 * @param it - 
 *  One of the two const iterators that we are checking.       
 * @return
 *  true if they have the same indexes, false otherwise. 
 */
template <class T>
bool SortedList<T>::const_iterator::operator==(const SortedList::const_iterator& it) const {
    return this->index == it.index;
}

/**
 * operator* : return the item in nide struct.  
 * 
 * @return const T& - which is the item in the node struct. 
 */
template <class T>
const T& SortedList<T>::const_iterator::operator*() {
    return this->getNodePtr()->item;
}

/**
 * begin : return a const iterator to the first node in the sorted list. 
 * 
 * @return const_iterator to the first node in the list. 
 */
template <class T>
typename SortedList<T>::const_iterator SortedList<T>::begin() const {
    return const_iterator(this, 0);
}

/**
 * end : return a const iterator to what is after the last node in the sorted list.
 * 
 * @return const_iterator 
 */
template <class T>
typename SortedList<T>::const_iterator SortedList<T>::end() const {
    return const_iterator(this, (this->len));
}

/////////////////////////////////////// INSERT, REMOVE, LENGHT, = /////////////////////////////////////////

/**
 * operator= : list2=list 1 : puts list1 in list 2 . 
 * 
 * @param sorted_list_original  - 
 *  the list want to put in the other one.
 * @return 
 *  list2 after being replaced with the sorted_list_original.
 */
template <class T>
SortedList<T>& SortedList<T>::operator=(const SortedList<T>& sorted_list_original) {
    if (this == &sorted_list_original){
        return *this;
    }
    this->clear(); 
    this->concatinate_list(sorted_list_original);
    this->len=sorted_list_original.len;
    return *this;
}

/**
 * lenght : Return a field called len in our sorted list class, that's being updated with every
 *          insert and remove.
 * 
 * @return - sorted list's lenght. 
 */
template <class T>
int SortedList<T>::length() const {
    return this->len;
}

/**
 * insert : Creates a new node and adds it to the sorted list, puts the elemnt
 *          in node's item and updates sorted list's lenght. 
 * @param elemnt -
 *  The elemnt we should put in the node that we created to put it in the sorted list.      
 */
template <class T>
void SortedList<T>::insert(const T& element) {
    if (this->len == 0) {
        Node* new_node = new Node(element, NULL);
        this->first_node = new_node;
        this->len++;
        return;
    }

    const_iterator i = this->begin();
    for(int counter=0; counter<len; counter++) {

        if (element < *i) {
            this->len++;
            if (i==this->begin()) {
                Node* new_node = new Node(element, i.getNodePtr());
                this->first_node = new_node;
                return;
            }
            Node* new_node = new Node(element, i.getNodePtr());
            const_iterator(this, i.index-1).getNodePtr()->next = new_node;
            return;
        }
        if (!(counter==len-1)) { 
            ++i;
        }
    }
    Node* new_node = new Node(element, NULL);
    i.getNodePtr()->next = new_node;
    this->len++;
}

/**
 * remove : Removes a specific node from our sorted list and updates the nes sorted list's lenght.
 * 
 * @param it -
 *  Iterator that holds the index of the node we want t oremove from sorted list.      
 */
template <class T>
void SortedList<T>::remove(const_iterator it) {
    this->len--;
    Node* node 
     it.getNodePtr();
    if (node == this->first_node) {
        this->first_node = node->next; 
    }   
      else { 
        const_iterator(this, it.index-1).getNodePtr()->next = node->next;
      }
      delete node;
}
////////////////////// filter and apply ///////////////////

/**
 * filter : Returns a new sorted list that has the only elemnts that go with the condition giving by predicate. 
 * 
 * @param function - The function that checks the condition. 
 * @return New sorted list with members that go along with the condition required. 
 */
template <class T>
template <class Predicate>
SortedList<T> SortedList<T>::filter(Predicate function){
    SortedList sorted_list_filter= SortedList();
    for(const_iterator i=this->begin(); !(i==this->end()); ++i){
        if(function(*i)){
            sorted_list_filter.insert(*i);
        }
    }
    return sorted_list_filter;
}


/**
 * apply  :  We apply the func we recieve on every element in our node, 
 *           and returns a new sorted list with fun being applied to all elements. 
 * 
 * @param func - 
 *  The function we recieve and should apply to all elemnts.  
 * @return 
 *   A new sorted list with func applied on all elements. 
 */
template <class T>
template <class function>
SortedList<T> SortedList<T>::apply(function func) {
    SortedList sorted_list_apply= SortedList();
    for(const_iterator i = this->begin(); (!(i==this->end())); ++i){
        T returned_value=func(*i);
        sorted_list_apply.insert(returned_value);
    }
    return sorted_list_apply;
}

/////////////////////////////////////// INTERNAL FUNCTIONS /////////////////////////////////////////

/**
 * concatinate_list : concatinate to sorted list in a row.  
 * 
 * @param list2 - 
 *  List 2 will be concatinated to *this*. 
 * @return 
 *  returnes a new list of the two concatinated lists. 
 */
template <class T>
SortedList<T>& SortedList<T>::concatinate_list(const SortedList<T>& list2) {
    const_iterator i = list2.begin();
    while(!(i==list2.end())){ 
        this->insert(*i);
        ++i;
    }
    return *this;
}


/**
 * clear : Clears the sorted list by removing every node.   
 */
template <class T>
void SortedList<T>::clear() {
    while (this->len>0) {
        this->remove(const_iterator(this, ((this->len)-1)));
    }
}


#endif // SORTED_LIST_H
