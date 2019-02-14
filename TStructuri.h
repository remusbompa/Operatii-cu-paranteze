/*BOMPA Remus-315CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef _STRUCTURI_
#define _STRUCTURI_
typedef int (*TFCmp) (void *, void *);
typedef void (*TF) (void *, FILE *);

typedef struct celulag
{
  void *info;
  struct celulag *urm;
} TCelulaG, *TLG, **ALG;

typedef struct
{
  int id_paranteza;
  char tip;
} Paranteza;

typedef struct
{
  size_t dime;
  TLG vf;
} TStiva;

typedef struct
{
  size_t dime;
  TLG ic, sc;
} TCoada;

TLG AlocCelula (void *ae);
TStiva *InitS (int dime);
TCoada *InitQ (int dime);
int Push (TStiva * s, void *ae);
int IntrQ (TCoada * c, void *ae);
int Pop (TStiva * s, void *ae);
int ExtrQ (TCoada * c, void *ae);
int cmp (void *a, void *b);
void SortS (TStiva * s, TFCmp cmp);
void SortQ (TCoada * c, TFCmp cmp);
void Afi (void *ae, FILE * fout);
void PrintS (TStiva * s, TF Afi, FILE * fout);
void PrintQ (TCoada * c, TF Afi, FILE * fout);
TStiva *CopyS (TStiva * s);
TCoada *CopyQ (TCoada * c);
int Verifica (char a, char b);
void CorrectS (TStiva * s, FILE * fout);
void CorrectQ (TCoada * c, FILE * fout);
void ElibS (TStiva * s);
void ElibQ (TCoada * c);
#endif
