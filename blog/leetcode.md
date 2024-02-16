记录作者在刷题时遇到的问题和一些解题思路。会尽量使用到标准库算法。

1.两数之和

给定一个整数数组 `nums` 和一个整数目标值 `target`，请你在该数组中找出 **和为目标值** *`target`* 的那 **两个** 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

```C++
//这是用哈希表，别人写的，贴在这里，希望作者能早日弄懂哈希表
class Solution {
public:
    
     vector<int> twoSum(vector<int>& nums, int target) 
    {
        std::unordered_map<int, int> hash;
        for(int i = 0; i < nums.size(); i++)
        {
            auto iter = hash.find(target - nums[i]);
            if(iter != hash.end())
            {
                return {i, iter->second};
            }
            else
            {
                hash.insert(pair<int, int>(nums[i], i));
            }
        }
        return {};
    } 
};
```

2.两数相加

给你两个 **非空** 的链表，表示两个非负的整数。它们每位数字都是按照 **逆序** 的方式存储的，并且每个节点只能存储 **一位** 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。



思路：将各个位数分别相加，考虑进位即可。

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *end1 = l1,*end2 = l2;
        int i = 1,j = 1,k=0,m=0;
        int sum1=0,sum2=0,sum=0;
        while(end1->next!=NULL){
            i++;
            end1 = end1->next;
        }
        while(end2->next!=NULL){
            j++;
            end2 = end2->next;
        }
        if(i>j)
        {
            m=i-j;
            while(m!=0)
            {
                end2->next = new ListNode(0);
                end2 = end2->next;
                m--;
            } 
        }
        else
        {
            m=j-i;
            while(m!=0)
            {
                end1->next = new ListNode(0);
                end1 = end1->next;
                m--;
            }
        }
        ListNode *p = new ListNode(-1);
        ListNode *q = p;
        int count = 0;     
        while(l1!=NULL && l2!=NULL )
        {
            k = count + l1->val + l2->val;
            q->next = new ListNode(k%10);
            if(k>=10)
                count = 1;
            else
                count = 0;
            q = q->next;
            l1 =l1->next;
            l2 = l2->next; 
        }
        if(count == 1)
        {
            q->next = new ListNode(1);
            q = q->next;
        }
        return p->next;
    }
};
```

3.无重复字符的最长子串

给定一个字符串 `s` ，请你找出其中不含有重复字符的 **最长子串** 的长度。



思路：由于子串是连在一起的，所以我们可以使用滑动窗口来遍历一个字符串的所有子串。

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        string str = "",max_str = "";
        for(auto a : s){
            str += a;
            for(int i = 0;i!=str.size()-1;i++){
                if(str.at(i)==a)
                {
                    str.erase(str.begin(),str.begin()+i+1);
                    break;
                }
            }
            if(str.size()>max_str.size())
            {
                max_str = str;
            }
        }
        return max_str.size();
    }
};
```

4.寻找两个正序数组的中位数

给定两个大小分别为 `m` 和 `n` 的正序（从小到大）数组 `nums1` 和 `nums2`。请你找出并返回这两个正序数组的 **中位数** 。

算法的时间复杂度应该为 `O(log (m+n))` 。

```c++
//这个时间复杂度达不到要求
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> nums3;
        if(nums1.size()>=nums2.size())
        {
            int i = 0;
            for(;i!=nums2.size();i++)
            {
                nums3.push_back(nums1[i]);
                nums3.push_back(nums2[i]);

            }
            for(;i!=nums1.size();i++)
                nums3.push_back(nums1[i]);

        }
        else
        {
            int i = 0;
            for(;i!=nums1.size();i++)
            {
                nums3.push_back(nums1[i]);
                nums3.push_back(nums2[i]);

            }
            for(;i!=nums2.size();i++)
                nums3.push_back(nums2[i]);
        }
        sort(nums3.begin(),nums3.end());
        int n1 = (nums3.size()+1)/2;
        int n2 = (nums3.size()+2)/2;
        double zhong = (double)(nums3.at(n1-1)+nums3.at(n2-1))/2;
        return zhong;
    }
};
```

5.最长回文子串

给你一个字符串 `s`，找到 `s` 中最长的回文子串。



思路：回文数的特点时对称，对称有对称点。我们设该回文数的中点是left和right，开始时left==right,如果中点是两个数则right右移。在不超过界限的情况下，如果right的下一个数与left的上一个数相等，则left左移，right右移。循环过后得到中心点在left.right初始值的最大回文数。将left.right的初始值在整个字符串移动，就得到最长回文子串。

```c++
class Solution {
public:
    string longestPalindrome(string s) {
    int left = 0,right = 0;
    int i = 0,j = 0;
    int max =0,index =0;
    for(;i!=s.size();++i)
    {
        j = i;
        //防止重复，例如"bb"
        while(j!=s.size()-1 && s[j+1]==s[i])
        {
            j++;
        }

        left = i;
        right = j;

        while(left!=0 && right!=s.size()-1 && s[left-1]==s[right+1])
        {
            left--;
            right++;
        }
        if((right-left+1)>max)
        {
            max = right-left+1;
            index = left;
        }
    }
    return s.substr(index,max);
}

};
```

6.整数反转

给你一个 32 位的有符号整数 `x` ，返回将 `x` 中的数字部分反转后的结果。

如果反转后整数超过 32 位的有符号整数的范围 `[−231, 231 − 1]` ，就返回 0。

**假设环境不允许存储 64 位整数（有符号或无符号）。**



思路：将整数变为string再由reverse函数进行反转

```c++
class Solution {
public:
    int reverse(int x) {
        int sign=1;
        if(x==INT_MIN)
            return 0;
        if(x<0)
        {
            x = -x;
            sign=-1;
        }
        std::string rev =  to_string(x);
        std::reverse(rev.begin(),rev.end());
        if(rev.size()>9)
        {
            string max = to_string(INT_MAX);
            if(rev>max)
            return 0;
        }
        int y = atoi(rev.c_str());
        return sign*y;
    }
};
```

7.字符串的排列

给你两个字符串 `s1` 和 `s2` ，写一个函数来判断 `s2` 是否包含 `s1` 的排列。如果是，返回 `true` ；否则，返回 `false` 。

换句话说，`s1` 的排列之一是 `s2` 的 **子串** 。



思路：判断s2中和s1一样长的子串的字母出现的次数是否与s1一样多。

```c++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int left = 0,right = s1.size()-1;
        if(s1.size()>s2.size())
            return false;
        vector<int> a(26),b(26);
        for(int i = 0;i!=s1.size();++i)
        {
            a[s1[i]-'a']++;  
            b[s2[i]-'a']++;
        }
        if(a==b)
            return true;
        for(;left!=s2.size()-s1.size()+1;++left)
        {
            right = left+s1.size()-1;
            for(int i = left ;i!=right+1;++i)
            {
                b[s2[i]-'a']++;
            }       
            if(a==b)
                return true;
            for(int i =0;i!=26;++i)
            {
                b[i]=0;
            }

        }
        return false;       
    }
};
```

8.回文数

给你一个整数 `x` ，如果 `x` 是一个回文整数，返回 `true` ；否则，返回 `false` 。

