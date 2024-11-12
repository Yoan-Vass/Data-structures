#include<iostream>
using namespace std;

template <class T>
class Stack{
private:
    T* arr;
    size_t capacity, length; 

    void Copy(const Stack<T>& other);
    void Move(Stack<T>&& other);
    void Free();
    void Resize();
public:
    size_t size() const;
    size_t empty() const;
    void pop();
    const T& top();
    void push(const T& data);

    Stack();
    virtual ~Stack();
    Stack(const Stack<T>& other);
    Stack<T>& operator=(const Stack<T>& other);
    Stack(Stack<T>&& other);
    Stack<T>& operator=(Stack<T>&& other);
};


template <class T>
inline void Stack<T>::Resize()
{
    capacity*=2;
    T* anew=new T[capacity];
    for(size_t i=0; i<length; i++)anew[i]=arr[i];
    delete[] arr; arr=anew;
}

template <class T>
inline size_t Stack<T>::empty() const
{
    return length == 0;
}

template <class T>
inline void Stack<T>::pop()
{
    if(length==0) throw "Stack empty";//!
    length--;
}

template <class T>
inline const T &Stack<T>::top()
{
    if(length==0) throw "Stack empty!";
    return arr[length-1];
}

template <class T>
inline void Stack<T>::push(const T &data)
{
    if(length==capacity) Resize();
    arr[length++]=data;
}

template <class T>
inline void Stack<T>::Copy(const Stack<T> &other)
{
    capacity=length=other.length();
    arr= new T[length];    
    for(size_t i=0; i<length; i++) arr[i]=other.arr[i];
}

template <class T>
inline void Stack<T>::Move(Stack<T> &&other)
{
    capacity=length=other.length();
    arr= other.arr; other.arr=nullptr;    
}

template <class T>
inline void Stack<T>::Free()
{
    delete[] arr;
    capacity=length=0;
}

template <class T>
inline size_t Stack<T>::size() const
{
    return length;
}

template <class T>
inline Stack<T>::Stack() : capacity(1), length(0)
{
    arr=new T[1];
}

template <class T>
inline Stack<T>::~Stack()
{
    Free();
}

template <class T>
inline Stack<T>::Stack(const Stack<T> &other)
{
    Copy(other);
}

template <class T>
inline Stack<T>& Stack<T>::operator=(const Stack<T> &other)
{
    if(&other!=this){
        Free();
        Copy(other);
    }
    return *this;
}

template <class T>
inline Stack<T>::Stack(Stack<T> &&other)
{
    Move(move(other));
}

template <class T>
inline Stack<T> &Stack<T>::operator=(Stack<T> &&other)
{
    if(&other!=this){
        Free();
        Move(move(other));
    }
    return *this;
}


int main(){

    
    return 0;
}
