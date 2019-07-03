#include <stdio.h>
#include <stdlib.h>

void readlist();
void createlist();

FILE *fp;
       
int main(){
	int choose;
	printf("Press 1 for to Create List and 2 to Read from List:");
	scanf("%i", &choose);
	
	if (choose == 1) {
		createlist();
	} else if (choose == 2) {
		readlist();
	} else {
		printf("WRONG INPUT\n");
	}
	getch();
	return 0;
}

void createlist(){
	fp = fopen("test.txt", "w");
	
	char name1[30], name2[30];
	int loop;
	
	int i;
	
	printf("Number of students: ");
	scanf("%i", &loop);
	
	
		printf("Name: ");
		scanf("%s", name1);
		fprintf(fp, "%s", name1);
		
	for (i=0; i<(loop-1); i++) {
		printf("Name: ");
		scanf("%s", name2);
		fprintf(fp, "\n%s", name2);
	}
	
	fclose(fp);
}

void readlist(){
    int str;
    int present = 0;
    int absent  = 0;
    int temp;
    
    fp = fopen("test.txt", "r");
    char singleLine[150];
    
    while(!feof(fp)) {
                     fgets(singleLine, 150, fp);
    
                     puts(singleLine);
                     printf("Present?: ");
                     scanf("%i", &str);
                     temp = str;
                     
                     if ( temp == 1 ){
                        present++;
                        }
                     else {
                        absent++;
                          }
                     
                     str = 0;
                     
                     printf("\n");
                     
    }
    
    fclose(fp);  
    
    printf("Present: %i \n", present);
    printf("Absent: %i ", absent);
    
    
    getch();
}

