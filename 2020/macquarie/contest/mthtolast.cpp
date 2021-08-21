#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> split_string(string);

struct Node {
    Node() : m_next(NULL), m_prev(NULL), m_val(0) {}
    Node* m_next;
    Node* m_prev;
    int m_val;
};

class MyDll {

public:
    MyDll() : m_head(NULL), m_tail(NULL), m_size(0) {}

    void push_back(int e)
    {
	Node *n(new Node());
	if (m_head == NULL)
	{
	    m_head = n;
	}
	else
	{
            n->m_prev = m_tail;
            m_tail->m_next = n;
	}
	n->m_val = e;
	m_tail = n;
	++m_size;
    }

    const Node* mthtolast(int m) const
    {
        Node *n(NULL);
	if (m > 0)
	{
	    n = m_tail;
	    for (int i(1); i < m && n; ++i)
	    {
                n = n->m_prev;
	    }
	}
	return n;
    } 

    virtual ~MyDll() 
    {
        Node *n = m_head;
	while(n)
	{
	    Node *t = n;
	    n = n->m_next;
	    delete t;
	}
	m_head = m_tail = NULL;
	m_size = 0;
    }

private:
    Node* m_head;
    Node* m_tail;
    int m_size;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    MyDll dll;
    for (int i = 0; i < arr_temp.size(); i++) {
        int arr_item = stoi(arr_temp[i]);
        dll.push_back(arr_item);
    }
    const Node* n(dll.mthtolast(m));
    if (n != NULL)
    {
        cout << n->m_val << endl;
    }
    else
    {
        cout << "NIL" << endl;
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
