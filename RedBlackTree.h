#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H


#include <iostream>

using namespace std;

struct Node
{
int data ;
Node* parent;
Node* liftchild;
Node* rightchild;
bool color; //red=true , black=false
};

typedef struct Node *Nodeptr;

class RedBlackTree
{
private:
    Nodeptr root;
    Nodeptr TNull;
    void Nodeintialization(Nodeptr node,Nodeptr parent)
    {
        node->data=0;
        node->parent=parent;
        node->liftchild=nullptr;
        node->rightchild= nullptr;
        node->color= false;
    }
    void LeftRotate(Nodeptr z)
    {
        Nodeptr temp=z->rightchild;
        z->rightchild=temp->liftchild;
        if(temp->liftchild!=TNull)
        {
            temp->liftchild->parent=z;
        }
        temp->parent=z->parent;
        if(z->parent== nullptr)
        {
            this->root=temp;
        }
        else if (z==z->parent->liftchild)
        {
            z->parent->liftchild=temp;
        }
        else
        {
            z->parent->rightchild=temp;
        }
        temp->liftchild=z;
        z->parent=temp;
    }
    void RightRotate(Nodeptr z)
    {
        Nodeptr temp=z->liftchild;
        z->liftchild=temp->rightchild;
        if(temp->rightchild!=TNull)
        {
            temp->rightchild->parent=z;
        }
        temp->parent=z->parent;
        if(z->parent== nullptr)
        {
            this->root=temp;
        }
        else if (z==z->parent->rightchild)
        {
            z->parent->rightchild=temp;
        }
        else
        {
            z->parent->liftchild=temp;
        }
        temp->rightchild=z;
        z->parent=temp;
    }
    void InsertionFix(Nodeptr z)
    {
        Nodeptr sipling;
        while(z->parent->color== true)
        {
            if(z->parent==z->parent->parent->rightchild)
            {
                sipling=z->parent->parent->liftchild;
                if(sipling->color==true)
                {
                    sipling->color=false;
                    z->parent->color= false;
                    z->parent->parent->color=true;
                    z=z->parent->parent;
                }
                else
                {
                    if(z==z->parent->liftchild)
                    {
                        z=z->parent;
                        RightRotate(z);
                    }
                    z->parent->color=false;
                    z->parent->parent->color=true;
                    LeftRotate(z->parent->parent);
                }
            }
            else
            {
                sipling=z->parent->parent->rightchild;
                if(sipling->color==true)
                {
                    sipling->color = false;
                    z->parent->color = false;
                    z->parent->parent->color = true;
                    z = z->parent->parent;
                }
                else
                {
                    if(z==z->parent->rightchild)
                    {
                        z=z->parent;
                        LeftRotate(z);
                    }
                    z->parent->color=false;
                    z->parent->parent->color=true;
                    RightRotate(z->parent->parent);
                }
            }
            if(z==root)
            {
                break;
            }
        }
        root->color = false;
    }
    void RedBlackTreeTransplant(Nodeptr x, Nodeptr y)
    {
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->liftchild)
        {
            x->parent->liftchild = y;
        } else
        {
            x->parent->rightchild = y;
        }
        y->parent = x->parent;
    }
    Nodeptr min(Nodeptr z)
    {
        while (z->liftchild != TNull)
        {
            z = z->liftchild;
        }
        return z;
    }
    void DeletationFix(Nodeptr z)
    {
        Nodeptr temp;
        while (z != root && z->color == false)
        {
            if (z == z->parent->liftchild)
            {
                temp = z->parent->rightchild;
                if (temp->color == true)
                {
                    temp->color = false;
                    z->parent->color = true;
                    LeftRotate(z->parent);
                    temp = z->parent->rightchild;
                }
                if (temp->liftchild->color == false && temp->rightchild->color == false)
                {
                    temp->color = true;
                    z = z->parent;
                }
                else
                {
                    if (temp->rightchild->color == false)
                    {
                        temp->liftchild->color = false;
                        temp->color = true;
                        RightRotate(temp);
                        temp = z->parent->rightchild;
                    }
                    temp->color = z->parent->color;
                    z->parent->color = false;
                    temp->rightchild->color = false;
                    LeftRotate(z->parent);
                    z = root;
                }
            }
            else
            {
                temp = z->parent->liftchild;
                if (temp->color == true)
                {
                    temp->color = false;
                    z->parent->color = true;
                    RightRotate(z->parent);
                    temp = z->parent->liftchild;
                }

                if (temp->rightchild->color == false && temp->rightchild->color == false)
                {
                    temp->color = true;
                    z = z->parent;
                }
                else
                {
                    if (temp->liftchild->color == false)
                    {
                        temp->rightchild->color = 0;
                        temp->color = true;
                        LeftRotate(temp);
                        temp = z->parent->liftchild;
                    }
                    temp->color = z->parent->color;
                    z->parent->color = false;
                    temp->liftchild->color = false;
                    RightRotate(z->parent);
                    z = root;
                }
            }
        }
        z->color = false;
    }
    void DeleteNode2(Nodeptr node,int value)
    {
        Nodeptr z = TNull;
        Nodeptr  y;
        while (node != TNull)
        {
            if (node->data == value)
            {
                z = node;
            }

            if (node->data <= value)
            {
                node = node->rightchild;
            } else
            {
                node = node->liftchild;
            }
        }
        if (z == TNull)
        {
           // cout<<" this value is not inside the tree\n";
            return;
        }
        y=z;
        Nodeptr  x;
        bool RealColorOfy=y->color;
        if (z->liftchild == TNull)
        {
            x = z->rightchild;
            RedBlackTreeTransplant(z, z->rightchild);
        }
        else if (z->rightchild == TNull)
        {
            x = z->liftchild;
            RedBlackTreeTransplant(z, z->liftchild);
        } else
        {
            y = min(z->rightchild);
            RealColorOfy= y->color;
            x = y->rightchild;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                RedBlackTreeTransplant(y, y->rightchild);
                y->rightchild = z->rightchild;
                y->rightchild->parent = y;
            }
            RedBlackTreeTransplant(z, y);
            y->liftchild = z->liftchild;
            y->liftchild->parent = y;
            y->color = z->color;
        }
        delete z;
        if ( RealColorOfy == 0)
        {
            DeletationFix(x);
        }
    }
    void DeleteNode(Nodeptr node,int value)
    {
        Nodeptr z = TNull;
        Nodeptr  y;
        while (node != TNull)
        {
            if (node->data == value)
            {
                z = node;
            }

            if (node->data <= value)
            {
                node = node->rightchild;
            } else
            {
                node = node->liftchild;
            }
        }
        if (z == TNull)
        {
            cout<<" this value is not inside the tree\n";
            return;
        }
        y=z;
        Nodeptr  x;
        bool RealColorOfy=y->color;
        if (z->liftchild == TNull)
        {
            x = z->rightchild;
            RedBlackTreeTransplant(z, z->rightchild);
        }
        else if (z->rightchild == TNull)
        {
            x = z->liftchild;
            RedBlackTreeTransplant(z, z->liftchild);
        } else
        {
            y = min(z->rightchild);
            RealColorOfy= y->color;
            x = y->rightchild;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                RedBlackTreeTransplant(y, y->rightchild);
                y->rightchild = z->rightchild;
                y->rightchild->parent = y;
            }
            RedBlackTreeTransplant(z, y);
            y->liftchild = z->liftchild;
            y->liftchild->parent = y;
            y->color = z->color;
        }
        delete z;
        if ( RealColorOfy == 0)
        {
            DeletationFix(x);
        }
    }

    void printHelper(Nodeptr root, string indent, bool last) {
        // print the tree structure on the screen
        if (root != TNull) {
            cout<<indent;
            if (last) {
                cout<<"R----";
                indent += "     ";
            } else {
                cout<<"L----";
                indent += "|    ";
            }

            string sColor = root->color?"RED":"BLACK";
            cout<<root->data<<"("<<sColor<<")"<<endl;
            printHelper(root->liftchild, indent, false);
            printHelper(root->rightchild, indent, true);
        }
        // cout<<root->left->data<<endl;
    }


