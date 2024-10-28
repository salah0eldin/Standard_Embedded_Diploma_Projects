/*******************************************************************************
 *
 * Module: Human Interface
 *
 * File Name: humaninterface.c
 *
 * Description: Source file for the Human Interface module in the FreeRTOS project.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "humaninterface.h"
#include "../../../shared/shared.h"
#include "../../FreeRTOS/FreeRTOS.h"
#include "../../FreeRTOS/semphr.h"
#include "../../ECU/Keypad/keypad.h"
#include "../../ECU/LCD/lcd.h"
#include "../queues.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
const uint8 keypadKeys[] = { '7', '8', '9', 0, '4', '5', '6', 0, '1', '2', '3', '-', 0, '0',
KEYPAD_ENTER_ASCII, '+' }; /* Keypad key mapping array */

static uint8 g_sendValue = 0; 	 /* Variable to hold the value to send  */
static uint8 g_receiveValue = 0; /* Variable to hold the received value */

uint8 timeToWait = 60; 	/* Time to wait during certain operations 	*/
uint8 iterator = 0; 	/* Counter for iterating attempts or inputs */
uint8 key; 				/* Variable for storing the pressed key		*/

/*******************************************************************************
 *                              Private Function Prototypes                    *
 *******************************************************************************/
/* Handle timeout when pass input times out */
static void HI_passTimesOut(void);

/* Display control error message */
static void HI_showControlError(void);

/* Enter the password */
static void HI_enterPassword(void);

/* Retrieve and validate the entered password */
static uint8 HI_getAndCheckPass(void);

/* Update the stored password */
static uint8 HI_updatePass(void);

/* Initialize the task for the human interface */
static void HI_taskInit(void);

/* Check if a password exists and log in */
static void HI_checkPassExistAndLogIn(void);

/* Manage door control based on conditions */
static void HI_handleDoor(void);


/*******************************************************************************
 *                              Public Function Definitions                     *
 *******************************************************************************/

/**
 * @brief Human Interface task for handling user interactions.
 *
 * This function runs in a FreeRTOS task to manage the human interface
 * and process user inputs or outputs.
 *
 * @param pvParameters Pointer to task parameters.
 */
void HI_task(void *pvParameters) {
	/** Initialize task components such as the LCD and keypad. */
	HI_taskInit();

	/** Check if a password exists and log in if necessary. */
	HI_checkPassExistAndLogIn();

	/** Infinite loop to handle user interactions. */
	for (;;) {

		/** Display options for the user on the LCD. */
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 1, "+ : Open Door");
		LCD_displayStringRowColumn(1, 1, "- : Change Pass");

		/** Wait for a key press from the keypad. */
		key = KEYPAD_getPressedKeyBlocking();

		/** Check if the pressed key is for opening the door or changing the password. */
		if (key == '-' || key == '+') {
			/** Set the action based on the pressed key. */
			g_sendValue = (key == '+') ? SHARED_OPEN_DOOR : SHARED_CHANGE_PASS;
			uint8 keyTemp = key;
			/** Send the action to the queue. */
			if (xQueueSend(g_xQueueSend, &g_sendValue, (TickType_t)20) == pdPASS) {
				/** Message sent successfully */
			}

			/** Check if the entered password is correct. */
			if (HI_getAndCheckPass() == TRUE) {
				if (keyTemp == '+') {
					HI_handleDoor();
				} else {
					if (HI_updatePass() == TRUE) {
						/** Notify the user that the password has been successfully changed. */
						LCD_displayString("Pass Changed");
						LCD_displayStringRowColumn(1, 0, "Successfully!");
						/** Delay to allow the user to read the message. */
						vTaskDelay(DELAY_TIME);
					}
				}
			}
		}
	}
}

/*******************************************************************************
 *                              Private Function Definitions                    *
 *******************************************************************************/

/**
 * @brief Handles the timeout situation for password attempts.
 *
 * This function activates the buzzer and displays a locked message for a defined time period.
 */
static void HI_passTimesOut(void) {
	/** Set the value to indicate the buzzer should be turned on. */
	g_sendValue = SHARED_BUZZER_ON;

	/** Attempt to send the buzzer on message to the queue. */
	if (xQueueSend(g_xQueueSend, &g_sendValue, (TickType_t)20) == pdPASS) {
		/** Message sent successfully */
	}

	/** Display a message indicating that the system is locked. */
	LCD_clearScreen();
	LCD_displayString("System Locked");
	LCD_displayStringRowColumn(1, 0, "Wait For");

	/** Countdown while timeToWait is not zero. */
	while (timeToWait != 0) {
		/** Display the remaining time on the LCD. */
		LCD_moveCursor(1, 9);
		LCD_displayNumber(timeToWait);
		LCD_displayString(" Sec ");

		/** Delay for a predefined period to manage the countdown timing. */
		vTaskDelay(LOCK_DELAY_TIME);

		/** Decrement the countdown timer. */
		timeToWait--;
	}

	/** Set the value to indicate the buzzer should be turned off. */
	g_sendValue = SHARED_BUZZER_OFF;

	/** Attempt to send the buzzer off message to the queue. */
	if (xQueueSend(g_xQueueSend, &g_sendValue, (TickType_t)20) == pdPASS) {
		/** Message sent successfully */
	}
}

