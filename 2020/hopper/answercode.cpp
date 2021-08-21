#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <map>
#include <memory>

using namespace std;

enum Type { OUTPUT, ANSWER, GOTO, CONCLUSION };

class InputLine {
public:
  virtual Type type() const = 0;
  virtual bool hasLabel() const = 0;
  virtual int getLabel() const = 0;
  virtual const string& getText() const = 0;

  virtual ~InputLine() {}

  friend ostream& operator<< (ostream& o, const InputLine& l) { l.toStream(o); return o; }

private:
  virtual void toStream(ostream& o) const = 0;
};

class Output : public InputLine {
public:
  Output(string t, bool h, int l) : text(move(t)), has_label(h), label(l) {}
  Output(string t) : text(move(t)), has_label(false), label(-1) {}

  Type type() const { return OUTPUT; }
  bool hasLabel() const { return has_label; }
  int getLabel() const { return label; }
  const string& getText() const { return text; }

private:
  void toStream(ostream&) const {};

  string text;
  bool has_label;
  int label;
};

class Answer : public InputLine {
public:
  Answer(string t) : text(move(t)) {}

  Type type() const { return ANSWER; }
  bool hasLabel() const { return false; }
  int getLabel() const { return -1; }
  const string& getText() const { return text; }

private:
  void toStream(ostream&) const {};

  string text;
};

class Goto : public InputLine {
public:
  Goto(int l) : label(l) {}

  Type type() const { return GOTO; }
  bool hasLabel() const { return true; }
  int getLabel() const { return label; }
  const string& getText() const { return empty_string; }

private:
  void toStream(ostream&) const {};

  int label;
  static const string empty_string;
};
const string Goto::empty_string;

class Conclusion : public InputLine {
public:
  Conclusion(string t) : text(move(t)) {}

  Type type() const { return CONCLUSION; }
  bool hasLabel() const { return false; }
  int getLabel() const { return -1; }
  const string& getText() const { return text; }

private:
  void toStream(ostream&) const {};

  string text;
};

struct IndentedLine {
  int indent;
  shared_ptr<const InputLine> line;
  IndentedLine(const int ind, const InputLine* ln) : indent(ind), line(ln) { }
};
ostream& operator<< (ostream& o, const IndentedLine& il);


struct AKey {
    int ident;
    string answer;
    bool operator<(const AKey& ak) const
    {
        if(ident < ak.ident)
	{
	    return true;
	}
	else if(ident == ak.ident)
	{
	    return answer.compare(ak.answer) < 0;
	}
	return false;
    }
};

struct LTreeVal {
    AKey src, dst;
    size_t si;
};

