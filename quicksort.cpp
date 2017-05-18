#include<iostream>
#include<random>
#include<time.h>
#include<algorithm>

using namespace std;

class QuickSort
{
public:
    QuickSort()
    {
        cnt = 0;
    }
    void insertion(int in)
    {
        arr[cnt] = in;
        cnt++;
    }
    void qsort();
    void qsortNoOUT();
private:
    int arr[100000];
    int cnt;
    void swapXY(int a,int b);
    int pickPivot(int bg, int ed);
    void qsort(int bg,int ed);
};
void QuickSort::qsort()
{
    cout <<"\nstart sorting..." << endl;
    qsort(0,cnt-1);

    cout << "RESULT:";
    for(int i=0;i<cnt;i++)
    {
        cout << arr[i] <<" " ;
    }
    cout << endl;
}
void QuickSort::qsortNoOUT()
{
    qsort(0,cnt-1);
}
void QuickSort::swapXY(int a,int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}
int QuickSort::pickPivot(int bg,int ed)
{
    //return arr[(bg+ed)/2];

    //return arr[bg];
    int a = arr[bg];
    int b = arr[ed];
    int c = arr[(bg+ed)/2];
    int s[3];
    if(a>b)
    {
        s[0]=b;s[1]=a;
    }
    else
    {
        s[0]=a;s[1]=b;
    }
    if(c>s[1]) return s[1];
    else if(c>s[0]) return s[0];
    else return c;
}
void QuickSort::qsort(int bg,int ed)
{
    if(ed<=bg) return ;

    if (ed - bg < 10)
		{
			for (int i = bg+1 ; i <= ed; i++)
			{
				if (arr[i - 1] > arr[i])
				{
					int temp = arr[i];
					int j = i;
					while (j > bg && arr[j - 1] > temp)
					{
						arr[j] = arr[j - 1];
						j--;
					}
					arr[j] = temp;
				}
			}
		}

    int pivot = arr[(bg+ed)/2];

    int x = bg;
    int y = ed;

    while(true)
    {
        while(arr[x]<pivot)
        {
            x+=1;
            if(x==ed) break;
        }
        while(arr[y]>=pivot)
        {
            y-=1;
            if(y==bg) break;
        }

        if(x>=y) break;

        swapXY(x,y);
        x++; y--;
    }

    qsort(bg,y);

    qsort(y+1,ed);
    return;
}

int main()
{
    QuickSort q;
    for(int i = 0;i<100;i++)
    {
        q.insertion(rand()%200);
    }
    q.qsort();

    QuickSort q1;
    QuickSort q2;
    QuickSort q3;

    int sizen = 70000;
    for(int i = 0;i<sizen;i++)
    {   q1.insertion(rand()%sizen);
        q2.insertion(i);
        q3.insertion(sizen - i);
    }
    clock_t a ;
    clock_t b ;

    a = clock();
    q1.qsortNoOUT();
    b = clock();
    cout << "1:" << b-a << endl;

    a = clock();
    q2.qsortNoOUT();
    b = clock();
    cout << "2:" << b-a << endl;

    a = clock();
    q3.qsortNoOUT();
    b = clock();
    cout << "3:" << b-a << endl;

}
