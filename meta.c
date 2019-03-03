#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

char *VOWELS="AEIOU",
     *FRONTV="EIY",
     *VARSON="CSPTG";

void metaphone(name,metaph,metalen)
char *name, *metaph;
int metalen;
{

int  i,j,new, silent,L,hard;
char *ename, *tmpstr,symb;
char two[3];

ename=malloc(strlen(name) * sizeof(char));

memset(ename, '\0', strlen(name));
memset(metaph, '\0', strlen(metaph));

j=0;

for (i=0;name[i]!='\0';i++)
{
    name[i]=toupper(name[i]);

    if (isalnum(name[i]))
    {
       ename[j]=name[i];
       j++;
    }
}

ename[j]='\0';

if (strlen(ename) == 0)
{
   free(ename);
   return;
}

/* realloc(ename, strlen(ename), sizeof(char)); */

strncpy(two,ename,2);

if ((!strncmp(two,"PN",2)) || (!strncmp(two,"AE",2)) ||
(!strncmp(two,"KN",2))
 || (!strncmp(two,"GN",2)) || (!strncmp(two,"WR",2)) ||
(!strncmp(two,"AE",2)))
{
   strcpy(ename,&ename[1]);
}


if  (ename[0] == 'X')
{
   tmpstr=strdup(ename);
   ename[0] = 'S';
   strcpy(&ename[1],&tmpstr[1]);
   free(tmpstr);
}

if (!strncmp(two,"WH",2))
{
   tmpstr=strdup(ename);
   ename[0] = 'W';
   strcpy(&ename[1],&tmpstr[2]);
   free(tmpstr);
}

L=strlen(ename);

for (i=0;((strlen(metaph) < metalen) && (i < L));i++)
{
   symb=ename[i];

   if ((symb != 'C') && (i > 0) && (ename[i-1] == symb))
      new=0;
   else
      new=1;

   if (new == 1)
   {
      if ((strrchr(VOWELS,symb) != (char *)NULL) && (i == 0))
         metaph[0]=symb;

      else if ( symb == 'B')
      {
         if (( i == (L -1)) && (ename[i-1] == 'M'))
            silent=1;
         else
            silent=0;

         if (!silent)
            strncat(metaph,&symb,1);
      }
      else if ( symb == 'C')
      {
         if (!((i > 0) && (ename[i-1] == 'S') && ((i+1) <= (L-1))
            && (strrchr(FRONTV,ename[i+1]) != (char *)NULL)))
         {
            if (((i+2) <= (L-1)) && (ename[i+1] == 'I') && (ename[i+2] ==
'A'))
               strncat(metaph,"X",1);
            else
            {
               if ((i < (L-1)) && (strrchr(FRONTV,ename[i+1]) != (char
*)NULL))
                  strncat(metaph,"S",1);
               else
               if ((i >0) && (i < (L-1)) && (ename[i+1] == 'H')
                && (ename[i-1] == 'S'))
                  strncat(metaph,"K",1);
               else
               if ((i < (L-1)) && (ename[i+1] == 'H'))
                  if ((i == 0) && ((i+2) <= (L-1))
                  && (strrchr(VOWELS,ename[i+2]) == (char *)NULL))
                      strncat(metaph,"K",1);
                  else
                      strncat(metaph,"X",1);
               else
                  strncat(metaph,"K",1);
            }
         }
      }
      else if ( symb == 'D')
      {
         if (((i+2) <= (L-1)) && (ename[i+1] == 'G')
           && (strrchr(FRONTV,ename[i+2]) != (char *)NULL))
             strncat(metaph,"J",1);
         else
             strncat(metaph,"T",1);
      }
      else if ( symb == 'G')
      {
         if ((i < (L-1)) && ( ename[i+1] == 'H')
          && (strrchr(VOWELS,ename[i+2]) == (char *)NULL))
             silent=1;
         else
             silent=0;

         if ((i > 0)
         && (((i+1) == (L-1)) || ((ename[i+1] == 'N')
                               && (ename[i+2] == 'E')
                               && (ename[i+3] == 'D')
                               && ((i+3) == (L-1))))
         && (ename[i+1] == 'N'))
            silent=1;

         if ((i > 0) && ((i+1) <= (L-1)) && (ename[i-1] == 'D')
          && (strrchr(FRONTV,ename[i+1]) != (char *)NULL))
            silent=1;

         if ((i > 0) && (ename[i-1] == 'G'))
            hard=1;
         else
            hard=0;

         if (!silent)
            if ((i < (L-1))
             && (strrchr(FRONTV,ename[i+1]) != (char *)NULL)
             && (!hard))
               strncat(metaph,"J",1);
            else
               strncat(metaph,"K",1);
      }
      else if ( symb == 'H')
      {
         if (!(( i == (L-1)) || ((i > 0)
                             && (strrchr(VARSON,ename[i-1]) != (char
*)NULL))))
             if (strrchr(VOWELS,ename[i+1]) != (char *)NULL)
                 strncat(metaph,"H",1);
      }
      else if ((symb == 'F')
            || (symb == 'J')
            || (symb == 'L')
            || (symb == 'M')
            || (symb == 'N')
            || (symb == 'R'))
      {
               strncat(metaph,&symb,1);
      }
      else if ( symb == 'K')
      {
         if ((i > 0) && (ename[i-1] != 'C'))
            strncat(metaph,"K",1);
         else
         if (i == 0)
            metaph[0]='K';
      }

      else if ( symb == 'P')
      {
         if ((i < (L-1)) && (ename[i+1] == 'H'))
            strncat(metaph,"F",1);
         else
            strncat(metaph,"P",1);
      }
      else if ( symb == 'Q')
      {
         strncat(metaph,"K",1);
      }
      else if ( symb == 'S')
      {
         /**
         if ((i > 0) && ((i+2) <= (L-1)) && (ename[i+1] == 'I')
         && (ename[i+2] == 'O') || (ename[i+2] == 'A'))
         **/
         if ((i >= 0) && ((i+2) <= (L-1)) && (((ename[i+1] == 'I')
         && (ename[i+2] == 'O')) || (ename[i+2] == 'A')))
            strncat(metaph,"X",1);
         else
         if (( i < (L-1)) && (ename[i+1] == 'H'))
            strncat(metaph,"X",1);
         else
            strncat(metaph,"S",1);
      }
      else if ( symb == 'T')
      {
         /*****
         if ((i > 0) && ((i+2) <= (L-1)) && (ename[i+1] == 'I')
         && ((ename[i+2] == 'O') || (ename[i+2] == 'A')))

         if ((i > 0) && ((i+2) <= (L-1)) && (((ename[i+1] == 'I')
         && (ename[i+2] == 'O')) || (ename[i+2] == 'A')))
            strncat(metaph,"X",1);
         if ((i > 0) && ((i+2) < (L-1)) && (((ename[i+1] == 'I')
         && (ename[i+2] == 'O')) || (ename[i+2] == 'A')))
            strncat(metaph,"X",1);
         *****/
         if ((i >= 0) && ((i+2) <= (L-1)) && (((ename[i+1] == 'I')
         && (ename[i+2] == 'O')) || (ename[i+2] == 'A')))
            strncat(metaph,"X",1);
         else
         if (( i < (L-1)) && (ename[i+1] == 'H'))
         {
            if (!((i > 0) && (ename[i-1] == 'T')))
               strncat(metaph,"O",1);
         }
         else if (!((ename[i+1] == 'C') && (ename[i+2] == 'H')))
                 strncat(metaph,"T",1);
      }
      else if ( symb == 'V')
      {
          strncat(metaph,"F",1);
      }
      else if ((symb == 'W') || (symb == 'Y'))
      {
         if (( i < (L-1)) && (strrchr(VOWELS,ename[i+1]) != (char *)NULL))
            strncat(metaph,&symb,1);
      }
      else if ( symb == 'X')
      {
          if (strlen(metaph) < (metalen-1))
             strncat(metaph,"KS",2);
          else
             strncat(metaph,"K",1);
      }
      else if ( symb == 'Z')
      {
          strncat(metaph,"S",1);
      }
   }
}
free(ename);
return;

}


int main()

{

  char name[30], metaph[8];
  int metalen=6;

  printf("Please enter metaphone size : ");
  scanf("%d",&metalen);
  fflush(stdin);

  if (metalen==0)
     exit(1);

loop:
  memset(metaph,'\0',sizeof(metaph));
  memset(name,'\0',sizeof(name));

  printf("Please enter name: ");
  gets(name);

  if (!strcmp(name,""))
     exit(0);

  metaphone(name,metaph,metalen);

printf( "Metaphone code is : %-.*s\n", metalen, metaph);
  /* printf( "Metaphone code is : %s\n", metaph);*/
/*
  printf("%s\n", metaph);
*/

  goto loop;

}


