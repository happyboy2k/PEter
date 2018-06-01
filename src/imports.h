/*! \file imports.h
    \brief These functions give you information about the import table.
*/
#ifndef IMPORTS_H
#define IMPORTS_H

#include "hdrs.h"
#include "sections.h"
#include "misc.h"

/*! \fn IMAGE_IMPORT_DESCRIPTOR *imports_by_index_get_import_descriptor(
                                                            void *image, int i)
    \brief return the import descriptor with the index i
    \param image points to the image you want to analyze
    \param i is 0 if you need the first import descriptor 
             i = 1 for the second and so on
*/
IMAGE_IMPORT_DESCRIPTOR *imports_by_index_get_import_descriptor(void *image, int i);
/*! \fn char *imports_by_index_get_name(void *image, int i)
    \brief returns a char *pointer on the import descriptors name (the dll name)
    \param image points tor the image you want to analyzee
    \param i is an index indicating which import disc.
            you want the name of (starting with 0)
*/
char *imports_by_index_get_name(void *image, int i);
/*! \fn int imports_by_name_get_index(void *image, const char *name)
    \brief returns the import descroptor index that fits the name parameter
    \param image points on the image you want to analyze
    \param name the dll name (== import descriptor name) you want the idx of
*/
int imports_by_name_get_index(void *image, const char *name);
/*! \fn imports_by_name_get_iname_index_by_name(void *image, 
                                                const char *dllName,
                                                const char *funcName)
    \brief returns the index of the imported fucntion of a dll
           (that's not an ordinal)
    \param image points to the PE file you want information of
    \param dllName is the name of the dll (import descriptor name) 
           where the function name resides in
    \param funcName is the name of the function you want the index of
*/
int imports_by_name_get_iname_index_by_name(void *image, const char *dllName,
                                            const char *funcName);
/*! \fn IMAGE_IMPORT_BY_NAME *imports_by_index_get_iname_by_index(void *image,
                                                                  int idtIdx,
                                                                  int intIdx)
    \brief you give it two indexes (import descriptor and its import name table)
           and you get the name of the function these two indexes discribe.
           That means you will get the first function name of the first
           imported dll if idtIdx and intIdx are both == 0. The returned
           pointer is an IMAGE_IMPORT_BY_NAME struct which is actually
           a uint8_t array but with a word (16bit) value at its start.
    \param image points to the PE file
    \param idtIdx is the import descriptor index
           (starting at 0 for the first import descriptor)
    \param intIdx is the name table index (also starting with 0)
 */
IMAGE_IMPORT_BY_NAME *imports_by_index_get_iname_by_index(void *image,
                                                          int idtIdx,
                                                          int intIdx);
/*! \fn void *imports_by_index_get_iaddr_thunk_by_index(void *image,
                                                         int idtIdx,
                                                        int iatIdx)
    \brief like imports_by_index_get_iname_by_index() but doesn't return a 
           name but a pointer on IMAGE_THUNK_DATA if it's a 32bit executable
           this function will return IMAGE_THUNK_DATA32 and if you have 64bit
           you may use the return value as a pointer on IMAGE_THUNK_DATA64
    \param image is the PE file
    \param idtIdx is an import descriptor index
    \param iatIdx is the address table index
*/
void *imports_by_index_get_iaddr_thunk_by_index(void *image, int idtIdx, int iatIdx);

/*! \fn void imports_by_index_set_iaddr_thunk_by_index(void *image, int idtIdx, 
                                               int iatIdx, void *address);
    \brief Writes an address into the specified field of the import address
           table.
    \param image is the PE file.
    \param idtIdx is the import descriptor index.
    \param iatIdx is the address table index.
    \param address is the address you want to write.
*/


void imports_by_index_set_iaddr_thunk_by_index(void *image, int idtIdx, 
                                               int iatIdx, void *address);

/******* /*! \fn void *imports_by_index_get_iat(void *image, int i)
    \brief returns a
    
void *imports_by_index_get_iat(void *image, int i); */

#endif
