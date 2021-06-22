#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;
using std:: ostream;
using std::out_of_range;

namespace mtm
{
template<class T>
class SortedList
{
public:
class Node
     {
       public:
       T* data;
       Node* next;

       friend class SortedList<T>::const_iterator;
       friend class SortedList<T>;

       Node(T t)
       {
           this->data = new T(t);
           this->next = NULL;
       }

       ~Node()
       {
       delete this->data;
       this->next = NULL;
       }
    };

 int size;
 Node* first;

 class const_iterator
    {
        public:
        Node* iter;
        const_iterator(Node* node)
        {
            this->iter = node;
        }
        friend class SortedList<T>;
        friend class SortedList<T>::Node;
        const_iterator(const const_iterator& const_iterator)
        {
            this->iter = const_iterator.iter;
        }
        const_iterator& operator = (const const_iterator& const_iterator)
        {
            this->iter = const_iterator.iter;
            return *this;
        }
        const_iterator operator++()
        {
            if(this->iter==NULL)
            {
                throw std::out_of_range("out_of_range");
            }
            this->iter = this->iter->next;
            return *this; 
        }
        
        const_iterator operator++(int)
        {
            if((this->iter)==NULL)
            {
                throw std::out_of_range("out_of_range");
            }
            const_iterator tmp = *this;
            this->iter = this->iter->next;
            return tmp;
        }
        
        bool operator == (const const_iterator& const_iterator)
        {
            if (this->iter == const_iterator.iter)
            {
                return true;
            } 
            return false;
        }
        bool operator != (const const_iterator& const_iterator)
        {
            if (this->iter!=const_iterator.iter)
            {
                return true;
            } 
            return false;
        }
        const T& operator * () const
        {
             if((this->iter)==NULL)
            {
                throw std::out_of_range("out_of_range");
            }
            return *(this->iter->data);
        }
    };

 friend class SortedList<T>::Node;
 friend class SortedList<T>::const_iterator;
//1
    SortedList()
    {
        this->size = 0;
        this->first = NULL;
    }
//2
    ~SortedList()
    {
        while (this->first!=NULL)
        {
        Node* tmp = this->first;
        this->first = this->first->next;
        delete tmp;
        }
        this->size = 0;
    }
//3
    SortedList(const SortedList& SortedList)
    {
    this->size = 0;
    this->first = NULL;
    // if it is an empty list
    if(SortedList.first==NULL)
    {
        return;
    }
    Node* SortedList_current = SortedList.first;
    while(SortedList_current!=NULL)
    {
       insert(*(SortedList_current->data));
       SortedList_current = SortedList_current->next;
    } 
    }
//4
    SortedList<T>& operator = (const SortedList& SortedList)
    {
//if its the same list
        if(this->first==SortedList.first)
        {
            return *this;
        }
//free all memory from current list
     while (this->first!=NULL)
        {
        Node* tmp = this->first;
        this->first = this->first->next;
        delete tmp;
        }

//insert the data from the new list to this list
    this->size = 0;
    this->first = NULL;
// if it is an empty list
    if(SortedList.first==NULL)
    {
        return *this;
    }
    Node* SortedList_current = SortedList.first;
    while(SortedList_current!=NULL)
    {
       insert(*(SortedList_current->data));
       SortedList_current = SortedList_current->next;
    }
    this->size = SortedList.size;
    return *this;
    }
//5
    void insert(T t)
    {
    Node* newNode = new Node(t);
    Node* tmp;
    //if the list is empty
    if(this->first==NULL)
    {
        this->first = newNode;
        this->size++;
        return;
    }
    //if this t should be the first 
    if(t < *(this->first->data))
    {
        tmp = this->first;
        this->first = newNode;
        newNode->next = tmp;
        this->size++;
        return;
    }
    //if this t should be the first but they are equel
    if(!(t < *(this->first->data))&&!(*(this->first->data) < t ))
    {
        tmp = this->first;
        this->first = newNode;
        newNode->next = tmp;
        this->size++;
        return;
    }
    //if this t should be ahead
    Node* current = this->first;
    Node* prev;
    while(*(current->data) < t )
    {
        //if this t should be the last
        if (current->next==NULL)
        {
            current->next=newNode;
            this->size++;
            return;
        }
        prev = current;
        current = current->next;
    }
    prev->next = newNode;
    newNode->next = current;
    this->size++;
    }
//6
    void remove(const const_iterator& const_iterator)
    {
    Node* current = this->first;
    Node* prev;
    //if we want to remove the first node
    if (const_iterator.iter == current)
     {
        this->first=current->next;
        delete current;
        this->size--;
        return;
     }
    //if we want to remove any other node
    while (current!=NULL)
     {
        if (const_iterator.iter == current)
        {
            prev->next=current->next;
            delete current;
            this->size--;
            return;
        }
        prev = current;
        current=current->next;
     }
    }
//7
    int length()
    {
      return this->size;
    }
//8
    template <class functionbool>
    SortedList<T> filter(functionbool funcb)
    {
    SortedList<T> boolist;
    Node* current = this->first;
    if(current==NULL)
    {
        boolist.first = NULL;
        return boolist;
    }
    while (current!=NULL)
    {
        if (funcb(*current->data))
        {
            boolist.insert(*current->data);
        }
       current = current->next;
    }
    return boolist;
    }
//9
    template <class function>
    SortedList<T> apply (function func)
    {
    SortedList<T> newlist;
    Node* current = this->first;
    if(current==NULL)
    {
        newlist.first = NULL;
        return newlist;
    }
    while (current!=NULL)
    {
       newlist.insert(func(*(current->data)));
       current = current->next;
    }
    return newlist;
    }
//10
    const_iterator begin() const
    {
    const_iterator it(this->first);
    return it;
    }   
//11
    const_iterator end() const
    {
    const_iterator it(this->first);
    while(it.iter!=NULL)
    {
        it.iter = it.iter->next;
    }
    return it;
    }
};

}