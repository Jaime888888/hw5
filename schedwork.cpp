
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// add or remove necessary headers as you please


#include "schedwork.h"
#include <algorithm> // for std::find

using namespace std;

bool backtrack(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shifts,
    size_t day,
    size_t slot
) {
    if (day == avail.size()) {
        return true;
    }

    for (size_t worker = 0; worker < avail[0].size(); ++worker) {
        if (avail[day][worker] &&
            shifts[worker] < maxShifts &&
            find(sched[day].begin(), sched[day].end(), worker) == sched[day].end()) {
            
            sched[day].push_back(worker);
            shifts[worker]++;

            size_t next_day = day;
            size_t next_slot = slot + 1;
            if (next_slot == dailyNeed) {
                next_day++;
                next_slot = 0;
            }

            if (backtrack(avail, dailyNeed, maxShifts, sched, shifts, next_day, next_slot)) {
                return true;
            }

            // backtrack
            sched[day].pop_back();
            shifts[worker]--;
        }
    }

    return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched)
{
    if (avail.empty() || avail[0].empty()) {
        return false;
    }

    size_t num_days = avail.size();
    size_t num_workers = avail[0].size();

    sched.clear();
    sched.resize(num_days);
    for (size_t i = 0; i < num_days; ++i) {
        sched[i].reserve(dailyNeed);
    }

    vector<size_t> shifts(num_workers, 0);

    return backtrack(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}
