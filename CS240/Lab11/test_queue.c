#include "Queue_List.h"
#include <assert.h>

/*This test will test the initializations*/

QueuedCar newCar, newCar1, newCar2, newCar3, newCar4, newCar5;
int QueueCount;
Queue TestList;

void test1(){
	
	Queue newList = newQueueList();
	assert(newList->_tail == NULL);
	assert(newList->_head == NULL);
	assert(newList->_count == 0);
	free(newList);
	printf("1-1.  List Initialization: Passed\n");

	QueuedCar newNode = newQueueNode();
	assert(newNode->_next == NULL);
	assert(newNode->_color == NULL);
	assert(newNode->_make == NULL);
	assert(newNode->_model == NULL);
	assert(newNode->_buyer == NULL);
	assert(newNode->_leather == 0);
	free(newNode);
	printf("1-2.  Node Initialization: Passed\n");
}

void test2(){

	newCar = newQueueNode();

  /***************Setters*****************/
	char* tempColor = "Blue";
	setCarColor(newCar, tempColor);
	assert("Setter: CarColor" && !strcmp(tempColor, newCar->_color));

	char* tempMake = "Buick";
	setCarMake(newCar, tempMake);
	assert("Setter: CarMake" && !strcmp(tempMake, newCar->_make));

	char* tempModel = "Century";
	setCarModel(newCar, tempModel);
	assert("Setter: CarModel" && !strcmp(tempModel, newCar->_model));

	char* tempName = "Joe Valle";
	setCarBuyer(newCar, tempName);
	assert("Setter: CarBuyer" && !strcmp(tempName, newCar->_buyer));

	addLeather(newCar);
	assert("Setter: AddLeather" && newCar->_leather);

	removeLeather(newCar);
	assert("Setter: RemoveLeather" && !newCar->_leather);

	printf("2: Setters Passed\n");
	free(newCar->_color);
	free(newCar->_make);
	free(newCar->_model);
	free(newCar->_buyer);
	free(newCar);
}

void test3(){ 

  /**************Getters*******************/

	newCar = newQueueNode();

	setCarColor(newCar, "Blue");
	char* carColor = getCarColor(newCar);
	assert("Getter: CarColor" && !strcmp("Blue", carColor));

	setCarMake(newCar, "Buick");
	char* carMake = getCarMake(newCar);
	assert("Getter: CarMake" && !strcmp("Buick", carMake));

	setCarModel(newCar, "Century");
	char* carModel = getCarModel(newCar);
	assert("Getter: CarModel" && !strcmp("Century", carModel));

	setCarBuyer(newCar, "Joe Valle");
	char* carBuyer = getCarBuyer(newCar);
	assert("Getter: CarBuyer" && !strcmp("Joe Valle", carBuyer));

	int leather = getCarLeather(newCar);
	assert("Getter: CarLeather" && !leather);

	printf("3: Getters Passed\n");
	free(newCar->_color);
	free(newCar->_make);
	free(newCar->_model);
	free(newCar->_buyer);
	free(newCar);
}

