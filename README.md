# Plain C Data Structures

A small plain C (C23) collection of generic data structures based on `void*` values.

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

Every function tolerates a null container (it returns `nullptr`, `false` or `0`), so error handling can be deferred to the end of a sequence of calls. Functions that allocate return `false` or `nullptr` when memory runs out and leave the container unchanged.

## Build

Requires a C23 compiler: GCC 14+ or Clang 18+ (`-std=c23`; GCC 13 accepts the same code as `-std=c2x`), MSVC with `/std:clatest`.

```sh
make            # builds libplaincds.a
make clean
```

Or compile the sources straight into your project:

```sh
gcc -std=c23 -O2 -Wall -Wextra -Wpedantic -c *.c
```

## Single Linked List

Create and delete a list:

```c
SingleLinkedList* list = SingleLinkedList_Create();
SingleLinkedList_Delete(list);
```

Add at either end, remove from either end:

```c
SingleLinkedList_Add(list, &a);                   // tail, O(1)
SingleLinkedList_AddFirst(list, &b);              // head, O(1)
void* first = SingleLinkedList_RemoveFirst(list); // head, O(1)
void* last = SingleLinkedList_Remove(list);       // tail, O(n) - a singly linked list has to find the node before the tail
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

Iterate over a list. Callbacks get the `context` pointer you pass in, so there is no need for globals:

```c
void add_to_sum(void* value, void* context)
{
    *(int*)context += *(int*)value;
}

int sum = 0;
SingleLinkedList_Foreach(list, add_to_sum, &sum);
```

Count elements (O(1), the count is maintained):

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

Look at either end without removing, or remove any node you hold:

```c
void* first = DoubleLinkedList_First(list);
void* last = DoubleLinkedList_Last(list);
void* value = DoubleLinkedList_RemoveNode(list, node);
```

Insert next to a known node:

```c
DoubleLinkedListNode* first = DoubleLinkedList_Add(list, &a);
DoubleLinkedList_Add(list, &b);
DoubleLinkedList_InsertAfter(list, first, &c);  // result: 1, 3, 2
DoubleLinkedList_InsertBefore(list, first, &d); // result: 4, 1, 3, 2
```

All of the above are O(1). Iterate forward and backward:

```c
DoubleLinkedList_Foreach(list, callback, context);
DoubleLinkedList_ForeachReverse(list, callback, context);
```

Count elements (O(1)):

```c
size_t count = DoubleLinkedList_Count(list);
```

Clear nodes without deleting the list object:

```c
DoubleLinkedList_Clear(list);
```

A list can also live inside another struct; `DoubleLinkedList_Init` resets it in place without allocating. The stack, queue and deque are built that way.

## Stack

LIFO container on top of the doubly linked list; every operation is O(1).

```c
Stack* stack = Stack_Create();

Stack_Push(stack, &a);
Stack_Push(stack, &b);

int top = *((int*)Stack_Peek(stack));  // b, still on the stack
int value = *((int*)Stack_Pop(stack)); // b

Stack_Delete(stack);
```

Count elements, or drop them all:

```c
size_t count = Stack_Count(stack);
Stack_Clear(stack);
```

## Queue

FIFO container on top of the doubly linked list; every operation is O(1).

```c
Queue* queue = Queue_Create();

Queue_Enqueue(queue, &a);
Queue_Enqueue(queue, &b);

int next = *((int*)Queue_Peek(queue));     // a, still queued
int value = *((int*)Queue_Dequeue(queue)); // a

Queue_Delete(queue);
```

Count elements, or drop them all:

```c
size_t count = Queue_Count(queue);
Queue_Clear(queue);
```

## Deque

Double-ended queue on top of the doubly linked list; every operation is O(1).

```c
Deque* deque = Deque_Create();

Deque_PushBack(deque, &b);
Deque_PushFront(deque, &a);

int front = *((int*)Deque_PeekFront(deque)); // a
int back = *((int*)Deque_PeekBack(deque));   // b
int first = *((int*)Deque_PopFront(deque));  // a
int last = *((int*)Deque_PopBack(deque));    // b

Deque_Delete(deque);
```

Count elements, or drop them all:

```c
size_t count = Deque_Count(deque);
Deque_Clear(deque);
```

## Dynamic Array

A resizable array of `void*` values.

```c
DynamicArray* array = DynamicArray_Create();

