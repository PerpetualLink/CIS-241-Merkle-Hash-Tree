/*
 * Simple MD5 implementation
 *
 * Compile with: gcc -o md5 -O3 -lm md5.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// These vars will contain the hash
uint8_t * concat(const char *s1, const uint8_t *s2);
char * treeHash(char **inputHash,int size);
char * readEntireFile(char *);
int lineByline(char *, char *[]);
void md52(uint8_t*,size_t,int);
void md5(uint8_t*,size_t);

int main() {

    /** Variable to hold all the paths to files to be checked **/
    char * msg[10000];

    // Variable to get the number or paths being read
    int size2 = 0;
    // Scan the file of path names line by line and populate the size
    size2 = lineByline("Paths.txt", msg);

    // Variable for the content within the files that were just scanned
    char * fileContent[size2];
    //Loop through and read the entire file
    for(int i = 0; i <= size2; i++){
        fileContent[i] = readEntireFile(msg[i]);
    }
    // Length of file for md5 hash
    size_t len;
    // Loop through entire files and hash them
    for(int i = 0; i <= size2; i++){
        len = strlen(fileContent[i]);
        md52(fileContent[i],len,i);
    }

    // Variable to house an array of the hashed values
    char * hashy[size2];
    // Scan the hashed file line by line
    int size = lineByline("theseHash.txt", hashy);
    for(int i = 0; i < size; i++){
        //printf("Hash Set %d: %s\n",i, hashy[i]);
    }

    // Recursively Hash the file to get the top hash
    char *ptr = treeHash(hashy,size);
    printf("==Top Hash== *** %s ***\n",ptr);

    // Check whether the top hash was changed
    FILE *top;
    top = fopen("topHash.txt", "r");
    if(top == NULL){
        top = fopen("topHash.txt","w");
        fprintf(top,"%s",ptr);
        fclose(top);
        printf("No previous top hash exists...\n");
        printf("New Top Hash Saved.\n\n");
        return 0;
    }
    else{
        char pastTop[32];
        fscanf(top,"%s",pastTop);
        fclose(top);
        if (!strcmp(pastTop, ptr)){
            puts("Top hash is equal to previous.");
            puts("No change found in files...");
        }
        else{
            puts("...\aFiles were changed!!!");
            puts("Top Hash not the same as previous saved Hash!");
            return -1;
        }
    }
}

//my attempt at hashing in tree order
char * treeHash(char **inputHash,int size){
    char hash[255];
    char arrayHash[size][255];
    int arrayCount=0;
    int num = sizeof(**inputHash) / sizeof(*inputHash[0]);

    if(size==1){
        return *inputHash;
    }
    else {
        if (size % 2 == 0) {
            for (int i = 0; i < size-1; i += 2) {
                char *result = malloc(strlen(inputHash[i]) + strlen(inputHash[i + 1]) + 1);

                strcpy(result, inputHash[i]);
                strcat(result, inputHash[i + 1]);
                size_t len = strlen(result);
                md5(result, len);

                FILE *cfPtr;
                cfPtr = fopen("thisHash.txt", "r");
                fscanf(cfPtr, "%32s\n", hash);
                strcpy(arrayHash[arrayCount], hash);
                arrayCount++;
                fclose(cfPtr);
            }
        }
        else{
            for (int i =0; i < size-2;i+=2){
                char *result = malloc(strlen(inputHash[i]) + strlen(inputHash[i+1]) +1);
                strcpy(result, inputHash[i]);

                strcat(result, inputHash[i+1]);

                size_t len = strlen(result);
                md5(result,len);
                FILE *cfPtr;

                cfPtr = fopen( "thisHash.txt", "r" );
                fscanf(cfPtr, "%32s\n", hash);
                strcpy(arrayHash[arrayCount],hash);
                arrayCount++;
                fclose(cfPtr);
            }
            int lastHash = (size/2);
            strcpy(arrayHash[lastHash],inputHash[size-1]);
            arrayCount++;
    }
        char * newString[arrayCount];
        for(int i = 0; i < arrayCount; i++){
            //printf("Next Hash set in tree %d: %s\n", i, arrayHash[i]);
            newString[i] = arrayHash[i];
        }
        return treeHash(newString,arrayCount);
    }

}
int lineByline(char *str, char *paths[]){
    FILE* inFile;
    int i = 0;
    long bufSize;
    inFile = fopen(str, "r");
    if(inFile != NULL){;
    }
    else{
        puts("\aOpen Unsuccessful.");
    }
    if (fseek(inFile, 0L, SEEK_END) == 0) {
            /* Get the size of the file. */
            bufSize = ftell(inFile);
            if (bufSize == -1) { /* Error */ }

            /* Allocate our buffer to that size. */
    }
        /* Go back to the start of the file. */
        fseek(inFile, 0L, SEEK_SET) != 0; { /* Error */ }
	char ** fileStuff = malloc(bufSize * sizeof(char*)+1);
	for(int i = 0; i < bufSize; i++){
	  fileStuff[i] = malloc((255) * sizeof(char)+ 1);
	}

    int count = 0;
    while(!feof(inFile)){
        fgets(fileStuff[count], 255, inFile);
        char *pos;
        if ((pos = strchr(fileStuff[count], '\n')) != NULL){
            *pos = '\0';
        }
        count++;
    }
    for (int k = 0; k < count; k++){
        paths[k] = fileStuff[k];
    }

    //printf("Everything is going really good right meow\n");

    fclose(inFile);
    return count-1;
}

