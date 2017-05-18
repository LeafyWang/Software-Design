#include<iostream>
#include<algorithm>
#include<set>
#include<time.h>

using namespace std;

struct vertex
{
    int  value;
    int  k;
    int edge_weight[51];
};

vertex* nodes[51];
int cnt;
set<int> visit;

void find_s()
{
    int no = 50;
    nodes[no]->value = 1000;
    int i;
    for(i=1;i<cnt+1;i++)
    {
        if(visit.find(i)!=visit.end())              //如果此点访问过 则跳过
        {
            continue;
        }

        nodes[i]->value = 999;
        set<int>::iterator it;                      //对未访问过的节点 寻找和已访问节点最近的点
        for(it=visit.begin();it!=visit.end();it++)
        {
            int a = *it;
            if(nodes[i]->edge_weight[a] < nodes[i]->value)
            {
                nodes[i]->k = a;
                nodes[i]->value = nodes[i]->edge_weight[a];
            }
        }
        if(nodes[i]->value < nodes[no]->value)
        {
            no = i;
        }
    }

    //cout << no << " (" << nodes[no]->k << " weight:" << nodes[no]->value << ")" << endl;

    visit.insert(no);
}

int main()
{
    for(int i=1;i<51;i++)               //initialization
    {
        nodes[i] = new vertex;
        nodes[i]->value = 999;
        for(int j=0;j<51;j++)
        {
            nodes[i]->edge_weight[j] = 999;
        }
    }

    cout << "Please input the number of nodes:" ;
    cin >> cnt;

    visit.clear();

    cout << "Input edges such as '1 2 10'(input '-1 -1 -1' to exit):" << endl;

    while(true)
    {
        int a;
        int b;
        int c;
        cin >> a;
        cin >> b;
        cin >> c;

        if(a==-1)
        {
            cout << "Begin..." << endl;
            break;
        }
        else
        {
            nodes[a]->edge_weight[b]=c;
            nodes[b]->edge_weight[a]=c;
        }
    }

    time_t a = time(NULL);
    for(int h = 0;h<100000;h++)
    {
        visit.clear();
        visit.insert(1);
        //cout << "1" << endl;
        int c = 0;
        while(visit.size()!=cnt &&c<10)
        {
            find_s();
            c++;
        }
    }
    time_t b = time(NULL);

    cout << b-a;

    return 0;
}

