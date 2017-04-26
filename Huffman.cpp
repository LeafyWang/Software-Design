//by Leafy 2017/03/27 k-Huffman
#include<iostream>
#include<fstream>
#include<string>

#define text_file "d:\\me.txt"
#define code_file "d:\\to.txt"
#define decode_file "d:\\decode.txt"

#define file_code "d:\\codes.txt"

using namespace std;

struct node
{
    char a;     //字符内容
    string no;  //code编码
    int cnt;    //出现次数
    node* child[20];    //所有K个子节点(此处限定 K<20)
};

class Huffman
{
public:
    node* root;
    Huffman(int a)
    {
        k=a;
        for(int i=0;i<200;i++)
        {
            arr[i] = new node;
            arr[i]->a = i;
            arr[i]->cnt = 0;
            arr[i]->no  = "";
            for(int j=0;j<10;j++)
            {
                arr[i]->child[j]=NULL;
            }
        }
        n_count = 0;
    }

    void read();
    void node_sort();
    node* build();
    void code(node* temp);
    void display(node* temp);
    void display_full();
    void encode(string output);
    void decode(string output);
    void decode_n();
    void find_char(node* temp,char x);

    void open_codefile();

private:
    int n_count;
    int k;

    node* arr[200];
    string char_set="0123456789ABCDE";
    void swap_node(int i,int j);

    string now_no;

    ofstream save;


};
void Huffman::open_codefile()
{
    ifstream incode;
    incode.open(file_code);

    n_count = 0;
    char ch;
    while((ch=incode.get())!=EOF)
    {
        arr[n_count]->a = ch;
        string codein ;
        incode >> codein;
        arr[n_count]->no = codein;

        n_count ++ ;

        incode.get();
    }
}
void Huffman::decode_n()
{
    cout << "flag!" << endl;
    ifstream intextn;
    intextn.open(code_file);

    cout <<"flaggggggggggg" ;


        cout << arr[1]->a;


    cout << "flaggggggggggg" << endl;

    string temp = "";
    char ch ;
    while((ch=intextn.get())!=EOF)
    {
        //333cout << ch;
        temp = temp + ch;
        for(int i=0;i<n_count;i++)
        {
            if(arr[i]->no == temp)
            {
                cout << arr[i]->a;
                temp = "";
                break;
            }
        }
    }
    intextn.close();
}
void Huffman::read()
{
    ifstream text;
    text.open(text_file);
    //text.open("d:\\me.txt");

    for (char ch; (ch=text.get())!=EOF;)
    {
        cout << ch;
        int temp = ch;
        arr[temp]->cnt++;
    }
    text.close();
}
void Huffman::node_sort()
{
    for(int i=0;i<199;i++)
    {
        for(int j=i+1;j<200;j++)
        {
            if(arr[i]->cnt<arr[j]->cnt)
            {
                swap_node(i,j);
            }
        }
    }
    cout << "The result of counting:" << endl;
    for(int i=0;i<200;i++)
    {
        char temp = arr[i]->a;
        if(arr[i]->cnt!=0)
        {
            cout << temp << arr[i]->cnt;
            n_count++;
        }
    }
    cout << "Total number:" << n_count << endl;

    int d = (n_count-1)%(k-1);
    if(d!=0) n_count = n_count + (k-1-d);

    cout << "Add some NULL points." << endl << "Total is " << n_count <<endl;

    return ;
}

node* Huffman::build()
{
    int pos = n_count;
    int sum = 0;

    while(pos>1)
    {
        sum = 0;
        for(int i = pos-k;i<pos;i++)
        {
            sum = sum + arr[i]->cnt;
        }
        node* temp = arr[pos-k];
        arr[pos-k] = new node;
        arr[pos-k]->a = '~';
        arr[pos-k]->cnt = sum;
        arr[pos-k]->child[0] = temp;

        for(int i=1;i<=k-1;i++)
        {
            arr[pos-k]->child[i] = arr[pos-k+i];
        }

        //调整新点位置
        int np = pos-k;
        for(int j=pos-k-1;j>=0;j--)
        {
            if(arr[np]->cnt > arr[j]->cnt)
            {
                swap_node(np,j);
                np = j;
            }
            else
            {
                break;
            }
        }
        pos = pos - k + 1 ;
    }

    root = arr[0];
    root->no = "";

    cout << "Success build\n";
}

void Huffman::code(node* temp)
{
    if(temp->child[0]==NULL)
        return;
    for(int i=0;i<k;i++)
    {
        //char t = i+48;
        //temp->child[i]->no = temp->no + t;

        temp->child[i]->no = temp->no + char_set[i];

        code(temp->child[i]);
    }
}

void Huffman::display_full()
{
    save.open(file_code);
    display(root);

    save.close();
}
void Huffman::display(node* temp)
{
    if(temp->child[0]==NULL)
        return;

    for(int i=0;i<k;i++)
    {
        if(temp->child[i]->a!='~' && temp->child[i]->cnt!=0)
        {
            cout << temp->child[i]->a << " as " << temp->child[i]->no << endl;
            save << temp->child[i]->a << temp->child[i]->no << "\n";
        }
        display(temp->child[i]);
    }
}

void Huffman::swap_node(int i, int j)
{
    node* temp = arr[i];
    arr[i]     = arr[j];
    arr[j]     = temp;
}

void Huffman::encode(string output)
{
    ifstream text;
    text.open(text_file);
    //text.open("d:\\me.txt");

    ofstream totext;
    totext.open(code_file);
    //totext.open("d:\\to.txt");

    for (char ch; (ch=text.get())!=EOF;)
    {
        find_char(root,ch);
        //cout << "flag1" << ch << now_no;
        totext << now_no;
    }
    text.close();
    totext.close();
}

void Huffman::find_char(node* temp,char x)
{
    if(temp->child[0]==NULL)
        return;

    for(int i=0;i<k;i++)
    {
        if(temp->child[i]->a==x)
        {
            now_no = temp->child[i]->no;
            return;
        }
        find_char(temp->child[i],x);
    }
}
void Huffman::decode(string output)
{
    ifstream intext;
    intext.open(code_file);
    //("d://to.txt");

    ofstream totext;
    totext.open(decode_file);
    //("d://decode.txt");

    char b;
    node* temp = root;
    while((b = intext.get())!=EOF)
    {
        int btoi = b - 48;
        temp = temp->child[btoi];
        if(temp->child[0]==NULL)
        {
            totext << temp->a;
            //cout << temp->a << "flag2";
            temp = root;
        }
    }

    intext.close();
    totext.close();
}

int main()
{
    cout << "Input K:" ;
    int a;
    cin >> a;
    while(a<=1)
    {
        cout << "K must be larger than 1." << endl;
        cout << "Input K:" ;
        cin >> a;
    }
    Huffman huf(a);
    huf.read();
    huf.node_sort();

    huf.build();

    huf.code(huf.root);
    cout << "CODE" << endl;
    huf.display_full();

    huf.encode("d:\\to.txt");
    huf.decode("d:\\decode.txt");

    huf.open_codefile();
    huf.decode_n();

    return 0;
}
