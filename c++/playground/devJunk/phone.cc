#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

struct Entry {
    string name;
    int number;
};


void pr(int n, vector<Entry*> &v)
{
    try {
        for (int i=0; i<n; ++i)
            cout << v.at(i)->name << endl;
    }
    catch (...) {
        cerr << "range error\n" << endl;
    }

}

// Just playing around. Not really necessary.
template <typename T>
void pr2(int n, vector<T> &v)
{
    try {
        for (int i=0; i<n; ++i)
            cout << v.at(i)->name << endl;
    }
    catch (...) {
        cerr << "range error\n" << endl;
    }

}






int main(void)
{

    vector<Entry*> phone_book;

    Entry *t;

    t=new Entry();
    t->name="bob";
    t->number=34523;

    phone_book.push_back(t);
    pr(5,phone_book);

    pr2<Entry*>(5,phone_book);

    delete t;



}
