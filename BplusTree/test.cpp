#include <iostream>

using namespace std;

int main()
{
  /*
    4 7 12 <-8
       8
    /    \
  4 7     12
 -1 4 7   L  R
  */
  int n = 4;
  int size = 4;
  int k[n] = {1, 2, 4, 8}; 
  int p[n + 1] = {-1, 1, 2, 4, 8};
  
  int key = 5;
  int ptrL = -2, ptrR = -3;
  int i, j;

  int left_nums = (n + 1) / 2; // 2
  int right_nums = n - (n + 1) / 2; // 1
  int left[n], leftP[n+1];
  int right[n], rightP[n+1];


  for(i = 0; i < size && key >= k[i]; i ++) {}
  cout << i << endl;

  int Ktemp[n + 1] = {0};
  int Ptemp[n + 2] = {0};
  for(j = 0 ; j < i ; j ++) {
    Ktemp[j] = k[j];
    Ptemp[j] = p[j];
  }
  
  Ktemp[j] = key;
  Ptemp[j] = ptrL;
  Ptemp[j+1] = ptrR;

  for(j++; j < n+1; j ++) {
    Ktemp[j] = k[j-1];
    Ptemp[j+1] = p[j];
  }
  Ptemp[n+1] = p[n];


  int LeftK[n], RightK[n];
  int LeftP[n+1], RightP[n+1];

  int mid = Ktemp[n / 2];

  for(i = 0; i < left_nums; i ++) {
    LeftK[i] = Ktemp[i];
    LeftP[i] = Ptemp[i]; 
  }
  LeftP[i] = Ptemp[i];

  for(i ++; i < n+2; i ++) {
    RightK[i-left_nums-1] = Ktemp[i];
    RightP[i-left_nums-1] = Ptemp[i]; 
  }
}