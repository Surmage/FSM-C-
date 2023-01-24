#include "Idle.h"
#include "Agent.h"
#include <iostream>
using namespace std;

int main(int arg, char* args[])
{
	Idle s;
	vector<Agent>v;
	//create actor 1
	Agent a;
	v.push_back(a);
	//create actor 2
	Agent b;
	v.push_back(b);
	//create actor 3
	Agent c;
	v.push_back(c);
	//create actor 4
	Agent d;
	v.push_back(d);

	cout << "hello world";
	return 1;
}