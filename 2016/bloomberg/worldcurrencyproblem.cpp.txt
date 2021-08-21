#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <memory>
using namespace std;

class Quote {

 enum FIELD { TSID = 0, PAIR, BANK, BUY, SELL, SIZE };
 int m_iTsId;
 double m_dBuy, m_dSell;
 string m_sPair, m_sBank;

 bool CheckItem(const FIELD fId, const string &sItem) {
  bool bIsEmpty = sItem.empty();
  if(bIsEmpty) {
   cerr << "Field #" << fId + 1 << " is empty" << endl;
  }
  return !bIsEmpty;
 }

 /* IMHO: scanf will be noticeably faster, but sstream header provided above
  * suggest to use istringstream as scanf is provided by stdlib.h
 */
 bool InitializeField(const FIELD fId, const string &sItem, int &iField) {
  bool bResult = CheckItem(fId, sItem);
  if(bResult) {
   istringstream iss(sItem);
   if(!(bResult = (iss >> iField))) {
    cerr << "Cannot initialize field #" << fId + 1 << " is an integer" << endl;
   } 
  }
  return bResult;
 }

 bool InitializeField(const FIELD fId, const string &sItem, double &dField) {
  bool bResult = CheckItem(fId, sItem);
  if(bResult) {
   istringstream iss(sItem); 
   if(!(bResult = (iss >> dField))) {
    cerr << "Cannot initialize field #" << fId + 1 << " is a double" << endl;
   }
  } 
  return bResult;
 }

 bool InitializeField(const FIELD fId, const string &sItem, string &sField) {
  bool bResult = CheckItem(fId, sItem);
  if(bResult) {
   sField = sItem; 
  }
  return bResult;
 }

public:

 Quote() : m_iTsId(0), m_sPair(), m_sBank(), m_dBuy(0.), m_dSell(0.) {}

 bool Initialize(const vector<string> &stringItems) {
  bool bResult = stringItems.size() >= SIZE;

  if(!bResult) {
   cerr << "Quote should have at least " << SIZE << " fields, but only " << stringItems.size() << " was provided" << endl;
  } else {
   bResult = InitializeField(TSID, stringItems[TSID], m_iTsId)
    && InitializeField(PAIR, stringItems[PAIR], m_sPair)
    && InitializeField(BANK, stringItems[BANK], m_sBank)
    && InitializeField(BUY, stringItems[BUY], m_dBuy)
    && InitializeField(SELL, stringItems[SELL], m_dSell);
  }

  return bResult;  
 }

 int GetTsId() const { return m_iTsId; }

 const string& GetPair() const { return m_sPair; }

 const string& GetBank() const { return m_sBank; }

 double GetBuy() const { return m_dBuy; }

 double GetSell() const { return m_dSell; }

 void UpdateQuote(const Quote &rhs) {
  m_iTsId = rhs.m_iTsId;
  m_dBuy = rhs.m_dBuy;
  m_dSell = rhs.m_dSell;
 }
};

ostream &operator<<(ostream &os, const Quote &quote) {
 os << quote.GetTsId() << '|' << quote.GetPair() << '|' 
  << quote.GetBank() << '|' << quote.GetBuy() << '|'
  << quote.GetSell();
 return os;
}

template<class T> struct CompareBuyAndTs {
 bool operator()(const T& lhs, const T& rhs) const {
  return  lhs->GetBuy() > rhs->GetBuy() ||
   (lhs->GetBuy() == rhs->GetBuy() && lhs->GetTsId() < rhs->GetTsId());
 }
};

template<class T> struct CompareSellAndTs {
 bool operator()(const T& lhs, const T& rhs) const {
  return  lhs->GetSell() < rhs->GetSell() || 
   (lhs->GetSell() == rhs->GetSell() && lhs->GetTsId() < rhs->GetTsId());
 }
};

template<class T> struct CompareBankAndPair {
 bool operator()(const T& lhs, const T& rhs) const {
  return lhs->GetBank().compare(rhs->GetBank()) < 0 ||
   (lhs->GetBank().compare(rhs->GetBank()) == 0 && 
   lhs->GetPair().compare(rhs->GetPair()) < 0);
 }
};

class QuoteProcessor {
 set<shared_ptr<Quote>, CompareBuyAndTs<shared_ptr<Quote> > > m_sBestBuy;
 set<shared_ptr<Quote>, CompareSellAndTs<shared_ptr<Quote> > > m_sBestSell;
 set<shared_ptr<Quote>, CompareBankAndPair<shared_ptr<Quote> > > m_sBank;
 const Quote m_qEmptyQuote;

public:

 bool ProcessQuote(const vector<string> &quote) {
  bool bResult = false;
  shared_ptr<Quote> spQuote(new Quote());
  if((bResult = spQuote->Initialize(quote))) {
   set<shared_ptr<Quote>, CompareBankAndPair<shared_ptr<Quote> > >::iterator qbsIter 
    = m_sBank.find(spQuote);
   if(qbsIter != m_sBank.end()) {
    /* We need to re-balance quote rank anyway.
     * Documentation doesn't say whether it's possible for a bank 
     * to supply (repeat) the same quote but with different (new) timestamp
     */
    m_sBestBuy.erase(*qbsIter);
    m_sBestSell.erase(*qbsIter);
    (*qbsIter)->UpdateQuote(*spQuote);
   } else {
    m_sBank.insert(spQuote);
   }
   m_sBestBuy.insert(spQuote);
   m_sBestSell.insert(spQuote);
  } else {
   cerr << "Quote: " << *spQuote << " is invalid and rejected from processing" << endl;
  }
  return bResult;
 } 

 const Quote& GetBestBuy() const {
  return (m_sBestBuy.empty()) ? m_qEmptyQuote : *(m_sBestBuy.begin()->get());
 }

 const Quote& GetBestSell() const {
  return (m_sBestSell.empty()) ? m_qEmptyQuote : *(m_sBestSell.begin()->get());
 }
};

int main () {
    /*Initialization 
    
    In this part of the program you can perform any kind of
    initialization routine before processing the stream 
    of data.*/

    QuoteProcessor qp;
    string line;
    vector<string> quote; 
    string item; 
    while(getline(cin, line)) {
    	if(!line.empty()) {
        	quote.clear(); 
    		istringstream ss(line); 
    		while (getline(ss, item, '|')) {
    			quote.push_back(item);
    		} 
               
    // Step 1: Process quote. 
		qp.ProcessQuote(quote);
   
    // A new quote has been received. You can now update 
    // your application. 
    // Step 2: Query 
    // Let's now get the best buy and sell rate 
    // for EURUSD currency pair
    /*
    		cout << "Best buy: "  << ... << endl;
    		cout << "Best sell: " << ...  << endl;
    */
    /* Accepted output format:
     *		Best EURUSD Buy = 1.1 from Bank1
     *		Best EURUSD Sell = 1.2 from Bank1
     */
                const Quote &qBestBuy =  qp.GetBestBuy();
		cout << "Best " << qBestBuy.GetPair() << " Buy = " << qBestBuy.GetBuy() << " from " << qBestBuy.GetBank() << endl;
                const Quote &qBestSell =  qp.GetBestSell();
		cout << "Best " << qBestSell.GetPair() << " Sell = " << qBestSell.GetSell() << " from " << qBestSell.GetBank() << endl;
    	}
    }
    return 0;
}
