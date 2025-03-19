#include <vector>
#include "../Customers/Customer.h"

class Solution {
    public:
        int removeElement(std::vector<Customer>& nums, int val) {
            int idx = 0;
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i].getId() != val) {
                    nums[idx] = nums[i];
                    idx++;
                }
            }
    
            return idx;
        }
    };