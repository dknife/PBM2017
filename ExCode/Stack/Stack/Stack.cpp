#include "Stack.h"


Queue::Queue() { front = rear = -1; }
bool Queue::isFull() {
	return rear == MAX_SIZE-1;
}
bool Queue::isEmpty() {
	return front==rear;
}

void Queue::add(int data) {

	if(!isFull()) n[++rear] = data;
}
int Queue::remove() {
	if(!isEmpty()) return n[++front];
	return -9999;
}
void Queue::display() {
	for(int i=front+1;i<=rear;i++) {
		printf("[%d]", n[i]);
	}
	printf("\n");
}


Stack::Stack() { top = -1; }

bool Stack::isEmpty() {
	return top==-1;
}
bool Stack::isFull() {
	return top == MAX_SIZE-1;
}

void Stack::push(int data) {
	if(!isFull()) n[++top] = data;
	else { printf("Stack Full!\n"); return; }
}

int Stack::pop() {	
	return isEmpty()?-999999:n[top--];
}

void Stack::display() {
	for(int i=0;i<=top;i++) {
		printf("[%d]", n[i]);
	}
	printf("\n");
}