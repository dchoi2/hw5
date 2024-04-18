#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool makeSched(int day, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts,
                DailySchedule& sched, vector<int>& amtShifts, size_t numWorkers, size_t numDays);

// Add your implementation of schedule() and other helper functions here
bool makeSched(int day, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts,
                DailySchedule& sched, vector<int>& amtShifts, size_t numWorkers, size_t numDays)
{
  // out of bounds of days
  if(day >= numDays)
  {
    return true;
  }

  // shifts for current day filled
  if(sched[day].size() == dailyNeed)
  {
    return makeSched(day + 1, avail, dailyNeed, maxShifts, sched, amtShifts, numWorkers, numDays);
  }

  for(size_t i = 0; i < numWorkers; ++i)
  {
    if(avail[day][i] && amtShifts[i] < maxShifts)
    {
      sched[day].push_back(i);
      amtShifts[i]++;
      if(makeSched(day, avail, dailyNeed, maxShifts, sched, amtShifts, numWorkers, numDays))
      {
        return true;
      }

      // set up for backtracking
      sched[day].pop_back();
      amtShifts[i]--;
    }

  }
  return false;
}


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    // n = days, k = workers
    size_t n = avail.size();
    size_t k = avail[0].size();

    vector<int> amtShifts(k);
    for(size_t i = 0; i < amtShifts.size(); i++)
    {
      amtShifts[i] = 0;
    }
    // initialize the schedule
    sched.resize(n);
    
    return makeSched(0, avail, dailyNeed, maxShifts, sched, amtShifts, k, n);
}

