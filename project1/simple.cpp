
//Tanner Bonds
//COMP 3500
//simple.cpp
// No external help received.

#include <iostream>
#include <cmath>
using namespace std;

float calculateSD(float data[]);



float calculateSD(float data[])
{
   float sum = 0.0, mean, standardDeviation = 0.0;

   int i;

   for(i = 0; i < 10; ++i)
   {
      sum += data[i];
   }

   mean = sum/10;

   for(i = 0; i < 10; ++i) {

      standardDeviation += pow(data[i] - mean, 2);

   }

   return sqrt(standardDeviation / 10);

}




int main()
{
   int i;
   float data[10] 
    int n; 
    int factorial = 1;

   cout << "How many positive numbers (must be less than 10) do you want to calculate: ";
   cin >> n;

   cout << "Please enter " << n << " elements:";

   for(i = 0; i < 10; ++i) {
   
      cin >> data[i];
      cout << " ";
   
   }

   for (i = 1; i <= n; ++i) {
   
      factorial *= i;   
   
   }

   cout << "\n\nStandard Deviation = " << calculateSD(data[]);
   cout << "\n\n Factorial of " << n << " = " << factorial;
   
}