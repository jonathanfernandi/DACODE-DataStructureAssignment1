#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 25

int no = 0;

struct Pet {
	char name[31], DoB[11], gender[7], age[5];
	int weight;
	
	Pet *prev, *next;
} *head[SIZE], *tail[SIZE];

Pet *newPet(char *name, char *DoB, char *age, char *gender, int weight) {
	Pet *pet = (Pet*)malloc(sizeof(Pet));
	strcpy(pet->name, name);
	strcpy(pet->DoB, DoB);
	strcpy(pet->age, age);
	strcpy(pet->gender, gender);
	pet->weight = weight;
	
	pet->prev = pet->next = NULL;
	
	return pet;
}

int hash(char *name) {
	int len = strlen(name), sum = 0;
	for(int i = 0; i < len; i++) {
		sum += name[i];
	}
	
	return (sum % SIZE);
}

void add() {
	system("cls");
	
	char name[31];
	int len = 0;
	while((len < 5) || (len > 30)) {
		printf(" Insert pet name [5-30 characters] : ");
		scanf("%[^\n]", name); getchar();
		
		len = strlen(name);
		if((len < 5) || (len > 30)){
			puts(" Pet name length must be between 5-30 characters!");
		}
	}
	
	char DoB[31];
	while(1) {
		printf(" Insert pet Date of Birth [dd-mm-yyyy] : ");
		scanf("%[^\n]", DoB); getchar();
		len = strlen(DoB);
		
		if(len == 10) {
			if((DoB[2] == '-') && (DoB[5] == '-')) {
				if((((DoB[0] >= '0') && (DoB[0] <= '2')) && ((DoB[1] >= '0') && (DoB[1] <= '9'))) || ((DoB[0] == '3') && (DoB[1] == '0'))) {
					if(((DoB[3] == '0') && ((DoB[4] >= '0') && (DoB[4] <= '9'))) || ((DoB[3] == '1') && ((DoB[4] >= '0') || (DoB[4] <= '2')))) {
						if(((DoB[6] >= '0') && (DoB[6] <= '9')) && ((DoB[7] >= '0') && (DoB[7] <= '9')) && ((DoB[8] >= '0') && (DoB[8] <= '9')) && ((DoB[9] >= '0') && (DoB[9] <= '9'))) {
							break;
						}
					}
				}
			}
		}
		puts(" Please input a valid date!");
	}
	
	char age[5];
	int validateAge = 0;
	while(!validateAge) {
		printf(" Insert pet age [must be a number] : ");
		scanf("%s", age); getchar();
		
		len = strlen(age);
		for(int i = 0; i < len; i++) {
			if((age[i] < '0') || (age[i] > '9')) {
				puts(" Input must be a number!");
				break;
			}
			
			if(!validateAge && (i == (len - 1))) {
				validateAge = 1;
			}
		}
	}
	
	char gender[7];
	while(1) {
		printf(" Insert pet gender [Male | Female] (case insensitive) : ");
		scanf("%[^\n]", gender); getchar();
		
		if(strcmpi(gender, "Male") == 0) {
			strcpy(gender, "male");
			break;
		} else if(strcmpi(gender, "Female") == 0) {
			strcpy(gender, "female");
			break;
		} else {
			puts(" Gender must be between Male or Female!");
		}
	}
	
	int weight;
	while(1) {
		printf(" Insert pet weight (not more than 80kg) : ");
		scanf("%d", &weight); getchar();
		
		if(weight <= 80) {
			break;
		} else {
			puts(" Your pet exceed the maximum pet weight!");
		}
	}
	
	Pet *pet = newPet(name, DoB, age, gender, weight);
	
	int index = hash(pet->name);
	if(head[index] == NULL) {
		head[index] = tail[index] = pet;
	} else {
		tail[index]->next = pet;
		pet->prev = tail[index];
		tail[index] = pet;
		tail[index]->next = NULL;
	}
	no++;
	
	printf(" Data has been recorded :D\n Press enter to continue . . ."); getchar();
}

void view() {
	system("cls");
	
	if(no) {
		for(int i = 0; i < SIZE; i++) {
			Pet *pet = head[i];
			while(pet != NULL) {
				printf(" No %d\n", no);
				printf(" Pet Name   : %s\n", pet->name);
				printf(" Pet DoB    : %s\n", pet->DoB);
				printf(" Pet Age    : %s\n", pet->age);
				printf(" Pet Gender : %s\n", pet->gender);
				printf(" Pet Weight : %d\n", pet->weight);
				puts(" ===================================================");
				
				pet = pet->next;
			}
		}
	} else {
		puts(" There\'s no pet yet :D");
	}
	
	printf(" Press enter to continue . . ."); getchar();
}

void deletePet() {
	system("cls");
	
	Pet *pet;
	
	if(no) {
		puts(" =================================\n |            Pet List           |\n =================================");
		for(int i = 0; i < SIZE; i++) {
			pet = head[i];
			while(pet != NULL) {
				printf(" | %-30s|\n", pet);
				pet = pet->next;
			}
		}
		puts(" =================================");
		
		char name[31];
		while(1) {
			printf(" Please input pet name to be removed [0 to exit] : ");
			scanf("%[^\n]", name); getchar();
			
			int len = strlen(name);
			if(strcmp(name, "0") == 0) {
				return;
			} else if((len < 5) || (len > 30)) {
				puts(" Name are not available on the list!");
			} else {
				int index = hash(name);
				if(head[index] == NULL) {
					puts(" Name are not available on the list!");
				} else if(head[index] == tail[index]) {
					if(strcmp(head[index]->name, name) == 0) {
						free(pet);
						head[index] = tail[index] = NULL;
						
						puts(" Name has been deleted");
						no--;
						break;
					} else {
						puts(" Name are not available on the list!");
					}
				} else {
					pet = head[index];
					while(pet != NULL) {
						if(strcmp(pet->name, name) == 0) {
							pet->prev->next = pet->next;
							pet->next->prev = pet->prev;
							free(pet);
							
							puts(" Name has been deleted");
							no--;
							break;
						}
						pet = pet->next;
					}
					
					puts(" Name are not available on the list!");
				}
					
			}
		}
	} else {
		puts(" There\'s no pet yet :D");
	}
	
	printf(" Press enter to continue . . ."); getchar();
}

void PMS() {
	int validateManagement = 0;
	while((validateManagement < 1) || (validateManagement > 3)) {
		system("cls");
		
		printf(" Welcome to Pet Management System\n ==========================\n 1. Add New Pet\n 2. Remove Pet\n 3. Back\n Choose [1-3] >> ");
		scanf("%d", &validateManagement); getchar();
		
		if((validateManagement >= 1) && (validateManagement <= 3)) {
			switch(validateManagement) {
				case 1: {
					add();
					break;
				}
				
				case 2: {
					deletePet();
					break;
				}
				
				case 3: {
					return;
				}
			}
			validateManagement = 0;
		}
	}
}

void menu() {
	int validateMenu = 0;
	while((validateMenu < 1) || (validateMenu > 3)) {
		system("cls");
		
		printf(" PetShop\n ==========================\n 1. Pet Management\n 2. View All Pet\n 3. Exit\n Choose [1-3] >> ");
		scanf("%d", &validateMenu); getchar();
		
		if((validateMenu >= 1) && (validateMenu <= 3)) {
			switch(validateMenu) {
				case 1: {
					PMS();
					break;
				}
				
				case 2: {
					view();
					break;
				}
				
				case 3: {
					return;
				}
			}
			validateMenu = 0;
		}
	}
}

int main() {
	menu();
	
	return 0;
}
