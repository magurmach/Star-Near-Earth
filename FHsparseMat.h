/*
Name:
Class:
Date:
Instructor:
Name of file: a2_1.cpp

Description:
The program allocates a large matrix (such as 100000 x 100000) by sparse matrix
algorithm without using disk storage. Each row of the matrix is a linked list
(FHlist); and the rows are inputted in vector FHvector. The goal of this program
is to test the the sparse matrix by it's set, get, and display functions.
*/




#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;

#define MAT_SIZE 100000
#ifndef MAT_NODE_H
#define MAT_NODE_H

#include <iostream>
using namespace std;




/*
class MatNode
Description: MatNode, a support class, represents a node in the sparse matrix,
containing the column, number, and data of the node.

Object data
Data of node; element in matrix

MatNode(){}
Pre: N/A
Post: N/a

MatNode(int cl, Object dt)
Pre: N/A
Post: The column (cl) and node data (dt) has been set

MatNode(Object dt)
Pre: N/A
Post: The Node data has been set

int getCol() const
Pre: N/A
Post: The column of this Matrix Node has been returned

const Object & operator=( const Object &x )
Pre: N/A
Post: The column and data of this node has been set from 'x'

friend ostream& operator<<(ostream& os, const MatNode& mn)
Pre: N/A
Post: The data has been fed to the ostream operator

bool operator==( const MatNode &x ) const
Pre: N/A
Post: After comparing the 2 MatNodes, true if both are equal, otherwise false
*/




template <class Object>
class MatNode {
protected:
    int col;
public:
    Object data;
    MatNode(){}
    MatNode(int cl, Object dt) : col(cl), data(dt) {}
    MatNode(Object dt) : col(-1), data(dt) {}
    int getCol() const { return col; }
    const Object & operator=( const Object &x ){
        return (data = x);
    }
    bool operator==( const MatNode &x ) const{
        return (data == x.data);
    }
    friend ostream& operator<<(ostream& os, const MatNode& mn){
        os << mn.data;
        return os;
    }
};
#endif




/*
class FHvector
Description: FHvector represents a vector. It works like STL::Vector including
index operator, resize, iterator, size, push_back, and so forth. The Vector
contains the array of an object.

FHvector( int initSize = 0 );
Pre: N/A
Post: The size has been set.

FHvector(const FHvector& rhs);
Pre: N/A
Post: The data from RHS has been copied to this vector

void pop_back();
Pre: N/A
Post: The last element has been removed (if vector is not empty)

const FHvector<Object>& operator= (const FHvector& rhs);
Pre: N/A
Post: The data from RHS has been copied to this vector

~FHvector () { delete[] mObjects; }
Pre: N/A
Post: An array of objects has been deleted

const Object& back() const;
Pre: N/A
Post: The obbject at the back position is returned
Exception: Throw VectorEmptyException (If vector is not empty)

void push_back( const Object& x );
Pre: N/A
Post: The 'x' object has been put to the end of the vector

Object& operator[](int index);
Pre: N/A
Post: An object at index has been returned
Exeption: OutOfBoundsException is thrown (If invalid index)

const Object& operator[] (int index) const;
Pre: N/A
Post: An object at index has been returned
Exception: OutOfBoundsException is thrown (If invalid index)

bool empty() const
Pre: N/A
Post: Return true if vector is empty, otherwise false

int size() const
Pre: N/A
Post: The size of the vector has been returned

class OutOfBoundsException { };
Thrown if vector is called with an invalid index position

class VectorEmptyException { };
Thrown if vector is called when empty

const Object& front() const;
Pre: N/A
Post: An object at the front of the vector has been returned
Exception: VectorEmptyException is thrown (If invalid index)

typedef Object *iterator;
Define iterator as a pointer to Object

typedef const Object *const_iterator;
Define const_iterator iterator as a pointer to const Object

iterator begin() { return &mObjects[0]; }
Pre: Vector is not empty
Post: Iterator has been returned

const_iterator begin() const
Pre: Vector is not empty
Post: Iterator has been returned

iterator end()
Pre: Vector is not empty
Post: Iterator has been returned

const_iterator end() const
Pre: Vector is not empty
Post: Iterator has been returned

void setCapacity(int capacity)
Pre: N/A
Post: Capacity of vector has been set

void resize(int newSize);
Pre: N/A
Post: The size of array has been changed

void reserve(int newCapacity);
//description: create new array and copy current array to it, set new capacity
Pre: N/A
Post:  An array of objects has been altered
*/




