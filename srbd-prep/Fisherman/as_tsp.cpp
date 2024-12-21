#include <bits/stdc++.h>
using namespace std;

int min_distance;

void assign_fishing_spots(vector<int>& spots, const vector<int>& gates, const vector<int>& fishermen, int index, int total_distance) {
    if (index == 3) {
        min_distance = min(min_distance, total_distance);
        return;
    }

    int gate_pos = gates[index];
    int num_fishermen = fishermen[index];

    for (int mask = 0; mask < (1 << spots.size()); mask++) {
        vector<int> temp_spots = spots;
        int remaining = num_fishermen;
        int distance = 0;
        
        vector<pair<int, int>> candidates;
        for (int i = 0; i < spots.size(); i++) {
            if (temp_spots[i] == 0) {
                candidates.emplace_back(abs(i - gate_pos), i);
            }
        }
        
        sort(candidates.begin(), candidates.end());

        for (auto& [dist, pos] : candidates) {
            if (remaining == 0) break;
            if (temp_spots[pos] == 0) {
                temp_spots[pos] = 1;
                distance += dist + 1;
                remaining--;
            }
        }

        if (remaining == 0) {
            assign_fishing_spots(temp_spots, gates, fishermen, index + 1, total_distance + distance);
        }
    }
}

int min_distance_fishermans_need_to_walk(int number_of_fishing_spots, const vector<int>& gates, const vector<int>& fishermen) {
    min_distance = INT_MAX;
    vector<int> spots(number_of_fishing_spots, 0);
    assign_fishing_spots(spots, gates, fishermen, 0, 0);
    return min_distance;
}

int main() {
    int number_of_fishing_spots;
    cin >> number_of_fishing_spots;

    vector<int> position_of_gates(3), number_of_fishermen_in_each_gate(3);
    for (int i = 0; i < 3; i++) cin >> position_of_gates[i];
    for (int i = 0; i < 3; i++) cin >> number_of_fishermen_in_each_gate[i];

    cout << min_distance_fishermans_need_to_walk(number_of_fishing_spots, position_of_gates, number_of_fishermen_in_each_gate) << endl;

    return 0;
}
