#include<iostream>
#include<random>
#include<time.h>

#define M 151
using namespace std;

class LinearProbingHash
{
public:
    LinearProbingHash()
    {
        for(int i=0;i<M;i++) table[i]=-1;
    }
    void insertion(int key);
    void searchKey(int key);
    void deleteKey(int key);

    void search_noOutput(int key);
private:
    int table[M];
    int hashKey(int a);
};
void LinearProbingHash::insertion(int key)
{
    int pos = hashKey(key);

    while(table[pos]!=-1)
    {
        pos += 1;
        if(pos==M) pos = 0;
    }

    table[pos] = key;
}
void LinearProbingHash::searchKey(int key)
{
    int hk = hashKey(key);
    while(table[hk]!=-1)
    {
        if(table[hk]==key)
        {
            cout << "True." << endl;
            return ;
        }
        hk++;
        if(hk==M) hk = 0;
    }
    cout << "False." << endl;
}
void LinearProbingHash::search_noOutput(int key)
{
    int hk = hashKey(key);
    while(table[hk]!=-1)
    {
        if(table[hk]==key) return ;
        hk++;
        if(hk==M) hk = 0;
    }
}
void LinearProbingHash::deleteKey(int key)
{
    int hk = hashKey(key);
    int pos = hk;
    while(table[pos]!=-1)
    {
        if(table[pos]==key)
        {
            table[pos]=-1;
            break;
        }
        pos++;
    }
    int save = pos;

    pos++;
    if(pos==M) pos = 0;
    while(pos!=hk)
    {
        if(hashKey(table[pos])==hk)
        {
            table[save] = table[pos];
            table[pos] = -1;
            save = pos;
        }
        pos++;
        if(pos==M) pos = 0;
    }
}
int LinearProbingHash::hashKey(int a)
{
    return a%M;
}
int main()
{
    LinearProbingHash l1;
    cout << "insert:" << endl;
    l1.insertion(151);
    l1.insertion(302);
    l1.insertion(453);
    cout << "delete" << endl;
    l1.deleteKey(151);
    cout << "search" << endl;
    l1.searchKey(453);

    for(int i=0;i<0.3*M;i++)
    {
        l1.insertion(rand()%1500);
    }
    clock_t a = clock();
    for(int i=0;i<M*1000;i++)
    {
        int a = rand()%1500;
        l1.search_noOutput(a);
    }
    clock_t b = clock();
    cout << "0.3:\t" << b-a << endl;

    LinearProbingHash l2;
    for(int i=0;i<0.6*M;i++)
    {
        l2.insertion(rand()%1500);
    }
    a = clock();
    for(int i=0;i<M*1000;i++)
    {
        int a = rand()%1500;
        l2.search_noOutput(a);
    }
    b = clock();
    cout << "0.6:\t" << b-a << endl;


    return 0;
}
