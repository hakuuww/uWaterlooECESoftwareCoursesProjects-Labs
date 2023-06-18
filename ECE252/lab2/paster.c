#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <curl/curl.h>
#include "zutil.h"
#include "crc.h"
#include "helper.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <getopt.h>

int write_file(int sequence, const void *data_copy, size_t length, int *count);
void *get_files_thread(void *arg);

// suppose to hold the fetched img segments in memory and in order from 1-50
char *final_file[50];
int final_file_size[50];
pthread_mutex_t mutex[50];


// an overall fetch function also an input to thread
void *get_files_thread(void *arg)
{
    struct thread_object *cast_p = (struct thread_object*)arg;
    CURL *curl_handle;
    CURLcode res;
    RECV_BUF recv_buf;

///////////////////////////////////////
//Only need to set the same curl option for requesting the same url
    curl_handle = curl_easy_init();

    if (curl_handle == NULL)
    {
        fprintf(stderr, "curl_easy_init: returned NULL\n");
    }

    //printf("Thread count:%d \n",cast_p->thread_count);


    // printf("URL cast_p->url value after:%s \n",cast_p->url);
    // printf("URL adress cast_p->url inside:%p \n", (void*)cast_p->url);
    // printf("png_count address: %p\n",(void*)cast_p->png_count);
    // printf("png_count value: %d\n",*cast_p->png_count);


    /* specify URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, cast_p->url);

    /* register write call back function to process received data */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_cb_curl3);
    /* user defined data structure passed to the call back function */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&recv_buf);

    /* register header call back function to process received header data */
    curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION, header_cb_curl);
    /* user defined data structure passed to the call back function */
    curl_easy_setopt(curl_handle, CURLOPT_HEADERDATA, (void *)&recv_buf);

    /* some servers requires a user-agent field */
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
///////////////////////////////////////////

    while (*(cast_p->png_count) < 50)
    {
        recv_buf_init(&recv_buf, BUF_SIZE);

        /* init a curl session */

        /* get it! */
        res = curl_easy_perform(curl_handle);


        if (res != CURLE_OK)
        {
            // fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            // printf("Thread count:%d \n",cast_p->thread_count);
            // printf("URL cast_p->url value after:    %s \n",cast_p->url);
        }else{
            // update the thread struct arguments
            write_file(recv_buf.seq, recv_buf.buf, recv_buf.size, cast_p->png_count);

            /* cleaning up */
        }

        recv_buf_cleanup(&recv_buf);




        // printf("png_count address: %p\n",(void*)cast_p->png_count);
        // printf("png_count value: %d\n",*cast_p->png_count);
    }

    curl_easy_cleanup(curl_handle);

    //     printf("png_count address: %p\n",(void*)cast_p->png_count);
    // printf("png_count value: %d\n",*cast_p->png_count);

    return NULL;
}

int write_file(int sequence, const void *data_copy, size_t length, int *count)
{
    // if the data is empty
    if (data_copy == NULL)
    {
        fprintf(stderr, "write_file: input data is null!\n");
        return -1;
    }

    // check if the img seq is already being fetched
    if (final_file[sequence] != NULL)
    {
        return -1;
    }

    pthread_mutex_lock(&mutex[sequence]);
    // save the copy of png segment in memory
    final_file[sequence] = malloc(length);
    final_file_size[sequence] = length;
    memcpy(final_file[sequence], data_copy, length);
    //no lock not safe
    // update the counter until all 50 pngs are fetched
    *count = *count + 1;
    pthread_mutex_unlock(&mutex[sequence]);

    return 0;
}