回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

- 例如，`121` 是回文，而 `123` 不是。

```c++
class Solution {
public:
    bool isPalindrome(int x) {
    string s1 = to_string(x);
    string s2 = s1;
    reverse(s1.begin(),s1.end());  //reverse函数没有返回值
    if(s1==s2)
        return true;
    return false;
    }
};
```

9.盛最多水的容器

给定一个长度为 `n` 的整数数组 `height` 。有 `n` 条垂线，第 `i` 条线的两个端点是 `(i, 0)` 和 `(i, height[i])` 。

找出其中的两条线，使得它们与 `x` 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

**说明：**你不能倾斜容器。



思想：双指针。将left,right指针分别置于0和size-1的位置。因为向内移动短板有可能能装更多水，向内移动长板只能装更少水。所以我们不断移动短板，并将当前值与最大值比较即可。

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0,right = height.size()-1;
        int area = min(height[left],height[right])*(right-left);
        int max = area;
        while(left<right)
        {
            if(height[left]<=height[right])
            {
                left++;
            }
            else if(height[right]<height[left])
            {
                right--;
            }
            area = min(height[left],height[right])*(right-left);
            if(area > max)
                max = area;
        }
        return max;
    }
};
```

9.整数转罗马数字

罗马数字包含以下七种字符： `I`， `V`， `X`， `L`，`C`，`D` 和 `M`。

```
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

例如， 罗马数字 2 写做 `II` ，即为两个并列的 1。12 写做 `XII` ，即为 `X` + `II` 。 27 写做 `XXVII`, 即为 `XX` + `V` + `II` 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 `IIII`，而是 `IV`。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 `IX`。这个特殊的规则只适用于以下六种情况：

- `I` 可以放在 `V` (5) 和 `X` (10) 的左边，来表示 4 和 9。
- `X` 可以放在 `L` (50) 和 `C` (100) 的左边，来表示 40 和 90。 
- `C` 可以放在 `D` (500) 和 `M` (1000) 的左边，来表示 400 和 900。

给你一个整数，将其转为罗马数字。



思想：将每个位数有9,4的数单独表示，然后再加上多少个该位的“1”。

```C++
//暴力算法
class Solution {
public:
    string intToRoman(int num) {
    int qianwei = num/1000;
    string luoma = "";
    for(int i =0;i!=qianwei ;++i)
        luoma += "M";
        
    int a = num%1000;
    int baiwei = a/100;
    if(baiwei >= 5)
    {
        if(baiwei == 9)
            luoma += "CM";
        else
            luoma += "D";  
    }
    else
    {
        if(baiwei == 4)
            luoma += "CD" ;  
    }
    if(baiwei != 9 && baiwei !=4)
        for(int count = baiwei>=5?(baiwei-5):baiwei;count!=0;count--)
        luoma += "C";
  

  
    
    int b = a%100;
    int shiwei = b/10;
    if(shiwei >= 5)
    {
        if(shiwei == 9)
            luoma += "XC";
        else
            luoma += "L";  
    }
    else
    {
        if(shiwei == 4)
            luoma += "XL" ;  
    }
    if(shiwei != 9 && shiwei !=4)
        for(int count = (shiwei>=5)?(shiwei-5):shiwei;count!=0;count--)
         luoma += "X";
  
    int c = b%10;
    int gewei = c/1;
    if(gewei >= 5)
    {
        if(gewei == 9)
            luoma += "IX";
        else
            luoma += "V";  
    }
    else
    {
        if(gewei == 4)
            luoma += "IV" ;  
    }
    if(gewei != 9 && gewei !=4)
        for(int count = gewei>=5?(gewei-5) : gewei;count!=0;count--)
            luoma += "I";
    return luoma;
        
        
    }
};
```



思路：与上面没有本质的不同，暴力创建了每个位数的可能值，相加即可。

```C++
class Solution {
public:
    string intToRoman(int num) {
        string s[4][9] ={{"I","II","III","IV","V","VI","VII","VIII","IX"},
                                  				              {"X","XX","XXX","XL","L","LX","LXX","LXXX","XC"},
                                  {"C","CC","CCC","CD","D","DC","DCC","DCCC","CM"},
                                  {"M","MM","MMM"}};
        int count = 3,beishu=1000;
        string luoma = "";
        while(num > 0)
        {
            int a = num/beishu;
            if(a>0)
                luoma += s[count][a-1];
            count--;
            num %= beishu;
            beishu /= 10;
        }
        return luoma;  
                   
    }
};
```

10.罗马数字转整数

罗马数字包含以下七种字符: `I`， `V`， `X`， `L`，`C`，`D` 和 `M`。

```
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

例如， 罗马数字 `2` 写做 `II` ，即为两个并列的 1 。`12` 写做 `XII` ，即为 `X` + `II` 。 `27` 写做 `XXVII`, 即为 `XX` + `V` + `II` 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 `IIII`，而是 `IV`。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 `IX`。这个特殊的规则只适用于以下六种情况：

- `I` 可以放在 `V` (5) 和 `X` (10) 的左边，来表示 4 和 9。
- `X` 可以放在 `L` (50) 和 `C` (100) 的左边，来表示 40 和 90。 
- `C` 可以放在 `D` (500) 和 `M` (1000) 的左边，来表示 400 和 900。

给定一个罗马数字，将其转换成整数。



思路：用map记录罗马数字和阿拉伯数字的对应关系。特殊情况下，小的数字在大的数字前面，使用含两个字符的滑动窗口，如果是特殊情况则加对应的值并向后滑两个字符，如果是通常情况则加map对应的值并向后滑动一个字符。

```c++
class Solution {
public:
    int romanToInt(string s) {
        int sum = 0;
        string s1 = "";
        map<string,int> map={{"I",1},{"V",5},{"X",10},{"L",50},{"C",100},{"D",500},{"M",1000}    
                            };
        for(int i=0;i!=s.size();++i)
        {
            s1.push_back(s[i]);
            s1.push_back(s[i+1]);
            if(s1=="IV"){
                 sum += 4;
                 i++;
            } 
            else if(s1=="IX"){
                 sum += 9;
                 i++;
            }        
            else if(s1=="XL"){
                sum += 40;
                i++;
            }               
            else if(s1=="XC"){
                sum += 90;
                i++;
            }   
            else if(s1=="CD"){
                sum += 400;
                i++;
            }    
            else if(s1=="CM"){
                sum += 900;
                i++;
            }
            else{
                string s2 = "";
                s2.push_back(s[i]);
                sum += map[s2];
            }  
            s1 = "";         
        }
    return sum;
    }
};
```

11.最长公共前缀

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 `""`。



思路：将string数组的每一个元素的第i个字符与第一个字符相比较。记录下相同部分。

```c++
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int len = strs[0].size();
        string s = "";
        if(strs.size()==1)
            return strs[0];
        else if(strs.size()==0)
            return s;      
        for(auto i : strs)
        {
            if(len > i.size())
                len = i.size();
        }
        int i,j;
        for(j = 0;j != len;++j)
        {
            
            for(i = 1;i != strs.size();++i)
            {
                if(strs[i][j] !=strs[0][j])
                    return s;
            }
            s.push_back(strs[0][j]);
        }
        return s;
    }
};
```

12.回文数

给你一个整数 `x` ，如果 `x` 是一个回文整数，返回 `true` ；否则，返回 `false` 。

回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

- 例如，`121` 是回文，而 `123` 不是。



思路：把int转成string，再用reverse函数。

```c++
class Solution {
public:
    bool isPalindrome(int x) {
    string s1 = to_string(x);
    string s2 = s1;
    reverse(s1.begin(),s1.end());
    if(s1==s2)
        return true;
    return false;
    }
};
```

13.三数之和

给你一个包含 `n` 个整数的数组 `nums`，判断 `nums` 中是否存在三个元素 *a，b，c ，*使得 *a + b + c =* 0 ？请你找出所有和为 `0` 且不重复的三元组。

**注意：**答案中不可以包含重复的三元组。



思想：排序加双指针。

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> v;
        int left = 0,right = 0,temp = 0;
        if(nums.size() < 3)
            return v;
        sort(nums.begin(),nums.end());

        for(int i = 0;i != nums.size()-2;++i)
        {
            if(nums[i]>0) return v;
            if(i> 0 && nums[i]==nums[i-1]) continue;
            
            left = i + 1;
            right = nums.size()-1;
            while(left<right)
            {
                temp = nums[i]+nums[left]+nums[right];
                if(temp==0)
                {
                    v.push_back(vector<int>{nums[i],nums[left],nums[right]});
                    while(left <right && nums[left]==nums[left+1])
                    {
                        left++;
                    }
                    while(right < right && nums[right]==nums[right-1])
                    {
                        right--;
                    }
                    left++;
                    right--;
                }
                else if(temp<0)
                {
                    left++;
                }
                else if(temp>0)
                {
                    right--;
                }
             }
        }
        return v;     
    }
};
```





