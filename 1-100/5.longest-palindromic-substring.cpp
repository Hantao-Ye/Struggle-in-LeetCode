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

void print_int(int num, fstream &out_stream)
{
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
 * @lc app=leetcode id=5 lang=cpp
 *
 * [5] Longest Palindromic Substring
 */

// @lc code=start
class Solution
{
    /**
    If you do the brute force way you would generate a lot more strings than this method looks at.
    which is set of all subsets ( rather substrings) -
    E(sigma) (n-i) as i runs from 1 to n-1 = n-squared + n(n+1)/2 - O(n-squared) complexity.
    This problem can be done using DP with n-squared complexity as shown above by [@GraceMeng](https://leetcode.com/GraceMeng)
    with a few comments below by me based on that
    **/
public:
    string longestPalindrome(string s)
    {
        if (s.length() <= 1)
            return s;

        int len = s.length();
        // dp[i][j] stands for status of a substring starting at i and ending at j incl j
        vector<vector<bool>> dp(len, vector<bool>(len));

        // initialize all the 1 character palins
        for (int i = 0; i < len; i++)
            dp[i][i] = true;

        // to compute dp[i][j] we need dp[i+1][j-1]
        // so the i - outer loop needs to go from higher to lower
        // and the j - inner loop needs to go from lower to higher
        int maxLen = 0, maxSta = 0, maxEnd = 0;
        for (int i = len; i >= 0; i--)
        {
            // dist of 0 - already covered by initialization
            for (int dist = 1; dist < len - i; dist++)
            {
                int j = i + dist;
                // we are ready to compute dp [i] [j]
                if (dist == 1 && s[i] == s[j])
                {
                    dp[i][j] = true;
                }
                else if (s[i] == s[j])
                {
                    dp[i][j] = dp[i + 1][j - 1];
                }
                // if true
                if (dp[i][j] && maxLen < (j - i + 1))
                {
                    maxLen = j - i + 1;
                    maxSta = i;
                    maxEnd = j;
                }
            }
        }
        return s.substr(maxSta, maxEnd - maxSta + 1);
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
            print_string(sol.longestPalindrome(read_string(in_txt)), out_txt);

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