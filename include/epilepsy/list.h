/**
 * @file
 * Lists.
 */

#ifndef EPILEPSY_LIST_H
#define EPILEPSY_LIST_H

#include <epilepsy/choice.h>
#include <epilepsy/control.h>
#include <epilepsy/logical.h>
#include <epilepsy/uint.h>
#include <epilepsy/variadics.h>

// Desugaring {
/**
 * Prepends @p head to @p tail.
 */
#define EPILEPSY_Cons(head, tail) call(EPILEPSY_Cons_IMPL, head tail)

/**
 * The empty list.
 */
#define EPILEPSY_Nil() call(EPILEPSY_Nil_IMPL, )

/**
 * Constructs a list from its arguments.
 */
#define EPILEPSY_List(...) call(EPILEPSY_List_IMPL, __VA_ARGS__)

/**
 * Performs a right fold.
 */
#define EPILEPSY_ListFoldr(list, op, init) call(EPILEPSY_ListFoldr_IMPL, list op init)

/**
 * Gets an @p i -indexed element.
 */
#define EPILEPSY_ListGet(list, i) call(EPILEPSY_ListGet_IMPL, list i)
// }

#ifndef DOXYGEN_IGNORE

// Implementation {
#define EPILEPSY_Cons_IMPL(head, tail) EPILEPSY_CHOICE(v(Cons), v(head, tail))
#define EPILEPSY_Nil_IMPL()            EPILEPSY_CHOICE(v(Nil), v(~))

#define EPILEPSY_List_IMPL(...)                                                                    \
    call(EPILEPSY_PRIV_List_AUX, EPILEPSY_VARIADICS_COUNT(v(__VA_ARGS__)) v(__VA_ARGS__, ~))
#define EPILEPSY_PRIV_List_AUX(count, ...)                                                         \
    EPILEPSY_IF_LAZY(                                                                              \
        EPILEPSY_UIntEq(v(count), v(1)), v(EPILEPSY_PRIV_List_DONE),                               \
        v(EPILEPSY_PRIV_List_PROGRESS), v(count, __VA_ARGS__))
#define EPILEPSY_PRIV_List_DONE(_count, last, _) EPILEPSY_Cons(v(last), EPILEPSY_Nil())
#define EPILEPSY_PRIV_List_PROGRESS(count, head, ...)                                              \
    EPILEPSY_Cons(v(head), call(EPILEPSY_PRIV_List_AUX, EPILEPSY_UIntDec(v(count)) v(__VA_ARGS__)))

#define EPILEPSY_ListFoldr_IMPL(list, op, init)                                                    \
    EPILEPSY_MATCH_WITH_ARGS(v(list), v(EPILEPSY_PRIV_ListFoldr_), v(op, init))
#define EPILEPSY_PRIV_ListFoldr_Cons(head, tail, op, acc)                                          \
    call(op, v(head) EPILEPSY_ListFoldr(v(tail), v(op), v(acc)))
#define EPILEPSY_PRIV_ListFoldr_Nil(_, _op, acc) v(acc)

#define EPILEPSY_ListGet_IMPL(list, i)                                                             \
    EPILEPSY_MATCH_WITH_ARGS(v(list), v(EPILEPSY_PRIV_ListGet_), v(i))
#define EPILEPSY_PRIV_ListGet_Nil(_, i) EPILEPSY_ERROR()
#define EPILEPSY_PRIV_ListGet_Cons(head, tail, i)                                                  \
    EPILEPSY_IF_LAZY(                                                                              \
        EPILEPSY_UIntEq(v(i), v(0)), v(EPILEPSY_PRIV_ListGet_Cons_DONE),                           \
        v(EPILEPSY_PRIV_ListGet_Cons_PROGRESS), v(head, tail, i))
#define EPILEPSY_PRIV_ListGet_Cons_DONE(head, _tail, _i) v(head)
#define EPILEPSY_PRIV_ListGet_Cons_PROGRESS(_head, tail, i)                                        \
    EPILEPSY_ListGet(v(tail), EPILEPSY_UIntDec(v(i)))
// }

#endif // DOXYGEN_IGNORE

#endif // EPILEPSY_LIST_H
