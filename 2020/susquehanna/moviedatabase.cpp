#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <memory>
using namespace std;

struct Movie 
{
    size_t m_id;
    string m_title;
    bool operator==(const Movie& r) const
    {
        return (m_id == r.m_id && m_title == r.m_title);
    }
};

istream& operator>>(istream& is, Movie &m)
{
     string str;
     getline(is, str, ',');
     m.m_id = atol(str.c_str());
     getline(is, str, ',');
     m.m_title = str;
     return is;
}

ostream& operator<<(ostream& os, Movie &m)
{
    os << m.m_id << ','
       << m.m_title;
    return os;
}

struct MovieRecord
{
    MovieRecord() : m_movie(new Movie()) {}

    shared_ptr<Movie> m_movie;
    short m_year;
    list<string> m_genres;
};

istream& operator>>(istream& is, MovieRecord &mr)
{
     is >> *mr.m_movie; 
     string str;
     getline(is, str, ',');
     mr.m_year = static_cast<short>(atol(str.c_str()));
     while (getline(is, str, '|'))
     {
         mr.m_genres.push_back(str);
     }
     return is;
}

ostream& operator<<(ostream& os, MovieRecord &mr)
{
    os << *mr.m_movie << ','
       << mr.m_year << ',';
    auto iter = mr.m_genres.begin();
    os  << *iter;
    for (++iter; iter != mr.m_genres.end(); ++iter)
    {
       os << '|' << *iter;
    }
    return os;
}

class Library
{
    map<string, map<short, list<shared_ptr<Movie> > > > m_movies;

public:
    void addMovie(const string& str)
    {
	MovieRecord mr;
        stringstream ss(str);
	ss >> mr;
	for (auto gliter(mr.m_genres.begin()); gliter != mr.m_genres.end(); ++gliter)
	{
	    map<short, list<shared_ptr<Movie> > > eml;
            auto mmiter(m_movies.insert(make_pair(*gliter, eml)).first);
	    list<shared_ptr<Movie> > lm;
            auto mliter(mmiter->second.insert(make_pair(mr.m_year, lm)).first);
	    mliter->second.push_back(mr.m_movie);
	}
    }

    list<Movie> getMovies(const string& genre, const short startYear, const short endYear) const
    {
         list<Movie> rs;
         auto gmiter(m_movies.find(genre));
	 if (gmiter != m_movies.end())
	 {
             for (short i(startYear); i <= endYear; ++i)
	     {
                  auto ymiter(gmiter->second.find(i));
		  if (ymiter != gmiter->second.end())
		  {
                      for (auto liter(ymiter->second.begin()); liter != ymiter->second.end(); ++liter)
                      {
                          rs.push_back(**liter);
		      }
		  }
	     }
	 }
	 return rs;
    }
};

void test1(const Library &l)
{
    list<Movie> rs = l.getMovies("Sci-fi", 1990, 1995);
    bool r(rs.empty());
    rs = l.getMovies("Sci-fi", 1995, 1995);
    r &= rs.empty();
    rs = l.getMovies("Sci-fi", 1995, 2000);
    r &= rs.empty();
    rs = l.getMovies("Sci-fi", 1990, 2000);
    r &= rs.empty();
    cout << "test1: " << (r ? "Passed!" : "Failed!") << endl;
}

void test2(const Library &l)
{
    list<Movie> rs = l.getMovies("Adventure", 1990, 1994);
    bool r(rs.empty());
    rs = l.getMovies("Adventure", 1994, 1994);
    r &= rs.empty();
    rs = l.getMovies("Adventure", 1996, 1996);
    r &= rs.empty();
    rs = l.getMovies("Adventure", 1996, 2000);
    r &= rs.empty();
    cout << "Test2: " << (r ? "Passed!" : "Failed!") << endl;
}

bool areListsEqual(const list<Movie>& lml, const list<Movie>& lmr)
{ 
    bool res(false);
    if (lml.size() == lmr.size())
    {
	res = equal(lml.begin(), lml.end(), lmr.begin());
    }
    return res; 
}

void test3(const Library &l)
{
    const list<Movie> lm = { {1,"Toy Story"}, {2,"Jumanji"} };
    list<Movie> rs = l.getMovies("Fantasy", 1990, 1995);
    bool r(areListsEqual(lm, rs));
    rs = l.getMovies("Fantasy", 1995, 1995);
    r &= areListsEqual(lm, rs);
    rs = l.getMovies("Fantasy", 1995, 2000);
    r &= areListsEqual(lm, rs);
    rs = l.getMovies("Fantasy", 1990, 2000);
    r &= areListsEqual(lm, rs);
    cout << "Test3: " << (r ? "Passed!" : "Failed!") << endl;
}

int main()
{
    ifstream f("moviedatabase.in");
    Library l;
    string str;
    while (getline(f, str))
    {
	if (str.empty() || str[0] == '#')
	{
            continue;
	}
	l.addMovie(str);
    }
    test1(l);
    test2(l);
    test3(l);
    return 0;
}
