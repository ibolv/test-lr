#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void randFilter (int randF) {
	
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

switch(randF) {
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
		lr_save_string(lr_paramarr_random("randFilter"), "randFilterDefin");
		strcat(pahtFiltr, lr_eval_string("{randFilterDefin}"));
		strcat(media, lr_eval_string("{randFilterDefin}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(media), "filterJSON");
		break;
	default :
		lr_save_string(lr_paramarr_random("randFilter"), "randFilterDefin");
		strcat(pahtFiltr, lr_eval_string("{randFilterDefin}"));
		strcat(categories, lr_eval_string("{randFilterDefin}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
}

}


int randFilterReg() {
	int randNum;
	
	srand(time(NULL));
	randNum = rand() % 4;
	lr_save_int(randNum, "randNumFilter");
	switch(randNum) {
		case 2:
		
			web_reg_save_param_json(
			"ParamName=routesLength",
			"QueryString=$.pageProps.initialState.filters.data[{randNumFilter}].children[*].slug",
			"NotFound=warning",
			"SelectAll=Yes",
			LAST);
		
			web_reg_save_param_json(
			"ParamName=routesLengthNum",
			"QueryString=$.pageProps.initialState.filters.data[{randNumFilter}].children[*].[to,from]",
			"NotFound=warning",
			"SelectAll=Yes",
			LAST);

			break;
		default :
			web_reg_save_param_json(
			"ParamName=randFilter",
			"QueryString=$.pageProps.initialState.filters.data[{randNumFilter}].children[*].slug",
			"NotFound=warning",
			"SelectAll=Yes",
			LAST);
			break;
	} 
	return randNum;
}