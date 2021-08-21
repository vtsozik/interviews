#include <iostream>
#include <unordered_set>
using namespace std;

string findFirstRepeatedWord(const string& sentence)
{
    unordered_set<string> words;
    for (size_t st(0), i(0); i < sentence.size(); ++i)
    {
        if (sentence[i] == ' ' || sentence[i] == '\t' ||
            sentence[i] == ',' || sentence[i] == ':' ||
	    sentence[i] == ';' || sentence[i] == '-' ||
	    sentence[i] == '.')
	{
	    string word = sentence.substr(st, i - st);
            if(!words.insert(word).second)
	    {
                return word;
	    }
	    st = i + 1;
	}
    }
    return string();
}

int main()
{
    string sentence("He had had quite enough of this nonsense.");
    cout << findFirstRepeatedWord(sentence) << endl;
    return 0;
}
