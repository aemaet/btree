#include "lib.h"
#include "bit.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

struct Pages* initPages(struct Pages* ps, const char* file, uint16_t pageSize, size_t poolSize)
{
    memset(ps, 0, sizeof(struct Pages));
    //ps->fd = open(file,O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    ps->pageSize = 4096;
    ps->poolSize = poolSize;
    ps->nPages = 16;
    posix_fallocate(ps->fd, 0, poolSize);
    ps->bitmask = malloc(ps->nPages/8);
    int pagenum = ps->nPages;
    while (pagenum>0) bit_set(ps->bitmask, pagenum--);

}

/*struct Node* loadNode(struct DB* db, struct Node* node, size_t page)
{
    void *data = (page > 0 ? pool_read(db->pool, page, 0, 0) : NULL);
    if (data)
    {
        node->h = (struct NodeHeader *)data;
    } else
    {
        node->h = (struct NodeHeader *)malloc(db->pool->pageSize);
        node->h->page = pool_alloc(db->pool);
        node->h->size = 0;
        node->h->nextPage = 0;
        node->h->flags = 0;
    }
    node->chld = (void *)node->h + sizeof(struct NodeHeader);
    node->vals = (void *)(node->chld + db->btree_degree + 1);
    node->keys = (void *)(node->vals + db->btree_degree);
    return 0;
}*/

struct DB *dbcreate(const char *file, const struct DBC *conf)
{
    if (file == NULL) return 0;
	struct DB* db = (struct DB* )malloc(sizeof(struct DB));
	    memset(db, 0, sizeof(struct DB));
	if (db == NULL) return 0;
	db->dbp = (struct DBP*)malloc(sizeof(struct DBP));
	if (db->dbp == NULL) return 0;

	db->dbp->meta->chunk_size = conf->chunk_size;
	db->dbp->meta->db_size = conf->db_size;
	db->dbp->mem_size = conf->mem_size;
	db->dbp->curr_mem = 0;
	db->dbp->dbFile = file;
	if (db->dbp->dbFile == NULL) return 0;

	db->dbp->pages = (struct Pages*)malloc(sizeof(struct Pages*));
	initPages(db->dbp->pages,file,db->dbp->meta->chunk_size,db->dbp->meta->db_size);

	db->dbp->topNode = (struct Node *)malloc(sizeof(struct Node));
	//loadNode(db,db->dbp->topNode,0);
    int fd = open(file,O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	write(fd, &(db->dbp->meta),sizeof(db->dbp->meta));
	write(fd, &(db->dbp->pages->bitmask), sizeof(db->dbp->pages->bitmask));
	return db;
}
struct DB *dbopen  (const char *file) /* Metadata in file */
{
	struct DB* a;
	return a;
}

int main()
{
    return 1;
}
