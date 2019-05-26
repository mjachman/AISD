#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Lista{
  char* klucz;
  struct Lista *nastepny;
  struct Lista *poprzedni;
}Lista;

void WSTAW(Lista **poczatek, char* klucz){

  Lista *nowy=(Lista *)malloc(sizeof(Lista));
  nowy->klucz = klucz;
  nowy->nastepny = *poczatek;
  nowy->poprzedni = NULL;
  *poczatek = nowy;
}

void DRUKUJ(Lista *element){
  while(element!=NULL){
  	  printf("%s ", element->klucz) ;
    	element=element->nastepny;
    }
  printf("\n");
}

Lista* SZUKAJ(Lista* element, char* klucz){

  while(element!=NULL){
    if(element->klucz == klucz){
      printf("\nZnaleziono '%s' \n", klucz);
      return element;
    }
    element=element->nastepny;
  }
  printf("\nBrak szukanego elementu\n");
  return NULL;
}

void USUN(Lista** poczatek, char* klucz){

  Lista* pierwszy = *poczatek;
  Lista* poprzedni;
  Lista* tmp = *poczatek;

  while(tmp != NULL){

      if(tmp->klucz == klucz){

        if(tmp == *poczatek){
          *poczatek = tmp->nastepny;
          return;
        }
        else{
          poprzedni->nastepny = tmp->nastepny;
          return;
        }
      }
      else{
        poprzedni=tmp;
        tmp = tmp->nastepny;
      }
  }

}

void SCAL(Lista** Lista1, Lista** Lista2, Lista** Lista3){
  Lista *tmp;
  *Lista3 = *Lista1;//
  tmp = *Lista3;
  while(tmp->nastepny != NULL){
    tmp=tmp->nastepny;
  }
  tmp->nastepny=*Lista2;
  (*Lista2)->poprzedni = tmp;
}

Lista* BEZPOWTORZEN(Lista* poczatek){
  Lista *element1, *element2, *duplikat, *ListaBezPowtorzen;
  ListaBezPowtorzen = poczatek;
  element1 = poczatek;

  while(element1 != NULL && element1->nastepny != NULL)
  {    element2 = element1;
    while(element2->nastepny != NULL)
    {
      if(element1->klucz == element2->nastepny->klucz)
      {
        duplikat = element2->nastepny;
        element2->nastepny = element2->nastepny->nastepny;
      }
      else
      {
        element2 = element2->nastepny;
      }
    }
    element1 = element1->nastepny;
  }
  return ListaBezPowtorzen;
}

void KASUJ(Lista* poczatek){
  Lista *poprzedni;
	poprzedni=poczatek;
	poczatek=poczatek->nastepny;

	while(poczatek!=NULL){
		poprzedni=poczatek;
		poczatek=poczatek->nastepny;
	}
}
int main(){
Lista *Lista1 = NULL;
Lista *Lista2 = NULL;
Lista *Lista3 = NULL;

  WSTAW(&Lista1, "jeden");
  WSTAW(&Lista1, "dwa");
  WSTAW(&Lista1, "trzy");
  WSTAW(&Lista1, "cztery");
  WSTAW(&Lista1, "piec");
  printf("Lista1 : \n");
  DRUKUJ(Lista1);
  WSTAW(&Lista2, "trzy");
  WSTAW(&Lista2, "dwa");
  WSTAW(&Lista2, "jeden");
  printf("\nLista2: \n");
  DRUKUJ(Lista2);
  SZUKAJ(Lista1, "dwa");
  SZUKAJ(Lista2, "cztery");
  USUN(&Lista2, "trzy");
  printf("\nLista po usunieciu 'trzy':\n");
  DRUKUJ(Lista1);
  printf("\nScalenie list : \n");
  SCAL(&Lista1, &Lista2, &Lista3);
  DRUKUJ(Lista3);
  Lista* bezpowtorzen;
  bezpowtorzen = BEZPOWTORZEN(Lista3);
  printf("\nLista bez powtorzen:\n");
  DRUKUJ(bezpowtorzen);
  KASUJ(Lista3);
  DRUKUJ(Lista3);
  return 0;
}
