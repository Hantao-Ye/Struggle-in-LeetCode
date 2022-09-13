#include <iostream>
#include <vector>
#include <stack>
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

void print_double(double num, fstream &out_stream)
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
    bool empty = true;
    for (char c : temp)
    {
        if (c == '[')
        {
            continue;
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
        else if (c == ',' || (c == ']' && !empty))
        {
            nums.push_back(temp_num * sign);
            temp_num = 0;
            sign = 1;
        }
        else if (c == ']' && empty)
        {
            break;
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

vector<vector<char>> read_vector_vector_char(fstream &in_stream)
{
    vector<vector<char>> board;

    bool insert = false;
    bool nextLine = true;
    while (nextLine)
    {
        string buffer;
        getline(in_stream, buffer);

        vector<char> line;
        for (char c : buffer)
        {
            if (c == '[')
            {
                insert = true;
            }
            else if (c != ',' && c != ']')
            {
                line.push_back(c);
            }
            else if (c == ',')
            {
                continue;
            }
            else if (c == ']' && insert)
            {
                insert = false;
                board.push_back(line);
                line.clear();
            }
            else if (c == ']' && !insert)
            {
                nextLine = false;
            }
        }
    }

    return board;
}

void print_vector_char(vector<char> strs, fstream &out_stream)
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

void print_vector_vector_char(vector<vector<char>> board, fstream &out_stream)
{
    for (int i = 0; i < board.size(); i++)
    {
        if (i == 0)
        {
            out_stream << '[';
        } else {
            out_stream << ',';
        }

        print_vector_char(board[i], out_stream);
        if (i == board.size() - 1)
        {
            out_stream << ']';
        }
        out_stream << endl;
    }
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

void print_vector_int_k(vector<int> nums, int k, fstream &out_stream)
{
    if (nums.empty())
        out_stream << "[]";

    if (k > nums.size())
        k = nums.size();

    for (int i = 0; i < k; i++)
    {
        if (i == 0)
        {
            out_stream << '[';
        }

        out_stream << nums[i];

        if (i != k - 1)
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
    bool empty = true;

    for (char c : temp)
    {
        if (c == '[')
        {
            continue;
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
        else if (c == ',' || (c == ']' && !empty))
        {
            ptr->next = new ListNode(sign * temp_num);

            ptr = ptr->next;

            temp_num = 0;
            sign = 1;
        }
        else if (c == ']' && empty)
        {
            break;
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
 * @lc app=leetcode id=4 lang=cpp
 *
 * [4] Median of Two Sorted Arrays
 */

// @lc code=start
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();

        if (n1 < n2)
            return findMedianSortedArrays(nums2, nums1);

        int low = 0, high = 2 * n2;
        while (low <= high)
        {
            int mid2 = (low + high) / 2;
            int mid1 = n2 + n1 - mid2;

            double L1 = (mid1 == 0) ? INT32_MIN : nums1[(mid1 - 1) / 2];
            double L2 = (mid2 == 0) ? INT32_MIN : nums2[(mid2 - 1) / 2];
            double R1 = (mid1 == n1 * 2) ? INT32_MAX : nums1[mid1 / 2];
            double R2 = (mid2 == n2 * 2) ? INT32_MAX : nums2[mid2 / 2];
            
            if (L1 > R2)
            {
                low = mid2 + 1;
            } else if (R1 < L2)
            {
                high = mid2 - 1;
            } else
            {
                return (max(L1, L2) + min(R1, R2)) / 2;
            }
        }

        return -1;
    }
};
// @lc code=end

int main()
{
    Solution sol = Solution();

    fstream in_txt("in.txt");
    fstream out_txt("out.txt", ios::out | ios::trunc);

    if (in_txt.is_open() && out_txt.is_open())
    {
        int n = read_int(in_txt);
        for (int i = 0; i < n; i++)
        {
            vector<int> nums1 = read_vector_int(in_txt);
            vector<int> nums2 = read_vector_int(in_txt);

            print_double(sol.findMedianSortedArrays(nums1, nums2), out_txt);

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