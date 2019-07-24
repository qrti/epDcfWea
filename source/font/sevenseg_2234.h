// max width, height, spacing, num chars, n * (char, width, offset HB:LB)

const uint8_t sevenseg_2234[] PROGMEM = {
0x16,0x22,0x04,0x28,0x20,0x01,0x00,0xa4,0x25,0x13,0x00,0xa9,0x2a,0x15,0x00,0xee,
0x2b,0x11,0x01,0x30,0x2d,0x11,0x01,0x5a,0x2e,0x05,0x01,0x77,0x30,0x16,0x01,0x85,
0x31,0x16,0x01,0xe3,0x32,0x16,0x02,0x0f,0x33,0x16,0x02,0x6a,0x34,0x16,0x02,0xbf,
0x35,0x16,0x02,0xff,0x36,0x16,0x03,0x5a,0x37,0x16,0x03,0xb8,0x38,0x16,0x03,0xe8,
0x39,0x16,0x04,0x4b,0x43,0x16,0x04,0xab,0x44,0x16,0x04,0xe8,0x46,0x16,0x05,0x38,
0x4d,0x16,0x05,0x76,0x53,0x16,0x05,0xc3,0x54,0x16,0x06,0x21,0x57,0x16,0x06,0x50,
0x61,0x16,0x06,0x97,0x65,0x16,0x06,0xdd,0x68,0x16,0x07,0x22,0x6f,0x16,0x07,0x60,
0x72,0x16,0x07,0xa9,0x75,0x16,0x07,0xd7,0x80,0x16,0x08,0x0a,0x81,0x16,0x08,0x31,
0x82,0x16,0x08,0x58,0x83,0x16,0x08,0x7f,0x84,0x16,0x08,0x9e,0x85,0x16,0x08,0xbf,
0x86,0x16,0x08,0xde,0x87,0x16,0x08,0xff,0x88,0x16,0x09,0x1e,0x89,0x16,0x09,0x45,
0x8a,0x16,0x09,0x6e,

0x00,0x01,0x02,0x00,0x00, // SPACE

0x00,0x01,0xc0,0xac,0xea,0x00,0x00,0xc0,0xff,0xff,0xb0,0xff,0x0f,0xec,0x3f,0xff, // %
0x01,0xfc,0x7f,0xc0,0xff,0xff,0x00,0x00,0x00,0x55,0x01,0x80,0x80,0x1f,0x3f,0x7f,
0x71,0x71,0x71,0x7f,0x3f,0x1f,0x80,0xe0,0xf0,0xf8,0x7c,0x3c,0x1c,0x80,0xe0,0xf0,
0xf0,0x70,0x07,0x07,0x07,0x03,0x1c,0x1e,0x1f,0x0f,0x07,0x03,0x7c,0xfe,0xff,0xc7,
0xc7,0xc7,0xff,0xfe,0x7c,

0x00,0x01,0x03,0x00,0x00,0x30,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0x93,0xff,0xef, // *
0xef,0xff,0x1b,0x54,0x00,0x2e,0x40,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,
0x87,0x8f,0x9f,0xbe,0xbc,0xb8,0x80,0xff,0xff,0xff,0x80,0xb8,0xbc,0xbe,0x9f,0x8f,
0x87,0x80,0xc3,0xe3,0xf3,0xfb,0x7b,0x3b,0xff,0xff,0xff,0x3b,0x7b,0xfb,0xf3,0xe3,
0xc3,0x07,

0x00,0x07,0xc0,0x00,0x00,0x00,0x00,0xac,0xea,0xff,0xaa,0x7e,0x55,0xff,0x57,0x35, // +
0x00,0xf0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xfe,0xff,0xff,0xff,0xfe,0x80,
0x03,0xff,0xff,0xff,0xff,0xff,0x03,0x01,0x01,0x01,

0x00,0x07,0xc0,0x00,0x00,0x00,0x00,0xac,0xaa,0xaa,0xaa,0x7e,0x55,0x55,0x55,0x35, // -
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x03,0x03,

0x00,0x03,0xe0,0x00,0x00,0x00,0xc0,0xea,0x57,0x03,0xc0,0xc0,0x01,0x01, // .

0x03,0x1f,0x00,0xff,0x57,0x55,0x55,0xfd,0xff,0x9f,0xaa,0xff,0x6f,0xff,0xff,0xfb, // 0
0xdf,0xb3,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0x0a,0x00,0x00,0x00,0x00,0x0a,0xfc,
0xfc,0xfb,0xf7,0xef,0xef,0xf7,0xfb,0xfc,0xfc,0xff,0xff,0x7f,0x3f,0x80,0xc0,0xe0,
0xf0,0xf8,0xf8,0x3f,0x7f,0xff,0xff,0xfe,0xfe,0xfc,0xf8,0xf0,0xf8,0xfc,0x7e,0x3f,
0x0f,0x07,0x01,0xf0,0xf8,0xfc,0xfe,0xfe,0xff,0xff,0x7f,0xbf,0xdf,0xe0,0xe0,0xe0,
0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xdf,0xbf,0x7f,0xff,0xff,

0x00,0xff,0xfc,0x00,0x00,0x00,0x00,0xfc,0x0a,0x00,0x00,0x00,0xc0,0x5f,0x00,0x00, // 1
0x00,0x00,0xbc,0x0f,0x00,0x00,0x00,0xc0,0x5f,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,
0xf0,0xf8,0x1f,0x3f,0x7f,0xf0,0xf8,0xfe,0xfe,0x1f,0x3f,0x7f,

0x03,0xc0,0x07,0x8f,0xff,0xff,0xff,0xff,0xff,0x55,0x55,0x55,0xd5,0xff,0xff,0xab, // 2
0xaa,0xaa,0xea,0xff,0xff,0xff,0xff,0x7f,0xff,0x0f,0x00,0x00,0x00,0x00,0x0f,0x00,
0x00,0x0f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0xef,0xf7,
0xfb,0xfc,0xfc,0x00,0x00,0xbf,0x7f,0xff,0xff,0xff,0xff,0xff,0xfe,0xfd,0xfb,0x06,
0x01,0x01,0xff,0xff,0x7f,0xbf,0xdf,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,
0xe0,0xe0,0xe0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x03,0x1f,0xd0,0xab,0xaa,0xaa,0xfe,0x0f,0x00,0xfc,0xff,0xff,0xff,0x00,0x00, // 3
0xf7,0xff,0xff,0x0f,0xfc,0xff,0xff,0xff,0xff,0x50,0x55,0x55,0x55,0x55,0x00,0x07,
0x0f,0xef,0xf7,0xfb,0xfc,0xfc,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
0xbf,0x7f,0xff,0x7f,0x3f,0x01,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0xfb,0xfd,0xfe,
0xfc,0xf8,0x80,0xc0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,
0xdf,0xbf,0x7f,0xff,0xff,

0x00,0x07,0xc0,0xff,0x03,0x00,0x00,0xfc,0xff,0xbf,0xaa,0xaa,0xea,0xff,0x7f,0x55, // 4
0x55,0x55,0xfd,0x0f,0x00,0x00,0x00,0xc0,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,
0xfc,0xf8,0xf0,0xe0,0xe0,0xf0,0xf8,0xfc,0xfc,0xff,0xff,0xff,0x7f,0xbf,0xbf,0x7f,
0xff,0x7f,0x3f,0x01,0x01,0x06,0xfb,0xfd,0xfe,0xfc,0xf8,0x1f,0x3f,0x7f,0xff,0xff,

0x03,0xc0,0x07,0xff,0xff,0xff,0xff,0x2f,0xff,0x7f,0x55,0x55,0x55,0xf5,0xbf,0xaa, // 5
0xaa,0xaa,0xfe,0xff,0xdf,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,0x00,0x0f,0xfc,
0xfc,0xfb,0xf7,0xef,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
0x0f,0x00,0x00,0xff,0xff,0xff,0x7f,0xbf,0x00,0x00,0x01,0x01,0x06,0xfb,0xfd,0xfe,
0xff,0xff,0x00,0x00,0x00,0x80,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,
0xe0,0xe0,0xdf,0xbf,0x7f,0xff,0xff,0x00,0x00,0x00,0x00,

0x03,0xc0,0x07,0xff,0xff,0xff,0xff,0x2f,0xff,0x7f,0x55,0x55,0x55,0xf5,0xff,0xab, // 6
0xaa,0xaa,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,0x00,0x0f,0xfc,
0xfc,0xfb,0xf7,0xef,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
0x0f,0x00,0x00,0x3f,0x7f,0xff,0x7f,0xbf,0x00,0x00,0xf8,0xfc,0xfe,0xfd,0xfb,0xfb,
0xfd,0xfe,0xff,0xff,0xff,0xff,0x7f,0xbf,0xdf,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,
0xe0,0xe0,0xe0,0xe0,0xe0,0xdf,0xbf,0x7f,0xff,0xff,0x00,0x00,0x00,0x00,

0x00,0x1f,0xff,0xf0,0x57,0x55,0x55,0xfd,0x0f,0x00,0x00,0x00,0x40,0xaf,0x00,0x00, // 7
0x00,0x00,0xfc,0x0f,0x00,0x00,0x00,0x40,0xaf,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0x07,0x0f,0xef,0xf7,0xfb,0xfc,0xfc,0x3f,0x7f,0xf0,0xf8,0xfc,0xfe,0xfe,0x3f,0x7f,

0x03,0x07,0x1f,0xff,0xab,0xaa,0xaa,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x57, // 8
0x55,0x55,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,0x00,0x0f,0xfc,
0xfc,0xfb,0xf7,0xef,0xef,0xf7,0xfb,0xfc,0xfc,0xff,0xff,0x7f,0xbf,0xdf,0xc0,0xc0,
0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xdf,0xbf,0x7f,0xff,0xff,0xfe,
0xfe,0xfd,0xfb,0xf7,0xf7,0xfb,0xfd,0xfe,0xfe,0xff,0xff,0x7f,0xbf,0xdf,0xe0,0xe0,
0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xdf,0xbf,0x7f,0xff,0xff,0x00,
0x00,0x00,0x00,

0x03,0x07,0xc0,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xaa,0xaa,0xea,0xff,0x7f,0x55, // 9
0x55,0x55,0xfd,0xff,0xef,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,0x00,0x0f,0xfc,
0xfc,0xfb,0xf7,0xef,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
0xef,0xf7,0xfb,0xfc,0xfc,0xff,0xff,0xff,0x7f,0xbf,0xbf,0x7f,0xff,0x7f,0x3f,0x01,
0x01,0x06,0xfb,0xfd,0xfe,0xfc,0xf8,0x00,0x00,0x00,0x80,0xe0,0xe0,0xe0,0xe0,0xe0,
0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xdf,0xbf,0x7f,0xff,0xff,0x00,0x00,0x00,0x00,

0x00,0x03,0xc0,0xff,0xff,0x83,0xaa,0xaa,0x7a,0xff,0xf7,0x7f,0x55,0x35,0x00,0x00, // C
0xfc,0x03,0x00,0x00,0x00,0xc0,0xbf,0xaa,0x3a,0x00,0x00,0x40,0x55,0x55,0x05,0xf0,
0xf8,0xfc,0x1c,0x1c,0x1c,0xfc,0xf8,0xf0,0x01,0x07,0x07,0x07,0x07,0x07,0x01,0xff,
0xff,0xfe,0xfd,0x01,0xf7,0xf7,0xe3,0xc1,0xff,0xff,0x7f,0xbf,0x80,

0x00,0x03,0x1f,0xff,0xab,0xaa,0xaa,0xff,0xf3,0x2f,0x00,0x00,0xe0,0x3f,0xff,0x03, // D
0x00,0x00,0xff,0xf3,0xff,0xff,0xff,0xff,0x2f,0x50,0x55,0x55,0x55,0x03,0x00,0xfc,
0xfc,0xfb,0xf7,0xef,0xee,0xf4,0xf8,0xf0,0xe0,0xff,0xff,0x7f,0x3f,0x3f,0x7f,0xff,
0xff,0xfe,0xfe,0xfc,0xf8,0xf0,0xf0,0xf8,0xfc,0xfe,0xfe,0xff,0xff,0x7f,0xbf,0xdf,
0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xdf,0xbf,0x7f,0x3f,0x01,

0x00,0x1f,0xc0,0xff,0x57,0x55,0x55,0xfd,0xf0,0xbf,0xaa,0xaa,0x02,0x00,0xff,0xff, // F
0xff,0x0f,0x00,0xf0,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,
0xfc,0xfb,0xf7,0xef,0x0f,0x07,0x03,0xff,0xff,0x7f,0xbf,0xdf,0xfe,0xfe,0xfd,0xfb,
0xf7,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x03,0x01,0xff,0xff,0x7f,0x3f,

0x00,0xff,0x07,0xff,0xff,0xcf,0xff,0xff,0x53,0x3f,0xaf,0xe8,0xf3,0x17,0xff,0x03, // M
0x00,0x00,0xff,0x53,0x3f,0x00,0x00,0xf0,0x17,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,
0xec,0xdc,0xbc,0x7c,0xfc,0xf8,0xf0,0xe0,0xc0,0xc0,0xe0,0xf0,0xf8,0xfc,0x7c,0xbc,
0xdc,0xec,0xe0,0x7f,0x3f,0x1f,0x01,0x03,0x03,0x01,0x1f,0x3f,0x7f,0xfe,0xfe,0xfc,
0xf8,0xf0,0xf0,0xf8,0xfc,0xfe,0xfe,0x7f,0x3f,0x1f,0x1f,0x3f,0x7f,

0x03,0x00,0x07,0xff,0xff,0xff,0xff,0xbf,0xf4,0xff,0xff,0xff,0xff,0x55,0x15,0xaa, // S
0xaa,0xaa,0xff,0xd7,0xff,0xff,0xff,0xff,0x7f,0x00,0x00,0x00,0x00,0x5c,0x05,0xf0,
0xf8,0xf8,0xf6,0xef,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
0x1f,0x0f,0x7f,0xff,0xff,0x7f,0xbf,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
0xc0,0xc0,0xc0,0x80,0xfb,0xfd,0xfe,0xfe,0xfc,0x80,0xc0,0xe0,0xe0,0xe0,0xe0,0xe0,
0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xdf,0xbf,0x7f,0x7f,0x3f,0x01,

0x00,0x1f,0xff,0x5f,0x55,0xff,0x57,0xd5,0x03,0x00,0xa0,0x2a,0x00,0x00,0x00,0x00, // T
0xff,0x03,0x00,0x00,0x00,0xb0,0x3a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0x0f,0xef,0xf7,0xf0,0xf7,0xef,0x0f,0x07,0xf8,0xfd,0xfd,0xfd,0xf8,0x7f,0x7f,

0x00,0xfc,0x1f,0xf5,0x03,0x00,0x00,0x7f,0xf1,0x2f,0x00,0x00,0xe0,0x3f,0xdf,0x03, // W
0xcf,0x03,0xdf,0xe3,0x7f,0xef,0xec,0xf7,0x2f,0x00,0x00,0x00,0x00,0x00,0x00,0xf8,
0xf0,0xe0,0xe0,0xf0,0xf8,0xff,0xff,0x7f,0x3f,0x3f,0x7f,0xff,0xff,0xfe,0xfe,0xf8,
0xf0,0x80,0x80,0x80,0x80,0xf0,0xf8,0xfe,0xfe,0xdf,0xef,0xf7,0xfb,0x7e,0x3f,0x0f,
0x0f,0x3f,0x7e,0xfb,0xf7,0xef,0xdf,

0x00,0xe3,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x3f,0xff,0x57, // a
0x55,0x55,0xff,0xf3,0x7f,0x55,0x55,0xf5,0x3f,0xa0,0xaa,0xaa,0xaa,0x2a,0x00,0x60,
0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0x60,
0x80,0x80,0x80,0x80,0x60,0xe0,0xe1,0xdd,0xbe,0x7f,0x7f,0x7f,0xff,0xff,0x7f,0xbe,
0xdd,0xdd,0xbe,0x7f,0xff,0xff,

0x00,0xe3,0x03,0x00,0x00,0x00,0x00,0x00,0xf0,0xff,0xff,0xff,0xff,0x3f,0xff,0x57, // e
0x55,0x55,0xff,0xf3,0x7f,0x55,0x55,0xf5,0x02,0xa0,0xaa,0xaa,0xaa,0x2a,0x00,0x80,
0x80,0x60,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,
0xe0,0x60,0x80,0x80,0x7f,0x7f,0x7f,0xbe,0xdd,0xdd,0xbe,0x7f,0xff,0xff,0xff,0xff,
0x7f,0xbe,0xdd,0xc3,0x83,

0x00,0xc0,0x07,0xff,0x03,0x00,0x00,0x00,0xf0,0x7f,0x55,0x55,0x55,0x03,0xff,0xab, // h
0xaa,0xaa,0xff,0xf3,0x3f,0x00,0x00,0xf0,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,
0xfc,0xf8,0xf0,0xe0,0xff,0xff,0x7f,0xbf,0xdf,0x80,0xfe,0xfe,0xfd,0xfb,0xf7,0xf7,
0xfb,0xfd,0xfe,0xfe,0xff,0xff,0x7f,0x3f,0x1f,0x1f,0x3f,0x7f,0xff,0xff,

0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0xaa,0xaa,0xaa,0xaa,0x02,0xff,0xff, // o
0xff,0xff,0xff,0xf3,0xff,0xff,0xff,0xff,0x3f,0x50,0x55,0x55,0x55,0x15,0x00,0xff,
0xff,0xfe,0xfd,0xfb,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0xfb,
0xfd,0xfe,0xff,0xff,0xff,0xff,0x7f,0xbf,0xdf,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,
0xe0,0xe0,0xe0,0xe0,0xdf,0xbf,0x7f,0xff,0xff,

0x00,0xe0,0x03,0x00,0x00,0x00,0x00,0x00,0xf0,0x57,0x55,0x55,0x55,0x03,0xff,0xab, // r
0xaa,0xaa,0x03,0xf0,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
0x80,0x60,0x60,0xff,0xff,0xff,0xfe,0xfd,0x01,0xff,0xff,0x7f,0x3f,0x1f,

0x00,0x03,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x03, // u
0x00,0x00,0xff,0xf3,0xbf,0xaa,0xaa,0xfa,0x3f,0x50,0x55,0x55,0x55,0x15,0x00,0xff,
0xff,0xfe,0xfc,0xf8,0xf8,0xfc,0xfe,0xff,0xff,0xff,0xff,0x7f,0xbf,0xdf,0xdf,0xbf,
0x7f,0xff,0xff,

0x00,0x03,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf5,0xaf, // 0x80
0xaa,0xff,0x05,0x00,0x00,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,
0x0f,0x3f,0x3f,0x3f,0x3f,0x0f,0x0f,

0x00,0x03,0x33,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf5,0xfa, // 0x81
0xfa,0xfa,0x05,0x00,0x00,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,
0x0c,0xcc,0xcc,0xcc,0xcc,0x0c,0x0c,

0x00,0x03,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa5,0xff, // 0x82
0xf5,0xaf,0x05,0x00,0x00,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,
0x33,0xc0,0xc0,0xc0,0xc0,0x33,0x33,

0x00,0x03,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x0a, // 0x83
0x05,0x0a,0x05,0x00,0x00,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x03,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x0a, // 0x84
0x0f,0x0a,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,
0x30,

0x00,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x05, // 0x85
0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0xf0,0xa0,0x00,0x00,0x05,0x00, // 0x86
0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,
0x30,

0x00,0x03,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x50,0xa0,0x00,0x00,0x05,0x00, // 0x87
0x05,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x03,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x5a,0xfa,0x0f,0x00,0x05,0x05, // 0x88
0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,
0xc0,0x30,0x30,0x30,0x30,0xc0,0xc0,

0x00,0x03,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0xaf,0xff,0xaf,0x0f,0x00,0x05,0x05, // 0x89
0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,
0xc0,0xcc,0xcc,0x33,0x33,0xcc,0xcc,0xc0,0xc0,

0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0xfa,0xff,0xff,0x0a,0x00,0x55,0x55, // 0x8a
0x55,0x55,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,
0xf0,0xfc,0xfc,0xff,0xff,0xfc,0xfc,0xf0,0xf0 };
