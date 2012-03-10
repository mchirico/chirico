#include <cstdio>
class G {
private:
    static const int NumTurns=5;
    int scores[NumTurns];

public:

    G() {
      fprintf(stderr,"Test %d %d\n",sizeof(scores),sizeof(int));
    }

};

int main(void) {

    G *g= new G();
    delete g;


}
