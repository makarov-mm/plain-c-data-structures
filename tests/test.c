#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "../single-linked-list.h"
#include "../double-linked-list.h"
#include "../stack.h"
#include "../queue.h"
#include "../deque.h"
#include "../dynamic-array.h"
#include "../priority-queue.h"
#include "../hash-map.h"
#include "../binary-search-tree.h"

static int visited_sum;

static void add_to_sum(void* value)
{
    visited_sum += *(int*)value;
}

static int compare_ints(const void* left, const void* right)
{
    int left_value = *(const int*)left;
    int right_value = *(const int*)right;

    if (left_value < right_value)
    {
        return -1;
    }

    if (left_value > right_value)
    {
        return 1;
    }

    return 0;
}

static void test_single_linked_list(void)
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    SingleLinkedList* list = SingleLinkedList_Create();
    assert(list);
    assert(SingleLinkedList_Count(list) == 0);

    SingleLinkedListNode* first = SingleLinkedList_Add(list, &a);
    assert(first);
    assert(list->head == first);
    assert(list->tail == first);

    SingleLinkedListNode* second = SingleLinkedList_Add(list, &b);
    assert(second);
    assert(list->head == first);
    assert(list->tail == second);
    assert(SingleLinkedList_Count(list) == 2);

    SingleLinkedListNode* third = SingleLinkedList_InsertAfter(list, second, &c);
    assert(third);
    assert(list->tail == third);
    assert(SingleLinkedList_Count(list) == 3);

    SingleLinkedListNode* inserted = SingleLinkedList_InsertAfter(list, first, &d);
    assert(inserted);
    assert(first->next == inserted);
    assert(inserted->next == second);
    assert(list->tail == third);
    assert(SingleLinkedList_Count(list) == 4);

    visited_sum = 0;
    SingleLinkedList_Foreach(list, add_to_sum);
    assert(visited_sum == 10);

    assert(*(int*)SingleLinkedList_Remove(list) == 3);
    assert(*(int*)SingleLinkedList_Remove(list) == 2);
    assert(*(int*)SingleLinkedList_Remove(list) == 4);
    assert(*(int*)SingleLinkedList_Remove(list) == 1);
    assert(SingleLinkedList_Remove(list) == NULL);
    assert(SingleLinkedList_Count(list) == 0);

    SingleLinkedList_Delete(list);
    SingleLinkedList_Delete(NULL);
}

static void test_double_linked_list(void)
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;

    DoubleLinkedList* list = DoubleLinkedList_Create();
    assert(list);
    assert(DoubleLinkedList_Count(list) == 0);

    DoubleLinkedListNode* first = DoubleLinkedList_Add(list, &a);
    DoubleLinkedListNode* second = DoubleLinkedList_Add(list, &b);
    assert(first);
    assert(second);
    assert(second->prev == first);
    assert(list->tail == second);

    DoubleLinkedListNode* third = DoubleLinkedList_InsertAfter(list, second, &c);
    assert(third);
    assert(third->prev == second);
    assert(list->tail == third);

    DoubleLinkedListNode* zero = DoubleLinkedList_AddFirst(list, &e);
    assert(zero);
    assert(list->head == zero);
    assert(zero->next == first);
    assert(first->prev == zero);

    DoubleLinkedListNode* inserted = DoubleLinkedList_InsertAfter(list, first, &d);
    assert(inserted);
    assert(first->next == inserted);
    assert(inserted->prev == first);
    assert(inserted->next == second);
    assert(second->prev == inserted);
    assert(list->tail == third);
    assert(DoubleLinkedList_Count(list) == 5);

    visited_sum = 0;
    DoubleLinkedList_Foreach(list, add_to_sum);
    assert(visited_sum == 15);

    visited_sum = 0;
    DoubleLinkedList_ForeachReverse(list, add_to_sum);
    assert(visited_sum == 15);

    assert(*(int*)DoubleLinkedList_RemoveFirst(list) == 5);
    assert(*(int*)DoubleLinkedList_Remove(list) == 3);
    assert(*(int*)DoubleLinkedList_Remove(list) == 2);
    assert(*(int*)DoubleLinkedList_Remove(list) == 4);
    assert(*(int*)DoubleLinkedList_Remove(list) == 1);
    assert(DoubleLinkedList_Remove(list) == NULL);
    assert(DoubleLinkedList_RemoveFirst(list) == NULL);
    assert(DoubleLinkedList_Count(list) == 0);

    DoubleLinkedList_Delete(list);
    DoubleLinkedList_Delete(NULL);
}