public:
    RedBlackTree()
    {
        TNull = new Node;
        TNull->color=0;
        TNull->liftchild= nullptr;
        TNull->rightchild= nullptr;
        root=TNull;
    }

    void insert(int value)
    {
        Nodeptr node = new Node;
        node->data=value;
        node->parent= nullptr;
        node->liftchild=TNull;
        node->rightchild=TNull;
        node->color=true;
        Nodeptr x=this->root;
        Nodeptr y= nullptr;
        while (x != TNull)
        {
            y = x;
            if (node->data < x->data)
            {
                x = x->liftchild;
            }
            else
            {
                x = x->rightchild;
            }
        }
        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (node->data < y->data)
        {
            y->liftchild = node;
        }
        else
        {
            y->rightchild = node;
        }
        if (node->parent == nullptr)
        {
            node->color = false;
            return;
        }
        if (node->parent->parent == nullptr)
        {
            return;
        }
        InsertionFix(node);
    }
    void Delete(int value)
    {
        DeleteNode(this->root,value);
    }
    void Print()
    {
        if (root)
        {
            printHelper(this->root, "", true);
        }

    }
    void Clear(int value)
    {
        DeleteNode2(this->root,value);
    }


    Nodeptr getRoot() const{
        return root;
    };
    Nodeptr getTNull() const{
        return TNull;
     };
};


#endif // REDBLACKTREE_H





