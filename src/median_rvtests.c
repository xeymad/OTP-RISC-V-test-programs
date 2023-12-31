#include "start.h"
#include "median_dataset.h"
#include "util.h"


//**************************************************************************
// Median filter (c version)
//--------------------------------------------------------------------------

void median( int n, int input[], int results[] )
{
  int A, B, C, i;

  // Zero the ends
  results[0]   = 0;
  results[n-1] = 0;

  // Do the filter
  for ( i = 1; i < (n-1); i++ ) {

    A = input[i-1];
    B = input[i];
    C = input[i+1];

    if ( A < B ) {
      if ( B < C )
        results[i] = B;
      else if ( C < A )
        results[i] = A;
      else
        results[i] = C;
    }

    else {
      if ( A < C )
        results[i] = A;
      else if ( C < B )
        results[i] = B;
      else
        results[i] = C;
    }

  }

}

//--------------------------------------------------------------------------
// Main

int main()
{
  int results_data[DATA_SIZE];

  // Do the filter
  median( DATA_SIZE, input_data, results_data );


  // Check the results
  return verify( DATA_SIZE, results_data, verify_data );
}