void test4(){//Enqueue
	enqueue(TestList, newCar);
	QueueCount++;
	enqueue(TestList, newCar1);
	QueueCount++;
	enqueue(TestList, newCar2);
	QueueCount++;
	enqueue(TestList, newCar3);
	QueueCount++;
	enqueue(TestList, newCar4);
	QueueCount++;
	enqueue(TestList, newCar5);
	QueueCount++;

	assert("Queue: Count" &&  QueueCount == TestList->_count);
	printf("Enqueue Count: Passed\n\n");
	printf("Expected Queue:\n");
	printf("%.6s->%.6s->%.6s->%.6s->%.6s->%.6s\n\n",
	newCar->_buyer, newCar1->_buyer, newCar2->_buyer,
	newCar3->_buyer, newCar4->_buyer, newCar5->_buyer);

	printf("Your Queue:\n");
	QueuedCar temp = TestList->_head;
	int i = 0;
	for (i = 0; i < QueueCount; i++){
		if(i == QueueCount-1){
			printf("%.6s\n\n", temp->_buyer);
			break;
		}
		printf("%.6s->", temp->_buyer);
		temp = temp->_next;
	}

	fflush(stdout);
	free(newCar->_color);//Car0
	free(newCar->_make);
	free(newCar->_model);
	free(newCar->_buyer);
	free(newCar);
	free(newCar1->_color);//Car1
	free(newCar1->_make);
	free(newCar1->_model);
	free(newCar1->_buyer);
	free(newCar1);
	free(newCar2->_color);//Car2
	free(newCar2->_make);
	free(newCar2->_model);
	free(newCar2->_buyer);
	free(newCar2);
	free(newCar3->_color);//Car3
	free(newCar3->_make);
	free(newCar3->_model);
	free(newCar3->_buyer);
	free(newCar3);
	free(newCar4->_color);//Car4
	free(newCar4->_make);
	free(newCar4->_model);
	free(newCar4->_buyer);
	free(newCar4);
	free(newCar5->_color);//Car5
	free(newCar5->_make);
	free(newCar5->_model);
	free(newCar5->_buyer);
	free(newCar5);
	free(TestList);
}

void test5(){
  /**************QueuePeek***************/

	printf("\n");
	assert("Queue: QueuePeek" && queuePeek(TestList) == TestList->_head);
	printf("QueuePeek: Passed\n");
	free(newCar->_color);//Car0
	free(newCar->_make);
	free(newCar->_model);
	free(newCar->_buyer);
	free(newCar);
	free(newCar1->_color);//Car1
	free(newCar1->_make);
	free(newCar1->_model);
	free(newCar1->_buyer);
	free(newCar1);
	free(newCar2->_color);//Car2
	free(newCar2->_make);
	free(newCar2->_model);
	free(newCar2->_buyer);
	free(newCar2);
	free(newCar3->_color);//Car3
	free(newCar3->_make);
	free(newCar3->_model);
	free(newCar3->_buyer);
	free(newCar3);
	free(newCar4->_color);//Car4
	free(newCar4->_make);
	free(newCar4->_model);
	free(newCar4->_buyer);
	free(newCar4);
	free(newCar5->_color);//Car5
	free(newCar5->_make);
	free(newCar5->_model);
	free(newCar5->_buyer);
	free(newCar5);
	free(TestList);
}

void test6(){
  /**************Dequeue****************/
	QueuedCar temp = NULL;
	fflush(stdout);
	printf("\n");
	printf("Expected Queue after dequeue:\n");
	printf("%.6s->%.6s->%.6s->%.6s\n\n",
	newCar4->_buyer, newCar3->_buyer,
	newCar->_buyer, newCar2->_buyer);

	dequeue(TestList);
	QueueCount--;
	dequeue(TestList);
	QueueCount--;

	printf("Your Queue after dequeue:\n");
	temp = queuePeek(TestList);
	int i = 0;
	for (i = 0; i < QueueCount; i++){
		if(i == QueueCount-1){
			printf("%.6s\n\n", temp->_buyer);
			break;
		}
		printf("%.6s->", temp->_buyer);
		temp = temp->_next;
	}
	assert("QueueList Count:" && QueueCount == TestList->_count);
	free(newCar->_color);//Car0
	free(newCar->_make);
	free(newCar->_model);
	free(newCar->_buyer);
	free(newCar);
	free(newCar1->_color);//Car1
	free(newCar1->_make);
	free(newCar1->_model);
	free(newCar1->_buyer);
	free(newCar1);
	free(newCar2->_color);//Car2
	free(newCar2->_make);
	free(newCar2->_model);
	free(newCar2->_buyer);
	free(newCar2);
	free(newCar3->_color);//Car3
	free(newCar3->_make);
	free(newCar3->_model);
	free(newCar3->_buyer);
	free(newCar3);
	free(newCar4->_color);//Car4
	free(newCar4->_make);
	free(newCar4->_model);
	free(newCar4->_buyer);
	free(newCar4);
	free(newCar5->_color);//Car5
	free(newCar5->_make);
	free(newCar5->_model);
	free(newCar5->_buyer);
	free(newCar5);
	free(TestList);
}

