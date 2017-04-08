#include <windows.h>
#include <stdio.h>





/**************************** dynamicstring.h begin ***************************************/
 typedef struct DynString
 {
    int cnt;            //the length of string;
    int capacity;       //the length of buffer holding the string;
    char *pData;        //pointer pointing to the string;
 }DynString;

 void DynstringInit(DynString *pStr, int initSize);
 void DynStringFree(DynString *pStr);
 void DynstringReset(DynString *pStr);
 void DynStringRealloc(DynString *pStr, int newSize);
 void DynStringCharCat(DynString *pStr, int ch);

/**************************** dynamicstring.h end ***************************************/


/**************************** dynamicarray.h begin ***************************************/
 typedef struct DynArray{
    int cnt;            // number of elements
    int capacity;       // size of buffer
    void **ppData;       // pointer pointing to pointer that points to data array
 }DynArray;
 void DynArrayInit(DynArray *pArr, int initSize);
 void DynArrayFree(DynArray *pArr);
 void DynArrayRealloc(DynArray *pArr, int newSize);
 void DynArrayAdd(DynArray *pArr, void *pData);
 int DynArraySearch(DynArray *pArr, int key);

/**************************** dynamicarray.h end ***************************************/


/**************************** lex.h begin ***************************************/
/**< begin of TokenCode */
enum eTokenCode
{
    /*Operator*/
    TK_PLUS,            // +
    TK_MINUS,           // -
    TK_STAR,            // *
    TK_DIVIDE,          // /
    TK_MOD,             // %
    TK_EQUAL,           // ==
    TK_NEQUAL,          // !=
    TK_LESSTHAN,        // <
    TK_LESSEQ,          // <=
    TK_GREATERTHAN,     // >
    TK_GREATEREQ,       // >=
    TK_ASSIGN,          // =
    TK_POINTSTO,        // ->
    TK_DOT,             // .
    TK_AND,             // &
    TK_OR,              // |
    TK_NOT,             // !
    TK_OPENPA,          // (
    TK_CLOSEPA,         // )
    TK_OPENBR,          // [
    TK_CLOSEBR,         // ]
    TK_BEGIN,           // {
    TK_END,             // }
    TK_SEMICOLON,       // ;
    TK_COMMA,           // ,
    TK_ELLIPSIS,        // ...
    TK_EOF,             // END OF FILE

    /*CONSTANTS*/
    TK_CINT,           // INT
    TK_CCHAR,          // CHAR
    TK_CSTRING,        // STRING

    /*KEYWORD*/
    KW_CHAR,            // CHAR
    KW_SHORT,           // SHORT
    KW_INT,             // INT
    KW_VOID,            // VOID
    KW_STRUCT,          // STRUCT
    KW_IF,              // IF
    KW_ELSE,            // ELSE
    KW_FOR,             // FOR
    KW_CONTINUE,        // CONTINUE
    KW_BREAK,           // BREAK
    KW_RETURN,          // RETURN
    KW_SIZEOF,          // SIZEOF


    KW_ALIGN,           // __ALIGN
    KW_CDECL,           // __CDECL
    KW_STDCALL,         // __STDCALL

    /*IDENTIFIER*/
    TK_IDENT
};
/**< end of TokenCode */



enum eLexState{
    LEX_NORMAL,
    LEX_SEP
};



/**< begin of word table */
typedef struct TkWord{
    int tkCode;                     //code of word
    struct TkWord *next;            //next node
    char *spelling;                 //word
    struct Symbol *symStruct;       //points to the structure
    struct symbol *symIdentifier;   //points to the Identifier
}TkWord;
/**< end of word table */


#define MAXKEY 1024             // capacity of hash table
extern TkWord *tkHashTable[MAXKEY];    // hash table
extern DynArray tkTable;              // token(word) table
#define CH_EOF -1

//int ELFHash(char *key);
TkWord* TkwordInsertDirect(TkWord *tp);
TkWord* TkwordInsert(char *p);
void GetCh();
void GetToken();
void PreProcess();
int isDigit(char ch);
int isNodigit(char ch);
void ParseNum();
void PreProcess();
void ParseComment();
void SkipWhiteSpace();
int isNodigit(char c);
int isDigit(char c);
TkWord* ParseIdentifier();
void ParseString(char sep);
char *GetTkStr(int v);

void InitLex();
void TestLex();
void ColorToken(int lexState);

/**************************** lex.h end ***************************************/


/**************************** error.h begin ***************************************/
/* lever of error */
enum eErrorLevel{
    LEVEL_WARNING,
    LEVEL_ERROR,
};

/* work stage */
enum eWorkStage{
    STAGE_COMPILE,
    STAGE_LINK,
};
//void HandleException(int stage, int level, char *fmt, va_list ap);
void PromptError(char *fmt, ...);
void PromptWarning(char *fmt, ...);
void Expect(char *msg);
void Skip(int c);
void PromptLinkError(char *fmt, ...);
/**************************** error.h end ***************************************/

/**************************** ncc.h begin ***************************************/
extern DynString tkStr;
extern FILE *fin;
extern char ch;
extern char *fileName;
extern int token;
extern int tkValue;
extern int lineNum;
int ELFHash(char *name);
void *MallocZ(int size);
void Init();
void CleanUp();


/**************************** ncc.h end ***************************************/


