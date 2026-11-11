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
    for (i=n-1;i>0;i--){
        swap(array[0],array[i]);
        n2--;
        heapify(array,0,n2);
    }
}

int search(int array[],int n,int begin, int end){
    if (end-begin==1){
        if (array[begin]==n) return begin;
        else return end;
    }
    int mid=(begin+end)/2;
    if (array[mid]==n) return mid;
    if (array[mid]<n) return search(array,n,mid,end);
    return search(array,n,begin,mid);
}

int wrap_up(queue<int>qu,int n){
    int size=qu.size();
    int *list=new int[size];
    for (int i=0;i<size;i++){
        list[i]=qu.front();
        qu.pop();
    }
    sort(list,size);
    /*for (int i=0;i<size;i++){
        cout<<list[i]<<' ';
    }
    cout<<'\n';*/
    return search(list,n,0,size-1);
}

bool lin_search_up(path*start,vector<bool>n){
    path*current=start;
    while (current!=nullptr){
        if (!n[current->course]) return false;
        //return false if some unvisited term preceeds
        current=current->next;
    }
    return true;
}

int main(){
    int n, m, i, j, k, count = 0, index = 0;
    path *temp, *start;
    bool flag = false;
    scanf("%d %d", &n, &m);
    vector<path *> adt(n, nullptr);
    vector<path*>up_path(n,nullptr);
    vector<bool> visited(n, true);
    for (i = 0; i < m; i++){
        scanf("%d %d", &j, &k);
        if (visited[k]){
            visited[k] = false;
            count++;
        }
        temp = new path{k, adt[j]};
        adt[j] = temp;
        temp=new path{j,up_path[k]};
        up_path[k]=temp;
    }
    cin >> k;
    j = 0;
    queue<int> *q=new queue<int>, *q2=new queue<int>;
    //cout<<count<<endl;
    for (i = 0; i < n; i++){
        if (visited[i]){
            j++;
            q2->push(i);
            //cout<<i<<' ';
            if (i == k) flag = true;
        }
        /*if (j == n - count)
            break;*/
    }
    cout<<endl;
    if (flag){
        cout<<wrap_up(*q2,k)+1;
        return 0;
    }
    queue<int>visited_temp;
    do{
        //cout<<q2->size()<<endl;
        index += q2->size();
        delete q;
        q=q2;
        q2=new queue<int>;
        vector<bool>visited_thisloop(n,false);
        while (!q->empty())
        {
            i = q->front();
            q->pop();
            temp = adt[i];
            while (temp != nullptr)
            {
                i = temp->course;
                if (!visited[i] && lin_search_up(up_path[i],visited) && !visited_thisloop[i]){
                    q2->push(i);
                    visited_temp.push(i);
                    //cout<<i<<' ';
                }
                visited_thisloop[i]=true;
                    //cout<<i<<' ';}
                //visited[i] = true;
                
                temp = temp->next;
            }
        }
        while (!visited_temp.empty()){
            int c=visited_temp.front();
            if (k==c) flag=true;
            visited[c]=true;
            visited_temp.pop();
        }
        cout<<endl;
    }while (!flag);
    //cout<<index<<endl;
    cout<<index+wrap_up(*q2,k)+1;
    return 0;
}


//It seems like there are a lot of ambiguity in the question. I don't really understand what a tie means.
//It also didn't mention what to do with two numbers from different branches that have no preceeding/suceeding relationship.
//In this program, I just assume a tie means there will be the same amount of edges passing through before it reached the two numbers.