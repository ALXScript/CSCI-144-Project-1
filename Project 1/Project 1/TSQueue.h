#include<mutex>

//make the MAX variable
const int MAX = 10;

class TSQueue {
	//create sync variables
	mutex mutexLock;

	//create actual variables
	int items[MAX];
	int front;
	int nextEmpty;

	//Public functions
public:
	TSQueue();
	~TSQueue() {};
	bool tryInsert(int item);
	bool tryRemove(int *item);
};

//initialize the queue to empty and the lock to free
TSQueue::TSQueue() {
	front = 0;
	nextEmpty = 0;
}

//producers will exclusively use this function
//Try to instert an item. If the queue is full, return false; otherise return true
bool TSQueue::tryInsert(int passItem) {
	bool success = false;

	mutexLock.acquire();
	if ((nextEmpty - front) < MAX) {
		items[nextEmpty % MAX] = passItem;
		nextEmpty++;
		success = true;
	}
	mutexLock.release();
	return success;
}

//consumers will exclusively use this function
//Try to removee an item. If the queue is empty, return false; otherwise return true
bool TSQueue::tryRemove(int *passItem) {
	bool success = false;

	mutexLock.acquire();
	if (front < nextEmpty) {
		*passItem = items[front % MAX];
		front++;
		success = true;
	}
	mutexLock.release();

	return success;
}