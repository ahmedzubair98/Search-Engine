#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<fstream>
#include<algorithm>
#include<functional>
#include"word.h"

using namespace std;


map<string, vector<word>> Map_;
unordered_map<string, vector<word>> Hash_;


int read(string filename)
{
	int count = 0;
	string end = "---END.OF.DOCUMENT---";
	ifstream fin;
	ofstream fout;
	string str;
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Cant read. File not opened" << endl;
		return -1;
	}
	while (!fin.eof())
	{
		str = to_string(count);
		str = str + ".txt";
		fout.open(str);
		fin >> str;
		while (str != end)
		{
			if (str.length() > 1)
			{
				if (str[str.length() - 1] == '.' || str[str.length() - 1] == ',' || str[str.length() - 1] == '!' || str[str.length() - 1] == '\''
					|| str[str.length() - 1] == ';' || str[str.length() - 1] == '"' || str[str.length() - 1] == ')')
					str.pop_back();
				if (str[str.length() - 1] == '.' || str[str.length() - 1] == ',' || str[str.length() - 1] == '!' || str[str.length() - 1] == '\''
					|| str[str.length() - 1] == ';' || str[str.length() - 1] == '"' || str[str.length() - 1] == ')')
					str.pop_back();
				if (str[0] == '"' || str[0] == '(' || str[0] == '\'')
					str.erase(0, 1);
			}
			if (str.length() > 2 && str[str.length() - 2] == '\'')
			{
				str[str.length() - 2] = str[str.length() - 1];
				str.pop_back();
			}
			fout << str << " ";
			fin >> str;
		}
		fout.close();
		count++;
	}
	return count;
}

int crawl(string filename, map<string, vector<word>> *map, unordered_map<string, vector<word>> *hashtable)
{
	ifstream  fin;
	int count = 0;
	bool deed = false;
	string buff;
	vector<word> arr(1);
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Cannot crawl. " << filename << " not opened." << endl;
		return -1;
	}
	while (!fin.eof())
	{
		fin >> buff;
		auto itr_map = map->find(buff);
		if (itr_map == map->end())
		{
			arr[0] = word(filename, count);
			map->insert(make_pair(buff,arr));
		}
		else
		{
			for (int i = 0; i < itr_map->second.size(); i++)
			{
				if (filename == itr_map->second[i].getDoc())
				{
					itr_map->second[i].push_back(count);
					deed = true;
					break;
				}
			}
			if (!deed)
			{
				itr_map->second.push_back(word(filename, count));
			}
		}
		auto itr_hash = hashtable->find(buff);
		deed = false;
		if (itr_hash == hashtable->end())
		{
			arr[0] = word(filename, count);
			hashtable->insert(make_pair(buff, arr));
		}
		else
		{
			for (int i = 0; i < itr_hash->second.size(); i++)
			{
				if (filename == itr_hash->second[i].getDoc())
				{
					itr_hash->second[i].push_back(count);
					deed = true;
					break;
				}
			}
			if (!deed)
			{
				itr_hash->second.push_back(word(filename, count));
			}
		}
		deed = false;
		count++;
	}
	return count;
}


void save(map<string, vector<word>> *map, unordered_map<string, vector<word>> *hashtable)
{
	ofstream fout;
	fout.open("map.txt");
	vector<word> a;
	vector<int> b;
	for (auto itr = map->begin(),itr2=itr; itr != map->end();++itr)
	{
		fout << itr->first << " " << itr->second.size() << endl;
		a = itr->second;
		for (int i = 0; i < a.size(); i++)
		{
			fout << a[i].getDoc() << " ";
			b = *(a[i].getPos());
			fout << b.size() << " ";
			for (int j = 0; j < b.size(); j++)
			{
				fout << b[j];
				if (j < b.size() - 1)
					fout << " ";
			}
			itr2 = itr;
			if (++itr2 != map->end())
				fout << endl;
			else
			{
				if (i < a.size() - 1)
					fout << endl;
			}
		}
	}
	fout.close();
	
	fout.open("unordered_map.txt");
	for (auto itr = hashtable->begin(), itr2 = itr; itr != hashtable->end(); ++itr)
	{
		fout << itr->first << " " << itr->second.size() << endl;
		a = itr->second;
		for (int i = 0; i < a.size(); i++)
		{
			fout << a[i].getDoc() << " ";
			b = *(a[i].getPos());
			fout << b.size() << " ";
			for (int j = 0; j < b.size(); j++)
			{
				fout << b[j];
				if (j < b.size() - 1)
					fout << " ";
			}
			itr2 = itr;
			if (++itr2 != hashtable->end())
				fout << endl;
			else
			{
				if (i < a.size() - 1)
					fout << endl;
			}
		}
	}
	fout.close();
}