void parseTreeAndLabels(const vector<IndentedLine>& flattree, map<AKey, vector<size_t> >& aTree)
{
  AKey ak = {-1, string()};
  map<int, LTreeVal> lTree;
  aTree.insert(pair<AKey, vector<size_t> >(ak, vector<size_t>()));
  for (size_t it(0), ai(0); it < flattree.size(); ++it) 
  {
    const IndentedLine& line = flattree[it];
    const int ident = line.indent;
    const string& text = line.line->getText();
    if (ident % 2 == 0)
    {
        if (ai == 0)
        {
            aTree.begin()->second.push_back(it);
        }
        else
        {
            ak.ident = flattree[ai].indent;
            ak.answer = flattree[ai].line->getText();
	    map<AKey, vector<size_t> >::iterator ati = aTree.find(ak);
            if(!text.empty())
            {
		if (ati->second.size() == 0 || it - *(ati->second.rbegin()) == 1)
		{
                    ati->second.push_back(it);
		}
                if (line.line->hasLabel())
                {
                   map<int, LTreeVal>::iterator lti = lTree.find(line.line->getLabel()); 
		   if (lti != lTree.end())
		   {
                      lti->second.src = ak;
                      lti->second.si = ati->second.size() - 1;
		   }
		   else
                   {
		       AKey dst;
                       LTreeVal lv = {ak, dst, ati->second.size() - 1};
                       lTree.insert(pair<int, LTreeVal>(line.line->getLabel(), lv));
                   }
                }
            } 
	    else 
	    {
                if (line.line->hasLabel())
                {
		    map<int, LTreeVal>::iterator lti = lTree.find(line.line->getLabel());
                    if (lti != lTree.end())
                    {
                        lti->second.dst = ak;
                    } 
		    else 
		    {
			AKey src;
                        LTreeVal lv = {src, ak, 0};
                        lTree.insert(pair<int, LTreeVal>(line.line->getLabel(), lv));
		    }
                }
            }
        }
    }
    else
    {
        ai = it;
        ak.ident = ident;
        ak.answer = text;
        aTree.insert(pair<AKey, vector<size_t> >(ak, vector<size_t>()));
    }
  }
  for (map<int, LTreeVal>::iterator lti = lTree.begin(); lti != lTree.end(); ++lti)
  {
      vector<size_t> vl = aTree.find(lti->second.src)->second;
      map<AKey, vector<size_t> >::iterator ati = aTree.find(lti->second.dst);
      for (size_t li(lti->second.si); li < vl.size(); ++li)
      {
          ati->second.push_back(vl[li]);
      }
  }
}

void printConversation(const vector<IndentedLine>& flattree, const vector<string>& answers, stringstream& out) 
{
  map<AKey, vector<size_t> > aTree;
  parseTreeAndLabels(flattree, aTree);
  vector<string> allanswers;
  allanswers.reserve(1 + answers.size());
  allanswers.push_back(string());
  allanswers.insert(allanswers.end(), answers.begin(), answers.end());
  for(size_t i(0), ai(-1); i < allanswers.size(); ++i)
  {
     if (i > 0)
     {
         out << "User: " << allanswers[i] << endl;
     }
     AKey ak = { static_cast<int>(ai), allanswers[i] }; 
     map<AKey, vector<size_t> >::iterator iat =  aTree.find(ak);
     if (iat != aTree.end())
     {
         vector<size_t>& inds = iat->second;
         for(size_t j(0); j < inds.size(); ++j)
	 {
             out << ((i < allanswers.size() - 1) ? "Hopper: " : "Conclusion: ") << flattree[inds[j]].line->getText() << endl;
	 }
         ai += 2;
     }
     else 
     {
         out << "Hopper: Invalid input" << endl;
     }
  }
}

void checkTestCase(const int number, const stringstream &et, const stringstream &out)
{
    cout << "Test case #" << number;
    if(et.str() != out.str())
    {
        cout << " failed!" << endl;
        cout << "Program output:" << endl;
        cout << out.str() << endl;
        cout << "Expected output:" << endl;
        cout << et.str() << endl;
    }
    else
    {
        cout << " passed!" << endl;
    }
}

