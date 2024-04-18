#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordFinder(const string& in, const set<string>& dict, set<string>& results, string buildStr, 
                  int idx, map<char, int>& floatCount, int count, int totalFloats);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
  map<char, int> floatCount;
  set<string> results;

  int blanks = 0;
  int totalFloats = 0;

  for(size_t i = 0; i < in.length(); i++)
  {
    if(in[i] == '-')
    {
      blanks++;
    }
  }

  for(size_t i = 0; i < floating.length(); i++)
  {
    floatCount[floating[i]]++;
    totalFloats++;
  }
  wordFinder(in, dict, results, in, 0, floatCount, blanks, totalFloats);
  return results;
} 

// Define any helper functions here
void wordFinder(const string& in, const set<string>& dict, set<string>& results, string buildStr, 
                  int idx, map<char, int>& floatCount, int blanks, int totalFloats)
{
  if(idx == in.size())
  {
    // all floating characters not used 
    if(totalFloats > 0)
    {
      return;
    }
    // if all letters used and in dictionary --> valid word
    else if(dict.find(buildStr) != dict.end())
    {
      results.insert(buildStr);
    }
    return;
  }

  if(in[idx] != '-')
  {
    wordFinder(in, dict, results, buildStr, idx + 1, floatCount, blanks, totalFloats);
  }
  else
  {
    map<char, int> originalFloatCount = floatCount;
    if(blanks == totalFloats)
    {
      for(map<char, int>::iterator it = floatCount.begin(); it != floatCount.end(); ++it)
      {
        if(it->second > 0)
        {
          buildStr[idx] = it->first;
          it->second--;
          wordFinder(in, dict, results, buildStr, idx + 1, floatCount, blanks - 1, totalFloats - 1);
          it->second++;
        }
        
      }
    }      
    
    else
    {
      for(char c = 'a'; c <= 'z'; c++)
      {
        buildStr[idx] = c;
        if(floatCount.find(c) != floatCount.end() && floatCount[c] > 0)
        {
          floatCount[c]--;
          wordFinder(in, dict, results, buildStr, idx + 1, floatCount, blanks - 1, totalFloats - 1);
          floatCount[c]++;
        }
        else
        {
          wordFinder(in, dict, results, buildStr, idx + 1, floatCount, blanks - 1, totalFloats);
        }
      }
    }
    buildStr[idx] = '-';
  }
}