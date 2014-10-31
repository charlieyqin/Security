/*
 * Copyright (c) 2014 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
    @header SecPolicyCerts
    Provides certificates used by policies for specific Apple services.
    These certificates allow a complete chain to be built in cases where
    the caller is unable to provide them; no inherent trust is granted
    by adding certificates to this file.
*/

#ifndef _SECURITY_SECPOLICYCERTS_H_
#define _SECURITY_SECPOLICYCERTS_H_

/* Test Apple Root CA - ECC */
static const UInt8 _SEC_TestAppleRootCAECC[]={
    0x30,0x82,0x02,0x27,0x30,0x82,0x01,0xCD,0xA0,0x03,0x02,0x01,0x02,0x02,0x08,0x59,
    0xD1,0xEC,0x10,0x92,0x41,0xC7,0xC4,0x30,0x0A,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,
    0x04,0x03,0x02,0x30,0x67,0x31,0x21,0x30,0x1F,0x06,0x03,0x55,0x04,0x03,0x0C,0x18,
    0x54,0x65,0x73,0x74,0x20,0x41,0x70,0x70,0x6C,0x65,0x20,0x52,0x6F,0x6F,0x74,0x20,
    0x43,0x41,0x20,0x2D,0x20,0x45,0x43,0x43,0x31,0x20,0x30,0x1E,0x06,0x03,0x55,0x04,
    0x0B,0x0C,0x17,0x43,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x69,0x6F,0x6E,
    0x20,0x41,0x75,0x74,0x68,0x6F,0x72,0x69,0x74,0x79,0x31,0x13,0x30,0x11,0x06,0x03,
    0x55,0x04,0x0A,0x0C,0x0A,0x41,0x70,0x70,0x6C,0x65,0x20,0x49,0x6E,0x63,0x2E,0x31,
    0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x30,0x1E,0x17,0x0D,
    0x31,0x34,0x30,0x31,0x33,0x31,0x32,0x31,0x34,0x36,0x34,0x36,0x5A,0x17,0x0D,0x33,
    0x34,0x30,0x31,0x32,0x36,0x32,0x31,0x34,0x36,0x34,0x36,0x5A,0x30,0x67,0x31,0x21,
    0x30,0x1F,0x06,0x03,0x55,0x04,0x03,0x0C,0x18,0x54,0x65,0x73,0x74,0x20,0x41,0x70,
    0x70,0x6C,0x65,0x20,0x52,0x6F,0x6F,0x74,0x20,0x43,0x41,0x20,0x2D,0x20,0x45,0x43,
    0x43,0x31,0x20,0x30,0x1E,0x06,0x03,0x55,0x04,0x0B,0x0C,0x17,0x43,0x65,0x72,0x74,
    0x69,0x66,0x69,0x63,0x61,0x74,0x69,0x6F,0x6E,0x20,0x41,0x75,0x74,0x68,0x6F,0x72,
    0x69,0x74,0x79,0x31,0x13,0x30,0x11,0x06,0x03,0x55,0x04,0x0A,0x0C,0x0A,0x41,0x70,
    0x70,0x6C,0x65,0x20,0x49,0x6E,0x63,0x2E,0x31,0x0B,0x30,0x09,0x06,0x03,0x55,0x04,
    0x06,0x13,0x02,0x55,0x53,0x30,0x59,0x30,0x13,0x06,0x07,0x2A,0x86,0x48,0xCE,0x3D,
    0x02,0x01,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x07,0x03,0x42,0x00,0x04,
    0x7B,0x38,0x10,0xD0,0x0A,0xA3,0x1B,0x7C,0x1D,0x24,0xFB,0x39,0xD6,0x6B,0x1C,0x0A,
    0x97,0x48,0x30,0xFF,0x4C,0x70,0x49,0x3D,0x21,0x66,0x4F,0xF5,0x89,0x00,0xAF,0x93,
    0xEF,0x74,0x9A,0xE8,0x4C,0x27,0x3D,0xBE,0x95,0x50,0x52,0x3D,0x53,0x90,0xF3,0x32,
    0xAB,0x83,0xB6,0x5E,0x73,0xC8,0xE7,0x17,0x8B,0x18,0x09,0x93,0x9F,0x97,0xD5,0x16,
    0xA3,0x63,0x30,0x61,0x30,0x1D,0x06,0x03,0x55,0x1D,0x0E,0x04,0x16,0x04,0x14,0xD2,
    0x47,0xE2,0xC5,0x34,0x71,0xC6,0x10,0x8D,0x93,0xEE,0x04,0x43,0x1F,0xE1,0x1B,0x0F,
    0xE1,0xCD,0x11,0x30,0x0F,0x06,0x03,0x55,0x1D,0x13,0x01,0x01,0xFF,0x04,0x05,0x30,
    0x03,0x01,0x01,0xFF,0x30,0x1F,0x06,0x03,0x55,0x1D,0x23,0x04,0x18,0x30,0x16,0x80,
    0x14,0xD2,0x47,0xE2,0xC5,0x34,0x71,0xC6,0x10,0x8D,0x93,0xEE,0x04,0x43,0x1F,0xE1,
    0x1B,0x0F,0xE1,0xCD,0x11,0x30,0x0E,0x06,0x03,0x55,0x1D,0x0F,0x01,0x01,0xFF,0x04,
    0x04,0x03,0x02,0x01,0x06,0x30,0x0A,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x04,0x03,
    0x02,0x03,0x48,0x00,0x30,0x45,0x02,0x21,0x00,0xDC,0x06,0x2B,0x72,0x87,0x20,0xEC,
    0xF7,0xDC,0xC8,0xF2,0xF8,0x89,0x0A,0x57,0x63,0x9A,0x92,0x4A,0x84,0x6E,0xDD,0x17,
    0x50,0xEE,0x6F,0x01,0x4C,0xA1,0xA0,0x74,0xD1,0x02,0x20,0x1F,0x35,0x7A,0xB5,0x0B,
    0x79,0x80,0xD4,0x9C,0x9F,0x31,0xDC,0x36,0x1C,0xC6,0xFD,0x65,0x72,0x40,0x67,0xBA,
    0xFC,0x6F,0x59,0x5E,0xEF,0xEA,0x5E,0x87,0xAC,0x30,0x0D
};

#endif /* !_SECURITY_SECPOLICYCERTS_H_ */