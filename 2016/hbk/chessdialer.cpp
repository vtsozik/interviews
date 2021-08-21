#include <stdlib.h>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
using namespace std;

class Dialer {
protected:
 vector<vector<int> > m_mPad;
 set<int> m_sStart;
 const int m_iNl;
 const int m_iXstep;
 const int m_iYstep;
 int m_iNc;
 bool IsValidStart(int d) const { return m_sStart.find(d) != m_sStart.end(); }
 bool IsValidDigit(int d) const { return 0 <= d && d <= 9; }
 bool IsValidElement(int i, int j) const { 
  bool valid = false;
  if(0 <= i && i < m_mPad.size()) {
   const vector<int> &row = m_mPad[i];
   if(0 <= j && j < row.size()) {
    valid = IsValidDigit(row[j]);
   }
  }
  return valid; 
 }

public:
 Dialer(const vector<vector<int> > &pad, const vector<int> &start, int nl, int xstep, int ystep) : m_mPad(pad), m_sStart(start.begin(), start.end()), 
  m_iNl(nl), m_iXstep(xstep), m_iYstep(ystep) { 
#ifdef DEBUG
   PrintInput(); 
#endif
  }

 int NumOfNums() {
  int i, j;
  m_iNc = 0; 
  for(i = 0; i < m_mPad.size(); ++i) {
   vector<int> &row = m_mPad[i];
   for(j = 0; j < row.size(); ++j) {
    if(IsValidStart(row[j])) {
#ifdef DEBUG
     vector<int> v;
     NextDigit(i, j, 1, v);
#else
     NextDigit(i, j, 1);
#endif
    }
   }
  }
   
  return m_iNc;
 }

#ifdef DEBUG
 void NextDigit(int i, int j, int curlen, vector<int> v) {
  v.push_back(m_mPad[i][j]);
#else
void NextDigit(int i, int j, int curlen) {
#endif
  if(curlen >= m_iNl) {
   ++m_iNc;
#ifdef DEBUG
   cout << m_iNc << " Valid number:";
   for(int l = 0; l < v.size(); ++l) {
    cout << ' ' << v[l];
   }
   cout << endl;
#endif
  } else {
   ++curlen;
   static const int m[][2] = { {1, 1}, { -1, 1}, {1, -1}, {-1, -1} };
   for(int k = 0; k < sizeof(m)/sizeof(m[0][0]); ++k) {
    int ni = i + m[k][0] * m_iYstep;
    int nj = j + m[k][1] * m_iXstep;
    if(IsValidElement(ni , nj)) {
#ifdef DEBUG
     NextDigit(ni, nj, curlen, v);
#else
     NextDigit(ni, nj, curlen);
#endif
    }
    if(m_iXstep != m_iYstep) {
     ni = i + m[k][0] * m_iXstep;
     nj = j + m[k][1] * m_iYstep;
     if(IsValidElement(ni , nj)) {
#ifdef DEBUG
      NextDigit(ni, nj, curlen, v);
#else
      NextDigit(ni, nj, curlen);
#endif
     }
    }
   }
  }
 }

 void PrintInput() {
  int i, j;
  cout << "Pad:" << endl;
  for(i = 0; i < m_mPad.size(); ++i) {
   vector<int> &row = m_mPad[i];
   for(j = 0; j < row.size(); ++j) {
    cout << '\t' << row[j];
   }
   cout << endl;
  }
  cout << "Valid start:";
  for(set<int>::const_iterator citer = m_sStart.begin(); citer != m_sStart.end(); ++citer) { 
   cout << ' ' << *citer;
  }
  cout << endl;
 }
  
};

template<typename C> void parsestring(const string& in, C &out) {
 char c;
 istringstream iss(in);
 while(iss) {
  iss >> c;
  if(iss) {
   out.push_back(c - 48);
  } else {
   break;
  }
 }
}

/*with nl = 2, output should be 16.*/
int main() {
#ifdef DEBUG
 string piece = "knight";
#else
 string line;
 getline(cin, line);
 string piece = line;
#endif
 cout << piece << endl;
#ifdef DEBUG
 int nl = 2;
#else
 getline(cin, line);
 int nl = atoi(line.c_str());
#endif
 cout << nl << endl;
 int xstep = 1, ystep = 1;
#ifdef DEBUG
 string svalstrt = "2 3 4 5 6 7 8 9";
#else
 string svalstrt;
 getline(cin, svalstrt, '\n');
#endif
 cout << svalstrt << endl;
 vector<int> vvalstrt;
 parsestring(svalstrt, vvalstrt);
#ifdef DEBUG
 int rows = 4;
#else
 getline(cin, line);
 int rows = atoi(line.c_str());
#endif
 cout << rows << endl;
 vector<vector<int> > pad;
 pad.reserve(rows);
#ifdef DEBUG
 int cols = 3;
#else
 getline(cin, line);
 int cols = atoi(line.c_str());
#endif
 cout << cols << endl;
#ifdef DEBUG
 string srows[] = { string("1 2 3"), string("4 5 6"), string("7 8 9"), string("* 0 #") };
#endif
 for(int i = 0; i < rows; ++i) {
  vector<int> vrow;
  vrow.reserve(cols);
#ifdef DEBUG
  parsestring(srows[i], vrow);
#else
  getline(cin, line);
  parsestring(line, vrow);
  cout << line << endl;
#endif
  if(vrow.size() == cols) {
   pad.push_back(vrow);
  }
 }
 if(pad.size() == rows) {
  if(piece.compare("knight") == 0) {
   ystep = 2;
  }
  Dialer dr(pad, vvalstrt, nl, xstep, ystep);
  cout << dr.NumOfNums() << endl;
 }
 return 0;
}
