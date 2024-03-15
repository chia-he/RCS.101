#ifndef CSTACK_H_
#define CSTACK_H_

/**
 * in case C library malloc() needs extra protection,
 * allow these defines to be overridden.
 */
#ifndef cstack_clib_free
#include <stdlib.h> /* for free */
#define cstack_clib_free free
#endif
#ifndef cstack_clib_malloc
#include <stdlib.h> /* for malloc */
#define cstack_clib_malloc malloc
#endif
#ifndef cstack_clib_realloc
#include <stdlib.h> /* for realloc */
#define cstack_clib_realloc realloc
#endif
#ifndef cstack_clib_assert
#include <assert.h> /* for assert */
#define cstack_clib_assert assert
#endif
#ifndef cstack_clib_memcpy
#include <string.h> /* for memcpy */
#define cstack_clib_memcpy memcpy
#endif

typedef void (*cstack_elem_destructor_t)(void* elem);

typedef struct {
        size_t size;
        size_t capacity;
        cstack_elem_destructor_t elem_destructor;
} cstack_metadata_t;

/**
 * @brief cstack_stack_type - The stack type used in this library
 * @param type The type of stack to act on.
 */
#define cstack_stack_type(type) type*

/**
 * @brief cstack - Syntactic sugar to retrieve a stack type
 * @param type The type of stack to act on.
 */
#define cstack(type) cstack_stack_type(type)

/**
 * @brief cstack_stack_to_base - For internal use, converts a stack pointer to a
 * metadata pointer
 * @param stack__ - the stack
 * @return the metadata pointer of the stack
 * @internal
 */
#define cstack_stack_to_base(stack__) (&((cstack_metadata_t*)(stack__))[-1])

/**
 * @brief cstack_base_to_stack - For internal use, converts a metadata pointer
 * to a stack pointer
 * @param ptr - pointer to the metadata
 * @return the stack
 * @internal
 */
#define cstack_base_to_stack(ptr) ((void*)&((cstack_metadata_t*)(ptr))[1])

/**
 * @brief cstack_capacity - gets the current capacity of the stack
 * @param stack__ - the stack
 * @return the capacity as a size_t
 */
#define cstack_capacity(stack__) \
    ((stack__) ? cstack_stack_to_base(stack__)->capacity : (size_t)0)

/**
 * @brief cstack_size - gets the current size of the stack
 * @param stack__ - the stack
 * @return the size as a size_t
 */
#define cstack_size(stack__) \
    ((stack__) ? cstack_stack_to_base(stack__)->size : (size_t)0)

/**
 * @brief cstack_elem_destructor - get the element destructor function used
 * to clean up elements
 * @param stack__ - the stack
 * @return the function pointer as cstack_elem_destructor_t
 */
#define cstack_elem_destructor(stack__) \
    ((stack__) ? cstack_stack_to_base(stack__)->elem_destructor : NULL)

/**
 * @brief cstack_empty - returns non-zero if the stack is empty
 * @param stack__ - the stack
 * @return non-zero if empty, zero if non-empty
 */
#define cstack_empty(stack__) (cstack_size(stack__) == 0)

/**
 * @brief cstack_set_capacity - For internal use, sets the capacity variable of
 * the stack
 * @param stack__ - the stack
 * @param size - the new capacity to set
 * @return void
 * @internal
 */
#define cstack_set_capacity(stack__, size)                    \
    do {                                                      \
        if (stack__) {                                        \
            cstack_stack_to_base(stack__)->capacity = (size); \
        }                                                     \
    } while (0)

/**
 * @brief cstack_set_size - For internal use, sets the size variable of the
 * stack
 * @param stack__ - the stack
 * @param size - the new capacity to set
 * @return void
 * @internal
 */
#define cstack_set_size(stack__, _size)                    \
    do {                                                   \
        if (stack__) {                                     \
            cstack_stack_to_base(stack__)->size = (_size); \
        }                                                  \
    } while (0)

/**
 * @brief cstack_set_elem_destructor - set the element destructor function
 * used to clean up removed elements
 * @param stack__ - the stack
 * @param elem_destructor_fn - function pointer of type cstack_elem_destructor_t
 * used to destroy elements
 * @return void
 */
#define cstack_set_elem_destructor(stack__, elem_destructor_fn) \
    do {                                                        \
        if (stack__) {                                          \
            cstack_stack_to_base(stack__)->elem_destructor =    \
                (elem_destructor_fn);                           \
        }                                                       \
    } while (0)

/**
 * @brief cstack_grow - For internal use, ensures that the stack is at least
 * <count> elements big
 * @param stack__ - the stack
 * @param count - the new capacity to set
 * @return void
 * @internal
 */
