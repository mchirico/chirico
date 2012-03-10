#ifndef NODE_H
#define NODE_H
class Node
{
public:
    Node(int value):data(value),nextPtr(0){}
    void setData(int value) {
        data = value;
    }
    int getData() const {
        return data;
    }
    void setNextPtr(Node *value) {
        nextPtr=value;
    }
    Node *getNextPtr() const {
        return nextPtr;
    }
private:
    int data;
    Node *nextPtr;
};
#endif
