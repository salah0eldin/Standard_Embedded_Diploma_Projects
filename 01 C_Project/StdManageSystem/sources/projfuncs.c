/*
 * projfuncs.c
 *
 *  Created on: Aug 5, 2024
 *      Author: Salah Eldin
 */

#include "../headers/projfuncs.h"

// Display the main menu and get the user's choice
void showMainWindow(mainInput *userChoice) {
	puts("");
	puts(" ___________________________________________________ ");
	puts("|                                                   |");
	puts("|                  MAIN WINDOW                      |");
	puts("|___________________________________________________|");
	puts("|                                                   |");
	printf("|  %d- Add new student         %d- Delete by ID       |\n", ADD,
			DELETE_STD);
	printf("|  %d- Display all students    %d- Calculate AVG GPA  |\n", DISPLAY,
			AVGGPA);
	printf("|  %d- Search by ID            %d- Get max GPA IDs    |\n", SEARCH,
			MAXGPA);
	printf("|  %d- Update by ID            %d- Exit               |\n", UPDATE,
			EXIT_PROG);
	puts("|___________________________________________________|");
	puts("|                                                   |");
	printf("| Enter your choice: ");
	while (scanf("%d", (int*) userChoice) != 1) {
		printf("| Invalid input. Please enter a number: ");
		while (getchar() != '\n')
			; // Clear the input buffer
	}
	puts("|___________________________________________________|");
	puts("");
}

// Add a new student to the list
void addStudent(node **stdListptr) {
	student std;
	puts(" ___________________________________________________ ");
	puts("|                                                   |");
	puts("|                 ADD STUDENT                       |");
	puts("|___________________________________________________|");
	puts("|                                                   |");
	printf("| Student ID: ");
	while (scanf("%d", &std.id) != 1) {
		printf("| Invalid input. Please enter a number: ");
		while (getchar() != '\n')
			; // Clear the input buffer
	}
	getchar();  // Clear newline character from input buffer
	printf("| Student Name: ");
	gets(std.name);  // Read student name
	printf("| Student Age: ");
	while (scanf("%d", &std.age) != 1) {
		printf("| Invalid input. Please enter a number: ");
		while (getchar() != '\n')
			; // Clear the input buffer
	}	// Check if age is within the valid range (optional validation)
	// if (std.age > 30 || std.age < 10) {
	//     puts("|                                                   |");
	//     puts("|        Age can't be out of range (10 -> 30)       |");
	//     puts("|___________________________________________________|");
	//     return;
	// }
	printf("| Student GPA: ");
	while (scanf("%f", &std.gpa) != 1) {
		printf("| Invalid input. Please enter a number: ");
		while (getchar() != '\n')
			; // Clear the input buffer
	}	// Check if GPA is within the valid range
	if (std.gpa > 4 || std.gpa < 0) {
		puts("|                                                   |");
		puts("|        GPA can't be out of range (0 -> 4)         |");
		puts("|___________________________________________________|");
		return;
	}
	// Add student to list and handle duplicate ID
	if (ID_TOKEN == addStdToList(stdListptr, &std)) {
		puts("|                                                   |");
		puts("|           ID is taken, choose another one         |");
	} else {
		puts("|                                                   |");
		puts("|                Added successfully                 |");
	}
	puts("|___________________________________________________|");
}

// Display all students in the list
void dispAllStudents(node **stdListptr) {
	puts(" ___________________________________________________ ");
	puts("|                                                   |");
	puts("|                   STUDENT LIST                    |");
	puts("|___________________________________________________|");
	puts("|                                                   |");
	// Check if list is empty
	if (*stdListptr == nullptr)
		puts("|                    EMPTY LIST                     |");
	else
		dispList(stdListptr);
	puts("|___________________________________________________|");
}

// Search for a student by ID and display their information
void searchById(node **stdListptr) {
	int id;

	puts(" ___________________________________________________ ");
	puts("|                                                   |");
	puts("|                  STUDENT By ID                    |");
	puts("|___________________________________________________|");
	puts("|                                                   |");
	printf("| Enter Student ID: ");
	while (scanf("%d", &id) != 1) {
		printf("| Invalid input. Please enter a number: ");
		while (getchar() != '\n')
			; // Clear the input buffer
	}
	node *std = findStudent(stdListptr, id);
	if (std == nullptr) {
		puts("|                                                   |");
		puts("|                No student matches this ID         |");
	} else {
		puts("|                                                   |");
		printf("| %-4s | %-20s | %-6s | %-10s |\n", "ID", "Name", "Age", "GPA");
		printf("|------|----------------------|--------|------------|\n");
		printf("| %-4d | %-20s | %-6d | %-10.2f |\n", std->data.id,
				std->data.name, std->data.age, std->data.gpa);
	}
	puts("|___________________________________________________|");
}

