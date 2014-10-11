#include <stdio.h>
#include <stdint.h>
#define key_cnt 3
#define child_cnt key_cnt+1
#define key_len 10
struct Pages {
	int fd;
    uint16_t pageSize;
    size_t poolSize;
    size_t nPages;
    void *bitmask;
    struct bit_iterator *it;
};

struct NodeHeader {
     size_t page;
    uint8_t flags;
    uint32_t size;
    size_t nextPage;
};

struct Node {
	struct NodeHeader *h;
    size_t *chld;
    size_t *vals;
    char *keys;
};
struct DBT {
     void  *data;
     size_t size;
};

struct Meta
{
    size_t db_size;
    size_t chunk_size;
};

struct DBP
{
    struct Meta* meta;
    size_t mem_size;
    char* dbFile;
    size_t curr_mem;
    struct Pages* pages;
    struct Node* topNode;
};

struct DB{
    /* Public API */
    int (*close)(const struct DB *db);
    int (*del)(const struct DB *db, const struct DBT *key);
    int (*get)(const struct DB *db, struct DBT *key, struct DBT *data);
    int (*put)(const struct DB *db, struct DBT *key, const struct DBT *data);
    int (*sync)(const struct DB *db);
    /* Private API */
    struct DBP* dbp;

}; /* Need for supporting multiple backends (HASH/BTREE) */

struct DBC {
        /* Maximum on-disk file size */
        /* 512MB by default */
        size_t db_size;
        /* Maximum chunk (node/data chunk) size */
        /* 4KB by default */
        size_t chunk_size;
        /* Maximum memory size */
        /* 16MB by default */
        size_t mem_size;
};

struct DB *dbcreate(const char *file, const struct DBC *conf);
struct DB *dbopen  (const char *file); /* Metadata in file */
