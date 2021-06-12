#include <stdio.h>
#include "queue.h"

void showitems(Queue* pq);

int main() {
	Item temp;
	Queue line;
	char ch;

	InitializeQueue(&line);
	puts("Testing the Queue interface, Type a to add a value,");
	puts("type d to delete a value,type q to quit.");
	while((ch = getchar()) != 'q') {
		if(ch != 'a' && ch != 'd')
			continue;
		if(ch == 'a') {
			if(QueueIsFull(&line) == true) {
				printf("The queue is full.\n"
					"You can't add a element!\n");
				continue;
			}
			puts("Integer to  add:");
			scanf("%d",&temp);
			EnQueue(temp,&line);
		}
		if(ch == 'd') {
			if(QueueIsEmpty(&line) == true) {
				printf("The queue is empty!\n");
				continue;
			}
			DeQueue(&temp,&line);
			printf("%d is removed from queue.\n",temp);
		}
		printf("%d items in queue\n",QueueItemCount(&line));
		puts("type a to add, d to delete, q to quit:");
	}
	showitems(&line);
	EmptyTheQueue(&line);
	puts("Bye!");
	return 0;
}

void showitems(Queue* pq) {
	Node* pnode = pq->front;
	if(pnode == NULL) {
		printf("There is 0 items.\n");
		return;
	}
	Node* pnext = pq->front->next;
	while(pnode != NULL) {
		printf("%d ",pnode->item);
		pnode = pnext;
		if(pnode != NULL) pnext = pnode->next;
	}
	return;
}