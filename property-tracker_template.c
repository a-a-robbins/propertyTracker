#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct prop_def
{
  int numProps; 
  char type[51]; 
  double rent;
  double repair;
  int numBeds;
  int numBaths;

};
typedef struct prop_def prop;

int readProps(FILE *ifp, prop O[]);
void printProps(prop O[], int num); //for testing
double totalIncome(prop O[], int num);
double totalCost(prop O[], int num);
double pricePerBed(prop O[], int num);
int numHouses(prop O[], int num);
double avgPropertyPrice(prop O1[], prop O2[], int num1, int num2);
void finalPrintProps(prop O1[], prop O2[], int num1, int num2); 


int main(int argc, char *argv[])
{  
  prop Owner1[51]; 
  prop Owner2[51]; 
  FILE *ifp1 = NULL; 
  FILE *ifp2 = NULL; 

  if(argc == 3)
  {
    ifp1 = fopen(argv[1], "r");    
      if(ifp1 == NULL)
        {
          printf("\nWhoops, looks like %s didn't open properly :( Exiting...\n", argv[1]); 
          exit(1); 
        } 

    ifp2 = fopen(argv[2], "r");   
      if(ifp2 == NULL)
      {
        printf("\nWhoops, looks like %s didn't open properly :( Exiting...\n", argv[2]); 
        exit(1); 
      }     
  }
  else
  {
    printf("\nInvalid syntax, please enter: fileName1 fileName2\n"); 
    exit(1); 
  }

  int numProps1 = readProps(ifp1, Owner1);
  int numProps2 = readProps(ifp2, Owner2); 

  finalPrintProps(Owner1, Owner2, numProps1, numProps2); 

  //printProps(Owner1, numProps1); 
  //printProps(Owner2, numProps2); 
 
	return 0;
}

int readProps(FILE *ifp, prop O[])
{
  int numProps; 

  fscanf(ifp, "%d", &numProps); 

  for(int i=0; i < numProps; i++)
  {
    fscanf(ifp, "%s", O[i].type);
    fscanf(ifp, "%lf", &O[i].rent); 
    fscanf(ifp, "%lf", &O[i].repair); 
    fscanf(ifp, "%d", &O[i].numBeds); 
    fscanf(ifp, "%d", &O[i].numBaths); 
  }
  fclose(ifp); 

  return numProps; 
}

void printProps(prop O[], int num)
{
  printf("\n"); 
  printf("numProps: %d\n\n", num); 

  for(int i = 0; i < num; i++)
  {
    printf("type: %s\n", O[i].type); 
    printf("rent: %.2f\n", O[i].rent); 
    printf("repair: %.2f\n", O[i].repair); 
    printf("numBeds: %d\n", O[i].numBeds); 
    printf("numBaths: %d\n", O[i].numBaths); 
    printf("\n");
  }
  printf("total income: %.2f\n", totalIncome(O, num)); 
  printf("total cost: %.2f\n", totalCost(O, num)); 
  printf("price per bed: %.2f\n", pricePerBed(O, num)); 
  printf("num houses owned: %d\n", numHouses(O, num));
  printf("\n");
}

double totalIncome(prop O[], int num)
{
  double totalIncome = 0; 

  for(int i = 0; i < num; i++)
  {
    totalIncome = (totalIncome + O[i].rent); 
  }
  
  return totalIncome; 
}

double totalCost(prop O[], int num)
{
  double totalCost = 0; 

  for(int i = 0; i < num; i++)
  {
    totalCost = (totalCost + O[i].repair); 
  }

  return totalCost; 
}

double pricePerBed(prop O[], int num)
{
  int totalBeds = 0; 
  
  for(int i = 0; i < num; i++)
  {
    totalBeds = (totalBeds + O[i].numBeds); 
  }

  double pricePerBed = totalIncome(O, num) / totalBeds; 

  return pricePerBed;
}

int numHouses(prop O[], int num)
{
  int numHouses = 0; 

  for(int i = 0; i < num; i++)
  {
    if(strcmp(O[i].type, "house") == 0)
    {
      numHouses++; 
    }    
  }
  return numHouses; 
}

double avgPropertyPrice(prop O1[], prop O2[], int num1, int num2)
{
  double avgPrice = (totalIncome(O1, num1) + (totalIncome(O2, num2)))/(num1 + num2); 

  return avgPrice; 
}

void finalPrintProps(prop O1[], prop O2[], int num1, int num2)
{
  printf("Total income Owner1: $%.2f\n", totalIncome(O1, num1));
  printf("Total cost Owner2: $%.2f\n", totalCost(O2, num2));
  printf("Average price per bedroom Owner1: $%.2f\n", pricePerBed(O1, num1)); 
  printf("Average price per bedroom Owner2: $%.2f\n", pricePerBed(O2, num2)); 
  printf("# of Houses Owner1: %d\n", numHouses(O1, num1)); 
  printf("# of Houses Owner2: %d\n", numHouses(O2, num2));
  printf("Average price of all properties: $%.2f\n", avgPropertyPrice(O1, O2, num1, num2));   
  
} 


