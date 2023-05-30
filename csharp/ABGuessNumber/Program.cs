using System;
using System.Collections.Generic;

class ABGuessNumber
{
  static void Main(){
    Random rand = new Random();
    List<int> arr = new List<int>(){1,2,3,4,5,6,7,8,9,0};
    arr = arr.OrderBy(item=>rand.Next()).ToList();
    int cnt = 0;
    while(cnt<10){
      Console.WriteLine("[{0}/10] Input a non-repeat 4-digit number:", cnt+1);
      var input = Console.ReadLine();
      if(input==null){
        Console.WriteLine("Input error, retry");
        continue;
      }
      string input_str = input.ToString().Trim();
      if (input_str.Length != 4){
        Console.WriteLine("Input error, retry");
        continue;
      }
      HashSet<int> input_set = new HashSet<int>();
      int tmp;
      foreach (var v in input_str)
      {
        if(int.TryParse(v.ToString(), out tmp)){
          input_set.Add(tmp);
        }
      }
      if(input_set.Count != 4){
        Console.WriteLine("Input error, retry");
        continue;
      }
      int correct_cnt = 0;
      int semi_correct_cnt = 0;
      for(int i=0; i<4; i++){
        int.TryParse(input_str[i].ToString(), out tmp);
        if(arr[i] == tmp){
          correct_cnt++;
        }else if(input_set.Contains(arr[i])){
          semi_correct_cnt++;
        }
      }
      if(correct_cnt == 4){
        Console.WriteLine("You win!");
        return;
      }
      Console.WriteLine("{0}A{1}B", correct_cnt, semi_correct_cnt);
      cnt++;
    }
    Console.WriteLine("You Lose! Answer: {0}{1}{2}{3}", arr[0], arr[1], arr[2], arr[3]);
  }
}
