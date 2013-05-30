#ifndef _SQUID_FORMAT_TOKEN_H
#define _SQUID_FORMAT_TOKEN_H

//#include "format/TokenTableEntry.h"
#include "format/ByteCode.h"

/*
 * Squid configuration allows users to define custom formats in
 * several components.
 * - logging
 * - external ACL input
 * - deny page URL
 *
 * These enumerations and classes define the API for parsing of
 * format directives to define these patterns. Along with output
 * functionality to produce formatted buffers.
 */

namespace Format
{

class TokenTableEntry;

#define LOG_BUF_SZ (MAX_URL<<2)

// XXX: inherit from linked list
class Token
{
public:
    Token() : type(LFT_NONE),
            label(NULL),
            widthMin(-1),
            widthMax(-1),
            quote(LOG_QUOTE_NONE),
            left(false),
            space(false),
            zero(false),
            divisor(0),
            next(NULL)
    { data.string = NULL; }

    ~Token();

    /// Initialize the format token registrations
    static void Init();

    /** parses a single token. Returns the token length in characters,
     * and fills in this item with the token information.
     * def is for sure null-terminated.
     */
    int parse(const char *def, enum Quoting *quote);

    ByteCode_t type;
    const char *label;
    union {
        char *string;

        struct {
            char *header;
            char *element;
            char separator;
        } header;
        char *timespec;
    } data;
    int widthMin; ///< minimum field width
    int widthMax; ///< maximum field width
    enum Quoting quote;
    bool left;
    bool space;
    bool zero;
    int divisor;
    Token *next;	/* todo: move from linked list to array */

private:
    const char *scanForToken(TokenTableEntry const table[], const char *cur);
};

} // namespace Format

#endif /* _SQUID_FORMAT_TOKEN_H */