#ifndef FHVECTOR_H
#define FHVECTOR_H

template <class Object>
class FHvector
{
private:
    int mSize;
    int mCapacity;
    Object *mObjects;
    static const int m_SPARE_CAPACITY = 16;
public:
    FHvector( int initSize = 0 );
    FHvector(const FHvector& rhs);
    void pop_back();
    const FHvector<Object>& operator= (const FHvector& rhs);
    ~FHvector () { delete[] mObjects; }
    const Object& back() const;
    void push_back( const Object& x );
    Object& operator[](int index);
    const Object& operator[] (int index) const;
    bool empty() const { return (mSize == 0); }
    int size() const { return mSize; }

    class OutOfBoundsException { };
    class VectorEmptyException { };
    const Object& front() const;

    typedef Object *iterator;
    typedef const Object *const_iterator;

    iterator begin() { return &mObjects[0]; }
    const_iterator begin() const { return &mObjects[0]; }
    iterator end() { return &mObjects[size()]; }
    const_iterator end() const { return &mObjects[size()]; }
    void setCapacity(int capacity);

    void resize(int newSize);
    void reserve(int newCapacity);

private:
    void setSize(int size);
};




template <class Object>
FHvector<Object>::FHvector(int initSize)
{
    setSize(initSize);
    setCapacity(mSize + m_SPARE_CAPACITY);
    mObjects = new Object[mCapacity];
}




template <class Object>
FHvector<Object>::FHvector(const FHvector& rhs)
{
    mObjects = NULL;
    operator = (rhs);
}




template <class Object>
Object& FHvector<Object>::operator[]( int index )
{
    if (index < 0 || index >= mSize)
        throw OutOfBoundsException();
    return mObjects[index];
}




template <class Object>
const Object& FHvector<Object>::operator[] (int index) const
{
    if (index < 0 || index >= mSize)
        throw OutOfBoundsException();
    return mObjects[index];
}




template <class Object>
void FHvector<Object>::push_back( const Object& x )
{
    if (mSize == mCapacity)
        reserve(2*mCapacity + 1);
    mObjects[mSize++] = x;
}




template <class Object>
void FHvector<Object>::pop_back()
{
    if (mSize > 0)
        mSize--;
}




template <class Object>
const Object& FHvector<Object>::front() const
{
    if (mSize <= 0)
        throw VectorEmptyException();
    return mObjects[0];
}




template <class Object>
const Object& FHvector<Object>::back() const
{
    if (mSize <= 0)
        throw VectorEmptyException();
    return mObjects[mSize - 1];
}




template <class Object>
void FHvector<Object>::resize( int newSize )
{
    if (newSize <= mCapacity)
    {
        setSize(newSize);
        return;
    }
    reserve(2*newSize + 1);
    setSize(newSize);
}




template <class Object>
void FHvector<Object>::reserve( int newCapacity )
{
    Object *oldObjects;
    int k;

    if (newCapacity < mSize)
        return;

    setCapacity(newCapacity);
    oldObjects = mObjects;
    mObjects = new Object[mCapacity];

    for (k = 0; k < mSize; k++)
        mObjects[k] = oldObjects[k];

    delete[] oldObjects;
}




template <class Object>
void FHvector<Object>::setSize(int size)
{
    mSize = (size < 0)? 0 : size;
}




template <class Object>
void FHvector<Object>::setCapacity(int capacity)
{
    mCapacity = ( capacity <= (mSize + 	m_SPARE_CAPACITY) )? mSize + m_SPARE_CAPACITY : capacity;
}




template <class Object>
const FHvector<Object>& FHvector<Object>::operator= (const FHvector& rhs)
{
    int k;
    if (this == &rhs)
        return *this;
    delete[] mObjects;
    setSize(rhs.mSize);
    setCapacity(rhs.mCapacity);
    mObjects = new Object[mCapacity];
    for (k = 0; k < mSize; k++)
        mObjects[k] = rhs.mObjects[k];
    return *this;
}

