# Plain C Data Structures

A small plain C collection of generic data structures based on `void*` values.

Included containers:

- singly linked list
- doubly linked list
- stack
- queue
- deque
- dynamic array
- priority queue
- string-keyed hash map
- binary search tree

The containers own and free only their internal nodes, entries, arrays, and tree nodes. They do not free the values stored in `void*`.

`HashMap` also does not copy or free string keys. The key pointer must remain valid while the entry exists in the map.

## Build

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -c *.c
```

Or use the included Makefile:

```sh
make
make test
```

## Single Linked List

Create and delete a list:

```c
SingleLinkedList* list = SingleLinkedList_Create();
SingleLinkedList_Delete(list);
```

Add and remove elements at/from the tail:

```c
SingleLinkedList_Add(list, &a);
void* value = SingleLinkedList_Remove(list);
```

Insert after a known node:

```c
int a = 1;
int b = 2;
int c = 3;

SingleLinkedList* list = SingleLinkedList_Create();
SingleLinkedListNode* first = SingleLinkedList_Add(list, &a);
SingleLinkedList_Add(list, &b);

SingleLinkedList_InsertAfter(list, first, &c); // result: 1, 3, 2
SingleLinkedList_Delete(list);
```

Iterate over a list:

```c
void callback(void* value)
{
    int integer = *((int*)value);
    printf("%d\n", integer);
}

SingleLinkedList_Foreach(list, callback);
```

Count elements:

```c
size_t count = SingleLinkedList_Count(list);
```

Clear nodes without deleting the list object:

```c
SingleLinkedList_Clear(list);
```

## Double Linked List

Create and delete a list:

```c
DoubleLinkedList* list = DoubleLinkedList_Create();
DoubleLinkedList_Delete(list);
```

Add and remove elements at/from the tail:

```c
DoubleLinkedList_Add(list, &a);
void* value = DoubleLinkedList_Remove(list);
```

Add and remove elements at/from the head:

```c
DoubleLinkedList_AddFirst(list, &a);
void* value = DoubleLinkedList_RemoveFirst(list);
```

`DoubleLinkedList_Remove` and `DoubleLinkedList_RemoveFirst` both work in `O(1)` time.

Insert after a known node:

```c
DoubleLinkedListNode* first = DoubleLinkedList_Add(list, &a);
DoubleLinkedList_Add(list, &b);
DoubleLinkedList_InsertAfter(list, first, &c); // result: 1, 3, 2
```

Iterate forward and backward:

```c
DoubleLinkedList_Foreach(list, callback);
DoubleLinkedList_ForeachReverse(list, callback);
```

Count elements:

```c
size_t count = DoubleLinkedList_Count(list);
```

Clear nodes without deleting the list object:

```c
DoubleLinkedList_Clear(list);
```

## Stack

LIFO container implemented on top of the doubly linked list.

```c
Stack* stack = Stack_Create();

Stack_Push(stack, &a);
Stack_Push(stack, &b);

int value = *((int*)Stack_Pop(stack)); // b

Stack_Delete(stack);
```

Count elements:

```c
size_t count = Stack_Count(stack);
```

## Queue

FIFO container implemented on top of the doubly linked list.

```c
Queue* queue = Queue_Create();

Queue_Enqueue(queue, &a);
Queue_Enqueue(queue, &b);

int value = *((int*)Queue_Dequeue(queue)); // a

Queue_Delete(queue);
```

Count elements:

```c
size_t count = Queue_Count(queue);
```

## Deque

Double-ended queue implemented on top of the doubly linked list.

```c
Deque* deque = Deque_Create();

Deque_PushBack(deque, &b);
Deque_PushFront(deque, &a);

int first = *((int*)Deque_PopFront(deque)); // a
int last = *((int*)Deque_PopBack(deque));   // b

Deque_Delete(deque);
```

Count elements:

```c
size_t count = Deque_Count(deque);
```

## Dynamic Array

A resizable array of `void*` values.

```c
DynamicArray* array = DynamicArray_Create();

