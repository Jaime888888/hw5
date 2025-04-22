
#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


void recurse(
    const string& in,
    string current,
    int freq[26],
    size_t totalFloating,
    const set<string>& dict,
    set<string>& results,
    size_t index
) {
  
    if ((in.size() - index) < totalFloating) {
        return;
    }

    if (index == in.size()) {
        if (totalFloating == 0 && dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }

    if (in[index] != '-') {
        recurse(in, current + in[index], freq, totalFloating, dict, results, index + 1);
    } else {
        for (char c = 'a'; c <= 'z'; ++c) {
            bool usedFloating = false;

            if (freq[c - 'a'] > 0) {
                freq[c - 'a']--;
                recurse(in, current + c, freq, totalFloating - 1, dict, results, index + 1);
                freq[c - 'a']++;
                usedFloating = true;
            }

            if (!usedFloating && (in.size() - index - 1) >= totalFloating) {
                recurse(in, current + c, freq, totalFloating, dict, results, index + 1);
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

    int freq[26] = {0};
    for (size_t i = 0; i < floating.size(); ++i) {
        freq[floating[i] - 'a']++;
    }

    recurse(in, "", freq, floating.size(), dict, results, 0);
    return results;
}
