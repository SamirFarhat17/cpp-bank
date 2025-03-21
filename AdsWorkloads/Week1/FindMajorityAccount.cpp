#include <vector>
#include <unordered_map>

class Solution {
    public:
        int majorityElement(std::vector<int>& nums) {
            if(nums.empty()) return -1;
            if(nums.size() <= 2) return nums[0];
            std::unordered_map<int,int> freqs;
    
            int n = nums.size() / 2;
    
            for(int num : nums) {
                freqs[num]++;
                if(freqs[num] > n) return num;
            }
    
            return -1;
    
        }
    };