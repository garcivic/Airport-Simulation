#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
using namespace std;


template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator
    {
    public:
        //give access to list to access _ptr
        friend class Stack;                 
        Iterator(){ _ptr = nullptr; }           
        //Point Iterator to where p is pointing to
        Iterator(node<ITEM_TYPE>* p) : _ptr(p) { }      
        //dereference operator                                    
        ITEM_TYPE operator *(){ return _ptr->_item; }
        //true if _ptr is NULL    
        bool is_null(){return _ptr == nullptr;}            
        friend bool operator !=(const Iterator& left, const Iterator& right)  //true if left != right
        { return left._ptr != right._ptr; }

        friend bool operator ==(const Iterator& left, const Iterator& right)  //true if left == right
        { return left._ptr == right._ptr; }

        //member operator:++it
        // or ++it = new_value
        Iterator& operator++()
        {
            _ptr = _ptr->_next;
            return Iterator(_ptr);                        
        }
        //friend operator: it++
        friend Iterator operator++(Iterator& it, int unused)
        {        
            assert(it._ptr!=nullptr );
            Iterator hold(it._ptr);
            it._ptr = it._ptr->_next;
            return hold;
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<ITEM_TYPE>& copyMe);
    ~Stack() 
    { 
        _clear_list(_top); 
        _size = 0;
    }
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe)
    {
        outs << "Stack : ";
        _print_list(printMe._top);
        return outs;
    }
    //Iterator to the head node
    Iterator begin() const 
    {
        return Iterator(_top);
    }
    //Iterator to NULL               
    Iterator end() const
    {
        return Iterator(nullptr);
    }                     
    int size() const { return _size; }

private:
    node<ITEM_TYPE>* _top;
    int _size;
};
template<typename ITEM_TYPE> Stack<ITEM_TYPE>::Stack()
{
    _top = nullptr;
    _size = 0;
}
template<typename ITEM_TYPE> Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE>& copyMe)
{
    _top = _copy_list(copyMe._top);
    _size = copyMe.size();
}
template<typename ITEM_TYPE> Stack<ITEM_TYPE>& Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE>& RHS)
{
    if (this == &RHS)
        return *this;

    if(_top)
        _clear_list(_top);
    _top = _copy_list(RHS._top);
    _size = RHS.size();
    
    return *this;
}
template <typename ITEM_TYPE> ITEM_TYPE Stack<ITEM_TYPE>::top()
{
    return _top->_item;
}
template <typename ITEM_TYPE> bool Stack<ITEM_TYPE>::empty()
{
    return (!_top && size() == 0);
}
template <typename ITEM_TYPE> void Stack<ITEM_TYPE>::push(ITEM_TYPE item)
{
    _top = _insert_head(_top, item);
    _size++;
}
template <typename ITEM_TYPE> ITEM_TYPE Stack<ITEM_TYPE>::pop()
{
    ITEM_TYPE item_deleted;
    if (_top)
    {
        item_deleted = _delete_node(_top, _top);
        _size--;
    }
    return item_deleted;
}
#endif //MYSTACK_H