DynamicArray_Add(array, &a);
DynamicArray_Add(array, &b);

int first = *((int*)DynamicArray_Get(array, 0));
DynamicArray_Set(array, 1, &c);

void* removed = DynamicArray_RemoveAt(array, 0);

DynamicArray_Delete(array);
```

Create with initial capacity:

```c
DynamicArray* array = DynamicArray_CreateWithCapacity(16);
```

Count and capacity:

```c
size_t count = DynamicArray_Count(array);
size_t capacity = DynamicArray_Capacity(array);
```


## Priority Queue

A min-priority queue implemented as a binary heap over `void*` values. You provide a comparison function. Values that compare as smaller are dequeued first.

```c
static int compare_ints(const void* left, const void* right)
{
    int a = *(const int*)left;
    int b = *(const int*)right;

    if (a < b)
    {
        return -1;
    }

    if (a > b)
    {
        return 1;
    }

    return 0;
}

PriorityQueue* queue = PriorityQueue_Create(compare_ints);

PriorityQueue_Enqueue(queue, &low_value);
PriorityQueue_Enqueue(queue, &high_value);

void* next = PriorityQueue_Peek(queue);
void* removed = PriorityQueue_Dequeue(queue);

PriorityQueue_Delete(queue);
```

Create with initial capacity:

```c
PriorityQueue* queue = PriorityQueue_CreateWithCapacity(compare_ints, 16);
```

Count and capacity:

```c
size_t count = PriorityQueue_Count(queue);
size_t capacity = PriorityQueue_Capacity(queue);
```

## Hash Map

A string-keyed hash map with separate chaining.

The map stores the key pointer as-is. It does not duplicate key strings. Use string literals, static strings, or keep dynamically allocated keys alive while they are stored in the map.

```c
HashMap* map = HashMap_Create();

HashMap_Put(map, "answer", &value);

if (HashMap_ContainsKey(map, "answer"))
{
    int answer = *((int*)HashMap_Get(map, "answer"));
}

void* removed = HashMap_Remove(map, "answer");

HashMap_Delete(map);
```

Create with a specific bucket count:

```c
HashMap* map = HashMap_CreateWithBucketCount(32);
```

Count elements:

```c
size_t count = HashMap_Count(map);
```

## Binary Search Tree

A binary search tree over `void*` values. You provide a comparison function.

```c
static int compare_ints(const void* left, const void* right)
{
    int a = *(const int*)left;
    int b = *(const int*)right;

    if (a < b)
    {
        return -1;
    }

    if (a > b)
    {
        return 1;
    }

    return 0;
}

BinarySearchTree* tree = BinarySearchTree_Create(compare_ints);

BinarySearchTree_Insert(tree, &a);
BinarySearchTree_Insert(tree, &b);

void* found = BinarySearchTree_Find(tree, &a);
void* removed = BinarySearchTree_Remove(tree, &b);

BinarySearchTree_Delete(tree);
```

In-order traversal:

```c
BinarySearchTree_ForeachInOrder(tree, callback);
```

Count elements:

```c
size_t count = BinarySearchTree_Count(tree);
```

## Notes

The API is intentionally small and plain. It avoids ownership callbacks, custom allocators, macros, and type-specific code generation.

The previous `InsertAt(node, value)` API was replaced with `InsertAfter(list, node, value)`. The list argument is required to preserve the `tail` invariant when inserting after the current tail.

For production use, you would normally add more explicit ownership rules, better error reporting, more removal operations, and probably typed wrappers or macros. For a compact C data-structures library, this version keeps the old style but fixes the most obvious correctness issues.

## Support

If you found this project interesting or useful, you can support my work:

[![GitHub Sponsors](https://img.shields.io/github/sponsors/makarov-mm?style=flat&logo=github)](https://github.com/sponsors/makarov-mm)
