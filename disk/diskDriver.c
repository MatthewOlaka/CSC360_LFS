#include <stdio.h>
#include <stdlib.h>
#include "diskDriver.h"


/* const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 4096; */
#define BLOCK_SIZE 512
#define NUM_BLOCKS 4096
#define NUM_INODES 128
#define INODE_SIZE 32

extern void initLLFS(){
    FILE *fp = fopen("disk/vdisk", "w+");
    fclose(fp);

}

void readtoBlock(FILE* disk, int blockNum, char* buffer){
    fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
    fread(buffer, BLOCK_SIZE, 1, disk);
}

void writetoBlock(FILE* disk, int blockNum, char* data){
    fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
    fwrite(data, BLOCK_SIZE, 1, disk); //this will overwrite any existing data
}
