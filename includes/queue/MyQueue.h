#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <cassert>
#include <iostream>
using namespace std;

#include "../node/node.h"
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                                    //give access to list to access _ptr
        Iterator() : _ptr(nullptr) { }
        Iterator(node<T>* p) : _ptr(p) { }                               
        T operator *()
        {
            return _ptr->_item;
        }
        bool is_null()
        {
            return (_ptr == nullptr);
        }    
        friend bool operator !=(const Iterator& left, 
        const Iterator& right)  
        {
            return (left._ptr != right._ptr);
        }
        friend bool operator ==(const Iterator& left,
        const Iterator& right)  
        {
            return (left._ptr == right._ptr);  
        }

        //member operator:++it or ++it = new_value
        Iterator& operator++()
        {                         
            _ptr = _ptr->_next;
            return Iterator(_ptr);   
        }
        //friend operator: it++
        friend Iterator operator++(Iterator& it,
        int unused)
        {
            Iterator hold(it);
            it._ptr = it._ptr->_next;
            return hold;         
        }

    private:
        node<T>* _ptr;                          
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();
    //Iterator to the head node
    Iterator begin() const
    {
        return Iterator(_front);
    }           
    //Iterator to NULL                          
    Iterator end() const
    {
        return Iterator(nullptr);
    }                                       
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe)
    {
        outs << "Queue :";
        _print_list(printMe._front);
        return outs;
    }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};
//--------------------------------------------------------------------------
template <typename T> Queue<T>::Queue()
{
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}
template <typename T> Queue<T>::Queue(const Queue<T>& copyMe)
{
    _front = _copy_list(copyMe._front);
    _rear = _copy_list(_rear, _front);
    _size = copyMe.size();
}
template <typename T> Queue<T>::~Queue()
{
    _clear_list(_front);
    _rear = nullptr;
    _size = 0;
}
template <typename T> Queue<T>& Queue<T>::operator=(const Queue<T>& RHS)
{
    if (this == &RHS)
        return  *this;
    if (_front)
    {
        _clear_list(_front);
        _rear = nullptr;
        _size = 0;
    }

    _front = _copy_list(RHS._front);
    _rear = _copy_list(_rear, _front);
    _size = RHS.size();

    return *this;
}
template <typename T> bool Queue<T>::empty()
{
    return (_front == nullptr && _size == 0);
}
template <typename T> T Queue<T>::front()
{
    return _front->_item;
}
template <typename T> T Queue<T>::back()
{
    return _rear->_item;
}
template <typename T> void Queue<T>::push(T item)
{
    _size++;
    bool debug = false;
    // This function inserts in appropriate location
    // and returns the node inserted. . .which 
    // happens to always be the last node in Queue.
    _rear = _insert_after(_front, _rear, item);
}
template <typename T> T Queue<T>::pop() //NOT WORKING PROPERLY. . .
{
    T deleted;
    _size--;
    if (_front)
    {
        deleted = _delete_node(_front, _front);
        if (_size == 1)
            _rear = _front;
    }
    return deleted;
}
#endif //MYQUEUE_H