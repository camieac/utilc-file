/**
* @file utilc-file-example.c
* @author Cameron A. Craig
* @date 08 Sep 2017
* @version 0.1.0
* @copyright 2017 Cameron A. Craig
* @brief Example usage of utilc-file library.
* -- RULE_3_2_CD_do_not_use_special_characters_in_filename
* -- RULE_8_1_A_provide_file_info_comment
*/
#include <utilc-file.h>

#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]){
  const char *filename = "examplefile.txt";
  struct uc_file_t f;

  // Open the file
	uint32_t ret = uc_file_open(&f, filename, UCF_RD);
  if(ret != UCF_OK){
    fprintf(stderr, "Error: %s\r\n", uc_file_err_to_string(ret));
  }

  // Read Contents of file into string
  ret = uc_file_read_to_str(&f);
  if(ret != UCF_OK){
    fprintf(stderr, "Error: %s\r\n", uc_file_err_to_string(ret));
  }

  // Print contents of file
  printf("Contents of file: \r\n%s\r\n", f.buffer);

  //Free string
  uc_file_free_buffer(&f);

  //Print size of file
  printf("Size of file: %lu bytes\r\n", f.bytes);

  uc_file_close(&f);
	return EXIT_SUCCESS;
}
