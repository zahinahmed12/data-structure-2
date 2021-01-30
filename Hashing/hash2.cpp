#include<bits/stdc++.h>
#include<stdio.h>

using namespace std;
const int m= 1e9+9;

string wordGenerator(int n)
{
    string s="";
    for(int i=0;i<n;i++)
    {
        char ch=(abs(rand())%26)+'a';
        s+=ch;
    }
    return s;
}

class hashNode
{
public:
    //char *word;
    string word;
    int val;
    hashNode(string s, int v)
    {
        word=s;
        val=v;
    }
};

class hashTable
{
public:
    int tablesize;
    int No_of_collision=0;
    int Avg_hits=0;
    vector <hashNode> *table;

    hashTable(int n)
    {
        tablesize=n;
        table= new vector<hashNode>[tablesize];
    }

    long long hashFunction1(string str, int len)
    {
        const int p=31;
        long long hashVal=0;
        long long powerOfP=1;

        for(int i=0;i<len;i++)
        {
            hashVal=(hashVal + (str[i]-'a'+1)* powerOfP) % m;
            powerOfP=(powerOfP * p)%m;
        }
        return hashVal;
    }

    void insertkey(string str, int v)
    {
        long long int a =hashFunction1(str,7);
        int index= a% tablesize;
        if(table[index].size()>0) No_of_collision++;
        hashNode node(str, v);
        vector <hashNode> ::iterator i;

        for(i=table[index].begin(); i!= table[index].end();i++)
        {
            if(i->word==str)
            {
                return;
            }
        }
        table[index].push_back(node);
    }

    void deleteKey(string str)
    {
        vector <hashNode> :: iterator i;
        long long int a=hashFunction1(str, 7);
        int index=a% tablesize;
        for(i =table[index].begin();i!=table[index].end();i++)
        {
            if(i->word==str)
            {
                break;
            }
        }
        if(i!=table[index].end())
        {
            table[index].erase(i);
        }

    }

    int searchKey(string str)
    {
        vector <hashNode> :: iterator i;
        long long int a=hashFunction1(str, 7);
        int index=a% tablesize;
        for(i =table[index].begin();i!=table[index].end();i++)
        {
            if(i->word==str)
            {
                break;
            }
        }
        if(i!=table[index].end())
        {
            //printf("%s",i->word);
            int x=i->val;
            //printf("%d\n",i->val);
            return x;
        }
        else return 0;
    }

    void print()
    {
        vector<hashNode> :: iterator chain;
        for (int i = 0; i < tablesize ; i++)
        {
            for (chain =table[i].begin(); chain != table[i].end(); chain++)
            {
                //printf("In chain %d\n",i+1);
               // printf("%d \n",table[i].size());
                cout<<chain->word<<" "<<chain->val<<endl;
            }
            //printf("\n\n%d finished\n\n",i+1);

        }
    }

};

int main()
{
    int b;
    scanf("%d",&b);
    hashTable H(b);
    //string z="zaheeen";
    //H.insertkey(z,b);
    for(int i=1;i<b;i++)
    {
        string s= wordGenerator(7);
        //hashNode node(s, i);
        H.insertkey(s,i);
    }
    printf("%d", H.No_of_collision);
   // H.print();
    //printf("%d\n",H.searchKey(z));
    //H.deleteKey(z);
   // printf("%d\n",H.searchKey(z));
    //H.print();
}

