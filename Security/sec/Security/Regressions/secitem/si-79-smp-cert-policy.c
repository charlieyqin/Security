/*
 *  si-79-smp-cert-policy.c
 *  Security
 *
 *  Copyright (c) 2014 Apple Inc. All Rights Reserved.
 *
 */

#include <CoreFoundation/CoreFoundation.h>
#include <Security/SecCertificate.h>
#include <Security/SecCertificatePriv.h>
#include <Security/SecCertificateInternal.h>
#include <Security/SecItem.h>
#include <Security/SecItemPriv.h>
#include <Security/SecIdentityPriv.h>
#include <Security/SecIdentity.h>
#include <Security/SecPolicy.h>
#include <Security/SecPolicyPriv.h>
#include <Security/SecPolicyInternal.h>
#include <Security/SecCMS.h>
#include <utilities/SecCFWrappers.h>
#include <stdlib.h>
#include <unistd.h>

#include "Security_regressions.h"

#if TARGET_OS_IPHONE

static const UInt8 kTestAppleRootCAECCCert[] = {
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
	0xFC,0x6F,0x59,0x5E,0xEF,0xEA,0x5E,0x87,0xAC,0x30,0x0D,
};

static const UInt8 kTestAppleSystemIntegrationCAECCCert[] = {
	0x30,0x82,0x02,0xD8,0x30,0x82,0x02,0x7F,0xA0,0x03,0x02,0x01,0x02,0x02,0x08,0x63,
	0x70,0x58,0xB8,0xE5,0xC6,0x5A,0x1E,0x30,0x0A,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,
	0x04,0x03,0x02,0x30,0x67,0x31,0x21,0x30,0x1F,0x06,0x03,0x55,0x04,0x03,0x0C,0x18,
	0x54,0x65,0x73,0x74,0x20,0x41,0x70,0x70,0x6C,0x65,0x20,0x52,0x6F,0x6F,0x74,0x20,
	0x43,0x41,0x20,0x2D,0x20,0x45,0x43,0x43,0x31,0x20,0x30,0x1E,0x06,0x03,0x55,0x04,
	0x0B,0x0C,0x17,0x43,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x69,0x6F,0x6E,
	0x20,0x41,0x75,0x74,0x68,0x6F,0x72,0x69,0x74,0x79,0x31,0x13,0x30,0x11,0x06,0x03,
	0x55,0x04,0x0A,0x0C,0x0A,0x41,0x70,0x70,0x6C,0x65,0x20,0x49,0x6E,0x63,0x2E,0x31,
	0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x30,0x1E,0x17,0x0D,
	0x31,0x34,0x30,0x32,0x30,0x36,0x31,0x36,0x32,0x36,0x34,0x37,0x5A,0x17,0x0D,0x32,
	0x34,0x30,0x32,0x30,0x34,0x31,0x36,0x32,0x36,0x34,0x37,0x5A,0x30,0x75,0x31,0x2F,
	0x30,0x2D,0x06,0x03,0x55,0x04,0x03,0x0C,0x26,0x54,0x65,0x73,0x74,0x20,0x41,0x70,
	0x70,0x6C,0x65,0x20,0x53,0x79,0x73,0x74,0x65,0x6D,0x20,0x49,0x6E,0x74,0x65,0x67,
	0x72,0x61,0x74,0x69,0x6F,0x6E,0x20,0x43,0x41,0x20,0x2D,0x20,0x45,0x43,0x43,0x31,
	0x20,0x30,0x1E,0x06,0x03,0x55,0x04,0x0B,0x0C,0x17,0x43,0x65,0x72,0x74,0x69,0x66,
	0x69,0x63,0x61,0x74,0x69,0x6F,0x6E,0x20,0x41,0x75,0x74,0x68,0x6F,0x72,0x69,0x74,
	0x79,0x31,0x13,0x30,0x11,0x06,0x03,0x55,0x04,0x0A,0x0C,0x0A,0x41,0x70,0x70,0x6C,
	0x65,0x20,0x49,0x6E,0x63,0x2E,0x31,0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,
	0x02,0x55,0x53,0x30,0x59,0x30,0x13,0x06,0x07,0x2A,0x86,0x48,0xCE,0x3D,0x02,0x01,
	0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x07,0x03,0x42,0x00,0x04,0x51,0xB4,
	0x48,0x6D,0x6B,0xB1,0xD2,0x48,0xE0,0x04,0x32,0x5E,0xA2,0x91,0xFF,0x86,0x21,0xE2,
	0x20,0x09,0xCE,0x46,0x7E,0xC2,0x10,0xAA,0x20,0x8A,0x47,0xF4,0x59,0x71,0xC2,0x69,
	0xBD,0xFE,0xF4,0xB8,0xEC,0xCB,0xDF,0x45,0x06,0x9B,0x64,0x3A,0x98,0x60,0x08,0x16,
	0xB8,0x87,0xF4,0x9E,0x6E,0xC5,0xBF,0x14,0xA9,0xB0,0x40,0x6B,0xD1,0x0B,0xA3,0x82,
	0x01,0x05,0x30,0x82,0x01,0x01,0x30,0x54,0x06,0x08,0x2B,0x06,0x01,0x05,0x05,0x07,
	0x01,0x01,0x04,0x48,0x30,0x46,0x30,0x44,0x06,0x08,0x2B,0x06,0x01,0x05,0x05,0x07,
	0x30,0x01,0x86,0x38,0x68,0x74,0x74,0x70,0x3A,0x2F,0x2F,0x6F,0x63,0x73,0x70,0x2D,
	0x75,0x61,0x74,0x2E,0x63,0x6F,0x72,0x70,0x2E,0x61,0x70,0x70,0x6C,0x65,0x2E,0x63,
	0x6F,0x6D,0x2F,0x6F,0x63,0x73,0x70,0x30,0x34,0x2D,0x74,0x65,0x73,0x74,0x61,0x70,
	0x70,0x6C,0x65,0x72,0x6F,0x6F,0x74,0x63,0x61,0x65,0x63,0x63,0x30,0x1D,0x06,0x03,
	0x55,0x1D,0x0E,0x04,0x16,0x04,0x14,0xA3,0x46,0x13,0xFE,0x94,0x7F,0xE0,0xA2,0x8F,
	0x16,0xF0,0xF8,0x1E,0x9B,0x8B,0x14,0x84,0x70,0x59,0xF9,0x30,0x12,0x06,0x03,0x55,
	0x1D,0x13,0x01,0x01,0xFF,0x04,0x08,0x30,0x06,0x01,0x01,0xFF,0x02,0x01,0x00,0x30,
	0x1F,0x06,0x03,0x55,0x1D,0x23,0x04,0x18,0x30,0x16,0x80,0x14,0xD2,0x47,0xE2,0xC5,
	0x34,0x71,0xC6,0x10,0x8D,0x93,0xEE,0x04,0x43,0x1F,0xE1,0x1B,0x0F,0xE1,0xCD,0x11,
	0x30,0x45,0x06,0x03,0x55,0x1D,0x1F,0x04,0x3E,0x30,0x3C,0x30,0x3A,0xA0,0x38,0xA0,
	0x36,0x86,0x34,0x68,0x74,0x74,0x70,0x3A,0x2F,0x2F,0x63,0x72,0x6C,0x2D,0x75,0x61,
	0x74,0x2E,0x63,0x6F,0x72,0x70,0x2E,0x61,0x70,0x70,0x6C,0x65,0x2E,0x63,0x6F,0x6D,
	0x2F,0x74,0x65,0x73,0x74,0x61,0x70,0x70,0x6C,0x65,0x72,0x6F,0x6F,0x74,0x63,0x61,
	0x65,0x63,0x63,0x2E,0x63,0x72,0x6C,0x30,0x0E,0x06,0x03,0x55,0x1D,0x0F,0x01,0x01,
	0xFF,0x04,0x04,0x03,0x02,0x01,0x06,0x30,0x0A,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,
	0x04,0x03,0x02,0x03,0x47,0x00,0x30,0x44,0x02,0x20,0x6A,0x68,0x3F,0x95,0xCA,0x35,
	0xD2,0xB6,0x46,0xF5,0x34,0xA2,0xF4,0x1A,0x8C,0x15,0x6D,0xC6,0x7E,0x88,0x95,0x9E,
	0x55,0x8E,0x8F,0x78,0x65,0x9D,0x5B,0x70,0x63,0x45,0x02,0x20,0x1B,0x45,0x91,0x33,
	0xF1,0x6E,0x7B,0xC1,0x0D,0x2E,0xF0,0x33,0xB3,0xFF,0xC3,0x1F,0xAC,0x6F,0xAB,0xFC,
	0x67,0xB6,0x1B,0x57,0xAF,0x88,0xA6,0xCF,0xA7,0x4F,0x20,0x06,
};

