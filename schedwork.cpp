#include "schedwork.h"
#include <algorithm> // std::find is allowed per instructions

using namespace std;

// Recursive setup for shifts vector
void initShifts(vector<size_t>& shifts, size_t i, size_t size) {
    if (i == size) return;
    shifts.push_back(0);
    initShifts(shifts, i + 1, size);
}

// Recursive setup for sched vector
void initSched(DailySchedule& sched, size_t i, size_t totalDays, size_t dailyNeed) {
    if (i == totalDays) return;
    sched.push_back(vector<Worker_T>());
    initSched(sched, i + 1, totalDays, dailyNeed);
}

// Recursive backtracking scheduler
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
    initSched(sched, 0, num_days, dailyNeed);

    vector<size_t> shifts;
    initShifts(shifts, 0, num_workers);

    return backtrack(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}
