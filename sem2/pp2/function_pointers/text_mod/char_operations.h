/* Character transformation operations and text modifier interface */

#ifndef CHAR_OPERATIONS_H
#define CHAR_OPERATIONS_H

#include <stddef.h>

/* Single-character transformers */
char lower_to_upper(char ch);
char upper_to_lower(char ch);
char space_to_dash(char ch);
char reverse_letter(char ch);

/* Applies modifier to each character of input_text.
 * Returns newly allocated string on success, or NULL on failure.
 */
char *letter_modifier(const char *input_text, char (*modifier)(char));

#endif /* CHAR_OPERATIONS_H */
