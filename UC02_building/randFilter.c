#include <stdio.h>
#include <stdlib.h>
#include <string.h>

randFilter() {
	
int randNumFiltr;
char pahtFiltr[30] = "filters=";
char categories[30] = "[categories]=";
char media[30] = "[media]=";
	
srand(time(NULL));

switch(rand() % 9) {
	case 0:
		lr_save_string(lr_paramarr_random("administrativnyyOkrug"), "administrativnyyOkrugRand");
		strcat(pahtFiltr, lr_eval_string("{administrativnyyOkrugRand}"));
		strcat(categories, lr_eval_string("{administrativnyyOkrugRand}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
	case 1:
		lr_save_string(lr_paramarr_random("architecturalStyle"), "architecturalStyleRand");
		strcat(pahtFiltr, lr_eval_string("{architecturalStyleRand}"));
		strcat(categories, lr_eval_string("{architecturalStyleRand}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
	case 2:
		lr_save_string(lr_paramarr_random("virtualTours"), "virtualToursRand");
		strcat(pahtFiltr, lr_eval_string("{virtualToursRand}"));
		strcat(categories, lr_eval_string("{virtualToursRand}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
	case 3:
		lr_save_string(lr_paramarr_random("cultb"), "cultbRand");
		strcat(pahtFiltr, lr_eval_string("{cultbRand}"));
		strcat(categories, lr_eval_string("{cultbRand}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
	case 4:
		lr_save_string(lr_paramarr_random("memorialValueHouse"), "memorialValueHouseRand");
		strcat(pahtFiltr, lr_eval_string("{memorialValueHouseRand}"));
		strcat(categories, lr_eval_string("{memorialValueHouseRand}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
	case 5:
		lr_save_string(lr_paramarr_random("moskovskayaRestavraciya"), "moskovskayaRestavraciyaRand");
		strcat(pahtFiltr, lr_eval_string("{moskovskayaRestavraciyaRand}"));
		strcat(categories, lr_eval_string("{moskovskayaRestavraciyaRand}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
	case 6:
		lr_save_string(lr_paramarr_random("purposeHouse"), "purposeHouseRand");
		strcat(pahtFiltr, lr_eval_string("{purposeHouseRand}"));
		strcat(categories, lr_eval_string("{purposeHouseRand}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
	case 7:
		lr_save_string(lr_paramarr_random("age"), "ageRand");
		strcat(pahtFiltr, lr_eval_string("{ageRand}"));
		strcat(categories, lr_eval_string("{ageRand}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(categories), "filterJSON");
		break;
	case 8:
		lr_save_string(lr_paramarr_random("multimedia"), "multimediaRand");
		strcat(pahtFiltr, lr_eval_string("{multimediaRand}"));
		strcat(media, lr_eval_string("{multimediaRand}"));
		lr_save_string(lr_eval_string(pahtFiltr), "filtr");
		lr_save_string(lr_eval_string(media), "filterJSON");
		break;
	default :
		break;

}

}