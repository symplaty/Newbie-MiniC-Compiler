#include "ncc.h"

//#define MAXKEY 1024             // capacity of hash table
TkWord *tkHashTable[MAXKEY];      // hash table
DynArray tkTable;                 // token(word) table
DynString tkStr;
DynString sourceStr;
int token;
char ch;
int lineNum = 0;
int tkValue;


/** \brief put operators, keywords and constants into token table directly
 *
 * \param
 * \param
 * \return
 *
 */
 TkWord * TkwordInsertDirect(TkWord *tp){
    int keyNo;
    tp->symIdentifier = NULL;
    tp->symStruct = NULL;
    DynArrayAdd(&tkTable, tp);
    keyNo = ELFHash(tp->spelling);
    tp->next = tkHashTable[keyNo];
    tkHashTable[keyNo] = tp;
    return tp;
 }

 /** \brief look up words in token table
  *
  * \param p: word to look up
  * \param keyNo: hash key of the word
  * \return
  *
  */
TkWord *TkwordFind(char *p, int keyNo){
    TkWord *tp = NULL, *tp1;
    for(tp1 = tkHashTable[keyNo]; tp1; tp1 = tp1->next){
        if(!strcmp(p, tp1->spelling)){
            token = tp1->tkCode;
            tp = tp1;
        }
    }
    return tp;
}

/** \brief insert identifier into token table when it cannot be found
 *
 * \param
 * \param
 * \return
 *
 */
