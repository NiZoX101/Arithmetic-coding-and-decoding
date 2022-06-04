#include <iostream>
#include <map>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

struct Node
{
    char key; float p;
};

bool Compare(Node* a, Node* b)
{
    return a->p > b->p;
}


int main()
{
    cout << fixed;
    cout.precision(16);
    int i;
    float alf[256]; char x;
    float low = 0, high = 0, num = 0;
    list<Node*> l;
    list<Node*>::iterator j;
    map<char, float[2]> mapa;
    map<char, float[2]>::iterator it;
    for (i = 0; i < 256; i++) alf[i] = 0;
    ifstream a("D:/text.txt"); ofstream aa("D:/chst.txt");

    a.get(x);
    while (a) {
        alf[(int)x]++; a.get(x); num++;
    }
    for (i = 0; i < 256; i++) {
        if (alf[i] != 0)
        {
            Node* r = new Node; r->key = (char)i; r->p = alf[i] / num;
            aa << ' '; aa << r->key; aa << alf[i];
            /*cout << (char)i << '-' << aski[i] / num<< endl;*/
            l.push_back(r);
        }
    }
    l.sort(Compare);
}