14.最接近的三数之和

给你一个长度为 `n` 的整数数组 `nums` 和 一个目标值 `target`。请你从 `nums` 中选出三个整数，使它们的和与 `target` 最接近。

返回这三个数的和。

假定每组输入只存在恰好一个解。



思路：排序+双指针

```c++
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int sum = nums[0]+nums[1]+nums[nums.size()-1];
        int left,right,temp;
        if(sum==target)
            return sum;
        for(int i = 0;i != nums.size()-2;i++)
        {
            left = i + 1;
            right = nums.size()-1;
            while(left != right)
            {
                temp = nums[i]+nums[left]+nums[right];
                if(temp < target)
                {              
                    left++;             
                }
                else if(temp > target)
                { 
                    right--;   
                } 
                else
                    return temp;   
                if(abs(target-temp) < abs(target-sum) )
                sum = temp;       
            }
           
        }
        return sum;
    }
};
```

15.电话号码的字母组合

给定一个仅包含数字 `2-9` 的字符串，返回所有它能表示的字母组合。答案可以按 **任意顺序** 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。



思路：这就是一个排列组合的问题。解决排列组合用到回溯。

```c++
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.size()==0)
            return {};
        unordered_map<char,string> hash = {{'2',"abc"},{'3',"def"},{'4',"ghi"},
                                            {'5',"jkl"},{'6',"mno"},{'7',"pqrs"},
                                            {'8',"tuv"},{'9',"wxyz"}};
        vector<string> v;
        string s;
        int index = 0;
        pailiezuhe(v,digits,s,hash,index);
        return v;   
    }

    void pailiezuhe(vector<string> &v,const string &digits,string &s,                  unordered_map<char,string> &hash,int index)
    {
        if(index == digits.size())
            v.push_back(s);
        else
        {
            char digit = digits[index];
            string temp = hash[digit];
            for(auto i : temp)
            {
                s.push_back(i);
                pailiezuhe(v,digits,s,hash,index+1);
                s.pop_back();
            }
        }
    }
};
```

16.四数之和

给你一个由 `n` 个整数组成的数组 `nums` ，和一个目标值 `target` 。请你找出并返回满足下述全部条件且**不重复**的四元组 `[nums[a], nums[b], nums[c], nums[d]]` （若两个四元组元素一一对应，则认为两个四元组重复）：

- `0 <= a, b, c, d < n`
- `a`、`b`、`c` 和 `d` **互不相同**
- `nums[a] + nums[b] + nums[c] + nums[d] == target`

你可以按 **任意顺序** 返回答案 。

思路：和三数之和类似，排序加双指针。注意去除重复。

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if(nums.size() < 4)
            return {};
        sort(nums.begin(),nums.end());
        int left,right;
        long long temp = 0;
        vector<vector<int>> v;
        for(int i = 0;i != nums.size()-3;++i)
        {
           if(i>0 && nums[i]==nums[i-1])
            continue;
            for(int j = i + 1;j != nums.size()-2;++j)
            {
                if(j>i+1 && nums[j]==nums[j-1]) 
                    continue;
                left = j + 1;
                right = nums.size()-1;
                while(left < right)
                {
                    if(nums[i]+nums[j] < target-(nums[left]+nums[right]))
                        left++;
                    else if(nums[i]+nums[j] > target-(nums[left]+nums[right]))
                        right--;
                    else
                    {
                        v.push_back({nums[i],nums[j],nums[left],nums[right]});
                        while(left < right && nums[left]==nums[left+1])
                            left++;
                        while(left < right && nums[right]==nums[right-1])
                            right--;
                        left++;
                        right--;
                    }
                }  
            }
        }
        return v;
    }
};
```

17.删除链表的倒数第n个节点

给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。



思路：注意删除头节点的情况即可。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *p = head,*temp = nullptr;
        int num = 0;
        while(p!=nullptr)
        {
            num++;
            p = p->next;
        }
        if(num == 1)
            return nullptr;
        int i = num - n -1;   
        p = head;
        while(p!=nullptr && i>0)
        {
            i--;
            p = p->next;
        }
        if(i < 0)
            return p->next;
        //temp = p->next;
        if(p->next)
            p->next = p->next->next;
        //free(temp);      //不需要手动free了，上面的ListNode会做delete
        return head;
    }
};
```

18.有效的括号