void test7(){
  /**********DeleteNode***********/
	fflush(stdout);
	deleteNode(newCar1);
	deleteNode(newCar);
	deleteNode(newCar3);
	deleteNode(newCar2);
	deleteNode(newCar5);
	deleteNode(newCar4);
	free(TestList);
}

void test8(){
	/************DeleteList************/
	fflush(stdout);
	deleteQueue(TestList);
	printf("Good: Did not SegFault\n");
}

void test9(){
	QueuedCar temp = NULL;
	dequeue(TestList);
	dequeue(TestList);
	enqueue(TestList, newCar1);
	dequeue(TestList);
	enqueue(TestList, newCar5);
	dequeue(TestList);
	dequeue(TestList);
	dequeue(TestList);
	dequeue(TestList);
	dequeue(TestList);
	temp = dequeue(TestList);
	if(temp != NULL){
		printf("If queue is empty, dequeue should return NULL\n");
		fflush(stdout);
		return;
	}
	enqueue(TestList, newCar2);
	enqueue(TestList, newCar5);
	enqueue(TestList, newCar1);
	deleteNode(newCar);
	deleteNode(newCar3);
	deleteNode(newCar4);

	QueueCount = 3;
	assert("Queue: QueueCount" && (QueueCount == TestList->_count));
	
	printf("Expected Queue before DeleteQueue:\n");
	printf("%.6s->%.6s->%.6s\n\n",
	newCar2->_buyer, newCar5->_buyer, newCar1->_buyer);

	printf("Your Queue before DeleteQueue:\n");
	temp = queuePeek(TestList);
	int i = 0;
	for (i = 0; i < QueueCount; i++){
		if(i == QueueCount-1){
			printf("%.6s\n\n", temp->_buyer);
			break;
		}
		printf("%.6s->", temp->_buyer);
		temp = temp->_next;
	}

	deleteQueue(TestList);
	printf("Didn't SegFault.  Yay!\n\n");
	printf("I hope Valgrind is okay with this...\n");
}

void test10(){
	QueuedCar temp = NULL;//203415
	removeNode(TestList, newCar4);//20315
	removeNode(TestList, newCar3);//2015
	removeNode(TestList, newCar5);//201
	removeNode(TestList, newCar2);//01
	removeNode(TestList, newCar);//1
	removeNode(TestList, newCar1);//
	enqueue(TestList, newCar1);//1
	enqueue(TestList, newCar5);//15
	enqueue(TestList, newCar4);//154
	removeNode(TestList, newCar1);//45
	enqueue(TestList, newCar2);//452
	enqueue(TestList, newCar1);//4521
	removeNode(TestList, newCar4);//521
	removeNode(TestList, newCar5);//21
	removeNode(TestList, newCar2);//1
	enqueue(TestList, newCar5);//15
	enqueue(TestList, newCar4);//154
	enqueue(TestList, newCar);//1540
	enqueue(TestList, newCar3);//15403
	enqueue(TestList, newCar2);//154032
	removeNode(TestList, newCar1);//54032

	QueueCount = 5;
	assert("Queue: QueueCount" && (QueueCount == TestList->_count));
	
	printf("Expected Queue after RemoveNode:\n");
	printf("%.6s->%.6s->%.6s->%.6s->%.6s\n\n",
	newCar5->_buyer, newCar4->_buyer, newCar->_buyer,
	newCar3->_buyer, newCar2->_buyer);

	printf("Your Queue after RemoveNode:\n");
	temp = queuePeek(TestList);
	int i = 0;
	for (i = 0; i < QueueCount; i++){
		if(i == QueueCount-1){
			printf("%.6s\n\n", temp->_buyer);
			break;
		}
		printf("%.6s->", temp->_buyer);
		temp = temp->_next;
	}

	printf("Didn't SegFault.  Yay!\n\n");
	deleteNode(newCar);
	deleteNode(newCar1);
	deleteNode(newCar2);
	deleteNode(newCar3);
	deleteNode(newCar4);
	deleteNode(newCar5);
	free(TestList);
}

