
#include "fs.h"
#include "disk.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

// for the 8M file system
#define TFS_MAGIC  0x345f2020

#define NUM_BLOCKS 2048
#define NUM_INODES 512 
#define NUM_DENTRIES_PER_BLOCK 128

#define INODES_PER_BLOCK   128
#define POINTERS_PER_INODE 5
#define POINTERS_PER_BLOCK 1024

// file type
#define REGULAR 1
#define DIR 2

struct tfs_superblock {
	int signature ; // Signature 
	int num_blocks; // number of blocks; same as NUM_BLOCKS in this project
	int num_inodes; // number of inodes; same as NUM_INODES in this project
	int root_inode; // inode number of root directory ; use 1
	unsigned int block_in_use[NUM_BLOCKS/sizeof(unsigned int)];
	unsigned int inode_in_use[NUM_INODES/sizeof(unsigned int)]; 
};

struct tfs_dir_entry {
	int valid; 
	char fname[24];
        int inum;
};

struct tfs_inode {
	int type;
	int size;
	int direct[POINTERS_PER_INODE];
	int indirect;
};

union tfs_block {
	struct tfs_superblock super;
	struct tfs_inode inode[INODES_PER_BLOCK];
	struct tfs_dir_entry dentry[NUM_DENTRIES_PER_BLOCK]; 
	int pointers[POINTERS_PER_BLOCK];
	char data[DISK_BLOCK_SIZE];
};

int tfs_format()
{
	return 0;
}

void tfs_debug()
{ 
        int i;
        int b_in_use = 0;

	union tfs_block block;

	disk_read(0,block.data);

        // check signature

        for(i=0; i<NUM_BLOCKS; i++)
           if(block.super.block_in_use[i/32] & (1 <<(i%32)) ) b_in_use++ ;  
        printf("      %d blocks in use \n", b_in_use); 

        // count inodes in use 

        // explore root directory


}

int tfs_mount()
{
	return 0;
}

int tfs_create(const char *filename )
{
        File *filename;
        filename=popen("image0://foo.txt","w");
	return 0;
}

int tfs_delete(const  char *filename )
{
	return 0;
}
// 
int tfs_get_inumber(const  char *filename )
{
	return 0;
}

int tfs_getsize(const  char *filename )
{
	return -1;
}

int tfs_read( int inumber,  char *data, int length, int offset )
{
	return 0;
}

int tfs_write( int inumber, const char *data, int length, int offset )
{
	return 0;
}