#endif




/*
class FHlist
Description: FHlist represents a double linked list -- a head node and a
tail node. The data in the list is between these two nodes.

FHlist()
Pre: N/A
Post: N/A

FHlist( const FHlist &rhs )
Pre: N/A
Post: The data from RHS has been copied to this list

void init()
Pre: N/A
Post: The size, head, and tail has been set with default values

void pop_front()
Pre: N/A
Post: The front object has been deleted, if list is empty, no change.

void push_front( const Object &x )
Pre: N/A
Post: The 'x' is pushed to the front

void pop_back()
Pre: N/A
Post: The 'back' object has been removed from list, if list is empty, no change.

void push_back( const Object &x )
Pre: N/A
Post: The 'x' has been pushed back

~FHlist()
Pre: N/A
Post: Objects has been deleted (tail, head)

bool empty() const
Pre: N/A
Post: Return true if list is empty, otherwise false

int size() const
Pre: N/A
Post: The size of the list has been returned

Object & front()
Pre: List is not empty
Post: The front object has been returned

const Object & front() const
Pre: List is not empty
Post: The const front object has been returned

Object & back()
Pre: List is not empty
Post: The back object has been returned

const Object & back() const
Pre: List is not empty
Post: The const back object has been returned

void clear()
Pre: N/A
Post: The list has been cleared

class const_iterator
Used to iterate the list; not change it

class iterator
Used to iterate the list

const_iterator begin() const
Pre: N/A
Post: The const_iterator has been created and returned

const_iterator end() const
Pre: The list is not empty
Post: The const_iterator has been created and returned

iterator begin()
Pre: List is not empty
Post: The const_iterator has been created and returned

iterator end()
Pre: List is not empty
Post: The const_iterator has been created and returned

class NullIteratorException
Thrown if list is empty whilst iterating

iterator insert( iterator iter, const Object &x )
Pre: N/A
Post: The 'x' is inserted

iterator erase( iterator iter )
Pre: N/A
Post: The element at the current position pointed by the iterator has been erased

iterator erase( iterator start, iterator stop )
Pre: N/A
Post: Elements from (start to stop) pointed by the iterator has been erased

const FHlist<Object> & operator=(const FHlist & rhs )
Pre: N/A
Post: This list has been copied from RHS
*/




#ifndef FHLIST_H
#define FHLIST_H

template <class Object>
class FHlist
{
public:
    // Node prototype - this nested template is defined outside
    class Node;
    FHlist() { init(); }
    FHlist( const FHlist &rhs ) { init(); *this = rhs; }
    void init();
    void pop_front();
    void push_front( const Object &x );
    void pop_back();
    void push_back( const Object &x );
    ~FHlist() { clear(); delete mHead; delete mTail; }
    bool empty() const { return (mSize == 0); }
    int size() const { return mSize; }

    Object & front() { return mHead->next->data; }
    const Object & front() const { return mHead->next->data; }
    Object & back() { return mTail->prev->data; }
    const Object & back() const { return mTail->prev->data; }
    void clear();

    // iterator prototypes - these nested classes are defined outside
    class const_iterator;
    class iterator;

    const_iterator begin() const { return
        const_iterator(mHead->next); }
    const_iterator end() const { return
        const_iterator(mTail); }
    iterator begin() { return iterator(mHead->next, *this); }
    iterator end() { return iterator(mTail, *this); }

    // for exception throwing
    class NullIteratorException { };

    // syntax too difficult to define outside
    iterator insert( iterator iter, const Object &x )
    {
        Node *p = iter.mCurrent;
        if (p == NULL)
            throw NullIteratorException();
        if (p->prev == NULL)
            throw NullIteratorException();
        // build a node around x and link it up
        Node *newNode = new Node(x, p->prev, p);
        p->prev->next = newNode;
        p->prev = newNode;
        iterator newIter(newNode, *this);
        mSize++;
        return newIter;
    }