void populateNodes(){
	TestList = newQueueList();
	QueueCount = 0;

	newCar = newQueueNode();
	setCarColor(newCar, "Blue");
	setCarMake(newCar, "Buick");
	setCarModel(newCar, "Century");
	setCarBuyer(newCar, "Joe");
	addLeather(newCar);

	newCar1 = newQueueNode();
	setCarColor(newCar1, "Red");
	setCarMake(newCar1, "Ford");
	setCarModel(newCar1, "Mustang");
	setCarBuyer(newCar1, "John");
	removeLeather(newCar1);


	newCar2 = newQueueNode();
	setCarColor(newCar2, "Fuschia");
	setCarMake(newCar2, "Toyota");
	setCarModel(newCar2, "Scion");
	setCarBuyer(newCar2, "Eliya");
	removeLeather(newCar2);


	newCar3 = newQueueNode();
	setCarColor(newCar3, "Off-White(Eggshell)");
	setCarMake(newCar3, "BMW");
	setCarModel(newCar3, "i8");
	setCarBuyer(newCar3, "Phil");
	addLeather(newCar3);

	newCar4 = newQueueNode();
	setCarColor(newCar4, "Avocado Green");
	setCarMake(newCar4, "McLaren");
	setCarModel(newCar4, "650S Spider");
	setCarBuyer(newCar4, "Les");
	removeLeather(newCar4);

	newCar5 = newQueueNode();
	setCarColor(newCar5, "Orange");
	setCarMake(newCar5, "Rolls-Royce");
	setCarModel(newCar5, "Ghost");
	setCarBuyer(newCar5, "Norma");
	addLeather(newCar5);
}

void populateList(){
	enqueue(TestList, newCar5);
	QueueCount++;
	enqueue(TestList, newCar1);
	QueueCount++;
	enqueue(TestList, newCar4);
	QueueCount++;
	enqueue(TestList, newCar3);
	QueueCount++;
	enqueue(TestList, newCar);
	QueueCount++;
	enqueue(TestList, newCar2);
	QueueCount++;
}

int main(int argc, char const *argv[]){
	const char *test;
	if(argc < 2){
		printf("Usage: test_queue test1|test2|test3...test");
		exit(1);
	}

	test = argv[1];
	printf("Running %s\n", test);
  if (strcmp(test, "test1") == 0){
    test1();
  }
  else if (strcmp(test, "test2") == 0){
    test2();
  }
  else if (strcmp(test, "test3") == 0){
    test3();
  }
  else if (strcmp(test, "test4") == 0){
  	populateNodes();
    test4();
  }
  else if (strcmp(test, "test5") == 0){
  	populateNodes();
  	populateList();
    test5();
  }
  else if (strcmp(test, "test6") == 0){
  	populateNodes();
  	populateList();
    test6();
  }
  else if (strcmp(test, "test7") == 0){
  	populateNodes();
    test7();
  }
  else if (strcmp(test, "test8") == 0){
  	populateNodes();
  	populateList();
    test8();
  }
  else if (strcmp(test, "test9") == 0){
  	populateNodes();
  	populateList();
  	printf("Running Queue Stress Test (Edge Cases)...\n\n");
  	test9();
  }
  else if (strcmp(test, "test10") == 0){
  	populateNodes();
  	populateList();
  	printf("Running Extra Credit RemoveNode()...\n\n");
  	test10();
  }
  else {
    printf("No such test\n");
    exit(0);
  }


	return 0;
}