#define cstack_grow(stack__, count)                                   \
    do {                                                              \
        const size_t cs_sz__ =                                        \
            (count) * sizeof(*(stack__)) + sizeof(cstack_metadata_t); \
        if (stack__) {                                                \
            void* cs_p1__ = cstack_stack_to_base(stack__);            \
            void* cs_p2__ = cstack_clib_realloc(cs_p1__, cs_sz__);    \
            cstack_clib_assert(cs_p2__);                              \
            (stack__) = cstack_base_to_stack(cs_p2__);                \
        } else {                                                      \
            void* cs_p__ = cstack_clib_malloc(cs_sz__);               \
            cstack_clib_assert(cs_p__);                               \
            (stack__) = cstack_base_to_stack(cs_p__);                 \
            cstack_set_size((stack__), 0);                            \
            cstack_set_elem_destructor((stack__), NULL);              \
        }                                                             \
        cstack_set_capacity((stack__), (count));                      \
    } while (0)

/**
 * @brief cstack_shrink_to_fit - requests the container to reduce its capacity
 * to fit its size
 * @param stack__ - the stack
 * @return void
 */
#define cstack_shrink_to_fit(stack__)                     \
    do {                                                  \
        if (stack__) {                                    \
            const size_t cs_sz___ = cstack_size(stack__); \
            cstack_grow(stack__, cs_sz___);               \
        }                                                 \
    } while (0)

/**
 * @brief cstack_reserve - Requests that the stack capacity be at least enough
 * to contain n elements. If n is greater than the current stack capacity, the
 * function causes the container to reallocate its storage increasing its
 * capacity to n (or greater).
 * @param stack__ - the stack
 * @param n - Minimum capacity for the stack.
 * @return void
 */
#define cstack_reserve(stack__, n)                  \
    do {                                            \
        size_t cs_cap__ = cstack_capacity(stack__); \
        if (cs_cap__ < (n)) {                       \
            cstack_grow((stack__), (n));            \
        }                                           \
    } while (0)

/**
 * @brief cstack_init - Initialize a stack.  The stack must be NULL for this to
 * do anything.
 * @param stack__ - the stack
 * @param capacity - stack capacity to reserve
 * @param elem_destructor_fn - element destructor function
 * @return void
 */
#define cstack_init(stack__, capacity, elem_destructor_fn)               \
    do {                                                                 \
        if (!(stack__)) {                                                \
            cstack_reserve((stack__), capacity);                         \
            cstack_set_elem_destructor((stack__), (elem_destructor_fn)); \
        }                                                                \
    } while (0)

/**
 * @brief cstack_free - frees all memory associated with the stack
 * @param stack__ - the stack
 * @return void
 */
#define cstack_free(stack__)                                       \
    do {                                                           \
        if (stack__) {                                             \
            void* p1__ = cstack_stack_to_base(stack__);            \
            cstack_elem_destructor_t elem_destructor__ =           \
                cstack_elem_destructor(stack__);                   \
            if (elem_destructor__) {                               \
                size_t i__;                                        \
                for (i__ = 0; i__ < cstack_size(stack__); ++i__) { \
                    elem_destructor__(&(stack__)[i__]);            \
                }                                                  \
            }                                                      \
            cstack_clib_free(p1__);                                \
        }                                                          \
    } while (0)

/* user request to use logarithmic growth algorithm */
#ifdef cstack_LOGARITHMIC_GROWTH

/**
 * @brief cstack_compute_next_grow - returns an the computed size in next stack
 * grow size is increased by multiplication of 2
 * @param size - current size
 * @return size after next stack grow
 */
#define cstack_compute_next_grow(size) ((size) ? ((size) << 1) : 1)

#else

/**
 * @brief cstack_compute_next_grow - returns an the computed size in next stack
 * grow size is increased by 1
 * @param size - current size
 * @return size after next stack grow
 */
#define cstack_compute_next_grow(size) ((size) + 1)

#endif /* cstack_LOGARITHMIC_GROWTH */

/**
 * @brief cstack_push - adds an element to the end of the stack
 * @param stack__ - the stack
 * @param value - the value to add
 * @return void
 */
#define cstack_push(stack__, value)                                     \
    do {                                                                \
        size_t cs_cap__ = cstack_capacity(stack__);                     \
        if (cs_cap__ <= cstack_size(stack__)) {                         \
            cstack_grow((stack__), cstack_compute_next_grow(cs_cap__)); \
        }                                                               \
        (stack__)[cstack_size(stack__)] = (value);                      \
        cstack_set_size((stack__), cstack_size(stack__) + 1);           \
    } while (0)

/**
 * @brief cstack_pop - removes the last element from the stack
 * @param stack__ - the stack
 * @return void
 */
#define cstack_pop(stack__)                                          \
    do {                                                             \
        cstack_elem_destructor_t elem_destructor__ =                 \
            cstack_elem_destructor(stack__);                         \
        if (elem_destructor__) {                                     \
            elem_destructor__(&(stack__)[cstack_size(stack__) - 1]); \
        }                                                            \
        cstack_set_size((stack__), cstack_size(stack__) - 1);        \
    } while (0)

/**
 * @brief cstack_top - returns a reference to the top element in the stack.
 * @return a reference to the top element in the stack.
 */
#define cstack_top(stack__)                                                   \
    ((stack__)                                                                \
         ? ((cstack_size(stack__) > 0) ? &(stack__)[cstack_size(stack__) - 1] \
                                       : NULL)                                \
         : NULL)

#endif /*CSTACK_H_*/
