#include<iostream>
#include<cstdlib>
using namespace std;

class pqueue{
public:
    int heap[50];
    int cnt = 0;
public:
    pqueue()
    {
        for(int i=0;i<50;i++)
        {
            heap[i]=-1;
        }
    }
    void insertion(int p);
    void pop_max();
    void display(int pos);
    void exchange(int a,int b);
    void heapify(int pos);
    void build();
    ~pqueue()
    {
        for(int i=0;i<50;i++)
        {
            heap[i]=-1;
        }
        cnt = 0;
    }

};
void pqueue::exchange(int a,int b)
{
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}
void pqueue::build()
{
    for(int i=(cnt+1)/2;i>=0;i--)
    {
        heapify(i);
    }
}
void pqueue::heapify(int pos)
{
    int l = pos*2+1;
    int r = pos*2+2;

    int largest = pos;
    if (l<cnt && heap[l]>heap[pos])
    {
        largest = l;
    }
    if (r<cnt && heap[r]>heap[largest])
    {
        largest = r;
    }
    if(largest != pos)
    {
        exchange(largest,pos);
        heapify(largest);
    }
}
void pqueue::pop_max()
{
    if(cnt>1)
    {
        cout << endl << "THE NODE WITH THE HIGHEST PRIORITY IS " << heap[0]<< " ";
        heap[0]= heap[cnt-1];
        heap[cnt-1] = -1;
        cnt = cnt-1;
        heapify(0);
    }
    else if(cnt==1)
    {
        heap[0] = -1;
        cnt = 0;
    }
    else cout << "THE PRIORITY QUEUE IS EMPTY NOW.";
    return;
}
void pqueue::display(int pos) //mid-
{
    if(heap[pos]!=-1)
    {
        display(pos*2+1);
        cout << heap[pos]<< " ";
        display(pos*2+2);
        return;
    }
    else
        return;
}
void pqueue::insertion(int p)
{
    heap[cnt] = p;
    cnt++;
    int parent = (cnt-2)/2;
    bool flag = true;
    while(parent>=0)
    {
        heapify(parent);
        if(parent==0)
            break;
        parent = (parent-1)/2;
    }
}
int main()
{
    pqueue prq;

    for(int i=0;i<10;i++)
    {
        prq.heap[i] = rand()%99+1;
    }
    prq.cnt = 10;

    prq.build();
    cout<< "随机插入十个数，中序遍历的结果是：" <<endl;
    prq.display(0);

    prq.pop_max();
    prq.pop_max();
    prq.pop_max();
    cout<< endl << "中序遍历的结果是：" <<endl;
    prq.display(0);

    for(int i =0;i<5;i++)
    {
        prq.insertion(rand()%99+1);
    }
    cout<< endl << "随机插入五个数，中序遍历的结果是：" <<endl;
    prq.display(0);

    while(prq.cnt>0)
    {
        prq.pop_max();
    }

    return 0;
}

