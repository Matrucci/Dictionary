#ifndef __INT_FUNC_H
#define __INT_FUNC_H

#include "C:/Users/Matan/Desktop/ITC/ass6/ass6/genericBinTree.h"
#include <stdlib.h>
#include <stdio.h>

Ptr allocate_keyValue();
void destroy_keyValue(Ptr p);
void copy_keyValue(Ptr p1, Ptr p2);
int compare_keyValue(Ptr p1, Ptr p2);
void print_keyValue(Ptr p);

static const BinTreeFunctions int_funcs = {
	allocate_keyValue,
	destroy_keyValue,
	copy_keyValue,
	compare_keyValue,
	print_keyValue
};

#endif