static const UInt8 kTestSMPCert[] = {
	0x30,0x82,0x02,0xC4,0x30,0x82,0x02,0x6B,0xA0,0x03,0x02,0x01,0x02,0x02,0x08,0x4B,
	0x62,0x72,0xF1,0xCD,0xCE,0xBA,0x8D,0x30,0x0A,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,
	0x04,0x03,0x02,0x30,0x75,0x31,0x2F,0x30,0x2D,0x06,0x03,0x55,0x04,0x03,0x0C,0x26,
	0x54,0x65,0x73,0x74,0x20,0x41,0x70,0x70,0x6C,0x65,0x20,0x53,0x79,0x73,0x74,0x65,
	0x6D,0x20,0x49,0x6E,0x74,0x65,0x67,0x72,0x61,0x74,0x69,0x6F,0x6E,0x20,0x43,0x41,
	0x20,0x2D,0x20,0x45,0x43,0x43,0x31,0x20,0x30,0x1E,0x06,0x03,0x55,0x04,0x0B,0x0C,
	0x17,0x43,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x69,0x6F,0x6E,0x20,0x41,
	0x75,0x74,0x68,0x6F,0x72,0x69,0x74,0x79,0x31,0x13,0x30,0x11,0x06,0x03,0x55,0x04,
	0x0A,0x0C,0x0A,0x41,0x70,0x70,0x6C,0x65,0x20,0x49,0x6E,0x63,0x2E,0x31,0x0B,0x30,
	0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x30,0x1E,0x17,0x0D,0x31,0x34,
	0x30,0x32,0x30,0x36,0x31,0x36,0x34,0x35,0x35,0x35,0x5A,0x17,0x0D,0x31,0x36,0x30,
	0x32,0x30,0x36,0x31,0x36,0x34,0x35,0x35,0x35,0x5A,0x30,0x70,0x31,0x32,0x30,0x30,
	0x06,0x03,0x55,0x04,0x03,0x0C,0x29,0x54,0x65,0x73,0x74,0x20,0x45,0x43,0x43,0x20,
	0x43,0x72,0x79,0x70,0x74,0x6F,0x20,0x53,0x65,0x72,0x76,0x69,0x63,0x65,0x73,0x20,
	0x45,0x6E,0x63,0x69,0x70,0x68,0x65,0x72,0x6D,0x65,0x6E,0x74,0x20,0x55,0x43,0x35,
	0x31,0x18,0x30,0x16,0x06,0x03,0x55,0x04,0x0B,0x0C,0x0F,0x43,0x72,0x79,0x70,0x74,
	0x6F,0x20,0x53,0x65,0x72,0x76,0x69,0x63,0x65,0x73,0x31,0x13,0x30,0x11,0x06,0x03,
	0x55,0x04,0x0A,0x0C,0x0A,0x41,0x70,0x70,0x6C,0x65,0x20,0x49,0x6E,0x63,0x2E,0x31,
	0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x30,0x59,0x30,0x13,
	0x06,0x07,0x2A,0x86,0x48,0xCE,0x3D,0x02,0x01,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,
	0x03,0x01,0x07,0x03,0x42,0x00,0x04,0xAC,0xB8,0x3A,0x1B,0x4E,0x15,0x87,0xDD,0xCF,
	0xCD,0x21,0x30,0x23,0x28,0xF2,0x86,0x10,0x28,0x7C,0xF3,0x65,0x39,0xCD,0xFD,0x30,
	0xB5,0x61,0x71,0xE0,0x59,0x20,0xB7,0xC0,0x59,0x24,0xF9,0x7F,0x75,0xBB,0xD5,0x30,
	0xC0,0x25,0x52,0xE2,0x13,0xF1,0x0B,0x4D,0x50,0xC4,0x46,0x57,0x6A,0x13,0x69,0xC9,
	0x82,0x8A,0xA9,0x21,0x24,0xD5,0x92,0xA3,0x81,0xE9,0x30,0x81,0xE6,0x30,0x4E,0x06,
	0x08,0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x01,0x04,0x42,0x30,0x40,0x30,0x3E,0x06,
	0x08,0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,0x86,0x32,0x68,0x74,0x74,0x70,0x3A,
	0x2F,0x2F,0x6F,0x63,0x73,0x70,0x2D,0x75,0x61,0x74,0x2E,0x63,0x6F,0x72,0x70,0x2E,
	0x61,0x70,0x70,0x6C,0x65,0x2E,0x63,0x6F,0x6D,0x2F,0x6F,0x63,0x73,0x70,0x30,0x34,
	0x2D,0x74,0x65,0x73,0x74,0x61,0x73,0x69,0x63,0x61,0x65,0x63,0x63,0x30,0x1D,0x06,
	0x03,0x55,0x1D,0x0E,0x04,0x16,0x04,0x14,0x73,0x0B,0x8A,0xF4,0xFA,0xA2,0xC9,0x6F,
	0xAC,0x2E,0x9C,0xCC,0xE9,0xFE,0xBD,0xA6,0xE2,0xF0,0xC0,0xFF,0x30,0x0C,0x06,0x03,
	0x55,0x1D,0x13,0x01,0x01,0xFF,0x04,0x02,0x30,0x00,0x30,0x1F,0x06,0x03,0x55,0x1D,
	0x23,0x04,0x18,0x30,0x16,0x80,0x14,0xA3,0x46,0x13,0xFE,0x94,0x7F,0xE0,0xA2,0x8F,
	0x16,0xF0,0xF8,0x1E,0x9B,0x8B,0x14,0x84,0x70,0x59,0xF9,0x30,0x36,0x06,0x03,0x55,
	0x1D,0x1F,0x04,0x2F,0x30,0x2D,0x30,0x2B,0xA0,0x29,0xA0,0x27,0x86,0x25,0x68,0x74,
	0x74,0x70,0x3A,0x2F,0x2F,0x75,0x61,0x74,0x2D,0x63,0x72,0x6C,0x2E,0x61,0x70,0x70,
	0x6C,0x65,0x2E,0x63,0x6F,0x6D,0x2F,0x61,0x73,0x69,0x63,0x61,0x65,0x63,0x63,0x2E,
	0x63,0x72,0x6C,0x30,0x0E,0x06,0x03,0x55,0x1D,0x0F,0x01,0x01,0xFF,0x04,0x04,0x03,
	0x02,0x03,0x28,0x30,0x0A,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x04,0x03,0x02,0x03,
	0x47,0x00,0x30,0x44,0x02,0x20,0x60,0x56,0xC6,0x37,0xB9,0x8B,0x58,0x05,0xF0,0x89,
	0x61,0x61,0xA4,0xB8,0x83,0x5F,0x9E,0xCF,0x6E,0x21,0x6E,0xEF,0xA1,0x89,0x5C,0xB5,
	0x2E,0x6E,0xE1,0x10,0x46,0x4F,0x02,0x20,0x07,0x8D,0xA5,0xD0,0xC8,0x85,0x31,0xF0,
	0x4B,0x2C,0xB5,0x1B,0x96,0xC4,0x5D,0x86,0x85,0xF8,0x1A,0x3A,0x37,0x6B,0xEC,0xD0,
	0x7F,0x45,0x88,0x35,0xD0,0x75,0xDC,0xA2,
};

