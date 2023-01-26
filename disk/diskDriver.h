#ifndef DISKDRIVER_H
#define DISKDRIVER_H

#define BLOCK_SIZE 512
#define NUM_BLOCKS 4096
#define NUM_INODES 128
#define INODE_SIZE 32
//#define vdisk_path "vdisk"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Arguments
//	- disk: absolute path to file
//	- blockNum: used to identify a specific block (Block number)
//	- buffer: data to write to file

// Used to read content of block
void readtoBlock(FILE* disk, int blockNum, char* buffer);

// Arguments
//	- disk: absolute path to file
//	- blockNum: used to identify a specific block (Block number)
//	- buffer: data to write to file

// Used to write content to a block
void writetoBlock(FILE* disk, int blockNum, char* data);

// Arguments
//	- disk: absolute path to file
//	- blockNum: used to identify a specific block (Block number)
//	- buffer: data to write to file

// Used to read content of buffer
extern void initLLFS();

#endif


