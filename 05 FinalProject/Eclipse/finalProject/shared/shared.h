/******************************************************************************
 * File Name: shared.h
 *
 * Description: This file defines shared constants used across the application
 *              for various status codes, actions, and system states.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *******************************************************************************/

#ifndef APP_SHARED_H_
#define APP_SHARED_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Success status code */
#define SHARED_SUCCESS          0x03

/* Failure status code */
#define SHARED_FAIL             0x04

/* Code for checking if the password exists */
#define SHARED_CHECK_PASS_EXIST 0x05

/* Code for updating the password */
#define SHARED_UPDATE_PASS      0x06

/* Code indicating the passwords do not match */
#define SHARED_PASS_DONT_MATCH  0x07

/* Code to turn the buzzer ON */
#define SHARED_BUZZER_ON        0x08

/* Code to turn the buzzer OFF */
#define SHARED_BUZZER_OFF       0x09

/* Command to open the door */
#define SHARED_OPEN_DOOR        '+'

/* Command to change the password */
#define SHARED_CHANGE_PASS      '-'

/* Code indicating waiting for people */
#define SHARED_WAIT_PEOPLE      0x0A

/* Code indicating the door is being locked */
#define SHARED_LOCKING_DOOR     0x0B

/* Code indicating the door is closed */
#define SHARED_DOOR_CLOSED      0x0C

/* The length of the password */
#define SHARED_PASS_LENGTH      5

#endif /* APP_SHARED_H_ */
