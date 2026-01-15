#include "test.h"
#include "linked_list.h"

// BEHAVIOR TESTS

TEST(t_linked_list_create_destroy) {
    LinkedList* list = linked_list_create(sizeof(int));
    ASSERT_TRUE(list != NULL);

    linked_list_destroy(&list);
    ASSERT_TRUE(list == NULL);
}

// ERROR CASE TESTS
