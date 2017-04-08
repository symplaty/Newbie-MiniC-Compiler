#include "ncc.h"

/** \brief initialize capacity of dynamic array
 *
 * \param pArr: structure of dynamic array
 * \param initSize: initial size of dynamic array
 * \return
 *
 */

 void DynArrayInit(DynArray *pArr, int initSize){
    if(pArr != NULL){
        pArr->ppData = (void **)malloc(sizeof(void *) * initSize);
        pArr->cnt = 0;
        pArr->capacity = initSize;
    }
 }

/** \brief release memory of dynamic array
 *
 * \param pArr: structure of dynamic array
 * \param p: temp pointer
 * \return
 *
 */

 void DynArrayFree(DynArray *pArr){
    void **p;
    for(p = pArr->ppData; pArr->cnt; ++p, --pArr->cnt){
        if(*p){
            free(*p);
        }
    }
    free(pArr->ppData);
    pArr->ppData = NULL;
 }

/** \brief reallocate capacity of dynamic array
 *
 * \param pArr: structure of dynamic array
 * \param newSize: latest number of dynamic string
 * \return
 *
 */

/**< I don't understand. */

 void DynArrayRealloc(DynArray *pArr, int newSize){
    int capacity;
    void *pData;

    capacity = pArr->capacity;
    while(capacity < newSize){
        capacity = capacity * 2;
    }

    pData = realloc(pArr->ppData, capacity);
    if(!pData){
        PromptError("NCC Error: Failed to allocate memory.");
    }
    pArr->capacity = capacity;
    pArr->ppData = pData;
 }

 /** \brief Add an element to dynamic array
  *
  * \param pArr: structure of dynamic array
  * \param pData: element to add
  * \return
  *
  */

 void DynArrayAdd(DynArray *pArr, void *pData){
    int cnt;
    cnt = pArr->cnt + 1;
    if(cnt * sizeof(void *) > pArr->capacity){
        DynArrayRealloc(pArr, cnt * sizeof(void *));
    }
    pArr->ppData[cnt - 1] = pData;
    pArr->cnt = cnt;
 }

/** \brief dynamic array search
 *
 * \param pArr: structure of dynamic array
 * \param key: element to search
 * \return position of element that we're looking for, -1 means no result
 *
 */
 int DynArraySearch(DynArray *pArr, int key){
    int i;
    int **p;
    p = (int **)pArr->ppData;
    for(i = 0; i < pArr->cnt; ++i, p++){
        if(key == **p){
            return i;
        }
    }
    return -1;
 }

