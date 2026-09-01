#include <assert.h>
#include <stdlib.h>

#define DYNARR_INIT_CAPACITY 8

#define dynarr_reserve(dynarr, additional)                                     \
    do {                                                                       \
        size_t min_capacity = (dynarr)->len + (additional);                    \
        if (min_capacity > (dynarr)->capacity) {                               \
            if ((dynarr)->capacity == 0) {                                     \
                (dynarr)->capacity = DYNARR_INIT_CAPACITY;                     \
            }                                                                  \
            while (min_capacity > (dynarr)->capacity) {                        \
                (dynarr)->capacity *= 2;                                       \
            }                                                                  \
            (dynarr)->items = realloc(                                         \
                (dynarr)->items, (dynarr)->capacity * sizeof(*(dynarr)->items) \
            );                                                                 \
            assert((dynarr)->items != NULL && "Out of memory!");               \
        }                                                                      \
    } while (0)

#define dynarr_init(dynarr)     \
    do {                        \
        (dynarr)->items = NULL; \
        (dynarr)->len = 0;      \
        (dynarr)->capacity = 0; \
    } while (0)

#define dynarr_init_capacity(dynarr, cap) \
    do {                                  \
        (dynarr)->items = NULL;           \
        (dynarr)->len = 0;                \
        (dynarr)->capacity = 0;           \
        dynarr_reserve((dynarr), (cap));  \
    } while (0)

#define dynarr_destroy(dynarr) free((dynarr)->items)

#define dynarr_append(dynarr, item)                \
    do {                                           \
        dynarr_reserve((dynarr), 1);               \
        (dynarr)->items[(dynarr)->len++] = (item); \
    } while (0)
