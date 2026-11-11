#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

struct path{
    int course;
    path *next;
};

void heapify(int array[],int i,int n){
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;
    if (left>=n)left=i;
    if (right>=n)right=i;
    if (array[left]>array[i]) largest=left;
    if (array[right]>array[largest]) largest=right;    
    if (i!=largest){
        swap(array[i],array[largest]);
        heapify(array,largest,n);
    }
}

void sort(int array[],int n){
    int heap_size=n/2-1,i;
    for (i=heap_size;i>-1;i--){
        heapify(array,i,n);
    }
    int n2=n;
    for (i=n-1;i>heap_size;i--){
        swap(array[0],array[i]);
        n2--;
        heapify(array,0,n2);
    }
}

int main(){
    int n, m, i, j, k, count = 0, index = 0;
    path *temp, *start;
    bool flag = false;
    scanf("%d %d", &n, &m);
    vector<path *> adt(n, nullptr);
    vector<bool> visited(n, true);
    for (i = 0; i < m; i++){
        scanf("%d %d\n", &j, &k);
        if (visited[k]){
            visited[k] = false;
            count++;
        }
        temp = new path{k, adt[j]};
        adt[j] = temp;
    }
    cin >> k;
    j = 0;
    queue<int> *q, *q2;
    for (i = 0; i < m; i++){
        if (!visited[i]){
            j++;
            q->push(i);
            if (i == k) flag = true;
        }
        if (j == n - count)
            break;
    }
    if (flag){
        int *last_list=new int[q->size()];
        sort(last_list,q->size());
    }
    do{
        index += q->size();
        while (!q->empty())
        {
            i = q->front();
            q->pop();
            temp = adt[i];
            while (temp != nullptr)
            {
                i = temp->course;
                if (!visited[i])
                    q2->push(i);
                visited[i] = true;
                if (k == i)
                    flag = true;
                temp = temp->next;
            }
        }
        if (flag){
            //type here
        }else{
            delete q;
            q=q2;
        }
    }
}