/**
 * @brief Displays a control error message.
 *
 * This function indicates a control error to the user.
 */
static void HI_showControlError(void) {
	/** Display a message indicating there was a control error. */
	LCD_displayString("Control Error");
	LCD_displayStringRowColumn(1, 0, "Try again!");

	/** Delay for a predefined period to allow the user to read the message. */
	vTaskDelay(DELAY_TIME);
}

/**
 * @brief Prompts the user to enter a password.
 *
 * This function displays a prompt for the user to enter a password using the keypad.
 */
static void HI_enterPassword(void) {
	/** Display the password entry prompt on the LCD. */
	LCD_displayStringRowColumn(1, 0, "Pass:_____");

	/** Move the cursor to the password entry position. */
	LCD_moveCursor(1, 5);

	/** Initialize the iterator to track the number of entered characters. */
	iterator = 0;

	/** Loop until the maximum password length is reached. */
	while (iterator < SHARED_PASS_LENGTH) {
		/** Wait for a key press from the keypad. */
		key = KEYPAD_getPressedKeyBlocking();

		/** Check if the pressed key is a digit. */
		if (key >= '0' && key <= '9') {
			/** Increment the iterator for valid password characters. */
			iterator++;
			/** Display asterisk for each entered character on the LCD. */
			LCD_displayCharacter('*');

			/** If not at the maximum length, send the key to the queue. */
			if (iterator < SHARED_PASS_LENGTH) {
				if (xQueueSend(g_xQueueSend, &key, (TickType_t)20) == pdPASS) {
					/** Message sent successfully. */
				}
			}
		}
	}

	/** Wait until the Enter key is pressed to confirm the password entry. */
	while (KEYPAD_ENTER_ASCII != KEYPAD_getPressedKeyBlocking()) {
		/** Loop until the Enter key is detected. */
	}

	/** Send the last key to the queue to indicate password entry completion. */
	if (xQueueSend(g_xQueueSend, &key, (TickType_t)20) == pdPASS) {
		/** Message sent successfully. */
	}
}

/**
 * @brief Validates the entered password against the stored password.
 *
 * @return uint8 Returns TRUE if the password is correct, otherwise FALSE.
 */
static uint8 HI_getAndCheckPass(void) {
	/** Initialize the number of allowed password attempts. */
	uint8 passTimes = 3;

	/** Loop until the maximum password attempts are exhausted or success is achieved. */
	do {

		/** Prompt the user to enter the password. */
		LCD_clearScreen();
		LCD_displayString("Enter the Pass");

		/** Call the function to enter the password. */
		HI_enterPassword();

		/** Set the default receive value to indicate a failed attempt. */
		g_receiveValue = SHARED_FAIL;

		/** Check if a message is received in the queue. */
		if (xQueueReceive(g_xQueueReceive, &g_receiveValue, DELAY_TIME) == pdPASS) {
			/** Message received successfully. */
		}

		/** Clear the LCD screen for feedback. */
		LCD_clearScreen();

		/** Handle the received value based on the authentication result. */
		switch (g_receiveValue) {
		case SHARED_FAIL:
			/** Show an error message if authentication failed. */
			HI_showControlError();
			break;
		case SHARED_PASS_DONT_MATCH:
			/** Decrement the number of remaining attempts. */
			passTimes--;

			/** Inform the user of the incorrect password. */
			LCD_displayString("Wrong Pass!");
			LCD_moveCursor(1, 0);
			LCD_displayNumber(passTimes);
			LCD_displayString(" Tries Left");

			/** Delay before the next attempt. */
			vTaskDelay(DELAY_TIME);
			break;
		}

		/** Check if the number of attempts has reached zero. */
		if (passTimes == 0) {
			/** Lock the system due to too many failed attempts. */
			HI_passTimesOut();
		}

		/** Continue looping until attempts are exhausted or success is achieved. */
	} while (passTimes != 0 && g_receiveValue != SHARED_SUCCESS);

	/** Return true if the password was successfully validated. */
	return (g_receiveValue == SHARED_SUCCESS);
}

/**
 * @brief Updates the password after validation.
 *
 * @return uint8 Returns TRUE if the password was updated successfully, otherwise FALSE.
 */
