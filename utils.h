#include <cstdlib>

inline int uniform_random(int lower, int upper) {
  int range = upper - lower + 1;
  int limit = RAND_MAX - (RAND_MAX % range);
  int r;
  do {
    r = rand();
  } while (r >= limit);
  return (r % range) + lower;
}
