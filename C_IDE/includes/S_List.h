//
// Created by loop on 28/03/18.
//
#include <cstdio>
#include <string.h>
#include <iostream>


using std::cout;


#ifndef PROYECTO_1_V0_S_LIST_H
#define PROYECTO_1_V0_S_LIST_H


//Nodo__________________________________________________________________________________________________________________
template<class T>
class Node
{
public:
    T data;
    Node *next;


    Node()
    {
        //data = NULL;
        next = nullptr;
    }
    Node(T data);

    T getData(){return data;}
    void setData(T data){this->data = data;}

    Node *getNext(){return next;}
    void setNext(Node *node){next = node;}
};
template<class T>
Node<T>::Node(T data)
{
    this->data = data;
    next = nullptr;
}




//Lista_________________________________________________________________________________________________________________
template<class T>
class S_List
{
public:
    S_List(){p = nullptr; u = nullptr; cantidad = 0;}
    Node<T>* getFirst(){return p;}
    Node<T>* getLast(){return u;}
    int getSize(){return cantidad;}
    bool isEmpty(){return p== nullptr;}
    void add(T data)
    {
        Node<T>* nuevo = new Node<T>;
        nuevo->setData(data);
        if(isEmpty())
        {
            p = nuevo;
            p->setNext(nullptr);
            u = nuevo;
        }
        else
        {
            u->next = nuevo;
            nuevo->next = nullptr;
            u = nuevo;
        }
        cantidad++;
    }
    void add(T data, int index)
    {
        Node<T>* nuevo = new Node<T>;
        nuevo->data = data;
        if(isEmpty())
        {
            p = nuevo;
            p->next = nullptr;
            u = nuevo;
        }
        else if(index >= cantidad)
        {
            u->next = nuevo;
            nuevo->next = nullptr;
            u = nuevo;
        }
        else if(index <= 0)
        {
            nuevo->next = p;
            p = nuevo;
        }
        else
        {
            Node<T>* piv = p;
            while(piv!= nullptr & index > 1)
            {
                piv = piv->next;
                index--;
            }
            nuevo->next = piv->next;
            piv->next = nuevo;
        }
        cantidad++;
    }
    void edit(T data, int index)
    {
        if(!isEmpty())
        {
            if(index >= cantidad-1)
            {
                u->data = data;
            }
            else if(index <= 0)
            {
                p->data = data;
            }
            else
            {
                Node<T>* piv = p;
                while(index > 0)
                {
                    piv = piv->next;
                    index--;
                }
                piv->data = data;
            }
        }
    }
    bool exist(T n)
    {
        if(!isEmpty())
        {
            Node<T>* piv = new Node<T>;
            piv = p;
            while(piv != nullptr)
            {
                if(piv->data == n)
                {
                    return true;
                }
                piv = piv->next;
            }
            free(piv);
            return false;
        }
    }
    T get(int index)
    {
        if(!isEmpty())
        {
            Node<T>* piv = p;
            while(piv != nullptr & index != 0)
            {
                piv = piv->next;
                index--;
            }
            return piv->data;
        }
    }
    void delFirst()
    {
        if(!isEmpty())
        {
            Node<T>* piv = new Node<T>;
            piv = p;
            p = p->next;
            free(piv);
            cantidad--;
        }
    }
    void delLast()
    {
        if(!isEmpty())
        {
            Node<T>* piv = new Node<T>;
            piv = p;
            while(piv->next != u)
            {
                piv = piv->next;
            }
            u = piv;
            free(piv->next);
            piv->next = nullptr;
            cantidad--;
        }
    }
    void del(int index)
    {
        if(!isEmpty())
        {
            if(index <= 0)
            {
                delFirst();
            }
            else if(index >= cantidad-1)
            {
                delLast();
            }
            else
            {
                index--;
                Node<T>* pre = p;
                while(pre != nullptr & index != 0)
                {
                    pre = pre->next;
                    index--;
                }
                if(pre != nullptr)
                {
                    free(pre->next);
                    cantidad--;
                    pre->next = pre->next->next;
                }
            }
        }
    }
    void del(T _data)
    {
        if(!isEmpty())
        {
            int index = 0;
            Node<T>* piv = p;

            while(piv != nullptr)
            {
                if(piv->data == _data)
                {
                    break;
                }
                index++;
                piv = piv->next;
            }
            if(index == cantidad)//No lo encontro
            {
                return;
            }


            if(index <= 0)
            {
                delFirst();
            }
            else if(index >= cantidad-1)
            {
                delLast();
            }
            else
            {
                index--;
                Node<T>* pre = p;
                while(pre != nullptr & index != 0)
                {
                    pre = pre->next;
                    index--;
                }
                if(pre != nullptr)
                {
                    free(pre->next);
                    cantidad--;
                    pre->next = pre->next->next;
                }
            }
        }
    }
    void delAll()
    {
        int n = cantidad;
        for(int i=0; i < n; i++)
        {
            delFirst();
        }
    }
    void show()
    {
        if(isEmpty())
        {
        }
        else
        {
            cout << "[->]";
            Node<T>* piv = p;

            while(piv != nullptr)
            {
                std::cout << piv->data << "-> ";
                piv = piv->next;
            }
            free(piv);
        }
    }
    void showln()
    {
        if(isEmpty())
        {
            cout << "[->]";
        }
        else
        {
            Node<T>* piv = p;
            while(piv != nullptr)
            {
                cout << piv->data << "-> ";
                piv = piv->next;
            }
            free(piv);
        }
        std::cout << "\n";
    }
    void show2ln()
    {
        if(isEmpty())
        {
            cout << "[->]";
        }
        else
        {
            Node<T>* piv = p;
            while(piv != nullptr)
            {
                cout << "[" << piv->data << "] ";
                piv = piv->next;
            }
            free(piv);
        }
        std::cout << "\n";
    }
    std::string getString()
    {
        std::string str = "";

        if(isEmpty())
        {
            str.append("[->]");
        }
        else
        {
            Node<T>* piv = p;
            while(piv != nullptr)
            {
                str.append("hmm...-> ");
                piv = piv->next;
            }
            free(piv);
        }
        return str;
    }



    Node<T>* p;
    Node<T>* u;
    int cantidad;



};


#endif //PROYECTO_1_V0_S_LIST_H
