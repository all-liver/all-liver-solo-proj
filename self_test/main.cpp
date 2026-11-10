#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct path{
    int course;
    path *next;
};

struct searcher{
    //records is for recording all the values that can be reached without n.
    //If it cannot be reached without n, its dauhter courses may be reached from another path
    int n,c;
    path*current;
    vector<bool>records;
    vector<path*>up;
    vector<path *> down;
    vector<bool>upvisited;
    stack<int>devlog;

    bool recording(int c){
        records[c]=true;
        return false;
    }

    bool searchup(int j){
        if (current==nullptr) return recording(j);
        while (current!=nullptr){
            c=current->course;
            current=current->next;
            if (records[c]) return recording(c);
            if (j==n||upvisited[c]) continue;
            upvisited[c]=true;
            if (!searchup(c)){
                return recording(c);
            }
        }
        return true;
    }

    int searchdown(){
        int length = up.size(), i, sum = 0;
        path *current;
        queue<int> process_line;
        vector<bool> visited(length, false);
        process_line.push(n);
        while (!process_line.empty())
        {
            i = process_line.front();
            process_line.pop();
            if (visited[i]) continue;
            if (i!=n){
            if (searchup(i)){
                sum++;
                //devlog.push(i);
            }}
            visited[i]=true;
            // whatever here
            current = down[i];
            while (current != nullptr)
            {
                if (!visited[current->course])
                    process_line.push(current->course);
                current = current->next;
            }
        }
        return sum;
    }

    searcher(int n,vector<path*>up,vector<path *> down){
        this->n=n;
        this->up=up;
        this->down=down;
        this->records=vector<bool>(up.size(),false);
        vector<bool>upvisited(up.size(),false);
        this->upvisited=upvisited;
        this->upvisited[n]=true;
    }
};

int
main(){
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
    searcher searching(n,previous,next);
    i= searching.searchdown();
    cout<<i<<endl;
/*    cout<<searching.records.size()<<endl;
    cout<<searching.upvisited.size()<<endl;
    for (int a=0;a<i;a++){
        cout<<searching.devlog.top()<<endl;
        searching.devlog.pop();
    }
    int b=0,c=0;
    for (int a=0;a<searching.upvisited.size();a++){
        if (searching.records[a]) b++;
        if (searching.upvisited[a])c++;
    }
    cout<<b<<endl;
    cout<<c<<endl;*/
}