class GuessNumber{
  static void Main()
  {
    Random rand = new Random();
    int ans = rand.Next(1, 1000);
    int cnt = 0;
    while(cnt<10){
      Console.WriteLine("[{0}/10] Input a number less than 1000", cnt+1);
      int input = Convert.ToInt32(Console.ReadLine());
      if(input >= 1000 || input < 1){
        Console.WriteLine("Input error, retry");
        continue;
      }
      if(input > ans){
        Console.WriteLine("Too big");
      }else if(input < ans){
        Console.WriteLine("Too small");
      }else{
        Console.WriteLine("You, win");
        return;
      }
      cnt++;
    }
    Console.WriteLine("You lose, answer: {0}", ans);
  }
}
