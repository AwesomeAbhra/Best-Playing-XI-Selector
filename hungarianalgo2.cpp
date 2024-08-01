#include <bits/stdc++.h>
using namespace std;


int cnt =0;

vector<int> rowtrack(100,0);
vector<int> columntrack(100,0);

struct st
{
    int roco;
    int smallestindex;
    double diff;
};
vector<st> status;

bool comparebydiff(const st &a, const st &b)
{
    return a.diff>b.diff;
}

int nonnegativecheck(vector<vector<double>>& a)
{

    double minnn=DBL_MAX;
    int rowindex, columnindex, rowindex2, columnindex2;
    int n= a.size();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            double dd=a[columntrack[i]][i];
            double dd2=a[j][i]-dd;
            if(dd2<0)
            {
                dd2+=a[columntrack[i]][rowtrack[j]];
                if(dd2<0 and dd2<minnn)
                {
                    minnn=dd2;
                    rowindex=j; columnindex=i; rowindex2=columntrack[i]; columnindex2=rowtrack[j];
                }
            }
        }
    }
    if(minnn>=0){return 1;}
    else
    {
        rowtrack[rowindex]=columnindex;
        rowtrack[rowindex2]=columnindex2;
        columntrack[columnindex]=rowindex;
        columntrack[columnindex2]=rowindex2;
        return 0;
    }


}

int assign(vector<vector<double>>& s)
{
    int n=s.size();
    if(status[0].roco>0)
    {
        for(int i=0; i<n; i++)
        {
            s[status[0].roco-1][i] = -1;
            s[i][status[0].smallestindex] = -1;
        }
        s[status[0].roco-1][status[0].smallestindex] = -2;
        rowtrack[status[0].roco-1]=status[0].smallestindex;
        columntrack[status[0].smallestindex]=status[0].roco-1;
    }
    else if(status[0].roco<0)
    {
        for(int i=0; i<n; i++)
        {
            s[status[0].smallestindex][i] = -1;
            s[i][-(status[0].roco)-1] = -1;
        }
        s[status[0].smallestindex][-(status[0].roco)-1] = -2;
        rowtrack[status[0].smallestindex]=-(status[0].roco)-1;
        columntrack[-(status[0].roco)-1]=status[0].smallestindex;
    }
    return 1;
}


void hungarianalgo(vector<vector<double>>& arr,vector<vector<double>>& s)
{   
    int n = arr.size();
    for(int i=0; i<n; i++)
    {   
        double x=DBL_MAX,y=DBL_MAX;int x1=-1;
        for(int j=0; j<n; j++)
        {
            if(s[i][j]==0 and x==DBL_MAX and y==DBL_MAX){x=arr[i][j]; x1=j;}
            if(s[i][j]==0 and y==DBL_MAX and arr[i][j]>x){y=arr[i][j];}
            if(s[i][j]==0 and arr[i][j]<x){y=x; x=arr[i][j]; x1=j;}
            if(s[i][j]==0 and arr[i][j]>x and arr[i][j]<y){y=arr[i][j];}
        }
        if(x1!=-1)
        {
            if(y==DBL_MAX){status.push_back({i+1,x1,x});}
            else{x=y-x;
            status.push_back({i+1,x1,x});}
        }
    }
    for(int i=0; i<n; i++)
    {   
        double x=DBL_MAX,y=DBL_MAX;int x1=-1;
        for(int j=0; j<n; j++)
        {
            if(s[j][i]==0 and x==DBL_MAX and y==DBL_MAX){x=arr[j][i]; x1=j;}
            if(s[j][i]==0 and y==DBL_MAX and arr[j][i]>x){y=arr[j][i];}
            if(s[j][i]==0 and arr[j][i]<x){y=x; x=arr[j][i]; x1=j;}
            if(s[j][i]==0 and arr[j][i]>x and arr[j][i]<y){y=arr[j][i];}
        }
        if(x1!=-1)
        {
            if(y==DBL_MAX){status.push_back({-(i+1),x1,x});}
            else{x=y-x;
            status.push_back({-(i+1),x1,x});}
        }
    }
    if(status.size()!=0){sort(status.begin(),status.end(),comparebydiff);}
    
}

int main()
{
    vector<vector<double>> arr = {{0,0,1,0},
                                  {0,1,1,0},
                                  {1,1,0,0},
                                  {1,0,0,0}/*{11,9,6,12,8},{5,4,3,2,20},{1,2,3,4,5},{15,14,13,18,19},{20,22,23,12,15}*/};
                                  
    int n = arr.size();
    
    vector<vector<double>> shadow;
    vector<double> shadow2(n,0);
    for(int i=0; i<n; i++){shadow.push_back(shadow2);}
    
    hungarianalgo(arr,shadow);
    
    while(cnt!=n)
    {
        int bb=assign(shadow);
        status.clear();
        cnt+=bb;
        hungarianalgo(arr,shadow);
    }
    cnt=0;
    int finale=0;
    while(finale==0)
    {
        finale=nonnegativecheck(arr);
    }


    for(int i=0; i<n; i++)
    {
        cout << i<<" "<<rowtrack[i]<<endl;
    }

    return 0;
}