static const UInt8 kAppleSystemIntegrationCAG3Cert[]={
	0x30,0x82,0x02,0xEB,0x30,0x82,0x02,0x70,0xA0,0x03,0x02,0x01,0x02,0x02,0x08,0x61,
	0x5A,0xA1,0xA9,0x73,0x3C,0xEB,0x81,0x30,0x0A,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,
	0x04,0x03,0x02,0x30,0x67,0x31,0x1B,0x30,0x19,0x06,0x03,0x55,0x04,0x03,0x0C,0x12,
	0x41,0x70,0x70,0x6C,0x65,0x20,0x52,0x6F,0x6F,0x74,0x20,0x43,0x41,0x20,0x2D,0x20,
	0x47,0x33,0x31,0x26,0x30,0x24,0x06,0x03,0x55,0x04,0x0B,0x0C,0x1D,0x41,0x70,0x70,
	0x6C,0x65,0x20,0x43,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x69,0x6F,0x6E,
	0x20,0x41,0x75,0x74,0x68,0x6F,0x72,0x69,0x74,0x79,0x31,0x13,0x30,0x11,0x06,0x03,
	0x55,0x04,0x0A,0x0C,0x0A,0x41,0x70,0x70,0x6C,0x65,0x20,0x49,0x6E,0x63,0x2E,0x31,
	0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x30,0x1E,0x17,0x0D,
	0x31,0x34,0x30,0x35,0x30,0x36,0x32,0x33,0x34,0x35,0x31,0x30,0x5A,0x17,0x0D,0x32,
	0x39,0x30,0x35,0x30,0x36,0x32,0x33,0x34,0x35,0x31,0x30,0x5A,0x30,0x75,0x31,0x29,
	0x30,0x27,0x06,0x03,0x55,0x04,0x03,0x0C,0x20,0x41,0x70,0x70,0x6C,0x65,0x20,0x53,
	0x79,0x73,0x74,0x65,0x6D,0x20,0x49,0x6E,0x74,0x65,0x67,0x72,0x61,0x74,0x69,0x6F,
	0x6E,0x20,0x43,0x41,0x20,0x2D,0x20,0x47,0x33,0x31,0x26,0x30,0x24,0x06,0x03,0x55,
	0x04,0x0B,0x0C,0x1D,0x41,0x70,0x70,0x6C,0x65,0x20,0x43,0x65,0x72,0x74,0x69,0x66,
	0x69,0x63,0x61,0x74,0x69,0x6F,0x6E,0x20,0x41,0x75,0x74,0x68,0x6F,0x72,0x69,0x74,
	0x79,0x31,0x13,0x30,0x11,0x06,0x03,0x55,0x04,0x0A,0x0C,0x0A,0x41,0x70,0x70,0x6C,
	0x65,0x20,0x49,0x6E,0x63,0x2E,0x31,0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,
	0x02,0x55,0x53,0x30,0x59,0x30,0x13,0x06,0x07,0x2A,0x86,0x48,0xCE,0x3D,0x02,0x01,
	0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x07,0x03,0x42,0x00,0x04,0xD1,0x57,
	0x4C,0x8E,0x38,0xD5,0xF7,0x36,0x28,0x54,0x7D,0x16,0x1A,0xE4,0xF0,0x4F,0x1E,0xB2,
	0xA8,0xC0,0x2F,0x1F,0xE2,0x26,0x69,0x76,0xDF,0x36,0xAB,0xDC,0xED,0xAF,0xA6,0x92,
	0xF2,0x5A,0x4E,0xAF,0x29,0x84,0xAC,0xF1,0x86,0x15,0x04,0x43,0xFA,0x83,0x03,0x03,
	0x58,0xF6,0x5E,0x8F,0xC2,0x22,0x29,0x28,0xF2,0x06,0x18,0x09,0x30,0x79,0xA3,0x81,
	0xF7,0x30,0x81,0xF4,0x30,0x46,0x06,0x08,0x2B,0x06,0x01,0x05,0x05,0x07,0x01,0x01,
	0x04,0x3A,0x30,0x38,0x30,0x36,0x06,0x08,0x2B,0x06,0x01,0x05,0x05,0x07,0x30,0x01,
	0x86,0x2A,0x68,0x74,0x74,0x70,0x3A,0x2F,0x2F,0x6F,0x63,0x73,0x70,0x2E,0x61,0x70,
	0x70,0x6C,0x65,0x2E,0x63,0x6F,0x6D,0x2F,0x6F,0x63,0x73,0x70,0x30,0x34,0x2D,0x61,
	0x70,0x70,0x6C,0x65,0x72,0x6F,0x6F,0x74,0x63,0x61,0x67,0x33,0x30,0x1D,0x06,0x03,
	0x55,0x1D,0x0E,0x04,0x16,0x04,0x14,0x26,0x5D,0xAF,0x92,0x3C,0x20,0x98,0x18,0x35,
	0xBE,0x98,0x50,0xA6,0x01,0x5E,0xA7,0xE9,0x21,0x2D,0x79,0x30,0x0F,0x06,0x03,0x55,
	0x1D,0x13,0x01,0x01,0xFF,0x04,0x05,0x30,0x03,0x01,0x01,0xFF,0x30,0x1F,0x06,0x03,
	0x55,0x1D,0x23,0x04,0x18,0x30,0x16,0x80,0x14,0xBB,0xB0,0xDE,0xA1,0x58,0x33,0x88,
	0x9A,0xA4,0x8A,0x99,0xDE,0xBE,0xBD,0xEB,0xAF,0xDA,0xCB,0x24,0xAB,0x30,0x37,0x06,
	0x03,0x55,0x1D,0x1F,0x04,0x30,0x30,0x2E,0x30,0x2C,0xA0,0x2A,0xA0,0x28,0x86,0x26,
	0x68,0x74,0x74,0x70,0x3A,0x2F,0x2F,0x63,0x72,0x6C,0x2E,0x61,0x70,0x70,0x6C,0x65,
	0x2E,0x63,0x6F,0x6D,0x2F,0x61,0x70,0x70,0x6C,0x65,0x72,0x6F,0x6F,0x74,0x63,0x61,
	0x67,0x33,0x2E,0x63,0x72,0x6C,0x30,0x0E,0x06,0x03,0x55,0x1D,0x0F,0x01,0x01,0xFF,
	0x04,0x04,0x03,0x02,0x01,0x06,0x30,0x10,0x06,0x0A,0x2A,0x86,0x48,0x86,0xF7,0x63,
	0x64,0x06,0x02,0x0D,0x04,0x02,0x05,0x00,0x30,0x0A,0x06,0x08,0x2A,0x86,0x48,0xCE,
	0x3D,0x04,0x03,0x02,0x03,0x69,0x00,0x30,0x66,0x02,0x31,0x00,0xD6,0xB2,0xC3,0xB3,
	0x3D,0xE3,0x30,0xE4,0x7A,0x24,0x62,0x35,0xDA,0xF0,0xB9,0xDC,0x3B,0x66,0x94,0x40,
	0xBA,0x8D,0x43,0xC4,0x2A,0xF5,0xE3,0xA1,0x4A,0x7C,0xD5,0x87,0x24,0xCC,0xEA,0x49,
	0x0E,0xEE,0xAA,0xE4,0x72,0x0D,0x63,0x4F,0x03,0x07,0x6C,0x63,0x02,0x31,0x00,0xFF,
	0xDF,0x24,0x7E,0xA8,0x28,0x02,0x55,0xBF,0xEB,0x8D,0x72,0x1D,0xC9,0x27,0x82,0xA1,
	0x0D,0xB7,0xD5,0x0F,0xAA,0xF2,0xFF,0x49,0xFA,0x3F,0xA4,0xED,0x44,0xEE,0x53,0x76,
	0x89,0x18,0x0A,0x64,0xC6,0x96,0x00,0x47,0x9D,0x40,0x04,0xEF,0x5A,0xAA,0x07,
};

