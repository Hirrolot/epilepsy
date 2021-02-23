#ifndef METALANG99_EVAL_FOLD_H
#define METALANG99_EVAL_FOLD_H

#include <metalang99/eval/acc.h>
#include <metalang99/priv/util.h>

#define METALANG99_PRIV_EVAL_FAPPEND(acc, ...)                                                     \
    (0non_empty, METALANG99_PRIV_EVAL_ACC_UNWRAP acc __VA_ARGS__)

#define METALANG99_PRIV_EVAL_FCOMMA(acc, ...)                                                      \
    (0non_empty, METALANG99_PRIV_EVAL_FCOMMA_AUX acc __VA_ARGS__)

#define METALANG99_PRIV_EVAL_FCOMMA_AUX(is_empty, ...)                                             \
    __VA_ARGS__ METALANG99_PRIV_EVAL_FCOMMA_AUX_##is_empty()
#define METALANG99_PRIV_EVAL_FCOMMA_AUX_0empty()     METALANG99_PRIV_EMPTY()
#define METALANG99_PRIV_EVAL_FCOMMA_AUX_0non_empty() ,

#endif // METALANG99_EVAL_FOLD_H
