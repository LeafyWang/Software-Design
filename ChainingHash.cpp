#include<iostream>
#include<random>
#include<time.h>

#define M 151
using namespace std;

struct node
{
    int     key;
    node*   next;
	node (int k,node* n=NULL) : key(k),next(n) {}
};

class SeparateChainingHash
{
public:
    SeparateChainingHash()
    {
        for(int i=0;i<M;i++) table[i] = NULL;
    }
    void insertion(int key);
    void searchKey(int key);
    void deleteKey(int key);

    void search_noOutput(int key);
private:
    node* table[M];
    int hashKey(int a);
};
int SeparateChainingHash::hashKey(int a)
{
    return a%M;
}
void SeparateChainingHash::insertion(int key)
{
    int hk = hashKey(key);

    if(table[hk]==NULL) table[hk] = new node(key,NULL);
    else
    {
        node* head = table[hk];
        while(head->next!=NULL)
        {
            if(head->key == key) return;
            head = head->next;
        }
        head->next = new node(key,NULL);
    }
}
void SeparateChainingHash::searchKey(int key)
{
    int hk = hashKey(key);

    node* temp = table[hk];
    while(temp!=NULL)
    {
        if(temp->key==key)
        {
            cout << "True." << endl;
            return ;
        }
        temp= temp->next;
    }
    cout << "False" << endl;
}
void SeparateChainingHash::search_noOutput(int key)
{
    int hk = hashKey(key);

    node* temp = table[hk];
    while(temp!=NULL)
    {
        if(temp->key==key)
        {
            return ;
        }
        temp= temp->next;
    }
}
void SeparateChainingHash::deleteKey(int key)
{
    int hk = hashKey(key);

    node* temp = table[hk];
    if(temp->key==key)
    {
        table[hk] = temp->next;
        delete temp;
        return;
    }
    while(temp->next!=NULL)
    {
        if(temp->next->key==key)
        {
            node* d = temp->next;
            temp->next = d->next;
            delete d;
            return;
        }
        temp= temp->next;
    }
}
int main()
{
    cout << "Test" <<endl;
    SeparateChainingHash s1;
    cout << "insert 24,38,66" << endl;
    s1.insertion(24);
    s1.insertion(38);
    s1.insertion(66);
    cout << "search: 24,26" << endl;
    s1.searchKey(24);
    s1.searchKey(26);
    cout << "delete 24 and search 24 again" << endl;
    s1.deleteKey(24);
    s1.searchKey(24);

    s1.deleteKey(38);
    s1.deleteKey(66);


    for(int i=0;i<M*0.3;i++)
    {
        int a = rand() %1500;
        s1.insertion(a);
    }
    clock_t a = clock();
    for(int i=0;i<M*1000;i++)
    {
        int a = rand()%1500;
        s1.search_noOutput(a);
    }
    clock_t b = clock();
    cout << "0.3:\t" << b-a << endl;

    SeparateChainingHash s2;

    for(int i=0;i<M;i++)
    {
        int a = rand() %1500;
        s2.insertion(a);
    }
    a = clock();
    for(int i=0;i<M*1000;i++)
    {
        int a = rand()%1500;
        s2.search_noOutput(a);
    }
    b = clock();
    cout << "1:\t" << b-a << endl;

    SeparateChainingHash s3;

    for(int i=0;i<M*3;i++)
    {
        int a = rand() %1500;
        s3.insertion(a);
    }
    a = clock();
    for(int i=0;i<M*1000;i++)
    {
        int a = rand()%1500;
        s3.search_noOutput(a);
    }
    b = clock();
    cout << "3:\t" << b-a << endl;

    return 0;

}
