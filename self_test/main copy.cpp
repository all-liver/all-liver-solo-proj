#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

struct path{
    int course;
    path *next;
};

class transverse{
protected:
    virtual bool interior(int i)=0;
    int breakorcont=1;
public:
    int n,sum=0;
    vector<path *> paths;
    vector<bool> visited;
    int shell()
    {
        int i;
        path *temp;
        queue<int> process_line;
        process_line.push(n);
        while (!process_line.empty())
        {
            i = process_line.front();
            process_line.pop();
            temp = paths[i];
            if (interior(i)){
                if (breakorcont){
                    continue;
                }else{
                    break;
                }
            }
            while (temp != nullptr)
            {
                i=temp->course;
                if (!visited[i]) process_line.push(i);
                temp = temp->next;
            }
        }
        return sum;
    }
};

class t_up:public transverse{
protected:
    bool interior(int i){
        visited[i]=true;
        int j=(paths[i]==nullptr || rec[i]);
        sum+=j;
        return j;
    }
    int breakorcont=0;
public:
    vector<bool>rec;
    bool upsearch(){
        if (!shell()){
            rec[n]=true;
            return true;
        }
        return false;
    }

    t_up(vector<path*>pup,int requirement){
        paths=pup;
        visited=vector<bool>(pup.size(),false);
        visited[requirement]=true;
        rec=vector<bool>(pup.size(),false);
    }
};

class t_down:public transverse{
protected:
    bool interior(int i){
        if (visited[i]) return true;
        visited[i]=true;
        upward_search.sum=0;
        upward_search.n=i;
        upward_search.visited=up_visited;
        bool j= !(upward_search.upsearch());
        return false;
    }
    int breakorcont=1;
public:
    t_up upward_search;
    vector<bool> up_visited;
    t_down(int x,vector<path*>down_path,vector<path*>up_path):upward_search(up_path,x){
        n=x;
        paths=down_path;
        visited=vector<bool>(down_path.size(),false);
        up_visited=vector<bool>(down_path.size(),false);
        up_visited[x]=true;
    }
};

int main(){
    int n, m, i, j, k;
    path *temp;
    string input;
    getline(cin, input);
    istringstream ss(input);
    ss >> n;
    ss >> m;
    vector<path *> previous(n, nullptr);
    vector<path *> next(n, nullptr);
    for (i = 0; i < m; i++)
    {
        getline(cin, input);
        istringstream ss(input);
        ss >> j;
        ss >> k;
        temp = new path{j, previous[k]};
        previous[k] = temp;
        temp = new path{k, next[j]};
        next[j] = temp;
    }
    cin >> n;
    t_down searching(n,next,previous);
    cout<<searching.shell();
}