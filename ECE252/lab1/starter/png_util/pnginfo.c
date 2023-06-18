/**
 * @file: ls_fname.c
 * @brief: simple ls command to list file names of a directory
 */

#include "crc.h"
#include "lab_png.h"
#include <dirent.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>  /* for printf().  man 3 printf */
#include <stdlib.h> /* for exit().    man 3 exit   */
#include <string.h> /* for strcat().  man strcat   */
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/// a.chunk_p_arg /home/a68xu/ECE252/G_33/lab1/starter/png_util/WEEF_1.png 8

unsigned const char magic_bytes[] = {
    0x89, 0x50, 0x4E, 0x47,
    0x0D, 0x0A, 0x1A, 0x0A}; //"Magic bytes for the PNG file format"
unsigned char buffer[8];

// int main(int argc, char *argv[]) {
//   if (argc != 2 && argc != 3) {
//     printf("Provide a absolute or relative path to a .png file");
//     return 1;
//   }

//   const char *filePath =
//       argv[1]; // file path is the second argument in the argument list

//   if (argc == 2) {
//     if (is_png(filePath) == 1) {
//       printf("The file is a png file\n");
//     } else {
//       printf("Not a PNG");
//     }
//   }

//   if (argc == 3) {
//     long offset = atol(argv[2]);
//     chunk_p ihdr_p = malloc(sizeof(struct chunk));
//     chunk_p idat_p = malloc(sizeof(struct chunk));
//     get_png_data_IHDR(ihdr_p, filePath, 8, SEEK_SET);
//     get_png_data_IDAT(idat_p, filePath, 33, SEEK_SET);

//     printf("%x actual crc\n", get_CRC_from_chunk(ihdr_p));
//     printf("%x actual crc\n", get_CRC_from_chunk(idat_p));
//   }

//   // get_png_data_IDAT(IDAT, filePath, 33, SEEK_SET);

//   return 0;
// }

int is_png(const char *file_path)
{ // return 1 if is png

  // Open the file for reading
  FILE *file_p = fopen(file_path, "r");
  if (file_p == NULL)
  {
    printf("Failed to open the file.\n");
    return -1; // Exit the program with an error status
  }
  else
  {
    // printf("success");
  }

  // set file position of a stream to a specified position, here it is begining
  // of the file
  if (fseek(file_p, 0, SEEK_SET) !=
      0)
  { // off is the offset in bytes, whence is the position from where
    // offset is added, specified by constants
    printf("Error seeking to the beginning of the file.\n");
    fclose(file_p);
    return -1;
  }

  // use a pointer to a buffer, which is a block of memory that has is least
  // size*nmemb big size is the size of each element that should be read nmemb
  // is the number of elements that should be read fread return the total number
  // of elements read from the file as a size_t object
  if (fread(buffer, sizeof(unsigned char), 8, file_p) != 8)
  {
    printf("Error reading the file.\n");
    fclose(file_p);
    return -1;
  }

  // compare the two blocks of data, n is the number of bytes to be compared
  // if return value is zero then that means the two memory blocks are identical
  if (memcmp(buffer, magic_bytes, 8) != 0)
  {
    // printf("Magic bytes do not match\n");
    
    fclose(file_p);
    return 0;
  }
  else
  {
    fclose(file_p);
    return 1; // is png
  }
  fclose(file_p);
  return 0;
}

// whence is from where the offset should be applied
int get_png_data_IHDR(chunk_p chunk_p_arg, struct IHDR_data *ihdr_data_p_arg, const char *file_path, long offset, int whence)
{
  FILE *file_p = fopen(file_path, "r");
  if (file_p == NULL)
  {
    printf("Failed to open the file.\n");
    return -1; // Exit the program with an error status
  }
  if (fseek(file_p, offset, whence) != 0)
  {
    printf("Error seeking to the IHDR part of the file.\n");
    fclose(file_p);
    return -1;
  }

  if (fread(&chunk_p_arg->chunk_length, sizeof(U32), 1, file_p) != 1)
  {
    printf("Error reading the IHDR chunk 1.\n");
    fclose(file_p);
    return -1;
  }
  chunk_p_arg->chunk_length = ntohl(chunk_p_arg->chunk_length);

  fread(&(chunk_p_arg->chunk_type[0]), 1, 1, file_p);
  fread(&(chunk_p_arg->chunk_type[1]), 1, 1, file_p);
  fread(&(chunk_p_arg->chunk_type[2]), 1, 1, file_p);
  fread(&(chunk_p_arg->chunk_type[3]), 1, 1, file_p);

  chunk_p_arg->data = malloc(chunk_p_arg->chunk_length * sizeof(U8));

  if (fread(chunk_p_arg->data, 13, 1, file_p) != 1)
  {
    printf("Error reading the IHDR chunk 1.\n");
    fclose(file_p);
    return -1;
  }
  fread(&(chunk_p_arg->CRC), 4, 1, file_p);
  chunk_p_arg->CRC = ntohl(chunk_p_arg->CRC);

  ihdr_data_p_arg = chunk_p_arg->data;

  fclose(file_p);

  return 0;
}

