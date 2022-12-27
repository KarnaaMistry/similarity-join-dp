#include "simJoin.h"

// Karnaa Mistry  simJoin.cc  CS541

int simJoin::getDataNum() const
{
  return data.size();
}

bool simJoin::getString(int id, string &out) const
{
  if (id < 0 || id >= data.size())
    return false;
  out = data[id];
  return true;
}

bool simJoin::readData(const string &filename)
{
  string str;
  ifstream datafile(filename, ios::in);
  while (getline(datafile, str))
    data.emplace_back(str);

  return true;
}

//Edit Distance calculation with DP, adjusted band, early termination
int ED(unsigned tau, string r, string s)
{
  int n = r.size();
  int m = s.size();

  if (abs(n - m) > tau) {
    return tau+2;
  }

  int arr[n+1][m+1];

  int large = n+m+1;
  std::fill(*arr, *arr + (n+1)*(m+1), large); 

  for (int i = 0; i <= n; i++) {
    arr[i][0] = i;
  }
  for (int j = 0; j <= m; j++) {
    arr[0][j] = j;
  }

  for (int i = 1; i <= n; i++) {
    

    int lo = i-tau;
    int hi = i+tau;
    for (int j = std::max(1, lo); j <= std::min(m, hi); j++) { 

      int diag;
      int del;
      int ins;
      
      if (r.at(i-1) == s.at(j-1)) { //match
        diag = 0 + arr[i-1][j-1];
      } else { //substitute
        diag = 1 + arr[i-1][j-1];
      }

      del = 1 + arr[i-1][j];
      ins = 1 + arr[i][j-1];

      arr[i][j] = std::min(std::min(ins, del), diag);

    }

    //post-row check for early termination
    for (int j = std::max(1, lo); j <= std::min(m, hi); j++) {
      if (arr[i][j] <= tau) {
        goto cont; //skip the early return
      }
    }

    return tau+2;

    //no early termination yet
    cont:;
    
  }


  return arr[n][m];

}


 /*
 * It should do a similarity join operation betweent the set of strings from a data file
 * such that the edit distance between two string is not larger than the given threshold. The 
 * format of result is a triple of numbers which respectively stand for the two IDs of the pair of strings
 * from the data file and the edit distance between the two strings. All results are stored in a vector, sorted based on the IDs of the string from
 * the first file and then the IDs of the string from the second file in an ascending order. Return 
 * an error if the similarity join operation is failed.
 * (Method objective provided by Rutgers University)
 */


bool simJoin::SimilarityJoin(unsigned threshold, vector< triple<unsigned, unsigned, unsigned> > &results) 
{

  int N = getDataNum();

  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      int dist = ED(threshold, data[i], data[j]);
      if (dist <= threshold) {
        triple<unsigned, unsigned, unsigned> t;
        t.id1 = i;
        t.id2 = j;
        t.ed = dist;

        results.push_back(t);

      }
      
    }

  }

  return true;
}

