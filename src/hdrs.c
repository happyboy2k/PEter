//License: GPLv3.0
#include "hdrs.h"

int hdrs_init(hdrs *self, void *image)
{
    self->dos = (IMAGE_DOS_HEADER *)image;
    if (IMAGE_DOS_SIGNATURE != self->dos->e_magic)
        return -1;
    self->nt = (IMAGE_NT_HEADERS32*)&((char*)image)[self->dos->e_lfanew];
    if (IMAGE_NT_SIGNATURE != ((IMAGE_NT_HEADERS32*)self->nt)->Signature)
        return -1;
    self->file = &((IMAGE_NT_HEADERS32*)self->nt)->FileHeader;
    self->opt = &((IMAGE_NT_HEADERS32*)self->nt)->OptionalHeader;
    if (*(uint16_t *)self->opt == 0x20b)
        self->type = 64;
    else 
        self->type = 32;
    return 0;
}

/////////////////////////////////////////////////
//set and get functions for the file header    //
/////////////////////////////////////////////////

/////////////////////////////////////////////////

uint16_t hdrs_get_machine_type(hdrs *self)
{
    return self->file->Machine;
}

/////////////////////////////////////////////////

uint16_t hdrs_get_number_of_sections(hdrs *self)
{
    return self->file->NumberOfSections;
}

/////////////////////////////////////////////////

