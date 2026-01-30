#include "test.h"
#include "hash_map.h"

TEST(t_hash_map_create_destroy) {
  HashMap* hp = hash_map_create(sizeof(int), 10, NULL, NULL, NULL);
  ASSERT_TRUE(hp != NULL);

  hash_map_destroy(&hp);
  ASSERT_TRUE(hp == NULL);
}
