#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>

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

void print_int(int num, fstream& out_stream) {
    out_stream << num;
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

void print_vector(vector<int> nums, fstream &out_stream)
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
 * @lc app=leetcode id=7 lang=cpp
 *
 * [7] Reverse Integer
 */

// @lc code=start
class Solution {
public:
    int reverse(int x) {
        if (x == 0 || x == INT32_MIN || x == INT32_MAX)
            return 0;

        int sign = x > 0 ? 1 : -1;
        
        string temp = to_string(x);

        int left = 0, right = temp.size() - 1;
        if (sign == -1)
            left++;

        while (left < right) {
            swap(temp[left], temp[right]);
            left++;
            right--;
        }

        int i = 0;
        if (sign == -1)
            i++;

        while (temp[i] == '0' && i < temp.size())
            i++;
        
        int ans = sign * (temp[i] - '0');
        for (i = i + 1; i < temp.size(); i++) {
            if (sign > 0 && ans > INT32_MAX / 10)
                return 0;
            else if (sign < 0 && ans < INT32_MIN / 10)
                return 0;

            ans = ans * 10 + sign * (temp[i] - '0');
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
            int x = read_int(in_txt);
            print_int(s.reverse(x), out_txt);

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