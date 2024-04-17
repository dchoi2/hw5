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
void wordFinder(const string& in, const set<string>& dict, set<string>& results, string& buildStr, 
                  int idx, map<char, int>& floatCount, map<char, int>& currCount, int blanks, int floats);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
  map<char, int> floatCount, currCount;
  set<string> results;
  string buildStr = in;
  int blanks = 0;
  int floats = floating.length();

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
  }
  wordFinder(in, dict, results, buildStr, 0, floatCount, currCount, blanks, floats);
  return results;
} 

// Define any helper functions here
void wordFinder(const string& in, const set<string>& dict, set<string>& results, string& buildStr, 
                  int idx, map<char, int>& floatCount, map<char, int>& currCount, int blanks, int floats)
{
  if(idx == in.size())
  {
    // all floating characters not used 
    for(map<char, int>::iterator it = floatCount.begin(); it != floatCount.end(); ++it)
    {
      if(currCount[it->first] < it->second)
      {
        return;
      }
    }
    // if all letters used and in dictionary --> valid word
    if (dict.find(buildStr) != dict.end())
    {
      results.insert(buildStr);
    }
    return;
  }

  if(in[idx] != '-')
  {
    wordFinder(in, dict, results, buildStr, idx + 1, floatCount, currCount, blanks, floats);
  }
  else
  {
    if(blanks == floats)
    {
      for(map<char, int>::iterator it = floatCount.begin(); it != floatCount.end(); ++it)
      {
        if(currCount[it->first] < it->second)
        {
          buildStr[idx] = it->first;
          currCount[it->first]++;
          wordFinder(in, dict, results, buildStr, idx + 1, floatCount, currCount, blanks, floats);
          currCount[it->first]--;
        }
      }      
    }
    else
    {
      for(char c = 'a'; c <= 'z'; c++)
    {
      buildStr[idx] = c;
      if(floatCount.find(c) != floatCount.end())
      {
        currCount[c]++;
      }
      wordFinder(in, dict, results, buildStr, idx + 1, floatCount, currCount, blanks, floats);

      // reset currCount status after recursion to backtrack properly
      if(floatCount.find(c) != floatCount.end())
      {
        currCount[c]--;
      }
    }
    }    
  }
}