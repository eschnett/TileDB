/*
 * File: tiledb_array_write_dense_1.cc
 * 
 * It shows how to write to a dense array.
 */

#include "c_api.h"

int main() {
  // Intialize context with the default configuration parameters
  TileDB_CTX* tiledb_ctx;
  tiledb_ctx_init(&tiledb_ctx, NULL);

  // Initialize array
  TileDB_Array* tiledb_array;
  tiledb_array_init(
      tiledb_ctx,                                // Context 
      &tiledb_array,                             // Array object
      "my_workspace/dense_arrays/my_array_A",    // Array name
      TILEDB_ARRAY_WRITE,                        // Mode
      NULL,                                      // Entire domain
      NULL,                                      // All attributes
      0);                                        // Number of attributes

  // Prepare cell buffers
  int buffer_a1[] = 
  {
      0,  1,  2,  3,                                     // Upper left tile 
      4,  5,  6,  7,                                     // Upper right tile
      8,  9,  10, 11,                                    // Lower left tile
      12, 13, 14, 15                                     // Lower right tile
  };
  size_t buffer_a2[] = 
  {
      0,  1,  3,  6,                                     // Upper left tile
      10, 11, 13, 16,                                    // Upper right tile
      20, 21, 23, 26,                                    // Lower left tile
      30, 31, 33, 36                                     // Lower right tile
  };
  const char buffer_var_a2[] =
      "abbcccdddd"                                       // Upper left tile
      "effggghhhh"                                       // Upper right tile
      "ijjkkkllll"                                       // Lower left tile
      "mnnooopppp";                                      // Lower right tile
  float buffer_a3[] = 
  {
      0.1,  0.2,  1.1,  1.2,  2.1,  2.2,  3.1,  3.2,     // Upper left tile
      4.1,  4.2,  5.1,  5.2,  6.1,  6.2,  7.1,  7.2,     // Upper right tile
      8.1,  8.2,  9.1,  9.2,  10.1, 10.2, 11.1, 11.2,    // Lower left tile
      12.1, 12.2, 13.1, 13.2, 14.1, 14.2, 15.1, 15.2,    // Lower right tile
  };
  const void* buffers[] = { buffer_a1, buffer_a2, buffer_var_a2, buffer_a3 };
  size_t buffer_sizes[] = 
  { 
      sizeof(buffer_a1),  
      sizeof(buffer_a2),
      sizeof(buffer_var_a2)-1,  // No need to store the last '\0' character
      sizeof(buffer_a3)
  };

  // Write to array
  tiledb_array_write(tiledb_array, buffers, buffer_sizes); 

  // Finalize array
  tiledb_array_finalize(tiledb_array);

  // Finalize context
  tiledb_ctx_finalize(tiledb_ctx);

  return 0;
}