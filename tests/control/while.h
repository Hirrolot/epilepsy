#include "../test.h"

#include "../../include/agony_pp/aux.h"
#include "../../include/agony_pp/control.h"
#include "../../include/agony_pp/eval.h"
#include "../../include/agony_pp/lang.h"
#include "../../include/agony_pp/uint.h"

#define LIMIT 10
#define SUM   ((LIMIT + 1) * (LIMIT / 2))

#define PREDICATE(state)       c(PREDICATE_AUX, c(AGONY_PP_UNPARENTHESISE, v(state)))
#define PREDICATE_AUX(_acc, i) c(AGONY_PP_UINT_NEQ, v(i) c(AGONY_PP_UINT_INC, v(LIMIT)))

#define OP(state)      c(OP_AUX, c(AGONY_PP_UNPARENTHESISE, v(state)))
#define OP_AUX(acc, i) v((v(acc + i) c(AGONY_PP_UINT_INC, v(i))))

#define STATE_FINALISER(state)      c(STATE_FINALISER_AUX, c(AGONY_PP_UNPARENTHESISE, v(state)))
#define STATE_FINALISER_AUX(acc, i) v(acc)

TEST(AGONY_PP_EVAL(c(STATE_FINALISER, c(AGONY_PP_WHILE, v(PREDICATE) v(OP) v((v(0, 1)))))) == SUM);

#undef PREDICATE
#undef PREDICATE_AUX
#undef OP
#undef OP_AUX
#undef STATE_FINALISER
#undef STATE_FINALISER_AUX
#undef LIMIT
#undef SUM
