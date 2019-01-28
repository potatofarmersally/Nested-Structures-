/*
 * assignment5SallyHo.c
 *
 *  Created on: May 7, 2018
 *      Author: Sally Ho
 */

#include <stdio.h>
#include <string.h>

struct item{
	char name[20];
	int quantity;
	double price;
	double combined;
} ;

typedef struct item Item;

struct customer {
	char custName[30];
	Item items[10];
	int numberOfItems;
	double totalCost;
};

typedef struct customer Customer;
/*
 * PROTOTYPE: reads the data from input file
 */
int readAndProcessFile(FILE*, Customer[], int*);
/*
 * PROTOTYPE: generates the output file
 */
void generatehw5Time(Customer[], int, FILE*);
/*
 * PROTOTYPE: sorts customers items based on total value of item
 */
void bubbleSort(Customer[], int);
/*
 * PROTOTYPE: sorts customers based on value of purchases
 */
void bubbleSort2(Item[], int);
/*
 * PROTOTYPE: generates output file to money
 */
void generatehw5Money(Customer[], int, FILE*);


/*
 * Main: executes everything
 */
int main() {
	FILE *inputFile = fopen("hw5input.txt", "r");
	FILE *timeFile = fopen("hw5Time.txt", "wt");
	FILE *moneyFile = fopen("hw5Money.txt", "wt");
	int hasName = 1;
	int i;
	int totalCount = 0;
	Customer theCustomer[21];
	totalCount = readAndProcessFile(inputFile, theCustomer, &hasName);
	readAndProcessFile(inputFile, theCustomer, &hasName);
	generatehw5Time(theCustomer, totalCount, timeFile);
	bubbleSort(theCustomer, totalCount);
	for(i = 0; i < totalCount; i++) {
		bubbleSort2(theCustomer[i].items, totalCount);
	}
	generatehw5Money(theCustomer, totalCount, moneyFile);
	fclose(inputFile);
	fclose(timeFile);
	fclose(moneyFile);
	return 0;
}

/*
 * reads the data from the input file
 */
int readAndProcessFile(FILE *inputFile, Customer theCustomer[],
		int *hasName) {
	int arrayCount = 0;
	int i = 0;
	int scan = 0;
	int itemIndex = 0;
	Customer tempCustomer;
	for(scan = 0; scan < 20 && fscanf(inputFile, "%s %d %s $%lf",
			tempCustomer.custName, &tempCustomer.items->quantity,
			tempCustomer.items->name,
			&tempCustomer.items->price) != EOF; scan++) {
		for(i = 0; i < 20; i++) {
			if(strcmp(theCustomer[i].custName,
					tempCustomer.custName) == 0) {
				*hasName = 0;
				//copy over customer's name
				//if the item names not same, increment item count.
				theCustomer[i].numberOfItems++;
				itemIndex = theCustomer[i].numberOfItems;
				strcpy(theCustomer[i].items[itemIndex].name,
						tempCustomer.items->name);
				//copy price over
				theCustomer[i].items[itemIndex].price =
						tempCustomer.items->price;
				//copy the quantity of each item over
				theCustomer[i].items[itemIndex].quantity =
						tempCustomer.items->quantity;
			}
		}
		if(*hasName == 1) {
			tempCustomer.numberOfItems = 0;
			theCustomer[arrayCount] = tempCustomer;
			arrayCount++;
		}
		*hasName = 1;
	}
	return arrayCount;
}
/*
 * Generates the info to hw5Time.txt
 */
void generatehw5Time(Customer theCustomer[], int totalCount,
		FILE *timeFile) {
	int i = 0;
	int j = 0;
	for(i = 0; i < totalCount; i++) {
		fprintf(timeFile, "Customer: %s\n        Orders: \n",
				theCustomer[i].custName);
		for(j = 0; j < theCustomer[i].numberOfItems + 1; j++) {
			fprintf(timeFile, "                %-15s%3d%9.2lf%11.2lf\n",
					theCustomer[i].items[j].name,
					theCustomer[i].items[j].quantity,
					theCustomer[i].items[j].price,
					theCustomer[i].items[j].quantity
					* theCustomer[i].items[j].price);
					theCustomer[i].items[j].combined =
							theCustomer[i].items[j].quantity
							* theCustomer[i].items[j].price;
					theCustomer[i].totalCost +=
							theCustomer[i].items[j].quantity
							* theCustomer[i].items[j].price;
		}
			fprintf(timeFile, "%46s", "Total: ");
			fprintf(timeFile, "%.2lf\n",
					theCustomer[i].totalCost);
	}
}
/*
 * Generates the output to hw5Money.txt
 */
void generatehw5Money(Customer theCustomer[], int totalCount,
		FILE *moneyFile) {
	int i, j;
	for(i = 0; i < totalCount; i++) {
		fprintf(moneyFile, "%s, Total Order = %.2lf\n",
				theCustomer[i].custName, theCustomer[i].totalCost);
		for(j = 0; j < theCustomer[i].numberOfItems + 1; j++) {
			fprintf(moneyFile, "%s %d %.2lf, Item Value: %.2lf\n",
				theCustomer[i].items[j].name,
				theCustomer[i].items[j].quantity,
				theCustomer[i].items[j].price,
				theCustomer[i].items[j].combined);
		}
	}

}
/*
 * Sorts the customers items based on total value of all purchases
 */
void bubbleSort(Customer theCustomer[], int totalCount) {
	Customer c;
	int topBubble, bubbles, notSorted = 1;
	for(topBubble = 0; topBubble < totalCount && notSorted;
			topBubble++) {
		for(bubbles = totalCount - 1, notSorted = 0;
				bubbles > topBubble; bubbles--) {
			if(theCustomer[bubbles].totalCost >
				theCustomer[bubbles - 1].totalCost) {
				c = theCustomer[bubbles];
				theCustomer[bubbles] = theCustomer[bubbles - 1];
				theCustomer[bubbles - 1] = c;
				notSorted = 1;
			}
		}

	}
}
/*
 * Sorts items based on value
 */
void bubbleSort2(Item theItem[], int totalCount) {
	Item i;
	int topBubble, bubbles, notSorted = 1;
	for(topBubble = 0; topBubble < totalCount && notSorted;
			topBubble++) {
			for(bubbles = totalCount - 1, notSorted = 0;
					bubbles > topBubble ;
					bubbles--) {
				if(theItem[bubbles].combined >
					theItem[bubbles - 1].combined) {
					i = theItem[bubbles];
					theItem[bubbles] = theItem[bubbles - 1];
					theItem[bubbles - 1] = i;
					notSorted = 1;
				}
			}

		}
}