void runTestCase1()
{
    // Labelless test case.
    static const int num = 1;
    vector<IndentedLine> flattree;
    flattree.push_back(IndentedLine(0, new Output("Hello, John! It looks like you booked a Basic Economy flight.")));
    flattree.push_back(IndentedLine(0, new Output("Are you aware that this flight doesn't have any storage for carry-on luggage?")));
    flattree.push_back(IndentedLine(1, new Answer("No")));
    flattree.push_back(IndentedLine(2, new Output("Some other limitations you may want to consider is that you will not be able to pick a seat.")));
    flattree.push_back(IndentedLine(2, new Output("We're happy to let you know that we can upgrade you today for just $25!")));
    flattree.push_back(IndentedLine(2, new Output("Would you like to do that now?")));
    flattree.push_back(IndentedLine(3, new Answer("Not right now")));
    flattree.push_back(IndentedLine(4, new Conclusion("Okay, please let our customer service team know if you change your mind.")));
    flattree.push_back(IndentedLine(3, new Answer("Yes, please upgrade")));
    flattree.push_back(IndentedLine(4, new Conclusion("Okay, you've been upgraded!")));
    flattree.push_back(IndentedLine(1, new Answer("Yes")));
    flattree.push_back(IndentedLine(2, new Output("We're happy to let you know that we can upgrade you today for just $25!")));
    flattree.push_back(IndentedLine(2, new Output("Would you like to do that now?")));
    flattree.push_back(IndentedLine(3, new Answer("Not right now")));
    flattree.push_back(IndentedLine(4, new Conclusion("Okay, please let our customer service team know if you change your mind.")));
    flattree.push_back(IndentedLine(3, new Answer("Yes, please upgrade")));
    flattree.push_back(IndentedLine(4, new Conclusion("Okay, you've been upgraded!")));

    vector<string> answers;
    answers.push_back("No");
    answers.push_back("Not right now");

    stringstream et;
    et << "Hopper: Hello, John! It looks like you booked a Basic Economy flight." << endl;
    et << "Hopper: Are you aware that this flight doesn't have any storage for carry-on luggage?" << endl;
    et << "User: No" << endl;
    et << "Hopper: Some other limitations you may want to consider is that you will not be able to pick a seat." << endl;
    et << "Hopper: We're happy to let you know that we can upgrade you today for just $25!" << endl;
    et << "Hopper: Would you like to do that now?" << endl;
    et << "User: Not right now" << endl;
    et << "Conclusion: Okay, please let our customer service team know if you change your mind." << endl;

    stringstream out;
    printConversation(flattree, answers, out);
    checkTestCase(num, et, out);
}

void runTestCase2()
{
    // Labeled test case, no label usage.
    static const int num = 2;
    vector<IndentedLine> flattree;
    flattree.push_back(IndentedLine(0, new Output("Hello, John! It looks like you booked a Basic Economy flight.")));
    flattree.push_back(IndentedLine(0, new Output("Are you aware that this flight doesn't have any storage for carry-on luggage?")));
    flattree.push_back(IndentedLine(1, new Answer("Yes")));
    flattree.push_back(IndentedLine(2, new Goto(1)));
    flattree.push_back(IndentedLine(1, new Answer("No")));
    flattree.push_back(IndentedLine(2, new Output("Some other limitations you may want to consider is that you will not be able to pick a seat.")));
    flattree.push_back(IndentedLine(2, new Output("We're happy to let you know that we can upgrade you today for just $25!", true, 1)));
    flattree.push_back(IndentedLine(2, new Output("Would you like to do that now?")));
    flattree.push_back(IndentedLine(3, new Answer("Not right now")));
    flattree.push_back(IndentedLine(4, new Conclusion("Okay, please let our customer service team know if you change your mind.")));
    flattree.push_back(IndentedLine(3, new Answer("Yes, please upgrade")));
    flattree.push_back(IndentedLine(4, new Conclusion("Okay, you've been upgraded!")));

    vector<string> answers;
    answers.push_back("No");
    answers.push_back("Not right now");

    stringstream et;
    et << "Hopper: Hello, John! It looks like you booked a Basic Economy flight." << endl;
    et << "Hopper: Are you aware that this flight doesn't have any storage for carry-on luggage?" << endl;
    et << "User: No" << endl;
    et << "Hopper: Some other limitations you may want to consider is that you will not be able to pick a seat." << endl;
    et << "Hopper: We're happy to let you know that we can upgrade you today for just $25!" << endl;
    et << "Hopper: Would you like to do that now?" << endl;
    et << "User: Not right now" << endl;
    et << "Conclusion: Okay, please let our customer service team know if you change your mind." << endl;

    stringstream out;
    printConversation(flattree, answers, out);
    checkTestCase(num, et, out);
}