    iterator erase( iterator iter )
    {
        Node *p = iter.mCurrent;
        if (p == NULL)
            throw iterator::NullIteratorException();
        if (p->prev == NULL || p->next == NULL)
            throw iterator::NullIteratorException();
        iterator retVal(p->next, *this);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        mSize--;
        return retVal;
    }

    iterator erase( iterator start, iterator stop )
    {
        if (start.mCurrent == NULL || stop.mCurrent == 	NULL)
            throw NullIteratorException();
        if (start.mCurrent->prev == NULL ||
            start.mCurrent->next == NULL
            || stop.mCurrent->prev == NULL)
            throw NullIteratorException();
        for (iterator iter = start; iter != stop; )
            iter = erase(iter); // if this throws, then
       // mCurrent erase() will throw, too
            return stop;
    }

    const FHlist<Object> & operator=(const FHlist & rhs );
private:
    // private data for FHlist
    int mSize;
    Node *mHead;
    Node *mTail;
};




template <class Object>
const FHlist<Object> & FHlist<Object>::operator=(const FHlist & rhs )
{
    const_iterator iter;
    if ( &rhs == this)
        return *this;
    clear();
    for (iter = rhs.begin(); iter != rhs.end();
        ++iter)
        this->push_back( *iter );
    return *this;
}




// definition of nested FHlist<Object>::iterator class ---------------------
template <class Object>
class FHlist<Object>::iterator : public FHlist<Object>::const_iterator
{
    friend class FHlist;
protected:
    // chain to base class
    iterator(Node *p, const FHlist<Object> & lst) :
        const_iterator(p, lst) { }
public:
    iterator() { }
    const Object &operator*() const { return const_iterator::operator*(); }
    Object &operator*()
    {
        if (!this->current)
            throw NullIteratorException();
        return this->current->data;
    }
    iterator & operator++()
    {
        if (this->current->next != NULL)
            this->current = this->current->next;
        return *this;
    }
    iterator & operator++(int)
    {
        static iterator old = *this;
        if (this->current->next != NULL)
            this->current = this->current->next;
        return old;
    }
    iterator & operator--()
    {
        if (this->current->prev != NULL)
            this->current = this->current->prev;
        return *this;
    }
    iterator & operator--(int)
    {
        static iterator old = *this;
        if (this->current->prev != NULL)
            this->current = this->current->prev;
        return old;
    }
};




// definition of nested FHlist<Object>::const_iterator class -------------
template <class Object>
class FHlist<Object>::const_iterator
{
    friend class FHlist;
protected:
    // protected member data
    Node *current;
    // protected constructor for use only by derived iterator
    const_iterator(Node *p) : current(p) { }
public:
    const_iterator() : current(NULL) { }
    const_iterator(Node *p, const FHlist<Object> & lst) : current(p){}
    const Object &operator*() const
    {
        if (!current)
            throw NullIteratorException();
        return current->data;
    }
    const_iterator & operator++()
    {
        if (current->next != NULL)
            current = current->next;
        return *this;
    }
    const_iterator & operator++(int)
    {
        static const_iterator old = *this;
        if (current->next != NULL)
            current = current->next;
        return old;
    }
    bool operator==(const const_iterator &rhs) const
    {
        return current == rhs.current;
    }
    bool operator!=(const const_iterator &rhs) const
    {
        return !(*this == rhs);
    }
};




template <class Object>
void FHlist<Object>::pop_back()
{
    Node *p;
    // safer, but a little slower with this test
    if ( mSize == 0 )
        return;
    p = mTail->prev;
    mTail->prev = p->prev;
    mTail->prev->next = mTail;
    delete p;
    mSize--;
}




template <class Object>
void FHlist<Object>::push_back( const Object &x )
{
    Node *p = new Node(x, mTail->prev, mTail);
    mTail->prev->next = p;
    mTail->prev = p;
    mSize++;
}




// public interface
template <class Object>
void FHlist<Object>::clear()
{
    while ( mSize > 0 )
        pop_front();
}




template <class Object>
void FHlist<Object>::push_front( const Object &x )
{
    Node *p = new Node(x, mHead, mHead->next);
    mHead->next->prev = p;
    mHead->next = p;
    mSize++;
}




