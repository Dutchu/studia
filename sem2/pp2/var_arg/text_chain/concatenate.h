#ifndef TEXT_CHAIN_CONCATENATE_H
#define TEXT_CHAIN_CONCATENATE_H

#include <stddef.h>

/* Match tested signature: int size, int num */
int concatenate(char *buf, int size, int texts_count, ...);

#endif /* TEXT_CHAIN_CONCATENATE_H */