DynamicArray_Add(array, &a);
DynamicArray_Add(array, &b);
DynamicArray_Insert(array, 1, &c);  // a, c, b

int first = *((int*)DynamicArray_Get(array, 0));
DynamicArray_Set(array, 1, &d);

void* removed = DynamicArray_RemoveAt(array, 0);
void* last = DynamicArray_RemoveLast(array);

DynamicArray_Delete(array);
```

Create with initial capacity, or grow it ahead of a batch of adds:

```c
DynamicArray* array = DynamicArray_CreateWithCapacity(16);
DynamicArray_Reserve(array, 1000);
```

Iterate, count and capacity:

```c
DynamicArray_Foreach(array, callback, context);
size_t count = DynamicArray_Count(array);
size_t capacity = DynamicArray_Capacity(array);
```

`Add` is amortized O(1); `Insert` and `RemoveAt` move the tail of the array with `memmove`.

## Priority Queue

A min-priority queue implemented as a binary heap over `void*` values. You provide a comparison function. Values that compare as smaller are dequeued first.

```c
static int compare_ints(const void* left, const void* right)
{
    int a = *(const int*)left;
    int b = *(const int*)right;

    return (a > b) - (a < b);
}

PriorityQueue* queue = PriorityQueue_Create(compare_ints);

PriorityQueue_Enqueue(queue, &low_value);
PriorityQueue_Enqueue(queue, &high_value);

void* next = PriorityQueue_Peek(queue);
void* removed = PriorityQueue_Dequeue(queue);

PriorityQueue_Delete(queue);
```

Create with initial capacity, or reserve:

```c
PriorityQueue* queue = PriorityQueue_CreateWithCapacity(compare_ints, 16);
PriorityQueue_Reserve(queue, 1000);
```

Count and capacity:

```c
size_t count = PriorityQueue_Count(queue);
size_t capacity = PriorityQueue_Capacity(queue);
```

`Enqueue` and `Dequeue` are O(log n), `Peek` is O(1).

## Hash Map

A string-keyed hash map with separate chaining. Each entry remembers its hash, so lookups compare strings only on a hash match and growing the table does not rehash the keys.

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

Create with a specific bucket count (the table doubles whenever it is more than 3/4 full):

```c
HashMap* map = HashMap_CreateWithBucketCount(32);
```

Iterate (in no particular order) and count:

```c
void print_entry(const char* key, void* value, void* context)
{
    printf("%s = %d\n", key, *(int*)value);
}

HashMap_Foreach(map, print_entry, nullptr);
size_t count = HashMap_Count(map);
```

## Binary Search Tree

An unbalanced binary search tree over `void*` values. You provide a comparison function. Inserting a value equal to a stored one replaces it.

```c
BinarySearchTree* tree = BinarySearchTree_Create(compare_ints);

BinarySearchTree_Insert(tree, &a);
BinarySearchTree_Insert(tree, &b);

void* found = BinarySearchTree_Find(tree, &a);
bool has = BinarySearchTree_Contains(tree, &a);
void* smallest = BinarySearchTree_Min(tree);
void* largest = BinarySearchTree_Max(tree);
void* removed = BinarySearchTree_Remove(tree, &b);

BinarySearchTree_Delete(tree);
```

In-order traversal (ascending). The tree must not be modified from the callback:

```c
BinarySearchTree_ForeachInOrder(tree, callback, context);
```

Count elements:

```c
size_t count = BinarySearchTree_Count(tree);
```

No operation recurses: traversal is a Morris walk and clearing rotates the tree flat as it frees it, so a degenerate (list-shaped) tree of a million nodes is slow to search but never overflows the stack.

## Layout

```
capacity.h            internal: growth policy shared by the array-backed containers
single-linked-list.*  double-linked-list.*
stack.*  queue.*  deque.*       adapters over the doubly linked list
dynamic-array.*  priority-queue.*
hash-map.*  binary-search-tree.*
Makefile              builds libplaincds.a
```

## Notes

The API is intentionally small and plain. It avoids ownership callbacks, custom allocators, macros, and type-specific code generation.

For production use, you would normally add more explicit ownership rules, better error reporting, and probably typed wrappers or macros.

## Support

If you found this project interesting or useful, you can support my work:

[![GitHub Sponsors](https://img.shields.io/github/sponsors/makarov-mm?style=flat&logo=github)](https://github.com/sponsors/makarov-mm)
