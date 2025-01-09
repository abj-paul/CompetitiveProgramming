#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    int number_of_spot;
    int gate_position[4];
    int fisherman_number_near_gates[4];
    int starting_position_for_each_fisher_group[4];
    int sum_of_min_distance_for_each_fisher_group[4];
    int suffix_sum_of_fisher_group = 0;
    int ans = INT_MAX;

    cin >> number_of_spot;

    for (int i = 1; i <= 3; i++)
    {
        cin >> gate_position[i];
    }
    for (int i = 1; i <= 3; i++)
    {
        cin >> fisherman_number_near_gates[i];
    }

    for (int i = 3; i >= 1; i--)
    {
        suffix_sum_of_fisher_group += fisherman_number_near_gates[i];
        starting_position_for_each_fisher_group[i] = number_of_spot - suffix_sum_of_fisher_group + 1;
        sum_of_min_distance_for_each_fisher_group[i + 1] = INT_MAX;
    }
    while (starting_position_for_each_fisher_group[1] >= 1)
    {
        for (int i = 3; i >= 1; i--)
        {
            int temporary_sum_of_distance;
            if (starting_position_for_each_fisher_group[i] + fisherman_number_near_gates[i] - 1 < gate_position[i])
            {
                int max_time_needed = gate_position[i] - starting_position_for_each_fisher_group[i] + 1;
                int min_time_needed = gate_position[i] - (starting_position_for_each_fisher_group[i] + fisherman_number_near_gates[i] - 1);

                temporary_sum_of_distance = (max_time_needed * (max_time_needed + 1)) / 2 - (min_time_needed * (min_time_needed + 1)) / 2;
            }
            else if (starting_position_for_each_fisher_group[i] >= gate_position[i])
            {
                int max_time_needed = (starting_position_for_each_fisher_group[i] + fisherman_number_near_gates[i]) - gate_position[i];
                int min_time_needed = starting_position_for_each_fisher_group[i] - gate_position[i];

                temporary_sum_of_distance = (max_time_needed * (max_time_needed + 1)) / 2 - (min_time_needed * (min_time_needed + 1)) / 2;
            }
            else
            {
                int max_time_needed_for_the_left_group = gate_position[i] - starting_position_for_each_fisher_group[i] + 1;
                int max_time_needed_for_the_right_group = (starting_position_for_each_fisher_group[i] + fisherman_number_near_gates[i]) - gate_position[i];

                temporary_sum_of_distance = (max_time_needed_for_the_left_group * (max_time_needed_for_the_left_group + 1)) / 2 + (max_time_needed_for_the_right_group * (max_time_needed_for_the_right_group + 1)) / 2 - 1;
            }
            if (temporary_sum_of_distance < sum_of_min_distance_for_each_fisher_group[i])
            {
                sum_of_min_distance_for_each_fisher_group[i] = temporary_sum_of_distance;
                sum_of_min_distance_for_each_fisher_group[i - 1] = INT_MAX;
            }
            starting_position_for_each_fisher_group[i]--;
        }
        ans = min(ans, sum_of_min_distance_for_each_fisher_group[1] + sum_of_min_distance_for_each_fisher_group[2] + sum_of_min_distance_for_each_fisher_group[3]);
    }
    cout << ans << endl;
}

/*

We are asked to determine the sum of minimum distance for each each group of fisherman behind each gate.

Observation 1:
We must place each fisherman consequtively, otherwise we cannot achieve minimum distance.
For example, if there are 3 fisherman near gate positioned at 4, and we place them like this: (1, 2, 4), then the distance sum is 1+3+4=8
Rather if we place them consecutively like this: (2,3,4), then the sum is 1+2+3=7

Observation 2:
Once we find a position of fishing spot for which the sum of distance is minimum for that group, shifting that group right or left from that spot, won't help us achieve less minimum distance sum that this.
For example, for the previous case, we can find the minimum distance sum like this: (3,4,5), where sum is 2+1+2=5
If we shift this group right/left any further, the sum will just increase. Suppose we shift the group right like this: (4,5,6), the sum is 1+2+3=6

Observation 3:
If a fishergroups last fisherman is placed to the left of that group's gate, then for the first fisherman of that group, it will require maximum distance to travel for them. And for the last fisherman, it will require minimum distance to travel.

Like this we can find min/max distance required, if the group is placed to the right or in between.
We can find the sum of distance using the formula for adding normal numbers from 1 to n.

In this solution, we placed the groups as right as possible initially.

Then we will try to shift them to the left little by little.

Let's see a dry run:
testcase:
10
4 6 10
5 2 2

initial position for each group keeping them as right as possible:
1st group: (2, 3, 4, 5, 6)
2nd group: (7, 8)
3rd group: (9, 10)

Sum for,
3rd group: 2+1=3
2nd group: 2+3=5
1st group: 3+2+1+2+3=11

Total sum: 11+5+3=19

let's shift position to the left by 1 position.
1st group: (1, 2, 3, 4, 5)
2nd group: (6, 7)
3rd group: (8, 9)

Sum for,
3rd group: 3+2=5
2nd group: 1+2=3
1st group: 4+3+2+1+2=12

Notice that we don't want to place the 3rd group to the left further than this cause sum has increased. When we placed them starting from 9, the sum was 3, whereas it was 5 for starting position 8. So we won't change the minimum distance sum for this group anymore.

If we ever see that sum has decreased than the previous position for a particular group, the minimum distance for the previous group has to be resetted, otherwise positioning of two group can be conflicting.

For example, in the initial case, for 2nd group the sum was 5, and for 1st the sum was 11.
But when we saw placing the 2nd group to the left gives sum 3, notice that we resetted the sum for 1st group to INT_MAX and calculated it again. Because if we insist on keeping the sum 11, then 1st group and 2nd group will have conflicting positioning.

*/