#define BLOCK_SIZE 512
#define NUM_BLOCKS 4096
#define NUM_INODES 128
#define INODE_SIZE 32
#define vdisk_path "../disk/vdisk"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../disk/diskDriver.h"
#include "File.h"


int blockCounter = 3;
void updatefreeblock(FILE* disk, int num);

const static uint32_t MAGIC_NUMBER	     = 0xf0f03410;
const static uint32_t INODES_PER_BLOCK   = 128;
const static uint32_t POINTERS_PER_INODE = 5;
const static uint32_t POINTERS_PER_BLOCK = 1024;

struct SuperBlock {		// Superblock structure
    uint32_t MagicNumber;	// File system magic number
    uint32_t Blocks;	// Number of blocks in file system
    //uint32_t InodeBlocks;	// Number of blocks reserved for inodes
    uint32_t Inodes;	// Number of inodes in file system
};

struct Inode {
    uint32_t Valid;		// Whether or not inode is valid
    uint32_t Size;		// Size of file
    uint32_t Direct[POINTERS_PER_INODE]; // Direct pointers
    uint32_t Indirect;	// Indirect pointer
}; 


void writeBlock(FILE* disk, int blockNum, char* data){
    fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
    fwrite(data, BLOCK_SIZE, 1, disk); //this will overwrite any existing data
}

void readBlock(FILE* disk, int blockNum, char* buffer){
    fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
    fread(buffer, BLOCK_SIZE, 1, disk);
}

void print_buffer(unsigned char buffer[], int size){

    //buffer = (char*) malloc(BLOCK_SIZE); 
    printf("%04x: ", 0);
    for (int i = 1; i <= size; i++) {
        printf("%02x ", buffer[i-1]);
        if(i % 16 == 0)
        {
            printf("\n");
            printf("%04x: ", i);
        }
    }
    printf("\n");
}
void printdisk(FILE* disk){
  
    // Open file 
    char c;
    disk = fopen(vdisk_path, "r");

    if (disk == NULL) 
    { 
        printf("Cannot open file \n"); 
        exit(0); 
    } 
  
    // Read contents from file 
    c = fgetc(disk); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(disk); 
    } 
  
    fclose(disk); 
    //return 0; 
    
}

void set_block(char* buffer, int block_num)
{
    int index = block_num / 16;
    int bit_index = block_num % 16;
    
    /* printf("SET\n");
    printf("Index: %d\n", index);
    printf("Bit Index: %d\n", bit_index); */
    buffer[index] |= 1UL << bit_index;
}
void toggleset_block(char* buffer, int block_num)
{
    int index = block_num / 16;
    int bit_index = block_num % 16;
    
    /* printf("Toggle\n");
    printf("Index: %d\n", index);
    printf("Bit Index: %d\n", bit_index); */
    buffer[index] ^= 1UL << bit_index;
}

void unset_block(char* buffer, int block_num)
{
    int index = block_num / 16;
    int bit_index = block_num % 16;
    
    printf("UNSET\n");
    printf("Index: %d\n", index);
    printf("Bit Index: %d\n", bit_index);
    buffer[index] &= ~(1UL << bit_index);
}


