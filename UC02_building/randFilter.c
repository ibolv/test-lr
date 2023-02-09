#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void randFilter(int randNumFiltr) {
	
char pahtFiltr[30] = "filters=";
char categories[30] = "[categories]=";
char media[30] = "[media]=";

switch(randNumFiltr) {
	case 8:
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
	randNum = rand() % 9;
	lr_save_int(randNum, "randNumFilter");
	
	web_reg_save_param_json(
		"ParamName=randFilter",
		"QueryString=$.pageProps.initialState.filters.data[{randNumFilter}].children[*].slug",
		"NotFound=warning",
		"SelectAll=Yes",
		LAST);
	
return randNum;
}