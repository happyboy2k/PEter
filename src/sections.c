#include "sections.h"
#include "misc.h"

IMAGE_SECTION_HEADER *sections_by_index_get_sh(void *image, int index)
{
    hdrs h;
    IMAGE_SECTION_HEADER *sh;

    if (-1 == hdrs_init(&h, image))
        return NULL;
    if (index >= hdrs_get_number_of_sections(&h))
        return NULL;
    sh = hdrs_get_first_section_header(&h);
    if (-1 == test_for_list_end(sh, index, sizeof (IMAGE_SECTION_HEADER)))
        return NULL;
    hdrs_destroy(&h);
    return &sh[index];
}

/////////////////////////////////////////////////

IMAGE_SECTION_HEADER* sections_by_name_get_sh(void *image, const char *name)
{
    hdrs h;
    IMAGE_SECTION_HEADER *currSh;
    
    if (-1 == hdrs_init(&h, image))
        goto sections_by_name_get_sh_error;
    for (int i = 0; i < hdrs_get_number_of_sections(&h); i++)
    {
        currSh = sections_by_index_get_sh(image, i);
        if (0 == strncmp(name, currSh->Name, IMAGE_SIZEOF_SHORT_NAME))
        {
            hdrs_destroy(&h);
            return currSh;
        }
    }
    sections_by_name_get_sh_error:
    hdrs_destroy(&h);
    return NULL;
}

/////////////////////////////////////////////////

int sections_by_name_get_index(void *image, const char *name)
{
    hdrs h;
    IMAGE_SECTION_HEADER *currSh;

    if (-1 == hdrs_init(&h, image))
        goto sections_by_name_get_index_error;
    for (int i = 0; i < hdrs_get_number_of_sections(&h); i++)
    {
        currSh = sections_by_index_get_sh(image, i);
        if (0 == strncmp(name, currSh->Name, IMAGE_SIZEOF_SHORT_NAME))
        {
            hdrs_destroy(&h);
            return i;
        }
    }
    sections_by_name_get_index_error:
    hdrs_destroy(&h);
    return -1;
}

/////////////////////////////////////////////////

char *sections_by_index_get_name(void *image, int idx)
{
    IMAGE_SECTION_HEADER *sh;
    
    sh = sections_by_index_get_sh(image, idx);
    if (NULL == sh) return NULL;
    return sh->Name;
}

/////////////////////////////////////////////////

void *sections_by_name_get_pointer_to_memory(void *image, const char *name)
{
    IMAGE_SECTION_HEADER *sh = sections_by_name_get_sh(image, name);
    return &((char*)image)[sh->PointerToRawData];
}

/////////////////////////////////////////////////

void sections_by_name_set_name(void *image, const char *name, const char *replace)
{
    IMAGE_SECTION_HEADER *sh;
    
    sh = sections_by_name_get_sh(image, name);
    memset(sh->Name, 0, IMAGE_SIZEOF_SHORT_NAME);
    strncpy(sh->Name, replace, IMAGE_SIZEOF_SHORT_NAME);
    return;
}

/////////////////////////////////////////////////

void sections_by_name_set_characteristics(void *image, const char *name, uint32_t characteristics)
{
    IMAGE_SECTION_HEADER *sh;
    
    sh = sections_by_name_get_sh(image, name);
    sh->Characteristics = characteristics;
    return;
}

/////////////////////////////////////////////////

uint32_t sections_by_name_get_characteristics(void *image, const char *name)
{
    IMAGE_SECTION_HEADER *sh;
    
    sh = sections_by_name_get_sh(image, name);
    return sh->Characteristics;
}

/////////////////////////////////////////////////

int sections_by_name_is_writable(void *image, const char *name)
{
    uint32_t flags = sections_by_name_get_characteristics(image, name);

    if (IMAGE_SCN_MEM_WRITE & flags)
        return 1;
    return 0;
}
//////////////////////////////////////////////////

int sections_by_name_is_readable(void *image, const char *name)
{
    uint32_t flags = sections_by_name_get_characteristics(image, name);

    if (IMAGE_SCN_MEM_READ & flags)
        return 1;
    return 0;
}

////////////////////////////////////////////////

int sections_by_name_is_executable(void *image, const char *name)
{
    uint32_t flags = sections_by_name_get_characteristics(image, name);

    if (IMAGE_SCN_MEM_EXECUTE & flags)
        return 1;
    return 0;
}

/////////////////////////////////////////////////

void sections_by_name_set_writable(void *image, const char *name)
{
    IMAGE_SECTION_HEADER *sh;
    
    sh = sections_by_name_get_sh(image, name);
    sh->Characteristics = (sh->Characteristics | IMAGE_SCN_MEM_WRITE);
}
//////////////////////////////////////////////////

void sections_by_name_set_readable(void *image, const char *name)
{
    IMAGE_SECTION_HEADER *sh;
    
    sh = sections_by_name_get_sh(image, name);
    sh->Characteristics = (sh->Characteristics | IMAGE_SCN_MEM_READ);
}

////////////////////////////////////////////////

void sections_by_name_set_executable(void *image, const char *name)
{
    IMAGE_SECTION_HEADER *sh;
    
    sh = sections_by_name_get_sh(image, name);
    sh->Characteristics = (sh->Characteristics | IMAGE_SCN_MEM_EXECUTE);
}



/////////////////////////////////////////////////

