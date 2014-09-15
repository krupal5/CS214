/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation
 */

struct TokenizerT_ {
  int numTok;
  char** toks;
  int iterator;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {

  TokenizerT* tok = (TokenizerT *)malloc(sizeof(TokenizerT));
  int lenOfts = strlen(ts);
  char *tsDuplic = (char *)calloc(lenOfts, sizeof(char));
  strcpy(tsDuplic, ts);
  tok->numTok = 0;
  tok->iterator = 0;
  int cmdStrLen = strlen(ts);
  char delim = separators[0];
  int i = 0; 
  int j = 0;
  int sizeHolder = 0;

  while(i < cmdStrLen){
    if (tsDuplic[i] == delim && sizeHolder >0){
      tok->numTok++;
      sizeHolder = 0;
    }
    else if(tsDuplic[i] != delim){
       sizeHolder++; 
    }
    i++;
  }
  
  sizeHolder = 0;
  tok->numTok++;
  tok->toks = (char**) malloc((tok->numTok+1) * sizeof(char*));

  for(i=0; i < cmdStrLen; i++){
    if (tsDuplic[i] == delim && sizeHolder >0){
      tok->toks[j] = (char*) malloc((sizeHolder+1) * sizeof(char));
      strncpy(tok->toks[j], tsDuplic+(i-sizeHolder), sizeHolder);
        tok->toks[j][sizeHolder] = '\0';
      j++;
      sizeHolder = 0;
    }
    else if(tsDuplic[i] != delim){
       sizeHolder++; 
    }
  }
  
  tok->toks[j] = (char*) malloc((sizeHolder+1) * sizeof(char));  
  strncpy(tok->toks[j], tsDuplic+(i-sizeHolder), sizeHolder);
  free(tsDuplic);
  return tok;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
  int i;
  
  for(i = 0; i < tk->numTok; i++) {
    free(tk->toks[i]);
  }

  free(tk->toks);
  free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {
  if (tk->iterator > tk->numTok) return NULL; 
  else {tk->iterator++; return tk->toks[tk->iterator-1];}
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {

  if(argc != 3){
    fprintf(stderr,"Error: Incorrect number of arguments.\n");
    return 1;
  }
  if(strcmp(argv[1],"-h") == 0){
    printf("Usage: ./tokenizer <delimeters> <tokens>\n");
    return 1;
  }
    
  TokenizerT* tok;
  char* retToken;

  tok = TKCreate(argv[1], argv[2]);
  retToken = TKGetNextToken(tok);

  while (retToken != NULL){
      printf("%s\n", retToken);
      retToken = TKGetNextToken(tok);
  }

  TKDestroy(tok);
  
  return 0;
}
