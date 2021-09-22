#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "buddy_allocator.h"
#include "utilities.c"

void BuddyAllocator_init(BuddyAllocator* allocator, int num_levels, char* memory, int memory_size,
char* memory_bitmap, int memory_bitmap_size, int min_bucket_size){
    allocator->num_levels=num_levels;
    allocator->memory=memory;
    allocator->memory_size=memory_size;

    //controllo se la dimensione è grande almeno per la bitmap
    assert(min_bucket_size>8);
    allocator->min_bucket_size=min_bucket_size;
    //mi assicuro che il numero di livelli sia minore del massimo consentito
    assert(num_levels<MAX_LEVELS);
    

    //generazione numero di bit per la bit_map
    int num_bits =(1<<(num_levels+1)) -1;

    assert(BitMap_getBytes(num_bits)<=memory_bitmap_size);

    printf("BUDDY INITIALIZING\n");
    printf("\tmanaged memory: %d bytes\n", memory_size);
    printf("\tlevels: %d\n", num_levels);
    printf("\tmin bucket size:%d\n", min_bucket_size);  
    printf("\tbits_bitmap: %d\n", num_bits);
    printf("\tbitmap memory %d bytes usati di %d bytes forniti \n",BitMap_getBytes(num_bits), memory_bitmap_size);

    BitMap_init(&allocator->bitmap, num_bits, memory_bitmap);
    print_bitmap(&allocator->bitmap);
}