// whence is from where the offset should be applied, WHENCE = SEEKGET for
// starting from begining of file
int get_png_data_IDAT(chunk_p chunk_p_arg, const char *file_path, long offset, int whence)
{
  // 33 for offset for IDAT
  // Open the file for reading
  FILE *file_p = fopen(file_path, "rb");
  if (file_p == NULL)
  {
    printf("Failed to open the file.\n");
    return -1; // Exit the program with an error status
  }
  // off is the offset in bytes, whence is the position from where
  // offset is added, specified by constants
  if (fseek(file_p, offset, whence) != 0)
  {
    printf("Error seeking to the IDAT part of the file.\n");
    fclose(file_p);
    return -1;
  }

  if (fread(&chunk_p_arg->chunk_length, sizeof(U32), 1, file_p) != 1)
  { // one means we are reading 1 byte each time
    printf("Error reading the IDAT chunk length.\n");
    fclose(file_p);
    // free the chunk_p_arg pointer?
    return -1;
  }

  chunk_p_arg->chunk_length = ntohl(chunk_p_arg->chunk_length);

  chunk_p_arg->data = malloc(chunk_p_arg->chunk_length * sizeof(U8));

  if (fread(&chunk_p_arg->chunk_type, sizeof(U32), 1, file_p) != 1)
  {
    printf("Error reading the IDAT chunk type.\n");
    fclose(file_p);
    // free the chunk_p_arg pointer?
    return -1;
  }
  // chunk_p_arg->chunk_type = ntohl(chunk_p_arg->chunk_type);
  //  convertToLittleEndian(&chunk_p_arg->CRC);

  if (fread(chunk_p_arg->data, chunk_p_arg->chunk_length, 1, file_p) != 1)
  {
    printf("Error reading the IDAT chunk data.\n");
    fclose(file_p);
    // free the chunk_p_arg pointer?
    return -1;
  }

  if (fread(&chunk_p_arg->CRC, sizeof(U32), 1, file_p) != 1)
  {
    printf("Error reading the IDAT chunk CRC.\n");
    fclose(file_p);
    // free the chunk_p_arg pointer?
    return -1;
  }
  chunk_p_arg->CRC = ntohl(chunk_p_arg->CRC);

  fclose(file_p);

  return 0;
}

int get_png_data_IEND(chunk_p chunk_p_arg, const char *file_path, long offset, int whence)
{
  FILE *file_p = fopen(file_path, "rb");
  if (file_p == NULL)
  {
    printf("Failed to open the file.\n");
    return -1; // Exit the program with an error status
  }
  // off is the offset in bytes, whence is the position from where
  // offset is added, specified by constants
  if (fseek(file_p, offset, whence) != 0)
  {
    printf("Error seeking to the IDAT part of the file.\n");
    fclose(file_p);
    return -1;
  }

  if (fread(&chunk_p_arg->chunk_length, sizeof(U32), 1, file_p) != 1)
  { // one means we are reading 1 byte each time
    printf("Error reading the IDAT chunk length.\n");
    fclose(file_p);
    // free the chunk_p_arg pointer?
    return -1;
  }

  chunk_p_arg->chunk_length = ntohl(chunk_p_arg->chunk_length);
  // printf("%d chunk_length\n", chunk_p_arg->chunk_length);

  if (fread(&chunk_p_arg->chunk_type, sizeof(U32), 1, file_p) != 1)
  {
    printf("Error reading the IDAT chunk type.\n");
    fclose(file_p);
    return -1;
  }

  if (fread(&chunk_p_arg->CRC, sizeof(U32), 1, file_p) != 1)
  {
    printf("Error reading the IDAT chunk CRC.\n");
    fclose(file_p);
    // free the chunk_p_arg pointer?
    return -1;
  }
  chunk_p_arg->CRC = ntohl(chunk_p_arg->CRC);

  fclose(file_p);

  return 0;
}

void convertToLittleEndian(U32 *value)
{
  *value = ((*value >> 24) & 0xFF) | ((*value >> 8) & 0xFF00) |
           ((*value << 8) & 0xFF0000) | ((*value << 24) & 0xFF000000);
}

U32 get_CRC_from_chunk(chunk_p chunk_arg)
{

  U8 *chunk_data = chunk_arg->data;

  int chunk_length = (chunk_arg->chunk_length + 4); // add 4 because the type is also included in the CRC calculation
  U8 *chunk_data_with_type = malloc(chunk_length * sizeof(U8));

  // Copy chunk_type to chunk_data_with_type
  for (int i = 0; i < 4; i++)
  {
    chunk_data_with_type[i] = chunk_arg->chunk_type[i];
  }
  // Copy starting from the position after chunk_type which is U32
  for (int i = 4; i < 4 + chunk_arg->chunk_length; i++)
  {
    chunk_data_with_type[i] = chunk_arg->data[i - 4];
  }
  U32 crc_val = crc(chunk_data_with_type, chunk_length);
  // printf("CRC value is: %x \n", crc_val);

  free(chunk_data_with_type);

  return crc_val; // the returning crc_val is in host order, little endian
}