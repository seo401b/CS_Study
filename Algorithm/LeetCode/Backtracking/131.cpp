#include <iostream>
#include <vector>
#include <string>

class Solution {
private:
    bool is_palin(std::string& s){
        for(int i = 0; i < s.size(); ++i){
            int pointer1 = s[i];
            int pointer2 = s[s.length()-i-1];
            // if(i==s.length()-i){
            //     return true;
            // }
            if(pointer1!=pointer2){
                return false;
            }
        }
        return true;
    }

    void dfs(std::string& s, std::vector<std::string>& cur, int start_idx, std::vector<std::vector<std::string>>& result){
        if(start_idx==s.length()){
            result.push_back(cur);
            return;
        }

        for(int i = 1; i < s.length()-start_idx+1; ++i){
            std::string cur_s = s.substr(start_idx, i);
            if(is_palin(cur_s)){
                cur.push_back(cur_s);
                dfs(s, cur, start_idx+i, result);
                cur.pop_back();
            }
        }
    }
public:
    std::vector<std::vector<std::string>> partition(std::string s) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> cur;

        dfs(s, cur, 0, result);
        return result;
    }
};

int main(){
    Solution sol;

    std::string s = "aabaab";

    std::vector<std::vector<std::string>> ans = sol.partition(s);

    // 각 분할(partition)을 순회
    for(const auto& a : ans){
        std::cout << "[ ";
        // 벡터 안의 문자열들을 순회하며 출력
        for(size_t i = 0; i < a.size(); ++i){
            std::cout << "\"" << a[i] << "\"";
            if(i + 1 < a.size()) std::cout << ", ";
        }
        std::cout << " ]\n";
    }

    return 0;
}