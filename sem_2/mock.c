#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "unity/unity.h"
#include "unity/unity.c"
#include <stdlib.h>
#include <time.h>
#include "src/utilities.h"

#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"


#ifdef _WIN32
#include <windows.h>
void enable_virtual_terminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (hOut == INVALID_HANDLE_VALUE) return;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

void setUp(void) {}
void tearDown(void) {}

void FillIncr_test(void) {
    int A[5];
    FillInc(5, A);
    int expected[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, A, 5);
}

void CheckSum_standard(void) {
    int A[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(15, CheckSum(5, A));
}

void CheckSum_empty(void){
    int A[1];
    TEST_ASSERT_EQUAL_INT(0, CheckSum(0, A));
}

void RunNumber_ascend(void) {
    int A[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(1, RunNumber(5, A));
}

void RunNumber_desc(void) {
    int A[] = {5, 4, 3, 2, 1};
    TEST_ASSERT_EQUAL_INT(5, RunNumber(5, A));
}

void RunNumber_mixed(void) {
    int A[] = {1, 3, 2, 4, 3, 5}; // 1→3, 3→2↓, 2→4, 4→3↓, 3→5 => 3 серии
    TEST_ASSERT_EQUAL_INT(3, RunNumber(6, A));
}

void RunNumber_empty(void) {
    int A[1];
    TEST_ASSERT_EQUAL_INT(0, RunNumber(0, A));
}

int main(void) {
	#ifdef _WIN32
    enable_virtual_terminal();
	#endif
    UNITY_BEGIN();
    RUN_TEST(FillIncr_test);
    RUN_TEST(CheckSum_standard);
    RUN_TEST(CheckSum_empty);
    RUN_TEST(RunNumber_ascend);
    RUN_TEST(RunNumber_desc);
    RUN_TEST(RunNumber_mixed);
    RUN_TEST(RunNumber_empty);
    return UNITY_END();
}