给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s` ，判断字符串是否有效。

有效字符串需满足：

1. 左括号必须用相同类型的右括号闭合。
2. 左括号必须以正确的顺序闭合。

 

思路:使用栈来进行操作。

```c++
class Solution {
public:
    bool isValid(string s) {
        if(s.size()%2==1)
            return false;
        string s1;  //防止s1.back()访问到s1的边界外
        for(int i = 0;i<s.size();i++)
        {
            switch(s[i]){
                case '(':
                    s1.push_back('(');
                    break;
                case '[':
                    s1.push_back('[');
                    break;
                case '{':
                    s1.push_back('{');
                    break;
                case ')':
                    if(s1.back()!='(')
                        return false;
                    s1.pop_back();
                    break;
                case ']':
                    if(s1.back()!='[')
                        return false;
                    s1.pop_back();
                    break;
                case '}':
                    if(s1.back()!='{')
                        return false;
                    s1.pop_back();
                    break;
            }
        }
        if(s1.empty()!=true && (s1.back()=='(' || s1.back()=='[' || s1.back()=='{'))
                return false;
        return true;
    }
};
```

19.合并两个有序链表

将两个升序链表合并为一个新的 **升序** 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。



思路：下面是使用原有节点进行合并。创建新节点的方法在我的Leetcode也有

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *list3 = new ListNode();
        ListNode *temp = list3;
        temp->next = nullptr;
        ListNode *p = list1,*q = list2;
        if(p==nullptr)
        {
            return q;
        }
        else if(q==nullptr)
        {
            return p;
        }
        while(p != nullptr && q != nullptr)
        {
            if(p->val < q->val )
            {
                ListNode *pnext = new ListNode();
                pnext->val = p->val;
                temp->next = pnext;
                temp = temp->next;
                p = p->next;
            }
            else if(p->val > q->val )
            {
                ListNode *qnext = new ListNode();
                qnext->val = q->val;
                temp->next = qnext;
                temp = temp->next;
                q = q->next;
            }
            else if(p->val == q->val)
            {
                ListNode *pnext = new ListNode();
                ListNode *qnext = new ListNode();
                pnext->val = p->val;
                qnext->val = q->val;
                temp->next = pnext;
                temp = temp->next;
                temp->next = qnext;
                temp = temp->next;
                p = p->next;
                q = q->next;
            }

        }
        if(p==nullptr)
        {
            temp->next = q;
        }
        else if(q==nullptr)
        {
            temp->next = p;
        }
        return list3->next;    
    }
};
```

20.括号生成

数字 `n` 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 **有效的** 括号组合。

 思路：深度遍历。这种题目遇到的很少，多看看。***

```c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {
    
        vector<string> v;
        dfs(n,0,0,"",v);
        return v;
    }
    void dfs(int n,int l,int r,string s,vector<string> &v)
    {
        if(l==n && r==n)
        {
            v.push_back(s);      
        }
        else
        {
            if(l < n)
            {
                dfs(n,l+1,r,s+"(",v);
            }
            if(r<n && r<l)
            { 
                dfs(n,l,r+1,s+")",v);
            }
        }
    }
};
```

21.两两交换链表中的节点

给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

思路：正常交换即可，注意头节点是有数据的，交换后的头节点不是原来的头节点。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head==nullptr || head->next==nullptr)
            return head;
        ListNode *p = head,*q = head->next;
        ListNode *phead = q;
        ListNode *temp = new ListNode();
        while(p != nullptr && q != nullptr)
        {
            temp->next = p;
            p->next = q->next;
            q->next = p;
            if(temp->next != nullptr)
                temp->next = q;
            temp = p;
            p = p->next;
            if(p != nullptr)
                q = p->next;
       }
        return phead;
    }
};
```

21.删除有序数组中的重复项

给你一个 **升序排列** 的数组 `nums` ，请你**[ 原地](http://baike.baidu.com/item/原地算法)** 删除重复出现的元素，使每个元素 **只出现一次** ，返回删除后数组的新长度。元素的 **相对顺序** 应该保持 **一致** 。

由于在某些语言中不能改变数组的长度，所以必须将结果放在数组nums的第一部分。更规范地说，如果在删除重复项之后有 `k` 个元素，那么 `nums` 的前 `k` 个元素应该保存最终结果。

将最终结果插入 `nums` 的前 `k` 个位置后返回 `k` 。

不要使用额外的空间，你必须在 **[原地 ](https://baike.baidu.com/item/原地算法)修改输入数组** 并在使用 O(1) 额外空间的条件下完成。



思路：标准库函数unique就是干这事的，直接用。

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
       auto end_unique = unique(nums.begin(),nums.end());
       int k = 0;
       auto i = nums.begin();
       while(i != end_unique)
       {
           k++;
           i++;
       }
       return k;
    }
};
```

22. 移除元素

给你一个数组 `nums` 和一个值 `val`，你需要 **[原地](https://baike.baidu.com/item/原地算法)** 移除所有数值等于 `val` 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 `O(1)` 额外空间并 **[原地 ](https://baike.baidu.com/item/原地算法)修改输入数组**。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。



思路：还是用标准库，排序后删除即可。

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        sort(nums.begin(),nums.end());
        auto i = find(nums.begin(),nums.end(),val);
        while(i!=nums.end() && *i == val )
        {
            i++;
            nums.erase(--i);
            
        }
        return nums.size();
    }
};
```

28.实现strStr()

实现 [strStr()](https://baike.baidu.com/item/strstr/811469) 函数。

给你两个字符串 `haystack` 和 `needle` ，请你在 `haystack` 字符串中找出 `needle` 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回 `-1` 。

**说明：**

当 `needle` 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

对于本题而言，当 `needle` 是空字符串时我们应当返回 0 。这与 C 语言的 [strstr()](https://baike.baidu.com/item/strstr/811469) 以及 Java 的 [indexOf()](https://docs.oracle.com/javase/7/docs/api/java/lang/String.html#indexOf(java.lang.String)) 定义相符。

 思路：使用string的find函数。不用非成员版本的find函数的原因是，它返回迭代器。而string的find函数返回下标，更简单。

```c++
class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.size()==0)
            return 0;
        if(haystack.size()==0)
            return -1;
        return haystack.find(needle);
    }
};
```

29.两数相除

给定两个整数，被除数 `dividend` 和除数 `divisor`。将两数相除，要求不使用乘法、除法和 mod 运算符。

返回被除数 `dividend` 除以除数 `divisor` 得到的商。

整数除法的结果应当截去（`truncate`）其小数部分，例如：`truncate(8.345) = 8` 以及 `truncate(-2.7335) = -2`

思路：使用递归。主要思想在递归函数中。注意:32位整型的范围，负数比正数范围大，采用long long来避免溢出。

```c++
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(divisor == 1)
            return dividend;
        if(divisor == -1)
        {
            if(dividend == INT_MIN)
                return INT_MAX;
            else
                return -dividend;
        }
        int sign = 1;
        if(dividend < 0)
            sign = -sign;
        if(divisor < 0)
            sign = -sign; 
        long long a = dividend;
        long long b = divisor;    
        a = a > 0 ? a : -a;
        b = b > 0 ? b : -b;
        if(sign== -1)
            return -div(a,b);
        return div(a,b);
      
    }

    int  div(long long a,long long b)
    {
        if(a < b)
            return 0;
        long long tb = b;
        int count = 1;
        while((tb+tb) <= a)
        {
            count += count;
            tb += tb;
        }
        return count+div(a-tb,b);
    }
};
```

30.搜索旋转排序数组

整数数组 `nums` 按升序排列，数组中的值 **互不相同** 。

在传递给函数之前，`nums` 在预先未知的某个下标 `k`（`0 <= k < nums.length`）上进行了 **旋转**，使数组变为 `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]`（下标 **从 0 开始** 计数）。例如， `[0,1,2,4,5,6,7]` 在下标 `3` 处经旋转后可能变为 `[4,5,6,7,0,1,2]` 。

给你 **旋转后** 的数组 `nums` 和一个整数 `target` ，如果 `nums` 中存在这个目标值 `target` ，则返回它的下标，否则返回 `-1` 。

思路：这是一个旋转过后的数组，但我没考虑它是否旋转。直接用标准库函数find找到它。速度上也超过了70%的用户，我觉得能用标准库函数就用标准库函数吧，挺快的，又方便。

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto i = find(nums.begin(),nums.end(),target);
        int num = 0;
        auto j = nums.begin();
        if(i == nums.end())
            return -1;
        while(j != i)
        {
            j++;
            num++;
        }
        return num;
    }
};
```

