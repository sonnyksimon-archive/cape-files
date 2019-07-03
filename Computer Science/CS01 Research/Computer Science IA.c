#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct inventory { // Inventory data and file locations are grouped together in the structure.
	FILE *pointer, *pointer2;
	int tempint, tempint2;
	float tempfloat, tempfloat2;
	char *output;
	char barcode[15];
	char label[50];
	float price;
	char tempchar[100];
	size_t size;
};

void Locate(); // The function prototypes
void Append();
void Display();
void Delete();
void Search();
void Stocks();
void DataStore(float price);
void IncomeCalculator();

char barcodetest[] = "MGSI";
char choice[100];

int main() {
	puts("MATTHEW'S GROCERY STORE INVENTORY\n");

	Locate(); // Loads file

	puts("\nINVENTORY OPTIONS\n"); // Prompts the user to input their choice.
	puts("a = Append/Create inventory\n");
	puts("b = Display inventory\n");
	puts("c = Delete inventory\n");
	puts("d = Search inventory\n");
	puts("e = Calculate stocks\n");
	puts("f = Income Calculator\n");
	printf("Choice: ");
	scanf("%s", choice);
	printf("\n");

	int error = strlen(choice);

	if(error>1) { // Checks if userinput is greater than 1 character and if input IS a character.
		puts("Error parsing data. Check input.\n");
		exit(0);
	} else if(choice[0] == 'a') { // Takes the first character of string as input.
		Append();
	} else if(choice[0] == 'b') {
		Display();
	} else if(choice[0] == 'c') {
		Delete();
	} else if(choice[0] == 'd') {
		Search();
	} else if(choice[0] == 'e') {
		Stocks();
	} else if(choice[0] == 'f') {
		IncomeCalculator();
	} else {
		puts("Error parsing data. Check input.\n");
		exit(0);
	}

	printf("Continue(y)?:");
	scanf("%s", choice);

	error = strlen(choice);

	if(error>1) {
		puts("Wrong input.");
		exit(0);
	}

	if(choice[0] == 'y'|| choice[0] == 'Y') {	// Loops the program.
		system("cls");
		main();
	}

	return 0;
}

void Locate() {
	struct inventory locate;

	if((locate.pointer=fopen("database.dat", "rb"))==NULL) // Checks if file exists already.
		puts("There is no file.");
	else
		puts("Successfully located file.");

	fclose(locate.pointer);
	return;
}

void Append() {
	struct inventory append;

	printf("8-Digit Barcode#(MGSI----): ");		// Prompts the user to input data.
	scanf("%s", append.barcode);
	printf("\n");

	append.tempint = strlen(append.barcode);

	if ((strncmp(append.barcode, barcodetest, 4))||(append.tempint != 8)) {
		puts("Wrong input.");
		exit(0);
	}

	getchar();	// Consumes the newline character that is stored in the input buffer.
	printf("Name: ");
	gets(append.label);
	printf("\n");
	printf("Price: $");
	scanf("%f", &append.price);
	printf("\n");

	if(append.price==0||append.price<0) {
		puts("Wrong input.");
		exit(0);
	}

	append.pointer = fopen("database.dat", "ab");	// Writes user input to file.
	fprintf(append.pointer, "%s", append.barcode);
	printf("Copied [%s]", append.barcode);
	fprintf(append.pointer, " / %.2f", append.price);
	printf(", [%.2f]", append.price);
	fprintf(append.pointer, " / %s\n", append.label);
	printf(" and [%s].", append.label);
	fclose(append.pointer);
	printf("\n\n");

	DataStore(append.price); // Calls the function DataStore() to store prices for stock calculation.

	return;
}

