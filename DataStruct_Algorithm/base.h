#define  DA_SUCCESS (0)
#define  DA_ERROR   (-1)
#define  DA_ALREADY_EXIST   (-2)

#define  CHECK_PTR_NULL (ptr)   \
if ((ptr) == NULL)              \
{                               \
    return false;               \
}                                