#include<iostream>
#include<set>
#include<math.h>
#include<time.h>
using namespace std;

int com = 0;

set<int> visit;

struct edges
{
    int weight;

    int a;
    int b;
};

edges* next[50];
int setn[50];
//set<int> sets[50];

int cnt = 0;
int cnte = 0;

void sort_w()
{
    for(int i=0;i<cnte-1;i++)
    {
        for(int j=i+1;j<cnte;j++)
        {
            if(next[i]->weight > next[j]->weight)
            {
                edges* temp = next[i];
                next[i] = next[j];
                next[j] = temp;
            }
        }
    }
    com += cnte * log(cnte);
}

void Kruskal()
{
    sort_w();

    time_t a = time(NULL);

        for(int pos=0;pos<cnte;pos++)
        {
            com += 1;
            int a = next[pos]->a;
            int b = next[pos]->b;
            if(setn[a]==setn[b])
                continue;
            else //setn[a]!=setn[b]
            {
                //cout << a << " " << b << " weight:" << next[pos]->weight << endl;
                int seta = setn[a];
                int setb = setn[b];
                for(int i=1;i<=cnt;i++)
                {
                    if(setn[i]==setb)
                        setn[i]=seta;
                }
                com += 1;
            }

        }

    int setx = setn[1];
    for(int i=1;i<cnt;i++)
    {
        if(setn[i]!=setx)
        {
            cout << "not a connected graph." << endl;
            break;
        }
    }
}

int main()
{
    cout << "Input the number of nodes:" ;
    cin >> cnt;
    for(int i=1;i<=cnt;i++)
    {
        setn[i] = i;
        //sets[i].clear();
        //sets[i].insert(i);
    }

    for(int i=0;i<50;i++)
    {
        next[i] = new edges;
    }

    cout << "Input edges:" << endl;

    while(true)
    {
        int a;
        int b;
        int w;
        cin >> a;
        cin >> b;
        cin >> w;

        if(a == -1)
        {
            break;
        }
        next[cnte]->a = a;
        next[cnte]->b = b;
        next[cnte]->weight = w;

        cnte++;
    }

    time_t a = time(NULL);
    for(int k=0;k<100000;k++)
    {
    Kruskal();
    }
    time_t b = time(NULL);

    cout <<b-a;
    return 0;
}
