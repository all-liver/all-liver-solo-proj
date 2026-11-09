#include <iostream>
#include <string>
#include <sstream>
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

void sort(int i,vector<stack<int>> matrix,int weight[],vector<path*>&storage){
    path*start=nullptr;
    while (matrix[i].size()){
        sortinsert(start,matrix[i].top(),weight);
        matrix[i].pop();
    }
    storage[i]=start;
}

int search(int i,vector<stack<int>> &matrix,int minvalue[],int weight[],vector<path*>&sorts,int acc){
    if (matrix[i].empty()) return acc+weight[i];
    if (sorts[i]!=nullptr) return minvalue[i];
    sort(i,matrix,weight,sorts);
    path*current=sorts[i];
    int minimum=99999999;
    while (current!=nullptr){
        if (weight[current->parent]>minimum) break;
        int j=search(current->parent,matrix,minvalue,weight,sorts,0);
        if (j<minimum) minimum=j;
        current=current->next;
    }
    minvalue[i]=weight[i]+minimum;
    return acc+weight[i]+minimum;
}

int main(){
    int n, m, i, j, k;
    string input;
    getline(cin, input);
    istringstream ss(input);
    ss >> n;
    ss >> m;
    vector<stack<int>>adj(n);
    vector<path*>sorts(n,nullptr);
    int *weight=new int[n],*minvalue=new int[n]{0};
    getline(cin, input);
    istringstream ss1(input);
    for (i = 0; i < n; i++)
    {
        ss1 >> weight[i];
    }
    for (i = 0; i < m; i++)
    {
        getline(cin, input);
        istringstream ss(input);
        ss >> j;
        ss >> k;
        adj[k].push(j);
    }
    cin >> n;
    cout<<search(n,adj,minvalue,weight,sorts,0)-weight[n];
}