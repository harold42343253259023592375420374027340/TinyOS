#include "../stdint.h"
#include "include/filesys.h"
#include "include/strings.h"
#include "include/stdio.h"

void init_filesystem(Filesystem *fs) {
    memset(fs, 0, sizeof(Filesystem));
    fs->fat.total_clusters = 1000;
    fs->fat.free_clusters = 1000;
    fs->fat.next_free = 2; // Clusters 0 and 1 are reserved
}

int create_file(Filesystem *fs, const char *filename, uint32_t size) {
    if (fs->root_dir.num_files >= MAX_FILES) return -1;
    if (strlen(filename) >= MAX_FILENAME) return -1;
    
    DirEntry *entry = &fs->root_dir.entries[fs->root_dir.num_files];
    strcpy(entry->filename, MAX_FILENAME, filename);
    entry->start_cluster = fs->fat.next_free;
    entry->file_size = size;
    
    uint32_t clusters_needed = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    fs->fat.free_clusters -= clusters_needed;
    fs->fat.next_free += clusters_needed;
    fs->root_dir.num_files++;
    
    return 0;
}
void list_files(Filesystem *fs) {
    for (uint32_t i = 0; i < fs->root_dir.num_files; i++) {
        DirEntry *entry = &fs->root_dir.entries[i];
        puts(entry->filename);
        putc('\n');
    }
}


int findFile(Filesystem *fs, const char *name) {
    for (uint32_t i = 0; i < fs->root_dir.num_files; i++) {
        DirEntry *entry = &fs->root_dir.entries[i];
        if (strcmp(name, entry->filename) == 0) {
            return 0;
        }
    }
    return 1;
}