31.在排序数组中查找元素的第一个和最后一个位置

给定一个按照升序排列的整数数组 `nums`，和一个目标值 `target`。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 `target`，返回 `[-1, -1]`。

思想：用标准库算法。

```c++
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto i = find(nums.begin(),nums.end(),target);
        if(i == nums.end())
            return {-1,-1};
        int num = 0,first = 0,last = 0;
        auto j = nums.begin();
        while(j != i)
        {
            j++;
            num++;
        }
        first = num;
        while(i != nums.end() && *i == target)
        {
            i++;
            num++;
        }
        last = num-1;
        return {first,last};
    }
};
```

32.搜索插入位置

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

思路：标准库算法find_if+lambda，找到第一个大于等于tatget的位置，根据返回的迭代器得到下标即可。

```c++
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        auto i = find_if(nums.begin(),nums.end(),
                [target](int k){return k >= target;});
        int num = 0;        
        auto j = nums.begin();
        while(j != nums.end() && j != i)
        {
            j++;
            num++;
        }
        return num;
    }
};
```

33.有效的数独

请你判断一个 `9 x 9` 的数独是否有效。只需要 **根据以下规则** ，验证已经填入的数字是否有效即可。

1. 数字 `1-9` 在每一行只能出现一次。
2. 数字 `1-9` 在每一列只能出现一次。
3. 数字 `1-9` 在每一个以粗实线分隔的 `3x3` 宫内只能出现一次。（请参考示例图）

**注意：**

- 一个有效的数独（部分已被填充）不一定是可解的。
- 只需要根据以上规则，验证已经填入的数字是否有效即可。
- 空白格用 `'.'` 表示。

思路：暴力检验每一行、每一列、每一九宫格是否1-9分别只出现一次

```c++
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        map<char,int> map = {{'1',0},{'2',0},{'3',0},{'4',0},{'5',0},{'6',0},{'7',0},
                                      {'8',0},{'9',0}};
        for(int i = 0;i != 9;i++)
        {
            for(int j = 0;j != 9;j++)
            {
                if(board[i][j] != '.')
                {
                    map[board[i][j]]++;
                }
            }
            for(auto i = map.begin();i != map.end();++i)
            {
                if(i->second > 1)
                    return false;
                i->second = 0;
            }
        }
        // 判断每一列是否合格   
        for(int i = 0;i != 9;i++) //这里的i是列，j是行
        {
            for(int j = 0;j != 9; j++)
            {
                if(board[j][i] != '.')
                {
                    map[board[j][i]]++;
                }
            }
            for(auto i = map.begin();i != map.end();++i)
            {
                if(i->second > 1)
                    return false;
                i->second = 0;
            }     
        }
        //判断每一个九宫格是否合格
        for(int h = 0;h < 9 ;h+=3)
        {
            for(int l = 0;l < 9;l+=3)
            {
               for(int ii = 0;ii < 3;ii++)
               {
                   for(int jj = 0;jj < 3;jj++)
                   {
                        if(board[h+ii][l+jj] != '.')
                        {
                            map[board[h+ii][l+jj]]++;   
                        }
                   }
               } 
               for(auto i = map.begin();i != map.end();++i)
                {
                    if(i->second > 1)
                        return false;
                    i->second = 0;
                }   
            }
        }
        return true;             
    }
};
```

34.组合总和

给你一个 **无重复元素** 的整数数组 `candidates` 和一个目标整数 `target` ，找出 `candidates` 中可以使数字和为目标数 `target` 的 *所有* **不同组合** ，并以列表形式返回。你可以按 **任意顺序** 返回这些组合。

`candidates` 中的 **同一个** 数字可以 **无限制重复被选取** 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 `target` 的不同组合数少于 `150` 个。

 思路：用回溯，将target-candidate[i]再次当一个新的target放入dfs中

```c++
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> temp;
        sort(candidates.begin(),candidates.end());
        dfs(candidates,target,res,temp,0);
        return res;

    }
    void dfs(vector<int>& candidates, int target,vector<vector<int>>& res,vector<int>& temp,int num)
    {
        if(target == 0)
            res.push_back(temp);
        else if(target > 0)
        {
            for(int i = num;i < candidates.size();i++)
            {
                temp.push_back(candidates[i]);
                dfs(candidates,target-candidates[i],res,temp,i);
                temp.pop_back();
            }
        }
    }

};
```

35.组合总和2

给定一个候选人编号的集合 `candidates` 和一个目标数 `target` ，找出 `candidates` 中所有可以使数字和为 `target` 的组合。

`candidates` 中的每个数字在每个组合中只能使用 **一次** 。

**注意：**解集不能包含重复的组合。

思路：大致与上题相同，注意避免重复使用的情况。注意：vector<int>::size_type实际上是一种unsigned类型。

```c++
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> temp;
        sort(candidates.begin(),candidates.end());
        dfs(candidates,target,res,temp,0);
        return res;

    }
    void dfs(vector<int>& candidates, int target,vector<vector<int>>& res,vector<int>& temp,int num)
    {
        if(target == 0)
            res.push_back(temp);
        else if(target > 0)
        {
            for(int i = num;i < candidates.size();i++)
            {
                temp.push_back(candidates[i]);
                dfs(candidates,target-candidates[i],res,temp,i+1);
                temp.pop_back();
                if(i == int(candidates.size()-1))
                    return ;
                while(i < int(candidates.size()-1) && candidates.at(i) == candidates.at(i+1))
                    i++;
            }
        }
    }

};
```

36.缺失的第一个正数

给你一个未排序的整数数组 `nums` ，请你找出其中没有出现的最小的正整数。

请你实现时间复杂度为 `O(n)` 并且只使用常数级别额外空间的解决方案。

思路：因为是连续的正数，用sort排序后用find找到1的位置，从一开始用k跟着迭代器计数，缺失啥就返回啥。记得数组的除去重复。

​			时间复杂度和官方给的O(n)的复杂度一样。

```c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        auto i = find(nums.begin(),nums.end(),1);
        if(i == nums.end())
            return 1;
        int j = 1;
        while(i != nums.end())
        {
            while((i+1) < nums.end()-1 && *i == *(i+1))
                i++;
            if(*i == j)
            {
                i++;
                j++;
            }
            else
                return j;       
        }
        return j;
    }
};
```

37.字符串相乘

给定两个以字符串形式表示的非负整数 `num1` 和 `num2`，返回 `num1` 和 `num2` 的乘积，它们的乘积也表示为字符串形式。

**注意：**不能使用任何内置的 BigInteger 库或直接将输入转换为整数。