void runTestCase3()
{
    // Labeled test case with label usage.
    static const int num = 3;
    vector<IndentedLine> flattree;
    flattree.push_back(IndentedLine(0, new Output("Hello, John! It looks like you booked a Basic Economy flight.")));
    flattree.push_back(IndentedLine(0, new Output("Are you aware that this flight doesn't have any storage for carry-on luggage?")));
    flattree.push_back(IndentedLine(1, new Answer("No")));
    flattree.push_back(IndentedLine(2, new Output("Some other limitations you may want to consider is that you will not be able to pick a seat.")));
    flattree.push_back(IndentedLine(2, new Output("We're happy to let you know that we can upgrade you today for just $25!", true, 1)));
    flattree.push_back(IndentedLine(2, new Output("Would you like to do that now?")));
    flattree.push_back(IndentedLine(3, new Answer("Not right now")));
    flattree.push_back(IndentedLine(4, new Conclusion("Okay, please let our customer service team know if you change your mind.")));
    flattree.push_back(IndentedLine(3, new Answer("Yes, please upgrade")));
    flattree.push_back(IndentedLine(4, new Conclusion("Okay, you've been upgraded!")));
    flattree.push_back(IndentedLine(1, new Answer("Yes")));
    flattree.push_back(IndentedLine(2, new Goto(1)));

    vector<string> answers;
    answers.push_back("Yes");
    answers.push_back("Yes, please upgrade");

    stringstream et;
    et << "Hopper: Hello, John! It looks like you booked a Basic Economy flight." << endl;
    et << "Hopper: Are you aware that this flight doesn't have any storage for carry-on luggage?" << endl;
    et << "User: Yes" << endl;
    et << "Hopper: We're happy to let you know that we can upgrade you today for just $25!" << endl;
    et << "Hopper: Would you like to do that now?" << endl;
    et << "User: Yes, please upgrade" << endl;
    et << "Conclusion: Okay, you've been upgraded!" << endl;

    stringstream out;
    printConversation(flattree, answers, out);
    checkTestCase(num, et, out);
}

void runTestCase4()
{
    // Warm up case with with error 
    static const int num = 4;
    vector<IndentedLine> flattree;
    flattree.push_back(IndentedLine(0, new Output("Hello world.")));
    flattree.push_back(IndentedLine(0, new Output("Good luck on your test!")));
    flattree.push_back(IndentedLine(1, new Answer("Thanks!")));
    flattree.push_back(IndentedLine(2, new Conclusion("Goodbye!")));
    
    vector<string> answers;
    answers.push_back("What test?");
    answers.push_back("Thanks!");

    stringstream et;
    et << "Hopper: Hello world." << endl;
    et << "Hopper: Good luck on your test!" << endl;
    et << "User: What test?" << endl;
    et << "Hopper: Invalid input" << endl;
    et << "User: Thanks!" << endl;
    et << "Conclusion: Goodbye!" << endl;

    stringstream out;
    printConversation(flattree, answers, out);
    checkTestCase(num, et, out);
}

void runTestCase5()
{
    // Warm up case with without error 
    static const int num = 5;
    vector<IndentedLine> flattree;
    flattree.push_back(IndentedLine(0, new Output("Hello world.")));
    flattree.push_back(IndentedLine(0, new Output("Good luck on your test!")));
    flattree.push_back(IndentedLine(1, new Answer("Thanks!")));
    flattree.push_back(IndentedLine(2, new Conclusion("Goodbye!")));

    vector<string> answers;
    answers.push_back("Thanks!");

    stringstream et;
    et << "Hopper: Hello world." << endl;
    et << "Hopper: Good luck on your test!" << endl;
    et << "User: Thanks!" << endl;
    et << "Conclusion: Goodbye!" << endl;

    stringstream out;
    printConversation(flattree, answers, out);
    checkTestCase(num, et, out);
}

int main()
{
   runTestCase1(); 
   runTestCase2(); 
   runTestCase3();
   runTestCase4();
   runTestCase5();
   return 0;
}

