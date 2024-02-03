#include "../../libraries/global_lib.h"

typedef struct {
    char* text;
} CopiedText;

typedef struct {
    int numCopiedText;
    CopiedText* copiedTextArray;
} CopiedTextArray;