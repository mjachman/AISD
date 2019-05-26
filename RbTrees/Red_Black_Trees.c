

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 1        /* stala oznaczajaca kolor wezla */
#define BLACK 0      /* stala oznaczajaca kolor wezla */
#define SZER_EKR 80  /* szerokosc ekranu */
#define IL_POZ   5   /* ilosc poziomow drzewa, ktore beda wydrukowane   */
                     /* gwiazdka bedzie sygnalizowac istnienie nizszych */
                     /* poziomow                                        */

/* struktury danych do reprezentowania drzewa */
typedef struct wezel *Wskwezla; /* wskaznik na wezel drzewa  */
typedef struct wezel{
	int klucz;
	Wskwezla left, right, p;
	int kolor;
} Twezla ;  /* typ wezla */

/* drzewa z wartownikami: wezel wskazywany przez "nil" jest wartownikiem
   zastepujacym NULL; dla korzenia pole "p" ma wartosc "nil";
   pole nil->p musi byc ustawione odpowiednio w przy usuwaniu
*/
Wskwezla nil;

void nilInit(void){
/* funkcja inicjujaca nil; musi byc wywolana przed budowaniem drzewa */
  nil= (Wskwezla) malloc(sizeof(Twezla));
  nil->p = NULL;
  nil->kolor = BLACK;
  nil->left = nil->right = NULL;
}

/* ------------  implementacja ------------------------------------- */
char wydruk[IL_POZ+1][SZER_EKR];

void drukujost(Wskwezla w, int l, int p,int poziom){
       int srodek = (l+p)/2;
       if (w==nil)   return;
       wydruk[poziom][srodek]='*';
}

void drukujwew(Wskwezla w, int l, int p,int poziom){
       int srodek = (l+p)/2;
       int i,dl;
       char s[19];
       if (w==nil)    return;
       if (w->kolor==BLACK)
         dl=sprintf(s,"%d",w->klucz);
       else
	 //	        dl=sprintf(s,"\e[31m%+d\e[0m",w->klucz);
       dl=sprintf(s,"%+d",w->klucz);
       for (i=0;i<dl;i++)
         wydruk[poziom][srodek-dl/2+i]=s[i];
       if (++poziom<IL_POZ){
         drukujwew(w->left,l,srodek,poziom) ;
         drukujwew(w->right,srodek+1,p,poziom) ;
       }
       else {
         drukujost(w->left,l,srodek,poziom) ;
         drukujost(w->right,srodek+1,p,poziom) ;
       }
}

void drukuj(Wskwezla w){
  int j,i;
  for (i=0;i<=IL_POZ;i++)
    for (j=0;j<SZER_EKR;j++)
      wydruk[i][j] = ' ';
  drukujwew(w,0,SZER_EKR,0);
  for (i=0;i<=IL_POZ;i++){
      for (j=0;j<SZER_EKR;j++)
        putchar(wydruk[i][j]);
      printf("\n");
  }
}

void LeftRotate(Wskwezla *k,Wskwezla x)
{
	Wskwezla y = x->right;
	x->right = y->left;
	if(y->left != nil)
		y->left->p = x;
	y->p = x->p;
	if(x->p  == nil)
        (*k) = y;
	else if(x == x->p->left)
        x->p->left = y;
	else
        x->p->right = y;
	y->left = x;
	x->p = y;
}

void RightRotate(Wskwezla *k,Wskwezla x)
{
	Wskwezla y = x->left;
	x->left = y->right;
	if(y->right != nil)
		y->right->p = x;
	y->p = x->p;
	if(x->p == nil)
        (*k)=y;
	else if(x == x->p->right)
        x->p->right = y;
	else
	    x->p->left = y;
	y->right = x;
	x->p = y;
}
Wskwezla RBInsert(Wskwezla *k, int kluczz)
{
	Wskwezla g = malloc(sizeof(Twezla));
	g->p = nil;
	g->klucz = kluczz;
	g->left = nil;
	g->right = nil;
	Wskwezla y = nil;
	Wskwezla x = *k;
	while( x!=nil)
	{
		y=x;
		if(g->klucz<x->klucz)
			x=x->left;
		else
			x=x->right;
	}
	g->p = y;
	if(y == nil)
	    *k=g;
	else if(g->klucz<y->klucz)
		{y->left = g;}
	 else
        y->right = g;
	return g;
}

void RBinsertFixup(Wskwezla *k, int klucz)
{
	Wskwezla x = RBInsert(k,klucz);
	x->kolor = RED;
	while(x->p->kolor == RED)
	{
		if(x->p==x->p->p->left)
		{
			Wskwezla y = x->p->p->right;
			if(y->kolor == RED)
			{
				x->p->kolor = BLACK;
				y->kolor = BLACK;
				x->p->p->kolor = RED;
				x = x->p->p;
			}
			else
			{
				if(x == x->p->right)
				{
					x = x->p;
					LeftRotate(k, x);
				}
				x->p->kolor = BLACK;
				x->p->p->kolor = RED;
				RightRotate(k, x->p->p);
			}
		}
		else
		{
			Wskwezla y = x->p->p->left;
			if(y->kolor == RED)
			{
				x->p->kolor = BLACK;
				y->kolor = BLACK;
				x->p->p->kolor = RED;
				x = x->p->p;
			}
			else
			{
				if(x == x->p->left)
				{
					x = x->p;
					RightRotate(k, x);
				}
				x->p->kolor = BLACK;
				x->p->p->kolor = RED;
				LeftRotate(k, x->p->p);
			}
		}
	}
	(*k)->kolor = BLACK;
}

int czerwone(Wskwezla T)
{
    static int czer;
	if(T != nil)
	{
		czerwone(T->left);
		if(T->kolor == RED)
		    czer++;
		czerwone(T->right);
	}
    return czer;
}

int glebokoscMax(Wskwezla T)
{
	int wys1;
	int wys2;
	if(T != nil)
	{
		wys1 = glebokoscMax(T->left);
		wys2 = glebokoscMax(T->right);
		if(wys1 > wys2)
            return wys1 + 1;
		else
            return wys2 + 1;
    }
	else
        return 0;
}

int glebokoscMin(Wskwezla T)
{
    int wys1;
    int wys2;
    if(T == nil)
        return 0;
    if(T->left == nil)
        return glebokoscMin(T->right) + 1;
    if(T->right == nil)
        return glebokoscMin(T->left) + 1;
    wys1 = glebokoscMin(T->right);
    wys2 = glebokoscMin(T->left);
    if(wys1 > wys2)
        return wys2 + 1;
    else
        return wys1 + 1;
}

int main()
{
    nilInit();
    int i,x,c;

    Wskwezla korzen=nil;
    int tab[10]={5,11,21,30,19,1,8,6,5,3};
    for(i=0;i<10;i++)
	{
	    printf("RBInsert: %i\n",tab[i]);
        RBinsertFixup(&korzen, tab[i]);
   		drukuj(korzen);
   		printf("----------------------------------------------------------------------\n");
    }
    c=czerwone(korzen);
        printf("Ilosc wezlow czerwonych: %i \n",c);
        printf("Max glebokosc: %i \n",glebokoscMax(korzen));
        printf("Min glebokosc: %i",glebokoscMin(korzen));
    return 0;
}
