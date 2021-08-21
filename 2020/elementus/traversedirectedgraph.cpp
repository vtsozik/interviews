#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



/*
 * Complete the 'traverse' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER starting_node
 *  2. 2D_INTEGER_ARRAY graph
 */

vector<int> traverse(int starting_node, vector<vector<int>> graph) {
    vector<list<int> > sg(graph.size(), list<int>());
    set<int> fg;
    for (int i(0); i < graph.size(); ++i)
    {
        if (graph[i][0] != graph[i][1] && graph[i][1] != starting_node)
	{
            sg[graph[i][0] - 1].push_back(graph[i][1]);
	}
    }
    list<int> ntv;
    ntv.splice(ntv.end(), sg[starting_node - 1]);
    while (!ntv.empty())
    {
        int n = ntv.front();
	ntv.pop_front();
	if (fg.insert(n).second)
        {
            ntv.splice(ntv.end(), sg[n - 1]);
	}
    }
    vector<int> sfa(fg.begin(), fg.end());
    return sfa;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string starting_node_temp;
    getline(cin, starting_node_temp);

    int starting_node = stoi(ltrim(rtrim(starting_node_temp)));

    string graph_rows_temp;
    getline(cin, graph_rows_temp);

    int graph_rows = stoi(ltrim(rtrim(graph_rows_temp)));

    string graph_columns_temp;
    getline(cin, graph_columns_temp);

    int graph_columns = stoi(ltrim(rtrim(graph_columns_temp)));

    vector<vector<int>> graph(graph_rows);

    for (int i = 0; i < graph_rows; i++) {
        graph[i].resize(graph_columns);

        string graph_row_temp_temp;
        getline(cin, graph_row_temp_temp);

        vector<string> graph_row_temp = split(rtrim(graph_row_temp_temp));

        for (int j = 0; j < graph_columns; j++) {
            int graph_row_item = stoi(graph_row_temp[j]);

            graph[i][j] = graph_row_item;
        }
    }

    vector<int> result = traverse(starting_node, graph);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

