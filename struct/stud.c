#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "stud.h"

void *create(void)
{
	struct student *db = (struct student *)malloc(sizeof(struct student));

	db->next = db;
	db->prior = db;
	return db;
}

int load(struct student *db, char *filename)
{
	FILE *fp;

	if ((fp = fopen(filename, "a+b")) == NULL)
		return 0;

	rewind(fp);

	while (1) {
		struct student *node = (struct student *)malloc(sizeof(struct student));

		if (fread(node, sizeof(struct student), 1, fp) == 1) {
			node->next = db;
			node->prior = db->prior;
			db->prior->next = node;
			db->prior = node;
		} else {
		    free(node);
			break;
		}
	}
	fclose(fp);
	return 1;
}

int save(struct student *db, char *filename)
{
	FILE *fp;

	if ((fp = fopen(filename, "w+b")) == NULL)
		return 0;

	for (struct student *i = db->next; i != db; i = i->next ) 
		fwrite(i, sizeof(struct student), 1, fp);

	fclose(fp);
	return 1;
}

void *find(struct student *db, int id)
{
	for (struct student *p = db->next; p != db; p = p->next)
		if (p->id == id)
			return p;
	return NULL;
}

int add(struct student *db, int id, char *name, int grade)
{
	if (find(db, id))
		return 0;

	struct student *node = (struct student *)malloc(sizeof(struct student));

	node->id = id;
	strcpy(node->name, name);
	node->grade = grade;

	node->prior = db->prior;
	node->next = db;
	db->prior->next = node;
	db->prior = node;
	
	return 1;
}

int del(struct student *db, int id)
{
	struct student *p = find(db, id);
	if (p) {
		p->prior->next = p->next;
		p->next->prior = p->prior;
		free(p);
		return 1;
	} else {
		return 0;
	}
}

void dump(struct student *db)
{
	if (db->next == db) {
		puts("None infomation has been loaded.");
		return;
	}

	puts("All information is as followed:");
	for (struct student *p = db->next; p != db; p = p->next)
		printf("id: %d\n"
		       "name: %s\n"
		       "grade: %d\n",
		       p->id, p->name, p->grade);
}

void destroy(struct student *db) 
{
	struct student *t;
	struct student *p = db;

	do {
		t = p->next;
		free(p);
		p = t;
	
	} while (p != db);
}