static void test_stack(void)
{
    int a = 1;
    int b = 2;

    Stack* stack = Stack_Create();
    assert(stack);
    assert(Stack_Count(stack) == 0);

    Stack_Push(stack, &a);
    Stack_Push(stack, &b);
    assert(Stack_Count(stack) == 2);

    assert(*(int*)Stack_Pop(stack) == 2);
    assert(*(int*)Stack_Pop(stack) == 1);
    assert(Stack_Pop(stack) == NULL);
    assert(Stack_Count(stack) == 0);

    Stack_Delete(stack);
    Stack_Delete(NULL);
}

static void test_queue(void)
{
    int a = 1;
    int b = 2;
    int c = 3;

    Queue* queue = Queue_Create();
    assert(queue);
    assert(Queue_Count(queue) == 0);

    Queue_Enqueue(queue, &a);
    Queue_Enqueue(queue, &b);
    Queue_Enqueue(queue, &c);
    assert(Queue_Count(queue) == 3);

    assert(*(int*)Queue_Dequeue(queue) == 1);
    assert(*(int*)Queue_Dequeue(queue) == 2);
    assert(*(int*)Queue_Dequeue(queue) == 3);
    assert(Queue_Dequeue(queue) == NULL);
    assert(Queue_Count(queue) == 0);

    Queue_Delete(queue);
    Queue_Delete(NULL);
}

static void test_deque(void)
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    Deque* deque = Deque_Create();
    assert(deque);

    Deque_PushBack(deque, &b);
    Deque_PushFront(deque, &a);
    Deque_PushBack(deque, &c);
    Deque_PushFront(deque, &d);
    assert(Deque_Count(deque) == 4);

    assert(*(int*)Deque_PopFront(deque) == 4);
    assert(*(int*)Deque_PopBack(deque) == 3);
    assert(*(int*)Deque_PopFront(deque) == 1);
    assert(*(int*)Deque_PopBack(deque) == 2);
    assert(Deque_PopBack(deque) == NULL);
    assert(Deque_PopFront(deque) == NULL);
    assert(Deque_Count(deque) == 0);

    Deque_Delete(deque);
    Deque_Delete(NULL);
}

