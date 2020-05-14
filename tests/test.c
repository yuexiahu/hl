#include "hl_string.h"
#include "simpletest.h"

void test_string();
void test_vector();

SIMPLETEST_CONF(SIMPLETEST_ENABLE_UNIT_OUTPUT | SIMPLETEST_ENABLE_CASE_OUTPUT);
SIMPLETEST_LIST(main, test_string, test_vector);