void *sections_add_section(void *image, int imageSz, void *spaceRetImage,
                           int spaceSz,  const char *name, uint32_t size)
{
    void *newImage;
    int newImageSz;
    IMAGE_SECTION_HEADER *newSection, *lastSection;
    hdrs h;
    
    if (-1 == hdrs_init(&h, image))
        return NULL;
    newImageSz = imageSz + align(size, hdrs_get_file_alignment(&h));
    if (newImageSz > spaceSz) return NULL;
    newImage = spaceRetImage;
    hdrs_destroy(&h);
    memcpy(newImage, image, imageSz);
    if (-1 == hdrs_init(&h, newImage))
        goto sections_add_section_error;
    /*hdrs_get_number_of_sections returns the index of the last section+1
      because indexes start counting with 0*/
    newSection = sections_by_index_get_sh(newImage,
                                          (hdrs_get_number_of_sections(&h)-1));
    newSection++;
    strncpy(newSection->Name, name, IMAGE_SIZEOF_SHORT_NAME);
    newSection->Misc.VirtualSize = size;
    lastSection =  sections_by_index_get_sh(newImage,
                                            hdrs_get_number_of_sections(&h)-1);
    newSection->VirtualAddress = lastSection->VirtualAddress
                               + lastSection->Misc.VirtualSize;
    newSection->VirtualAddress = align(newSection->VirtualAddress,
                                       hdrs_get_section_alignment(&h));
    newSection->SizeOfRawData = align(size, hdrs_get_file_alignment(&h));
    newSection->PointerToRawData = lastSection->PointerToRawData
                                 + lastSection->SizeOfRawData;
    newSection->Characteristics = 0;
    hdrs_set_number_of_sections(&h, hdrs_get_number_of_sections(&h)+1);
    hdrs_set_size_of_image(&h, hdrs_get_size_of_image(&h)
                             + align(newSection->Misc.VirtualSize,
                                     hdrs_get_section_alignment(&h)));
    /*relocate the symbol table*/
    int stripSz;
    char *stripBuf;
    if (hdrs_get_pointer_to_symbol_table(&h))
    {
        stripSz = imageSz - hdrs_get_pointer_to_symbol_table(&h);
        stripBuf = malloc(stripSz);
        memcpy(stripBuf, &((char*)newImage)[hdrs_get_pointer_to_symbol_table(&h)], stripSz);
        hdrs_set_pointer_to_symbol_table(&h, newSection->PointerToRawData
                                           + newSection->SizeOfRawData);
        memcpy(&((char*)newImage)[hdrs_get_pointer_to_symbol_table(&h)], stripBuf,
               stripSz);
        free(stripBuf);
    }
    return &newImage[newSection->PointerToRawData];
    sections_add_section_error:
    free(newImage);
     return NULL;
}

/////////////////////////////////////////////////

uint32_t sections_get_sizeof_image_after_add_section(void *oldImage, 
                                                     uint32_t oldSz,
                                                     uint32_t  addedSz)
{
    hdrs h;
    uint32_t newImageSz;
    
    hdrs_init(&h, oldImage);
    newImageSz = oldSz + align(addedSz, hdrs_get_file_alignment(&h));
    hdrs_destroy(&h);
    return newImageSz;
}

///////////////////////////////////////////////// 

void *sections_by_name_enlarge(void *image, const char *name,
                               char *bytes, uint32_t bytesLen)
{
    IMAGE_SECTION_HEADER *enlargeSec;
    char *writePtr;

    enlargeSec = sections_by_name_get_sh(image, name);

    if (NULL == enlargeSec) return NULL;

    if ((enlargeSec->SizeOfRawData - enlargeSec->Misc.VirtualSize) < bytesLen)
        return NULL;
    writePtr = rva_to_ptr(image, (enlargeSec->VirtualAddress));
    writePtr += enlargeSec->Misc.VirtualSize;
    enlargeSec->Misc.VirtualSize += bytesLen;
    if (NULL != bytes)
        memcpy(writePtr, bytes, bytesLen);
    return (void *)writePtr;
}    

/////////////////////////////////////////////////

uint32_t rva_to_raw(char *image, uint32_t rva)
{
    hdrs h;
    hdrs_init(&h, image);
    IMAGE_SECTION_HEADER *sh;

    for(int i = 0; i < hdrs_get_number_of_sections(&h); i++)
    {
        sh = sections_by_index_get_sh(image, i);
        if (sh->VirtualAddress <= rva
        &&  rva < (sh->VirtualAddress + sh->Misc.VirtualSize))
            return (rva - sh->VirtualAddress + sh->PointerToRawData);
    }
    return -1;
}

/////////////////////////////////////////////////

void *rva_to_ptr(void *image, uint32_t rva)
{
    return &((char *)image)[rva_to_raw(image, rva)];
}

/////////////////////////////////////////////////

uint32_t raw_to_rva(char *image, uint32_t raw)
{
    hdrs h;
    IMAGE_SECTION_HEADER *sh;
    hdrs_init(&h, image);
    
    for (int i = 0; i < hdrs_get_number_of_sections(&h); i++)
    {
        sh = sections_by_index_get_sh(image, i);
        if (sh->PointerToRawData <= raw
        &&  raw < (sh->PointerToRawData + sh->SizeOfRawData))
            return (raw - sh->PointerToRawData + sh->VirtualAddress);
    }
    return -1;
}

/////////////////////////////////////////////////

uint32_t ptr_to_rva(void *image, void *ptr)
{
    uint32_t raw;
    raw = (uint32_t)(ptr - image);
    return raw_to_rva(image, raw);
}