TkWord* TkwordInsert(char *p){
    TkWord *tp;
    int keyNo;
    char *s;
    char *end;
    int length;

    keyNo = ELFHash(p);
    tp = TkwordFind(p, keyNo);
    if(tp == NULL){
        length = strlen(p);
        tp = (TkWord *)MallocZ(sizeof(TkWord) + length + 1);
        tp->next = tkHashTable[keyNo];
        tkHashTable[keyNo] = tp;
        DynArrayAdd(&tkTable, tp);
        tp->tkCode = tkTable.cnt - 1;
        s = (char *)tp + sizeof(TkWord);
        tp->spelling = (char *)s;
        for(end = p + length; p < end;){
            *s++ = *p++;
        }
        *s = (char)'\0';
        tp->symIdentifier = NULL;
        tp->symStruct = NULL;
    }
    return tp;
}


 /** \brief initialize lex analyze
  *
  * \param
  * \param
  * \return
  *
  */
  void InitLex(){
    TkWord *tp;
    static TkWord keywords[] = {
        {TK_PLUS,		NULL,	  "+",	NULL,	NULL},
        {TK_MINUS,		NULL,	  "-",	NULL,	NULL},
        {TK_STAR,		NULL,	  "*",	NULL,	NULL},
        {TK_DIVIDE,		NULL,	  "/",	NULL,	NULL},
        {TK_MOD,		NULL,	  "%",	NULL,	NULL},
        {TK_EQUAL,		NULL,	  "==",	NULL,	NULL},
        {TK_NEQUAL,		NULL,	  "!=",	NULL,	NULL},
        {TK_LESSTHAN,	NULL,	  "<",	NULL,	NULL},
        {TK_LESSEQ,		NULL,	  "<=",	NULL,	NULL},
        {TK_GREATERTHAN,NULL,	  ">",	NULL,	NULL},
        {TK_GREATEREQ,	NULL,	  ">=",	NULL,	NULL},
        {TK_ASSIGN,		NULL,	  "=",	NULL,	NULL},
        {TK_POINTSTO,	NULL,	  "->",	NULL,	NULL},
        {TK_DOT,		NULL,	  ".",	NULL,	NULL},
        {TK_AND,		NULL,	  "&",	NULL,	NULL},
        {TK_OR,		    NULL,	  "|",	NULL,	NULL},
        {TK_NOT,		NULL,	  "!",	NULL,	NULL},
        {TK_OPENPA,		NULL,	  "(",	NULL,	NULL},
        {TK_CLOSEPA,	NULL,	  ")",	NULL,	NULL},
        {TK_OPENBR,		NULL,	  "[",	NULL,	NULL},
        {TK_CLOSEBR,	NULL,	  "]",	NULL,	NULL},
        {TK_BEGIN,		NULL,	  "{",	NULL,	NULL},
        {TK_END,		NULL,	  "}",	NULL,	NULL},
        {TK_SEMICOLON,	NULL,	  ";",	NULL,	NULL},
        {TK_COMMA,		NULL,	  ",",	NULL,	NULL},
        {TK_ELLIPSIS,	NULL,	"...",	NULL,	NULL},
        {TK_EOF,		NULL,	 "End Of File",	NULL,	NULL},

        {TK_CINT,		NULL,	"int constant",	    NULL,	NULL},
        {TK_CCHAR,		NULL,	"char constant",	NULL,	NULL},
        {TK_CSTRING,	NULL,	"string constant",	NULL,	NULL},

        {KW_CHAR,		NULL,		"char",	    NULL,	NULL},
        {KW_SHORT,		NULL,		"short",	NULL,	NULL},
        {KW_INT,		NULL,		"int",	    NULL,	NULL},
        {KW_VOID,		NULL,		"void",	    NULL,	NULL},
        {KW_STRUCT,		NULL,		"struct",	NULL,	NULL},

        {KW_IF,			NULL,		"if"	,	NULL,	NULL},
        {KW_ELSE,		NULL,		"else",	    NULL,	NULL},
        {KW_FOR,		NULL,		"for",	    NULL,	NULL},
        {KW_CONTINUE,	NULL,		"continue",	NULL,	NULL},
        {KW_BREAK,		NULL,		"break",	NULL,	NULL},
        {KW_RETURN,		NULL,		"return",	NULL,	NULL},
        {KW_SIZEOF,		NULL,		"sizeof",	NULL,	NULL},
        /*
        {KW_ALIGN,		NULL,		"__align",	NULL,	NULL},
        {KW_CDECL,		NULL,		"__cdecl",	NULL,	NULL},
        {KW_STDCALL,	NULL,		"__stdcall",NULL,	NULL},
        */{0,				NULL,	    NULL,	    NULL,	NULL},

	};

	DynArrayInit(&tkTable,8);
    for (tp = &keywords[0]; tp->spelling != NULL; tp++){
			TkwordInsertDirect(tp);
    }
  }

  /** \brief get word
   *
   * \param
   * \param
   * \return
   *
   */
 void GetToken(){
	PreProcess();
	switch(ch)
	{
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
    case 'o': case 'p': case 'q': case 'r': case 's': case 't':
    case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T':
    case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
    case '_':
		{
			TkWord* tp;
			tp = ParseIdentifier();
			token = tp->tkCode;
			break;
		}
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
		ParseNum();
		token = TK_CINT;
		break;
    case '+':
		GetCh();
		token = TK_PLUS;
		break;
	case '-':
		GetCh();
		if(ch == '>')
		{
		    token = TK_POINTSTO;
			GetCh();
		}
		else
			token = TK_MINUS;
		break;
	case '/':
		token = TK_DIVIDE;
		GetCh();
		break;
	case '%':
		token = TK_MOD;
		GetCh();
		break;
	case '=':
		GetCh();
		if(ch == '=')
		{
			token = TK_EQUAL;
			GetCh();
		}
		else
			token = TK_ASSIGN;
		break;
	case '!':
		GetCh();
		if(ch == '=')
		{
			token = TK_NEQUAL;
			GetCh();
		}
		else
			PromptError("NCC Error: Unsupported character '!'.");
		break;
	case '<':
		GetCh();
		if(ch == '=')
		{
			token = TK_LESSEQ;
			GetCh();
		}
		else
			token = TK_LESSTHAN;
		break;
	case '>':
		GetCh();
		if(ch == '=')
		{
			token = TK_GREATEREQ;
			GetCh();
		}
		else
			token = TK_GREATERTHAN;
		break;
	case '.':
		GetCh();
		if(ch == '.')
		{
			GetCh();
			if(ch != '.')
			  PromptError("NCC Error: Spelling error of ellipsis.");
			else
			  token = TK_ELLIPSIS;
			GetCh();
		}
		else
		{
			token = TK_DOT;
		}
		break;
	case '&':
		token = TK_AND;
		GetCh();
		break;
	case ';':
		token = TK_SEMICOLON;
		GetCh();
		break;
	case ']':
		token = TK_CLOSEBR;
		GetCh();
		break;
	case '}':
		token = TK_END;
		GetCh();
		break;
	case ')':
		token = TK_CLOSEPA;
		GetCh();
		break;
	case '[':
		token = TK_OPENBR;
		GetCh();
		break;
	case '{':
		token = TK_BEGIN;
		GetCh();
		break;
	case ',':
		token = TK_COMMA;
		GetCh();
		break;
	case '(':
		token = TK_OPENPA;
		GetCh();
		break;
	case '*':
		token = TK_STAR;
		GetCh();
		break;
    case '\'':
		ParseString(ch);
		token = TK_CCHAR;
		tkValue = *(char *)tkStr.pData;
		break;
    case '\"':
		{
			ParseString(ch);
			token = TK_CSTRING;
            break;
		}
	case EOF:
		token = TK_EOF;
		break;
    default:
        PromptError("NCC Error: Unknown Character: \\x%02x", ch);
		GetCh();
        break;
    }
 }


 /** \brief get token string that word v represents
 *
 * \param v: word token
 *\param
 * \return
 *
 */
 char* GetTkStr(int v){
    if(v > tkTable.cnt){
        return NULL;
    }
    else if(v >= TK_CINT && v <= TK_CSTRING){
        return sourceStr.pData;
    }
    else{
        return ((TkWord *)tkTable.ppData[v])->spelling;
    }
 }

 /** \brief get a char from NC(Newbie C) source file
  *
  * \param
  * \param
  * \return
  *
  */
 void GetCh(){
    ch = getc(fin);     //return EOF when meets end of file, else return the character
  }


  /** \brief pre-process ignore space and comments
   *
   * \param
   * \param
   * \return
   *
   */
  void PreProcess(){
    while(1){
        if(ch == ' ' || ch == '\t' || ch == '\r'){
            SkipWhiteSpace();
        }
        else if(ch == '/'){
            GetCh();
            if(ch == '*'){
                ParseComment();
            }
            else{
                ungetc(ch, fin);
                ch = '/';
                break;
            }
        }
        else
            break;
    }
  }

  /** \brief handle comment
   *
   * \param
   * \param
   * \return
   *
   */
  void ParseComment(){
    GetCh();
    do{
        do{
            if(ch == '\n' || ch == '*' || ch == CH_EOF)
                break;
            else
                GetCh();
        }while(1);
        if(ch == '\n'){
            lineNum ++;
            GetCh();
        }
        else if(ch == '*'){
            GetCh();
            if(ch == '/'){
                GetCh();
                return;
            }
        }
        else{
            PromptError("Error: Unmatched comment symbol.");
            return;
        }
    }while(1);
  }


  /** \brief Ignore space, Tab and CR(Carriage Return)
   *
   * \param
   * \param
   * \return
   *
   */
    void SkipWhiteSpace(){
        while(ch == ' ' || ch == '\t' || ch == '\r'){
            if(ch == '\r'){
                GetCh();
                if(ch != '\n'){
                    return;
                }
                lineNum ++;
            }
            printf("%c", ch);
            GetCh();
        }
    }

 /** \brief if c is a letter(a~z, A~Z, _)
  *
  * \param c: character
  * \param
  * \return
  *
  */
 int isNodigit(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
 }

 /** \brief if c is a digit
  *
  * \param c: character
  * \param
  * \return
  *
  */
  int isDigit(char c){
    return c >= '0' && c <= '9';
  }

  /** \brief parse identifier
   *
   * \param
   * \param
   * \return
   *
   */
 TkWord * ParseIdentifier(){
    DynstringReset(&tkStr);
    DynStringCharCat(&tkStr, ch);
    GetCh();
    while(isNodigit(ch) || isDigit(ch)){
        DynStringCharCat(&tkStr, ch);
        GetCh();
    }
    DynStringCharCat(&tkStr, '\0');
    return TkwordInsert(tkStr.pData);
 }

 /** \brief parse number
  *
  * \param
  * \param
  * \return
  *
  */
  void ParseNum(){
    DynstringReset(&tkStr);
    DynstringReset(&sourceStr);
    do{
        DynStringCharCat(&tkStr, ch);
        DynStringCharCat(&sourceStr, ch);
        GetCh();
    }while(isDigit(ch));
    if(ch == '.');{
        do{
            DynStringCharCat(&tkStr, ch);
            DynStringCharCat(&sourceStr, ch);
            GetCh();
        }while(isDigit(ch));
    }
    DynStringCharCat(&tkStr, '\0');
    DynStringCharCat(&sourceStr, '\0');
    tkValue = atoi(tkStr.pData);
}