template <class Object>
void FHlist<Object>::pop_front()
{
    Node *p;
    // safer, but a little slower with this test
    if ( mSize == 0 )
        return;
    p = mHead->next;
    mHead->next = p->next;
    mHead->next->prev = mHead;
    delete p;
    mSize--;
}




template <class Object>
void FHlist<Object>::init()
{
    mSize = 0;
    mHead = new Node;
    mTail = new Node;
    mHead->next = mTail;
    mTail->prev = mHead;
}




template <class Object>
class FHlist<Object>::Node
{
public:
    Node *prev, *next;
    Object data;
    Node( const Object & d = Object(), Node *prv = NULL, Node *nxt = NULL): prev(prv), next(nxt), data(d){ }
};

#endif




/*
class SparseMat

The class represents a sparse matrix.

SparseMat( int r, int c, const Object & defaultVal)
Pre: N/A
Post: N/A

const Object & get(int r, int c) const
Pre: N/A
Post: The object at (row, column) has been returned
Exception: OutOfBoundsException has been thrown if row or column is invalid

bool set(int r, int c, const Object &x)
Pre: N/A
Post: The object at (row, column) has been returned, unless it is invalid

void clear()
Pre: N/A
Post: All the rows have been cleared and returned to defaultVal, whilst leaving
the matrix size unaltered

void showSubSquare(int start, int size)
Pre: Start and size are valid
Post: The submatrix has been outputted to screen

bool search(const Object &x, int& row, int& col)
Pre: N/A
Post: (row, col) has been set; True has been returned if found, otherwise, false
*/




#ifndef FHSPARSE_MAT_H
#define FHSPARSE_MAT_H

template <class Object>
class SparseMat
{
public:
    SparseMat( int r, int c, const Object & defaultVal): ROWS(r), COLS(c), defaultValue(defaultVal), vector(r){ }
    const Object & get(int r, int c) const;
    bool set(int r, int c, const Object &x);
    void clear();
    void showSubSquare(int start, int size);
    bool search(const Object &x, int& row, int& col);
private:
    int ROWS;
    int COLS;
    Object defaultValue;
    FHvector< FHlist<MatNode<Object> > > vector;
};




/*
class SparseMat Implementation

The class uses FHvector and FHlist to implement sparse matrix.
Private members include row and column.
*/




template <class Object>
bool SparseMat<Object>::search(const Object &x, int& row, int& col)
{
    row = -1;
    col = -1;
    for (int r = 0 ; r < ROWS; r++){
        if (vector[r].size() > 0){
            typename FHlist<MatNode<Object> >::iterator iter;
            for (iter = vector[r].begin(); iter != vector[r].end(); iter++)
            {
                if ((*iter).data == x){
                    row = r;
                    col = (*iter).getCol();
                    return true;
                }
            }
        }
    }
    return false;
}




template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x)
{
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS)
        return false;
    bool existing = false;
    if (vector[r].size() > 0){
        typename FHlist<MatNode<Object> >::iterator iter;
        for (iter = vector[r].begin(); iter != vector[r].end(); iter++)
        {
            if ((*iter).getCol() == c){
                *iter = x;
                existing = true;
                break;
            }
        }
    }

    if (!existing){
        vector[r].push_back(MatNode<Object>(c, x));
    }
    return true;
}




template <class Object>
const Object & SparseMat<Object>::get(int r, int c) const
{
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS)
        throw FHvector<FHlist<MatNode<Object> > >::OutOfBoundsException();
    bool existing = false;
    if (vector[r].size() > 0){
        typename FHlist<MatNode<Object> >::const_iterator iter;
        for (iter = vector[r].begin(); iter != vector[r].end(); iter++)
        {
            if ((*iter).getCol() == c){
                return (*iter).data;
            }
        }
    }

    return defaultValue;
}



/*
template <class Object>
void clear()
{
    for (int r = 0; r < ROWS; r++){
        vector[r].clear();
    }
}
*/




template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size)
{
    for (int r = start; r < start + size; r++){
        for (int c = start; c < start + size; c++){
            cout << setw(4) << get(r,c);
        }
        cout << endl;
    }
    cout << endl;
}
#endif




typedef SparseMat<MatNode <float> > SpMat;
