#include "node.h"
int main(void)
{
  Node *newPtr = new Node(10);

  delete newPtr;

  return 0;
}
