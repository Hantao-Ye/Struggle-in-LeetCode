#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int read_int(fstream &in_stream)
{
    string temp;
    getline(in_stream, temp);

    return stoi(temp);
}

void print_int(int num, fstream &out_stream)
{
    out_stream << num;
}

void print_bool(bool out, fstream &out_stream)
{
    if (out)
        out_stream << "true";
    else
        out_stream << "false";
}

vector<int> read_vector_int(fstream &in_stream)
{
    vector<int> nums;

    string temp;
    getline(in_stream, temp);

    int temp_num = 0, sign = 1;
    for (char c : temp)
    {
        if (c >= '0' && c <= '9')
        {
            temp_num = temp_num * 10 + c - '0';
        }
        else if (c == '-')
        {
            sign = -1;
        }
        else
        {
            nums.push_back(temp_num * sign);
            temp_num = 0;
            sign = 1;
        }
    }
    nums.push_back(temp_num);

    return nums;
}

vector<string> read_vector_string(fstream& in_stream) 
{
    vector<string> strs;

    string buffer;
    getline(in_stream, buffer);

    string temp;
    for (char c : buffer) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            temp += c;
        } else {
            strs.push_back(temp);
            temp = "";
        }
    }
    strs.push_back(temp);

    return strs;
}

void print_vector_int(vector<int> nums, fstream &out_stream)
{
    for (int i = 0; i < nums.size(); i++)
    {
        if (i == 0)
        {
            out_stream << '[';
        }

        out_stream << nums[i];

        if (i != nums.size() - 1)
        {
            out_stream << ',';
        }
        else
        {
            out_stream << ']';
        }
    }
}

void print_vector_vector_int(vector<vector<int>> nums, fstream &out_stream)
{
    for(int i = 0; i < nums.size(); i++)
    {
        if (i == 0) {
            out_stream << '[';
        }

        print_vector_int(nums[i], out_stream);

        if (i != nums.size() - 1)
        {
            out_stream << ',';
        }
        else
        {
            out_stream << ']';
        }
    }
}

ListNode *read_list_node(fstream &in_stream)
{
    string temp;
    getline(in_stream, temp);

    ListNode *head = new ListNode();
    ListNode *ptr = head;

    int temp_num = 0, sign = 1;
    for (char c : temp)
    {
        if (c >= '0' && c <= '9')
        {
            temp_num = temp_num * 10 + c - '0';
        }
        else if (c == '-')
        {
            sign = -1;
        }
        else
        {
            ptr->next = new ListNode(sign * temp_num);

            ptr = ptr->next;

            temp_num = 0;
            sign = 1;
        }
    }
    ptr->next = new ListNode(temp_num);

    return head->next;
}

void print_list_node(ListNode *head, fstream &out_stream)
{
    out_stream << '[';
    while (head->next)
    {
        out_stream << head->val << ',';
        head = head->next;
    }
    out_stream << head->val << ']';
}

string read_string(fstream &in_stream)
{
    string temp;

    getline(in_stream, temp);

    return temp;
}

void print_string(string str, fstream &out_stream)
{
    out_stream << str;
}
/*
 * @lc app=leetcode id=15 lang=cpp
 *
 * [15] 3Sum
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;


        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            if (nums[i] > 0)
                break;

            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum > 0) {
                    right --;
                } else if (sum < 0) {
                    left++;
                } else if (sum == 0) {
                    ans.push_back({nums[i], nums[left], nums[right]});

                    while (left < right && nums[right - 1] == nums[right])
                        right--;

                    while (left < right && nums[left + 1] == nums[left]) {
                        left++;
                    }

                    right--;
                    left++;
                }
            }

        }

        return ans;
    }
};
// @lc code=end

int main()
{
    Solution s = Solution();

    fstream in_txt("in.txt");
    fstream out_txt("out.txt", ios::out | ios::trunc);

    if (in_txt.is_open() && out_txt.is_open())
    {
        int n = read_int(in_txt);
        for (int i = 0; i < n; i++)
        {
            vector<int> nums = read_vector_int(in_txt);
            print_vector_vector_int(s.threeSum(nums), out_txt);

            if (i != n - 1)
            {
                out_txt << endl;
            }
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