思路：把每个字符转成int，将竖式相乘的结果放入数组c中。注意乘以0的特殊性

```c++
class Solution {
public:
    string multiply(string num1, string num2) {
        //这里c的空间使用的是num1.size()+num.size()-1
        vector<int> a(num1.size(),0),b(num2.size(),0),c(num1.size()+num2.size()-1,0);
        for(int i = 0;i != num1.size();i++)
            a[i] = num1[i]-'0';
        for(int i = 0;i != num2.size();i++)
            b[i] = num2[i]-'0';
        if(a.size() == 1 && a[0] == 0)
            return "0";
        if(b.size() == 1 && b[0] == 0)
            return "0";
        for(int i = 0;i != a.size();i++)  
        {
            for(int j = 0;j != b.size();j++) 
            {
                c[i+j] += a[i] * b[j];
            }
        } 
        for(int i = c.size()-1;i != 0;i--)
        {
            if(c[i]/10 != 0)
            {
                c.at(i-1) += c[i]/10;
                c[i] %= 10;
            }         
        } 
        string s;
        for(int i = 0;i != c.size();i++)
        {
            s.append(to_string(c[i]));
        }
        return s;
            
    }
};
```

38.跳跃游戏

给你一个非负整数数组 `nums` ，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

假设你总是可以到达数组的最后一个位置。

思路：把这一格所有跳到的位置+距离这一格的长度 存放进一个数组里，找出最大值。这样得到局部最优解。在最后一步时做特殊处理，得到整体最优解。

```c++
class Solution {
public:
    int jump(vector<int>& nums) {
        int i = 0; //现在的位置
        int j = nums[i]; //该位置能跳的最大数
        int n = 0; //计数
        vector<int> v;
        while(i < nums.size()-1)
        {
            for(int k = 1;i+k < nums.size() && k <= j;k++)
            {
               v.push_back(k+nums[i+k]);
               if(i+k == nums.size()-1)  //得到全局最优解
                {
                    n++;
                    return n;
                }
            }
            auto p = max_element(v.begin(),v.end());
            int d = distance(v.begin(),p)+1;
            i += d;  
            j = nums[i]; 
            n++;
            v.clear();
        }
        return n;
    }
};
```

39.全排列

给定一个不含重复数字的数组 `nums` ，返回其 *所有可能的全排列* 。你可以 **按任意顺序** 返回答案。

思路：回溯。主要是把push进temp的元素从数组中消失，又不能动原来的数组，我就新建了一个数组存放没有push进temp的其他元素。（每次新建比较耗时耗空间，因此时间不太理想）

```c++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if(nums.size()==1 || nums.size()==0)
            return {nums};
        vector<vector<int>> v;  
        vector<int> temp;  
        dfs(v,nums,temp); 
        return v;
    }
    void dfs(vector<vector<int>> &v,vector<int> &nums,vector<int> &temp)
    {
        if(nums.size() == 0)
            v.push_back(temp);
        else
        {
            for(int i = 0;i < nums.size();i++)
            {
                vector<int> num(nums.size()-1);
                temp.push_back(nums[i]);
                copy_if(nums.begin(),nums.end(),num.begin(),
                        [=](const int &j)
                        {
                            if(j == nums[i])
                                return false;
                            else
                                return true;
                        });  
                dfs(v,num,temp);
                temp.pop_back();
            }     
        }
    }
};

```

解法二：上面在每次循环的时候都创建一个新的数组来表示一个数已经被使用过。解法二使用一个数组check来表示一个数已经被使用过。

```c++
private:
    vector<int> check;
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if(nums.size()==1 || nums.size()==0)
            return {nums};
        check.resize(nums.size());
        vector<vector<int>> v;  
        vector<int> temp;  
        dfs(v,nums,temp,0); 
        return v;
    }
    void dfs(vector<vector<int>> &v,vector<int> &nums,vector<int> &temp,int index)
    {
        if(nums.size() == index)
            v.push_back(temp);
        else
        {
            for(int i = 0;i < nums.size();i++)
            {
                if(check[i]==1)
                    continue;
                temp.push_back(nums[i]);
                check[i] = 1;
                dfs(v,nums,temp,index+1);
                check[i] = 0;
                temp.pop_back();
            }     
        }
    }
};
```

40.全排列2

给定一个可包含重复数字的序列 `nums` ，***按任意顺序*** 返回所有不重复的全排列。

思路：由于上一题的解法一比较耗费内存，所以选择解法一的思路来进行修改。将重复部分修改即可

```c++
class Solution {
private:
    vector<int> check;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if(nums.size()==1 || nums.size()==0)
                    return {nums};
        check.resize(nums.size());
        vector<vector<int>> v;  
        vector<int> temp;  
        sort(nums.begin(),nums.end());  //与上一题不同，这里需要排序，为了下面方便除去重复
        dfs(v,nums,temp,0);
        return v;
    }
    void dfs(vector<vector<int>> &v,vector<int> &nums,vector<int> &temp,int index)
    {
        if(index == nums.size())
            v.push_back(temp);
        else
        {
            for(int i = 0;i < nums.size();i++)
            {
                if(check[i] == 1 || (i > 0 && nums[i] == nums[i - 1] && check[i - 1] == 0))  //新加部分为了除重
                    continue;
                temp.push_back(nums[i]);
                check[i] = 1;
                dfs(v,nums,temp,index+1);
                check[i] = 0;
                temp.pop_back();
            }
        }
    }
};
```

41.旋转图像

给定一个 *n* × *n* 的二维矩阵 `matrix` 表示一个图像。请你将图像顺时针旋转 90 度。

