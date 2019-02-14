/*BOMPA Remus-315CB*/
#include"TStructuri.h"

TLG
AlocCelula (void *ae)
{
  TLG aux = (TLG) malloc (sizeof (TCelulaG));
  if (!aux)
    return NULL;
  aux->info = ae;
  aux->urm = NULL;
  return aux;
}

TStiva *
InitS (int dime)
{
  TStiva *s = (TStiva *) malloc (sizeof (TStiva));
  if (!s)
    {
      printf ("eroare alocare stiva!\n");
      return NULL;
    }
  s->dime = dime;
  s->vf = NULL;
  return s;
}

TCoada *
InitQ (int dime)
{
  TCoada *c = (TCoada *) malloc (sizeof (TCoada));
  if (!c)
    {
      printf ("eroare alocare coada!\n");
      return NULL;
    }
  c->dime = dime;
  c->ic = NULL;
  c->sc = NULL;
  return c;
}

int
Push (TStiva * s, void *ae)
{
  TLG aux = AlocCelula (ae);
  if (!aux)
    return 0;
  aux->urm = s->vf;
  s->vf = aux;
  return 1;
}

int
IntrQ (TCoada * c, void *ae)
{
  TLG aux = AlocCelula (ae);
  if (!aux)
    return 0;
  if (!c->ic)
    {
      c->ic = aux;
      c->sc = aux;
    }				/*daca coada e goala */
  else
    {
      c->sc->urm = aux;
      c->sc = aux;
    }
  return 1;
}

int
Pop (TStiva * s, void *ae)
{
  TLG aux = s->vf;
  if (!aux)
    return 0;
  s->vf = aux->urm;
  memcpy (ae, aux->info, s->dime);
  free (aux->info);
  free (aux);
  return 1;
}

int
ExtrQ (TCoada * c, void *ae)
{
  TLG aux = c->ic;
  if (!aux)
    return 0;
  memcpy (ae, aux->info, c->dime);
  c->ic = aux->urm;
  if (aux == c->sc)
    c->sc = NULL;		/*daca coada are doar un element */
  free (aux->info);
  free (aux);
  return 1;
}

int
cmp (void *a, void *b)
{
  Paranteza *pa = (Paranteza *) a, *pb = (Paranteza *) b;
  return pa->id_paranteza - pb->id_paranteza;
}

