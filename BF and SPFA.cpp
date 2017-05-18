#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;
struct edges
{
    int a;
    int b;
    int weight;
};
class Graph
{
public:
    int type;
    int cnt;
    int cnte;

    edges* e[100];

    Graph()                                                     //initialization
    {
        cout << "有向图(1)/无向图(0):" ;
        cin >> type;

        cout << "Input the number of nodes:" ;
        cin >> cnt;

        cout << "Input edges such as 1 2 -1('-1 -1 -1' to exit)" << endl;
        cnte = 0;
        while(true)
        {
            int a,b,c;
            cin >> a;
            cin >> b;
            cin >> c;

            if(a==-1)
                break;

            e[cnte] = new edges;
            if(type==1)
            {
                e[cnte]->a = a;
                e[cnte]->b = b;
                e[cnte]->weight = c;
            }
            else
            {
                e[cnte]->a = a;
                e[cnte]->b = b;
                e[cnte]->weight = c;
                e[cnte]->a = b;
                e[cnte]->b = a;
                e[cnte]->weight = c;
            }
            cnte++;
        }
    }
    void BF();
    void SPFA();
};

void Graph::BF()
{
    int s; //source
    cout <<"The source is:" ;
    cin >> s;

    int sh[100];

    for(int i=1;i<=cnt;i++)
    {
        sh[i]=9999;
    }
    sh[s] = 0;

    for(int i=1;i<cnt;i++)
    {
        for(int j=0;j<cnte;j++) //对于图中的每条边 如果起点u的距离d加上边的权值w小于终点v的距离d 则更新终点v的距离值d
        {
            int x = e[j]->a;
            int y = e[j]->b;
            if( sh[x]+e[j]->weight < sh[y] )
            {
                sh[y] = sh[x]+e[j]->weight;
            }
        }
    }

    for(int j=0;j<cnte;j++) //对于图中的每条边 如果起点u的距离d加上边的权值w小于终点v的距离d 则更新终点v的距离值d
    {
        int x = e[j]->a;
        int y = e[j]->b;
        if( sh[x]+e[j]->weight < sh[y] )
        {
            cout << "Error." << endl;
            return ;
        }
    }

    for(int i=1;i<=cnt;i++)
    {
        cout << sh[i] << "\t";
    }
}
void Graph::SPFA()
{
    int dist[100];      //the distance from source to i
    int father[100];    //the last node
    int times[100];
    bool inq[100];

    int s;
    cout << "Input the source node:" ;
    cin >> s;
    for(int i=1;i<=cnt;i++)
    {
        dist[i]   = 9999;
        father[i] = 0;
        times[i]  = 0;
        inq[i]    = false;
    }
    dist[s]   = 0;
    father[s] = s;
    times[s]++;
    inq[s] = true;

    queue<int> visit;
    visit.push(s);

    while(!visit.empty())
    {
        int x = visit.front();
        inq[x] = false;
        visit.pop();

        for(int j=0;j<cnte;j++)
        {
            if(e[j]->a==x)
            {
                int y = e[j]->b;
                if(dist[x]+e[j]->weight < dist[y])
                {
                    father[y] = x;
                    dist[y]   = dist[x]+e[j]->weight;
                    if(inq[y]==false)
                    {
                        visit.push(y);
                        inq[y] = true;
                        times[y]++;
                        if(times[y]>20)
                        {
                            cout<< "存在负环路" << endl;
                            return ;
                        }
                    }
                }
            }
        }
    }
    for(int i=1;i<=cnt;i++)
    {
        if(dist[i])
        {
            cout << dist[i] <<"\t" ;
        }
        else
        {
            cout << dist[i] << "\t" ;
        }
    }
    cout << endl;
}

int main()
{
    Graph g;
    cout << "Bellman-Ford:" <<endl;
    g.BF();
    cout << endl << "SPFA:" <<endl;
    g.SPFA();

    return 0;
}
