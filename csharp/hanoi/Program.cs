using System;

class Hanoi
{
    static void Main(string[] args){
        Console.WriteLine(args.Length);
        if(args.Length != 1){
            Console.WriteLine("usage: hanoi <number>");
        }else{
            int n = int.Parse(args[0]);
            Move(n, 'A', 'B', 'C');
        }
    }
    private static void Move(int number, char from , char mid, char to){
        if(number==1){
            Console.WriteLine("Move from {0} -> {1}", from, to);
            return;
        }
        Move(number-1, from, to, mid);
        Move(1, from ,mid, to);
        Move(number-1, mid, from ,to);
    }
}