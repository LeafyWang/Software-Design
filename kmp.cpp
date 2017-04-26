//Leafy 2017/3/14
//I hate KMP
#include<iostream>
#include<string>
#include<time.h>
using namespace std;

class KMP
{
    string pattern;
    int kmpNext[50];
    int cnt;
public:
    void setArray(string p);
    void attemp(string text,int i);
    void showNext();
};
void KMP::setArray(string p)
{
    pattern = p+"#";
    cnt = pattern.size();
    int j = 0;
    int k = -1;
    kmpNext[0] = -1;
    while (j < cnt -1 )
    {
        if (k == -1 || pattern[j] == pattern[k])
        {
            if (pattern[j + 1] == pattern[k + 1])
            {
                kmpNext[++j] = kmpNext[++k];
            }
            else
            {
                kmpNext[++j] = ++k;
            }
        }
        else
        {
            k = kmpNext[k];
        }
    }
}
void KMP::showNext()
{
    cout << "kmpNext:" << endl;
    for(int i=0;i<cnt-1;i++)
    {
        cout << pattern[i] << "\t" ;
    }
    cout << endl;
    for(int i=0;i<cnt;i++)
    {
        cout << kmpNext[i] << "\t" ;
    }
}
void KMP::attemp(string text,int i)
{
    //cout << endl;
    int pos = 0;
    int shift;
    while( i + pos <= text.size() )
    {
        if(pattern[pos] == text[i+pos])
        {
            if(pos==cnt-2)
            {
                cout << i << " - " << pos+i << " success." << endl;
            }
            pos++;
        }
        else
        {
            shift = pos - kmpNext[pos];
            i = i + shift;
            pos = 0;
        }
    }
}
void naive(string a,string text)
{
    int i = 0, k = 0;
    while(k<text.size()-a.size())
    {
        if(text[i+k]==a[i])
        {
            if(i==a.size()-1)
            {
                //cout << k << "-" << k+i << endl;
                i = 0;
                k++  ;
            }
            i++;
        }
        else
        {
            k = k + 1;
            i = 0;
        }
    }
}
int main()
{
    clock_t a,b,c;
    KMP kmp;
    string input;
    cout <<"INPUT THE PATTERN(input 1 to use default pattern and text):" << endl;
    cin  >>input;
    string aaa = "GCATCGCAGAGAGTATACAGTACG";
    //string aaa= "
    if( input == "1" )
    {
        kmp.setArray("GCAGAGAG");
        kmp.showNext();
        cout << endl << "THE TEXT IS:" << aaa;
        //a = clock();
        //for(int x=0;x<100000;x++)
        cout << "KMP: " << endl;
        kmp.attemp(aaa,0);
        //b = clock();
        //for(int x=0;x<100000;x++)
        cout << "NAIVE: " << endl;
        naive("GCAGAGAG",aaa);
        //c = clock();

        //cout << endl << (double)(b-a)/CLOCKS_PER_SEC << endl;
        //cout << endl << (double)(c-b)/CLOCKS_PER_SEC << endl;
    }
    else
    {
        kmp.setArray(input);
        kmp.showNext();
        cout <<"INPUT THE TEXT:" << endl;
        cin >> input;
        kmp.attemp(input,0);
    }

    cout << "AFTER TEST,I FOUND THAT : " << "KMP 100000 TIMES: 0.116s" << endl << "NAIVE 100000 TIMES: 0.203" << endl;
    cout << "IT IS OBVIOUS THAT KMP IS FATER." << endl;


    return 0;
}
