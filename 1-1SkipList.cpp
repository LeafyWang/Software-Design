//Leafy code 2017/03/11  test 3/14
//Skip List 1-1
#include<iostream>
#include <cstdlib>
using namespace std;

struct nodes{
    int value;     //the value of the node
    int layer;     //number of the level
    nodes * nextr; //next node
    nodes * nextl;
};

nodes* new_list()/*create a skip list with two nodes*/
{
    nodes* root = new nodes;
    root->value = -1;
    root->layer = 1;
    root->nextl = NULL;
    root->nextr = new nodes;

    root->nextr->value = 1;
    root->nextr->layer = 1;
    root->nextr->nextl = NULL;
    root->nextr->nextr = NULL;
    return root;
}
nodes* add_layer(nodes* root)
{
    nodes* newr = new nodes;
    newr->layer= root->layer + 1;
    newr->value= -1;
    newr->nextl=root;

    nodes* temp = root;
    while(temp->value!=1){
        temp = temp->nextr;
    }
    newr->nextr= new nodes();
    newr->nextr->value = 1;
    newr->nextr->layer = newr->layer;
    newr->nextr->nextr = NULL;
    newr->nextr->nextl = temp;

    return newr;
}
int rand_layer()//a short function to calculate a random number which means the layer of new node.
{
    int n = 1;
    while(rand()%10>4 && n<=9)
        n++;
    return n;
}
nodes* insert_d(nodes* r,int v,nodes* newp)
{
    while(r->nextr->value< v && r->nextr->value!=1){
        r = r->nextr;
    }
    nodes* temp = r->nextr;
    r->nextr = new nodes;
    r->nextr->value = v;
    r->nextr->layer = r->layer;
    r->nextr->nextr = temp;
    r->nextr->nextl = NULL;

    if(newp!=NULL){
        newp->nextl = r->nextr;
    }
    return r->nextr;
}
nodes* insertion(int v,nodes* root)//insert a node into the skip_list
{
    int level = rand_layer();

    nodes * temp = root;
    nodes * neig = root->nextr;

    while(temp->layer>level)  //找到本层前
    {
        neig = temp->nextr;
        if(temp->value==-1 && neig->value==1)//本层没有其他节点
        {
            temp = temp->nextl;
        }
        else if(temp->value < v && neig->value==1)//到最后一个点仍然比新加入点值小
        {
            temp = temp->nextl;
        }
        else if(neig->value < v)//yima no ni point wa <
        {
            temp = temp->nextr;
        }
        else {//temp->value < v < temp->nextr->value
            temp = temp->nextl;
        }
    }
    //zai benceng xunzhao weizhi
    nodes* newp = NULL;
    while(temp!=NULL)
    {
        newp = insert_d(temp,v,newp);
        temp = temp->nextl;
    }
    return root;
}
void display(nodes* root)//show the skip list from high layer to low layer
{
    nodes* temp = root;
    if(root->value==-1&&root->nextr->value==1)
    {
        display(root->nextl);
        return;
    }
    while(temp!=NULL)
    {
        nodes* nex = temp;
        while(nex!=NULL)
        {
            if(nex->value!=-1&& nex->value!=1)
                cout << nex->value << " ->" ;
            nex = nex->nextr;
        }
        cout << endl;
        temp = temp->nextl;
    }
}
nodes* searching(int v,nodes* root,int type)//find a node and return the address of another node which lies left to it
{
    if(type==0)cout << "search for " << v << ": " ;
    nodes* temp = root;
    while(temp!=NULL)
    {
        if(temp->value==-1 && temp->nextr->value==1)
        {
            temp = temp->nextl;
        }
        else if(temp->value<v && temp->nextr->value==1)
        {
            temp = temp->nextl;
        }
        else if(temp->nextr->value < v)
        {
            temp = temp->nextr;
        }
        else
        {
            if(temp->nextr->value==v)
            {
                if(type==0)cout << "find " << v << endl;
                return temp;
            }
            temp = temp->nextl;
        }
    }
    if(type==0)cout << "cannot find " << v << endl;
    return NULL;
}
void delete_s(int v,nodes* root)
{
    nodes* former = searching(v,root,1);
    if(former == NULL)
    {
        cout << "Can't delete: no such point!" << endl;
        return ;
    }
    while(former!=NULL)
    {
        nodes* del = former->nextr;
        former->nextr = former->nextr->nextr;
        delete del;
        former = searching(v,former->nextl,1);
    }
    display(root);
}
int main()
{
    int n_count = 0;
    nodes * root = new_list();
    while(root->layer!=10)
        root = add_layer(root);

    cout << "Now we insert some number into the skip list:" << endl;
    for(int x=2;x<6;x++)
        insertion(x*x,root);
    for(int y=12;y>5;y--)
        insertion(y*y,root);
    display(root);
    cout << "----------------------------------------" << endl;
    cout << "Now we begin to search some numbers:" << endl;
    searching(9,root,0);
    searching(18,root,0);
    searching(230,root,0);
    searching(3,root,0);
    searching(64,root,0);
    cout << "----------------------------------------" << endl;
    cout << "Now we try to delete some nodes:" << endl;
    cout << "16" << ":" << endl ;
    delete_s(16,root);
    cout << "18" << ":" << endl ;
    delete_s(18,root);

    cout << "ALL CORRECT." <<endl;

    return 0;
}
