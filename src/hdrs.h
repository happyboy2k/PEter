//License: GPLv3.0
#ifndef HDRS
#define HDRS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "pe.h"
//#include "/usr/x86_64-w64-mingw32/include/windef.h"
//#include "/usr/x86_64-w64-mingw32/include/winnt.h"

typedef struct _hdrs
{
    char type; //32 or 64Bit?
    IMAGE_DOS_HEADER *dos;
    void *nt;
    IMAGE_FILE_HEADER *file;
    void *opt;
}hdrs;


//returns -1 on failure and 0 on success
int hdrs_init(hdrs *self, void *image);

//set and get for file header
uint16_t hdrs_get_machine_type(hdrs *self);
uint16_t hdrs_get_number_of_sections(hdrs *self);
void hdrs_set_number_of_sections(hdrs *self, uint16_t setVal);
uint32_t hdrs_get_time_date_stamp(hdrs *self);
void hdrs_set_time_date_stamp(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_pointer_to_symbol_table(hdrs *self);
void hdrs_set_pointer_to_symbol_table(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_number_of_symbols(hdrs *self);
void hdrs_set_number_of_symbold(hdrs *self, uint32_t setVal);
uint16_t hdrs_get_characteristics(hdrs *self);
void hdrs_set_characteristics(hdrs *self, uint16_t setVal);

//set and get for optional header
uint32_t hdrs_get_size_of_code(hdrs *self);
void hdrs_set_size_of_code(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_size_of_initialized_data(hdrs *self);
void hdrs_set_size_of_initialized_data(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_size_of_uninitialized_data(hdrs *self);
void hdrs_set_size_of_uninitialized_data(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_address_of_entry_point(hdrs *self);
void hdrs_set_address_of_entry_point(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_base_of_code(hdrs *self);
void hdrs_set_base_of_code(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_base_of_data(hdrs *self);
void hdrs_set_base_of_data(hdrs *self, uint32_t setVal);
uint64_t hdrs_get_image_base(hdrs *self);
void hdrs_set_image_base(hdrs *self, uint64_t setVal);
uint32_t hdrs_get_section_alignment(hdrs *self);
void hdrs_set_section_alignment(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_file_alignment(hdrs *self);
void hdrs_set_file_alignment(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_size_of_image(hdrs *self);
void hdrs_set_size_of_image(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_checksum(hdrs *self);
void hdrs_set_checksum(hdrs *self, uint32_t setVal);
uint32_t hdrs_get_number_of_rva_and_sizes(hdrs *self);
void hdrs_set_number_of_rva_and_sizes(hdrs *self, uint32_t setVal);

//data directorys
uint32_t hdrs_get_first_import_descriptor_rva(hdrs *self);
void hdrs_set_data_directory_import(hdrs *self, 
                                    IMAGE_DATA_DIRECTORY *setVal);
void hdrs_set_data_directory_iat(hdrs *self,
                                 IMAGE_DATA_DIRECTORY *setVal);
uint32_t hdrs_get_load_cfg_rva(hdrs *self);
uint32_t hdrs_get_load_cfg_size(hdrs *self);
void hdrs_set_data_directory_load_cfg(hdrs *self,
                                      IMAGE_DATA_DIRECTORY *setVal);

uint32_t hdrs_get_export_directory(hdrs *self);

/////////////////////////////////////////////////
//section headers
IMAGE_SECTION_HEADER *hdrs_get_first_section_header(hdrs *self);


void hdrs_destroy(hdrs *self);
#endif
