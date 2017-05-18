#include<iostream>
#include<random>
#include<algorithm>

using namespace std;

class CountingSort
{
public:
    int arr[1000];
    int counting[1000];
    int cnt ;
    int maxn=0;
    CountingSort()
    {
        cnt = 0;

        for(int i=0;i<1000;i++)
        {
            arr[i] = 0;
            counting[i]= 0;
        }
    }
    void insertion(int in)
    {
        in = in%1000;
        if(maxn<in) maxn = in;

        counting[in]+=1;
        arr[cnt] = in;
        cnt++;
    }
    void sorting()
    {
        int n=0;
        for(int i=0;i<=maxn;i++)
        {
            if(counting[i]==0)continue;
            else{
                while(counting[i]!=0)
                {
                    arr[n] = i;
                    n++;
                    counting[i]-=1;
                }
            }
        }
    }
    void display()
    {
        for(int i=0;i<cnt;i++)cout << arr[i] <<" " ;
    }
};

class BucketSort
{
public:
    vector<int> buckets[10];
    int arr[1005];
    int cnt;
    BucketSort()
    {
        cnt = 0;
    }

    void insertion(int in)
    {
        arr[cnt] = in % 1000 ;
        cnt++;
    }
    void sorting()
    {

        for (int i = 0; i <cnt; i++)
        {
            int inb = arr[i] / 100;
            buckets[inb].push_back(arr[i]);
        }

        for (int i = 0; i < 10; i++)
        {
            sort(buckets[i].begin(), buckets[i].end());
        };
    }
    void display()
    {
        for (int i = 0; i < 10; i++)
        {
            for (unsigned int j = 0; j < buckets[i].size(); j++)
                cout << buckets[i][j] << " ";
        };
    }
};
class RadixSort
{
public:
    int arr[1005];
    int cnt;
    vector<int> buckets[10];

    RadixSort()
    {
        cnt = 0;
    }
    void insertion(int in)
    {
        arr[cnt] = in % 1000;
        cnt++;
    }

    void sorting()
    {
        for(int i=0;i<cnt;i++)
            buckets[arr[i]%10].push_back(arr[i]);
        int x = 0;
        for(int i=0;i<10;i++)
        {
            for (unsigned int j = 0; j < buckets[i].size(); j++)
            {
                arr[x] = buckets[i][j];
                x++;
            }
        }
        for(int i=0;i<10;i++) buckets[i].clear();

        for(int i=0;i<cnt;i++)
            buckets[arr[i]%100/10].push_back(arr[i]);
        x = 0;
        for(int i=0;i<10;i++)
        {
            for (unsigned int j = 0; j < buckets[i].size(); j++)
            {
                arr[x] = buckets[i][j];
                x++;
            }
        }
        for(int i=0;i<10;i++) buckets[i].clear();

        for(int i=0;i<cnt;i++)
            buckets[arr[i]/100].push_back(arr[i]);
        x = 0;
        for(int i=0;i<10;i++)
        {
            for (unsigned int j = 0; j < buckets[i].size(); j++)
            {
                arr[x] = buckets[i][j];
                x++;
            }
        }
    }
    void display()
    {
        for(int i=0;i<cnt;i++)cout << arr[i] <<" " ;
    }
};

int main()
{
    CountingSort c;
    BucketSort b;
    RadixSort r;
    for(int i=0;i<1000;i++)
    {
        int a = rand();
        c.insertion(a);
        b.insertion(a);
        r.insertion(a);
    }
    cout << "CountingSort:" << endl;
    c.sorting();
    c.display();

    cout << endl<< endl;
    cout << "BucketSort:" << endl;
    b.sorting();
    b.display();

    cout << endl<< endl;
    cout << "RadixSort:" << endl;
    r.sorting();
    r.display();
    return 0;
}
