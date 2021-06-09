
template <class T>
struct Node {
    T item;
    struct Node* next;
};


template <class T>
class SortedList {
private:
    Node<T>* first_node;
    int size;

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
    int length();

};


template <class T>
class SortedList<T>::Iterator {
private:
    const SortedList<T>* sorted_list;
    int index;
    Iterator(const SortedList<T>* sorted_list, int index);
    Node<T> getNode();
    friend class SortedList;

public:
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    ~Iterator() = default;
    Iterator& operator++();
    bool operator==(const Iterator&) const;
    const T& operator*();

};
