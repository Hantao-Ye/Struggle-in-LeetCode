#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

// @lc code=start
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> um;
        for (int i = 0; i < nums.size(); i++)
        {
            if (um.find(target - nums[i]) != um.end() && um.find(target - nums[i])->second != i)
            {
                return {um.find(target - nums[i])->second, i};
            }
            um.insert({nums[i], i});
        }

        return {-1, -1};
    }
};
// @lc code=end

int main()
{
    Solution s = Solution();

    fstream in_txt("in.txt");
    fstream out_txt("out.txt");

    if (in_txt.is_open() && out_txt.is_open())
    {
        out_txt.clear();

        string temp;
        getline(in_txt, temp);

        int n = stoi(temp);
        for (int i = 0; i < n; i++)
        {
            getline(in_txt, temp);
            vector<int> nums;

            int temp_num = 0;
            for (char c : temp)
            {
                if (c >= '0' && c <= '9')
                {
                    temp_num = temp_num * 10 + c - '0';
                }
                else
                {
                    nums.push_back(temp_num);
                    temp_num = 0;
                }
            }
            nums.push_back(temp_num);

            getline(in_txt, temp);
            int target = stoi(temp);

            vector<int> res = s.twoSum(nums, target);

            out_txt << '[' << res[0] << ',' << res[1] << ']' << endl;
        }

        in_txt.close();
        out_txt.close();
    }
    else
    {
        cout << "File does not open!" << endl;
    }

    return 0;
}