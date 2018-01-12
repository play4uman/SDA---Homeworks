#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <fstream>

using namespace std;

typedef list<int> Vertex;
typedef list<Vertex> Graph;
typedef Vertex::iterator vIterator;
typedef Graph::iterator gIterator;

void removeWhite(string& s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ')
			s.erase(s.begin() + i);
	}
}

/*
void read() {
	fstream fstr;
	fstr.open("C:/Users/grade/Desktop/test.txt");
	string str = "";
	char c;
	while (!fstr.eof()) {
		c = fstr.get();
		while (c != '\n' && !fstr.eof()) {
			str += c;
			c = fstr.get();
		}
		cout << str << endl;
		removeWhite(str);
		int* temp = new int[str.length()];
		fstr.seekg(fstr.tellg - str.length());


		str = "";
	}
}
*/


gIterator point(Graph& g, int a) {
	gIterator git = g.begin();
	for (; git != g.end(); git++) {
		if (git->front() == a)
			return git;
	}
	return git;
}

bool isInVisited(gIterator& l, int a) {
	vIterator vit = l->begin();
	for (; vit != l->end(); vit++) {
		if (*vit == a)
			return true;
	}
	return false;
}

Vertex shortestPath(Graph& g, gIterator start, gIterator& target) {
	queue<int> help;

	Vertex visited;
	visited.push_back(start->front());

	Vertex path;
	path.push_back(start->front());

	while (start != target) {
		for (vIterator vit = start->begin(); vit != start->end(); vit++) {
			if (!isInVisited(start, *vit)) {
				visited.push_back(*vit);
				help.push(*vit);
			}
			start = point(g, help.front());
			path.push_back(start->front());
			help.pop();
		}
	}
	return path;
}




struct node {
	char c;
	node* left;
	node* right;
};

int* split(string const & input) {
	int* out = new int[input.length() + 1];
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '.')
			out[i] = 1;
		else if (input[i] == '-')
			out[i] = 2;
		else
			out[i] = 0;
	}
	out[input.length()] = 0;
	return out;
}

string decipher(node* root, string const & input) {
	node* q = root;
	string out = "";
	int* in = split(input);
	for (int i = 0; i < input.length() + 1; i++) {
		if (in[i] == 1)
			q = q->left;
		if (in[i] == 2)
			q = q->right;
		if(in[i] == 0) {
			out += q->c;
			q = root;
		}
	}
	return out;
}



int main(){

	node M = { 'M', NULL, NULL };
	node N = { 'N', NULL, NULL };
	node T = { 'T', &N, &M };
	node A = { 'A', NULL, NULL };
	node I = { 'I', NULL, NULL };
	node E = { 'E', &I, &A };
	node root = { 'R', &E, &T };

	fstream temp; 
	char c;
	temp.open("C:/Users/grade/Desktop/test.txt");
	c = temp.get();
	cout << c;
	c = temp.get();
	cout << c;
	c = temp.get();
	cout << c;
	long p = temp.tellg();
	p -= 2;
	temp.seekg(p);
	c = temp.get();
	cout << c;


	int tempa;
	cin >> tempa;
	return 0;
}

