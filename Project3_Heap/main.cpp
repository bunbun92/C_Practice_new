#include <stdio.h>
#include <stdlib.h>
#include "strutil.h"
#include "arr.h"
#include "heap.h"
/*#include "heap_test.h"*/

int main(){

// 	printf("%d\n", 22);
// 
// 	char p1[100] = "aBcd";
// 	char p2[] = "aBcD";
// 	
// 	printf("%d\n", str_compare(p1, p2));	
// 
// 	char* p3 = "";
// 	p3 = new char[str_length(p1) + 1];
// 	str_copy(p3, p1);
// 
// 	printf("%s\n", p3);
// 	printf("p1= %s, p1Addr= %d // p3= %s, p3Addr= %d\n", p1, p1, p3, p3);
// 
// 	char* p4 = str_dup(p3);
// 	printf("p4= %s, p4Addr= %d // p3= %s, p3Addr= %d\n", p4, p4, p3, p3);
// 
// 	delete p3;
// 	delete p4;
// 
// 	str_append(p1, p2);
// 	puts(p1);	
// 
// 	printf("%s\n", str_find(p1, p2));
// 	printf("22\n");
// 
// 	char p5[] = "  ai jf  ";
// 
// 	printf("trim:%s:\n", p5);
// 	str_trim(p5);
// 	printf("trim:%s:\n", p5);
// 
// 
// 	Arr p6;
// 	Arr* p7= &p6;
// 	
// 
// 	arr_alloc(p7, 5);
// 
// 	arr_push_back(p7, 'a');
// 
// 	printf("p7: %s\n", p7->A);
// 
// 	arr_push_back(p7, 'g');
// 
// 	printf("p7: %s, N: %d\n", p7->A, p7->N);
// 
// 	arr_push_at(p7, 'D', 4);
// 
// 	printf("p7: %s, N: %d\n", p7->A, p7->N);
// 
// 	char* p8= "3425";
// 
// 	printf("%d\n", str_to_int(p8));
// 
// 	Arr p9;
// 	Arr* p10= &p9;
// 
// 	arr_alloc(p10, 5);
// 	arr_push_back(p10, '3');
// 	arr_push_back(p10, '4');
// 	arr_push_back(p10, 'g');
// 	arr_push_back(p10, '2');
// 
// 	printf("oo %s, %d\n", p10->A, p10->A);
// 
// 	printf("%d\n", arr_min(p10));
// 	printf("%s, %d\n", p10->A, p10->A);
// 
// 	printf("avg= %.2lf\n", arr_avg(p10));
// 	printf("%s, %d\n", p10->A, p10->A);
// 
// 	printf("avg= %.2lf\n", arr_avg(p10));
// 	printf("%s, %d\n", p10->A, p10->A);
// 
// 	printf("%d\n", arr_min(p10));
// 	printf("%s, %d\n", p10->A, p10->A);
// 
// 	printf("%d\n", arr_min(p10));
// 	printf("%s, %d\n", p10->A, p10->A);

// 	Heap a;
// 	Heap* b = &a;
// 
// 	puts("");
// 	puts("heap");
// 	printf("init 전		= %s \n", b);
// 
// 	heap_init(b);
// 
// 	printf("init 후		= %s\n", b);
// 
// 	char* p11 = heap_alloc(b, 10);
// 	printf("alloc 리턴 주소	= %s\n", p11);
// 	printf("alloc 후	= %s\n", b);
// 
// 	char* p12 = heap_alloc(b, 20);
// 	printf("alloc 리턴 주소	= %s\n", p12);
// 	printf("alloc 후	= %s\n", b);
// // 
// // 	printf("oi= %s\n", heap_alloc(b, 100));
// // 	printf("ooo= %s\n", b);
// 
// // 	heap_free(p11);
// // 	printf("free 후		= %s\n", b);
// 	
// 	heap_free(p12);
// 	printf("free 후		= %s\n", b);
// 
// 	heap_free(b->pool);
// 	printf("free 후		= %s\n", b);

	puts("");
	puts("");

	Heap p15;
	Heap* p16 = &p15;

	heap_init(p16);
	char** pa0= heap_alloc(p16, 15);
	char** pa1= heap_alloc(p16, 10);
	heap_free(p16, pa0);	

	char** pa2 = heap_alloc(p16, 11);
	char** pa3 = heap_alloc(p16, 17);

	heap_defrag(p16);
	puts("");

	heap_free(p16, pa2);
	heap_free(p16, pa3);

	return 0;
}