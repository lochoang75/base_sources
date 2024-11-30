#ifndef ABSTRACT_ERRORS_H
#define ABSTRACT_ERRORS_H

typedef enum {
    kSUCCESS = 0,
    kNO_MEM = -1,
    kINVALID_MEM = -2,
    kTRY_AGAIN = -3,
    kERROR = -4
} base_error_t;
#endif /*ABSTRACT_ERRORS_H*/
