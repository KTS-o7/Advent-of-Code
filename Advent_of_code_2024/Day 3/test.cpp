#include <iostream>
#include <vector>
#include <regex>
#include <string>

using namespace std;

int main() {
    vector<string> data = {
        "do()_mul(1,2)",
        "don't()_mul(3,4)",
        "mul(5,6)",
        "do()_mul(7,8)",
        "mul(9,10)"
    };

    regex do_dont_pattern(R"((do\(\)|don't\(\)))");
    regex mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");

    vector<pair<size_t, bool>> do_dont_positions;
    vector<pair<size_t, smatch>> mul_positions;

    for (const auto& str : data) {
        auto do_dont_begin = sregex_iterator(str.begin(), str.end(), do_dont_pattern);
        auto do_dont_end = sregex_iterator();
        for (auto it = do_dont_begin; it != do_dont_end; ++it) {
            smatch match = *it;
            cout<<"1. matched string is "<< match.str() << endl;
            bool is_do = match.str() == "do()";
            do_dont_positions.emplace_back(match.position(), is_do);
        }

        auto mul_begin = sregex_iterator(str.begin(), str.end(), mul_pattern);
        auto mul_end = sregex_iterator();
        for (auto it = mul_begin; it != mul_end; ++it) {
            smatch match = *it;
            cout<<"2. matched string is "<< match.str() << endl;
            mul_positions.emplace_back(match.position(), match);
        }
    }

    bool enabled = true;
    size_t do_dont_index = 0;
    int sum = 0;

    vector<pair<size_t, bool>> all_positions;
    for (const auto& pos : do_dont_positions) {
        all_positions.emplace_back(pos.first, pos.second);
    }
    for (const auto& pos : mul_positions) {
        all_positions.emplace_back(pos.first, true); // true here is a placeholder
    }


    for (const auto& [pos, is_do] : all_positions) {
        if (do_dont_index < do_dont_positions.size() && do_dont_positions[do_dont_index].first == pos) {
            enabled = do_dont_positions[do_dont_index].second;
            ++do_dont_index;
        } else {
            for (const auto& [mul_pos, match] : mul_positions) {
                if (mul_pos == pos && enabled) {
                    int x = stoi(match[1].str());
                    int y = stoi(match[2].str());
                    sum += x * y;
                }
            }
        }
    }

    cout << "Sum of multiplications: " << sum << endl;

    return 0;
}