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
    // Hash the plaintext
    char *hashedText = md5(plaintext, strlen(plaintext));
    // Open the hash file
    FILE *hashFile = fopen(hashFilename, "r");
    if (!hashFile)
    {
        perror("Error opening hash file");
        free(hashedText);
        return NULL;
    }
    // Loop through the hash file, one line at a time.
    char fileHash[HASH_LEN];
    while (fgets(fileHash, HASH_LEN, hashFile) != NULL)
    {
        fileHash[strcspn(fileHash, "\n")] = 0;
    
    // Attempt to match the hash from the file to the
    // hash of the plaintext.
        if (strcmp(fileHash, hashedText) == 0)
        {
        fclose(hashFile);
        free(hashedText);
        return strdup(fileHash);
        }
    }
    // If there is a match, you'll return the hash.
    // If not, return NULL.
    fclose(hashFile);
    free(hashedText);
    return NULL;
    // Before returning, do any needed cleanup:
    //   Close files?
    //   Free memory?

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
   
    // Open the dictionary file for reading.
    FILE *dictFile = fopen(argv[2], "r");
    if (!dictFile)
    {
        perror("Error opening dictionary file");
        exit(1);
    }

    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    char word[PASS_LEN];
    int crackedCount = 0;
    while (fgets(word, PASS_LEN, dictFile) != NULL)
    {
        word[strcspn(word, "\n")] = '\0';
        char *match = tryWord(word, argv[1]);
        if (match) 
        {
            printf("%s %s\n", match, word);
            free(match);
            crackedCount++;
        }
    }
    // If we got a match, display the hash and the word. For example:
    //   5d41402abc4b2a76b9719d911017c592 hello
    
    // Close the dictionary file.
    fclose(dictFile);
    // Display the number of hashes that were cracked.
    printf("Total hashes cracked: %d\n", crackedCount);
    // Free up any malloc'd memory?
    return 0;
}
