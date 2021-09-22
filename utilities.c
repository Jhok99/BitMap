#include <stdio.h>
#include <math.h> //per floor e log2
#include "buddy_allocator.h"
#include "bit_map.h"

int levelIdx(size_t idx){
  if(!idx) return 0;
  if(idx==1) return 1;
  return (int)floor(log2(idx+1));
}

int buddyIdx(int idx){
  if(idx & 0x1){
    return idx+1;
  }
  else return idx-1;
}

int parentIdx(int idx){
  return floor((idx-1)/2);
}

int startIdx(int idx){
  return (idx-((1<<levelIdx(idx))-1));
}

int firstIdx(int lvl){
  return (1<<lvl)-1;
}

void print_bitmap(BitMap* bit_map){
  for(int i=0;i<bit_map->num_bits;i++){
    if(i==firstIdx(levelIdx(i))){
      printf("level %d: ", levelIdx(i));
      for(int k=bit_map->num_bits>>(levelIdx(i)+1);k>0;k--){
        printf(" ");
      }
    }
    if(levelIdx(i)!=levelIdx(i+1)){
      printf("%d ",BitMap_bit(bit_map,i));
      printf("\n");
    }
    else{
      printf("%d ",BitMap_bit(bit_map,i));
      for(int k=bit_map->nume_bits>>(levelIdx(i)+1);k>0;k--){
        printf("  ");
      }
    }
  }
  printf("\n");
}

int check_level(BuddyAllocator *allocator, int size, int bucket_size, int actual_level){
  for(int i=0; i<allocator->num_levels;i++){//salgo di livello per trovare l'indice di dim minima che soddisfi la richiesta
    if(bucket_size>size) return actual_level;
    else{
      bucket_size*=2; //raddoppio la size mentre salgo
      actual_level--; // salgo di livello
    }
  }
  return actual_level;
}

void set_parent(BitMap* bit_map, int bit_num, int status){
  if(bit_num==0){//sono al nodo radice
    BitMap_setBit(bit_map, bit_num, status);
  }
  else{
    BitMap_setBit(bit_map, bit_num, status);
    printf("il figlio è %d, il padre è %d\n", bit_num,parentIdx(bit_num));
    set_parent(bit_map,parentIdx(bit_num),status);
  }
}


void set_child(BitMap* bit_map, int bit_num, int status){
  if(bit_num<bit_map->num_bits){
    BitMap_setBit(bit_map, bit_num, status);
    set_child(bit_map,bit_num*2+1, status);
    set_child(bit_map, bit_num*2+2,status);
  }
}
