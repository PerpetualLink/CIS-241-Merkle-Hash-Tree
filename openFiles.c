#include <stdio.h>
#include <stdlib.h>

// Testing File reading stuff
int main()
{

    char *source = NULL;
        //FILE *fp = fopen("C:\\Users\\Brad Samack\\Documents\\School\\GVSU\\CIS\\290\\Samack, Brad Memo Nov 2019.pdf", "rb");
        //FILE *fp = fopen("C:\\Users\\Brad Samack\\Documents\\School\\GVSU\\CIS\\353 Database\\db.pdf", "rb");
    if (fp != NULL) {
    /* Go to the end of the file. */
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
        } else {
            source[newLen++] = '\0'; /* Just to be safe. */
        }
    }
    printf("%s", source);
    fclose(fp);
}

free(source);
//    FILE* inFile;
//    unsigned char content[255];
//    unsigned char fileStuff[20][255];
//    int i = 0;
//    inFile = fopen("C:\\Users\\Brad Samack\\Documents\\School\\GVSU\\CIS\\241\\HW 1\\infiniteLoop.txt", "r");
//  while(!feof(inFile)){
//        fgets(content, 255, (FILE*)inFile);
//        //printf("%s", content);
//        strcpy(fileStuff[i], content);
//        //printf("%s", fileStuff[i]);
//        //printf("%d", i);
//        i++;
//    }
//    for (int k = 0; k < 20; k++){
//        printf("%s", fileStuff[k]);
//    }
//
//    fclose(inFile);
    return 0;
}
/** How do we get the path names / input from user? **/
/*Unix commands/script:
    where do we want to look into?
    How are we searching file? looking through all files, or just one directory?
    Do we want to only check integrity of key words?
    Prompt to enter keyword or manually enter filenames / paths of filename  / files of filetype
    Find files and redirect to file where our program is.

*/

/** Crap code to explain idea for project  **/

/**
// hash(char *str, int size, int doIOverWrite){
//    if (doIOverWrite){
//        write to file
//    }
//    else
//        append to file
//}
//
//
//int funct (int size){
//    if size == 1
//        return 1;
//    if (size % 2 != 0){
//        int size2 = 0;
//        for (int i = 0; i < size - 1; i = i + 2){
//            size2 += strlen(str[i]) + strlen(str(i+1));
//
//            hash((str[i] + str[i+1]), size2, i);
//        }
//        return funct(size/2);
//    }
//    else{
//        int size2 = 0;
//        for (int i = 0; i < size - 2; i = i + 2){
//            size2 += strlen(str[i]) + strlen(str(i+1));
//
//            hash((str[i] + str[i+1]), size2, i);
//        }
//        hash(str[size-1], strlen(str[size-1], 1));
//        return funct(size/2);
//    }
//}
//
//read top hash{
//    counter variable
//    read file
//    is counter == 1
//        if so return top hash
//
//        else this is not top hash something not correct
//    print the line
//    write to history of top hash file?
//    if checking integrity
//        is top hash == prev top hash?
// }
**/
