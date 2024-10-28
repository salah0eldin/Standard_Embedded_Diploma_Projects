/*******************************************************************************
 *
 * Module: Human Machine Interface (HMI) ECU Interface
 *
 * File Name: hmi.c
 *
 * Description: Implementation file for the HMI module that handles
 *              communication with the ECU via USART in a FreeRTOS environment.
 *
 * Created on: Oct 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "hmi.h"
#include "../../../Shared/shared.h"
#include "../../FreeRTOS/FreeRTOS.h"
#include "../../FreeRTOS/semphr.h"
#include "../../ECU/I2C_EEPROM/i2c_eeprom.h"
#include "../../ECU/Buzzer/buzzer.h"
#include "../../MCAL/USART/usart.h"
#include "../globals.h"

/*******************************************************************************
 *                              Static Variables                                *
 *******************************************************************************/
static uint8 password[SHARED_PASS_LENGTH] = { 0 };  /* Holds the stored password */
static uint8 passTemp[SHARED_PASS_LENGTH] = { 0 };  /* Temporary storage for a new password */

static uint8 equality = FALSE;   /* Flag to check if the entered password matches    */
static uint8 iterator = 0;       /* Iterator for looping through password characters */
static uint8 passTimes = 3;      /* Counter for the number of password attempts      */

SemaphoreHandle_t usartReceiveSemphr;   /* Semaphore for USART receive synchronization */

uint8 g_dataReceive;        /* Variable to store received data from USART  */
uint8 g_dataSend;           /* Variable to store data to be sent via USART */


/*******************************************************************************
 *                              Static Function Prototypes                      *
 *******************************************************************************/
static uint8 PASSHANDLER_isPassExist(void); /* Checks if a password exists in EEPROM */
static uint8 PASSHANDLER_checkPass(void);   /* Validates the entered password against the stored password */
static uint8 PASSHANDLER_updatePass(void);  /* Updates the password in EEPROM with a new value */


/*******************************************************************************
 *                              Public Functions                                *
 *******************************************************************************/

/**
 * @brief Task for sending data over USART.
 *
 * This function runs as a FreeRTOS task to handle outgoing USART communication.
 *
 * @param pvParameters Pointer to task parameters.
 */
void HMI_usartSenderTask(void *pvParameters) {
    /* Initialize the USART if it hasn't been initialized yet */
    if (USART_isInit() == FALSE) {
        USART_init(&g_usart);  /* Initialize the USART with the global settings */
    }

    uint8 dataSend;  /* Variable to hold the data to be sent over USART */
    for (;;) {
        /* Wait indefinitely for data to be available in the queue */
        if (xQueueReceive(g_xQueueSend, &dataSend, portMAX_DELAY) == pdPASS) {
            /* Send the data character non-blockingly until successful */
            while (!USART_sendCharNonBlocking(dataSend))
                ;  /* Loop until the character is sent successfully */
        }
    }
}


/**
 * @brief Interrupt handler for receiving USART data.
 *
 * This function is called from the USART receive interrupt to handle incoming data.
 */
void CI_usartReceiveIntHandl(void) {
    /* Receive a character from USART in a non-blocking manner */
    USART_receiveCharNonBlocking(&g_dataReceive);

    /* Release the semaphore to indicate that data has been received */
    xSemaphoreGiveFromISR(usartReceiveSemphr, NULL);
}


/**
 * @brief Task for receiving data over USART.
 *
 * This function runs as a FreeRTOS task to handle incoming USART communication
 * and processes various commands.
 *
 * @param pvParameters Pointer to task parameters.
 */
void HMI_usartReceiverTask(void *pvParameters) {
	/* Initialize USART if it is not already initialized */
	if (USART_isInit() == FALSE) {
		USART_init(&g_usart);
	}

	/* Initialize I2C EEPROM and buzzer components */
	I2C_EEPROM_init();
	BUZZER_init(&g_buzzer1);

	/* Create a binary semaphore for USART reception */
	usartReceiveSemphr = xSemaphoreCreateBinary();

	/* Set the USART RX complete interrupt handler */
	USART_setRXCompleteInterruptHandler(CI_usartReceiveIntHandl);

	/* Infinite loop for task execution */
	for (;;) {
		/* Wait indefinitely for the semaphore to be given */
		if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
			uint8 ret;

			/* Handle different types of received commands */
			switch (g_dataReceive) {
			case SHARED_CHECK_PASS_EXIST:
				/* Check if the password exists */
				ret = PASSHANDLER_isPassExist();
				if (xQueueSend(g_xQueueSend, &ret, (TickType_t)20) == pdPASS) {
					/* Response sent to indicate if the password exists */
				}
				/* If password exists, check the password */
				if (ret == SHARED_SUCCESS) {
					while (PASSHANDLER_checkPass() == FALSE)
						; /* Wait until password check passes */
				} else {
					while (PASSHANDLER_updatePass() == FALSE)
						; /* Wait until password update passes */
				}
				break;

			case SHARED_OPEN_DOOR:
				/* If the password is correct, open the door */
				if (PASSHANDLER_checkPass() == TRUE) {
					xSemaphoreGive(g_doorSemphr); /* Open the door */
				}
				break;

			case SHARED_CHANGE_PASS:
				/* If the password is correct, allow password change */
				if (PASSHANDLER_checkPass() == TRUE) {
					PASSHANDLER_updatePass(); /* Update the password */
				}
				break;
			}
		}
	}
}


/*******************************************************************************
 *                              Static Functions                                *
 *******************************************************************************/

