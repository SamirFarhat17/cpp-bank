#include <vector>
#include "../Transactions/Transaction.h"

class Solution {
    public:
        int removeDuplicates(std::vector<Transaction>& transactions) {
            std::vector<int> nums;
            for(Transaction t : transactions) {
                nums.push_back(t.amount);
            }
            if(nums.size() <= 2) return nums.size();
            
            bool twice = false;
            int prev = nums[0];
            int idx = 1;
    
            for(int i = 1; i < nums.size(); i++) {
                if(nums[i] == prev) {
                    if(twice) {
                        continue;
                    }
                    else {
                        twice = true;
                        nums[idx] = nums[i];
                        idx++;
                    }
                }
                else {
                    prev = nums[i];
                    nums[idx] = nums[i];
                    idx++;
                    twice = false;
                }
            }
    
            nums.resize(idx);
            return idx;
        }
    };