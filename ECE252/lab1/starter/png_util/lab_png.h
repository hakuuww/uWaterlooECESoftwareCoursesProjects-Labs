/**
 * @brief  micros and structures for a simple PNG file
 *
 * Copyright 2018-2020 Yiqing Huang
 *
 * This software may be freely redistributed under the terms of MIT License
 */
#pragma once

/******************************************************************************
 * INCLUDE HEADER FILES
 *****************************************************************************/
#include <stdio.h>

/******************************************************************************
 * DEFINED MACROS
 *****************************************************************************/

#define PNG_SIG_SIZE 8    /* number of bytes of png image signature data */
#define CHUNK_LEN_SIZE 4  /* chunk length field size in bytes */
#define CHUNK_TYPE_SIZE 4 /* chunk type field size in bytes */
#define CHUNK_CRC_SIZE 4  /* chunk CRC field size in bytes */
#define DATA_IHDR_SIZE 13 /* IHDR chunk data field size */

/******************************************************************************
 * STRUCTURES and TYPEDEFS
 *****************************************************************************/
typedef unsigned char U8;
typedef unsigned int U32;

typedef struct IHDR_data { // IHDR chunk data
  U32 width;               /* 4 bytes, width in pixels, big endian   */
  U32 height;              /* 4 bytes height in pixels, big endian  */
  U8 bit_depth;            /* num of bits per sample or per palette index.
                              valid values are: 1, 2, 4, 8, 16 */
  U8 color_type;           /* =0: Grayscale; =2: Truecolor; =3 Indexed-color                            =4: Greyscale with alpha; =6: Truecolor with alpha */
  U8 compression;          /* only method 0 is defined for now */
  U8 filter;               /* only method 0 is defined for now */
  U8 interlace;            /* =0: no interlace; =1: Adam7 interlace */
} *IHDR_data_p;


/* A simple PNG file format, three chunks only*/
typedef struct simple_PNG {
  struct chunk *p_IHDR;
  struct chunk *p_IDAT; /* only handles one IDAT chunk */
  struct chunk *p_IEND;
} *simple_PNG_p;

typedef struct chunk { // IHDR chunk data
  U32 chunk_length;
  U8  chunk_type[4]; /* chunk type */
  U8 *data;
  U32 CRC;
} *chunk_p;

/******************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************/
int is_png(const char *file_path);
int get_png_height(chunk_p *buf);
int get_png_width(chunk_p *buf);
int get_png_data_IHDR(chunk_p chunk_p_arg, struct IHDR_data* ihdr_data_p_arg, const char *file_path, long offset, int whence);
void convertToLittleEndian(U32 *value);
int get_png_data_IDAT(chunk_p chunk_p_arg, const char *file_path, long offset, int whence);
U32 get_CRC_from_chunk( chunk_p chunk_arg);
/* declare your own functions prototypes here */
