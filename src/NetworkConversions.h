/*
 * (c) 2022 Copyright, Real-Time Innovations, Inc. (RTI) All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the Software solely in combination with RTI Connext DDS. Licensee
 * may redistribute copies of the Software provided that all such copies are
 * subject to this License. The Software is provided "as is", with no warranty
 * of any type, including any warranty for fitness for any purpose. RTI is
 * under no obligation to maintain or support the Software. RTI shall not be
 * liable for any incidental or consequential damages arising out of the use or
 * inability to use the Software. For purposes of clarity, nothing in this
 * License prevents Licensee from using alternate versions of DDS, provided
 * that Licensee may not combine or link such alternate versions of DDS with
 * the Software.
 */

#ifndef N_CONVERSIONS
    #ifdef RTI_WIN32
        #include <winsock2.h>
    #endif
    #ifndef htonll
        #define htonll(x)                                                 \
            ((((DDS_UnsignedLongLong) htonl((DDS_UnsignedLong) x)) << 32) \
             + htonl((DDS_UnsignedLong)(x >> 32)))
        #define ntohll(x)                                                 \
            ((((DDS_UnsignedLongLong) ntohl((DDS_UnsignedLong) x)) << 32) \
             + ntohl((DDS_UnsignedLong)(x >> 32)))
/*     #define ntohll(x)   (((DDS_UnsignedLongLong)(htonl((DDS_UnsignedLong)((x
    << 32) >> 32))) << 32) + htonl((DDS_UnsignedLong)(x >> 32))) #define
    htonll(x)   ntohll(x)
 */
    #endif

    #ifndef dim
        #define dim(x) (sizeof(x) / sizeof(x[0]))
    #endif

union SwapFloat {
    DDS_Float f;
    DDS_UnsignedLong ul;
};

union SwapDouble {
    DDS_Double d;
    DDS_UnsignedLongLong ull;
};
    #ifdef RTI_UNIX

DDS_Float ntohf(DDS_UnsignedLong value)
{
    union SwapFloat val;
    val.ul = value;
    val.ul = ntohl(val.ul);
    return val.f;
};

DDS_UnsignedLong htonf(DDS_Float value)
{
    union SwapFloat val;
    /* unsigned char *charPtr = (unsigned char *)&val.ul; */
    val.f = value;
    /* printf("Not Swapped = %02x %02x %02x %02x\n",
              *(charPtr), *(charPtr+1), *(charPtr+2), *(charPtr+3)); */
    val.ul = htonl(val.ul);
    /* printf("Swapped = %02x %02x %02x %02x\n",
              *(charPtr), *(charPtr+1), *(charPtr+2), *(charPtr+3)); */
    return val.ul;
};

DDS_Double ntohd(DDS_UnsignedLongLong value)
{
    union SwapDouble val;
    val.ull = value;
    val.ull = ntohll(val.ull);
    return val.d;
};

DDS_UnsignedLongLong htond(DDS_Double value)
{
    union SwapDouble val;
/*     unsigned char *charPtr = (unsigned char *)&val.ull; */
    val.d = value;
    /* 	printf("Double = %f\n", val.d);
    	printf("Not Swapped = %02x %02x %02x %02x %02x %02x %02x %02x\n",
              *(charPtr), *(charPtr+1), *(charPtr+2), *(charPtr+3),
              *(charPtr+4), *(charPtr+5), *(charPtr+6), *(charPtr+7)); */
    val.ull = htonll(val.ull);
/*     	printf("Swapped = %02x %02x %02x %02x %02x %02x %02x %02x\n",
              *(charPtr), *(charPtr+1), *(charPtr+2), *(charPtr+3),
              *(charPtr+4), *(charPtr+5), *(charPtr+6), *(charPtr+7));
 */
    return val.ull;
};
    #endif
#endif /* N_CONVERSIONS */