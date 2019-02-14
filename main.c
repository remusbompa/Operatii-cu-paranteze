/*BOMPA Remus-315CB*/
#include"TStructuri.h"

int
main (int argc, char *argv[])
{
  char *nume_in = argv[1], *nume_out = argv[2], operatie[20];
  FILE *fin = fopen (nume_in, "rt"), *fout = fopen (nume_out, "wt");
  int N, S, C, id_stiva, id_coada, i;
  fscanf (fin, "%d%d%d", &N, &S, &C);
  TStiva **s = (TStiva **) calloc (S, sizeof (TStiva *));
  if (!s)
    {
      printf ("eroare la alocare S stive!\n");
      return 0;
    }
  for (i = 0; i < S; i++)
    s[i] = InitS (sizeof (Paranteza));
  TCoada **c = (TCoada **) calloc (C, sizeof (TCoada *));
  if (!c)
    {
      printf ("eroare la alocare C cozi!\n");
      return 0;
    }
  for (i = 0; i < C; i++)
    c[i] = InitQ (sizeof (Paranteza));
  while (N > 0)
    {
      N--;
      if (fscanf (fin, "%s", operatie) != 1)
	{
	  printf ("eroare citire operatie!\n");
	  return 0;
	}
      if (!strcmp (operatie, "push"))
	{
	  Paranteza *p = (Paranteza *) malloc (sizeof (Paranteza));
	  if (!p)
	    {
	      printf ("eroare alocare paranteza!\n");
	      return 0;
	    }
	  fscanf (fin, "%d%d %c", &id_stiva, &p->id_paranteza, &p->tip);
	  if (!Push (s[id_stiva], p))
	    return 0;
	}
      else if (!strcmp (operatie, "intrq"))
	{
	  Paranteza *p = (Paranteza *) malloc (sizeof (Paranteza));
	  if (!p)
	    {
	      printf ("eroare alocare paranteza!\n");
	      return 0;
	    }
	  fscanf (fin, "%d%d %c", &id_coada, &p->id_paranteza, &p->tip);
	  if (!IntrQ (c[id_coada], p))
	    return 0;
	}
      else if (!strcmp (operatie, "pop"))
	{
	  Paranteza *p = (Paranteza *) malloc (sizeof (Paranteza));
	  if (!p)
	    {
	      printf ("eroare alocare paranteza!\n");
	      return 0;
	    }
	  fscanf (fin, "%d", &id_stiva);
	  Pop (s[id_stiva], p);
	  free (p);
	}
      else if (!strcmp (operatie, "extrq"))
	{
	  Paranteza *p = (Paranteza *) malloc (sizeof (Paranteza));
	  if (!p)
	    {
	      printf ("eroare alocare paranteza!\n");
	      return 0;
	    }
	  fscanf (fin, "%d", &id_coada);
	  ExtrQ (c[id_coada], p);
	  free (p);
	}
      else if (!strcmp (operatie, "sorts"))
	{
	  fscanf (fin, "%d", &id_stiva);
	  SortS (s[id_stiva], cmp);
	}
      else if (!strcmp (operatie, "sortq"))
	{
	  fscanf (fin, "%d", &id_coada);
	  SortQ (c[id_coada], cmp);
	}
      else if (!strcmp (operatie, "prints"))
	{
	  int i;
	  for (i = 0; i < S; i++)
	    PrintS (s[i], Afi, fout);
	}
      else if (!strcmp (operatie, "printq"))
	{
	  int i;
	  for (i = 0; i < C; i++)
	    PrintQ (c[i], Afi, fout);
	}
      else if (!strcmp (operatie, "corrects"))
	{
	  fscanf (fin, "%d", &id_stiva);
	  CorrectS (s[id_stiva], fout);
	}
      else if (!strcmp (operatie, "correctq"))
	{
	  fscanf (fin, "%d", &id_coada);
	  CorrectQ (c[id_coada], fout);
	}
      else
	{
	  printf ("Operatie invalida!\n");
	  return 0;
	}
    }
  while (S > 0)
    {
      S--;
      ElibS (s[S]);
    }
  while (C > 0)
    {
      C--;
      ElibQ (c[C]);
    }
  free (s);
  free (c);
  fclose (fin);
  fclose (fout);
  return 0;
}
