#include "./starter/png_util/crc.h"
#include "./starter/png_util/lab_png.h"
#include "./starter/png_util/zutil.h"
#include <dirent.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  U64 png_buffer_size = 0; // to hold the data after decompressing
  U32 total_height = 0;
  U32 total_width = 0;
  chunk_p final_IHDR_chunk = malloc(sizeof(struct chunk));
  IHDR_data_p pointer_to_final_ihdr_data;

  int *arr_png_height = malloc((argc - 1) * sizeof(int));
  int *arr_png_width = malloc((argc - 1) * sizeof(int));

  // need to include struct since in the typedef, we
  // created an alias to the pointer of data_IHDR

  unsigned const char magic_bytes[] = {0x89, 0x50, 0x4E, 0x47,
                                       0x0D, 0x0A, 0x1A, 0x0A};
  //"Magic bytes for the PNG file format"

  get_png_data_IHDR(final_IHDR_chunk, pointer_to_final_ihdr_data, argv[1], 8, SEEK_SET);
  pointer_to_final_ihdr_data = final_IHDR_chunk->data;

  for (int i = 1; i < argc; i++)
  {
    chunk_p ihdr_chunk_p_temp = malloc(sizeof(struct chunk));
    IHDR_data_p ihdr_data_temp;

    get_png_data_IHDR(ihdr_chunk_p_temp, ihdr_data_temp, argv[i], 8, SEEK_SET);


    int height_temp = 0;
    int width_temp = 0;

    ihdr_data_temp = ihdr_chunk_p_temp->data;

    height_temp = ntohl(ihdr_data_temp->height);
    width_temp = ntohl(ihdr_data_temp->width);

    // uncompressed data size is HEIGHT*(WIDTH*4+1) bytes
    total_height += height_temp;
    total_width = width_temp;
    arr_png_height[i - 1] = height_temp;
    arr_png_width[i - 1] = width_temp;

    free(ihdr_data_temp);
    free(ihdr_chunk_p_temp);
  }

  pointer_to_final_ihdr_data->height = total_height;
  pointer_to_final_ihdr_data->width = total_width;

  // printf("total height is: %d\n", total_height);
  // printf("total width is: %d\n", total_width);

  // for (int i = 0; i < (argc - 1); i++) {
  //   printf("height:%d  ", arr_png_height[i]);
  //   printf("\n");
  // }

  // for (int i = 0; i < (argc - 1); i++) {
  //   printf("width:%d  ", arr_png_width[i]);
  //   printf("\n");
  // }

  png_buffer_size += total_height * (total_width * 4 + 1);

  U64 destination_length_total = 0;
  U64 destination_length_temp = 0;


  // IDAT
  /////////////////////////

  // data buffer is the buffer to hold the concatenated inflated data from each
  // png, thus total height
  int data_buffer_size = total_height * (total_width * 4 + 1);
  U8 *data_buffer = malloc(data_buffer_size);
  int data_buffer_index = 0;      // for concatenating inflated buffer to data buffer
  U64 deflated_buffer_length = 0; // add up the chunk length

  for (int i = 1; i < argc; i++)
  {
    int height_temp2 = arr_png_height[i - 1];
    int width_temp2 = arr_png_width[i - 1];

    U64 inflated_buffer_length = height_temp2 * (width_temp2 * 4 + 1);
    U8 *buffer_inf = malloc(inflated_buffer_length);
    chunk_p idat_p_temp = malloc(sizeof(struct chunk));

    get_png_data_IDAT(idat_p_temp, argv[i], 33, SEEK_SET);

    if (mem_inf(buffer_inf, &inflated_buffer_length, idat_p_temp->data,
                idat_p_temp->chunk_length) != 0)
    {
      printf("fail");
    };

    for (int i = 0; i < inflated_buffer_length; i++)
    {
      data_buffer[data_buffer_index] = buffer_inf[i];
      data_buffer_index++;
    }

    deflated_buffer_length += idat_p_temp->chunk_length;

    free(idat_p_temp->data);
    free(idat_p_temp);
    free(buffer_inf);
  }



  U8 *buffer_def = malloc(deflated_buffer_length);
  mem_def(buffer_def, &deflated_buffer_length, data_buffer, data_buffer_size,
          Z_DEFAULT_COMPRESSION);

 
  // Create final IDAT chunk
  //////////////////////////////////////////
  chunk_p idat_final = malloc(sizeof(struct chunk)); // idat for all.png
  idat_final->chunk_length = deflated_buffer_length;
  idat_final->chunk_type[0] = 0x49;
  idat_final->chunk_type[1] = 0x44;
  idat_final->chunk_type[2] = 0x41;
  idat_final->chunk_type[3] = 0x54; // signature for IDAT chunk type



  idat_final->data = buffer_def;
  idat_final->CRC = get_CRC_from_chunk(idat_final);
  idat_final->CRC = htonl(idat_final->CRC);
  idat_final->chunk_length = htonl(idat_final->chunk_length);


  ///////////////////////////////////////////////////////////////////

  // Create final IEND chunk
  ///////////////////////////////////////////////////////////////////
  struct chunk *iend_final = malloc(sizeof(struct chunk));
  iend_final->chunk_length = 0;
  iend_final->data =
      NULL; // IEND chunk has no data so length is 0, data points to null
  iend_final->chunk_type[0] = 0x49;
  iend_final->chunk_type[1] = 0x45;
  iend_final->chunk_type[2] = 0x4E;
  iend_final->chunk_type[3] = 0x44;
  iend_final->CRC = 0x826042ae; // the CRC is the same for all IEND

  ///////////////////////////////////////////////////////
  // Create the all.png file
  FILE *file_p = fopen("./all.png", "wb+");
  if (file_p == NULL)
  {
    printf("fail");
  }
  // Write the magic bytes
  fwrite(magic_bytes, sizeof(unsigned char), sizeof(magic_bytes), file_p);



  // Write the ihdr_data_final part
  //////////////////////////////////
  pointer_to_final_ihdr_data->height = htonl(total_height);
  pointer_to_final_ihdr_data->width = htonl(total_width);
  final_IHDR_chunk->CRC = get_CRC_from_chunk(final_IHDR_chunk);
  final_IHDR_chunk->CRC = htonl(final_IHDR_chunk->CRC);
  final_IHDR_chunk->chunk_length = htonl(final_IHDR_chunk->chunk_length);

  fwrite(&(final_IHDR_chunk->chunk_length), sizeof(U32), 1, file_p);
  fwrite(&(final_IHDR_chunk->chunk_type), sizeof(U32), 1, file_p);
  fwrite((final_IHDR_chunk->data), 13 * sizeof(U8), 1, file_p);
  fwrite(&(final_IHDR_chunk->CRC), sizeof(U32), 1, file_p);
  /////////////////////////////////////////////////////////////////

  // Write to the IDAT part
  ///////////////////////////////////////////

  fwrite(&(idat_final->chunk_length), sizeof(U32), 1, file_p);
  fwrite(&(idat_final->chunk_type), sizeof(U32), 1, file_p);
  fwrite((idat_final->data), ntohl(idat_final->chunk_length) * sizeof(U8), 1,
         file_p);
  fwrite(&(idat_final->CRC), sizeof(U32), 1, file_p);

  //////////////////////////////////////////

  // Write to the IEND part
  ////////////////////////////
  fwrite(&(iend_final->chunk_length), sizeof(U32), 1, file_p);
  fwrite(&(iend_final->chunk_type), sizeof(U32), 1, file_p);
  fwrite(&(iend_final->CRC), sizeof(U32), 1, file_p);

  //////////////////////////////////

  free(data_buffer);
  free(idat_final);
  free(iend_final);
  free(buffer_def);
  free(pointer_to_final_ihdr_data);
  free(final_IHDR_chunk);
  free(arr_png_height);
  free(arr_png_width);

  fclose(file_p);

  return 0;
}
