#include "test.h"
#include "stack.h"

TEST(stack_test_create_destroy) {
   Stack* s1 = stack_create(sizeof(int), 4);
   ASSERT_TRUE(s1 != NULL);

   stack_destroy(&s1);
   ASSERT_TRUE(s1 == NULL);
}

TEST(stack_test_push_peek) {
   Stack* s1 = stack_create(sizeof(int), 2);
   int x = 0;
   int y;
   for (size_t i = 0; i < 10; i++) {
      stack_push(s1, &x);
      stack_peek(s1, &y);
      ASSERT_TRUE(x == y);
      x++;
   }
}

TEST(stack_test_pop_empty) {
   Stack* s1 = stack_create(sizeof(long), 4);
   long x = 0;
   for (size_t i = 0; i < 10; i++) {
      stack_push(s1, &x);
      x++;
   }

   for (size_t i = 0; i < 10; i++) {
      stack_pop(s1, &x);
      ASSERT_TRUE(x == (long)(9-i));
   }

   ASSERT_TRUE(stack_is_empty(s1));
}
