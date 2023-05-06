#include <iostream>
#include <cstring>


void move(int num, char from, char mid, char to){
  if(num==1){
    std::cout<<"move "<<from<<"->"<<to<<"\n";
    return;
  }
  move(num-1, from, to, mid);
  move(1, from, mid, to);
  move(num-1, mid, from, to);
}


int main(int argc, char** argv){
  if(argc<2){
    std::cout<<"usage: hanoi <number>\n";
    return -1;
  }
  int n = atoi(argv[1]);
  move(n, 'A', 'B', 'C');
  return 0;
}
