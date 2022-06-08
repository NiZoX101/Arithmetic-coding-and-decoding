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

//ѕостроение вектора дл€ послед-ти символов
void Result(int& kolbyte, double ol, double oh, vector <bool>& v)
{
    double ch = 0; int size = 31;
    kolbyte = 0;
    int i = 0;
    do
    {

        if (ch + pow(2, -(32 - size)) < oh)
        {

            ch += pow(2, -(32 - size)); v.push_back(1);

        }
        else {
            v.push_back(0);
        };
        size--; i++;
        if (i == 8 || ch >= ol) { i = 0; kolbyte++; }
    } while (ch < ol);
}

void arif(std::map<char, float[2]>& m)
{
    char simb, zsimb = 0;
    ifstream inp("D:/in.txt");
    ofstream code("D:/out.txt");
    ofstream posled("D:/posl.txt");
    double high = 0, low = 0, ol = 0, oh = 0;
    int i = 0, kb;
    map<char, float[2]>::iterator it;
    vector <bool>vec;
    vector <bool>vec1;
    inp.get(simb);
    while (inp) {
        vec1.clear();
        int pos = 1;//сколько байт за раз
        kb = 0;
        it = m.find(simb);
        low = m[it->first][0];
        high = m[it->first][1];
        Result(kb, low, high, vec1);
        if (kb <= 4) { vec = vec1; inp.get(simb); }
        while (kb < 4 && inp)
        {
            vec1.clear();
            kb = 0;
            it = m.find(simb); ol = low; oh = high;
            low = ol + (oh - ol) * m[it->first][0];
            high = ol + (oh - ol) * m[it->first][1];
            Result(kb, low, high, vec1);
            if (kb <= 4) { vec = vec1; inp.get(simb); pos++; }
        }
        posled << pos << ' ';
        i = 7;
        int byte = 0;
        //кодируем и заносим 0(если получилось на байт меньше)
        for (int j = 0; j < vec.size(); j++)
        {
            zsimb |= vec[j] << i;
            i--;
            if (i < 0 || j == vec.size() - 1) { i = 7;code << zsimb; byte++; zsimb = 0; }
        }
        while (byte < 4) { zsimb = 0; code << zsimb; byte++; }
    }
    inp.close(); 
    code.close();
    posled.close();
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
    ifstream inpe("D:/in.txt"); ofstream chastot("D:/chast.txt");

    inpe.get(x);
    while (inpe) 
    {
        alf[(int)x]++; 
        inpe.get(x); 
        num++;
    }
    for (i = 0; i < 256; i++) 
    {
        if (alf[i] != 0)
        {
            Node* r = new Node; r->key = (char)i; r->p = alf[i] / num;
            chastot << ' '; 
            chastot << r->key; 
            chastot << alf[i];
            l.push_back(r);
        }
    }
    l.sort(Compare);
    //формируем отрезки дл€ символов
    for (j = l.begin(); j != l.end(); j++)
    {  
        low = high; high = low + (*j)->p;
        mapa[(*j)->key][0] = low;
        mapa[(*j)->key][1] = high;
    }
    arif(mapa);
    inpe.close(); chastot.close();
}