static const UInt8 kProdSMPCert[]={
	0x30,0x82,0x02,0xC6,0x30,0x82,0x02,0x6D,0xA0,0x03,0x02,0x01,0x02,0x02,0x08,0x52,
	0x6F,0x62,0xEF,0x7A,0x0F,0x39,0x08,0x30,0x0A,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,
	0x04,0x03,0x02,0x30,0x75,0x31,0x29,0x30,0x27,0x06,0x03,0x55,0x04,0x03,0x0C,0x20,
	0x41,0x70,0x70,0x6C,0x65,0x20,0x53,0x79,0x73,0x74,0x65,0x6D,0x20,0x49,0x6E,0x74,
	0x65,0x67,0x72,0x61,0x74,0x69,0x6F,0x6E,0x20,0x43,0x41,0x20,0x2D,0x20,0x47,0x33,
	0x31,0x26,0x30,0x24,0x06,0x03,0x55,0x04,0x0B,0x0C,0x1D,0x41,0x70,0x70,0x6C,0x65,
	0x20,0x43,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x69,0x6F,0x6E,0x20,0x41,
	0x75,0x74,0x68,0x6F,0x72,0x69,0x74,0x79,0x31,0x13,0x30,0x11,0x06,0x03,0x55,0x04,
	0x0A,0x0C,0x0A,0x41,0x70,0x70,0x6C,0x65,0x20,0x49,0x6E,0x63,0x2E,0x31,0x0B,0x30,
	0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x30,0x1E,0x17,0x0D,0x31,0x34,
	0x30,0x35,0x30,0x38,0x30,0x31,0x32,0x31,0x31,0x34,0x5A,0x17,0x0D,0x31,0x36,0x30,
	0x36,0x30,0x36,0x30,0x31,0x32,0x31,0x31,0x34,0x5A,0x30,0x6C,0x31,0x32,0x30,0x30,
	0x06,0x03,0x55,0x04,0x03,0x0C,0x29,0x65,0x63,0x63,0x2D,0x63,0x72,0x79,0x70,0x74,
	0x6F,0x2D,0x73,0x65,0x72,0x76,0x69,0x63,0x65,0x73,0x2D,0x65,0x6E,0x63,0x69,0x70,
	0x68,0x65,0x72,0x6D,0x65,0x6E,0x74,0x5F,0x55,0x43,0x35,0x2D,0x50,0x52,0x4F,0x44,
	0x31,0x14,0x30,0x12,0x06,0x03,0x55,0x04,0x0B,0x0C,0x0B,0x69,0x4F,0x53,0x20,0x53,
	0x79,0x73,0x74,0x65,0x6D,0x73,0x31,0x13,0x30,0x11,0x06,0x03,0x55,0x04,0x0A,0x0C,
	0x0A,0x41,0x70,0x70,0x6C,0x65,0x20,0x49,0x6E,0x63,0x2E,0x31,0x0B,0x30,0x09,0x06,
	0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x30,0x59,0x30,0x13,0x06,0x07,0x2A,0x86,
	0x48,0xCE,0x3D,0x02,0x01,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x07,0x03,
	0x42,0x00,0x04,0xBC,0x09,0xB9,0xBA,0x02,0xDA,0x80,0x3F,0x60,0xCC,0xE0,0xEB,0xC6,
	0x16,0x76,0xDE,0x7F,0x40,0x7A,0x52,0x34,0xB8,0x22,0x65,0xB8,0x7A,0x08,0x22,0xD1,
	0x6F,0xF4,0x5A,0x0F,0x69,0xE2,0x31,0x7F,0x83,0x60,0x04,0x0A,0xBF,0x80,0xF7,0x8D,
	0xEB,0x40,0x15,0x84,0xBE,0x65,0x70,0x41,0x22,0xEE,0x63,0x0B,0x04,0x5E,0xB3,0x4F,
	0xD7,0x73,0x0E,0xA3,0x81,0xEF,0x30,0x81,0xEC,0x30,0x45,0x06,0x08,0x2B,0x06,0x01,
	0x05,0x05,0x07,0x01,0x01,0x04,0x39,0x30,0x37,0x30,0x35,0x06,0x08,0x2B,0x06,0x01,
	0x05,0x05,0x07,0x30,0x01,0x86,0x29,0x68,0x74,0x74,0x70,0x3A,0x2F,0x2F,0x6F,0x63,
	0x73,0x70,0x2E,0x61,0x70,0x70,0x6C,0x65,0x2E,0x63,0x6F,0x6D,0x2F,0x6F,0x63,0x73,
	0x70,0x30,0x34,0x2D,0x61,0x70,0x70,0x6C,0x65,0x73,0x69,0x63,0x61,0x33,0x30,0x31,
	0x30,0x1D,0x06,0x03,0x55,0x1D,0x0E,0x04,0x16,0x04,0x14,0xD2,0xFD,0x1F,0xDD,0x61,
	0xA8,0xE4,0x0E,0x78,0xBD,0xDB,0x60,0xB9,0xCC,0x7A,0x3F,0x46,0x8B,0xF5,0xA4,0x30,
	0x0C,0x06,0x03,0x55,0x1D,0x13,0x01,0x01,0xFF,0x04,0x02,0x30,0x00,0x30,0x1F,0x06,
	0x03,0x55,0x1D,0x23,0x04,0x18,0x30,0x16,0x80,0x14,0x26,0x5D,0xAF,0x92,0x3C,0x20,
	0x98,0x18,0x35,0xBE,0x98,0x50,0xA6,0x01,0x5E,0xA7,0xE9,0x21,0x2D,0x79,0x30,0x34,
	0x06,0x03,0x55,0x1D,0x1F,0x04,0x2D,0x30,0x2B,0x30,0x29,0xA0,0x27,0xA0,0x25,0x86,
	0x23,0x68,0x74,0x74,0x70,0x3A,0x2F,0x2F,0x63,0x72,0x6C,0x2E,0x61,0x70,0x70,0x6C,
	0x65,0x2E,0x63,0x6F,0x6D,0x2F,0x61,0x70,0x70,0x6C,0x65,0x73,0x69,0x63,0x61,0x33,
	0x2E,0x63,0x72,0x6C,0x30,0x0E,0x06,0x03,0x55,0x1D,0x0F,0x01,0x01,0xFF,0x04,0x04,
	0x03,0x02,0x03,0x28,0x30,0x0F,0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x63,0x64,0x06,
	0x1E,0x04,0x02,0x05,0x00,0x30,0x0A,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x04,0x03,
	0x02,0x03,0x47,0x00,0x30,0x44,0x02,0x20,0x33,0x1F,0xB7,0xC0,0x93,0x22,0x9C,0x71,
	0xD8,0x62,0xF1,0x7B,0x72,0xDC,0x97,0x63,0xDF,0xD1,0x3B,0xBF,0xD7,0x8C,0xB0,0xE7,
	0xE0,0xC1,0x6B,0x26,0x6A,0xC4,0xF0,0x14,0x02,0x20,0x20,0xD7,0xD7,0xD1,0x7B,0xAD,
	0x90,0x83,0x23,0xEA,0x34,0x1E,0x0C,0x8F,0x90,0xAB,0x97,0xB1,0x2D,0x06,0xE3,0x30,
	0x56,0x29,0x20,0x94,0x74,0x36,0xFD,0x1B,0x9C,0xD5,
};

