#include "misc.h"

long align(long size, long align)
{
    int alignBuffer = align;
    
    while (alignBuffer < size)
        alignBuffer += align;
    return alignBuffer;
}

/////////////////////////////////////////////////
/* this function tests for if index points behind 
 * the terminating 0x00 element */
int test_for_list_end(void *list, int index, int null_size_in_bytes)
{
    int trigger = 0;
    for (int i = 0; i < index; i++)
    {
        for (int j = 0; j < null_size_in_bytes; j++)
            if (((char *)list)[(i*null_size_in_bytes)+j] != 0) trigger = 1;
        if (trigger == 0) return -1;
        trigger = 0;
    }
    return 0;
}
