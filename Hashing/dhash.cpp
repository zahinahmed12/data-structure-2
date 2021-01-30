#include<bits/stdc++.h>
#include<stdio.h>

using namespace std;
//const int m= 1e9+9;

/*string wordGenerator(int n)
{
    string s="";
    for(int i=0;i<n;i++)
    {
        char ch=(abs(rand())%26)+'a';
        s+=ch;
    }
    return s;
}*/

/*class hashNode
{
public:
    string word;
    int val;
    /*hashNode()
    {
        //word=;
        val=-1;
    }
};*/


class openAddressing
{
public:
    int tsize;
    int element;
    int ins=0;
    int ncoll=0;
    float hit=0.0;
    hashNode *arr1,*arr2;

    openAddressing(int cap)
    {
        tsize=cap;
        arr1=new hashNode[tsize];
        for(int i=0; i<tsize; i++)
        {
            arr1[i].val=-1;
        }
        //arr2=new hashNode[tsize];
        element=0;
    }

    long long hashF1(string str )
    {
        const int p=31;
        long long hashVal=0;
        long long powerOfP=1;

        for(int i=0;i<str.size();i++)
        {
            hashVal=(hashVal + (str[i]-'a'+1)* powerOfP) % m;
            powerOfP=(powerOfP * p)% m;
        }
        return hashVal;
    }

    int auxHash(string str)
    {
        int  hashV = 0;
        string s=str;

        for (int i = 0; i < s.size(); i++)
        {
            hashV ^= s[i];
        }
        //printf("%d \n",hashV);

        return hashV =hashV % tsize ;
    }

    long long hashF2(string str )
    {
        const int p=37;
        long long hashVal=0;
        long long powerOfP=1;

        for(int i=0;i<str.size();i++)
        {
            hashVal=(hashVal + (str[i]-'a'+1)* powerOfP) % m;
            powerOfP=(powerOfP * p)%m;
        }
        return hashVal;
    }

    void insert1(string str)
    {
        if(element==tsize)
        {
            return;
        }

        int pIdx= hashF1(str) % tsize;
       // printf("ekhane3\n");

        if(arr1[pIdx].word==str)
        {
            //printf("here2\n");
            return;
        }
       // printf("ekhane4\n");
        if(arr1[pIdx].val == -1)
        {
           // printf("here lol");
            //printf("here3\n");
            ins++;
            arr1[pIdx].word=str;
            arr1[pIdx].val=ins;
        }
        else
        {
            int sIdx=hashF2(str) % tsize;
            //int sIdx=auxHash(str);
            int i=0;
           // printf("ekhane5\n");
            while(1)
            {
                //printf("ekhane6\n");
                int New = (pIdx + i*sIdx)% tsize;
                //printf("%d\n",New);
                if(arr1[New].word==str)
                {
                   // printf("here 2");
                   //printf("here4\n");
                    return;
                }
                ncoll++;
                //printf("ekhane7\n");
                if(arr1[New].val==-1)
                {
                    //printf("here lol5\n");
                    ins++;
                    arr1[New].val=ins;
                    arr1[New].word=str;
                    break;
                }
                i++;
               // printf("ekhane8\n");
            }

        }
        //printf("ekhane9\n");
        element++;
       // printf("%d\n",element);

    }
    void insert2(string str)
    {
        if(element==tsize)
        {
            return;
        }
        int pIdx= hashF1(str) % tsize;

        if(arr1[pIdx].word==str)
        {
            return;
        }
        if(arr1[pIdx].val == -1)
        {
            ins++;
            arr1[pIdx].word=str;
            arr1[pIdx].val=ins;
        }
        else
        {
            //int sIdx=hashF2(str) % tsize;
            int sIdx=auxHash(str);
            int i=0;
            while(1)
            {
                int New = (pIdx + i*sIdx)% tsize;
                if(arr1[New].word==str)
                {
                    return;
                }
                ncoll++;
                if(arr1[New].val==-1)
                {
                    ins++;
                    arr1[New].val=ins;
                    arr1[New].word=str;
                    break;
                }
                i++;
            }

        }
        element++;
    }