你必须在**[ 原地](https://baike.baidu.com/item/原地算法)** 旋转图像，这意味着你需要直接修改输入的二维矩阵。**请不要** 使用另一个矩阵来旋转图像。

思路：由于不允许新建矩阵来旋转，因此采用原地旋转。注意 第i行,第j列 变成 第j行,第n-1-i列 。一次旋转一组4个数据。

```c++
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix[0].size(); //记录矩阵公有几行/几列
        int temp;
        //根据题意，第i行,第j列 变成 第j行,第n-1-i列  
        for(int i = 0;i < n/2;i++)
        {
            for(int j = 0;j <(n+1)/2;j++)
            {
                temp = matrix[i][j];
                //这下面几个都是由 第i行,第j列 变成 第j行,第n-1-i列 推导出来的 
                matrix[i][j] = matrix[n-1-j][i];          
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = temp;
            }
        }
    }
};
```

42.字母异位词分组

给你一个字符串数组，请你将 **字母异位词** 组合在一起。可以按任意顺序返回结果列表。

**字母异位词** 是由重新排列源单词的字母得到的一个新单词，所有源单词中的字母通常恰好只用一次。

思路：使用unordered_map<string,vector<string>> ，key存放排序后的string，value存放key值一样的string（排序前）。

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> hash;
        vector<vector<string>> v;
        string s;
        for(auto i : strs)
        {
            s = i;
            sort(s.begin(),s.end());
            hash[s].push_back(i);
            s.clear();
        }
        for(auto i = hash.begin();i != hash.end();i++)
            v.push_back(i->second);
        return v;
    }
};
```

43.Pow(x,n)

实现 [pow(*x*, *n*)](https://www.cplusplus.com/reference/valarray/pow/) ，即计算 `x` 的 `n` 次幂函数。

思路：当n是偶数时，将n/2,x平方。当n是奇数时，将n/2,x平方，把此时的x平方前的数据在res中。不论n开始时是奇数是偶数，由于n/2像下取整，所以最后一定能让n变成1，因为1也是奇数，按照前面的方法把x平方前的数据在res中,然后n/2==0退出循环，res就是x的n次幂函数。

```c++
class Solution {
public:
    double myPow(double x, int n) 
    {
        if(x == 0 || x == 1)
            return x;
        if(n == 0)
            return 1;
        long long N = n;
        return N > 0 ? quick(x,N) : 1/quick(x,-N);
    }
    double quick(double x,long long N)
    {
        double i = x;
        double res = 1.0;
        while(N != 0)
        {
            if(N % 2 == 1) //把奇数时的i用res存下来
            {
                res *= i;     
            }   
            i *= i;
            N /= 2;  
        }
       
        return res;
    }
};
```

44.最大的子数组和 ***

给你一个整数数组 `nums` ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

**子数组** 是数组中的一个连续部分。

思路：动态规划。***

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size() == 1)
            return nums[0];
        int pre = 0, maxSum = nums[1];
        for(const int &i : nums)
        {
            pre = max(pre+i,i);   //前面的数加起来小于0，就把i当作子数组的起点
            maxSum = max(pre,maxSum);
        }
        return maxSum;
    }
};
```

45.螺旋矩阵

给你一个 `m` 行 `n` 列的矩阵 `matrix` ，请按照 **顺时针螺旋顺序** ，返回矩阵中的所有元素。

思路：用m,n,hz,lz四个值分别表示行最大值、列最大值、行最小值、列最小值。flag=0表示向右遍历，flag=1表示像下遍历，flag=2表示向左遍历，flag=3表示向上遍历。用i,j遍历整个数组即可。

```c++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size()-1;      //行的最大值
        int n = matrix[0].size()-1;   //列的最大值
        int hz = 0;  //行的最小值
        int lz = 0;  //列的最小值
        vector<int> res;
        int i = 0,j = 0;  //i,j代表坐标
        int flag = 0;     //0表示向右
        while(i >= 0 && j >= 0 && i <= m && j <= n)
        {
            if(i >= hz && j >= lz)
                res.push_back(matrix[i][j]);
            if(flag == 0)
            {
                if(j == n && i < m)
                {
                    flag = 1;
                    i++;
                    hz++;
                }
                else 
                    j++;   
            }
            else if(flag == 1)
            {
                if(i == m && j > lz)
                {
                    flag = 2;
                    j--;
                    n--;
                }
                else
                    i++;       
            }
            else if(flag == 2)
            {
                if(j == lz && i > hz)
                {
                    flag = 3;
                    i--;
                    m--;
                }
                else
                    j--;
                
            }
            else if(flag == 3)
            {      
                if(i == hz && j < n)
                {
                    flag = 0;
                    lz++;
                    j++;
                }
                else 
                    i--;
            }       
        }
        return res;
    }
};
```

46.跳跃游戏

给定一个非负整数数组 `nums` ，你最初位于数组的 **第一个下标** 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。

思路：用temp记录当前能跳的最远距离，循环后就能得到整体能跳的最远距离。就可以判断能否达到最后一个下标。

```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size() == 1)
            return true;
        if(nums[0] == 0)
            return false;
        int temp = nums[0];
        int j = 0;//记录现在的位置
        for(int i = 0;i < nums.size()-1 ;++i)
        {
            if(temp <= nums[i+1]+i-j+1)
            {
                temp = nums[i+1];
                j = i + 1;   
            }
            if(i-j > temp)
                return false;
            if(j + temp >= nums.size()-1)    
                return true;  
            if(temp == 0)
                return false;
        }  
        return false;
        
    }
};

```

47.合并区间

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

思路：先排序，如果 可以合并则用t记录endi最大的值，之后把合并的push_back，如果不能合并则直接push_back。

```c++
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(),intervals.end());
        vector<vector<int>> v;
        for(auto i = 0;i != n;)
        {
            int t = intervals[i][1];
            int j = i + 1;
            while(j < n && t >= intervals[j][0])
            {
                t = max(t,intervals[j][1]);
                j++;
            }
            v.push_back({intervals[i][0],t});       
            i = j;
        }
        return v;
    }
};
```

48.插入区间

给你一个 **无重叠的** *，*按照区间起始端点排序的区间列表。

在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。

思路：用t1,t2表示当前的边界，循环过后得到整体的边界。如果没有重叠部分直接push进v中即可。

```c++
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int left = newInterval[0];
        int right = newInterval[1];
        int t1 = newInterval[0]; //用来表示当前最小的左边界
        int t2 = newInterval[1]; //用来表示当前最大的右边界
        vector<vector<int>> v;
        for(int i = 0;i < intervals.size();i++)
        {
            if(intervals[i][0] <= left && intervals[i][1] >= left)
            {
                t1 = intervals[i][0];
                if(intervals[i][1] < right)
                    t2 = max(right,t2);
                else
                    t2 = intervals[i][1];
            }
            else if(intervals[i][0] <= right && intervals[i][1] >= right)
            {
                t2 = intervals[i][1];
                if(intervals[i][0] > left)
                    t1 = min(left,t1);
                else
                    t1 = intervals[i][0];
            }
            else if(intervals[i][0] >= t2 || intervals[i][1] <= t1)
            {
                v.push_back({intervals[i][0],intervals[i][1]});
            }
        }
        v.push_back({t1,t2});
        sort(v.begin(),v.end());
        return v;
    }
};
```

49.最后一个单词的长度

给你一个字符串 `s`，由若干单词组成，单词前后用一些空格字符隔开。返回字符串中 **最后一个** 单词的长度。

**单词** 是指仅由字母组成、不包含任何空格字符的最大子字符串。

思路：p作为尾部迭代器，判断*p是不是空格，分类处理之后，将能合并的合并之后得到下面的代码

```c++
class Solution {
public:
    int lengthOfLastWord(string s) {
        auto p = s.end()-1;
        int n  = 0;
        while(p != s.begin() && *p == ' ')
        {
            p--;
        }
        
        while(p != s.begin() && *p != ' ')
        {
            p--;
            n++;
        }
        if(*p != ' ' && p == s.begin())
            n++; 
        return n;

    }
};
```

50.螺旋矩阵2

给你一个正整数 `n` ，生成一个包含 `1` 到 `n2` 所有元素，且元素按顺时针顺序螺旋排列的 `n x n` 正方形矩阵 `matrix` 。

思路：由上一个螺旋矩阵修改而来，因为n有重复，因此将原来代码中的n改为k。再进行简单修改之后即可得到题解。

