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
        if (c == '[')
        {
            continue;
        }
        else if (c >= '0' && c <= '9')
        {
            temp_num = temp_num * 10 + c - '0';
        }
        else if (c == '-')
        {
            sign = -1;
        }
        else if (c == ',' || c == ']')
        {
            nums.push_back(temp_num * sign);
            temp_num = 0;
            sign = 1;
        }
    }

    return nums;
}

vector<string> read_vector_string(fstream &in_stream)
{
    vector<string> strs;

    string buffer;
    getline(in_stream, buffer);

    string temp;
    for (char c : buffer)
    {
        if (c == '[')
        {
            continue;
        }
        else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            temp += c;
        }
        else if (c == ',' || c == ']')
        {
            strs.push_back(temp);
            temp = "";
        }
    }

    return strs;
}

void print_vector_string(vector<string> strs, fstream &out_stream)
{
    if (strs.empty())
        out_stream << "[]";

    for (int i = 0; i < strs.size(); i++)
    {
        if (i == 0)
        {
            out_stream << '[';
        }

        out_stream << strs[i];

        if (i != strs.size() - 1)
        {
            out_stream << ',';
        }
        else
        {
            out_stream << ']';
        }
    }
}

void print_vector_int(vector<int> nums, fstream &out_stream)
{
    if (nums.empty())
        out_stream << "[]";
    

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
    if (nums.empty())
        out_stream << "[]";

    for (int i = 0; i < nums.size(); i++)
    {
        if (i == 0)
        {
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
        if (c == '[')
        {
            continue;
        }
        else if (c >= '0' && c <= '9')
        {
            temp_num = temp_num * 10 + c - '0';
        }
        else if (c == '-')
        {
            sign = -1;
        }
        else if (c == ',' || c == ']')
        {
            ptr->next = new ListNode(sign * temp_num);

            ptr = ptr->next;

            temp_num = 0;
            sign = 1;
        }
    }

    return head->next;
}

vector<ListNode *> read_vector_list_node(fstream &in_stream)
{
    string temp;
    getline(in_stream, temp);

    vector<ListNode *> lists;
    ListNode *head, *ptr;

    int temp_num = 0, sign = 1;
    bool insert = false;
    bool empty = true;

    for (char c : temp)
    {
        if (c == '[')
        {
            head = new ListNode();
            ptr = head;

            insert = true;
            empty = true;
        }
        else if (c >= '0' && c <= '9')
        {
            temp_num = temp_num * 10 + c - '0';
            empty = false;
        }
        else if (c == '-')
        {
            sign = -1;
        }
        else if (c == ',' && insert)
        {
            ptr->next = new ListNode(sign * temp_num);

            ptr = ptr->next;

            temp_num = 0;
            sign = 1;
        } 
        else if (c == ']' && empty)
        {
            lists.push_back(head->next);

            temp_num = 0;
            sign = 1;

            insert = false;
        }
        else if (c == ']' && insert)
        {
            ptr->next = new ListNode(sign * temp_num);
            lists.push_back(head->next);

            temp_num = 0;
            sign = 1;

            insert = false;
        }
    }

    return lists;
}

void print_list_node(ListNode *head, fstream &out_stream)
{
    out_stream << '[';
    while (head)
    {
        out_stream << head->val;
        if (head->next)
            out_stream << ',';

        head = head->next;
    }
    out_stream << ']';
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
 * @lc app=leetcode id=18 lang=cpp
 *
 * [18] 4Sum
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        if (nums.size() < 4)
            return ans;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 3; i++) {
            if (target > 0 && nums[i] > target)
                break;

            if (i > 0 && nums[i] == nums[i - 1])
                continue;
                
            for (int j = i + 1; j < nums.size() - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;

                int sum_fix = nums[i] + nums[j];
                int left = j + 1, right = nums.size() - 1;
                while (left < right)
                {
                    int sum_move = nums[left] + nums[right];
                    if ((long) sum_fix + sum_move > target)
                    {
                        right--;
                    } else if ((long) sum_fix + sum_move < target)
                    {
                        left++;
                    } else {
                        ans.push_back({nums[i], nums[j], nums[left], nums[right]});
                        
                        while (left < right && nums[left + 1] == nums[left])
                            left++;

                        while (left < right && nums[right-1] == nums[right])
                            right--;

                        left++;
                        right--;
                    }
                    
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
            int target = read_int(in_txt);

            print_vector_vector_int(s.fourSum(nums, target), out_txt);

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