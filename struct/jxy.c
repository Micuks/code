#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <sys/timeb.h>
#include "stud.h"

void menu(void)
{
	puts("                                Welcome to manage students' information.\n\n\n"
		"1.Show all data.\n"
		"2.Add new data.\n"
		"3.Delete data.\n"
		"4.Revise data.\n"
		"5.Search specific data.\n"
		"6.Exit with saving data.\n"
		"7.Exit without saving data.");
	printf("Please input the function you want to use: ");
}

int main(void)
{
	struct timeb t1, t2;
	ftime(&t1);
	int index;
	int tempid, tempgrade;
	char tempname[30];
	char *filename = "studentinfo.dat";
	struct student *db = create();

	load(db, filename);

	while (1) {
		menu();

		scanf("%d", &index);
		switch (index) {
		    case 1:
			    dump(db);
			    break;
		    case 2:
			    while (1) {
				    printf("Input the id(Input 0 to quit):");
				    scanf("%d", &tempid);

				    if (tempid == 0)
					    break;
				    
				    printf("Input the name:");
				    scanf("%s", tempname);
				    printf("Input the grade:");
				    scanf("%d", &tempgrade);

				    if (add(db, tempid, tempname, tempgrade) == 0)
					    puts("This id has been added. You can't add it again.");
			    }
			    
			    break;
		    case 3:
			    printf("Input the id of the student you want to delete(Or press 0 to quit.):");
			    while (scanf("%d", &tempid) == 1 && tempid != 0) {
				    if (del(db, tempid) == 1)
					    puts("Successfully delete.");
				    else
					    puts("No such id.");
				    puts("Input the next one you want to delete(Or press 0 to quit.):");
			    }
			    break;
		    case 4:
			    printf("Please input the id of the student whose information you want to revise: (Press 0 to exit)");
			    while (scanf("%d", &tempid), tempid) {
				    int choice;
				    struct student *p = find(db, tempid);

				    if (p == NULL) {
					    puts("No such id.");
					    break;
				    }

					tempid = p->id;
				    strcpy(tempname, p->name);
					tempgrade = p->grade;
					
				    puts("Which information do you want to revise?(Input 0 to exit)\n"
					     "1.id\n"
					     "2.name\n"
					     "3.grade");

				    while (scanf("%d", &choice), choice) {
					    switch (choice) {
					    case 1:
						    printf("Input new id: ");
						    scanf("%d", &p->id);
						    break;
					    case 2:
						    printf("Input new name: ");
						    scanf("%s", p->name);
						    break;
					    case 3:
						    printf("Input new grade: ");
						    scanf("%d", &p->grade);
						    break;
					    default:
						    puts("Illegal input.You should input 1-3.");
					    }
					    printf("Input next choice: (Press 0 to exit)");
				    }

				    printf("Input another id(or input 0 to quit):");
			    }
			    break;
		    case 5:
			    printf("Which one do you want to check?(Input id)(Press 0 to exit)\n");
			    while (scanf("%d", &tempid), tempid) {
				    struct student *p = find(db, tempid);

				    if (p == NULL) {
						puts("No such id\n"
							 "Which one do you want to check?(Input id)(Press 0 to exit)");
				    } else {
					    printf("id: %d\n"
					           "name: %s\n"
					           "grade: %d\n",
					           p->id, p->name, p->grade);
					    printf("Input next target:(Press 0 to exit)");
				    }
			    }

			    break;
		    case 6:
			    if (save(db, filename) == 0)
				    puts("Can't save the data.");
			    else
				    puts("Data saved.");
		    case 7:
			    destroy(db);
			    puts("Bye.");
			    return 0;
		    default:
			    puts("It's illegal input.Please input 1-7.");
			    break;
		}

		puts("Press 'r' to clean the screen and return to the menu");
		char c;
		while ((c = getchar()) != 'r')
			continue;

		system("cls");
	}
	ftime(&t2);
	
	return 0;
}

