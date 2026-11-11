#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct path{
    int parent;
    path *next;
};

void sortinsert(path *&lis, int i,int weight[])
{
    path *ele=new path{i,nullptr};
    if (lis == nullptr){
        lis=ele;
        return;
    }
    if (weight[lis->parent] > weight[i])
    {
        ele->next = lis;
        lis = ele;
        return;
    }
    path *current = lis;
    while (current->next != nullptr)
    {
        if (weight[current->next->parent]>weight[i])
        {
            ele->next = current->next;
            current->next = ele;
            break;
        }
        current = current->next;
    }
    current->next = ele;
}

void sort(int i,stack<int> record,int weight[],vector<path*>&storage){
    path*start=nullptr;
    while (record.size()){
        sortinsert(start,record.top(),weight);
        record.pop();
    }
    storage[i]=start;
}

int search(int i,stack<int> *matrix,int minvalue[],int weight[],vector<path*>&sorts,int acc){
    if (matrix->empty()) return acc+weight[i];
    if (sorts[i]!=nullptr) return minvalue[i];
    sort(i,*matrix,weight,sorts);
    path*current=sorts[i];
    int minimum=99999999,j;
    stack<int>*newstack;
    while (current!=nullptr){
        if (weight[current->parent]>minimum) break;
        newstack=matrix+(current->parent)-i;
        j=search(current->parent,newstack,minvalue,weight,sorts,0);
        if (j<minimum) minimum=j;
        current=current->next;
    }
    minvalue[i]=weight[i]+minimum;
    return acc+weight[i]+minimum;
}

int main(){
    int n, m, i, j, k;
    scanf("%d %d\n",&n,&m);
    vector<stack<int>>adj(n);
    vector<path*>sorts(n,nullptr);
    int *weight=new int[n],*minvalue=new int[n]{0};
    k=0;
    for (i = 0; i < n; i++)
    {
        while ((j=getchar())>='0' && j<='9'){
            k=k*10+j-'0';
        }
        weight[i]=k;
        k=0;
    }
    for (i = 0; i < m; i++)
    {
        scanf("%d %d",&j,&k);
        adj[k].push(j);
    }
    cin >> n;
    cout<<search(n,&adj[n],minvalue,weight,sorts,0)-weight[n];
}