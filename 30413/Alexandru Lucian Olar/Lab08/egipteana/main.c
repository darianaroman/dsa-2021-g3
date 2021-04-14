#include <stdio.h>
#include <math.h>

int unit_den_array[10];
int iter = 0;

int gcd(int a, int b) {
  int c = a%b;
  while(c > 0) {
    a = b;
    b = c;
    c = a % b;
  }
  return b;
}

void unit_den_init() {
  int i;
  for(i=0; i<10; i++) {
    unit_den_array[i] = 0;
  }
}

void greedy_egyptian_fraction(int num, int den) {
  if(num == 1) {
    //appending array unit_den_array
    iter++; // storing in unit_den_array from index 1 not 0
    unit_den_array[iter] = den;
  }
  else {
    int unit_den = ceil(den/(num*1.0));
    iter++;
    unit_den_array[iter] = unit_den;
    int gcd_of_numbers = gcd((num*unit_den) - den, den*unit_den);
    greedy_egyptian_fraction(((num*unit_den) - den)/gcd_of_numbers, (den*unit_den)/gcd_of_numbers);
  }
}

int main() {
  unit_den_init();
  greedy_egyptian_fraction(4, 5);
  int i;
  for(i=1; i<=iter; i++) {
    printf("%d\n",unit_den_array[i]);
  }
  return 0;
}
