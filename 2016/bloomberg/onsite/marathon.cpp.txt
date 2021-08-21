/*
 * Question:
 *
 * Design an algorithm and associated data structure(s) to capture marathon runner 
 * ids which are reported by sensors installed along the marathon route. A sensor 
 * reports runner id whenever the runner crosses mark where the corresponding 
 * sensor is installed. Print top ten runner ids and sensor ids that they are 
 * just passed whenever this top ten list differs from the previous version.
 *
 * Answer:
 *
 * Program below simulates the problem described above. Runner ids are recorded
 * into two dimensional array (matrix) where first dimension corresponds to 
 * sensor id and second reflects the order in which runners crossing this indexed
 * sensor. To print top ten runners start enumerating first dimension from the
 * end (highest id sensor crossed first) and second dimension from the beginning (
 * order in which runners crossing this sensor). Record each runner and sensor
 * ids into vector of pairs and unordered_map (hashmap, with runner id as a key 
 * and sensor id as a value) only if runner id was not found in the unordered map.
 * Stop when vector size will reach ten. Compare unordered_map with its previous
 * version if different print the results and assign new version of unordered map
 * to variable that keeps its previous version instance.
 *
 * Compile this program with:
 *  g++ -O3 -std=c++11 marathon.cpp -lpthread
 *
 * Run resulted executable with:
 *  ./a.out
 *
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define DISTANCE_BETWEEN_SENSORS 100
#define MARATHON_DISTANCE 10000
#define NUMBER_OF_RUNNERS 100
#define NUMBER_OF_TOP_RUNNERS 10
static const int NUMBER_OF_SENSORS = MARATHON_DISTANCE / DISTANCE_BETWEEN_SENSORS + 1;

vector< vector<int> > results;
mutex randm, resm;
bool strtd = false;
unordered_map<int, int> pastRepRes;
condition_variable_any cvstrt, cvprgrs;

double GetNextPosition() {
 lock_guard<mutex> randGuard(randm);
 while(!strtd) { cvstrt.wait(randm); } 
 return static_cast<double>(rand()) / RAND_MAX;
}

void SubmitRunnersProgress(int sensID, int runnerID) {
 lock_guard<mutex> srpGuard(resm);
 if(results.size() < sensID + 1) {
  vector<int> passOrder;
  passOrder.reserve(NUMBER_OF_RUNNERS);
  results.push_back(passOrder);
  /*
  * Don't worry about incomplete update (runnerID still has to be pushed in)
  * resm mutex locked anyway, so awaken thread still has to wait until it
  * gets unlocked
  */
  cvprgrs.notify_one();
 }
 results[sensID].push_back(runnerID);
}

void RunMarathon(int runnerID) {
 double currPos(0.);
 int lastRepSensID(-1);
 do {
  currPos += GetNextPosition();
  int currSensID = static_cast<int>(currPos / DISTANCE_BETWEEN_SENSORS);
  if(currSensID > lastRepSensID) {
   SubmitRunnersProgress(currSensID, runnerID);
   lastRepSensID = currSensID;
  }
 } while(currPos < MARATHON_DISTANCE);
}

void PrintTopResults() {
 vector<pair<int, int> > top;
 do {
  unordered_map<int, int> pastRes;
  top.clear();
  top.reserve(NUMBER_OF_TOP_RUNNERS);
  resm.lock();
  cvprgrs.wait(resm);
  for(int i(results.size() - 1); i >= 0; --i) {
   const vector<int> &sensRes = results[i];
   int j, sz(sensRes.size());
   for(j = 0; j < sz; ++j) {
    int runID = sensRes[j];
    if(pastRes.find(runID) == pastRes.end()) {
     pair<int, int> p(runID, i);
     top.push_back(p);
     pastRes.insert(p);
     if(top.size() == NUMBER_OF_TOP_RUNNERS) {
      break;
     }
    }
   }
   if(j < sz) {
    break;
   }
  }
  resm.unlock();
  if(top.size() < NUMBER_OF_TOP_RUNNERS || pastRepRes == pastRes) {
   continue;
  } else {
   pastRepRes = pastRes;
  }
  cout << "Top ten runners progress:" << endl;
  for(int i = 0; i < top.size(); ++i) {
   cout << i + 1 << ") Runner id: " << top[i].first << ", sensor id: " << top[i].second << endl;
  }
 } while(top.begin()->second + 1 < NUMBER_OF_SENSORS);
}

int main() {
 vector<shared_ptr<thread> > thrds;
 thrds.reserve(NUMBER_OF_RUNNERS);
 results.reserve(NUMBER_OF_SENSORS);
 for(int i(0); i < NUMBER_OF_RUNNERS; ++i) {
  thrds.push_back(shared_ptr<thread>(new thread(RunMarathon, i + 1))); 
 }
 cout << "Starting marathon !!!!" << endl;
 strtd = true;
 cvstrt.notify_all();
 PrintTopResults();
 cout << "And we have a winner above!!!!" << endl;
 for(int i(0); i < NUMBER_OF_RUNNERS; ++i) {
  thrds[i]->join();
 }
 return 0;
}