static uint8 HI_updatePass(void) {
	/** Prompt the user to enter a new password. */
	LCD_clearScreen();
	LCD_displayString("Enter new Pass");

	/** Call the function to enter the new password. */
	HI_enterPassword();

	/** Prompt the user to re-enter the new password for confirmation. */
	LCD_clearScreen();
	LCD_displayString("ReEnter new Pass");

	/** Call the function to enter the new password again. */
	HI_enterPassword();

	/** Set the default receive value to indicate a failed attempt. */
	g_receiveValue = SHARED_FAIL;

	/** Check if a message is received in the queue. */
	if (xQueueReceive(g_xQueueReceive, &g_receiveValue, DELAY_TIME) == pdPASS) {
		/** Message received successfully. */
	}

	/** Clear the LCD screen for feedback on the password update. */
	LCD_clearScreen();

	/** Handle the received value based on the password update result. */
	switch (g_receiveValue) {
	case SHARED_FAIL:
		/** Show an error message if the password update failed. */
		HI_showControlError();
		break;
	case SHARED_PASS_DONT_MATCH:
		/** Inform the user that the passwords do not match. */
		LCD_displayString("Passwords don't");
		LCD_displayStringRowColumn(1, 0, "Match!");

		/** Delay to allow the user to read the message. */
		vTaskDelay(DELAY_TIME);
		break;
	}

	/** Return true if the password was successfully updated. */
	return (g_receiveValue == SHARED_SUCCESS);
}

/**
 * @brief Initializes the Human Interface module.
 *
 * This function initializes the LCD and keypad.
 */
static void HI_taskInit(void) {
	/** Initialize the LCD display for use. */
	LCD_init();

	/** Initialize the keypad for input. */
	KEYPAD_init();

	/** Set the keys for the keypad using the predefined key array. */
	KEYPAD_setKeys(keypadKeys);

	/** Display the main title for the door lock system on the LCD. */
	LCD_displayString("Door Lock System");

	/** Indicate that the system is loading on the second row of the LCD. */
	LCD_displayStringRowColumn(1, 0, "Loading...");

	/** Delay for a specified time to allow the loading message to be visible. */
	vTaskDelay(DELAY_TIME);
}

/**
 * @brief Checks if a password exists and attempts to log in.
 */
static void HI_checkPassExistAndLogIn(void) {
	/** Infinite loop to continuously check for password existence and login. */
	for (;;) {
		/** Prepare to check if the password exists. */
		g_sendValue = SHARED_CHECK_PASS_EXIST;

		/** Check if the send queue is empty and send the message if possible. */
		if (xQueueIsQueueEmptyFromISR(g_xQueueSend) &&
		xQueueSend(g_xQueueSend, &g_sendValue, (TickType_t)20) == pdPASS) {
			/** Message sent successfully. */
		}

		/** Wait to receive a response regarding password existence. */
		if (xQueueReceive(g_xQueueReceive, &g_receiveValue, DELAY_TIME) == pdPASS) {
			break; /** Exit the loop upon successful receipt. */
		}
	}

	/** If the password exists, attempt to get and validate the password. */
	if (g_receiveValue == SHARED_SUCCESS) {
		while (HI_getAndCheckPass() == FALSE)
			; /** Keep trying until the password is correct. */

		/** Clear the LCD screen and display the unlock message. */
		LCD_clearScreen();
		LCD_displayString("System Un-Locked");
		LCD_displayStringRowColumn(1, 0, "Welcome!");

		/** Delay to allow the user to see the unlock message. */
		vTaskDelay(DELAY_TIME);
	} else {
		/** If the password does not exist, attempt to update the password. */
		while (HI_updatePass() == FALSE)
			; /** Keep trying until the password is successfully updated. */
	}
}

/**
 * @brief Handles the door operation based on user input.
 *
 * If the user wants to open the door, this function will manage the door unlocking process.
 */
static void HI_handleDoor(void) {
	/** Display a message indicating the door is unlocking. */
	LCD_displayString("Door Unlocking");
	LCD_displayStringRowColumn(1, 0, "Please Wait...");

	/** Initialize the receive value to indicate failure initially. */
	g_receiveValue = SHARED_FAIL;

	/** Wait for a message indicating it's okay to proceed. */
	do {
		if (xQueueReceive(g_xQueueReceive, &g_receiveValue, DELAY_TIME) == pdPASS) {
			/** Message received successfully. */
		}
	} while (g_receiveValue != SHARED_WAIT_PEOPLE); /** Loop until the expected 'wait for people' message is received. */

	/** Clear the display and notify users to wait for people to enter. */
	LCD_clearScreen();
	LCD_displayString("Wait For People");
	LCD_displayStringRowColumn(1, 0, "To Enter");

	/** Wait for a message indicating the door is locking. */
	do {
		if (xQueueReceive(g_xQueueReceive, &g_receiveValue, DELAY_TIME) == pdPASS) {
			/** Message received successfully. */
		}
	} while (g_receiveValue != SHARED_LOCKING_DOOR); /** Loop until the 'locking door' message is received. */

	/** Clear the display and show a message indicating the door is locking. */
	LCD_clearScreen();
	LCD_displayString("Door Locking...");

	/** Wait for a message indicating the door is closed. */
	do {
		if (xQueueReceive(g_xQueueReceive, &g_receiveValue, DELAY_TIME) == pdPASS) {
			/** Message received successfully. */
		}
	} while (g_receiveValue != SHARED_DOOR_CLOSED); /** Loop until the 'door closed' message is received. */
}

