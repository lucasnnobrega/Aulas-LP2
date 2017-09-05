#include <vector>
#include <algorithm>
#include <iostream>

//using namespace std;

// Function that generates random array elements
int random_element();

const int n = 10;  // Size of the array
const int k = 4;   // Number of random (non-zero) elements in the array
int a[n];          // The array, filled with zeros

int main()
{
  for (size_t i = 0; i < k; ++i)
    a[i] = random_element();

  std::random_shuffle(a, a + n);

  for (int q = 0 ; q = n; q++)
    std::cout<<a[q]<<std::endl;

  // Now 'a' contains k random elements and (n-k) zeros, in a random order
}