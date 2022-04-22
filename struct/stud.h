struct student {
	int id;
	char name[30];
	int grade;
	struct student *prior;
	struct student *next;
};

//0Ê§°Ü£¬1³É¹¦
extern void *create(void);
extern int load(void *db, char *filename);
extern int save(void *db, char *filename);
extern void destroy(void *db);

extern void *find(void *db, int id);
extern int add(void *db, int id, char *name, int grade);
extern int del(void *db, int id);
extern void dump(void *db);
