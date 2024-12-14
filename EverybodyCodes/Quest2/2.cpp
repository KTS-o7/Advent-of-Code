#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Result {
    int symbols;
    int words;
};

Result getRunicCounts(const string& wordsAndInscription, bool searchBackwards, bool searchVertically, bool wrapHorizontally) {
    vector<pair<int, int>> searchDirections = { {0, 1} }; // Right
    if (searchBackwards) {
        searchDirections.push_back({0, -1}); // Left
    }
    if (searchVertically) {
        searchDirections.push_back({-1, 0}); // Up
        searchDirections.push_back({1, 0});  // Down
    }

    size_t sepPos = wordsAndInscription.find("\n\n");
    string wordsPart = wordsAndInscription.substr(0, sepPos);
    string inscriptionPart = wordsAndInscription.substr(sepPos + 2);

    size_t wordsPos = wordsPart.find("WORDS:");
    vector<string> words;
    if (wordsPos != string::npos) {
        string wordsStr = wordsPart.substr(wordsPos + 6);
        size_t pos = 0;
        while ((pos = wordsStr.find(',')) != string::npos) {
            words.push_back(wordsStr.substr(0, pos));
            wordsStr.erase(0, pos + 1);
        }
        words.push_back(wordsStr);
    }

    vector<string> lines;
    size_t start = 0, end;
    while ((end = inscriptionPart.find('\n', start)) != string::npos) {
        lines.push_back(inscriptionPart.substr(start, end - start));
        start = end + 1;
    }
    lines.push_back(inscriptionPart.substr(start));

    int rowCount = lines.size();
    int wordsFound = 0;
    vector<vector<char>> grid(rowCount);
    for (int r = 0; r < rowCount; ++r) {
        grid[r] = vector<char>(lines[r].begin(), lines[r].end());
    }

    vector<vector<int>> scales(rowCount, vector<int>(grid[0].size(), 0));

    for (int r = 0; r < rowCount; ++r) {
        for (int c = 0; c < grid[r].size(); ++c) {
            for (const string& word : words) {
                if (grid[r][c] != word[0]) continue;
                for (auto& dir : searchDirections) {
                    bool failed = false;
                    vector<pair<int, int>> coords = { {r, c} };
                    for (int i = 1; i < word.length(); ++i) {
                        int nr = r + dir.first * i;
                        int nc = c + dir.second * i;

                        if (wrapHorizontally) {
                            if (nc >= grid[nr].size()) nc -= grid[nr].size();
                            if (nc < 0) nc += grid[nr].size();
                        } else {
                            if (nc >= grid[nr].size() || nc < 0) {
                                failed = true;
                                break;
                            }
                        }

                        if (nr >= rowCount || nr < 0) {
                            failed = true;
                            break;
                        }

                        if (grid[nr][nc] != word[i]) {
                            failed = true;
                            break;
                        }
                        coords.push_back({ nr, nc });
                    }
                    if (!failed) {
                        wordsFound++;
                        for (auto& coord : coords) {
                            scales[coord.first][coord.second] = 1;
                        }
                    }
                }
            }
        }
    }

    int scaleCount = 0;
    for (auto& row : scales) {
        for (auto& slot : row) {
            if (slot) scaleCount++;
        }
    }
    return { scaleCount, wordsFound };
}

int solvePart1(const string& wordsAndInscription) {
    return getRunicCounts(wordsAndInscription, false, false, false).words;
}

int solvePart2(const string& wordsAndInscription) {
    return getRunicCounts(wordsAndInscription, true, false, false).symbols;
}

int solvePart3(const string& wordsAndInscription) {
    return getRunicCounts(wordsAndInscription, true, true, true).symbols;
}