void hdrs_set_number_of_sections(hdrs *self, uint16_t setVal)
{
    self->file->NumberOfSections = setVal;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_time_date_stamp(hdrs *self)
{
    return self->file->TimeDateStamp;
}

/////////////////////////////////////////////////

void hdrs_set_time_date_stamp(hdrs *self, uint32_t setVal)
{
    self->file->TimeDateStamp = setVal;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_pointer_to_symbol_table(hdrs *self)
{
    return self->file->PointerToSymbolTable;
}

/////////////////////////////////////////////////

void hdrs_set_pointer_to_symbol_table(hdrs *self, uint32_t setVal)
{
    self->file->PointerToSymbolTable = setVal;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_number_of_symbols(hdrs *self)
{
    return self->file->NumberOfSymbols;
}

/////////////////////////////////////////////////

void hdrs_set_number_of_symbold(hdrs *self, uint32_t setVal)
{
    self->file->NumberOfSymbols = setVal;
}

/////////////////////////////////////////////////

uint16_t hdrs_get_size_of_optional_header(hdrs *self)
{
    return self->file->SizeOfOptionalHeader;
}

/////////////////////////////////////////////////

void hdrs_set_size_of_optional_header(hdrs *self, uint16_t setVal)
{
    self->file->SizeOfOptionalHeader = setVal;
}

/////////////////////////////////////////////////

uint16_t hdrs_get_characteristics(hdrs *self)
{
    return self->file->Characteristics;
}

/////////////////////////////////////////////////

void hdrs_set_characteristics(hdrs *self, uint16_t setVal)
{
    self->file->Characteristics = setVal;
}


/////////////////////////////////////////////////
// set and get functions for the optional hdr  //
/////////////////////////////////////////////////

uint32_t hdrs_get_size_of_code(hdrs *self)
{
    return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->SizeOfCode;
}

/////////////////////////////////////////////////

void hdrs_set_size_of_code(hdrs *self, uint32_t setVal)
{
    ((IMAGE_OPTIONAL_HEADER32*)self->opt)->SizeOfCode = setVal;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_size_of_initialized_data(hdrs *self)
{
    return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->SizeOfInitializedData;
}

/////////////////////////////////////////////////

void hdrs_set_size_of_initialized_data(hdrs *self, uint32_t setVal)
{
    ((IMAGE_OPTIONAL_HEADER32*)self->opt)->SizeOfInitializedData = setVal;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_size_of_uninitialized_data(hdrs *self)
{
    return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->SizeOfUninitializedData;
}

/////////////////////////////////////////////////

void hdrs_set_size_of_uninitialized_data(hdrs *self, uint32_t setVal)
{
    ((IMAGE_OPTIONAL_HEADER32*)self->opt)->SizeOfUninitializedData = setVal;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_address_of_entry_point(hdrs *self)
{
    return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->AddressOfEntryPoint;
}

/////////////////////////////////////////////////

void hdrs_set_address_of_entry_point(hdrs *self, uint32_t setVal)
{
    ((IMAGE_OPTIONAL_HEADER32*)self->opt)->AddressOfEntryPoint = setVal;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_base_of_code(hdrs *self)
{
    return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->BaseOfCode;
}

/////////////////////////////////////////////////

void hdrs_set_base_of_code(hdrs *self, uint32_t setVal)
{
    ((IMAGE_OPTIONAL_HEADER32*)self->opt)->BaseOfCode = setVal;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_base_of_data(hdrs *self)
{
    return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->BaseOfData;
}

/////////////////////////////////////////////////

void hdrs_set_base_of_data(hdrs *self, uint32_t setVal)
{
    ((IMAGE_OPTIONAL_HEADER32*)self->opt)->BaseOfData = setVal;
}

/////////////////////////////////////////////////

uint64_t hdrs_get_image_base(hdrs *self)
{
    if (64 == self->type)
        return ((IMAGE_OPTIONAL_HEADER64*)self->opt)->ImageBase;
    else if (32 == self->type)
        return (uint64_t)((IMAGE_OPTIONAL_HEADER32*)self->opt)->ImageBase;
    return 0;
}

/////////////////////////////////////////////////

void hdrs_set_image_base(hdrs *self, uint64_t setVal)
{
    if (64 == self->type)
        ((IMAGE_OPTIONAL_HEADER64*)self->opt)->ImageBase = setVal;
    else if (32 == self->type)
        ((IMAGE_OPTIONAL_HEADER32*)self->opt)->ImageBase = (uint32_t)setVal;
    return;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_section_alignment(hdrs *self)
{
    if (64 == self->type)
        return ((IMAGE_OPTIONAL_HEADER64*)self->opt)->SectionAlignment;
    else if (32 == self->type)
        return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->SectionAlignment;
    return 0;
}

/////////////////////////////////////////////////

void hdrs_set_section_alignment(hdrs *self, uint32_t setVal)
{
    if (64 == self->type)
        ((IMAGE_OPTIONAL_HEADER64*)self->opt)->SectionAlignment = setVal;
    else if (32 == self->type)
        ((IMAGE_OPTIONAL_HEADER32*)self->opt)->SectionAlignment = setVal;
    return;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_file_alignment(hdrs *self)
{
    if (64 == self->type)
        return ((IMAGE_OPTIONAL_HEADER64*)self->opt)->FileAlignment;
    else if (32 == self->type)
        return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->FileAlignment;
    return 0;
}

/////////////////////////////////////////////////

void hdrs_set_file_alignment(hdrs *self, uint32_t setVal)
{
    if (64 == self->type)
        ((IMAGE_OPTIONAL_HEADER64*)self->opt)->FileAlignment = setVal;
    else if (32 == self->type)
        ((IMAGE_OPTIONAL_HEADER32*)self->opt)->FileAlignment = setVal;
    return;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_size_of_image(hdrs *self)
{
    if (64 == self->type)
        return ((IMAGE_OPTIONAL_HEADER64*)self->opt)->SizeOfImage;
    else if (32 == self->type)
        return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->SizeOfImage;
    return 0;
}

/////////////////////////////////////////////////

void hdrs_set_size_of_image(hdrs *self, uint32_t setVal)
{
    if (64 == self->type)
        ((IMAGE_OPTIONAL_HEADER64*)self->opt)->SizeOfImage = setVal;
    else if (32 == self->type)
        ((IMAGE_OPTIONAL_HEADER32*)self->opt)->SizeOfImage = setVal;
    return;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_checksum(hdrs *self)
{
    if (64 == self->type)
        return ((IMAGE_OPTIONAL_HEADER64*)self->opt)->CheckSum;
    else if (32 == self->type)
        return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->CheckSum;
    return 0;
}

/////////////////////////////////////////////////

void hdrs_set_checksum(hdrs *self, uint32_t setVal)
{
    if (64 == self->type)
        ((IMAGE_OPTIONAL_HEADER64*)self->opt)->CheckSum = setVal;
    else if (32 == self->type)
        ((IMAGE_OPTIONAL_HEADER32*)self->opt)->CheckSum = setVal;
    return;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_number_of_rva_and_sizes(hdrs *self)
{
    if (64 == self->type)
        return ((IMAGE_OPTIONAL_HEADER64*)self->opt)->NumberOfRvaAndSizes;
    else if (32 == self->type)
        return ((IMAGE_OPTIONAL_HEADER32*)self->opt)->NumberOfRvaAndSizes;
    return 0;
}

/////////////////////////////////////////////////

void hdrs_set_number_of_rva_and_sizes(hdrs *self, uint32_t setVal)
{
    if (64 == self->type)
        ((IMAGE_OPTIONAL_HEADER64*)self->opt)->NumberOfRvaAndSizes = setVal;
    else if (32 == self->type)
        ((IMAGE_OPTIONAL_HEADER32*)self->opt)->NumberOfRvaAndSizes = setVal;
    return;
}

/////////////////////////////////////////////////

//other functions
IMAGE_SECTION_HEADER *hdrs_get_first_section_header(hdrs *self)
{
    void *ptr = (void *)self->dos;
    
    ptr += self->dos->e_lfanew;
    if (64 == self->type)
        ptr += sizeof(IMAGE_NT_HEADERS64);
    else if (32 == self->type)
        ptr += sizeof(IMAGE_NT_HEADERS32);
    return (IMAGE_SECTION_HEADER*)ptr;
}

////////////////////////////////////////////////

uint32_t hdrs_get_first_import_descriptor_rva(hdrs *self)
{
    if (64 == self->type)
        return ((IMAGE_OPTIONAL_HEADER64 *)self->opt)->
               DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
    return ((IMAGE_OPTIONAL_HEADER32 *)self->opt)->
           DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
}

/////////////////////////////////////////////////

void hdrs_set_data_directory_import(hdrs *self, 
                                    IMAGE_DATA_DIRECTORY *setVal)
{
    if (64 == self->type)
        memcpy(&((IMAGE_OPTIONAL_HEADER64 *)self->opt)
                                 ->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT], 
               setVal, sizeof (IMAGE_DATA_DIRECTORY));
    else 
        memcpy(&((IMAGE_OPTIONAL_HEADER32 *)self->opt)
                                ->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT],
               setVal, sizeof (IMAGE_DATA_DIRECTORY));
    return;
} 

/////////////////////////////////////////////////

void hdrs_set_data_directory_iat(hdrs *self,
                                 IMAGE_DATA_DIRECTORY *setVal)
{
    if (64 == self->type)
        memcpy(&((IMAGE_OPTIONAL_HEADER64 *)self->opt)
                                ->DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT],
                setVal, sizeof (IMAGE_DATA_DIRECTORY));
    else 
        memcpy(&((IMAGE_OPTIONAL_HEADER32 *)self->opt)
                                ->DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT],
                setVal, sizeof (IMAGE_DATA_DIRECTORY));
    return;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_load_cfg_rva(hdrs *self)
{
    if (64 == self->type)
        return ((IMAGE_OPTIONAL_HEADER64 *)self->opt)
                ->DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG]
                .VirtualAddress;
    else
        return ((IMAGE_OPTIONAL_HEADER32 *)self->opt)
                ->DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG]
                .VirtualAddress;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_load_cfg_size(hdrs *self)
{
    if (64 == self->type)
        return ((IMAGE_OPTIONAL_HEADER64 *)self->opt)
                ->DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG]
                .Size;
    else
        return ((IMAGE_OPTIONAL_HEADER32 *)self->opt)
                ->DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG]
                .Size;
}

/////////////////////////////////////////////////

void hdrs_set_data_directory_load_cfg(hdrs *self,
                                      IMAGE_DATA_DIRECTORY *setVal)
{
    if (64 == self->type)
        memcpy(&((IMAGE_OPTIONAL_HEADER64 *)self->opt)
                    ->DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG],
                setVal, sizeof (IMAGE_DATA_DIRECTORY));
    else
        memcpy(&((IMAGE_OPTIONAL_HEADER32 *)self->opt)
                    ->DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG],
                setVal, sizeof (IMAGE_DATA_DIRECTORY));
    return;
}

/////////////////////////////////////////////////

uint32_t hdrs_get_export_directory(hdrs *self)
{
    if (64 == self->type)
        return ((IMAGE_OPTIONAL_HEADER64 *)self->opt)->
                DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    return ((IMAGE_OPTIONAL_HEADER32 *)self->opt)->
            DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
}

//hdrs_destroy is empty till now
void hdrs_destroy(hdrs *self)
{
    return;
}

