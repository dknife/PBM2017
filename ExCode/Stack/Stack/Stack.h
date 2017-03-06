#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

#define MAX_SIZE 4

class Stack
{
private:
	int n[MAX_SIZE];
	int top;
public:
	Stack();
	bool isEmpty();
	bool isFull();
	void push(int data);
	int pop();
	void display();
};

class Queue {
private:
	int n[MAX_SIZE];
	int front;
	int rear;
public:
	Queue();
	bool isEmpty();
	bool isFull();
	void add(int data);
	int remove();
	void display();
};

#endif STACK_H