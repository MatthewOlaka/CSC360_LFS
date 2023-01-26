#ifndef FILE_H
#define FILE_H

#define BLOCK_SIZE 512
#define NUM_BLOCKS 4096
#define NUM_INODES 128
#define INODE_SIZE 32
//#define vdisk_path "../disk/vdisk"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// Arguments
//	- disk: absolute path to file
//	- blockNum: used to identify a specific block (Block number)
//	- buffer: data to write to file

// Used to read content of buffer
void readBlock(FILE* disk, int blockNum, char* buffer);

// Arguments
//	- buffer: data to write to file
//	- size: size of buffer you mean to print

// Used to print content of buffer
void print_buffer(unsigned char buffer[], int size);

// Arguments
//	- disk: absolute path to file

// Used to print content of disk 
void printdisk(FILE* disk);

// Arguments
//	- buffer: data to write to file
//	- blockNum: used to identify a specific block (Block number)

// Used to set a block
void set_block(char* buffer, int block_num);

// Arguments
//	- buffer: data to write to file
//	- blockNum: used to identify a specific block (Block number)

// Used to toggle a block wheter set or unset
void toggleset_block(char* buffer, int block_num);

// Arguments
//	- buffer: data to write to file
//	- blockNum: used to identify a specific block (Block number)

//Used to unset a set block
void unset_block(char* buffer, int block_num);

// Arguments
// no arguments

// Used to initialize the disk( initilizes superblock, freeblock, inode block and inode map)
void InitLLFS();

// Arguments
//	- disk: absolute path to file
//	- num: used to identify a specific block (Block number)

// Used to update the freeblock on disk
void updatefreeblock(FILE* disk, int num);

// Arguments
//	- disk: absolute path to file
//	- blockNum: used to identify a specific block (Block number)

// Used to delete a specific block on the disk
void deleteBlock(FILE* disk, int block_num);

// Arguments
//	- disk: absolute path to file
//	- data: data to write to file

//Used to write to file
void writeFile(FILE* disk, char* data);

// Arguments
//	- disk: absolute path to file
// Return 0 means sucess

//Used to find the next Available block
int findAvailBlock(FILE* disk);

// Arguments
//	- disk: absolute path to file

//Used to format disk
void formatDisk(FILE* disk);

#endif
