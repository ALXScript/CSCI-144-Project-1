#include<iostream>
#include"TSQueue.h"
#include"Producer.h"
#include"Consumer.h"
#include<thread>
#include<chrono>

using namespace std;

//funciton for producer threads to add an item to the queue
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
	if(queue->tryInsert(item)){
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

int main() {

	//create initial queue structure
	TSQueue *queue;

	//create random sleep intervals
	int t;

	

	/*program runs forever
	while (true)
	{

	}*/

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
	}
}