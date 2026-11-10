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
    virtual int interior(int i)=0;
    virtual bool intbreak(int i)=0;
public:
    int n;
    vector<path *> paths;
    int shell()
    {
        int i,sum=0;
        path *temp;
        queue<int> process_line;
        vector<bool> visited(paths.size(),false);
        process_line.push(n);
        while (!process_line.empty())
        {
            i = process_line.front();
            visited[i]=true;
            process_line.pop();
            temp = paths[i];
            sum+=interior(i);
            if (intbreak(i)) break;
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
    int interior(int i){
        return (paths[i]==nullptr);
    }
    bool intbreak(int i){
        return (paths[i]==nullptr);
    }
public:

    t_up(vector<path*>pup,int n){
        this->n=n;
        paths=pup;
    }
};

class t_down:public transverse{
protected:
    int interior(int i){
        t_up upward_search(up_path,i);
        return (upward_search.shell()<1);
    }
    bool intbreak(int i){
        return false;
    }
public:
    vector<path*>up_path;
    t_down(int x,vector<path*>down_path,vector<path*>up_path){
        n=x;
        paths=down_path;
        this->up_path=up_path;
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