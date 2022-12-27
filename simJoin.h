#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sys/time.h>

using namespace std;

// Karnaa Mistry  simJoin.h  CS541
// Provided by Rutgers University CS541

template<typename T1, typename T2, typename T3>
struct triple
{
  T1 id1;
  T2 id2;
  T3 ed;
};

class simJoin 
{
public:
	simJoin(const string &filename) 
  {
    readData(filename);
  };

	~simJoin  () {};

  bool SimilarityJoin(unsigned ed_threshold, vector< triple<unsigned, unsigned, unsigned> > &results);
  bool getString(int id, string &out) const;
  int getDataNum() const;
  
private:
  vector<string> data;
  bool readData(const string &filename);
};
