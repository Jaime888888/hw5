#include "wordle.h"
#include <set>
#include <string>

using namespace std;

// Helper to count how many times a character appears in a string
int countChar(const string& s, char ch) {
    int count = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == ch) {
            count++;
        }
    }
    return count;
}

// Recursive helper to generate possible words
void recurse(
    const string& in,
    string current,
    string floating,
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
        // Try each letter a–z
        for (char c = 'a'; c <= 'z'; ++c) {
            int fCount = countChar(floating, c);
            if (fCount > 0) {
                // use c as a floating letter
                string newFloating = floating;
                for (size_t i = 0; i < newFloating.size(); ++i) {
                    if (newFloating[i] == c) {
                        newFloating.erase(i, 1);
                        break;
                    }
                }
                recurse(in, current + c, newFloating, dict, results, index + 1);
            } else {
                // Only use non-floating letters if we still have room after all floating are placed
                size_t remainingBlanks = 0;
                for (size_t j = index; j < in.size(); ++j) {
                    if (in[j] == '-') {
                        remainingBlanks++;
                    }
                }
                if (remainingBlanks > floating.size()) {
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
