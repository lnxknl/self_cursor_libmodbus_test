/* tests/unit-test.h.  Generated from unit-test.h.in by configure.  */
/*
 * Copyright © Stéphane Raimbault <stephane.raimbault@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _UNIT_TEST_H_
#define _UNIT_TEST_H_

/* Constants defined by configure.ac */
#define HAVE_INTTYPES_H 1
#define HAVE_STDINT_H 1

// clang-format off
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#ifdef HAVE_STDINT_H
# ifndef _MSC_VER
# include <stdint.h>
# else
# include "stdint.h"
# endif
#endif
// clang-format on

#define SERVER_ID         17
#define INVALID_SERVER_ID 18

const uint16_t UT_BITS_ADDRESS = 0x130;
const uint16_t UT_BITS_NB = 0x25;
const uint8_t UT_BITS_TAB[] = { 0xCD, 0x6B, 0xB2, 0x0E, 0x1B };
const uint16_t UT_BITS_ADDRESS_INVALID_REQUEST_LENGTH = UT_BITS_ADDRESS + 2;

const uint16_t UT_INPUT_BITS_ADDRESS = 0x1C4;
const uint16_t UT_INPUT_BITS_NB = 0x16;
const uint8_t UT_INPUT_BITS_TAB[] = { 0xAC, 0xDB, 0x35 };

const uint16_t UT_REGISTERS_ADDRESS = 0x160;
const uint16_t UT_REGISTERS_NB = 0x3;
const uint16_t UT_REGISTERS_NB_MAX = 0x20;
const uint16_t UT_REGISTERS_TAB[] = { 0x022B, 0x0001, 0x0064 };

/* Raise a manual exception when this address is used for the first byte */
const uint16_t UT_REGISTERS_ADDRESS_SPECIAL = 0x170;
/* The response of the server will contains an invalid TID or slave */
const uint16_t UT_REGISTERS_ADDRESS_INVALID_TID_OR_SLAVE = 0x171;
/* The server will wait for 1 second before replying to test timeout */
const uint16_t UT_REGISTERS_ADDRESS_SLEEP_500_MS = 0x172;
/* The server will wait for 5 ms before sending each byte */
const uint16_t UT_REGISTERS_ADDRESS_BYTE_SLEEP_5_MS = 0x173;

/* If the following value is used, a bad response is sent.
   It's better to test with a lower value than
   UT_REGISTERS_NB_POINTS to try to raise a segfault. */
const uint16_t UT_REGISTERS_NB_SPECIAL = 0x2;

const uint16_t UT_INPUT_REGISTERS_ADDRESS = 0x108;
const uint16_t UT_INPUT_REGISTERS_NB = 0x1;
const uint16_t UT_INPUT_REGISTERS_TAB[] = { 0x000A };

/*
 * This float value is 0x47F12000 (in big-endian format).
 * In Little-endian(intel) format, it will be stored in memory as follows:
 * 0x00 0x20 0xF1 0x47
 *
 * You can check this with the following code:

   float fl = UT_REAL;
   uint8_t *inmem = (uint8_t*)&fl;
   int x;
   for(x = 0; x < 4; x++){
       printf("0x%02X ", inmem[ x ]);
   }
   printf("\n");
 */
const float UT_REAL = 123456.00;

/*
 * libmodbus will convert all words to processor-endianness as they come in and also converts them
 * back to big endian as they are sent out.
 * The memory layout in modbus_mapping_t.tab_registers is thus processor-endianess.
 * Hence we define the comparison constants to check against the content of modbus_mapping_t.tab_registers
 * in terms of 16 bit integer values, that are likewise stored in memory in processor-endianess.
 */
const uint16_t UT_IREAL_ABCD[] = {0x47F1, 0x2000};
const uint16_t UT_IREAL_DCBA[] = {0x0020, 0xF147};
const uint16_t UT_IREAL_BADC[] = {0xF147, 0x0020};
const uint16_t UT_IREAL_CDAB[] = {0x2000, 0x47F1};

#endif /* _UNIT_TEST_H_ */
