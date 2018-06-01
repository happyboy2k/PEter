/*! \file exports.h
    \brief These functions can be used to get information from a PE files export header.
*/
#include "hdrs.h"
#include "sections.h"
#include "misc.h"

/*! \fn uint16_t exports_get_ordinal_by_name(void *image, const char *name)
    \brief returns the ordinal for the function you name
    \param image is a pointer to the first byte of the image you want to analyze
    \param name is a pointer on the name of the function you want to get the ordinal of
*/
uint16_t exports_get_ordinal_by_name(void *image, const char *name);

/*! \fn void *exports_get_function_by_name(void *image, const char *name)
    \brief returns a functions address
    \param image is a pointer to the pe image you want to analyze
    \param name is a pointer on the name of the API function you want the address of
*/ 
void *exports_get_function_by_name(void *image, const char *name);

/*! \fn char *exports_get_name_by_index(void *image, const uint32_t idx)
    \brief returns the first function name in the export headerif idx = 0, the second if idx = 1 and so on
    \param image is a pointer on the pe image
    \param idx is 0 for the first name and so on... (like an array index)
*/ 
char *exports_get_name_by_index(void *image, const uint32_t idx);
/*! \fn void *exports_get_function_by_ordinal(void *image, uint32_t ord)
    \brief you give it an ordinal and you get a pointer to a function
    \param image <-- like above
    \param ord should be one of the values you can find in the odinal list
 of the PEs export table.
*/
void *exports_get_function_by_ordinal(void *image, uint32_t ord);

