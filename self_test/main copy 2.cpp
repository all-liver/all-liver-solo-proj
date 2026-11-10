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
    int n;
    vector<bool>records;
    vector<path*>up;
    vector<path *> down;
    vector<bool>upvisited;

    bool merging(vector<bool>visited){
        for (int i=0;i<up.size();i++){
            records[i]=records[i]+visited[i];
        }
        records[n]=false;
        return false;
    }

    bool searchup(int j){
        int length = up.size(), i, sum = 0,c;
        bool result=true;
        path *current;
        stack<int> process_line;
        vector<bool>visited(length,false);
        process_line.push(j);
        while (!process_line.empty())
        {
            i = process_line.top();
            process_line.pop();
            visited[i] = true;
            upvisited[i] = true;
            // whatever here
            current = up[i];
            if (current == nullptr){
                return merging(visited);
            }
            while (current != nullptr)
            {
                c=current->course;
                if (!upvisited[c]){
                    process_line.push(c);
                }else if (records[c]){
                    return merging(visited);
                }
                current = current->next;
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

            if (searchup(i)){
                sum++;
            }else{
                records[i]=true;
            }
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
        records=vector<bool>(up.size(),false);
        vector<bool>upvisited(up.size(),false);
        this->upvisited=upvisited;
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
    cout<< searching.searchdown();

}