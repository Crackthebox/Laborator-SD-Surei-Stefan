#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> rezultate;
        int n = nums.size();
        
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < n - 2; ++i) {
            if (nums[i] > 0) {
                break;
            }
            
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            int stanga = i + 1;
            int dreapta = n - 1;
            
            while (stanga < dreapta) {
                int suma = nums[i] + nums[stanga] + nums[dreapta];
                
                if (suma == 0) {
                    rezultate.push_back({nums[i], nums[stanga], nums[dreapta]});
                    stanga++;
                    dreapta--;
                    
                    while (stanga < dreapta && nums[stanga] == nums[stanga - 1]) {
                        stanga++;
                    }
                    while (stanga < dreapta && nums[dreapta] == nums[dreapta + 1]) {
                        dreapta--;
                    }
                } else if (suma < 0) {
                    stanga++;
                } else {
                    dreapta--;
                }
            }
        }
        
        return rezultate;
    }
};