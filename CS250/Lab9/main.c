#include <stdio.h>
//#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define READABLE_FILE "file_to_read.txt" /* File to be read during read operations */
#define BYTES_TO_READ_WRITE 819200 /* 800 KB */
#define MAX_BUFFER  1048576 /* 1 MB*/

/* Function for write without buffer */
void mywritec(char);

/* Functions for write with buffer */
void mywritebufsetup(int);
void myputc(char);
void mywriteflush(void);

/* Function for read without buffer */
int myreadc(void);

/* Functions for read with buffer */
void myreadbufsetup(int);
int mygetc(void);

/* Declare global variables for write operations here */
int fd_write = 1;
int write_buf_size;
int write_pos;
char write_buffer[MAX_BUFFER];
char * write_pointer;

/* Declare global variables for read operations here */
int fd_read;
int read_buf_size;
int read_count;
int read_buffer[MAX_BUFFER];
int * read_pointer;

/* Main function starts */
int main()
{
    clock_t begin, end;
    int option, n, temp;
    const char *a="Writing byte by byte\n";
    const char *b="Writing using buffers\n";
    unsigned long i, bytes_to_write = BYTES_TO_READ_WRITE, bytes_to_read = BYTES_TO_READ_WRITE;
    char ch;

    while(1)
    {
        printf("\n 1 - Write without buffering \n 2 - Write with buffering");
        printf("\n 3 - Read without buffering \n 4 - Read with buffering");
        printf(("\n 5 - Exit \n Enter the option: "));
        scanf("%d", &option);
        switch(option)
        {
            case 1: /* Write without buffer */
                begin = clock();
                for (i=0;i<bytes_to_write;i++)
                {
                    ch = a[i%strlen(a)];
                    mywritec(ch);
                }
                end = clock();
                printf("\n Time to write without buffering: %f secs\n",(double)(end - begin)/CLOCKS_PER_SEC);
                break;

            case 2:  /* Write with buffer */
                printf("\n Enter the buffer size in bytes: ");
                scanf("%d", &n);
                mywritebufsetup(n);
                begin = clock();
                for (i=0;i<bytes_to_write;i++)
                {
                    ch = b[i%strlen(b)];
                    myputc(ch);
                }
                mywriteflush();
                end = clock();
                printf("\n Time to write with buffering: %f secs\n",(double)(end - begin)/CLOCKS_PER_SEC);
                break;

            case 3:  /* Read without buffer */
                fd_read = open(READABLE_FILE, O_RDONLY);
                if(fd_read < 0)
                {
                    printf("\n Error opening the readable file \n");
                    return 1;
                }
                begin = clock();
                for (i=0;i<bytes_to_read;i++)
                {  /* you may need to modify this slightly to print the character received and also check for end of file */
                    if(myreadc() == -1)
                    {
                        printf("\n End of file \n");
                        break;
                    }
                }
                end = clock();
                if(close(fd_read))
                {
                    printf("\n Error while closing the file \n ");
                }
                printf("\n Time to read without buffering: %f secs\n",(double)(end - begin)/CLOCKS_PER_SEC);
                break;

            case 4:  /* Read with buffer */
                printf("\n Enter the buffer size in bytes: ");
                scanf("%d", &n);
                myreadbufsetup(n);
                fd_read = open(READABLE_FILE, O_RDONLY);
                if(fd_read < 0)
                {
                    printf("\n Error opening the readable file \n");
                    return 1;
                }
                begin = clock();
                for (i=0;i<bytes_to_read;i++)
                { /* you may need to modify this slightly to print the character received and also check for end of file */
                    if(mygetc() == -1)
                    {
                        printf("\n End of file \n");
                        break;
                    }
                }
                end = clock();
                if(close(fd_read))
                {
                    printf("\n Error while closing the file \n ");
                }
                printf("\n Time to read with buffering: %f secs\n",(double)(end - begin)/CLOCKS_PER_SEC);
                break;

            default:
                return 0;
        }
    }
}


void mywritec(char ch)

{

    /* Use the system call write() to write char 'ch' to standard output (file descriptor 1) */

    write(fd_write, &ch, sizeof(char));

}


void mywritebufsetup(int n)

{

    /* Verify that n is a positive integer less than or equal to MAX_BUFFER, and */

    /* store n in global variable write_buf_size. */

    /* Initialize wp to point to the first byte of buffer. */

    if (n >= 0 && n <= MAX_BUFFER) {

        write_buf_size = n;
        write_pos = 0;
        write_pointer = &write_buffer[0];

    }

}

void myputc(char ch)

{

    /* Place character ch in the location given by wp, and increment wp. */

    /* If the buffer is full (contains write_buf_size characters), write the entire buffer */

    /* to standard output using the write() system call and reset wp to the first location */

    /* of the buffer. Note that myputc() will be called multiple times before the buffer */

    /* is completely written out. */

    *write_pointer = ch;
    write_pointer++;

    if (++write_pos == write_buf_size) {

        write(fd_write, write_buffer, sizeof(char) * write_buf_size);
        write_pos = 0;
        write_pointer = &write_buffer[0];

    }

}

void mywriteflush(void)

{

    /* Note: this function will be called after all calls to myputc() have been made */

    /* if any characters remain in the write buffer, write them to standard output */

    write(fd_write, write_buffer, sizeof(char) * write_pos);

}




int myreadc(void)

{

    /* Use read() system call to read a character from text file(file descriptor is 'fd_read') */

    /* if read() indicates end-of-file, return -1 to the caller. Otherwise, return the */

    /* character that was read in the low-order byte of the integer (be careful to avoid 8? */

    /* sign extension). */

    int tempReadBuff[1];
    int temp;

    read(fd_read, tempReadBuff, 1);

    if (tempReadBuff[0] == 0xFFFFFFFF)
        return -1;

    else {

        temp = tempReadBuff[0];

        if (temp > 0)
            temp += 2 * temp;

        return temp;

    }

}


/* Declare a global array of MAX_BUFFER characters named "read_buf" that will */

/* serve as an input buffer. */

/* Declare a global character pointer, rp, that will point to a location in the buffer. */

/* Declare a global integer, read_buf_size, that stores the size of the input buffer */

/* being used at the current time. */

/* Declare a global integer, read_count, that tells how many bytes were read. */

void myreadbufsetup(int n)

{

    /* Verify that n is a positive integer less than or equal to MAX_BUFFER, */

    /* and store n in global variable read_buf_size. */

    /* Set read_count to zero. */

    if (n >= 0 && n <= MAX_BUFFER) {

        read_buf_size = n;
        read_count = 0;
        read_pointer = &read_buffer[0];

    }

}

int mygetc()

{

    /* If read_count is less than or equal to zero, call read() to read up to */

    /* read_buf_size bytes into read_buf from text file (file descriptor is 'fd_read'), */

    /* and set read_count to the number of bytes actually read. Set rp to the */

    /* first location in the buffer. If the read_count is zero (the read call returned */

    /* end-of-file), return -1 to the caller to indicate end-of-file. Extract the next */

    /* character from the buffer, increment rp, and decrement read_count. */

    /* Return the character extracted from the buffer in the low-order byte of an */

    /* integer (be careful to avoid sign extension). */

    /* Note that this function will be called multiple times before the buffer is emptied. */

    int temp;

    if (read_count <= 0) {

        while (read_count < read_buf_size) {

            temp = read(fd_read, read_buffer, read_buf_size);
            read_count += temp;

            read_pointer = &read_buffer[0];

            if (temp == 0)
                return -1;

        }

    }

    temp = *read_pointer;
    read_pointer++;
    read_count--;

    return temp;

}
