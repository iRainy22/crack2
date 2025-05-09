#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    char * targetHash = md5(plaintext,strlen(plaintext));
    FILE * src = fopen(hashFilename, "r");
    char line[136];

    // Loop through the hash file, one line at a time.
    while(!feof(src)) {
        if(fgets(line,255,src) != NULL) {
            line[strcspn(line, "\n")] = 0;
            if(strcmp(line,targetHash) == 0) {
                return targetHash;
            }

        }

    }
    return NULL;
    free(targetHash);
    fclose(src);
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }


    // Open the dictionary file for reading.
    FILE * dict = fopen(argv[2],"r");
    int count;
    char line[136], try[PASS_LEN];
    //loop through dict
    while(!feof(dict)) {
        if(fgets(line,255,dict) != NULL) {
            line[strcspn(line, "\n")] = 0;
            char * try = tryWord(line,argv[1]);
            //if hash matches a dict word, than it will print it in increment the count.
            if(try != NULL) {
                count++;
                printf("Hash: %s, Plaintxt: %s\n",try, line);
            }
        }
    }

]
    
    // Close the dictionary file.
    fclose(dict);
    // Display the number of hashes that were cracked.
    printf("%i Hashes were cracked!",count);
}

