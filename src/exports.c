#include "exports.h"


uint16_t exports_get_ordinal_by_name(void *image, const char *name)
{
    hdrs h;
    IMAGE_EXPORT_DIRECTORY *exDir;
    uint32_t *ent; //name table
    uint16_t *eot; //ordinal table

    hdrs_init(&h, image);
    exDir = (IMAGE_EXPORT_DIRECTORY *)
                rva_to_ptr(image, hdrs_get_export_directory(&h));

    ent = (uint32_t *)rva_to_ptr(image, exDir->AddressOfNames);
    eot = (uint16_t *)rva_to_ptr(image, exDir->AddressOfNameOrdinals);

    for (int i = 0; i < exDir->NumberOfNames; i++)
    {
        if (0 == strcmp(rva_to_ptr(image, ent[i]), name))
            return eot[i];
    }
    return -1;
}

/////////////////////////////////////////////////

void *exports_get_function_by_ordinal(void *image, uint32_t ord)
{
    IMAGE_EXPORT_DIRECTORY *exDir;
    hdrs h;
    uint32_t *eft; //export function table

    hdrs_init(&h, image);
    exDir = (IMAGE_EXPORT_DIRECTORY *)
                rva_to_ptr(image, hdrs_get_export_directory(&h));
    eft = (uint32_t *)rva_to_ptr(image, exDir->AddressOfFunctions);
    return rva_to_ptr(image, eft[ord]);
}
/////////////////////////////////////////////////

void *exports_get_function_by_name(void *image, const char *name)
{
    IMAGE_EXPORT_DIRECTORY *exDir;
    hdrs h;
    uint32_t *eft; //export function table

    hdrs_init(&h, image);
    exDir = (IMAGE_EXPORT_DIRECTORY *)
                rva_to_ptr(image, hdrs_get_export_directory(&h));
    eft = (uint32_t *)rva_to_ptr(image, exDir->AddressOfFunctions);
    return rva_to_ptr(image, eft[exports_get_ordinal_by_name(image, name)]);
}

/////////////////////////////////////////////////

char *exports_get_name_by_index(void *image, const uint32_t idx)
{
    IMAGE_EXPORT_DIRECTORY *exDir;
    hdrs h;
    uint32_t *ent;


    hdrs_init(&h, image);
    exDir = (IMAGE_EXPORT_DIRECTORY *)
                rva_to_ptr(image, hdrs_get_export_directory(&h));
    ent = (uint32_t *)rva_to_ptr(image, exDir->AddressOfNames);
    if (idx >= exDir->NumberOfNames) return NULL;
    return (char *)rva_to_ptr(image, ent[idx]);
}

/////////////////////////////////////////////////