void Display() {
	struct inventory display;

	if((display.pointer = fopen("database.dat", "rb"))==NULL) {
		puts("There is no file.\n");
	} else {
		fseek(display.pointer, 0L, SEEK_END);  // Takes the seeker to the end of the file.
		display.tempint = ftell(display.pointer); // Stores the position of the seeker in a pointer.
		fseek(display.pointer, 0L, SEEK_SET);  // Brings the seeker back to start of the program.

		display.output = malloc(display.tempint+1);
		display.size = fread(display.output, 1, display.tempint, display.pointer);
		display.output[display.size] = 0;

		printf("Format: ( Barcode Number / Price($) / Label )\n%s\n", display.output); // Prints the entire file onto the screen.

		free(display.output); // Frees the memory allocated for the buffer.
	}

	fclose(display.pointer);
	return;
}

void Delete() {
	remove("database.dat");
	remove("price.dat"); // Deletes the two files used in the program.
	puts("Successfully deleted file(s).\n");
	return;
}

void Search() {
	struct inventory search;

	if((search.pointer = fopen("database.dat", "rb"))==NULL) {
		puts("There is no file.\n");
	} else {
		getchar();
		printf("8-Digit Barcode#(MGSI----):");
		gets(search.barcode);

		search.tempint = strlen(search.barcode);

		if ((strncmp(search.barcode, barcodetest, 4))||(search.tempint != 8)) { // Checks for MGSI or string length that is not 8 characters.
			puts("Wrong input.");
			exit(0);
		}

		while(!feof(search.pointer)) {
			fgets(search.tempchar, 100, search.pointer);
			search.output = strstr(search.tempchar, search.barcode);

			if(search.output == NULL) { // Loops until the record is found.
				puts("Not found.");
			} else {
				puts("Found record.");
				puts(search.tempchar);
				return;
			}
		}
	}
	fclose(search.pointer);
	return;
}

void DataStore(float price) {
	struct inventory data;

	if((data.pointer = fopen("price.dat", "rb"))==NULL) {
		fclose(data.pointer);
		data.pointer = fopen("price.dat", "wb");
		fprintf(data.pointer, "%.2f %d", price, 1); // Writes initial input to create the file.
		fclose(data.pointer);
	} else {
		fscanf(data.pointer, "%f %d", &data.tempfloat, &data.tempint); // Recalls stock information.
		price += data.tempfloat;
		data.tempint++;
		fclose(data.pointer);
		data.pointer = fopen("price.dat", "wb");
		fprintf(data.pointer, "%.2f %d", price, data.tempint);
		fclose(data.pointer);
	}
	return;
}

void Stocks() { // Calculates the budget information needed.
	struct inventory stocks;
	float budget, income;

	printf("Current Budget: $");
	scanf("%f", &budget);
	if(budget==0) {
		puts("Wrong input.");
		exit(0);
	}

	printf("\n");

	printf("Total Income: $");
	scanf("%f", &income);
	if(income==0) {
		puts("Wrong input.");
		exit(0);
	}

	printf("\n");

	stocks.pointer = fopen("price.dat", "rb");
	fscanf(stocks.pointer, "%f %d", &stocks.price, &stocks.tempint);
	printf("Total items: %d\n", stocks.tempint);
	printf("Total Inventory Price: $%.2f\n", stocks.price);
	fclose(stocks.pointer);

	printf("Total Budget: $%.2f\n", budget+=stocks.price);
	printf("Old Budget: $%.2f\n\n", budget-=income);

	return;
}

void IncomeCalculator() { // Calculates income from user input.
	int i, itemssold;
	float current_price, total_price = 0;

	printf("Items Sold: ");
	scanf("%i", &itemssold);

	if(itemssold==0) {
		puts("Wrong input.");
		exit(0);
	}

	printf("\n");
	itemssold++;

	for(i=1; i<itemssold; i++) { // Loops for each item sold.
		printf("Price of item %i: $", i);
		scanf("%f", &current_price);

		if(current_price==0) {
			puts("Wrong input.");
			exit(0);
		}

		total_price+=current_price;
		printf("\n");
	}

	printf("Total Income: $%.2f", total_price);
	puts("\n");
	return;
}
