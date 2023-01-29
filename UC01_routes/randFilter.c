#include <stdio.h>
#include <stdlib.h>
#include <string.h>

randFilter () {
	
int rayonRoute;
int routeType;
int routesLength;
int multimedia;
int randNumFiltr;
char randStrFiltr[30];
char pahtFiltr[30] = "filters=";
char pathRoutesLength[30] = "routesLength=";
char categories[30] = "[categories]=";
char media[30] = "[media]=";
char lengthTo[30] = "[length][to]=";
char lengthFrom[30] = "[length][from]=";
char lengthToNum[30];

srand(time(NULL));

switch(rand() % 4) {
	case 0:
		randNumFiltr = rand() % (atoi(lr_eval_string("{rayonRoute_count}"))) + 1;
		sprintf(randStrFiltr,"{rayonRoute_%d}", randNumFiltr);
		strcat(pahtFiltr, randStrFiltr);
		strcat(categories, randStrFiltr);
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
	case 1:
		randNumFiltr = rand() % (atoi(lr_eval_string("{routeType_count}"))) + 1;
		sprintf(randStrFiltr,"{routeType_%d}", randNumFiltr);
		strcat(pahtFiltr, randStrFiltr);
		strcat(categories, randStrFiltr);
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
	case 2:
		randNumFiltr = rand() % (atoi(lr_eval_string("{routesLength_count}"))) + 1;
		sprintf(randStrFiltr,"{routesLength_%d}", randNumFiltr);
		sprintf(lengthToNum,"{routesLengthNum_%d}", randNumFiltr);
		strcat(pathRoutesLength, randStrFiltr);
		if (randNumFiltr == 4) {
			strcat(lengthFrom, lengthToNum);
			lr_save_string(lr_eval_string(lengthFrom), "filterJSON");
		} else {
			strcat(lengthTo, lengthToNum);
			lr_save_string(lr_eval_string(lengthTo), "filterJSON");
		}
		lr_save_string(lr_eval_string(pathRoutesLength), "filtr");
		break;
	case 3:
		randNumFiltr = rand() % (atoi(lr_eval_string("{multimedia_count}"))) + 1;
		sprintf(randStrFiltr,"{multimedia_%d}", randNumFiltr);
		strcat(pahtFiltr, randStrFiltr);
		strcat(media, randStrFiltr);
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(media), "filterJSON");
		break;
	default :
		break;
}

}