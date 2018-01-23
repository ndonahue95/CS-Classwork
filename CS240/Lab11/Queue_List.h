#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct QueueNode{
	struct QueueNode *_next;//Going from head to tail
	struct QueueNode *_prev;//(points to node that closer to head)
	char *_color;//Red, Yellow, Green, etc
	char *_make;//Honda, BMW, etc.
	char *_model;//Prius, Camry, etc
	char *_buyer;//George, Jane, Pauly, etc.
	int _leather;//1 for yes.  0 for no.
};

struct QueueList {
	struct QueueNode *_tail;//points to tail of queue -- insert here
	struct QueueNode *_head;//points to head of queue -- dequeue from here
	int _count;//How many items in the list
};


typedef struct QueueNode* QueuedCar;
typedef struct QueueList* Queue; 

/*********************************************/
/*                INITIALIZE                 */
/*********************************************/
Queue newQueueList();
QueuedCar newQueueNode();//initialize

/*********************************************/
/*                  SETTERS                  */
/*********************************************/
void setCarColor(QueuedCar car, char color[]);
void setCarMake(QueuedCar car, char make[]);
void setCarModel(QueuedCar car, char model[]);
void setCarBuyer(QueuedCar car, char name[]);
void addLeather(QueuedCar car);
void removeLeather(QueuedCar car);

/*********************************************/
/*                  GETTERS                  */
/*********************************************/
char* getCarColor(QueuedCar car);
char* getCarMake(QueuedCar car);
char* getCarModel(QueuedCar car);
char* getCarBuyer(QueuedCar car);
int getCarLeather(QueuedCar car);

/*********************************************/
/*                OPERATIONS                 */
/*********************************************/
void enqueue(Queue list, QueuedCar car);//add to the tail
QueuedCar dequeue(Queue list);//remove and return;  Do not free
QueuedCar queuePeek(Queue list);//just return _head
void deleteNode(QueuedCar car);//Free the passed Node
void deleteQueue(Queue list);//Free the whole list
void removeNode(Queue list, QueuedCar car);//Remove car from list.  Don't Free.