/** \brief parse string
 *
 * \param sep:
 * \param
 * \return
 *
 */
 void ParseString(char sep){
    char c;
    DynstringReset(&tkStr);
    DynstringReset(&sourceStr);
    DynStringCharCat(&sourceStr, sep);
    GetCh();
    for(; ;){
        if(ch == sep)
            break;
        else if(ch == '\\'){
            DynStringCharCat(&sourceStr, ch);
            GetCh();
            switch(ch){
                case '0':
                    c = '\0';
                    break;
                case 'a':
                    c = '\a';
                    break;
                case 'b':
                    c = '\b';
                    break;
                case 't':
                    c = '\t';
                    break;
                case 'n':
                    c = '\n';
                    break;
                case 'v':
                    c = '\v';
                    break;
                case 'f':
                    c = '\f';
                    break;
                case 'r':
                    c = '\r';
                    break;
                case '\"':
                    c = '\"';
                    break;
                case '\'':
                    c = '\'';
                    break;
                case '\\':
                    c = '\\';
                    break;
                default:
                    c = ch;
                    if(c >= '!' && c <= '~'){
                        PromptWarning("Warning: Illegal escape character: \'\\%c\'.", c);
                    }
                    else{
                        PromptWarning("Warning: Illegal escape character: \'\\0x%x\'", c);
                    }
                    break;
            }
            DynStringCharCat(&tkStr, c);
            DynStringCharCat(&sourceStr, ch);
            GetCh();
        }
        else{
            DynStringCharCat(&tkStr, ch);
            DynStringCharCat(&sourceStr, ch);
            GetCh();
        }
    }
    DynStringCharCat(&tkStr, '\0');
    DynStringCharCat(&sourceStr, sep);
    DynStringCharCat(&sourceStr, '\0');
    GetCh();
 }


 void ColorToken(int lexState){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    char *p;
    switch(lexState){
    case LEX_NORMAL:
        {
            if(token >= TK_IDENT)
                SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
            else if(token >= KW_CHAR)
                SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
            else if(token >= TK_CINT)
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
            else
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            p = GetTkStr(token);
            printf("%s", p);
            break;
        }
    case LEX_SEP:
        printf("%c", ch);
        break;
    }
 }

 void TestLex(){
    do{
        GetToken();
        ColorToken(LEX_NORMAL);
    }while(token != TK_EOF);
    printf("\n\n%d lines in total.\n", lineNum);
 }
