#include<iostream>
#include<algorithm>

using namespace std;

class Graph
{
public:
    int cnt ;
    int c[20][20];

    Graph()
    {
        cout << "有向图输入1，无向图输入0：";
        int type;
        cin >> type;
        cout << "Input the number of nodes(<10):" ;
        cin >> cnt;

        for(int i=0;i<20;i++)
        {
            for(int j=0;j<20;j++)
                c[i][j] = 999;
        }

        cout << "Input the edges(-1 -1 -1 to exit):" << endl;
        while(1)
        {
            int x,y,z;
            cin >> x;
            cin >> y;
            cin >> z;

            if(x==-1)
            {
                break;
            }
            if(type==1)
            {
                c[x][y] = z;
            }
            else
            {
                c[x][y] = z;
                c[y][x] = z;
            }

        }
    }
    void Floyd();

};
void Graph::Floyd()
{
    int A[20][20];

    for(int i=1;i<=cnt;i++)
    {
        for(int j=1;j<cnt+1;j++)
        {
            A[i][j] = c[i][j];
        }
    }
    for(int i=1;i<=cnt;i++)
    {
        A[i][i]=0;
    }
    for(int k=1;k<=cnt;k++)
    {
        for(int i=1;i<=cnt;i++)
        {
            for(int j=1;j<cnt+1;j++)
            {
                A[i][j] = min(A[i][k]+A[k][j],A[i][j]);
            }
        }
    }

    for(int k=1;k<=cnt;k++)
    {
        for(int i=1;i<=cnt;i++)
        {
            for(int j=1;j<cnt+1;j++)
            {
                if(A[i][k]+A[k][j] < A[i][j])
                {
                    cout  << "存在负环路。" << endl;
                    return ;
                }
            }
        }
    }

    for(int i=1;i<=cnt;i++)
    {
        for(int j=1;j<cnt+1;j++)
        {
            if(A[i][j]>900)
            {
                cout << "∞" << "\t";
            }
            else{
                cout << A[i][j] << "\t";
            }

        }
        cout << endl;
    }
}
int main()
{
    Graph g;
    g.Floyd();
    return 0;
}