void
SortS (TStiva * s, TFCmp cmp)
{
  TStiva *aux = InitS (s->dime);
  while (s->vf)
    {
      void *svf = malloc (s->dime);
      if (!svf)
	{
	  printf ("eroare alocare svf!\n");
	  return;
	}
      Pop (s, svf);
      while (aux->vf && cmp (svf, aux->vf->info) > 0)
	{
	  void *ae = malloc (s->dime);
	  if (!ae)
	    {
	      printf ("eroare alocare ae!\n");
	      return;
	    }
	  Pop (aux, ae);
	  Push (s, ae);
	}
      Push (aux, svf);
    }
  while (aux->vf)
    {
      void *ae = malloc (s->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      Pop (aux, ae);
      Push (s, ae);
    }
  free (aux);
}

void
SortQ (TCoada * c, TFCmp cmp)
{
  TStiva *s = InitS (c->dime), *aux = InitS (c->dime);
  while (c->ic)
    {
      void *ae = malloc (c->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      ExtrQ (c, ae);
      Push (s, ae);
    }
  SortS (s, cmp);
  while (s->vf)
    {
      void *ae = malloc (c->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      Pop (s, ae);
      Push (aux, ae);
    }
  while (aux->vf)
    {
      void *ae = malloc (c->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      Pop (aux, ae);
      IntrQ (c, ae);
    }
  free (aux);
  free (s);
}

void
Afi (void *ae, FILE * fout)
{
  Paranteza *info = (Paranteza *) ae;
  fprintf (fout, "%c", info->tip);
}

void
PrintS (TStiva * s, TF Afi, FILE * fout)
{
  TStiva *aux = InitS (s->dime);
  while (s->vf)
    {
      void *ae = malloc (s->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      Pop (s, ae);
      Push (aux, ae);
    }
  fprintf (fout, "\"");
  while (aux->vf)
    {
      void *ae = malloc (s->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      Pop (aux, ae);
      Afi (ae, fout);
      Push (s, ae);
    }
  fprintf (fout, "\"\n");
  free (aux);
}

void
PrintQ (TCoada * c, TF Afi, FILE * fout)
{
  TCoada *aux = InitQ (c->dime);
  while (c->ic)
    {
      void *ae = malloc (c->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      ExtrQ (c, ae);
      IntrQ (aux, ae);
    }
  fprintf (fout, "\"");
  while (aux->ic)
    {
      void *ae = malloc (c->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      ExtrQ (aux, ae);
      Afi (ae, fout);
      IntrQ (c, ae);
    }
  fprintf (fout, "\"\n");
  free (aux);
}

TStiva *
CopyS (TStiva * s)
{
  TStiva *copy = InitS (s->dime), *aux = InitS (s->dime);
  while (s->vf)
    {
      void *ae = malloc (s->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return NULL;
	}
      void *cae = malloc (s->dime);
      if (!cae)
	{
	  printf ("eroare alocare cae!\n");
	  free (ae);
	  return NULL;
	}
      Pop (s, ae);
      memcpy (cae, ae, s->dime);
      Push (aux, ae);
      Push (copy, cae);
    }
  while (aux->vf)
    {
      void *ae = malloc (s->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return NULL;
	}
      Pop (aux, ae);
      Push (s, ae);
    }
  free (aux);
  return copy;
}

TCoada *
CopyQ (TCoada * c)
{
  TCoada *copy = InitQ (c->dime), *aux = InitQ (c->dime);
  while (c->ic)
    {
      void *ae = malloc (c->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return NULL;
	}
      void *cae = malloc (c->dime);
      if (!cae)
	{
	  printf ("eroare alocare cae!\n");
	  free (ae);
	  return NULL;
	}
      ExtrQ (c, ae);
      memcpy (cae, ae, c->dime);
      IntrQ (aux, ae);
      IntrQ (copy, cae);
    }
  while (aux->ic)
    {
      void *ae = malloc (c->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return NULL;
	}
      ExtrQ (aux, ae);
      IntrQ (c, ae);
    }
  free (aux);
  return copy;
}

int
Verifica (char a, char b)
{
  if (a == '(')
    {
      if (b == ')')
	return 1;
    }
  else if (a == '[')
    {
      if (b == ']')
	return 1;
    }
  else if (a == '{')
    {
      if (b == '}')
	return 1;
    }
  return 0;
}

void
CorrectS (TStiva * s, FILE * fout)
{
  TStiva *intors, *aux = InitS (s->dime);
  int maxl = 0, l = 0, ant = 0, ind = 0;
  char deschis[4] = "([{";
  intors = CopyS (s);
  if (!intors)
    return;
  while (intors->vf)
    {
      void *ae = malloc (s->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      Pop (intors, ae);
      ind++;
      char p = ((Paranteza *) ae)->tip;
      ((Paranteza *) ae)->id_paranteza = ind;
      if (strchr (deschis, p))
	{
	  if (!intors->vf)
	    {
	      while (aux->vf)
		Pop (aux, ae);
	      free (ae);
	    }
	  else
	    Push (aux, ae);
	}
      else
	{
	  if (aux->vf && Verifica (((Paranteza *) aux->vf->info)->tip, p))
	    {
	      Pop (aux, ae);
	      if (!aux->vf)
		l = ind - ant;
	      else
		l = ind - ((Paranteza *) aux->vf->info)->id_paranteza;
	      if (l > maxl)
		maxl = l;
	      if (!intors->vf)
		{
		  while (aux->vf)
		    Pop (aux, ae);
		}
	      free (ae);
	    }
	  else
	    {
	      ant = ind;
	      while (aux->vf)
		Pop (aux, ae);
	      free (ae);
	    }
	}
    }
  free (intors);
  free (aux);
  fprintf (fout, "%d\n", maxl);
}

void
CorrectQ (TCoada * c, FILE * fout)
{
  TCoada *copie;
  TStiva *aux = InitS (c->dime);
  int maxl = 0, l = 0, ant = 0, ind = 0;
  char deschis[4] = "([{";
  copie = CopyQ (c);
  if (!copie)
    return;
  while (copie->ic)
    {
      void *ae = malloc (c->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      ExtrQ (copie, ae);
      ind++;
      char p = ((Paranteza *) ae)->tip;
      ((Paranteza *) ae)->id_paranteza = ind;
      if (strchr (deschis, p))
	{
	  if (!copie->ic)
	    {
	      while (aux->vf)
		Pop (aux, ae);
	      free (ae);
	    }
	  else
	    Push (aux, ae);
	}
      else
	{
	  if (aux->vf && Verifica (((Paranteza *) aux->vf->info)->tip, p))
	    {
	      Pop (aux, ae);
	      if (!aux->vf)
		l = ind - ant;
	      else
		l = ind - ((Paranteza *) aux->vf->info)->id_paranteza;
	      if (l > maxl)
		maxl = l;
	      if (!copie->ic)
		{
		  while (aux->vf)
		    Pop (aux, ae);
		}
	      free (ae);
	    }
	  else
	    {
	      ant = ind;
	      while (aux->vf)
		Pop (aux, ae);
	      free (ae);
	    }
	}
    }
  free (copie);
  free (aux);
  fprintf (fout, "%d\n", maxl);
}

void
ElibS (TStiva * s)
{
  while (s->vf)
    {
      void *ae = malloc (s->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      Pop (s, ae);
      free (ae);
    }
  free (s);
}

void
ElibQ (TCoada * c)
{
  while (c->ic)
    {
      void *ae = malloc (c->dime);
      if (!ae)
	{
	  printf ("eroare alocare ae!\n");
	  return;
	}
      ExtrQ (c, ae);
      free (ae);
    }
  free (c);
}
