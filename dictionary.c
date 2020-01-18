/**************
*Matan Saloniko
*318570769
*01
*ass06
**************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "result.h"
#include "genericSort.h"
#include "intFunctions.h"

typedef struct Dictionary {
	BinTree* dicTree;
} Dictionary;

Result removeFromDictionary(Dictionary* d, int key);

/*****************************************************************************
*Function name: initDictionary.
*Input: None.
*Output: Dictionary* (a pointer to Dictionary, if malloc fails, returns NULL).
*Function operation: The function initializes a Dictionary with a pointer
					 to a BinTree.
					 If one of the functions fails, we free the memory.
*****************************************************************************/
Dictionary* initDictionary() {
	Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));
	if (dictionary != NULL) {
		dictionary->dicTree = createBinTree(int_funcs);
		if (dictionary->dicTree != NULL) {
			return dictionary;
		}
		free(dictionary);
	}
	return NULL;
}

/*****************************************************************************
*Function name: destroyDictionary.
*Input: Dictionary* d.
*Output: None.
*Function operation: The function frees all the memory taken by the dictionary.
					 (BinTree* and the dictionary itself.)
*****************************************************************************/
void destroyDictionary(Dictionary* d) {
	if (d != NULL) {
		if (d->dicTree != NULL) {
			destroyBinTree(d->dicTree);
		}
		free(d);
	}
}

/*****************************************************************************
*Function name: sizeOfDictionary.
*Input: Dictionary* d.
*Output: int (if the dictionary is empty, return 0).
*Function operation: The function checks and returns the size of the dictionary.
*****************************************************************************/
int sizeOfDictionary(Dictionary* d) {
	if (d == NULL) {
		return 0;
	}
	return sizeOfBinTree(d->dicTree);
}

/*****************************************************************************
*Function name: putInDictionary.
*Input: Dictionary* d, int key, int value.
*Output: Result (enum) {SUCCESS, FAILURE, MEM_ERROR} .
*Function operation: The function adds a key and a value to the dictionary.
					 If the key is already in the dictionary, replace the value.
*****************************************************************************/
Result putInDictionary(Dictionary* d, int key, int value) {
	KeyValue keyValue;
	keyValue.key = key;
	keyValue.value = value;
	Result result = addToBinTree(d->dicTree, &keyValue);
	if (result == FAILURE) {
		result = removeFromDictionary(d, key);
		result = putInDictionary(d, key, value);
		return result;
	}
	return result;
}

/*****************************************************************************
*Function name: getFromDictionary.
*Input: Dictionary* d, int key.
*Output: int (The value the key holds).
*Function operation: The function finds the value of the given key.
					 If a value isn't found, return 0.
*****************************************************************************/
int getFromDictionary(Dictionary* d, int key) {
	KeyValue keyValue;
	keyValue.key = key;
	BinTree* treeTemp = findInBinTree(d->dicTree, &keyValue);
	if (treeTemp != NULL) {
		KeyValue* keyTemp = (KeyValue*)createCopyOfValueInRoot(treeTemp);
		if (keyTemp == NULL) {
			return 0;
		}
		int val = keyTemp->value;
		free(keyTemp);
		return val;
	}
	return 0;
}

/*****************************************************************************
*Function name: initDictionary.
*Input: None.
*Output: Dictionary* (a pointer to Dictionary, if malloc fails, returns NULL).
*Function operation: The function initializes a Dictionary with a pointer
					 to a BinTree.
					 If one of the functions fails, we free the memory.
*****************************************************************************/
Result removeFromDictionary(Dictionary* d, int key) {
	KeyValue keyValue;
	keyValue.key = key;
	BinTree** binTreeTemp = &(d->dicTree);
	Result result = removeFromBinTree(binTreeTemp, &keyValue);
	return result;
}

/*****************************************************************************
*Function name: initDictionary.
*Input: None.
*Output: Dictionary* (a pointer to Dictionary, if malloc fails, returns NULL).
*Function operation: The function initializes a Dictionary with a pointer
					 to a BinTree.
					 If one of the functions fails, we free the memory.
*****************************************************************************/
void printDictionary(Dictionary* d) {
	printf("{");
	printInOrder(d->dicTree);
	printf("}");
}

/*****************************************************************************
*Function name: initDictionary.
*Input: None.
*Output: Dictionary* (a pointer to Dictionary, if malloc fails, returns NULL).
*Function operation: The function initializes a Dictionary with a pointer
					 to a BinTree.
					 If one of the functions fails, we free the memory.
*****************************************************************************/
Dictionary* createDictionaryFromArrays(int keys[], int values[], int size) {
	Dictionary* d = initDictionary();
	if (d == NULL) {
		return NULL;
	}
	for (int i = 0; i < size; i++) {
		putInDictionary(d, keys[i], values[i]);
	}
	if (d->dicTree == NULL) {
		destroyDictionary(d);
		return NULL;
	}
	return d;
}
