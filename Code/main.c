#include <stdio.h>
#include <stdlib.h>
#include "ncc.h"

FILE *fin = NULL;
char *fileName;
char *outFile;


/** \brief compute hash address
 *
 * \param key: hash keyword
 * \param MAXKEY: length of hash table
 * \return
 *
 */
int ELFHash(char *key){
    int h = 0, g;
    while(*key){
        h = (h << 4) + *key++;
        g = h & 0xf0000000;
        if(g){
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h % MAXKEY;
}


/** \brief allocate heap memory and initialize it to 0
 *
 * \param size: size of the memory
 * \param
 * \return
 *
 */
 void *MallocZ(int size){
    void *ptr;
    ptr = malloc(size);
    if(!ptr && size){
        PromptError("NCC Error: Failed to allocate memory.");
    }
    memset(ptr, 0, size);
    return ptr;
 }



int main(int argc, char **argv)
{
    fin = fopen(argv[1], "rb");
    if(!fin){
        printf("Could not open NC source file!\n");
        return 0;
    }
    Init();
    GetCh();
    TestLex();
    CleanUp();
    fclose(fin);
    printf("%s is analyzed successfully!\n", argv[1]);
    return 1;
    /*
    printf("Hello world!\n");
    */
}

void Init(){
    lineNum = 1;
    InitLex();
}
void CleanUp(){
    int i;
    //printf("\n tkTable.cnt = %d\n", tkTable.cnt);
    for(i = TK_IDENT; i < tkTable.cnt; i++){
        free(tkTable.ppData[i]);
    }
    free(tkTable.ppData);

   //system("color 07");
}

char *GetFileExt(char *fName){
    char *p;
    p = strrchr(fName, '.');
    return p + 1;
}
