#ifndef INCL_USI_max_min_H
#define INCL_USI_max_min_H


#define __USI_MIN(a,b)    (((a)<(b))?(a):(b))
#define __USI_MAX(a,b)    (((a)>(b))?(a):(b))

#define __BIT_MASK(bit)   ((1 << (bit)) - 1)
#define __CELLING(n, unit) ((((n) - 1) / (unit)) + 1)

inline unsigned char revertBits(unsigned char from)
{
    from = (from & 0X55) << 1 | (from & 0xaa) >> 1;
    from = (from & 0X33) << 2 | (from & 0xcc) >> 2;
    from = (from & 0X0f) << 4 | (from & 0xf0) >> 4;

    return from;
}
#endif

