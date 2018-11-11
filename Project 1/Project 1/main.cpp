#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>

using namespace std;

//make the MAX variable
const int MAX = 10;

//****************CLASS DECLARATION****************
class TSQueue {
	//create sync variables
	mutex mutexLock;

	//create actual variables
	int items[MAX];
	int front;
	int nextEmpty;

public:
	TSQueue();
	~TSQueue();
	bool tryInsert(int passItem);
	bool tryRemove(int *passItem);
};

TSQueue::TSQueue() {
	front = 0;
	nextEmpty = 0;
}

TSQueue::~TSQueue() {};

bool TSQueue::tryInsert(int passItem) {
	bool success = false;

	mutexLock.lock();
	if ((nextEmpty - front) < MAX) {
		items[nextEmpty % MAX] = passItem;
		nextEmpty++;
		success = true;
	}
	mutexLock.unlock();
	return success;
};

bool TSQueue::tryRemove(int *passItem) {
	bool success = false;

	mutexLock.lock();
	if (front < nextEmpty) {
		*passItem = items[front % MAX];
		front++;
		success = true;
	}
	mutexLock.unlock();

	return success;
};
//**********END CLASS DECLARATION********************


//Funciton for producer threads to add an item to the queue
void produceFunction(TSQueue *queue) {
	//item to add to the queue
	int item;

	//variable to hold the current thread id
	thread::id threadID = this_thread::get_id();

	//while the queue is full, wait until it is not to produce
	while (queue->tryInsert(item) == false)
	{
		//wait
	}

	//produce item and put it in the queue
	if (queue->tryInsert(item)) {
		printf("Item ID %d\n", item, " produced by thread number: %d\n", threadID, "\n");
	}
}

//function for the consumer threads to remove an item from the queue
void consumeFunction(TSQueue *queue) {
	//item to remove from the queue
	int item;

	//variable to hold the current thread id
	thread::id threadID = this_thread::get_id();

	//if the queue is empty, then wait until there is something to remove
	while (queue->tryRemove(&item) == false)
	{
		//wait
	}

	//consume item from the queue
	if (queue->tryRemove(&item)) {
		printf("Item ID %d\n", item, " consumed by thread number: ", threadID, "\n");
	};
}

int main(int argc, char *argv[]) {
	//get the TP and TC values from the terminal
	char firstArg = *argv[1];
	char secondArg = *argv[2];

	//convert the TP and TC values to Integers
	int TP = (firstArg - '0');
	int TC = (secondArg - '0');

	//cout TP and TC for testing
	printf("First argument is: %d\nSecond Argument is: %d", TP, TC);

	//create initial queue structure
	//TSQueue *queue;

	//create random sleep intervals
	//int t;



	/*program runs forever
	while (true)
	{

	}

	//start producer threads to insert
	for (int i = 0; i < 3; i++) {
	queue = new TSQueue();
	thread producer(produceFunction, queue);
	producer.join();
	}


	// Remove 20 items from each queue
	for (int i = 0; i < 3; i++) {
	printf("Queue %d:\n", i);
	thread consumer(consumeFunction, queue);
	consumer.join();
	}*/
}