void load(map<string, vector<word>> *Map, unordered_map<string, vector<word>> *hashtable)
{
	ifstream fin;
	fin.open("map.txt");
	bool deed = false;
	string buff,filename;
	int x,y;
	vector<word> arr(1);
	vector<int> arr2;
	unordered_map<string, vector<word>>::iterator itr_hash;
	map<string, vector<word>>::iterator itr_map;
	if (!fin.is_open())
	{
		cout << "Cannot load. " << "map.txt" << " not opened." << endl;
		return;
	}
	while (!fin.eof())
	{
		fin >> buff;
		fin >> x;
		for (int i = 0; i < x; i++)
		{
			fin >> filename;
			fin >> y;
			arr2.resize(y);
			for (int j = 0, k; j < y; j++)
			{
				fin >> k;
				arr2[j] = k;
			}
			if (i == 0)
			{
				arr[0] = word(filename, arr2);
				Map->insert(make_pair(buff, arr));
			}
			else
			{
				itr_map = Map->find(buff);
				itr_map->second.push_back(word(filename, arr2));
			}
		}
	}
	fin.close();


	fin.open("unordered_map.txt");
	if (!fin.is_open())
	{
		cout << "Cannot load. " << "unordered_map.txt" << " not opened." << endl;
		return;
	}
	while (!fin.eof())
	{
		fin >> buff;
		fin >> x;
		for (int i = 0; i < x; i++)
		{
			fin >> filename;
			fin >> y;
			arr2.resize(y);
			for (int j = 0, k; j < y; j++)
			{
				fin >> k;
				arr2[j] = k;
			}
			if (i == 0)
			{
				arr[0] = word(filename, arr2);
				hashtable->insert(make_pair(buff, arr));
			}
			else
			{
				itr_hash = hashtable->find(buff);
				itr_hash->second.push_back(word(filename, arr2));
			}
		}
	}
	fin.close();
}

void mapByOccurence(vector<word> arr, multimap<int, word, greater <int>> &Map)
{
	for (int i = 0; i < arr.size(); i++)
	{
		Map.insert(make_pair(arr[i].occurence(), arr[i]));
	}
	return;
}


void case1(vector<string> arr, int mode)
{
	multimap<int, word, greater<int>> final_map;
	if (mode == 1)
	{
		auto itr = Hash_.find(arr[0]);
		if (itr == Hash_.end())
		{
			return;
		}
		mapByOccurence(itr->second, final_map);
	}
	if (mode == 2)
	{
		auto itr = Map_.find(arr[0]);
		if (itr == Map_.end())
		{
			return;
		}
		mapByOccurence(itr->second, final_map);
	}

	for (auto itr = final_map.begin(); itr != final_map.end(); ++itr)
	{
		cout << itr->second.getDoc() << endl;
	}
}

void case2(vector<string> arr, int mode)
{
	multimap<int, multimap<int, word, greater <int>>, greater <int>> final_map;
	int count;
	vector<unordered_map<string, word>> hash_arr(arr.size());
	vector<word> a;
	if (mode == 1)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			auto itr = Hash_.find(arr[i]);
			if (itr != Hash_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
	}
	if (mode == 2)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			auto itr = Map_.find(arr[i]);
			if (itr != Map_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
	}

	
	unordered_map<string, word>::iterator itr, itr2;
	for (int i = 0; i < hash_arr.size(); i++)
	{
		for (itr = hash_arr[i].begin();itr != hash_arr[i].end(); ++itr)
		{
			count = 0;
			for (int j = i + 1; j < hash_arr.size(); j++)
			{
				itr2 = hash_arr[j].find(itr->first);
				if (itr2 != hash_arr[j].end())
				{
					count++;
					hash_arr[j].erase(itr2);
				}
			}
			multimap<int, word, greater <int>> temp;
			temp.insert(make_pair(itr->second.occurence(), itr->second));
			final_map.insert(make_pair(count, temp));
		}
	}
	for (auto itr = final_map.begin(); itr != final_map.end(); ++itr)
	{
		for (auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2)
		{
			cout << itr2->second.getDoc() << endl;
		}
	}
}


