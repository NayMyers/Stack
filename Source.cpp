#pragma once
#include <iostream>

using namespace std;


class Node
{
public:
	int value;
	Node* pNext = nullptr;
};


class Stack
{
private:
	int count = 0;
	Node* pTop = nullptr;
	Node* nodePop(void);
public:
	~Stack(void);
	void push(int value);
	int pop(void);
	int size(void);

};

Node* Stack::nodePop(void) //Switches Ptop to the next value in the chain and makes pTmp equal to the top of the chain.
{
	Node* pTmp = pTop; //creates a new pointer of type Node and makes it point to the same address as Ptop. This means pTmp is now 
						  //pointing to the top of the stack. This means when we move pTop to the next Node along we don't lose the top node causing a 
						  //memory leak.
	if (pTop != nullptr) pTop = pTop->pNext;
	return pTmp; //essentially return the address that pTop was pointing to
}
int Stack::pop(void)
{
	if (count == 0) // this means there are no more nodes on the chain and the program needs to exit to the catch blocks 
	{
		throw "Stack Empty!";
	}

	Node* pTmp = nodePop(); // makes pTmp equal to the top of the chain and moves pTop to the next node along. 
	int returnVal; // makes value to store value of node in

	if (pTmp != nullptr)
	{
		returnVal = pTmp->value;
	}
	else
	{
		throw "Error!";
	}

	delete pTmp; //deletes the temporary node so there is no memory leak
	count--; // decrements the count because a value has been removed from the stack. 
	return returnVal;
}
void Stack::push(int value) // creates a new node makes it value equal to the one passed to the method. Makes it's pointer point to the current top of the chain then makes pTop point to the new top.
{
	Node* pTmp = new Node; //Creating new node
	pTmp->value = value; //filling the node with the value 
	pTmp->pNext = pTop; // makes the node point to the current top of the chain 
	pTop = pTmp; // makes pTop now point at the newly added node 
	count++; //incriments the count so the program knows how many items are on the stack so it can throw an error if too many are popped.
}

Stack::~Stack(void) //deconstructor that runs when the stack object is deleted
{
	while (pTop != nullptr) { delete nodePop(); } //deletes all elements in the stack 
}



int main()
{
	Stack* Stack1 = new Stack;
	try
	{
		for (int x = 0; x < 10; x++)
		{
			Stack1->push(x);
		}
		while (true) // This will exit when the throw is reached inside the method pop and fall to the next availible relevant catch 
		{             // block
			cout << Stack1->pop() << " ";
		}
	}
	catch (char* errorMessage)
	{
		cout << errorMessage << endl;
	}
	catch (...) //Will be the default for any data type if it hasn't allready been caught by a previous catch block. 
	{
		cout << "There has been an unexpected error" << endl;
	}
	delete Stack1;
	return 0;
}