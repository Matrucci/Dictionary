#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "C:/Users/Matan/Desktop/ITC/ass6/ass6/genericBinTree.h"
//#include "C:/Users/Matan/Desktop/ITC/ass6/ass6/genericBinTree.c"
#include "C:/Users/Matan/Desktop/ITC/ass6/ass6/result.h"
#include "C:/Users/Matan/Desktop/ITC/ass6/ass6/dictionary.h"
#include "C:/Users/Matan/Desktop/ITC/ass6/ass6/genericSort.h"
#include "intFunctions.h"

typedef struct BinTree {
	Ptr val;
	struct BinTree* left;
	struct BinTree* right;
	BinTreeFunctions funcs;
} BinTree;


typedef struct Dictionary {
	BinTree* dicTree;
} Dictionary;

typedef struct KeyValue {
	int key; 
	int value;
} KeyValue;

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

void destroyDictionary(Dictionary* d) {
	printInOrder(d->dicTree);
	/*
	if (d->dicTree != NULL) {
		destroyBinTree(d->dicTree);
	}
	if (d != NULL) {
		free(d);
	}
	*/
}

int sizeOfDictionary(Dictionary* d) {
	return sizeOfBinTree(d->dicTree);
}

Result putInDictionary(Dictionary* d, int key, int value) {
	KeyValue keyValue;
	keyValue.key = key;
	keyValue.value = value;
	Result result = addToBinTree(d->dicTree, &keyValue);
	/*
	KeyValue* keyValue = (KeyValue*)malloc(sizeof(KeyValue));
	if (keyValue != NULL) {
		keyValue->key = key;
		keyValue->value = value;
		Result result = addToBinTree(d->dicTree, keyValue);
		free(keyValue);
		return result;
	}
	return MEM_ERROR;
	*/
}

int getFromDictionary(Dictionary* d, int key) {
	KeyValue keyValue;
	keyValue.key = key;
	BinTree* treeTemp = findInBinTree(d->dicTree, &keyValue);
	if (treeTemp != NULL) {
		KeyValue* keyTemp = treeTemp->val;
		return keyTemp->value;
	}
	/*
	KeyValue* keyValue = (KeyValue*)malloc(sizeof(KeyValue));
	if (keyValue != NULL) {
		keyValue->key = key;
		BinTree* treeTemp = findInBinTree(d->dicTree, keyValue);
		if (treeTemp != NULL) {
			keyValue = treeTemp->val;
			int v = keyValue->value;
			free(keyValue);
			return v;
		}
		return 0;
		//destroyBinTree(treeTemp);
	}
	return 0;
	*/
}

Result removeFromDictionary(Dictionary* d, int key) {
	KeyValue keyValue;
	keyValue.key = key;
	Result result = removeFromBinTree(d, &keyValue);
	return result;
	/*
	KeyValue* keyValue = (KeyValue*)malloc(sizeof(KeyValue));
	if (keyValue != NULL) {
		keyValue->key = key;
		Result result = removeFromBinTree(&(d->dicTree), keyValue);
		free(keyValue);
		return result;
	}
	return MEM_ERROR;
	*/
}

void printDictionary(Dictionary* d) {
	printf("{");
	printInOrder(d->dicTree);
	printf("}");
}

//BinTree* createBinTreeFromArr(BinTreeFunctions funcs, Ptr arr[], int size);

/*
Dictionary* createDictionaryFromArrays(int keys[], int values[], int size) {
	Dictionary* dic = initDictionary();
	if (dic == NULL) {
		return NULL;
	}
	KeyValue** keyValues;
	if (keyValues != NULL) {
		int j = 0;
		for (int i = 0; i < size; i++) {
			keyValues[j] = keys[i];
			j++;
			keyValues[j] = values[i];
			j++;
		}
		dic->dicTree = createBinTreeFromArr(int_funcs, keyValues, size);
		free(keyValues);
	}
	return dic;
}*/