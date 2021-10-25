#include "buddy_allocator.h"
#include <stdio.h>

#define BUFFER_SIZE 256
#define BUDDY_LEVELS 3
#define MEMORY_SIZE 256
#define MIN_BUCKET_SIZE (BUFFER_SIZE>>(BUDDY_LEVELS))

char buffer[BUFFER_SIZE];
char memory[MEMORY_SIZE];

BuddyAllocator alloc;
int main(int argc, char** argv){
printf("init... ");
  BuddyAllocator_init(&alloc, BUDDY_LEVELS,
                      buffer,
                      BUFFER_SIZE,
                      memory,
                      MEMORY_SIZE,
                      MIN_BUCKET_SIZE);
  printf("FATTO\n");
  printf("ALLOCO P1\n");
  printf("---------------------------\n");
  void* p1=BuddyAllocator_malloc(&alloc, 10);
  printf("ALLOCO P5\n");
  printf("---------------------------\n");

  void* p5=BuddyAllocator_malloc(&alloc, 10);
  printf("FREE P1\n");
  printf("---------------------------\n");
  BuddyAllocator_free(&alloc, p1);
  printf("FREE P5\n");
  printf("---------------------------\n");
  BuddyAllocator_free(&alloc, p5);
  printf("ALLOCO P4\n");
  printf("---------------------------\n");
  void* p4=BuddyAllocator_malloc(&alloc, 50);
  printf("ALLOCO P2\n");
  printf("---------------------------\n");
  void* p2=BuddyAllocator_malloc(&alloc, 10);

  printf("ALLOCO P7\n");
  printf("---------------------------\n");
  void* p7=BuddyAllocator_malloc(&alloc, 50);

  printf("ALLOCO P3\n");
  printf("---------------------------\n");
  void* p3=BuddyAllocator_malloc(&alloc, 10);
  printf("%p\n",p3);
  printf("FREE P2\n");
  printf("---------------------------\n");
  BuddyAllocator_free(&alloc, p2);
  printf("FREE P3\n");
  printf("---------------------------\n");
  BuddyAllocator_free(&alloc, p3);
  printf("FREE P7\n");
  printf("---------------------------\n");
  BuddyAllocator_free(&alloc, p7);
  printf("FREE P4\n");
  printf("---------------------------\n");
  BuddyAllocator_free(&alloc, p4);

  //failing tests:
  printf("QUESTI TEST DEVONO FALLIRE\n");
  printf("---------------------------\n");
  printf("FREE P4\n");
  printf("---------------------------\n");
  BuddyAllocator_free(&alloc, p4);
  printf("ALLOCO P8\n");
  printf("---------------------------\n");
  void* p8=BuddyAllocator_malloc(&alloc, 64);
  printf("ALLOCO P9\n");
  printf("---------------------------\n");
  void* p9=BuddyAllocator_malloc(&alloc, 128);
  printf("FREE P8\n");
  printf("---------------------------\n");
  BuddyAllocator_free(&alloc, p8);
  printf("FREE P9\n");
  printf("---------------------------\n");
  BuddyAllocator_free(&alloc, p9);
  printf("FREE P1\n");
  printf("---------------------------\n");
  BuddyAllocator_free(&alloc, p1);

return 0; 
    
}
