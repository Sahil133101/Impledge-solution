
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std;
using namespace chrono;

class Solution
{
public:
    unordered_map<string, bool> mp;

    bool isCompound(string word, unordered_set<string> &st)
    {
        if (mp.find(word) != mp.end())
            return mp[word];

        int l = word.length();
        for (int i = 0; i < l; i++)
        {
            string prefix = word.substr(0, i + 1);
            string suffix = word.substr(i + 1);

            if ((st.find(prefix) != st.end() && isCompound(suffix, st)) || (st.find(prefix) != st.end() && st.find(suffix) != st.end()))
                return mp[word] = true;
        }
        return mp[word] = false;
    }

    pair<string, string> findLongestAndSecondLongestConcatenatedWords(vector<string> &words)
    {
        mp.clear();
        unordered_set<string> st(begin(words), end(words));

        string longestWord = "", secondLongestWord = "";
        for (const string &word : words)
        {
            if (isCompound(word, st))
            {
                if (word.length() > longestWord.length())
                {
                    secondLongestWord = longestWord;
                    longestWord = word;
                }
                else if (word.length() > secondLongestWord.length())
                {
                    secondLongestWord = word;
                }
            }
        }
        return {longestWord, secondLongestWord};
    }
};

vector<string> readWordsFromFile(const string &filename)
{
    vector<string> words;
    ifstream file(filename);
    string word;
    if (!file)
    {
        cerr << "Error opening file: " << filename << endl;
        return words;
    }
    while (file >> word)
    {
        words.push_back(word);
    }
    file.close();
    return words;
}

int main()
{
    vector<string> filenames = {"Input_01.txt", "Input_02.txt"};

    for (const string &filename : filenames)
    {
        vector<string> words = readWordsFromFile(filename);
        if (words.empty())
        {
            cout << "No words found in " << filename << endl;
            continue;
        }

        Solution sol;
        auto start = high_resolution_clock::now();

        pair<string, string> result = sol.findLongestAndSecondLongestConcatenatedWords(words);

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        cout << "File: " << filename << endl;
        cout << "Longest concatenated word: " << result.first << endl;
        cout << "Second longest concatenated word: " << result.second << endl;
        cout << "Time taken to process file " << filename << ": " << duration.count() << " milliseconds" << endl;
        cout << "----------------------------------------------------\n";
    }

    return 0;
}
