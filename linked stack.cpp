#include<iostream>
#include<stdexcept>
using namespace std;

template <class T>
class Stack{
private:
    struct Node{
        T data;
        Node* next;
        Node(const T& data, Node* next=nullptr) : data(data), next(next){}
    };
    size_t length;
    Node* head;

    void Free();
    void Copy(const Stack<T>& other);
    void Move(Stack<T>&& other);

public:
    bool empty() const;
    size_t size() const;
    void push(const T& data);
    void pop();
    const T& top() const;

    Stack();
    Stack(const Stack<T>& other);
    Stack(Stack<T>&& other);
    Stack<T>& operator=(const Stack<T>& other);
    Stack<T>& operator=(Stack<T>&& other);
    ~Stack();

    
};

template <class T>
bool Stack<T>::empty() const{
    return length == 0;
}

template <class T>
size_t Stack<T>::size() const{
    return length;
}

template <class T>
void Stack<T>::pop() {
    if(head==nullptr) throw runtime_error("Stack emopty!");
    const Node* temp=head;
    head=head->next;
    length--;
    delete temp;
}

template <class T>
const T& Stack<T>::top() const {
    if(head==nullptr) throw runtime_error("Stack emopty!");
    return head->data;
}

template <class T>
void Stack<T>::push(const T& data){
    head=new Node(data, head);
    length++;
}

template <class T>
void Stack<T>::Free(){
    while(head) pop();
}

template <class T>
void Stack<T>::Copy(const Stack<T>& other){
    if(other.empty()) {head=nullptr; return;}
    length=other.length;
    Node* toCopy=other.head, *ptr;

    ptr=head=new Node(toCopy->data);
    while(toCopy->next){
        toCopy = toCopy->next;
        ptr->next = new Node(toCopy->data);
        ptr = ptr->next;
    }
}

template <class T>
void Stack<T>::Move(Stack<T>&& other){
    head=other.head;
    length=other.length;
    other.head=nullptr; other.length=0;
}

template <class T>
Stack<T>::Stack() : length(0), head(nullptr) { }

template <class T>
Stack<T>::Stack(const Stack<T>& other){
    Copy(other);
}

template <class T>
Stack<T>::Stack(Stack<T>&& other){
    Copy(move(other));
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other){
    if(this != &other){
        Free();
        Copy(other);
    }
    return  *this;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other){
    if(this != &other){
        Free();
        Move(move(other));
    }
    return  *this;
}

template <class T>
Stack<T>::~Stack(){
    Free();
}

int main(){
    // Stack<int> s1,s2;
    // s1.push(1); s1.push(2);  s1.push(3); 
    // s2=s1;
    // s2.pop(); cout<<s2.size()<<" "<<s2.top()<<endl;

    return 0;
}