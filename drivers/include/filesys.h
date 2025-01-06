#ifndef FILESYS_H
#define FILESYS_H

#include "../../stdint.h"
#define BLOCK_SIZE 512
#define MAX_FILES 100
#define MAX_FILENAME 32

typedef struct {
    char filename[MAX_FILENAME];
    uint32_t start_cluster;
    uint32_t file_size;
} DirEntry;

typedef struct {
    DirEntry entries[MAX_FILES];
    uint32_t num_files;
} RootDirectory;

typedef struct {
    uint32_t total_clusters;
    uint32_t free_clusters;
    uint32_t next_free;
} FAT;

typedef struct {
    RootDirectory root_dir;
    FAT fat;
} Filesystem;

void list_files(Filesystem *fs);
int create_file(Filesystem *fs, const char *filename, uint32_t size);
void init_filesystem(Filesystem *fs);
int findFile(Filesystem *fs, const char *name);

#endif