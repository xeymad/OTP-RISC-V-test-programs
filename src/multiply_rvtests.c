#include "start.h"
#include "multiply_dataset.h"
#include "util.h"

// *************************************************************************
// multiply filter bencmark
// -------------------------------------------------------------------------
//
// This benchmark tests the software multiply implemenation. The
// input data (and reference data) should be generated using the
// multiply_gendata.pl perl script and dumped to a file named
// multiply_dataset.h
int multiply(int x, int y);

//--------------------------------------------------------------------------
// Main
int main(void)
{
  int i;
  int results_data[DATA_SIZE];

  for (i = 0; i < DATA_SIZE; i++)
  {
    results_data[i] = multiply( input_data1[i], input_data2[i] );
  }

  // Check the results
  return verify( DATA_SIZE, results_data, verify_data );
}

// *************************************************************************
// multiply function (c version)
// -------------------------------------------------------------------------

int multiply( int x, int y )
{

 int i;
 int result = 0;

 for (i = 0; i < 32; i++) {
   if ((x & 0x1) == 1)
     result = result + y;
       
   x = x >> 1;
   y = y << 1;
 } 
 
 return result;

}