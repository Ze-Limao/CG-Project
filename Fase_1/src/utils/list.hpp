#ifndef LIST
#define LIST
#include <stdlib.h>
#include <variant>

#define STDSIZE 100


using namespace std;

typedef struct list* List;

List newEmptyList();

int listIsFull(List);

void addValueToList(List, void*);

void** getListValues(List);

unsigned long getListLength(List);

void* getListElemAt(List, unsigned long);

void deleteList(List);

void deepDeleteList(List, void (*)(void *));

#endif // LIST