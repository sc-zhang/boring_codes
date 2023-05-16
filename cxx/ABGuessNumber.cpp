#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <random>


int main()
{
  const int N = 10;
  const int DIGIT_CNT = 4;
  std::vector<char> ans;
  for(int i=0; i<10; ++i){
    ans.push_back(i+'0');
  }
  std::random_device rd;
  std::mt19937 rng(rd());
  std::shuffle(ans.begin(), ans.end(), rng);
  std::unordered_set<char> ans_set;
  for(int i = 0; i<DIGIT_CNT; ++i){
    ans_set.insert(ans[i]);
  }
  int cur_round = 1;
  std::unordered_set<char> input_set;
  int tmp;
  int corr_cnt, semi_corr_cnt;
  while(cur_round<=N){
    std::cout<<"["<<cur_round<<"/"<<N<<"]Input a non-repeat four-digit number: ";
    std::string input;
    std::cin>>input;
    int cur = DIGIT_CNT-1;
    input_set.clear();
    if(input.size()!=DIGIT_CNT){
      std::cout<<"Invalid Number Found, Retry\n";
      continue;
    }
    for(int i=0; i<input.size(); ++i){
      input_set.insert(input[i]);
    }
    if(input_set.size()!=DIGIT_CNT){
      std::cout<<"Repeat Number Found, Retry\n";
      continue;
    }
    corr_cnt = 0;
    semi_corr_cnt = 0;
    for(int i=0; i<DIGIT_CNT; ++i){
      if(input[i] == ans[i]){
        ++corr_cnt;
      }else{
        if(ans_set.count(input[i])){
          ++semi_corr_cnt;
        }
      }
    }
    if(corr_cnt == DIGIT_CNT){
      std::cout<<"You Win!\n";
      return 0;
    }else{
      std::cout<<corr_cnt<<"A"<<semi_corr_cnt<<"B\n";
    }
    ++cur_round;
  }
  std::cout<<"You Lose!, Ans:";
  for(int i=0; i<DIGIT_CNT; ++i){
    std::cout<<ans[i];
  }
  std::cout<<"\n";
  return 0;
}
