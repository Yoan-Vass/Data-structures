#include<iostream>
#include<stdexcept>
using namespace std;

template <class T>
class Queue{
private:
    T* arr;
    size_t capacity, length; 
    int head, tail;

    void Copy(const T& other);
    void Move(T&& other);
    void Free();
    void Resize();
public:
    size_t size() const;
    bool empty() const;
    void pop();
    const T& front() const;
    const T& back() const;
    void push(const T& data);

    Queue();
    virtual ~Queue();
    Queue(const T& other);
    Queue<T>& operator=(const T& other);
    Queue(T&& other);
    Queue<T>& operator=(T&& other);
};


template <class T>
inline void Queue<T>::Resize()
{
    T* a = new T[2*capacity];
    for(size_t i=0; i<length; i++) a[i] = arr[(head+i)%capacity];
    head = 0; tail=length-1; capacity*=2;
    delete [] arr; arr=a;
}

template <class T>
inline bool Queue<T>::empty() const
{
    return length == 0;
}

template <class T>
inline size_t Queue<T>::size() const
{
    return length;
}

template <class T>
inline void Queue<T>::pop()
{
    if(length==0) throw runtime_error("Queue empty");
    length--;
    head=(head+1)%capacity;
    if(length==0){head = 0; tail = -1;}
}

template <class T>
inline const T &Queue<T>::front() const
{
    if(length==0) throw runtime_error("Queue empty");
    return arr[head];
}

template <class T>
inline const T &Queue<T>::back() const
{
    if(length==0) throw runtime_error("Queue empty");
    return arr[tail];
}

template <class T>
inline Queue<T>::Queue()
{
    arr=new T[1];
    length = 0; capacity = 1;
    head = 0; tail = -1;
}

template <class T>
inline Queue<T>::~Queue()
{
    Free();
}

template <class T>
inline void Queue<T>::push(const T &data)
{
    if(length==capacity) Resize();
    tail = (tail + 1 ) % capacity;
    arr[tail]=data; length++;
}

template <class T>
inline void Queue<T>::Copy(const T &other)
{
    capacity=length=other.length();
    tail=capacity-1;
    arr= new T[length];    
    size_t i, index;
    for(i=0; i<length; i++){
        index=(other.head+i)%length;
        arr[i]=other.arr[index];
    }
}

template <class T>
inline void Queue<T>::Move(T &&other)
{
    capacity=length=other.length();
    tail=other.tail; head=other.head();
    arr= other.arr; other.arr=nullptr;
}

template <class T>
inline void Queue<T>::Free()
{
    delete[] arr; arr=nullptr;
    capacity=length=0;
}

template <class T>
inline Queue<T>::Queue(const T &other)
{
    Copy(other);
}

template <class T>
inline Queue<T> &Queue<T>::operator=(const T &other)
{
    if(this != &other){
        Free();
        Copy(other);
    }   
    return *this;
}

template <class T>
inline Queue<T>::Queue(T &&other)
{
    Move(move(other));
}

template <class T>
inline Queue<T>& Queue<T>::operator=(T &&other)
{
    if(this != &other){
        Free();
        Move(move(other));
    }   
    return *this;
}
