// FILE IS emergencyRoomMain.c
/*
Description:

This is an exmaple of a test program that you should write to test your code.  
The testing is not complete because it checks only a subset of the required functionality
and not all aspects of it. 

This code will not be used by the TAs to test your code.


Revisions:
Doron Nussbaum 2022  File created

 Copyright Doron Nussbaum 2022

*/


/************************************************************************/
// INCLUDES

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "patient.h"
#include "linked_list_hospital.h"

#define NUMBER_OF_TEST_PATIENTS 20


#define CONTINUE {printf("hit <cr> to continue \n"); getchar();}

int populatePatient(int arrivalTime, PatientInfo *patient);


int main(int argc, char* argv[])
{
	ListNode *patientsList = NULL;
	ListNode *p = NULL;
	int i;
    int rc = 0;
    FILE *fid = NULL;
    PatientInfo patient;
    static int initRand = 0;	
    static int arrivalTime = 1;




	if (!initRand) {
		srand(15857);
		initRand ++;
	}


 	// creating a list
	for (i = 0; i < NUMBER_OF_TEST_PATIENTS; i++) {
	// add code for testing
		populatePatient(arrivalTime, &patient);
		printPatient(&patient);
		insertToList(&patientsList, &patient);
		arrivalTime++;
	}


	// testing printing the list forward and in reverse
	printf("\n\n--------printing the list-------- \n\n");

	printList(patientsList,printPatient);

	printf("printing the list in reverse\n");

	printListReverse(patientsList,printPatient);

	// checking number of patients by priority
	printf("\nprinting the patients by priorityLevel \n");
	for (i = 0; i < 10; i++) {
		ListNode * p = searchFirstPatientByPriority(patientsList, i, &patient);
		if (p == NULL) printf("no patient with priority %d\n",i);
		else printPatient(&patient);

	}

	// testing  counting 
	printf("\n number of patients in emergency room = %d\n", numPatientsInEmergency(patientsList));

	printf("\ncounting patients by priority \n");
	for (i = 0; i < 10; i++) {
		printf("There are %d patients with priority %d \n", countPatients(patientsList, i), i);
	}

	// testing priority queue by higher priority
	printf("Patient to be treated by maximum priority\n ");

	for (i = 0; i <5; i++) {
		arrivalTime++;
		rc = retrieveNextPatientByCriteria(&patientsList, comparePatients, arrivalTime, &patient);
		if (rc == 1) {
			printf(" no more patients \n");
			break;
		} else {
			printf("next patient to be treated \n ");
			printPatient(&patient);
		}
	}

	// testing priority queeue by highest priority level
	printf("Patient to be treated by priority\n ");

	for (i = 9; i >= 0; i--) {
		rc = retrieveNextPatientByPriority(&patientsList, i, &patient);
		//printf("priority = %d rc = %d \n", i, rc);
		if (rc == 0) break;
	}
	if (rc == 0) { 
		printPatient(&patient);
	} else {
		printf("no patients to be treated \n");
	}

	// testing the list revers function
	patientsList = reverse(patientsList);


	printf("printing list after it was reversed \n");
	printList(patientsList,printPatient);


	return 0;
}


	

/***************************************************************************/
/* purpose: the function populate the patient info for testing

output
patient - allocated memory to the struct pointer which the function assigns values.




*/

int populatePatient(int arrivalTime, PatientInfo *patient)
{
	int j;
	char *first[10] = { "John", "Don", "Edna", "Bev", "Miya", "Jennifer", "Mark","Leslie","Ian","Fraser" };
	char *family[10] = { "Broker", "Smith", "Tower", "Little", "Bronson" , "Guy","Parrot","Klein", "Snow","Dual"};
	char *highPriorMedicalProblem[5] = { "High Fever", "COVID", "Drug Overdose", "Concussion", "Car Accident" };
	char *lowPriorMedicalProblem[5] = { "Low Fever", "Earaches", "Broken Bone", "Nosebleed", "Mild concussion"};
	

	// populate the first  name using a random i ndex to the first name array 
	j = rand() % 10;
	// copy the first name to the structure pointed by p using strcpy
	strncpy(patient->firstName, first[j], NAME_LENGTH);

	// populate the family  name using a random i ndex to the first name array 
	j = rand() % 10;
	// copy the family name to the structure pointed by p using strcpy
	strncpy(patient->familyName, family[j], NAME_LENGTH);

	// populate the patient id using the random numnber in the range of 0-4096  
	patient->id = rand() % 15000;

	// populate arrival time 
	patient->arrivalTime = arrivalTime;

	// populate the priorty level and the medical condition 
	patient->priorityLevel = rand() % 10;
	switch(patient->priorityLevel) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			strncpy(patient->medicalProblem, lowPriorMedicalProblem[patient->priorityLevel], sizeof(patient->medicalProblem)-1);
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			strncpy(patient->medicalProblem, highPriorMedicalProblem[patient->priorityLevel-5], sizeof(patient->medicalProblem)-1);
			break;
		default:
			printf("should not be here priorityLevel = %d \n", patient->priorityLevel);
			return(1);
			break;
	}

	return(0);
}






