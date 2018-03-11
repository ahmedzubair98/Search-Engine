#include<iostream>
#include<string>
#include<vector>
using namespace std;

class word {
private:
	string doc;
	vector<int> pos;
public:
	word(string document, int position)
	{
		doc = document;
		pos.push_back(position);
	}
	word()
	{
		;
	}
	word(string document, vector<int> arr)
	{
		doc = document;
		pos = arr;
	}
	string getDoc()
	{
		return doc;
	}
	int occurence()
	{
		return pos.size();
	}
	void push_back(int x)
	{
		pos.push_back(x);
	}
	vector<int>* getPos()
	{
		return &pos;
	}
};