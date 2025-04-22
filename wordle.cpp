#include <iostream>
#include <algorithm> 
#include <map>
#include "dict-eng.h"
#include "wordle.h"
#include <set>
#include <string>

using namespace std;

void recurse(
    const string& in,
    string current,
    const string& floating,
    const set<string>& dict,
    set<string>& results,
    size_t index
) {
    if (index == in.size()) {
        if (floating.empty() && dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }

    if (in[index] != '-') {
        recurse(in, current + in[index], floating, dict, results, index + 1);
    } else {
        // Try every lowercase letter
        for (char c = 'a'; c <= 'z'; ++c) {
            size_t count = 0;
            for (char f : floating) {
                if (f == c) {
                    count++;
                }
            }

            if (count > 0) {
                string new_floating = floating;
                size_t pos = new_floating.find(c);
                if (pos != string::npos) {
                    new_floating.erase(pos, 1);
                }
                recurse(in, current + c, new_floating, dict, results, index + 1);
            } else {
                // Only allow unused chars if there's still space left after placing all floating
                if ((in.size() - index - 1) >= floating.size()) {
                    recurse(in, current + c, floating, dict, results, index + 1);
                }
            }
        }
    }
}

set<string> wordle(
    const string& in,
    const string& floating,
    const set<string>& dict)
{
    set<string> results;
    recurse(in, "", floating, dict, results, 0);
    return results;
}
