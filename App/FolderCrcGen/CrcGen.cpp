#include "CrcGen.hpp"

unsigned Checksum::crc_16(void *b, size_t s)
{
    // BISYNCH, ARC, LHA, ZOO
    boost::crc_basic<16> crc( 0x8005u, 0u, 0u, true, true );
    crc.process_bytes( b, s );
    return crc.checksum();
}

unsigned Checksum::crc_ccitt(void *b, size_t s)
{
    // Designated by CCITT (Comit Consultatif International Telegraphique et Telephonique), KERMIT
    boost::crc_optimal<16, 0x1021, 0, 0, true, true> crc;
    crc.process_bytes( b, s );
    return crc.checksum();
}

unsigned Checksum::crc_xmodem(void *b, size_t s)
{
    // XMODEM, ZMODEM, ACORN
    boost::crc_optimal<16, 0x1021, 0, 0, false, false> crc;
    crc.process_bytes( b, s );
    return crc.checksum();
}

unsigned Checksum::crc_32(void *b, size_t s)
{
    // ADCCP, PKZip, libPNG, AUTODIN II, Ethernet, FDDI
    boost::crc_optimal<32, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true> crc;
    crc.process_bytes( b, s );
    return crc.checksum();
}