char * readEntireFile(char *str)
{

    char *source = NULL;
    FILE *fp = fopen(str, "r");

    if (fp != NULL) {}
    else{
        printf("File was not opened...\n");
        if (!strcmp("",str)){
            printf("White Space Found in File...\n");
        }
	return "";
    }
    if (fseek(fp, 0L, SEEK_END) == 0) {
        /* Get the size of the file. */
        long bufsize = ftell(fp);
        if (bufsize == -1) { /* Error */ }

        /* Allocate our buffer to that size. */
        source = malloc(sizeof(char) * (bufsize + 1));

        /* Go back to the start of the file. */
    if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

    /* Read the entire file into memory. */
    size_t newLen = fread(source, sizeof(char), bufsize, fp);
    if ( ferror( fp ) != 0 ) {
        fputs("Error reading file", stderr);
    }
    else {
        source[newLen++] = '\0'; /* Just to be safe. */
    }
    }
        // Add this chunk's hash to result so far:
    //printf("%s", source);

    fclose(fp);
    return source;
}

void md52(uint8_t *initial_msg, size_t initial_len, int wa) {

    // Message (to prepare)
    uint32_t h0, h1, h2, h3;

    uint8_t *msg = NULL;

    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating

    // r specifies the per-round shift amounts

    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    uint32_t k[] = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
            0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
            0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
            0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
            0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
            0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
            0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
            0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
            0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
            0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
            0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
            0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
            0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;

    // Pre-processing: adding a single 1 bit
    //append "1" bit to message
    /* Notice: the input bytes are considered as bits strings,
       where the first bit is the most significant bit of the byte.[37] */

    // Pre-processing: padding with zeros
    //append "0" bit until message length in bit ≡ 448 (mod 512)
    //append length mod (2 pow 64) to message

    int new_len = ((((initial_len + 8) / 64) + 1) * 64) - 8;

    msg = calloc(new_len + 64, 1); // also appends "0" bits
    // (we alloc also 64 extra bytes...)
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit

    uint32_t bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer

    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    int offset;
    for(offset=0; offset<new_len; offset += (512/8)) {

        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *) (msg + offset);

#ifdef DEBUG
        printf("offset: %d %x\n", offset, offset);

        int j;
        for(j =0; j < 64; j++) printf("%x ", ((uint8_t *) w)[j]);
        puts("");
#endif

        // Initialize hash value for this chunk:
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;

        // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {

#ifdef ROUNDS
            uint8_t *p;
            printf("%i: ", i);
            p=(uint8_t *)&a;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], a);

            p=(uint8_t *)&b;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], b);

            p=(uint8_t *)&c;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], c);

            p=(uint8_t *)&d;
            printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], d);
            puts("");
