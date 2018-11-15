#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* origin;
        int columns;
        int rows;

    public:
        Matrix(){};
        Matrix(int sizeX, int sizeY) : columns(sizeX), rows(sizeY){
            Node<T> *temp, *tempnext;
            origin = new Node<T>(0,0);
            temp = origin;

            tempnext = new Node<T>(0,1);
            tempnext->down = nullptr;
            temp->next = tempnext;

            // Horizontal
            for (int i=1;  i<sizeX; ++i){
                // Create new node, point and move
                tempnext = new Node<T>(0,i);
                tempnext->down = nullptr;
                temp->next = tempnext;
                temp = tempnext;
            }
            temp->next = nullptr;

            temp = origin; // reset

            // Vertical
            for (int i=1;  i<sizeY; ++i){
                // Create new node, point and move
                tempnext = new Node<T>(i,0);
                tempnext->next = nullptr;
                temp->down = tempnext;
                temp = tempnext;
            }
            temp->down = nullptr;
        };

        void set(int row, int col, T data){
            if (0>row || row>=rows || 0>col || col>=columns) throw "Invalid coordinate";

            Node<T>* prev_row_temp, *temp, *prev_column;
            prev_column = temp = origin;
            bool pause = true;

            // go down and right
            while (temp->row!=row) temp = temp->down;
            prev_row_temp = temp;
            while (temp->next && temp->next->column<=col){
                if (pause) pause=false;
                else prev_row_temp=prev_row_temp->next;

                temp = temp->next;
            }
            
            // go right and down
            while (prev_column->column!=col) prev_column=prev_column->next;
            while (prev_column->down && prev_column->down->row<row) prev_column=prev_column->down;

            // Create (avoid creating node for data 0)
            if (temp->column!=col){
                if (!data) return;

                Node<T>* newnode = new Node<T>(row, col, data);
                newnode->next = temp->next;
                newnode->down = prev_column->down;

                temp->next = newnode;
                prev_column->down = newnode;

                return;
            }

            // Exists and data==0 and node is not a header (erase)
            if (!data && row && col){

                prev_column->down = temp->down;
                prev_row_temp->next = temp->next;

                delete temp;
                temp = nullptr;
                return;
            }

            // Exists
            temp->data = data;

        };

        T operator()(int row, int col){
            if (0>row || row>=rows || 0>col || col>=columns) throw "Invalid coordinate";

            Node<T>* temp=origin;

            while (temp->row!=row) temp=temp->down;
            while (temp->column<col && temp->next) temp=temp->next;
            if (temp->column!=col) return 0; // TODO: or ""?

            return temp->data;
        };
        Matrix<T> operator*(Matrix<T> other);
        Matrix<T> operator*(T scalar);
        Matrix<T> operator+(Matrix<T> other);
        Matrix<T> operator-(Matrix<T> other);
        Matrix<T> transposed();
        Matrix<T> operator=(Matrix<T> other);

        //~Matrix();
};

#endif