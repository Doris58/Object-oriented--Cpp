#ifndef BIN_TREE_IMPL_H_INCLUDED
#define BIN_TREE_IMPL_H_INCLUDED

///// Implementacija metoda iz Node klase //////////////////////

template <typename T>
Node<T>::Node()    // : left(nullptr), right(nullptr), data() {}
{
    left = right = nullptr; data();
}

template <typename T>
Node<T>::Node(T const & t) : data(t), left(nullptr), right(nullptr)
{}

//// Implementacija metoda iz BinaryTree klase //////////////////

template <typename T>
template <typename Funct>
void BinarySTree<T>::preOrder(Node<T> * root, Funct visit)
{
    if(root != nullptr)
    {
        visit(root->data);
        preOrder(root->left, visit);
        preOrder(root->right, visit);
    }
}

template <typename T>
template <typename Funct>
void BinarySTree<T>::postOrder(Node<T> * root, Funct visit)
{
    if(root != nullptr)
    {
        postOrder(root->left, visit);
        postOrder(root->right, visit);
        visit(root->data);
    }
}

template <typename T>
template <typename Funct>
void BinarySTree<T>::inOrder(Node<T> * root, Funct visit)
{
    if(root != nullptr)
    {
        inOrder(root->left, visit);
        visit(root->data);
        inOrder(root->right, visit);
    }
}

template <typename T>
int BinarySTree<T>::size()
{
    int size = 0;
    preOrder([&size](T data){size++;});
    return size;
}

template <typename T>
bool BinarySTree<T>::empty() const
{
    if(root == nullptr) return true;
    return false;
}

template <typename T>
BinarySTree<T>::BinarySTree() : root(nullptr) {}

template <typename T>
ErrorCode BinarySTree<T>::insert(Node<T> * & root, T const & t)
{
    if(root == nullptr)  
    {
        root = new Node<T>(t);   // --> & is necessary!
        return success;
    }

    // if(isInTree(t)) return duplicate;  (+)

    if(t < root->data) return insert(root->left, t);
    if(t > root->data) return insert(root->right, t);   // no need for else if

    return duplicate;  // (+)
}

template <typename T>
void BinarySTree<T>::clear()  // public mehtod does not take class members as arguments
{                             // --> recursive method must be private
    clear(root);
}

template <typename T>
void BinarySTree<T>::clear(Node<T>* & cvor) 
{
    if(cvor != nullptr)
    {
        clear(cvor->left);
        clear(cvor->right);
        remove(cvor);
    }
}

template <typename T>
bool BinarySTree<T>::isInTree(T const & t)
{
    if(isInTree(root, t) == nullptr) return false;
    return true;
}

template <typename T>
Node<T>*& BinarySTree<T>::isInTree(Node<T>* & cvor, T const & t)   // & is necessary for the remove method
{
    // if cvor == nullptr, cvor->data is not defined (also cvor->left and cvor->right, since there is no node referenced by cvor)
    if(cvor == nullptr)
        return cvor;

    if(t == cvor->data)
        return cvor;

    if(t < cvor->data) 
        return isInTree(cvor->left, t);

    // if(t > cvor->data) 
    return isInTree(cvor->right, t);
    
}

template <typename T>
ErrorCode BinarySTree<T>::remove(T const & t)
{  
    Node<T>*& node = isInTree(root, t);
    return remove(node);
}

template <typename T>
ErrorCode BinarySTree<T>::remove(Node<T> * & root)
{
    if(root == nullptr) return notfound;

    Node<T>* temp = root;

    if(root->left == nullptr && root->right == nullptr) 
        root = nullptr;              // --> & is necessary

    else if(root->left == nullptr) 
        root = root->right;          // --> & is necessary

    else if(root->right == nullptr) 
        root = root->left;           // --> & is necessary
    
    else
    {
        root->data = najmanji(root->right);
        return success;
    }

    delete temp;
    return success;
}

template <typename T>
T BinarySTree<T>::najmanji(Node<T>* & root)
{
    Node<T>* temp;
    T min_data;

    if(root->left == nullptr) 
    {
        min_data = root->data; 
        temp = root; 
        root = root->right;   // & is necessary; root = root->right is OK also if root->right == nullptr
        delete temp;
    }
    else 
        min_data = najmanji(root->left);

    return min_data;
}

#endif 
// BIN_STABLO_IMPL_H_INCLUDED



/*
    Notes to observe

    By definiton of Binary Search Tree:
    - each element in the left subtree is less than the root,
    - each element in the right subtree is greater than the root,
    - going from the root down to the left elements are decreasing,
    - going from the root down to the right elements are increasing

*/