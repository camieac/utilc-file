/**
* @file utilc-file.h
* @author Cameron A. Craig
* @date 08 Sep 2017
* @version 0.1.0
* @copyright 2017 Cameron A. Craig
* @brief Defines uc_timing_h handle and function prototypes.
* -- RULE_3_2_CD_do_not_use_special_characters_in_filename
* -- RULE_8_1_A_provide_file_info_comment
*/
#ifndef UTILC_FILE_H
#define UTILC_FILE_H

#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>

typedef struct uc_file_t* uc_file_h;
struct uc_file_t {
	FILE *f;
	char *buffer; //Stores contents of file.
	long bytes; //Number of bytes in file.
  char * filename;
};

enum uc_file_error_code_e {
	UCF_ERR = 0,
	UCF_OK,
	UCF_FILE_NOT_FOUND,
	UCF_NULL_POINTER,
  UCF_INVALID_FLAGS,
	UCF_MAX_ERR_NUM
};

#define UCF_RD (1 << 0)
#define UCF_WRT (1 << 1)

char *   uc_file_err_to_string(enum uc_file_error_code_e err);
uint32_t uc_file_open(uc_file_h f, const char *filename, uint32_t mode);
uint32_t uc_file_read_to_str(uc_file_h f);
uint32_t uc_file_prepend_str(uc_file_h f, const char *str);
uint32_t uc_file_append_str(uc_file_h f, const char *str);
uint32_t uc_file_merge();
uint32_t uc_file_free_buffer(uc_file_h f);
uint32_t uc_file_close(uc_file_h f);


#endif
