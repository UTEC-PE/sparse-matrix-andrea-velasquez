#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
struct Node {
    int row, column;
    T data=0;
    Node* next;
    Node* down;
    Node(){};
    Node(int _row, int _column, int _data=0): row(_row), column(_column), data(_data){};

    killSelf(){
        if (next) this->next->killSelf();
        delete this;
    }
};

#endif