#endif


            uint32_t f, g;

            if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

#ifdef ROUNDS
            printf("f=%x g=%d w[g]=%x\n", f, g, w[g]);
#endif
            uint32_t temp = d;
            d = c;
            c = b;
            // printf("rotateLeft(%x + %x + %x + %x, %d)\n", a, f, k[i], w[g], r[i]);
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;



        }

        // Add this chunk's hash to result so far:

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;

    }

    uint8_t *p;

    // display result
    char finalHash[255]="";
    FILE *hashFile;
    if(!wa){
    hashFile = fopen("./theseHash.txt","w");
    }
    else{
        hashFile = fopen("./theseHash.txt","a");
    }

    p=(uint8_t *)&h0;
    fprintf( hashFile,"%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3],h0);

    p=(uint8_t *)&h1;
    fprintf(hashFile,"%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);

    p=(uint8_t *)&h2;
    fprintf(hashFile,"%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);

    p=(uint8_t *)&h3;
    fprintf(hashFile,"%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h3);

    fputs("\n", hashFile);

    fclose(hashFile);
    free(msg);

}
void md5(uint8_t *initial_msg, size_t initial_len) {

    // Message (to prepare)
    uint32_t h0, h1, h2, h3;

    uint8_t *msg = NULL;

    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating

    // r specifies the per-round shift amounts

    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    uint32_t k[] = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
            0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
            0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
            0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
            0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
            0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
            0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
            0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
            0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
            0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
            0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
            0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
            0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;

    // Pre-processing: adding a single 1 bit
    //append "1" bit to message
    /* Notice: the input bytes are considered as bits strings,
       where the first bit is the most significant bit of the byte.[37] */

    // Pre-processing: padding with zeros
    //append "0" bit until message length in bit ≡ 448 (mod 512)
    //append length mod (2 pow 64) to message

    int new_len = ((((initial_len + 8) / 64) + 1) * 64) - 8;

    msg = calloc(new_len + 64, 1); // also appends "0" bits
    // (we alloc also 64 extra bytes...)
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit

    uint32_t bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer

    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    int offset;
    for(offset=0; offset<new_len; offset += (512/8)) {

        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *) (msg + offset);

#ifdef DEBUG
        printf("offset: %d %x\n", offset, offset);

        int j;
        for(j =0; j < 64; j++) printf("%x ", ((uint8_t *) w)[j]);
        puts("");
#endif

        // Initialize hash value for this chunk:
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;

        // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {

#ifdef ROUNDS
            uint8_t *p;
            printf("%i: ", i);
            p=(uint8_t *)&a;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], a);

            p=(uint8_t *)&b;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], b);

            p=(uint8_t *)&c;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], c);

            p=(uint8_t *)&d;
            printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], d);
            puts("");
#endif


            uint32_t f, g;

            if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

#ifdef ROUNDS
            printf("f=%x g=%d w[g]=%x\n", f, g, w[g]);
#endif
            uint32_t temp = d;
            d = c;
            c = b;
            // printf("rotateLeft(%x + %x + %x + %x, %d)\n", a, f, k[i], w[g], r[i]);
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;



        }

        // Add this chunk's hash to result so far:

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;

    }

    uint8_t *p;

    // display result
    char finalHash[255]="";
    FILE *hashFile;
    hashFile = fopen("./thisHash.txt","w");


    p=(uint8_t *)&h0;
    fprintf( hashFile,"%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3],h0);

    p=(uint8_t *)&h1;
    fprintf(hashFile,"%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);

    p=(uint8_t *)&h2;
    fprintf(hashFile,"%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);

    p=(uint8_t *)&h3;
    fprintf(hashFile,"%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h3);

    printf("");

    fclose(hashFile);
    free(msg);

}
