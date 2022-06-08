#include <iostream>
#include <map>
#include <fstream>
#include <list>
#include <vector>
#include <locale.h>

using namespace std;

struct Node
{
	char key; float p;
};

bool Compare(Node* a, Node* b)
{
	return a->p > b->p;
}

void zaplist(list<Node*>& l, float& weight1)
{
	char s, pr; float ch;
	ifstream chast("D:/chast.txt");

	chast.seekg(0, ios::beg);
	chast.get(pr); chast.get(s); chast >> ch;
	weight1 = ch;
	while (chast)
	{
		Node* r = new Node; r->key = s; r->p = ch;
		l.push_back(r);
		chast.get(pr); chast.get(s); chast >> ch;
		if (chast) weight1 += ch;
	}
	chast.close();
}

void vmapy(map<char, float[2]>& m, list<Node*> l, float weight1)
{
	float low = 0, high = 0;
	list<Node*>::iterator j;
	map<char, float[2]>::iterator it;
	for (j = l.begin(); j != l.end(); j++)
	{
		low = high; high = low + (*j)->p / weight1;
		m[(*j)->key][0] = low;
		m[(*j)->key][1] = high;
	}
}

void vect(vector<bool>& v, char s)
{
	int i = 7;
	while (i >= 0)
	{
		if (s & 1 << i)
		{
			v.push_back(1);
		}
		else {
			v.push_back(0);
		}
		i--;
	}

}
//обратно формируем частоты
double chp(vector<bool>& v)
{
	double ch = 0; int p = 1;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == 1) ch += pow(2, -p);
		p++;
	}
	return ch;
}

void sravn(double ch, ifstream& pos, ofstream& dec, map<char, float[2]>& m)
{
	map<char, float[2]>::iterator it;
	double low, high;
	int posl, pod = 0;
	pos >> posl;
	while (pod != posl)
	{
		it = m.begin();
		while (ch < m[it->first][0] || ch >= m[it->first][1]) it++;
		dec << it->first;
		low = m[it->first][0];
		high = m[it->first][1];
		ch = (ch - low) / (high - low);
		pod++;
	}
}

void decode(map<char, float[2]>& m, float& weight2)
{
	ifstream inp("D:/out.txt", ios::binary);
	ofstream dec("D:/Dec.txt");
	ifstream posled("D:/posl.txt");
	double ch; char s;
	int kol = 0;
	vector<bool>v;
	inp.get(s);
	char bu;
	while (inp)
	{

		v.clear();
		kol = 0;
		while (kol != 4 && inp)
		{
			if ((int)s == 13)
			{
				inp.get(bu);
				if ((int)bu == 10)
				{
					s = bu; weight2--;
				}
				else inp.seekg(-1, ios::cur);
			}
			vect(v, s);
			inp.get(s);
			kol++;
		}
		ch = chp(v);
		sravn(ch, posled, dec, m);
		weight2 += 4;
	}
	inp.close();
	dec.close();
	posled.close();
}

bool check()
{
	ifstream dec("D:/Dec.txt");
	ifstream ish("D:/in.txt");
	char symb1, symb2;
	dec >> symb1; ish >> symb2;
	while (dec || ish)
	{

		if (symb1 != symb2) return false;
		dec >> symb1; ish >> symb2;
	}
	return true;
}

void szhat(float ves1, float ves2)
{
	cout << "compressed " << ves1 / ves2 << " times";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	char s, pr; float ch;
	float weight1 = 0, weight2 = 0;
	cout << fixed;
	cout.precision(16);
	list<Node*> l;
	map<char, float[2]> mapa;
	zaplist(l, weight1);
	l.sort(Compare);
	vmapy(mapa, l, weight1);
	decode(mapa, weight2);
	if (check()) cout << "matched";
	else cout << "didn't match";
	cout << endl;
	szhat(weight1, weight2);


}