static void test_dynamic_array(void)
{
    int values[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int replacement = 42;

    DynamicArray* array = DynamicArray_CreateWithCapacity(2);
    assert(array);
    assert(DynamicArray_Count(array) == 0);
    assert(DynamicArray_Capacity(array) >= 2);

    for (size_t i = 0; i < 8; ++i)
    {
        assert(DynamicArray_Add(array, &values[i]));
    }

    assert(DynamicArray_Count(array) == 8);
    assert(*(int*)DynamicArray_Get(array, 0) == 1);
    assert(*(int*)DynamicArray_Get(array, 7) == 8);
    assert(DynamicArray_Get(array, 8) == NULL);

    assert(DynamicArray_Set(array, 3, &replacement));
    assert(*(int*)DynamicArray_Get(array, 3) == 42);
    assert(!DynamicArray_Set(array, 8, &replacement));

    assert(*(int*)DynamicArray_RemoveAt(array, 3) == 42);
    assert(*(int*)DynamicArray_Get(array, 3) == 5);
    assert(DynamicArray_Count(array) == 7);
    assert(DynamicArray_RemoveAt(array, 100) == NULL);

    DynamicArray_Clear(array);
    assert(DynamicArray_Count(array) == 0);

    DynamicArray_Delete(array);
    DynamicArray_Delete(NULL);
}

static void test_priority_queue(void)
{
    int values[] = { 5, 1, 4, 2, 3 };

    PriorityQueue* queue = PriorityQueue_CreateWithCapacity(compare_ints, 2);
    assert(queue);
    assert(PriorityQueue_Count(queue) == 0);
    assert(PriorityQueue_Capacity(queue) >= 2);

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
    {
        assert(PriorityQueue_Enqueue(queue, &values[i]));
    }

    assert(PriorityQueue_Count(queue) == 5);
    assert(*(int*)PriorityQueue_Peek(queue) == 1);

    for (int expected = 1; expected <= 5; ++expected)
    {
        assert(*(int*)PriorityQueue_Dequeue(queue) == expected);
    }

    assert(PriorityQueue_Dequeue(queue) == NULL);
    assert(PriorityQueue_Peek(queue) == NULL);
    assert(PriorityQueue_Count(queue) == 0);

    assert(PriorityQueue_Enqueue(queue, &values[0]));
    PriorityQueue_Clear(queue);
    assert(PriorityQueue_Count(queue) == 0);

    PriorityQueue_Delete(queue);
    PriorityQueue_Delete(NULL);
    assert(PriorityQueue_Create(NULL) == NULL);
}

static void test_hash_map(void)
{
    int one = 1;
    int two = 2;
    int three = 3;
    int updated = 22;

    HashMap* map = HashMap_CreateWithBucketCount(2);
    assert(map);
    assert(HashMap_Count(map) == 0);

    assert(HashMap_Put(map, "one", &one));
    assert(HashMap_Put(map, "two", &two));
    assert(HashMap_Put(map, "three", &three));
    assert(HashMap_Count(map) == 3);

    assert(*(int*)HashMap_Get(map, "one") == 1);
    assert(*(int*)HashMap_Get(map, "two") == 2);
    assert(HashMap_Get(map, "missing") == NULL);
    assert(HashMap_ContainsKey(map, "three"));
    assert(!HashMap_ContainsKey(map, "missing"));

    assert(HashMap_Put(map, "two", &updated));
    assert(HashMap_Count(map) == 3);
    assert(*(int*)HashMap_Get(map, "two") == 22);

    assert(*(int*)HashMap_Remove(map, "two") == 22);
    assert(!HashMap_ContainsKey(map, "two"));
    assert(HashMap_Remove(map, "two") == NULL);
    assert(HashMap_Count(map) == 2);

    HashMap_Clear(map);
    assert(HashMap_Count(map) == 0);

    HashMap_Delete(map);
    HashMap_Delete(NULL);
}

static void test_binary_search_tree(void)
{
    int values[] = { 5, 3, 7, 2, 4, 6, 8 };
    int find_value = 4;
    int missing_value = 10;
    int remove_leaf = 2;
    int remove_one_child = 3;
    int remove_two_children = 7;
    int duplicate = 4;

    BinarySearchTree* tree = BinarySearchTree_Create(compare_ints);
    assert(tree);
    assert(BinarySearchTree_Count(tree) == 0);

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
    {
        assert(BinarySearchTree_Insert(tree, &values[i]));
    }

    assert(BinarySearchTree_Count(tree) == 7);
    assert(*(int*)BinarySearchTree_Find(tree, &find_value) == 4);
    assert(BinarySearchTree_Find(tree, &missing_value) == NULL);

    assert(BinarySearchTree_Insert(tree, &duplicate));
    assert(BinarySearchTree_Count(tree) == 7);

    visited_sum = 0;
    BinarySearchTree_ForeachInOrder(tree, add_to_sum);
    assert(visited_sum == 35);

    assert(*(int*)BinarySearchTree_Remove(tree, &remove_leaf) == 2);
    assert(BinarySearchTree_Count(tree) == 6);
    assert(BinarySearchTree_Find(tree, &remove_leaf) == NULL);

    assert(*(int*)BinarySearchTree_Remove(tree, &remove_one_child) == 3);
    assert(BinarySearchTree_Count(tree) == 5);
    assert(BinarySearchTree_Find(tree, &remove_one_child) == NULL);

    assert(*(int*)BinarySearchTree_Remove(tree, &remove_two_children) == 7);
    assert(BinarySearchTree_Count(tree) == 4);
    assert(BinarySearchTree_Find(tree, &remove_two_children) == NULL);

    assert(BinarySearchTree_Remove(tree, &missing_value) == NULL);
    assert(BinarySearchTree_Count(tree) == 4);

    BinarySearchTree_Clear(tree);
    assert(BinarySearchTree_Count(tree) == 0);

    BinarySearchTree_Delete(tree);
    BinarySearchTree_Delete(NULL);
    assert(BinarySearchTree_Create(NULL) == NULL);
}

int main(void)
{
    test_single_linked_list();
    test_double_linked_list();
    test_stack();
    test_queue();
    test_deque();
    test_dynamic_array();
    test_priority_queue();
    test_hash_map();
    test_binary_search_tree();

    return 0;
}
