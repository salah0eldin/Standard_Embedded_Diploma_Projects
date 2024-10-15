/*
 * projfuncs.h
 *
 *  Created on: Aug 5, 2024
 *      Author: Salah Eldin
 */


#ifndef HEADERS_PROJFUNCS_H_
#define HEADERS_PROJFUNCS_H_

#include "stdList.h"

#define NUM_OF_FUNCS 9

// Enum for main menu options
typedef enum {
	ADD = 1, DISPLAY, SEARCH, UPDATE, DELETE_STD, AVGGPA, MAXGPA, EXIT_PROG
} mainInput;

// Function prototypes

// Show the main menu window and get user choice
void showMainWindow(mainInput *userChoice);


// Add a new student to the list
void addStudent(node **stdListptr);

// Display all students in the list
void dispAllStudents(node **stdListptr);

// Search for a student by ID
void searchById(node **stdListptr);

// Update a student's information by ID
void updateById(node **stdListptr);

// Delete a student from the list by ID
void deleteById(node **stdListptr);

// Calculate the average GPA of all students
void calcAvgGpa(node **stdListptr);

// Get the maximum GPA among all students
void getMaxGpa(node **stdListptr);

// End the program and clean up
void endProgram(node **stdListptr);

#endif /* HEADERS_PROJFUNCS_H_ */