int main(int argc, char **argv)
{
    int c;
    int t = 1;
    int n = 1;
    char *str = "option requires an argument";

    while ((c = getopt(argc, argv, "t:n:")) != -1)
    {
        switch (c)
        {
        case 't':
            t = strtoul(optarg, NULL, 10);
            printf("option -t specifies a value of %d.\n", t);
            if (t <= 0)
            {
                fprintf(stderr, "%s: %s > 0 -- 't'\n", argv[0], str);
                return -1;
            }
            break;
        case 'n':
            n = strtoul(optarg, NULL, 10);
            printf("option -n specifies a value of %d.\n", n);
            if (n <= 0 || n > 3)
            {
                fprintf(stderr, "%s: %s 1, 2, or 3 -- 'n'\n", argv[0], str);
                return -1;
            }
            break;
        default:
            return -1;
        }
    }



    // initialize the 50 size array of png segments
    for (int i = 0; i < 50; i++)
    {
        final_file[i] = NULL;
        final_file_size[i] = 0;
    }

    // initialize n threads
    pthread_t *threads = malloc(sizeof(pthread_t) * t);

        //initialize t thread_objects
    struct thread_object*  thread_recorder = malloc(sizeof(struct thread_object)*t);
    


for(int i=0 ;i<50;i++){
    pthread_mutex_init(&(mutex[i]),NULL);
}
    // inirialize the argument feed into function of thread
    int *count = malloc(sizeof(int));
    *count = 0;


    curl_global_init(CURL_GLOBAL_DEFAULT);

    // distribute the work to n threads with 3 servers
    for (int i = 0; i < t; i++)
    {
        // hold the url for each thread
        char* url_thread = malloc(1000);
        thread_recorder[i].png_count = count;
        thread_recorder[i].thread_count = i;
        sprintf(url_thread, "http://ece252-%d.uwaterloo.ca:2520/image?img=%d", i % 3 + 1, n);
        thread_recorder[i].url = url_thread;

        int create_result = pthread_create(&threads[i], NULL, get_files_thread, (void*)&thread_recorder[i]);

        if (create_result != 0) {
            printf("pthread_create failed with error code: %d\n", create_result);
            printf("Error message: %s\n", strerror(create_result));
            threads[i] = -1;

        }
    }

    // finish fetching and join threads
    for (int i = 0; i < t; i++)
    {
        if(threads[i] != -1){
        pthread_join(threads[i], NULL);
        printf("Thread number %lu have joined.\n", threads[i]);
        }
        free(thread_recorder[i].url);
    }

for(int i=0 ;i<50;i++){
    pthread_mutex_destroy(&(mutex[i]));
}


    free(count);
    free(threads);
    free(thread_recorder);
    curl_global_cleanup();

    // concat process begin, concate img segment in final_file one by one in order

    // get the png width for calculation
    int final_width_png;
    memcpy(&final_width_png, final_file[0] + 16, 4);
    final_width_png = ntohl(final_width_png);

    // get the png height for calculation
    int final_height_png = 0;
    for (int i = 0; i < 50; i++)
    {
        int image_height_segment;

        memcpy(&image_height_segment, final_file[i] + 20, 4);

        final_height_png = final_height_png + ntohl(image_height_segment);
    }

    // set up the buffer for meminf and memdef
    U8 idat_data_buff[(final_width_png * 4 + 1) * final_height_png];
    U64 total_data_length = 0;

    U8 compressed_data_buff[(final_width_png * 4 + 1) * final_height_png];
    U64 total_compressed_length = 0;

    // meminf the idat data
    for (int i = 0; i < 50; i++)
    {
        U64 idat_length;

        // Seek to each position and read idat data length

        memcpy(&idat_length, final_file[i] + 33, 4);
        idat_length = ntohl(idat_length);

        // Load data from IDAT into idat buffer
        U8 idat_buff[idat_length];

        memcpy(&idat_buff, final_file[i] + 41, idat_length);

        U64 out_length = 0;
        int mem_inf_ret = 0;

        // meminf for idat data
        mem_inf_ret = mem_inf(&(idat_data_buff[total_data_length]), &out_length, idat_buff, idat_length);

        if (mem_inf_ret != 0)
        {
            fprintf(stderr, "mem_inf failed. ret = %d.\n", mem_inf_ret);
        }

        // Update total length of PNG
        total_data_length += out_length;
    }

    // data compression of IDAT for insertion into new PNG
    int mem_def_ret = 0;

    mem_def_ret = mem_def(compressed_data_buff, &total_compressed_length, idat_data_buff, total_data_length, Z_DEFAULT_COMPRESSION);

    if (mem_def_ret != 0)
    {
        fprintf(stderr, "mem_inf failed. ret = %d.\n", mem_def_ret);
    }
    // convert back height after calculation
    final_height_png = htonl(final_height_png);
    U64 total_compressed_length_out = htonl(total_compressed_length);

    // output HEADER is constant
    unsigned char header[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    unsigned char ihdr_buffer[25];

    memcpy(&ihdr_buffer, final_file[0] + 8, 25);

    // Set constant chunk components for output
    unsigned char iend_type[4] = {'I', 'E', 'N', 'D'};
    unsigned char idat_type[4] = {'I', 'D', 'A', 'T'};
    unsigned char ihdr_crc_in[17];
    unsigned char idat_crc_in[total_compressed_length + 4];
    int ihdr_crc_out;
    int idat_crc_out;
    int iend_crc_out;
    int iend_length_constant = 0;

    // new png
    FILE *all_png = fopen("all.png", "wb+");

    // Write Header and IHDR
    fwrite(header, 8, 1, all_png);
    fwrite(ihdr_buffer, 25, 1, all_png);

    fseek(all_png, 20, SEEK_SET);
    fwrite(&final_height_png, 4, 1, all_png);

    fseek(all_png, 12, SEEK_SET);
    fread(ihdr_crc_in, 17, 1, all_png);

    // CRC calculation on type and data of IHDR
    ihdr_crc_out = htonl(crc(ihdr_crc_in, 17));
    fwrite(&ihdr_crc_out, 4, 1, all_png);

    // write the IDAT body
    fwrite(&total_compressed_length_out, 4, 1, all_png);
    fwrite(idat_type, 4, 1, all_png);
    fwrite(compressed_data_buff, total_compressed_length, 1, all_png);

    // CRC calculation on type and data of IDAT
    fseek(all_png, 37, SEEK_SET);
    fread(idat_crc_in, total_compressed_length + 4, 1, all_png);

    idat_crc_out = htonl(crc(idat_crc_in, total_compressed_length + 4));
    fwrite(&idat_crc_out, 4, 1, all_png);

    // write the IEND
    fwrite(&iend_length_constant, 4, 1, all_png);
    fwrite(iend_type, 4, 1, all_png);

    // CRC calculation on IEND
    iend_crc_out = htonl(crc(iend_type, 4));
    fwrite(&iend_crc_out, 4, 1, all_png);

    fclose(all_png);

    for (int j = 0; j < 50; j++)
    {
        free(final_file[j]);
    }

    return 0;
}
