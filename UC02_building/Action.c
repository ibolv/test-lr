#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Action()
{
	
double time_elapsed, duration, waste;
merc_timer_handle_t timer;
	
//web_set_sockets_option("SSL_VERSION", "TLS1.1");
web_set_sockets_option("SSL_VERSION", "2&3");
lr_start_transaction("UC02_TC01_openMain");

	web_url("um.mos.ru", 
		"URL=https://um.mos.ru/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);

lr_end_transaction("UC02_TC01_openMain", LR_AUTO);

	
web_reg_save_param_regexp(
		"ParamName=administrativnyyOkrug",
		"RegExp=\\{\\\"id\\\"\\:\\d*,\\\"slug\\\":\\\"([\\w-]*)\\\"[\\w-:,\\\"]*parent\\\":388",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);

web_reg_save_param_regexp(
		"ParamName=architecturalStyle",
		"RegExp=\\{\\\"id\\\"\\:\\d*,\\\"slug\\\":\\\"([\\w-]*)\\\"[\\w-:,\\\".\\d/]*parent\\\":2",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);

web_reg_save_param_regexp(
		"ParamName=virtualTours",
		"RegExp=\\{\\\"id\\\"\\:\\d*,\\\"slug\\\":\\\"([\\w-]*)\\\"[\\w-:,\\\".\\d/]*parent\\\":6",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);
	
web_reg_save_param_regexp(
		"ParamName=cultb",
		"RegExp=\\{\\\"id\\\"\\:\\d*,\\\"slug\\\":\\\"([\\w-]*)\\\"[\\w-:,\\\".\\d/]*parent\\\":8",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);
	
web_reg_save_param_regexp(
		"ParamName=memorialValueHouse",
		"RegExp=\\{\\\"id\\\"\\:\\d*,\\\"slug\\\":\\\"([\\w- ]*)\\\"[\\w-:,\\\".\\d/]*parent\\\":4",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);
	
web_reg_save_param_regexp(
		"ParamName=moskovskayaRestavraciya",
		"RegExp=\\{\\\"id\\\"\\:\\d*,\\\"slug\\\":\\\"([\\w- ]*)\\\",[^,]*[\\w-:,\\\".\\d/ ]*parent\\\":5",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);
	
web_reg_save_param_regexp(
		"ParamName=purposeHouse",
		"RegExp=\\{\\\"id\\\"\\:\\d*,\\\"slug\\\":\\\"([\\w- ]*)\\\",[^,]*[\\w-:,\\\".\\d/ ]*parent\\\":3",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);
		
web_reg_save_param_regexp(
		"ParamName=age",
		"RegExp=\\{\\\"id\\\"\\:\\d*,\\\"slug\\\":\\\"([\\w- ]*)\\\",[^,]*[\\w-:,\\\".\\d/ ]*parent\\\":1",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);
	

/*
web_reg_save_param_regexp(
		"ParamName=categories",
		"RegExp=\\{\\\"id\\\"\\:\\d*,\\\"slug\\\":\\\"([\\w- ]*)\\\"[\\w-:,\\\".\\d/+\\[\\]+\\u0401\\u0451\\u0410-\\u044f ]*\\\"entitySlug\\\":\\\"categories\\\"",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);
*/

web_reg_save_param_regexp(
		"ParamName=multimedia",
		"RegExp=\\{\\\"id\\\":\\\"(\\w*)\\\",[\\w\\d\\\",:]+:\\[\\]\\}",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);
		
	

lr_start_transaction("UC02_TC02_openHouse");

	web_url("houses_2", 
		"URL=https://um.mos.ru/houses", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		EXTRARES,
		LAST);
lr_end_transaction("UC02_TC02_openHouse",LR_AUTO);


randFilter();


lr_start_transaction("UC02_TC03_useFilter");

	web_url("houses_4", 
		"URL=https://um.mos.ru/houses?{filtr}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t93.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);
		
timer = lr_start_timer();
		
	web_reg_save_param_json(
		"ParamName=house",
		"QueryString=$.result[*].slug",
		"NotFound=warning",
		"SelectAll=Yes",
		LAST);
		
time_elapsed = lr_end_timer(timer);
waste = time_elapsed * 1000;
lr_wasted_time(waste); 

	web_url("houses_5", 
		"URL=https://um.mos.ru/api/v1/houses?page=1&filter{filterJSON}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://um.mos.ru/houses?{filtr}", 
		"Snapshot=t95.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);
		
timer = lr_start_timer();
	
if (atoi(lr_eval_string("{house_count}")) == 0) {
	lr_end_transaction("UC02_TC03_useFilter", LR_AUTO);
	return 0;
}
	
lr_save_string(lr_paramarr_random("house"), "houseRand");


web_reg_save_param_regexp(
		"ParamName=audiofile",
		"RegExp=\\\"audioFile\\\":\\\"([\\d\\w/ .]*)\\\",",
		"NotFound=warning",
		"Group=1",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);
		
time_elapsed = lr_end_timer(timer);
waste = time_elapsed * 1000;
lr_wasted_time(waste); 


	web_url("houseRand", 
		"URL=https://um.mos.ru/houses/{houseRand}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t137.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);
		
lr_end_transaction("UC02_TC03_useFilter",LR_AUTO);



if (strcmp(lr_eval_string("{audiofile}"),"") != 0) {
	
web_add_header("Accept","audio/webm,audio/ogg,audio/wav,audio/*;q=0.9,application/ogg;q=0.7,video/*;q=0.6,*/*;q=0.5");
web_add_header("Range", "bytes=0-");
web_add_header("Sec-Fetch-Dest", "audio");
web_add_header("Sec-Fetch-Mode", "no-cors");
web_add_header("Sec-Fetch-Site", "same-origin");
web_add_header("Accept-Encoding", "identity");


lr_start_transaction("UC02_TC04_listen");

web_url("listen",	

		"URL=https://um.mos.ru{audiofile}", 
		"TargetFrame=", 
		"Resource=0",
		"RecContentType=audio/mpeg",
		"Referer=https://um.mos.ru/routes/{routeRand}",
		"Snapshot=t805.inf",
		"Mode=HTML",
		EXTRARES, 
		LAST);
lr_end_transaction("UC02_TC04_listen", LR_AUTO);

}

	return 0;
}