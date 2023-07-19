#include <stdio.h>
#include "strList.h"
#include <string.h>
#include <iostream>
#include <cstring>

int main(){

// 	StrList a;
	/*char* b = "abcd";*/
// 	a.push_back("afsf", 4);
// 	a.push_back("bbbb", 4);
// 	a.push_front("ccccc", 5);
// 
// 	/*a.pop_back();*/
// 	a.print();

/*	char* b = "asdf";*/

	StrList a;

	a.push_back("aaaa", 4);
	a.push_back("bbbb", 4);
	a.push_back("ccccc", 5);
	a.push_front("000", 3);

	a.print();

	a.pop_back();
	a.pop_front();
	a.pop_front();
	a.pop_front();

	a.push_back("asc", 3);
	a.pop_back();
	a.push_front("xx", 2);
	a.push_front("aaax", 4);
	a.push_front("bbbxx", 5);
	a.push_front("ccccxx", 6);
	a.push_front("dddddxx", 7);

	a.print();

	printf("%s \n", a.at(1));
	printf("%d \n", a.size());

	a.save("test.txt");
	
	char* b = new char[50];

	a.load("test.txt", b, 50);

	puts(b);

};