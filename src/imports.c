//License: GPLv3.0
#include "imports.h"

IMAGE_IMPORT_DESCRIPTOR *imports_by_index_get_import_descriptor(void *image, int idtIdx)
{
    IMAGE_IMPORT_DESCRIPTOR *imp;
    hdrs h;
    
    hdrs_init(&h, image);
    imp = (IMAGE_IMPORT_DESCRIPTOR*)rva_to_ptr(image, 
                            hdrs_get_first_import_descriptor_rva(&h));
    imp = &imp[idtIdx];
    if (-1 == test_for_list_end(imp, idtIdx, sizeof(IMAGE_IMPORT_DESCRIPTOR)))
        return NULL;
    return imp;
}

/////////////////////////////////////////////////

char *imports_by_index_get_name(void *image, int idtIdx)
{
    IMAGE_IMPORT_DESCRIPTOR *imp;
    imp = (IMAGE_IMPORT_DESCRIPTOR*)
            imports_by_index_get_import_descriptor(image, idtIdx);
    if (NULL == imp) return NULL;
    return (char *)rva_to_ptr(image, imp->Name);
}

/////////////////////////////////////////////////

int imports_by_name_get_index(void *image, const char *name)
{
    int i = 0;
    char *currentName;
    do
    {
        currentName = imports_by_index_get_name(image, i);
        if (NULL == currentName)
            return -1;
        if (0 == strcmp(currentName, name))
            return i;
        i++;
    }while(1);
}

/////////////////////////////////////////////////

int imports_by_name_get_iname_index_by_name(void *image, const char *dllName,
                                            const char *funcName)
{
    int idtIdx;
    int intIdx;
    IMAGE_IMPORT_BY_NAME *currentIname;

    idtIdx = imports_by_name_get_index(image, dllName);
    if (-1 == idtIdx) return -1;
    intIdx = 0;
    while (1)
    {
        currentIname = imports_by_index_get_iname_by_index(image, idtIdx,
                                                           intIdx);
        if (NULL == currentIname) return -1;
        if (0 == strcmp(currentIname->Name, funcName)) return intIdx;
        intIdx++;
    }
}    
            
/////////////////////////////////////////////////

IMAGE_IMPORT_BY_NAME *imports_by_index_get_iname_by_index(void *image,
                                                          int idtIdx,
                                                          int intIdx)
{
    /*TODO: handling of IMAGE_ORDINAL_FLAG */
    IMAGE_IMPORT_DESCRIPTOR *imp;
    IMAGE_THUNK_DATA32 *thd32;
    IMAGE_THUNK_DATA64 *thd64;
    hdrs h;
    hdrs_init(&h, image);
    int i = 0;
    uint32_t firstThunkRva;
    
    imp = imports_by_index_get_import_descriptor(image, idtIdx);
    if (NULL == imp) return NULL;
    firstThunkRva = imp->u1.OriginalFirstThunk;
    /* someone told me some linkers place the OriginalFirstThunk
     * wrongly into FirstThunk. This is how i tried to handle that. */
    if (0 == firstThunkRva) firstThunkRva = imp->FirstThunk;
    if (64 == h.type)
    {
        thd64 = (IMAGE_THUNK_DATA64*)rva_to_ptr(image, firstThunkRva);
        for (i = 0; i <= intIdx; i++)
        {
            if (0 == (&thd64[i])->u1.AddressOfData)
                break;
        }
        i--;
        if (i == intIdx) 
            return (IMAGE_IMPORT_BY_NAME*)rva_to_ptr(image,
                                            (&thd64[intIdx])->u1.AddressOfData);
        else return NULL;
    }
    else if (32 == h.type)
    {
        thd32 = (IMAGE_THUNK_DATA32*)rva_to_ptr(image, firstThunkRva);
        for (i = 0; i <= intIdx; i++)
        {
            if (0 == (&thd32[i])->u1.AddressOfData)
                break;
        }
        i--;
        if (i == intIdx)
            return (IMAGE_IMPORT_BY_NAME*)rva_to_ptr(image,
                                           (&thd32[intIdx])->u1.AddressOfData);
        else return NULL;
    }
    return NULL;
}
          

/////////////////////////////////////////////////

void *imports_by_index_get_iaddr_thunk_by_index(void *image, int idtIdx, int iatIdx)
{
    IMAGE_IMPORT_DESCRIPTOR *imp;
    IMAGE_THUNK_DATA64 *thd64;
    IMAGE_THUNK_DATA32 *thd32;
    hdrs h;
    int i;
    hdrs_init(&h, image);

    imp = imports_by_index_get_import_descriptor(image, idtIdx);
    
    if (64 == h.type)
    {
        thd64 = (IMAGE_THUNK_DATA64*)rva_to_ptr(image, imp->FirstThunk);
        i = 0;
        while (i <= iatIdx)
        {
            if (i == iatIdx) return &thd64[i];
            i++;
        }
        return NULL;
     }
    else if (32 == h.type)
    {
        thd32 = (IMAGE_THUNK_DATA32*)rva_to_ptr(image, imp->FirstThunk);
        i = 0;
        while (i <= iatIdx)
        {
            if (i == iatIdx) return &thd32[i];
            i ++;
        }
        return NULL;
    }
    return NULL;
}

/////////////////////////////////////////////////

void imports_by_index_set_iaddr_thunk_by_index(void *image, int idtIdx, 
                                               int iatIdx, void *address)
{
    IMAGE_THUNK_DATA32 *thd32;
    IMAGE_THUNK_DATA64 *thd64;
    hdrs h;

    hdrs_init(&h, image);
    if (64 == h.type)
    {
        thd64 = imports_by_index_get_iaddr_thunk_by_index(image, idtIdx,
                                                          iatIdx);
        thd64->u1.Function = (uint64_t)address;
    }
    if (32 == h.type)
    {
        thd32 = imports_by_index_get_iaddr_thunk_by_index(image, idtIdx,
                                                          iatIdx);
        thd32->u1.Function = (uint32_t)address;
    }
    hdrs_destroy(&h);
    return;
}
    
