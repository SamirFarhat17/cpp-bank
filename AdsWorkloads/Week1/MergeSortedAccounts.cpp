#include <vector>
#include <../Accounts/Account.h>

class Solution {
public:
    void merge(std::vector<Account>& nums1, int m, std::vector<Account>& nums2, int n) {
        int lIdx = m-1, rIdx = n-1;
        int end = m+n-1;

        while(rIdx >= 0) {
            if(lIdx >= 0&& nums1[lIdx] > nums2[rIdx]) {
                nums1[end] = nums1[lIdx];
                lIdx--;
            }
            else {
                nums1[end] = nums2[rIdx];
                rIdx--;
            }
            end--;
        }
    }
};