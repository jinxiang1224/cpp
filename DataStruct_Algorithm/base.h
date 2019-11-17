#define  DA_SUCCESS (0)
#define  DA_ERROR   (-1)
#define  DA_ALREADY_EXIST   (-2)

#define  CHECK_PTR_RETURN_FALSE(ptr)   \
if ((ptr) == NULL)              \
{                               \
    return false;               \
} \

#define  CHECK_PTR_RETURN_ERROR(ptr)   \
if ((ptr) == NULL)              \
{                               \
    return DA_ERROR;               \
} 

typedef unsigned int UINT32;
#include <memory>
