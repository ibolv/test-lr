#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Action()
{

double time_elapsed, duration, waste;
merc_timer_handle_t timer;

web_set_sockets_option("SSL_VERSION", "2&3");

lr_start_transaction("UC01_TC01_openMain");

	web_url("um.mos.ru", 
		"URL=https://{host}/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t687.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);

lr_end_transaction("UC01_TC01_openMain", LR_AUTO);

web_reg_save_param_regexp(
		"ParamName=rayonRoute",
		"RegExp=\\{\\\"id\\\":\\d*,\\\"slug\\\":\\\"([\\w-]+)\\\",\\\"image\\\":\\w*,\\\"active\\\":\\w*,\\\"parent\\\":458",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);
		
web_reg_save_param_regexp(
		"ParamName=routeType",
		"RegExp=\\{\\\"id\\\":\\d*,\\\"slug\\\":\\\"([\\w\\d-]+)\\\",\\\"image\\\":\\w*,\\\"active\\\":\\w*,\\\"parent\\\":242",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);

web_reg_save_param_regexp(
		"ParamName=routesLength",
		"RegExp=\\\"slug\\\":\\\"(\\w*)\\\",\\\"nameWithT\\\":\\\"\\w*\\\"",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);
		
web_reg_save_param_regexp(
		"ParamName=routesLengthNum",
		"RegExp=\\\"slug\\\":\\\"(\\w*)\\\",\\\"nameWithT\\\":\\\"\\w*\\\"[,\\\"\\w:\\[\\]]*\\\":(\\d+)",
		"NotFound=error",
		"Group=2",
		"Ordinal=All",
		LAST);


web_reg_save_param_regexp(
		"ParamName=multimedia",
		"RegExp=\\{\\\"id\\\":\\\"(\\w*)\\\",[\\w\\d\\\",:]+:\\[\\]\\}",
		"NotFound=error",
		"Group=1",
		"Ordinal=All",
		LAST);



lr_start_transaction("UC01_TC02_openRoutes");

	web_url("routes", 
		"URL=https://{host}/routes", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t718.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);
	
lr_end_transaction("UC01_TC02_openRoutes", LR_AUTO);

		
randFilter ();

		
/*web_reg_save_param_regexp(
		"ParamName=route",
		"RegExp=\\{\\\"id\\\":\\d*,\\\"slug\\\":\\\"([\\w\\d-]+)\\\",\\\"time\\\"",
		"NotFound=warning",
		"Group=1",
		"Ordinal=All",
		LAST);
*/		


		
lr_start_transaction("UC01_TC03_chooseRandFilterAndRoute");

	web_url("routes_3", 
		"URL=https://{host}/routes?{filtr}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t739.inf", 
		"Mode=HTML", 
		LAST);
		
timer = lr_start_timer();

web_reg_save_param_json(
		"ParamName=route",
		"QueryString=$.result[*].slug",
		"NotFound=warning",
		"SelectAll=Yes",
		LAST);
		
time_elapsed = lr_end_timer(timer);
waste = time_elapsed * 1000;
lr_wasted_time(waste); 

	web_url("routes_6", 
		"URL=https://{host}/api/v1/routes?page=1&filter{filterJSON}",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://{host}/routes?{filtr}", 
		"Snapshot=t754.inf", 
		"Mode=HTML", 
		LAST);
		
	timer = lr_start_timer();
	
	if (atoi(lr_eval_string("{route_count}")) == 0) {
	lr_end_transaction("UC01_TC03_chooseRandFilterAndRoute", LR_AUTO);
	return 0;
	}

	
lr_save_string(lr_paramarr_random("route"), "routeRand");


web_reg_save_param_regexp(
		"ParamName=audiofile",
		"RegExp=name\\\":\\\"\\D*\\\",\\\"audioFile\\\":\\\"(.*)\\\",\\\"announce",
		"NotFound=warning",
		"Group=1",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);


web_reg_save_param_regexp(
		"ParamName=object",
		"RegExp=</div><a href=\\\"([\\w-/]*)\\\">",
		"NotFound=warning",
		"Group=1",
		"Ordinal=All",
		SEARCH_FILTERS,
    	"Scope=BODY",
		"RequestUrl=*/routes/*",
		LAST);
		
	time_elapsed = lr_end_timer(timer);
	waste = time_elapsed * 1000;
	lr_wasted_time(waste); 	

	web_url("routeRand", 
		"URL=https://{host}/routes/{routeRand}",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://{host}/routes?{filtr}", 
		"Snapshot=t804.inf", 
		"Mode=HTML", 
		EXTRARES,  
		LAST);

lr_end_transaction("UC01_TC03_chooseRandFilterAndRoute", LR_AUTO);



/*while (complite1) {
	
leftRange = chunkRange * countRange;

rightRange = chunkRange * (countRange + 1);

if ((atoi(lr_eval_string("{totalLength}")) - rightRange) <= chunkRange && countRange !=0) {
	rightRange = atoi(lr_eval_string("{totalLength}"));
	complite1 = false;
}

lr_save_int(leftRange, "leftRange");
lr_save_int(rightRange, "rightRange");

web_reg_save_param_regexp(
		"ParamName=totalLength",
		"RegExp=Content-Range: bytes \\d*-\\d*\\/(\\d*)",
		"NotFound=warning",
		"Group=1",
		"Ordinal=1",
		LAST);

*/

if (strcmp(lr_eval_string("{audiofile}"),"") != 0) {
	
web_add_header("Accept","audio/webm,audio/ogg,audio/wav,audio/*;q=0.9,application/ogg;q=0.7,video/*;q=0.6,*/*;q=0.5");
web_add_header("Range", "bytes=0-");
web_add_header("Sec-Fetch-Dest", "audio");
web_add_header("Sec-Fetch-Mode", "no-cors");
web_add_header("Sec-Fetch-Site", "same-origin");
web_add_header("Accept-Encoding", "identity");


lr_start_transaction("UC01_TC04_listen");
web_url("listen",	

		"URL=https://{host}{audiofile}", 
		"TargetFrame=", 
		"Resource=0",
		"RecContentType=audio/mpeg",
		"Referer=https://{host}/routes/{routeRand}",
		"Snapshot=t805.inf",
		"Mode=HTML",
		EXTRARES, 
		LAST);
lr_end_transaction("UC01_TC04_listen", LR_AUTO);
}
/*countRange = countRange + 1;

}
*/

lr_save_string(lr_paramarr_random("object"), "objectRand");

lr_start_transaction("UC01_TC05_openRandHouse");


	web_url("object", 
		"URL=https://{host}{objectRand}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t833.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);
		
lr_end_transaction("UC01_TC05_openRandHouse", LR_AUTO);


	return 0;
}