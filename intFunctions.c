#include "C:/Users/Matan/Desktop/ITC/ass6/ass6/genericBinTree.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct KeyValue {
	int key;
	int value;
} KeyValue;

Ptr allocate_keyValue() {
	return malloc(sizeof(KeyValue));
}
void destroy_keyValue(Ptr p) {
	free(p);
}
void copy_keyValue(Ptr p1, Ptr p2) {
	KeyValue* i1 = (KeyValue*)p1;
	KeyValue* i2 = (KeyValue*)p2;
	*i1 = *i2;
}
int compare_keyValue(Ptr p1, Ptr p2) {
	KeyValue* i1 = (KeyValue*)p1;
	KeyValue* i2 = (KeyValue*)p2;
	//printf("HELLO:: %d::%d\n", i1->key, i2->key);
	return i1->key - i2->key;
}
void print_keyValue(Ptr p) {
	KeyValue* i = (KeyValue*)p;
	printf("[%d:%d]", i->key, i->value);
}

