#include <iostream>
#include <unistd.h>


int main(){
  int sum = 0;
  for (;;) {
    std::cout << "haha" << std::endl;
    ++sum;
    sleep(1);
    if (sum >= 10) {
      break;
    }
  }

  return 0;
}
