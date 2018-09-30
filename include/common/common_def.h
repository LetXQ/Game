#ifndef COMMON_DEF_H
#define COMMON_DEF_H
#include <string.h>
#include <cstdint>

#define SAVE_DELETE(x) { \
            if (x) { \
                delete x; \
                x = nullptr; \
            } \
        }

#define SAVE_DELETES(x) { \
            if (x) { \
                delete [] x; \
                x = nullptr; \
            } \
        }


#endif // COMMON_DEF_H
