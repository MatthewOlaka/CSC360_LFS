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
#include "../io/File.h"

int main(){

    FILE* disk = fopen(vdisk_path, "ab+");
    fclose(disk);
    //unsigned char buffer[512];
    char* buffer = (char*) malloc(BLOCK_SIZE);
    disk = fopen(vdisk_path, "rb+");
    char* str = "Hello my name is Matthew and im Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
    char* str2 = "Matty Mattyy Matttyyyy dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
    char* str3 = "Start of Str3 dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";


    InitLLFS();
    printf("After LLFS is initialised!\n");
    
    printf("Writing and reading file into next available blocks in disk:\n");
    writeFile(disk, str);
    readBlock(disk, 3, buffer);
    print_buffer(buffer, 512);
    free(buffer);

    writeFile(disk, str2);
    readBlock(disk, 4, buffer);
    print_buffer(buffer, 512);
    //free(buffer);

    writeFile(disk, str3);
    readBlock(disk, 5, buffer);
    print_buffer(buffer, 512);
    //free(buffer);


    deleteBlock(disk, 4);

    printf("Delecting specific file:\n");
    printf("After Delecting file 2:\n");
    readBlock(disk, 3, buffer);
    print_buffer(buffer, 512);

    readBlock(disk, 4, buffer);
    print_buffer(buffer, 512);

    readBlock(disk, 5, buffer);
    print_buffer(buffer, 512);

    
    formatDisk(disk);
    printf("Formatting entire disk:\n");

    for (int i = 0; i < 5; i++)
    {
        readBlock(disk, i, buffer);
        print_buffer(buffer, 512);
    }
    
    //printdisk(disk);

}