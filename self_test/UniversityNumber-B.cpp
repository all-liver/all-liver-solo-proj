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
    void interior(int n);
public:
    void shell(int n, vector<path *> paths)
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
            interior(i);
            while (temp != nullptr)
            {
                process_line.push(temp->course);
                temp = temp->next;
            }
        }
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
    getline(cin, input);
    istringstream ss1(input);
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

    return 0;
}