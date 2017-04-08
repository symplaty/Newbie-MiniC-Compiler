#include "ncc.h"

/** \brief initialize dynamic string capacity
 *
 * \param pStr: structure of dynamic string
 * \param initSize: initial size of string
 * \return
 *
 */

void DynstringInit(DynString *pStr, int initSize){
    if(pStr != NULL){
        pStr->pData = (char *)malloc(sizeof(char) *initSize);
        pStr->cnt = 0;
        pStr->capacity = initSize;
    }
}

/** \brief release the memory used by dynamic string
 *
 * \param pStr: structure of dynamic string
 * \param
 * \return
 *
 */

void DynStringFree(DynString *pStr){
    if(pStr != NULL){
        if(pStr->pData){
            free(pStr->pData);
        }
        pStr->cnt = 0;
        pStr->capacity = 0;

    }
}

/** \brief reset dynamic string
 *
 * \param pStr: structure of dynamic string
 * \param
 * \return
 *
 */

 void DynstringReset(DynString *pStr){
    DynStringFree(pStr);
    DynstringInit(pStr, 8);
 }


/** \brief reallocate dynamic string
 *
 * \param pStr: structure of dynamic string
 * \param newSize: new size of string
 * \return
 *
 */

 void DynStringRealloc(DynString *pStr, int newSize){
    int capacity;
    char *pData;

    capacity = pStr->capacity;
    while(capacity < newSize){
        capacity = capacity * 2;
    }
    pData = realloc(pStr->pData, capacity);
    if(!pData){
        PromptError("NCC Error: Failed to allocate memory!");
    }
    pStr->capacity = capacity;
    pStr->pData = pData;
 }


/** \brief add a single char to dynamic string
 *
 * \param pStr: structure of dynamic string
 * \param ch: char to add
 * \return
 *
 */

 void DynStringCharCat(DynString *pStr, int ch){
    int cnt;
    cnt = pStr->cnt + 1;
    if(cnt > pStr->capacity){
        DynStringRealloc(pStr, cnt);
    }
    ((char *)pStr->pData)[cnt - 1] = ch;
    pStr->cnt  = cnt;

 }
