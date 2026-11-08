#include <iostream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

struct path;

struct course
{
    bool sorted;
    int weight;
    path *parent;
};

struct path
{
    course *coe;
    path *next;
};

void mergeList(path *p1, path *p2)
{
    path *cp1 = p1, *cp2 = p2;
    while (cp2 != nullptr)
    {
        cp1->coe = cp2->coe;
        if (cp1->next = nullptr)
        {
            cp1->next = cp2->next;
            return;
        }
        cp1 = cp1->next;
        cp2 = cp2->next;
    }
    cp1->coe == nullptr;
}

void sortinsert(path *&lis, path *&ele)
{
    if (lis->coe->weight > ele->coe->weight)
    {
        ele->next = lis;
        lis = ele;
        return;
    }
    path *current = lis;
    while (current->next != nullptr)
    {
        if (current->next->coe->weight > ele->coe->weight)
        {
            ele->next = current->next;
            current->next = ele;
            break;
        }
        current = current->next;
    }
    current->next = ele;
}

void sort(course &dau)
{
    path *temp = dau.parent;
    if (temp == nullptr)
        return;
    path *current = temp->next, *temp2;
    temp->next = nullptr;
    while (current != nullptr)
    {
        temp2 = current->next;
        sortinsert(temp, current);
        current = temp2;
    }
    dau.parent = temp;
}

// searching recursive func
int search(course &dau, int w)
{
    int nw = w + dau.weight, smallest = 999999, i;
    if (dau.parent == nullptr || dau.sorted)
        return nw;
    sort(dau);
    dau.sorted = true;
    path *current = dau.parent;
    while (current != nullptr)
    {
        if (current->coe->weight > smallest)
            break;
        i = search(*(current->coe), 0);
        if (i < smallest)
        {
            smallest = i;
        }
        current = current->next;
    }
    dau.weight += smallest;
    return nw + smallest;
}

int main()
{
    int n, m, i, j, k;
    string input;
    path *pa;
    getline(cin, input);
    istringstream ss(input);
    ss >> n;
    ss >> m;
    getline(cin, input);
    istringstream ss1(input);
    course *courses = new course[n];
    for (i = 0; i < n; i++)
    {
        ss1 >> j;
        courses[i] = {false, j, nullptr};
    }
    for (i = 0; i < m; i++)
    {
        getline(cin, input);
        istringstream ss(input);
        ss >> j;
        ss >> k;
        pa = new path{&courses[j], courses[k].parent};
        courses[k].parent = pa;
    }
    cin >> n;
    m = courses[n].weight;
    cout << search(courses[n], 0) - m;
    return 0;
    /*while (record != nullptr && record->coe != nullptr)
    {
        cout << record->coe->weight << " ";
        record = record->next;
    }*/
}