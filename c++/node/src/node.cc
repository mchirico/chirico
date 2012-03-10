/* Copyright (C) GPL 2007  Mike Chirico <mchirico@users.sourceforge.net>

   This program implements a linked list going in two directions. I
   was using this for the connect-4 game. There are NUM_NODES of
   connectors.




*/


#include <stdio.h>
#include <list>
#include <iostream>

const int NUM_NODES =8;

class  node {
public:
    node() {}

    char name[20];
    int num;
    int x;
    int y;
    node *next[NUM_NODES];
    node *prev[NUM_NODES];
};

typedef node *nodePtr;
nodePtr start_ptr = NULL;

template<typename T>
class nodeStats {
public:
    nodeStats():number(0) {}
    void inc(){
        ++number;
    }
    void incp(T p) {
        l.push_back(p);
    }
    T p(const int i) {
        return l[i];
    }
    std::list<T> L() {
        return l;
    }
    void dec(){
        if ( number >= 1 ) --number;
    }
    int get_number() {
        return number;
    }
    std::list<nodePtr>::const_iterator begin() {
        return l.begin();
    }
    std::list<nodePtr>::const_iterator end() {
        return l.end();
    }


private:
    int number;
    std::list<T> l;

};
class nodeStats<nodePtr> ns;


//Beginning of adds

int add(nodePtr & h,nodePtr & t, const char c,int i, int x, int y);

int add2(nodePtr & t, const char c, int i = -1, int x = 0, int y = 0)
{

    // Reassign if i out of range
    // otherwise follow to the end and add.
    if (i <= -1 || i >= NUM_NODES) {
        t->name[0] = c;
        t->x = x;
        t->y = y;
        return -1;
    }

    nodePtr head = t;
    while (t->next[i] != NULL)
        t = t->next[i];
    int ret = add(t,t->next[i], c, i, x, y);
    t = head;
    return ret;
}


int add(nodePtr &h, nodePtr & t, const char c = '\0', int i = 0, int x = 0, int y = 0)
{
    // Add new node
    if (t == NULL) {
        t = new node;
        ns.inc();
        ns.incp(t);
        t->name[0] = c;
        t->x = x;
        t->y = y;
        t->prev[i]=h;
        // NULL out everything
        for (int j = 0; j < NUM_NODES; ++j)
            t->next[j] = NULL;
        for (int j = 0; j < NUM_NODES; ++j)
            if ( i != j )
                t->prev[j] = NULL;

        return 1;
    }

    return add2(t, c, i, x, y);
}

int pr(nodePtr & t)
{
    if (t == NULL)
        return 0;

    fprintf(stderr, "(%c (%d,%d)", t->name[0],t->x,t->y);
    for (int j = 0; j < NUM_NODES; ++j) {
        if (t->next[j] != NULL) {
            nodePtr & n = t->next[j];
            fprintf(stderr, ",%c-%d",n->name[0], j);
        }
    }
    fprintf(stderr, ")");
    return 1;
}

void prn(nodePtr & t)
{
    pr(t);
    for (int j = 0; j < NUM_NODES; ++j) {
        if (t->next[j] != NULL) {
            fprintf(stderr,"\n\t");
            pr(t->next[j]);
        }
    }
}


void walk(nodePtr & t)
{
    prn(t);
    fprintf(stderr,"\n\n");
    for (int j = 0; j < NUM_NODES; ++j) {
        if (t->next[j] != NULL) {
            walk(t->next[j]);
        }
    }
}



int main(void)
{
    nodePtr t = NULL;
    nodePtr p = NULL;
    add(t,t,'A',0,0,0);
    nodePtr h = t;
    add(t,t,'B',0,0,0);
    add(t,t,'C',1,0,0);
    add(t,t,'D',2,0,0);
    add(t,t,'E',3,0,0);
    add(t,t,'F',4,0,0);
    add(t,t,'G',5,0,0);
    add(t,t,'H',6,0,0);
    add(t,t,'I',7,0,0);
    add(t,t,'a',0,0,0);
    add(t,t,'b',0,0,0);

    t=t->next[2];
    add(t,t,'x',0,0,0);
    add(t,t,'y',0,0,0);
    add(t,t,'z',0,0,0);
    add(t,t,'Y',1,0,0);


    p=h;
    walk(h);

    //This lists all the nodes
    std::cout << "Size is " << ns.L().size() << std::endl;
    for (std::list<nodePtr>::const_iterator  iter = ns.begin(); iter != ns.end(); ++iter ) {
        std::cout << (*iter)->name[0] << std::endl;
    }


    return 0;
}
