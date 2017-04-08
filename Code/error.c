#include "ncc.h"

/** \brief handle exception
 *
 * \param stage: stage of work
 * \param level: level of error
 * \param fmt: output format of parameter
 * \param ap: variable list
 * \return
 *
 */
 void HandleException(int stage, int level, char *fmt, va_list ap){
    char buf[1024];
    vsprintf(buf, fmt, ap);
    if(stage == STAGE_COMPILE){
        if(level == LEVEL_WARNING){
            printf("\n%s (Line %d) | NCC Compiling Warning | %s\n", fileName, lineNum, buf);
        }
        else{
            printf("\n%s (Line %d) | NCC Compiling Error | %s\n", fileName, lineNum, buf);
            exit(-1);
        }
    }
    else{
        printf("NCC Link Error: %s!\n", buf);
        exit(-1);
    }
 }

 /** \brief handle warning
  *
  * \param fmt: output format of parameter
  * \param ap: variable list
  * \return
  *
  */

  void PromptWarning(char *fmt, ...){
      va_list ap;

      va_start(ap, fmt);
      HandleException(STAGE_COMPILE, LEVEL_WARNING, fmt, ap);
      va_end(ap);
  }

  /** \brief handle error
  *
  * \param fmt: output format of parameter
  * \param ap: variable list
  * \return
  *
  */

  void PromptError(char *fmt, ...){
        va_list ap;
        va_start(ap, fmt);
        HandleException(STAGE_COMPILE, LEVEL_ERROR, fmt, ap);
        va_end(ap);
  }

  /** \brief prompt message what grammatical component missing
   *
   * \param msg: what grammatical component is expected
   * \param
   * \return
   *
   */

    void Expect(char *msg){
        PromptError("NCC Error: %s is missing.", msg);
    }


    /** \brief skip word c to get the next word, if the current word is not c, prompt error
     *
     * \param c: word to skip
     * \param
     * \return
     *
     */

     void Skip(int c){
        if(token != c){
            PromptError("NCC Error: '%s' is missing.", GetTkStr(c));
        }
        GetToken();
     }

     /** \brief Handle Link error
      *
      * \param fmt: output format of parameter
      * \param ap: variable list
      * \return
      *
      */

    void PromptLinkError(char *fmt, ...){
        va_list ap;
        va_start(ap, fmt);
        HandleException(STAGE_LINK, LEVEL_ERROR, fmt, ap);
        va_end(ap);
    }