void InitLLFS(){
    FILE* disk = fopen(vdisk_path, "ab+");
    char* init = calloc(BLOCK_SIZE * NUM_BLOCKS, 1);
    fwrite(init, BLOCK_SIZE * NUM_BLOCKS, 1, disk);
    free(init);
    fclose(disk);

    disk = fopen(vdisk_path, "rb+");
    if(disk == NULL){
        printf("Couldn't open file\n");
    }

    //initialize Super Block
    char* buffer;
    //unsigned char buffer[512];
    buffer = (char*) malloc(BLOCK_SIZE);

    int magic = 42;
    int blocks = NUM_BLOCKS;
    int inodes = NUM_INODES;
    memcpy(buffer, &magic, sizeof(magic));
    memcpy(buffer + sizeof(int) * 1, &blocks, sizeof(int));
    memcpy(buffer + sizeof(int) * 2, &inodes, sizeof(int));

    writeBlock(disk, 0, buffer);
    //print_buffer(buffer, BLOCK_SIZE);

    /* free(buffer);
    fclose(disk); */

    //print_buffer(buffer, NUM_BLOCKS);
    //print_buffer(buffer, BLOCK_SIZE);

    //--- Block 1 ---
    char* freeblockbuffer = (char*) malloc(BLOCK_SIZE);

    memset(freeblockbuffer, 0, 9);
    fwrite(freeblockbuffer,1,512,disk);

    /* memset(buffer + 10, 1, BLOCK_SIZE);
    fwrite(buffer,1,512,disk);
    writeBlock(disk, 1, buffer); */
    
	
	//Initialize the remaining blocks as AVAILABLE (1);
	for(int i = 10; i < 4096; i++)
	{
		set_block(freeblockbuffer, i);
	}
	
	writeBlock(disk, 1, freeblockbuffer);


   // print_buffer(freeblockbuffer, BLOCK_SIZE);
    
    free(freeblockbuffer);
    fclose(disk);

    //INODES Block
    int inodeID;
    int filesize;
    int flag;
    int blocknum;
    int single_indir;
    int double_indir;
    memset(buffer, 0, 512);
   //unsigned int 

    memcpy(buffer, &inodeID, sizeof(inodeID));
    memcpy(buffer, &filesize, sizeof(filesize));
    memcpy(buffer, &flag, sizeof(flag));
    memcpy(buffer + sizeof(int) * 1, &blocknum, sizeof(int));
    memcpy(buffer + sizeof(int) * 2, &single_indir, sizeof(int));
    memcpy(buffer + sizeof(int) * 3, &double_indir, sizeof(int));
    //memset(buffer, 0, 32);
    writeBlock(disk, 2, buffer);


    //print_buffer(buffer, BLOCK_SIZE);
    free(buffer);



}

void updatefreeblock(FILE* disk, int num){
   char* buffer = (char*) malloc(BLOCK_SIZE);
   readBlock(disk, num, buffer);
    for(int i=0; i<num; i++){
        if (num > 0 && num < NUM_BLOCKS){
            toggleset_block(buffer, num);
            //i = i;
        }
    }
    free(buffer);
    fclose(disk);
}

void deleteBlock(FILE* disk, int block_num){

    char* buffer = (char*) malloc(BLOCK_SIZE);

    memset(buffer, 0, BLOCK_SIZE);
    fwrite(buffer,1,512,disk);
    writeBlock(disk, block_num, buffer);
    free(buffer);
    
}
void writeFile(FILE* disk, char* data){

    char* buffer = (char*) malloc(BLOCK_SIZE);
    //memset(buffer, 0, 9);
    //fwrite(buffer,2,512,disk);

    int filesize = strlen(data); 

    //str = "Hello my name is Matthew";
    writeBlock(disk, blockCounter, data);
    //set_block(disk, 2);
    readBlock(disk, 1, buffer);
    set_block(buffer, blockCounter);
    writeBlock(disk, 1, buffer);

    readBlock(disk, 2, buffer);
    set_block(buffer, blockCounter);
    writeBlock(disk, 2, buffer);


    //set_block(buffer, 2)
    free(buffer);
   
    
    blockCounter++;

   // printf("this the counter: %d\n", blockCounter);
}
void readFile(){
    
}
void findInode(){
    
}
int findAvailBlock(FILE* disk){
    char* buffer = (char*) malloc(BLOCK_SIZE);
    for (int i = 0; i < NUM_BLOCKS; i++){
        for (int j = 0; j < BLOCK_SIZE; j++)
        {
           if(buffer[j] == 0){
               return j;
           }
        }
    }
    return 1;
}
void formatDisk(FILE* disk){

    for (int i = 1; i < blockCounter; i++)
    {
        deleteBlock(disk, i);
    }
    //fclose(disk);
}