void case3(vector<string> arr, int mode)
{
	arr[arr.size() - 1].pop_back();
	arr[0].erase(0, 1);
	if (arr.size() == 1)
	{
		case1(arr, mode);
		return;
	}

	vector<unordered_map<string, word>> hash_arr(arr.size());
	vector<word> a;
	
	if (mode == 1)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			auto itr = Hash_.find(arr[i]);
			if (itr != Hash_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
	}
	if (mode == 2)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			auto itr = Map_.find(arr[i]);
			if (itr != Map_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
	}

	multimap<int, word, greater <int>> final_map;
	vector<int> v,v2;
	int count = 0;
	bool flag=true;
	for (auto itr = hash_arr[0].begin(); itr != hash_arr[0].end(); ++itr)
	{
		v = *(itr->second.getPos());
		for (int i = 0; i < v.size(); i++)
		{
			for (int j = 1,flag = true; j < hash_arr.size() && flag; j++)
			{
				auto itr2 = hash_arr[j].find(itr->first);
				if (itr2 != hash_arr[j].end())
				{
					v2 = *(itr2->second.getPos());
					if (!binary_search(v2.begin(), v2.end(), v[i] + j))
					{
						flag = false;
					}
				}
				else
					flag = false;
				if (flag)
					count++;
			}
		}
		if(count != 0)
			final_map.insert(make_pair(count, itr->second));
		count = 0;
	}
	for (auto itr = final_map.begin(); itr != final_map.end(); ++itr)
	{
		cout << itr->second.getDoc() << endl;
	}
}


void case4(vector<string> arr, int index, int mode)
{
	arr[index].pop_back();
	arr[0].erase(0, 1);
	if (arr.size() == 1)
	{
		case1(arr, mode);
		return;
	}

	vector<unordered_map<string, word>> hash_arr(arr.size());
	vector<word> a;
	
	if (mode == 1)
	{
		for (int i = 0; i <= index; i++)
		{
			auto itr = Hash_.find(arr[i]);
			a = itr->second;
			for (int j = 0; j < a.size(); j++)
			{
				hash_arr[i].insert(make_pair(a[j].getDoc(), a[j]));
			}
		}
	}

	if (mode == 2)
	{
		for (int i = 0; i <= index; i++)
		{
			auto itr = Map_.find(arr[i]);
			a = itr->second;
			for (int j = 0; j < a.size(); j++)
			{
				hash_arr[i].insert(make_pair(a[j].getDoc(), a[j]));
			}
		}
	}

	unordered_map<string,int> temp_hash;
	vector<int> v, v2;
	int count = 0;
	bool flag;
	for (unordered_map<string, word>::iterator itr = hash_arr[0].begin(); itr != hash_arr[0].end(); ++itr)
	{
		v = *(itr->second.getPos());
		for (int i = 0; i < v.size(); i++)
		{
			for (int j = 1, flag = true; j < hash_arr.size() && flag; j++)
			{
				auto itr2 = hash_arr[j].find(itr->first);
				if (itr2 != hash_arr[j].end())
				{
					v2 = *(itr2->second.getPos());
					if (!binary_search(v2.begin(), v2.end(), v[i] + j))
					{
						flag = false;
					}
				}
				else
					flag = false;
				if (flag)
					count++;
			}
		}
		if(count != 0)
			temp_hash.insert(make_pair(itr->second.getDoc(), count));
		count = 0;
	}

	vector<unordered_map<string, word>> hash_arr2(arr.size() - (index + 1));
	
	if (mode == 1)
	{
		for (int i = 0; i < arr.size() - (index + 1); i++)
		{
			auto itr = Hash_.find(arr[index + 1 + i]);
			a = itr->second;
			for (int j = 0; j < a.size(); j++)
			{
				hash_arr2[i].insert(make_pair(a[j].getDoc(), a[j]));
			}
		}
	}
	
	if (mode == 2)
	{
		for (int i = 0; i < arr.size() - (index + 1); i++)
		{
			auto itr = Map_.find(arr[index + 1 + i]);
			a = itr->second;
			for (int j = 0; j < a.size(); j++)
			{
				hash_arr2[i].insert(make_pair(a[j].getDoc(), a[j]));
			}
		}
	}


	for (auto itr = temp_hash.begin(); itr != temp_hash.end(); ++itr)
	{
		for (int i = 0; i < hash_arr2.size(); i++)
		{
			auto itr2 = hash_arr2[i].find(itr->first);
			if (itr2 != hash_arr2[i].end())
			{
				itr->second += itr2->second.occurence();
				hash_arr2[i].erase(itr2);
			}
		}
	}
	
	multimap<int, string, greater <int>> final_map;
	for (auto itr = temp_hash.begin(); itr != temp_hash.end(); ++itr)
	{
		final_map.insert(make_pair(itr->second,itr->first));
	}
	for (int i = 0; i < hash_arr2.size(); i++)
	{
		for (auto itr = hash_arr2[i].begin(); itr != hash_arr2[i].end(); ++itr)
		{
			final_map.insert(make_pair(itr->second.occurence(), itr->first));
		}
	}

	for (auto itr = final_map.begin(); itr != final_map.end(); ++itr)
	{
		cout << itr->second << endl;
	}
}


