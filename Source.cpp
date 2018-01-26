#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Node
{
public:
	T value;
	Node* pNext = nullptr;
};

template<typename T>
class Stack
{
private:
	int count = 0;
	Node<T>* pTop = nullptr;
	Node<T>* nodePop(void);
public:
	~Stack(void);
	void push(T value);
	T pop(void);
	int size(void);
	
};
template<typename T>
Node<T>* Stack<T>::nodePop(void) //Switches Ptop to the next value in the chain and makes pTmp equal to the top of the chain.
{
	Node<T>* pTmp = pTop;
	if (pTop != nullptr) pTop = pTop->pNext;
	return pTmp;
}
template<typename T>
T Stack<T>::pop(void)
{
	if (count == 0) 
	{ 
		throw "Stack Empty!"; 
	}

	Node<T> *pTmp = nodePop(); // makes pTmp equal to the top of the chain and moves pTop to the next node along. 
	T returnVal; // makes value to store value of node in

	if (pTmp != nullptr)
	{
		returnVal = pTmp->value;
	}
	else
	{
		throw "Error!";
	}

	delete pTmp;
	count--;
	return returnVal;
}
template<typename T>
void Stack<T>::push(T value) // creates a new node makes it value equal to the one passed to the method. Makes it's pointer point to the current top of the chain then makes pTop point to the new top.
{
	Node<T>* pTmp = new Node<T>; //Creating new node
	pTmp->value = value; //filling the node with the value 
	pTmp->pNext = pTop; // makes the node point to the current top of the chain 
	pTop = pTmp; // makes pTop now point at the newly added node 
	count++;
}
template<typename T>
Stack<T>::~Stack(void)
{
	while (pTop != nullptr) { delete nodePop(); } //deletes all elements in the stack
}



int main()
{
	Stack<int>* Stack1 = new Stack<int>;
	try
	{
		for (int x = 0; x < 10; x++)
		{
			Stack1->push(x);
		}
		while (true)
		{
			cout << Stack1->pop() << " ";
		}
	}
	catch (char* errorMessage)
	{
		cout << errorMessage << endl;
	}
	catch (...)
	{
		cout << "There has been an unexpected error" << endl;
	}
	delete Stack1;
	return 0;
}