#pragma once
#include <stdint.h>
#include "bit_map.h"

#define MAX_LEVELS 16



typedef struct {
  int num_levels;
  char *memory;        // the memory area to be managed
  int memory_size;
  BitMap bitmap;
  int min_bucket_size; // the minimum page of RAM that can be returned
} BuddyAllocator;


// initializes the buddy allocator, and checks that the buffer is large enough
void BuddyAllocator_init(BuddyAllocator* allocator,
                         int num_levels,                         
                         char* memory, //memoria allocator
                         int memory_size, 
                         char* memory_bitmap, //memoria bitmap
                         int memory_bitmap_size,                                                 
                         int min_bucket_siz);

// allocates memory
void *BuddyAllocator_malloc(BuddyAllocator *allocator, int size);

// releases allocated memory
void BuddyAllocator_free(BuddyAllocator *allocator, void *mem);
