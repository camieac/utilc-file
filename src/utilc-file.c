/**
* @file utilc-timing.c
* @author Cameron A. Craig
* @date 08 Sep 2017
* @version 0.1.0
* @copyright 2016 Cameron A. Craig
* @brief Measure time without thinking about the arithmetic.
* -- RULE_3_2_CD_do_not_use_special_characters_in_filename
* -- RULE_8_1_A_provide_file_info_comment
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "utilc-file.h"

static const char * ucf_err_string[] = {
	"Error",
	"Ok",
	"UCL_DEST_STDERR",
	"UCL_DEST_UDP"
};

char * uc_file_err_to_string(enum uc_file_error_code_e err) {
	if(err < 0 || (err > UCF_MAX_ERR_NUM)){
		return "Error";
	}
	return ucf_err_string[err];
}

uint32_t uc_file_open(uc_file_h f, const char *filename, uint32_t mode) {
  /* Covert mode into fopen compatible string */
  char md[2];
  // If RD + WRT
  if((mode & (UCF_RD | UCF_WRT)) == (UCF_RD | UCF_WRT)) {
    strncpy(md, "w+", 2);
    //md = "w+"; // Open for rd/wrt, create file if it doesn't exist (cursor at start)
  // If WRT !RD
  } else if ((mode & (UCF_RD | UCF_WRT)) == UCF_WRT) {
    strncpy(md, "w", 1);
    //md = "w"; // Open for write only, create file or truncate (cursor at start)
  // If RD !WRT
  } else if ((mode & (UCF_RD | UCF_WRT)) == UCF_RD) {
    strncpy(md, "r", 1);
    //md = "r";
  // No mode flags!
  } else {
    return UCF_INVALID_FLAGS;
  }

  /* TODO: If we are reading, make sure file exists */

  /* Open file */
  if ((f->f = fopen (filename, md)) == NULL) {
    fprintf(stderr, "ucf error: (%d) %s\r\n", errno, strerror(errno));
    return UCF_FILE_NOT_FOUND;
  }

  /* Done */
#ifdef DEBUG
  //Classic file open method
  FILE *file;
  file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file\r\n");
  }
  fclose(file);
#endif

#ifdef DEBUG
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    fprintf(stdout, "Current working dir: %s\n", cwd);
  } else {
    perror("getcwd() error");
    return 0;
  }
#endif

#ifdef DEBUG
  if (access(filename , F_OK ) == -1 ) {
    fprintf(stderr, "File does not exist\r\n");
  }
#endif

#ifdef DEBUG
  printf("Enter %s()\r\n", __func__);
  printf("Attempting to open %s\r\n", filename);
#endif

FILE *f2;


#ifdef DEBUG
  printf("File open\r\n");
#endif

  /* Get the size of the file by setting the cursor to the end of the file
     and reading its value. */

  //Set cursor to end of file
  fseek (f->f, 0, SEEK_END);

  //Get the value of the cursor
  f->bytes = ftell (f->f);

  //Set cursor to start of file
  fseek (f->f, 0, SEEK_SET);



	return UCF_OK;
}

uint32_t uc_file_read_to_str(uc_file_h f) {
  f->buffer = malloc (f->bytes);
  if (f->buffer == NULL) {
    return UCF_NULL_POINTER;
  }

  if(fread(f->buffer, 1, f->bytes, f->f) != f->bytes){
    return UCF_ERR;
  }
  return UCF_OK;
}

uint32_t uc_file_free_buffer(uc_file_h f){
	free(f->buffer);
}

uint32_t uc_file_close(uc_file_h f){
	fclose(f->f);
}
