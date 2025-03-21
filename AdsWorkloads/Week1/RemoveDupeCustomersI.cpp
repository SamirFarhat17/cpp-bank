#include <vector>
#include <../Transactions/Transaction.h>

class Solution {
    public:
        int removeDuplicates(std::vector<Transaction>& transactions) {
            std::vector<int> nums;
            for(Transaction t : transactions) {
                nums.push_back(t.amount);
            }
            if(nums.size() <= 1) return nums.size();
    
            int idx = 1;
            int prev = nums[0];
    
            for(int i = 1; i < nums.size(); i++) {
                if(nums[i] != prev) {
                    nums[idx] = nums[i];
                    idx++;
                    prev = nums[i];
                }
            }
    
            nums.resize(idx);
            return nums.size();
        }
    };