```c++
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> v(n,vector<int>(n));
        int m = n-1;      //行的最大值
        int k = n-1;   //列的最大值
        int hz = 0;  //行的最小值
        int lz = 0;  //列的最小值
        vector<int> res;
        int i = 0,j = 0;  //i,j代表坐标
        int flag = 0;     //0表示向右
        int num = 1;
        while(i >= 0 && j >= 0 && i <= m && j <= k)
        {
            if(i >= hz && j >= lz)
            {
                v[i][j] = num;
                num++;
            }
            if(flag == 0)
            {
                if(j == k && i < m)
                {
                    flag = 1;
                    i++;
                    hz++;
                }
                else 
                    j++;   
            }
            else if(flag == 1)
            {
                if(i == m && j > lz)
                {
                    flag = 2;
                    j--;
                    k--;
                }
                else
                    i++;       
            }
            else if(flag == 2)
            {
                if(j == lz && i > hz)
                {
                    flag = 3;
                    i--;
                    m--;
                }
                else
                    j--;
                
            }
            else if(flag == 3)
            {      
                if(i == hz && j < k)
                {
                    flag = 0;
                    lz++;
                    j++;
                }
                else 
                    i--;
            }       
        }
        return v;
    }
};
```

51.旋转链表

给你一个链表的头节点 `head` ，旋转链表，将链表每个节点向右移动 `k` 个位置。

思路：向右移动k个位置就是最后面的k个元素移动到前面，就是n-k个元素不动，后面的元素移动到前面。注意k>n的情况即可。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr || head->next == nullptr || k == 0)
            return head;  
        ListNode *l1 = new ListNode();
        l1->next = head;
        int n = 0;//记录有几个节点
        ListNode *p = l1;
        ListNode *q = p;  //用来记录不变动的最后一个节点的位置
        ListNode *nhead = new ListNode();
        while(p->next != nullptr)
        {
            n++;
            p = p->next;
        }
        int k2 = n - k%n;
        if(k2 == n)
            return head;
        p = l1; 
        while(p->next != nullptr)
        { 
            p = p->next;
            k2--; 
            if(k2 == 0)
            {
                q = p;
                nhead->next = p->next;
            }        
        }
        q->next = nullptr;
        p->next = l1->next;
        return nhead->next;
    }
};
```

52.不同路径

一个机器人位于一个 `m x n` 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

思路：动态规划，令f(i,j)是路径的总数，则f(i,j) = f(i-1,j)+f(i,j-1)

```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> v(m,vector<int>(n,1)); //将初始值都设为1
        for(int i = 1;i < m;++i)
        for(int j = 1;j < n;++j)
        {
            v[i][j] = v[i-1][j]+v[i][j-1];  //动态规划后得到每个位置的不同路径总数
        }
        return v[m-1][n-1];
    }
};
```

53.不同路径2

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。



思路：写出递推表达式，将第一行、第一列初始化。注意：当第一行第一列出现障碍物的情况下，后续的路不可能再走通。

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

        //获得行数、列数
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m,vector<int>(n,0));


        if(obstacleGrid[0][0] == 1)
            return 0;
        //初始化第一行、第一列
        for(int i = 0; i < n ;i++)
        {
            if(obstacleGrid[0][i] == 1)
                break;
            else  
               dp[0][i] = 1;
        }
        for(int i = 1; i < m ;i++)
        { 
            if(obstacleGrid[i][0] == 0)
                dp[i][0] = 1;
            else
                break;
        }
        
   
        for(int i = 1; i < m ;i++)
        {
            for(int j = 1; j < n ;j++)
            {
                if(obstacleGrid[i][j] == 0)
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }

        return dp[m-1][n-1];

    }
};
```

54.给定一个包含非负整数的 `*m* x *n*` 网格 `grid` ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

**说明：**每次只能向下或者向右移动一步。

思路：动态规划，注意不要超限访问。

```c++
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m,vector<int>(n,0));
        dp[0][0] = grid[0][0];
        for(int i = 0; i < m ; i++)
        {
            for(int j = 0; j < n ;j++)
            {
                if(i == 0 && j != 0)
                {
                    dp[0][j] = dp[0][j-1] + grid[0][j];
                }
                else if(j == 0 && i != 0)
                {
                    dp[i][0] = dp[i-1][0] + grid[i][0];
                }
                else if(i == 0 && j == 0)
                    ;
                else
                    dp[i][j] = min(dp[i-1][j],dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};
```

55.加1

给定一个由 整数 组成的 非空 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

思路：分两种情况讨论，一种是没溢出，一种溢出。

```c++
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        int i = n-1;
        vector<int> result(n+1,0);
        for(int j = 0; j < n; j++)
        {
            result[j+1] = digits[j];
        }
        while(i >-1 && digits.at(i) == 9)
        {
            i--;
        } 
        if(i == n-1)
        {
            digits[n-1]++;
            return digits;
        }
        else if(i == -1)
        {
            for(int j = i+2; j <= n ;j++)
            {
                result[j] = 0;       
            }
            result[i+1] = 1;
            return result;
        }
        else
        {
            for(int j = i+1; j < n; j++)
            {
                digits[j] = 0;
            }
            digits[i] += 1;
            return digits;
        }
    }
};
```

56.二进制求和

给你两个二进制字符串，返回它们的和（用二进制表示）。

输入为 **非空** 字符串且只包含数字 `1` 和 `0`。

思路：分情况讨论。注意string不能用push_front。

```c++
class Solution {
public:
    string addBinary(string a, string b) {
        int m = a.size();
        int n = b.size();
        int l = max(m,n);
        string sum(l,'0');
        int d_value = m - n;
        while(d_value > 0)
        {     
            b = '0' + b;;
            d_value--;
        }
        while(d_value < 0)
        {
            a = '0' + a;
            d_value++;
        }
        for(int i = l - 1; i >= 0; i--)
        {
            int he = int(a[i] -'0') + int(b[i]-'0') + int(sum[i]-'0');
            if( he == 2)
            {
                sum[i] = '0';
                if(i-1 < 0)
                {
                    sum = '1' + sum;
                }
                else
                    sum[i-1] = '1';
            }
            else if(he == 3)
            {
                sum[i] = '1';
                if(i - 1 < 0)
                    sum = '1' + sum;
                else
                    sum[i-1] = '1';
            }
            else
            {
                sum[i] = he + '0';
            }

        }
        return sum;
    }
};
```

57. x的平方根

     给你一个非负整数 x ，计算并返回 x 的 算术平方根 。

    由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。

    注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。

    思路：每次以平方的形式增加，后面使用二分查找法。

    ```c++
    class Solution {
    public:
        int mySqrt(int x) {
            long long int r = 2;
            long long int l = r;
            if(x == 0)
                return 0;
            else if(x == 1 || x == 2 || x == 3)
                return 1;
                
            while(r * r <= x)
            {
                l = r;
                r *= r;
                if(r == x)
                    return l; 
            }
    
            long long int mid = (l + r) / 2;
            while(mid > l  && mid < r)
            {
                if(mid * mid > x)
                {
                    r = mid;
                    mid = (l + mid)/2;
                }  
                else if(mid * mid < x)
                {
                    l = mid;
                    mid = (r + mid)/2;
                }
                else
                    return mid;
            }
       
            return mid;
    
    
        }
    };
    ```

    











































