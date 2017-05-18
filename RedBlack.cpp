//Leafy 2017/04/25
//Thank BigThigh and Robert Sedgewick
#include<iostream>
#include<queue>

#define RED true
#define BLACK false

using namespace std;

struct node
{
    int key;            //键
    string value;       //值
    bool color;         //颜色 1 红

    int n;              //子树中结点总数
    node* lchild;       //左右子树
    node* rchild;
};

class RBTree
{
public:
    node* root;
    RBTree()
    {
        root = new node;
        cout << "input a number as root of this tree:" ;
        cin >> root->key;
        cout << "input the value:";
        cin >> root->value;

        root->lchild = NULL;
        root->rchild = NULL;
        root->n = 1;
        root->color = BLACK;
    }
    void put();

    void findKey();

    void deleteMin();
    void deleteMax();

    void delete_n();

    void display();
private:
    bool isRed(node* x);
    node* rotateLeft(node* x);
    node* rotateRight(node* x);
    void flipColors(node* x);
    int sizen(node* temp);

    node* put(node* temp,int key,string value);

    void findKey(node* x, int a);

    node* balance(node* x);

    node* moveRedLeft(node* x);
    node* moveRedRight(node* x);
    node* deleteMin(node* x);
    node* deleteMax(node* x);

    node* delete_n(node* x, int key);
    node* minimum(node* nd);
    string get(node* x,int key);
};
string RBTree::get(node* x,int key)
{
    while(x!=NULL)
    {
        if(key<x->key)
            x = x->lchild;
        else if(key>x->key)
            x = x->rchild;
        else return x->value;
    }
}
void RBTree::display()
{
    queue<node*> q;
    if(root==NULL)
        return ;

    q.push(root);
    while(!q.empty())
    {
        node* temp = q.front();
        q.pop();
        cout << temp->key << " " << temp->value << " color:" << temp->color << endl;
        if(temp->lchild!=NULL) q.push(temp->lchild);
        if(temp->rchild!=NULL) q.push(temp->rchild);
    }
}
node* RBTree::balance(node* x)
{
    if( isRed(x->rchild) ) x = rotateLeft(x);
    if( isRed(x->rchild) && !isRed(x->lchild) ) x = rotateLeft(x);
    if( isRed(x->lchild) && isRed(x->lchild->lchild) ) x = rotateRight(x);
    if( isRed(x->lchild) && isRed(x->rchild) ) flipColors(x);

    x->n = 1 + sizen(x->lchild) + sizen(x->rchild);

    return x;
}
void RBTree::findKey()
{
    cout << "input the key you wanna search for:";
    int a;
    cin >> a;
    findKey(root,a);
}
void RBTree::findKey(node* x, int a)
{
    while(x!=NULL)
    {
        if(a<x->key) x = x->lchild;
        else if(a>x->key) x = x->rchild;
        else {
            cout << "find " << a << " " << x->value << endl;
            return ;
        }
    }
    cout << "No such key." << endl;
}
void RBTree::put()
{
    int k;
    string v;

    cout << "input the key:" ;
    cin >> k;
    cout << "input the value:" ;
    cin >> v;

    root = put(root,k,v);
    root->color = BLACK;
}
int RBTree::sizen(node* temp)
{
    if(temp==NULL)
        return 0;
    else
        return temp->n;
}
bool RBTree::isRed(node* x)
{
    if(x==NULL) return false;
    return x->color;
}
node* RBTree::rotateLeft(node* x)//右链接为红时发生的左旋
{
    node* temp = x->rchild;
    x->rchild = temp->lchild;
    temp->lchild = x;

    temp->color = x->color;
    x->color = RED;

    temp->n = x->n;
    x->n = 1 + sizen(x->lchild) + sizen(x->rchild);

    return temp;
}
node* RBTree::rotateRight(node* x)//仅仅更改方向的右旋
{
    node* temp = x->lchild;
    x->lchild = temp->rchild;
    temp->rchild = x;

    temp->color = x->color;
    x->color = RED;

    temp->n = x->n;
    x->n = 1 + sizen(x->lchild) + sizen(x->rchild);

    return temp;
}
void RBTree::flipColors(node* x)
{
    x->color = RED;
    x->lchild->color = BLACK;
    x->rchild->color = BLACK;
}
node* RBTree::put(node* temp,int key,string value)
{
    if(temp==NULL)
    {
        node* newN = new node;
        newN->color = RED;
        newN->key = key;
        newN->value = value;
        newN->rchild = NULL;
        newN->lchild = NULL;
        newN->n = 1;
        return newN;
    }

    if(temp->key > key)
    {
        temp->lchild = put(temp->lchild,key,value);
    }
    else if(temp->key < key)
    {
        temp->rchild = put(temp->rchild,key,value);
    }
    else //==
    {
        temp->value = value;
    }

    if( isRed(temp->rchild) && !isRed(temp->lchild) )
    {
        temp = rotateLeft(temp);
    }
    if( isRed(temp->lchild) && isRed(temp->lchild->lchild) )
    {
        temp = rotateRight(temp);
    }
    if( isRed(temp->lchild) && isRed(temp->rchild) )
    {
        flipColors(temp);
    }

    temp->n = 1 + sizen(temp->lchild) + sizen(temp->rchild);

    return temp;
}
node* RBTree::moveRedLeft(node* x)
{
    //TODO
    x->color = BLACK ;
    x->lchild->color = RED ;
    x->rchild->color = RED ;

    if( isRed(x->rchild->lchild) )
    {
        x->rchild = rotateRight(x->rchild);
        x = rotateLeft(x);
    }
    return x;
}
node* RBTree::moveRedRight(node* x)
{
    //TODO
    x->color = BLACK ;
    x->rchild->color = RED ;
    x->lchild->color = RED ;

    if( !isRed(x->lchild->lchild) )
    {
        x = rotateRight(x);
    }
    return x;
}
void RBTree::deleteMin()
{
    if( !isRed(root->lchild) && !isRed(root->rchild) )
    {
        root->color = RED;
    }
    root = deleteMin(root);
    if( root!=NULL ) root->color = BLACK;
}
void RBTree::deleteMax()
{
    if( !isRed(root->lchild) && !isRed(root->rchild) )
    {
        root->color = RED;
    }
    root = deleteMax(root);
    if( root!=NULL ) root->color = BLACK;
}
node* RBTree::deleteMin(node* x)
{
    if(x->lchild==NULL)
    {
        return NULL;
    }
    if( !isRed(x->lchild) && isRed(x->lchild->lchild) )
    {
        x = moveRedLeft(x);
    }
    x->lchild = deleteMin(x->lchild);
    return balance(x);
}
node* RBTree::deleteMax(node* x)
{
    if( isRed(x->lchild))
    {
        x = rotateRight(x);
    }
    if(x->rchild==NULL)
    {
        return NULL;
    }
    if( !isRed(x->rchild) && !isRed(x->rchild->lchild) )
    {
        x = moveRedRight(x);
    }
    x->rchild = deleteMax(x->rchild);
    return balance(x);
}
void RBTree::delete_n()
{
    cout << "input the key you wanna delete:";
    int k;
    cin >> k;
    if( !isRed(root->lchild) && !isRed(root->rchild) )
    {
        root->color = RED;
    }
    root = delete_n(root,k);
    if( root!=NULL ) root->color = BLACK;
}
node* RBTree::minimum(node* nd)
{
	for (; nd->lchild; nd = nd->lchild);
	return nd;
}
node* RBTree::delete_n(node* x, int key)
{
    if(key < x->key )
    {
        if( !isRed(x->lchild) && !isRed(x->lchild->lchild) )
        {
            x = moveRedLeft(x);
        }
        x->lchild = delete_n(x->lchild,key);
    }
    else
    {
        if(isRed(x->lchild))
            x = rotateRight(x);
        if(key == x->key && x->rchild == NULL )
        {
            return NULL;
        }
        if( !isRed(x->rchild) && !isRed(x->rchild->lchild) )
        {
            x = moveRedRight(x);
        }
        if( key == x->key )
        {
            x->value = get(x->rchild,minimum(x->rchild)->key);
            x->key = minimum(x->rchild)->key;
            x->rchild = deleteMin(x->rchild);
        }
        else
        {
            x->rchild = delete_n(x->rchild,key);
        }
    }
    return balance(x);
}
int main()
{
    RBTree r;

    while(true)
    {
        char choice;
        cout << "input A-insert/update, B-delete, C-search, D-display, E-quit:" ;
        cin >> choice;
        switch(choice)
        {
            case 'A':
                r.put();
                break;
            case 'B':
                r.delete_n();
                break;
            case 'C':
                r.findKey();
                break;
            case 'D':
                r.display();
                break;
            case 'E':
                return 0;
            case 'X':
                r.deleteMax();
                break;
            case 'N':
                r.deleteMin();
                break;
            default:
                cout << "Wrong Command!" << endl;
                break;
        }
    }
    return 0;
}