// Update a student's information by ID
void updateById(node **stdListptr) {
	int id;
	student std;
	char c;

	puts(" ___________________________________________________ ");
	puts("|                                                   |");
	puts("|                  UPDATE By ID                     |");
	puts("|___________________________________________________|");
	puts("|                                                   |");
	printf("| Enter Student ID: ");
	while (scanf("%d", &id) != 1) {
		printf("| Invalid input. Please enter a number: ");
		while (getchar() != '\n')
			; // Clear the input buffer
	}
	node *stdptr = findStudent(stdListptr, id);
	if (stdptr == nullptr) {
		puts("|                                                   |");
		puts("|                No student matches this ID         |");
		puts("|___________________________________________________|");
		return;
	} else {
		puts("|                                                   |");
		printf("| %-4s | %-20s | %-6s | %-10s |\n", "ID", "Name", "Age", "GPA");
		printf("|------|----------------------|--------|------------|\n");
		printf("| %-4d | %-20s | %-6d | %-10.2f |\n", stdptr->data.id,
				stdptr->data.name, stdptr->data.age, stdptr->data.gpa);
		puts("|                                                   |");
		std.id = id;
		getchar();  // Clear newline character from input buffer
		printf("| NEW Name: ");
		gets(std.name);  // Read new student name
		printf("| NEW Age: ");
		while (scanf("%d", &std.age) != 1) {
			printf("| Invalid input. Please enter a number: ");
			while (getchar() != '\n')
				; // Clear the input buffer
		}
		printf("| NEW GPA: ");
		while (scanf("%f", &std.gpa) != 1) {
			printf("| Invalid input. Please enter a number: ");
			while (getchar() != '\n')
				; // Clear the input buffer
		}
		// Check if new GPA is within the valid range
		if (std.gpa > 4 || std.gpa < 0) {
			puts("|                                                   |");
			puts("|        GPA can't be out of range (0 -> 4)         |");
			puts("|___________________________________________________|");
			return;
		}

		// Display the new data and ask for confirmation
		puts("|                                                   |");
		puts("|      New data to be updated:                      |");
		printf("| %-4s | %-20s | %-6s | %-10s |\n", "ID", "Name", "Age", "GPA");
		printf("|------|----------------------|--------|------------|\n");
		printf("| %-4d | %-20s | %-6d | %-10.2f |\n", std.id, std.name, std.age,
				std.gpa);
		puts("|                                                   |");
		printf("| Confirm update? (y/n): ");
		scanf(" %c", &c);
		while (getchar() != '\n')
			; // Clear the input buffer
		// If user confirms, update the student information in the list
		if (c == 'y') {
			updateStdFromList(&stdptr->data, &std);
			puts("|                                                   |");
			puts("|                Updated successfully               |");
		} else {
			puts("|                                                   |");
			puts("|                  Update Canceled                  |");
		}
	}
	puts("|___________________________________________________|");
}

// Delete a student from the list by ID
void deleteById(node **stdListptr) {
	int id;
	puts(" ___________________________________________________ ");
	puts("|                                                   |");
	puts("|                  DELETE By ID                     |");
	puts("|___________________________________________________|");
	puts("|                                                   |");
	printf("| Enter Student ID: ");
	while (scanf("%d", &id) != 1) {
		printf("| Invalid input. Please enter a number: ");
		while (getchar() != '\n')
			; // Clear the input buffer
	}	// Perform deletion and handle possible outcomes
	switch (deleteStdFromList(stdListptr, id)) {
	case ID_NOT_FOUND:
		puts("|                                                   |");
		puts("|                No student matches this ID         |");
		break;
	case CANCEL:
		puts("|                                                   |");
		puts("|                     CANCELED                      |");
		break;
	case SUCCESS:
		puts("|                                                   |");
		puts("|                Deleted Successfully               |");
		break;
	}
	puts("|___________________________________________________|");
}

// Calculate and display the average GPA of all students
void calcAvgGpa(node **stdListptr) {
	puts(" ___________________________________________________ ");
	puts("|                                                   |");
	puts("|                     AVG GPA                       |");
	puts("|___________________________________________________|");
	puts("|                                                   |");
	printf("| Average GPA is : %-33.2f|\n", calcAvgGpaList(stdListptr));
	puts("|___________________________________________________|");
}

// Find and display the student with the highest GPA
void getMaxGpa(node **stdListptr) {
	puts(" ___________________________________________________ ");
	puts("|                                                   |");
	puts("|                     MAX GPA                       |");
	puts("|___________________________________________________|");
	puts("|                                                   |");
	getMaxGpaList(stdListptr);
	puts("|___________________________________________________|");
}

// Free all allocated memory and exit the program
void endProgram(node **stdListptr) {
	freeStdList(stdListptr);

	puts(" ___________________________________________________ ");
	puts("|                                                   |");
	puts("|                  EXIT BYE BYE                     |");
	puts("|___________________________________________________|");
	exit(0);
}
