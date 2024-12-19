#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cmath>

using namespace std;

template<class T>
class BST{
    struct Node{
        Node *left, *right;
        T data;
        Node(const T& data, Node* l=nullptr, Node* r=nullptr) : data(data), left(l), right(r) {}
    };
    Node* root=nullptr;
    
    Node* copy(const Node* other) const;//! Връща Node
    bool contains(const Node* cr, const T& data) const;
    Node* insert(Node* cr, const T& data) const;//! Връща Node
    Node* remove(Node* cr, const T& data) const;//! Връща Node
    void free(Node* cr) const;
    const T& findMin(const Node* cr) const;
    Node* deleteMin(Node* cr, T& val) const;
    void inorder(Node* cr) const;
    

    void Move(BST<T>&& other);
    void Copy(const BST<T>& other);
    void Free();

    
public: 
    BST() = default;
    BST(const BST<T>& other);
    BST(BST<T>&& other);
    BST& operator = (const BST<T>& other);
    BST& operator = (BST<T>&& other);
    ~BST();

    bool contains(const T& data) const;
    void insert(const T& data); 
    void remove(const T& data); 
    void inorder() const;//Morris traversal algorithm
};

template <class T>
void BST<T>::Copy(const BST<T>& other)
{
    root = copy(other->root);
}

template <class T>
void BST<T>::Move(BST<T>&& other)
{
    root = other->root;
    other->root=nullptr;
}

template <class T>
void BST<T>::Free()
{
    free(root);
    root=nullptr;
}

template <class T>
BST<T>::BST(const BST<T> &other)
{
    Copy(other);
}

template <class T>
BST<T>::BST(BST<T> &&other)
{
    Move(move(other));
}

template <class T>
BST<T>& BST<T>::operator=(const BST<T> &other)
{
    if(&other==this){
        Free();
        Copy(other);
    }
    return *this;
}

template <class T>
BST<T>& BST<T>::operator=(BST<T> &&other)
{
    if(&other==this){
        Free();
        Move(other);
    }
    return *this;
}

template <class T>
BST<T>::Node* BST<T>::copy(const Node *other) const
{
    if(other==nullptr) return nullptr;
    Node* cr = new Node(other->data, copy(other->left), copy(other->right));
    return cr;
}

template <class T>
bool BST<T>::contains(const Node *cr, const T &data) const
{
    if(cr==nullptr)return false;
    if(cr->data==data)return true;
    return contains(cr->left,data) || contains(cr->right,data);
}

template <class T>
BST<T>::Node* BST<T>::insert(Node *cr, const T &data) const
{
    if(cr==nullptr) return new Node(data);
    if(cr->data == data) return cr;
    if(data < cr->data) cr->left=insert(cr->left, data);
    else cr->right = insert(cr->right, data);
    return cr;
}

template <class T>
BST<T>::Node *BST<T>::remove(Node *cr, const T &data) const
{
    if (cr==nullptr) throw runtime_error("No such element");
    Node* temp;
    if (data == cr->data){
        if(cr->left==nullptr && cr->right==nullptr) {delete cr;  return nullptr; }
        else if(cr->left==nullptr) {temp=cr->right; delete cr; return temp;}
        else if(cr->right==nullptr) {temp=cr->left; delete cr; return temp;}
        //find min in rtree and swap
        // const T& var= findMin(cr); cr->data=var; cr->right=remove(cr->right, var);
        cr->right = deleteMin(cr->right, cr->data);
        return cr;
    }

    if(data < cr->data) cr->left=remove(cr->left, data);
    else cr->right=remove(cr->right, data);
    return cr;
}

template <class T>
void BST<T>::free(Node *cr) const
{
    if(cr==nullptr) return;
    free(cr->left);
    free(cr->right);
    delete cr; cr=nullptr;
}

template <class T>
BST<T>::Node* BST<T>::deleteMin(Node *cr, T &val) const
{
    if (cr==nullptr) throw runtime_error("Empty tree!");
    if(cr->left==nullptr) {val=cr->data; delete cr; return nullptr;}
    cr->left=deleteMin(cr->left, val);
    return cr;
}

template <class T>
void BST<T>::inorder(Node *root) const
{
    BST<T>::Node *cr=root, *previous;
    while(cr){
        if(cr->left==nullptr) {cout<<cr->data<<" "; cr=cr->right; }
        else {
            //there is a left subtree, find the predecessor of cr there
            previous=cr->left;
            while(previous->right!=nullptr && previous->right!=cr) previous=previous->right;
            if(previous->right==nullptr){
                //predecessor found
                previous->right=cr;     
                cr=cr->left; //traversal of the left tree prepared, traverse
            }
            else{
                //predecessor already found
                previous->right=nullptr;
                cout<<cr->data<<" "; cr=cr->right;
            }
        }

    }
    cout<<endl;
}

template <class T>
const T& BST<T>::findMin(const Node *cr) const
{
    if (cr==nullptr) throw runtime_error("Empty tree!");
    Node* temp;
    while(temp->left) temp=temp->left;
    return cr->data;
}

template <class T>
BST<T>::~BST()
{
    Free();
}

template <class T>
bool BST<T>::contains(const T &data) const
{
    return contains(root, data);
}

template <class T>
void BST<T>::insert(const T &data)
{
    root = insert(root,data);
}

template <class T>
void BST<T>::remove(const T &data)
{
    root=remove(root,data);
}

template <class T>
void BST<T>::inorder() const
{
    inorder(root);
}

int main(){
    BST<int> t;
    t.insert(4); t.insert(2); t.insert(8); t.insert(1); t.insert(3);

    cout<<t.contains(5)<<endl;
    cout<<t.contains(2)<<endl;
    t.remove(2);
    cout<<t.contains(2)<<endl;
    cout<<t.contains(3)<<endl;
    cout<<t.contains(1)<<endl;
    

    return 0;
}