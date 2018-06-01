/*! \file sections.h
    \brief This file contains functions for getting information concerning the
           section headers (e.g. sections_by_name_is_writable() informs you
           wether the writable flag in a section header is set). 
           An other type of function changes the values within the section
           headers (set functions like sections_by_name_set_name() ) or may even
           add a new one. The functions which convert e.g. pointers to rva 
           values where placed in this header too, because they need information
           from the section headers to calculate their return values.
*/
#include "hdrs.h"
#ifndef SECTIONS_HDR
#define SECTIONS_HDR
/*! \fn IMAGE_SECTION_HEADER *sections_by_index_get_sh(void *image, int index)
    \brief returns a pointer on the IMAGE_SECTION_HEADER at the indexed
           poisition.
    \param image is a pointer on the PE file in memory.
    \param index starts with 0 and is 1 if you want the second section header.
*/
IMAGE_SECTION_HEADER *sections_by_index_get_sh(void *image, int index);
/*! \fn IMAGE_SECTION_HEADER *sections_by_name_get_sh(void *image,
                                                      const char *name)
    \brief like sections_by_index_get_sh() but index is replaced by the section
           name.
    \param image is the PE file.
    \param name is a pointer on the section name. It should not exceed 8 bytes
                since the section names of PE files are not alowed to be longer
                than 8 bytes.
*/
IMAGE_SECTION_HEADER *sections_by_name_get_sh(void *image, const char *name);
/*! \fn int sections_by_name_get_index(void *image, const char *name);
    \brief Tells you at which position the section header with the name xy lies.
    \param image is the PE file.
    \param name is the name of the section (max 8 byte)
**/
int sections_by_name_get_index(void *image, const char *name);
/*! \fn uint32_t sections_by_name_get_characteristics(void *image,
                                                      const char *name)
    \brief returns the characteristics field of a section header.
    \param image is like always the PE file.
    \param name is the section name.
**/
uint32_t sections_by_name_get_characteristics(void *image, const char *name);

/*! \fn char *sections_by_index_get_name(void *image, int idx)
    \brief returns the name of the section nr idx
    \param index is the PE file.
    \param idx is the section index (starts with 0)
*/
char *sections_by_index_get_name(void *image, int idx);

/*! \fn int sections_by_name_is_writable(void *image, const char *name)
    \brief returns 1 if the section is writable and 0 if not
    \param image is the PE file.
    \param name is the section name
*/
int sections_by_name_is_writable(void *image, const char *name);
/*! \fn int sections_by_name_is_readable(void *image, const char *name)
    \brief returns 1 if section is readable and 0 if not
    \param image is the PE file.
    \param name is the section name.
*/
int sections_by_name_is_readable(void *image, const char *name);
/*! \fn int sections_by_name_is_executable(void *image, const char *name)
    \brief returns 1 if the section is executable and 0 if not.
    \param image is the PE file.
    \param name is the section name.
*/
int sections_by_name_is_executable(void *image, const char *name);
/*! \fn void *sections_by_name_get_pointer_to_memory(void *image, 
                                                     const char *name)
    \brief returns a pointer on the first byte of a section
    \param image is the PE file.
    \param name is the section name.
*/
void *sections_by_name_get_pointer_to_memory(void *image, const char *name);

/*! \fn uint32_t rva_to_raw(char *image, uint32_t rva)
    \brief you give it a 32bit rva and it returns the raw offset
    \param image is the PE file.
    \param rva 
*/
uint32_t rva_to_raw(char *image, uint32_t rva);
/*! \fn void *rva_to_ptr(void *image, uint32_t rva)
    
    \param image
    \param rva
*/
void *rva_to_ptr(void *image, uint32_t rva);
/*! \fn uint32_t raw_to_rva(char *image, uint32_t raw)
    \brief returns a rva if you give it a raw offset
    \param image
    \param raw
*/
uint32_t raw_to_rva(char *image, uint32_t raw);
/*! \fn uint32_t ptr_to_rva(char *image, char *ptr)
    \brief makes a rva address from a pointer
    \param image
    \param ptr 
*/
uint32_t ptr_to_rva(void *image, void *ptr);

/*! \fn void sections_by_name_set_writable(void *image, const char *name)
    \brief Sets the writable flag in the section header
    \param image is the PE image
    \param name is the section name
*/
void sections_by_name_set_writable(void *image, const char *name);

/*! \fn void sections_by_name_set_readable(void *image, const char *name)
   \brief sets the readable flag in the section header
   \param image
   \param name
*/
void sections_by_name_set_readable(void *image, const char *name);

/*! \fn void sections_by_name_set_executable(void *image, const char *name)
   \brief sets the executable flag in the section header
   \param image
   \param name
*/
void sections_by_name_set_executable(void *image, const char *name);

/*! \fn void sections_by_name_set_name(void *image, const char *name,
                                      const char *replace)
   \brief replaces the section name with a section name of your choise
          (8 byte max)
   \param image is the PE file
   \param name is the section name you want to replace
   \param replace is the new section name
*/
void sections_by_name_set_name(void *image, const char *name,
                               const char *replace);
/*! \fn void sections_by_name_set_characteristics(void *image,
                                                  const char *name,
                                                  uint32_t characteristics)
    \brief sets the characteristics field of a section header.
    \param image is the PE file.
    \param name is the name of the section
    \param characteristics is the value the characteristics filed should be changed to.
*/
void sections_by_name_set_characteristics(void *image, const char *name,
                                          uint32_t characteristics);

/*! \fn void *sections_add_section(void *image, int imageSz, 
                                   void *spaceRetImage, int spaceSz,
                                   const char *name, uint32_t size)
    \brief Creates a new PE image from image. The new image will be written to
           spaceSpaceRetImage is there is enough space. The new image will be
           like the old but with a section added to it. You can calculate the 
           number of bytes you must allocate with: 
           sections_get_sizeof_image_after_add_section(). 
           The return value is a pointer on the first byte of the new section.
    \param image is the old pe image
    \param imageSz is the size of the old image in bytes
    \param spaceRetImage should point on an allocated space in memory
    \param spaceSz must contain the size in bytes of the memory spaceRetImage
           is pointing to.
    \param name is the name of the new section (not longer than 8 bytes)
    \param size is how big you want the new section to be (in bytes)
*/               
void *sections_add_section(void *image, int imageSz, void *spaceRetImage,
                           int spaceSz,  const char *name, uint32_t size);
/*! \fn  uint32_t sections_get_sizeof_image_after_add_section(void *oldImage, 
                                                   uint32_t oldSz,
                                                   uint32_t  addedSz)
   \brief calculates the size, the image will have after adding a section
   \param oldImage is the PE image before adding a section
   \param oldSz is the size of the image, oldImage is pointing to
   \param addedSz is the size of the section you want to add.   
*/
uint32_t sections_get_sizeof_image_after_add_section(void *oldImage, 
                                                   uint32_t oldSz,
                                                   uint32_t  addedSz);

/*! \fn void *sections_by_name_enlarge(void *image, const char *name,
                                      char *bytes, uint32_t bytesLen)
   \brief enlarges a section and returns a pointer on the first byte of the
          new allocated space. If it fails it returns NULL.
   \param image is the PE image
   \param name is the name of the section you want to enlarge
   \param bytes are the bytes you want to add to the section. It can be NULL.
   \param bytesLen is the size in bytes by which you want the section to be
          enlarged.
*/
void *sections_by_name_enlarge(void *image, const char *name,
                               char *bytes, uint32_t bytesLen);


#endif