    int search1(string str)
    {
        int pIdx= hashF1(str) % tsize;

        if(arr1[pIdx].val == -1)
        {
            return 0;
        }
         hit=hit+1.0;
        if(arr1[pIdx].word==str)
        {
            return arr1[pIdx].val;
        }
        else
        {
            int sIdx=hashF2(str) % tsize;
            int i=0;
            while(1)
            {
                int New = (pIdx + i*sIdx)% tsize;
                hit=hit+1.0;
                if(arr1[New].word==str)
                {
                    return arr1[New].val;
                }
                if(arr1[New].val==-1)
                {
                    break;
                }
                i++;
            }
            return 0;

        }
    }
    int search2(string str)
    {
        int pIdx= hashF1(str) % tsize;

        if(arr1[pIdx].val == -1)
        {
            return 0;
        }
        hit=hit+1.0;
        if(arr1[pIdx].word==str)
        {
            //hit=hit+1.0;
            return arr1[pIdx].val;
        }
        else
        {
            //int sIdx=hashF2(str) % tsize;
            int sIdx=auxHash(str);
            int i=0;
            while(1)
            {
                int New = (pIdx + i*sIdx)% tsize;
                hit=hit+1.0;
                if(arr1[New].word==str)
                {
                    //hit=hit+1.0;
                    return arr1[New].val;
                }
                if(arr1[New].val==-1)
                {
                    break;
                }
                i++;
            }
            return 0;

        }
    }

    void delete1(string str)
    {
        int pIdx= hashF1(str) % tsize;

        if(arr1[pIdx].val == -1)
        {
            return;
        }
        if(arr1[pIdx].word==str)
        {
            arr1[pIdx].val=-1;
        }
        else
        {
            int sIdx=hashF2(str) % tsize;
            int i=0;
            while(1)
            {
                int New = (pIdx + i*sIdx)% tsize;
                if(arr1[New].word==str)
                {
                    arr1[New].val=-1;
                }
                if(arr1[New].val==-1)
                {
                    break;
                }
                i++;
            }
            //return 0;

        }
    }
    void print1()
    {
        for(int i=0;i<tsize;i++)
        {
            cout<<arr1[i].word<<" ";
            cout<<arr1[i].val<<endl;
        }
    }

    float avgHit1()
     {
         int c=0;
         for(int i=0;i<tsize;i++)
         {
             if(arr1[i].val!=-1)
             {
                 c++;
                 search1(arr1[i].word);
                 if(c==1000) break;
             }
         }
         return hit/1000;
     }
     float avgHit2()
     {
         int c=0;
         for(int i=0;i<tsize;i++)
         {
             if(arr1[i].val!=-1)
             {
                 c++;
                 search2(arr1[i].word);
                 if(c==1000) break;
             }
         }
         return hit/1000;
     }

};

/*int main()
{
    int b;
    scanf("%d",&b);
    openAddressing A(2*b);
    openAddressing B(2*b);


    //printf("%d \n",A.search1("goooood"));
    for(int i=1;i<=b;i++)
    {
        string s= wordGenerator(7);
        A.insert1(s);
        B.insert2(s);
    }
    //A.insert1("ancient");
    /*A.insert1("pleasee");
    A.insert1("blueeee");
   // A.insert1("zaheeen");
    printf("%d \n",A.search1("blueeee"));
    A.delete1("germany");
    A.delete1("blueeee");
    printf("%d \n",A.search1("blueeee"));

    //printf("\n%d \n",A.ncoll);
    //A.print1();
    printf("Double Hashing:\n\n");
    printf("Hash 1\t\t\t");
    printf("Hash 2\n\n");
    printf("No Of Coll: %d\t", A.ncoll);
    printf("No Of Coll: %d\n\n", B.ncoll);
    //printf("Avg Hits: %f\t", H1.getAvgHit());
    //printf("Avg Hits: %f\n\n", H2.getAvgHit());
}*/
