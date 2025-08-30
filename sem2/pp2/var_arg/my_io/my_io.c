#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <limits.h>
#include "my_io.h"

static int io_putc(char c) {
    if (putchar((unsigned char)c) == EOF) return 0;
    return 1;
}

static int print_cstr(const char *s) {
    int count = 0;
    if (!s) {
        const char *nulls = "(null)";
        const char *p = nulls;
        while (*p) {
            count += io_putc(*p);
            p++;
        }
        return count;
    }
    const char *p = s;
    while (*p) {
        count += io_putc(*p);
        p++;
    }
    return count;
}

static int print_unsigned_ull(unsigned long long v) {
    int count = 0;
    if (v >= 10ULL) {
        count += print_unsigned_ull(v / 10ULL);
    }
    count += io_putc((char)('0' + (v % 10ULL)));
    return count;
}

static int print_int(int val) {
    int count = 0;
    long long v = (long long)val;
    if (v < 0) {
        count += io_putc('-');
        v = -v;
    }
    count += print_unsigned_ull((unsigned long long)v);
    return count;
}

static int print_fixed_double(double x, int precision) {
    int count = 0;
    if (x < 0.0) {
        count += io_putc('-');
        x = -x;
    }

    /* integer part */
    unsigned long long ipart = (unsigned long long)x;
    double frac = x - (double)ipart;

    /* scale fractional and round */
    unsigned long long scale = 1ULL;
    int i = 0;
    while (i < precision) { scale *= 10ULL; i++; }

    /* add 0.5 ulp at target precision for rounding */
    double fscaled_d = frac * (double)scale + 0.5;
    unsigned long long fscaled = (unsigned long long)fscaled_d;

    if (fscaled >= scale) {
        ipart += 1ULL;
        fscaled -= scale;
    }

    count += print_unsigned_ull(ipart);
    count += io_putc('.');

    /* print fractional with leading zeros to fixed width */
    unsigned long long div = scale / 10ULL;
    while (div > 0ULL) {
        unsigned long long digit = fscaled / div;
        count += io_putc((char)('0' + digit));
        fscaled %= div;
        div /= 10ULL;
    }
    return count;
}

int my_printf(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    int count = 0;

    const char *p = format;
    while (p && *p) {
        char c = *p;
        p++;
        if (c != '%') {
            count += io_putc(c);
            continue;
        }

        /* handle format specifier */
        char spec = *p;
        if (spec == '\0') {
            break;
        }
        p++;
        if (spec == '%') {
            count += io_putc('%');
        } else if (spec == 's') {
            const char *s = va_arg(ap, const char *);
            count += print_cstr(s);
        } else if (spec == 'd') {
            int v = va_arg(ap, int);
            count += print_int(v);
        } else if (spec == 'f') {
            double d = va_arg(ap, double);
            count += print_fixed_double(d, 5);
        } else if (spec == 'p') {
            struct point_t pt = va_arg(ap, struct point_t);
            count += io_putc('(');
            count += print_int(pt.x);
            count += io_putc(' ');
            count += print_int(pt.y);
            count += io_putc(')');
        } else {
            /* unknown specifier, print as-is */
            count += io_putc('%');
            count += io_putc(spec);
        }
    }

    va_end(ap);
    return count;
}

/* input helpers */
static int io_getc(void) {
    return getchar();
}

static void io_ungetc(int c) {
    if (c != EOF) ungetc(c, stdin);
}

static void skip_ws(void) {
    int c = io_getc();
    while (c != EOF && isspace(c)) {
        c = io_getc();
    }
    io_ungetc(c);
}

static int scan_int_internal(int *out) {
    skip_ws();
    int c = io_getc();
    int sign = 1;
    int sign_ch = 0;
    if (c == '+' || c == '-') {
        if (c == '-') sign = -1;
        sign_ch = c;
    } else {
        io_ungetc(c);
    }

    long long val = 0;
    int any = 0;
    c = io_getc();
    while (c != EOF && c >= '0' && c <= '9') {
        any = 1;
        val = val * 10LL + (long long)(c - '0');
        c = io_getc();
    }
    io_ungetc(c);

    if (!any) {
        /* push back sign if we consumed it */
        if (sign_ch) io_ungetc(sign_ch);
        return 0;
    }
    long long sval = sign < 0 ? -val : val;
    *out = (int)sval;
    return 1;
}

static int scan_double_internal(double *out) {
    skip_ws();
    int c = io_getc();
    int sign = 1;
    int sign_ch = 0;
    if (c == '+' || c == '-') {
        if (c == '-') sign = -1;
        sign_ch = c;
    } else {
        io_ungetc(c);
    }

    int any = 0;
    double ip = 0.0;
    c = io_getc();
    while (c != EOF && c >= '0' && c <= '9') {
        any = 1;
        ip = ip * 10.0 + (double)(c - '0');
        c = io_getc();
    }

    double frac = 0.0;
    double scale = 1.0;
    if (c == '.') {
        int c2 = io_getc();
        while (c2 != EOF && c2 >= '0' && c2 <= '9') {
            any = 1;
            frac = frac * 10.0 + (double)(c2 - '0');
            scale *= 10.0;
            c2 = io_getc();
        }
        io_ungetc(c2);
    } else {
        io_ungetc(c);
    }

    if (!any) {
        /* push back sign if consumed */
        if (sign_ch) io_ungetc(sign_ch);
        return 0;
    }

    double val = ip + (scale > 1.0 ? (frac / scale) : 0.0);
    if (sign < 0) val = -val;
    *out = val;
    return 1;
}

static int scan_point_internal(struct point_t *out) {
    /* Save state by buffering assignments until success */
    skip_ws();
    int c = io_getc();
    if (c != '(') {
        io_ungetc(c);
        return 0;
    }

    int x = 0; int y = 0;

    if (!scan_int_internal(&x)) {
        return 0;
    }
    skip_ws();
    if (!scan_int_internal(&y)) {
        return 0;
    }
    skip_ws();
    c = io_getc();
    if (c != ')') {
        io_ungetc(c);
        return 0;
    }

    out->x = x;
    out->y = y;
    return 2; /* counts as two items */
}

int my_scanf(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    int assigned = 0;

    const char *f = format;
    while (f && *f) {
        char ch = *f;
        f++;
        if (isspace((unsigned char)ch)) {
            skip_ws();
            continue;
        }
        if (ch != '%') {
            /* literal match */
            int c = io_getc();
            if (c != (unsigned char)ch) {
                io_ungetc(c);
                break;
            }
            continue;
        }

        char spec = *f;
        if (spec == '\0') break;
        f++;

        if (spec == 'd') {
            int *ptr = va_arg(ap, int *);
            int ok = scan_int_internal(ptr);
            if (!ok) break;
            assigned += 1;
        } else if (spec == 'f') {
            double *ptr = va_arg(ap, double *);
            int ok = scan_double_internal(ptr);
            if (!ok) break;
            assigned += 1;
        } else if (spec == 'p') {
            struct point_t *ptr = va_arg(ap, struct point_t *);
            int got = scan_point_internal(ptr);
            if (got == 0) break;
            assigned += got; /* +2 */
        } else {
            /* unsupported specifier - treat as literal */
            int c = io_getc();
            if (c != (unsigned char)spec) {
                io_ungetc(c);
                break;
            }
        }
    }

    va_end(ap);
    return assigned;
}