void case5(vector<string> arr, int index, int mode)
{
	vector<unordered_map<string, word>> hash_arr(arr.size()-1);
	vector<word> a;
	
	if (mode == 1)
	{
		for (int i = 0; i < index; i++)
		{
			auto itr = Hash_.find(arr[i]);
			if (itr != Hash_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
		for (int i = index + 1; i < arr.size(); i++)
		{
			auto itr = Hash_.find(arr[i]);
			if (itr != Hash_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i - 1].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
	}

	if (mode == 2)
	{
		for (int i = 0; i < index; i++)
		{
			auto itr = Map_.find(arr[i]);
			if (itr != Map_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
		for (int i = index + 1; i < arr.size(); i++)
		{
			auto itr = Map_.find(arr[i]);
			if (itr != Map_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i - 1].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
	}


	for (int i = 0; i < arr.size() - (index + 1); i++)
	{
		for (auto itr = hash_arr[index + i].begin(); itr != hash_arr[index + i].end(); ++itr)
		{
			for (int j = 0; j < index; j++)
			{
				auto itr2 = hash_arr[j].find(itr->first);
				if (itr2 != hash_arr[j].end())
				{
					hash_arr[j].erase(itr2);
				}
			}
		}
	}

	if (index == 1)
	{
		multimap<int, word, greater <int>> final_map;
		for (auto itr = hash_arr[0].begin(); itr != hash_arr[0].end(); ++itr)
		{
			final_map.insert(make_pair(itr->second.occurence(), itr->second));
		}
		for (auto itr = final_map.begin(); itr != final_map.end(); ++itr)
		{
			cout << itr->second.getDoc() << endl;
		}
	}
	else
	{
		int count = 0;
		multimap<int, multimap<int, word, greater <int>>, greater <int>> final_map;
		unordered_map<string, word>::iterator itr, itr2;
		for (int i = 0; i < index; i++)
		{
			for (itr = hash_arr[i].begin(); itr != hash_arr[i].end(); ++itr)
			{
				count = 0;
				for (int j = i + 1; j < index; j++)
				{
					itr2 = hash_arr[j].find(itr->first);
					if (itr2 != hash_arr[j].end())
					{
						count++;
						hash_arr[j].erase(itr2);
					}
				}
				multimap<int, word, greater <int>> temp;
				temp.insert(make_pair(itr->second.occurence(), itr->second));
				final_map.insert(make_pair(count, temp));
			}
		}
		for (auto itr = final_map.begin(); itr != final_map.end(); ++itr)
		{
			for (auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2)
			{
				cout << itr2->second.getDoc() << endl;
			}
		}
	}
}


void case6(vector<string> arr, int index, int mode)
{
	arr[index].pop_back();
	arr[0].erase(0, 1);
	index++;

	vector<unordered_map<string, word>> hash_arr(arr.size() - 1);
	vector<word> a;
	
	if (mode == 1)
	{
		for (int i = 0; i < index; i++)
		{
			auto itr = Hash_.find(arr[i]);
			if (itr != Hash_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
		for (int i = index + 1; i < arr.size(); i++)
		{
			auto itr = Hash_.find(arr[i]);
			if (itr != Hash_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i - 1].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
	}

	if (mode == 2)
	{
		for (int i = 0; i < index; i++)
		{
			auto itr = Map_.find(arr[i]);
			if (itr != Map_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
		for (int i = index + 1; i < arr.size(); i++)
		{
			auto itr = Map_.find(arr[i]);
			if (itr != Map_.end())
			{
				a = itr->second;
				for (int j = 0; j < a.size(); j++)
				{
					hash_arr[i - 1].insert(make_pair(a[j].getDoc(), a[j]));
				}
			}
		}
	}

	multimap<int, word, greater <int>> final_map;
	vector<int> v, v2;
	int count = 0;
	bool flag = true;
	for (auto itr = hash_arr[0].begin(); itr != hash_arr[0].end(); ++itr)
	{
		v = *(itr->second.getPos());
		for (int i = 0; i < v.size(); i++)
		{
			for (int j = 1, flag = true; j < index && flag; j++)
			{
				auto itr2 = hash_arr[j].find(itr->first);
				if (itr2 != hash_arr[j].end())
				{
					v2 = *(itr2->second.getPos());
					if (!binary_search(v2.begin(), v2.end(), v[i] + j))
					{
						flag = false;
					}
				}
				else
					flag = false;
				if (flag)
					count++;
			}
		}
		if (count != 0)
		{
			bool found = false;
			for (int i = index; i < hash_arr.size() && !found; i++)
			{
				found = false;
				auto itr2 = hash_arr[i].find(itr->second.getDoc());
				if (itr2 != hash_arr[i].end())
					found = true;
			}
			if(!found)
				final_map.insert(make_pair(count, itr->second));
		}
		count = 0;
	}
	for (auto itr = final_map.begin(); itr != final_map.end(); ++itr)
	{
		cout << itr->second.getDoc() << endl;
	}
}



void parse(string str, int mode)
{
	vector<string> arr;
	char delim = ' ';
	size_t itr = 0;
	size_t begin = 0;
	while (itr != string::npos)
	{
		itr = str.find(delim, begin);
		arr.push_back(str.substr(begin, itr-begin));
		begin = itr + 1;
	}
	if (arr.size() == 0)
	{
		arr.push_back(str);
	}
	if (arr.size() == 1 && arr[0][0] != '"')
		case1(arr, mode);
	else if (arr[0][0] == '"')
	{
		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i][arr[i].size() - 1] == '"' && i == arr.size() - 1)
			{
				case3(arr, mode);
				return;
			}
			else if (arr[i][arr[i].size() - 1] == '"')
			{
				
				if (arr[i+1] == "-")
				{
					case6(arr, i, mode);
					return;
				}
				case4(arr, i, mode);
				return;
			}
		}
	}
	else
	{
		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i] == "-")
			{
				case5(arr, i, mode);
				return;
			}
		}
		case2(arr, mode);
	}

	return;
}


int main()
{
	int x,count;
	string buff;
	cout << "---SEARCH ENGINE---" << endl<<endl;
	cout << "1. Create databse" << endl;
	cout << "2. Load Database" << endl;
	cin >> x;
	while (x != 1 && x != 2)
		cout << "Choose correct option" << endl;
	if (x == 1)
	{
		cout << "Enter filename to read from: ";
		cin >> buff;
		cout << "Please wait ..." << endl;
		count = read(buff);
		for (int i = 0; i < count; i++)
		{
			buff = to_string(count);
			buff += ".txt";
			crawl(buff, &Map_, &Hash_);
		}
		cout << "Press 1 to save database." << endl;
		cin >> count;
		if (count == 1)
		{
			save(&Map_, &Hash_);
		}
	}
	else
	{
		cout << "Please wait..." << endl;
		load(&Map_, &Hash_);
		cout << "done..." << endl;
	}
	system("cls");
	while (1)
	{
		cout << "1. Search by map" << endl;
		cout << "2. Search by hash" << endl;
		cin >> x;
		while (x != 1 && x != 2)
			cout << "Enter correct option" << endl;
		system("cls");
		cout << "Enter query:" << endl;
		getline(cin, buff);
		getline(cin, buff);
		parse(buff, x);
		cout << endl << "Press any key to continue." << endl;
		cin >> x;
		system("cls");
	}
}