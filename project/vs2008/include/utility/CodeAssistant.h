#ifndef __CODE_ASSISTANT_H__
#define __CODE_ASSISTANT_H__

#define CHECK_PTR_RETURN_FALSE(ptr)  \
    if (NULL == (ptr))               \
    {                                \
        return false;                \
    }                                \

#endif