/**
 * @brief Check if the password exists in the system.
 *
 * This function checks EEPROM to determine whether a password has been set.
 *
 * @return uint8 Returns SHARED_SUCCESS if the password exists, SHARED_FAIL otherwise.
 */
static uint8 PASSHANDLER_isPassExist(void) {
    /* Initialize the return value to FALSE */
    uint8 ret = FALSE;
    uint8 val;

    /* Read the byte from EEPROM that indicates if the password exists */
    I2C_EEPROM_receiveByte(PASSHANDLER_IS_PASS_ADDR, &val);

    /* Check if the read value matches the constant indicating the password exists */
    if (val == PASSHANDLER_PASS_EXIST) {
        ret = TRUE; /* Password exists */

        vTaskDelay(pdMS_TO_TICKS(100));
        /* Read the password data from EEPROM */
        I2C_EEPROM_receiveData(PASSHANDLER_PASS_ADDR, password, SHARED_PASS_LENGTH);
    }

    /* Return success if the password exists, otherwise return failure */
    return (ret == TRUE) ? SHARED_SUCCESS : SHARED_FAIL;
}


/**
 * @brief Verify the user-provided password.
 *
 * This function checks the inputted password against the stored password.
 *
 * @return uint8 Returns 1 if the password matches, 0 otherwise.
 */
static uint8 PASSHANDLER_checkPass(void) {
    /* Loop until either the password is correctly entered or the attempt limit is reached */
    do {
        iterator = 0; /* Reset the iterator for password checking */
        equality = TRUE; /* Assume equality until proven otherwise */

        /* Check each character of the password */
        while (iterator < SHARED_PASS_LENGTH) {
            /* Wait for a character to be received via USART */
            if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
                /* Compare received character with the stored password */
                equality &= (password[iterator++] == g_dataReceive);
            }
        }

        /* If the entered password doesn't match */
        if (equality == FALSE) {
            passTimes--; /* Decrement the allowed attempts */
            g_dataSend = SHARED_PASS_DONT_MATCH; /* Set response to indicate mismatch */
        } else {
            g_dataSend = SHARED_SUCCESS; /* Set response to indicate success */
        }

        /* Send the result back through the queue */
        if (xQueueSend(g_xQueueSend, &g_dataSend, (TickType_t)20) == pdPASS) {
            /* Response sent */
        }

        /* If the number of attempts has been exhausted */
        if (passTimes == 0) {
            /* Wait for the command to turn on the buzzer */
            do {
                if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
                    /* Wait for the buzzer command */
                }
            } while (SHARED_BUZZER_ON != g_dataReceive);
            BUZZER_turnOn(&g_buzzer1); /* Turn on the buzzer */

            /* Wait for the command to turn off the buzzer */
            do {
                if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
                    /* Wait for the buzzer off command */
                }
            } while (SHARED_BUZZER_OFF != g_dataReceive);
            BUZZER_turnOff(&g_buzzer1); /* Turn off the buzzer */
        }

    } while (passTimes != 0 && equality == FALSE); /* Repeat until correct or attempts run out */

    passTimes = 3; /* Reset the password attempt counter */
    return equality; /* Return the result of the password check */
}


/**
 * @brief Update the password stored in EEPROM.
 *
 * This function updates the stored password with a new one provided by the user.
 *
 * @return uint8 Returns 1 if the update is successful, 0 otherwise.
 */
static uint8 PASSHANDLER_updatePass(void) {
    iterator = 0; /* Initialize the iterator for password entry */
    equality = TRUE; /* Assume equality until proven otherwise */

    /* Collect new password from USART */
    while (iterator < SHARED_PASS_LENGTH) {
        /* Wait for a character to be received via USART */
        if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
            /* Store the received character in passTemp */
            passTemp[iterator++] = g_dataReceive;
        }
    }

    iterator = 0; /* Reset iterator for password confirmation */

    /* Confirm the entered password by re-reading it */
    while (iterator < SHARED_PASS_LENGTH) {
        /* Wait for a character to be received via USART */
        if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
            /* Compare the confirmation character with the entered password */
            equality &= (passTemp[iterator++] == g_dataReceive);
        }
    }

    /* Check if the entered password matches the confirmation */
    if (equality == FALSE) {
        g_dataSend = SHARED_PASS_DONT_MATCH; /* Set response to indicate mismatch */
    } else {
        g_dataSend = SHARED_SUCCESS; /* Set response to indicate success */
    }

    /* Send the result back through the queue */
    if (xQueueSend(g_xQueueSend, &g_dataSend, (TickType_t)20) == pdPASS) {
        /* Response sent */
    }

    /* If the password confirmation was successful */
    if (equality == TRUE) {
        /* Indicate that a password exists in the EEPROM */
        I2C_EEPROM_sendByte(PASSHANDLER_IS_PASS_ADDR, PASSHANDLER_PASS_EXIST);
        vTaskDelay(pdMS_TO_TICKS(100)); /* Delay for stability */

        /* Store the new password in EEPROM */
        I2C_EEPROM_sendData(PASSHANDLER_PASS_ADDR, passTemp, SHARED_PASS_LENGTH);

        /* Update the current password with the new one */
        iterator = 0;
        while (iterator < SHARED_PASS_LENGTH) {
            password[iterator] = passTemp[iterator]; /* Update the stored password */
            iterator++;
        }
    }

    /* Return success status of the password update */
    return (g_dataSend == SHARED_SUCCESS);
}

