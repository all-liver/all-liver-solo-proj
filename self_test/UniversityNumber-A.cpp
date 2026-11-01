#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

struct course{
    int weight;
    list <course*> parent;
    private:

};

course* minpar (course dau){
    list <course*> storage;
    int i=dau.parent.size();
    for (int j=0;j<i;j++){

    }
}

list<course*> sort (list<course*>inputs,course ele){
    if (ele.weight>inputs.front()->weight){
        inputs.push_back(&ele);
        return inputs;
    }
}

int traverse(course dau){
    if (dau.parent.size()==0) return dau.weight;
    int i=dau.parent.size(),min=99999;
    for (int j=0;j<i;j++){
        if (min<adfd.weight) break;
        min=((min>traverse(kjsd))?traverse():min);
    }
    return min;
}

course* minpar(course dau,int order){
    if (dau.parent.size()==1) return dau.parent.front();
    course** temp=new course*[n]
    for (course*p:dau.parent){

    }
    
}

int main(){
    int n,m,i,j,k;
    string input;
    course temp;
    cin>>n;
    cin>>m;
    getline(cin,input);
    istringstream ss(input);
    course* courses=new course[n];
    for (i=0;i<n;i++){
        ss>>j;
        courses[i].weight=j;
    }
    for (i=0;i<m;i++){
        getline(cin,input);
        istringstream ss(input);
        ss>>j;
        ss>>k;
        courses[k].parent=&courses[j];
    }
}