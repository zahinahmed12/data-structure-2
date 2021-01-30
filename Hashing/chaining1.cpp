#include<bits/stdc++.h>
#include<stdio.h>
#include "listforhash1.cpp"

using namespace std;
//const int m= 1e9+9;
int ins1=0;
int ins2=0;

/*string wordGenerator(int n)
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

    string word;
    int val;
   /* hashNode(string s, int v)
    {
        word=s;
        val=v;
    }
};*/

class hashTable
{
public:
    int tablesize;
    int No_of_collision=0;
    float Avg_hits=0.0;
    //vector <hashNode> *table;
    LinkedList * a1;

    //string User;
    //string *sa;
    //sa =new string[1000];
    string sa[1000];
    int element=0;

    hashTable(int n)
    {
        tablesize=n;
        a1= new LinkedList[tablesize];
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

    long long hashFunction2(string str, int len)
    {
        long long x=0;
        for(int i=0;i<str.size();i++)
        {
            x=29*x+(int)str[i];
        }
        return x;
    }

    void insertkey2(string str)
    {
        long long int a =hashFunction2(str,7);
        int index= a% tablesize;
       // if(a1[index].getLength()>0) No_of_collision++;

        ListNode *l=a1[index].searchItem(str);
        if(l==NULL)
        {
            if(a1[index].getLength()>0) No_of_collision++;
            ins2++;
            a1[index].insertItem(str,ins2);

            if(element<1000) sa[element]=str;
            element++;
        }

        //table[index].push_back(node);
    }

    void insertkey1(string str)
    {
        long long int a =hashFunction1(str,7);
        int index= a% tablesize;
       // if(a1[index].getLength()>0) No_of_collision++;

        ListNode *l=a1[index].searchItem(str);
        if(l==NULL)
        {
            if(a1[index].getLength()>0) No_of_collision++;
            ins1++;
            a1[index].insertItem(str,ins1);

            if(element<1000) sa[element]=str;
            element++;
        }

        //table[index].push_back(node);
    }

    void deleteKey(string str)
    {
        long long int a=hashFunction1(str, 7);
        int index=a% tablesize;

        ListNode *l=a1[index].searchItem(str);
        if(l!=NULL)
        {
            int ss=l->item;
            int v=a1[index].deleteItem(ss);
        }

    }

    int searchKey1(string str)
    {
        long long int a=hashFunction1(str, 7);
        int index=a% tablesize;

        ListNode *l=a1[index].searchItem(str);
        if(l!=NULL)
        {
            if(a1[index].getLength()>0) Avg_hits=Avg_hits+a1[index].getLength();
            int ss=l->item;
            return ss;
        }
        else return 0;
    }

    int searchKey2(string str)
    {
        long long int a=hashFunction2(str, 7);
        int index=a% tablesize;

        ListNode *l=a1[index].searchItem(str);
        if(l!=NULL)
        {
            if(a1[index].getLength()>0) Avg_hits=Avg_hits+a1[index].getLength();
            int ss=l->item;
            return ss;
        }
        else return 0;
    }

    void print()
    {
        for(int i=0;i<tablesize;i++)
        {
            a1[i].printList();
        }

    }

    /*float getAvgHit()
    {
        return Avg_hits/1000;
    }*/
    void gethit1()
    {
        for(int i=0;i<1000;i++)
        {
            searchKey1(sa[i]);
        }
        Avg_hits=Avg_hits/1000;

    }
    void gethit2()
    {
        for(int i=0;i<1000;i++)
        {
            searchKey2(sa[i]);
        }
        Avg_hits=Avg_hits/1000;
    }

};

/*int main()
{
    int b;
    scanf("%d",&b);
    hashTable H1(b);
    hashTable H2(b);

    //H.insertkey("zaheeen");
    for(int i=1;i<=b;i++)
    {
        string s= wordGenerator(7);
        H1.insertkey1(s);
        H2.insertkey2(s);
    }
    //H.insertkey("zaheeen");
    //H1.print();
    //H2.print();
    //int x=H.searchKey("zaheeen");
    //printf("The value of the string searched: %d \n",x);
    //H.deleteKey("zaheeen");


    //H.print();
    printf("Chaining method:\n\n");
    printf("Hash 1\t\t\t");
    printf("Hash 2\n\n");
    printf("No Of Coll: %d\t", H1.No_of_collision);
    printf("No Of Coll: %d\n\n", H2.No_of_collision);
    //printf("Avg Hits: %f\t", H1.getAvgHit());
    //printf("Avg Hits: %f\n\n", H2.getAvgHit());
    //H.print();

}*/

