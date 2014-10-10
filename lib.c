#include "lib.h"
#include <stdio.h>



struct Pages* initPages(cons char* file)
{
    struct Pages* ps = (struct Pages*)malloc(sizeof(struct Pages*));
    ps->fd = fopen(file);
    ps->pageSize = 4096;
    ps->nPages = 20;
    setBitmap();

}

struct Node* makeNode(strcut Pages* ps, bool is_leaf, int parentPage)
{
    Node* n = (Node*)malloc(sizeof(Node*));
    n->nKeys = 0;
}

struct DB *dbcreate(const char *file, const struct DBC *conf)
{
    if (file == NULL) return 0;
	struct DB* db = (struct DB* )malloc(sizeof(struct DB));
	if (db == NULL) return 0;
	db->DBprivate = (struct DBP*)malloc(sizeof(struct DBP));
	if (db->DBprivate == NULL) return 0;
	db->DBprivate->chunk_size = conf->chunk_size;
	db->DBprivate->db_size = conf->db_size;
	db->DBprivate->mem_size = conf->mem_size;
	db->DBprivate->curr_mem = 0;
	dbFile = fopen(file,"w+");
	if (dbFile == 0) return 0;
	db->DBprivate->dbFile = dbFile;
	db->DBprivate->pages = initPages();
	db->DBprivate->topNode = makeNode();
	return db;
}
struct DB *dbopen  (const char *file) /* Metadata in file */
{
	struct DB* a;
	return a;
}