static void test_smp_cert_policy()
{
	CFDateRef date=NULL;
	CFArrayRef policies=NULL;
	SecPolicyRef policy=NULL;
	SecTrustRef trust=NULL;
    SecCertificateRef testCert0=NULL, testCert1=NULL, testRoot=NULL;
    SecCertificateRef prodCert0=NULL, prodCert1=NULL;
    CFMutableArrayRef testCerts=NULL, prodCerts=NULL;
    SecTrustResultType trustResult;
    CFIndex chainLen;

    /* Test hierarchy */
    isnt(testCert0 = SecCertificateCreateWithBytes(NULL, kTestSMPCert, sizeof(kTestSMPCert)),
	    NULL, "create testCert0");
    isnt(testCert1 = SecCertificateCreateWithBytes(NULL, kTestAppleSystemIntegrationCAECCCert, sizeof(kTestAppleSystemIntegrationCAECCCert)),
	    NULL, "create testCert1");
    isnt(testRoot = SecCertificateCreateWithBytes(NULL, kTestAppleRootCAECCCert, sizeof(kTestAppleRootCAECCCert)),
	    NULL, "create testRoot");

    isnt(testCerts = CFArrayCreateMutable(kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks), NULL, "create test cert array");
    CFArrayAppendValue(testCerts, testCert0);
    CFArrayAppendValue(testCerts, testCert1);

    /* Production hierarchy */
    isnt(prodCert0 = SecCertificateCreateWithBytes(NULL, kProdSMPCert, sizeof(kProdSMPCert)),
         NULL, "create prodCert0");
    isnt(prodCert1 = SecCertificateCreateWithBytes(NULL, kAppleSystemIntegrationCAG3Cert, sizeof(kAppleSystemIntegrationCAG3Cert)),
         NULL, "create prodCert1");

    isnt(prodCerts = CFArrayCreateMutable(kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks), NULL, "create prod cert array");
    CFArrayAppendValue(prodCerts, prodCert0);
    CFArrayAppendValue(prodCerts, prodCert1);


	/* Case 1: production policy with production certs (should succeed) */
    isnt(policy = SecPolicyCreateAppleSMPEncryption(), NULL, "create policy");
    policies = CFArrayCreate(NULL, (const void **)&policy, 1, &kCFTypeArrayCallBacks);
    CFRelease(policy);
	policy = NULL;
    ok_status(SecTrustCreateWithCertificates(prodCerts, policies, &trust),
        "create trust");
	CFRelease(policies);
	policies = NULL;
	isnt(date = CFDateCreateForGregorianZuluMoment(NULL, 2014, 4, 11, 12, 0, 0),
			NULL, "create verify date");
    //%%% policy currently doesn't care about expiration dates
	//ok_status(SecTrustSetVerifyDate(trust, date), "set date");
	CFReleaseSafe(date);
	date = NULL;
	ok_status(SecTrustEvaluate(trust, &trustResult), "evaluate trust");
	ok(trustResult == kSecTrustResultUnspecified, "trustResult 4 expected (got %d)",
       (int)trustResult);
    chainLen = SecTrustGetCertificateCount(trust);
    ok(chainLen == 3, "chain length 3 expected (got %d)", (int)chainLen);
	CFRelease(trust);
	trust = NULL;

	/* Case 2: test policy with test certs (should succeed) */
    isnt(policy = SecPolicyCreateTestAppleSMPEncryption(), NULL, "create policy");
    policies = CFArrayCreate(NULL, (const void **)&policy, 1, &kCFTypeArrayCallBacks);
    CFRelease(policy);
	policy = NULL;
    ok_status(SecTrustCreateWithCertificates(testCerts, policies, &trust),
        "create trust");
	CFRelease(policies);
	policies = NULL;
	isnt(date = CFDateCreateForGregorianZuluMoment(NULL, 2014, 4, 11, 12, 0, 0),
			NULL, "create verify date");
    //%%% policy currently doesn't care about expiration dates
	//ok_status(SecTrustSetVerifyDate(trust, date), "set date");
	CFReleaseSafe(date);
	date = NULL;

	ok_status(SecTrustEvaluate(trust, &trustResult), "evaluate trust");
	ok(trustResult == kSecTrustResultUnspecified, "trustResult 4 expected (got %d)",
       (int)trustResult);
    chainLen = SecTrustGetCertificateCount(trust);
    ok(chainLen == 3, "chain length 3 expected (got %d)", (int)chainLen);
	CFRelease(trust);
	trust = NULL;

	/* Case 3: production policy with test certs (should fail) */
    isnt(policy = SecPolicyCreateAppleSMPEncryption(), NULL, "create policy");
    policies = CFArrayCreate(NULL, (const void **)&policy, 1, &kCFTypeArrayCallBacks);
    CFRelease(policy);
	policy = NULL;
    ok_status(SecTrustCreateWithCertificates(testCerts, policies, &trust),
        "create trust");
	CFRelease(policies);
	policies = NULL;
	isnt(date = CFDateCreateForGregorianZuluMoment(NULL, 2014, 4, 11, 12, 0, 0),
			NULL, "create verify date");
    //%%% policy currently doesn't care about expiration dates
	//ok_status(SecTrustSetVerifyDate(trust, date), "set date");
	CFReleaseSafe(date);
	date = NULL;
	ok_status(SecTrustEvaluate(trust, &trustResult), "evaluate trust");
	ok(trustResult == kSecTrustResultRecoverableTrustFailure, "trustResult 5 expected (got %d)",
       (int)trustResult);
	CFRelease(trust);
	trust = NULL;

	/* Case 4: test policy with production certs (should fail) */
    isnt(policy = SecPolicyCreateTestAppleSMPEncryption(), NULL, "create policy");
    policies = CFArrayCreate(NULL, (const void **)&policy, 1, &kCFTypeArrayCallBacks);
    CFRelease(policy);
	policy = NULL;
    ok_status(SecTrustCreateWithCertificates(prodCerts, policies, &trust),
        "create trust");
	CFRelease(policies);
	policies = NULL;
	isnt(date = CFDateCreateForGregorianZuluMoment(NULL, 2014, 4, 11, 12, 0, 0),
			NULL, "create verify date");
    //%%% policy currently doesn't care about expiration dates
	//ok_status(SecTrustSetVerifyDate(trust, date), "set date");
	CFReleaseSafe(date);
	date = NULL;
	ok_status(SecTrustEvaluate(trust, &trustResult), "evaluate trust");
	ok(trustResult == kSecTrustResultRecoverableTrustFailure, "trustResult 5 expected (got %d)",
       (int)trustResult);
	CFRelease(trust);
	trust = NULL;

    CFReleaseSafe(testCert0);
    CFReleaseSafe(testCert1);
    CFReleaseSafe(testRoot);
    CFReleaseSafe(prodCert0);
    CFReleaseSafe(prodCert1);

    CFReleaseSafe(testCerts);
    CFReleaseSafe(prodCerts);
}

static void tests(void)
{
    test_smp_cert_policy();
}

int si_79_smp_cert_policy(int argc, char *const *argv)
{
	plan_tests(29);

	tests();

	return 0;
}

#endif
