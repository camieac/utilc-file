/**
* @file test-utilc-file.c
* @author Cameron A. Craig
* @date 08 Sep 2017
* @version 0.1.0
* @copyright 2017 Cameron A. Craig
* @brief Unit tests for utilc-file.
* -- RULE_3_2_CD_do_not_use_special_characters_in_filename
* -- RULE_8_1_A_provide_file_info_comment

* @note Check unit test documentation can be cound here:
* https://libcheck.github.io/check/doc/check_html/index.html#Top
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <check.h>

#include "utilc-file.h"

static uc_file_h f;
/************************
* Test Case Setup and teardown
************************/

/**
* @brief Setup
* @details Checked fixture: Runs for each unit test.
*/
void uc_template_test_setup(void){

}

/**
* @brief Teardown
* @details Checked fixture: Runs for each unit test.
*/
void uc_template_test_teardown(void){

}

/************************
* Unit Tests
************************/

START_TEST (test_template){
	int ret = uc_file_open(f, "testfile1.txt", UCF_RD);
	fail_if(ret != UCF_OK);

  ret = uc_file_close(f);
  fail_if(ret != UCF_OK);
}
END_TEST



/**
* @brief Defines test suite for utilc-file lib.
*/
Suite* utilc_test_suite (void) {
				Suite *suite = suite_create("utilc_file_test_suite");

				TCase *tempate_tcase = tcase_create("File Test Case");
				tcase_add_checked_fixture(tempate_tcase, uc_template_test_setup, uc_template_test_teardown);
				tcase_add_test(tempate_tcase, test_template);
				suite_add_tcase(suite, tempate_tcase);

				return suite;
}

/**
* @brief Run the full test suite.
* @returns Number of tests failed.
*/
uint32_t main (uint32_t argc, char *argv[]) {
				uint32_t number_failed;
				Suite *suite = utilc_test_suite();
				SRunner *runner = srunner_create(suite);
				srunner_run_all(runner, CK_NORMAL);
				number_failed = srunner_ntests_failed(runner);
				srunner_free(runner);
				return number_failed;
}
