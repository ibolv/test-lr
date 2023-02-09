Action()
{
	
int randNumFilter;
double time_elapsed, duration, waste;
merc_timer_handle_t timer;

web_set_sockets_option("SSL_VERSION", "2&3");

lr_start_transaction("UC02_building");


lr_start_transaction("UC02_TR01_openMain");

	web_url("um.mos.ru", 
		"URL=https://{host}/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);

lr_end_transaction("UC02_TR01_openMain", LR_AUTO);


lr_think_time(rand() % 5 + 1);


web_reg_save_param_regexp(
		"ParamName=path",
		"RegExp=page\\\":\\\"/houses\\\".*\\\"buildId\\\":\\\"(\\w*)",
		"NotFound=warning",
		"Group=1",
		"Ordinal=1",
		LAST);


lr_start_transaction("UC02_TR02_openHouse");

	web_url("houses_2", 
		"URL=https://{host}/houses", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		EXTRARES,
		LAST);
		
randNumFilter = randFilterReg();
		
	web_url("houses_7", 
		"URL=https://um.mos.ru/_next/data/{path}/ru/houses.json",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://{host}/routes", 
		"Snapshot=t687.inf", 
		"Mode=HTML", 
		LAST);
		
lr_end_transaction("UC02_TR02_openHouse",LR_AUTO);


randFilter(randNumFilter);

lr_think_time(rand() % 5 + 1);


lr_start_transaction("UC02_TR03_useFilter");

	web_url("houses_4", 
		"URL=https://{host}/houses?{filtr}", 
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
		"URL=https://{host}/api/v1/houses?page=1&filter{filterJSON}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://{host}/houses?{filtr}", 
		"Snapshot=t95.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);
		
timer = lr_start_timer();
	
if (atoi(lr_eval_string("{house_count}")) == 0) {
	lr_end_transaction("UC02_TR03_useFilter", LR_FAIL);
	lr_end_transaction("UC02_building", LR_FAIL);
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
		"URL=https://{host}/houses/{houseRand}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t137.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);
		
lr_end_transaction("UC02_TR03_useFilter",LR_AUTO);

lr_think_time(rand() % 5 + 1);

lr_start_transaction("UC02_TR04_listen");

if (strcmp(lr_eval_string("{audiofile}"),"") != 0) {
	
web_add_header("Accept","audio/webm,audio/ogg,audio/wav,audio/*;q=0.9,application/ogg;q=0.7,video/*;q=0.6,*/*;q=0.5");
web_add_header("Range", "bytes=0-");
web_add_header("Sec-Fetch-Dest", "audio");
web_add_header("Sec-Fetch-Mode", "no-cors");
web_add_header("Sec-Fetch-Site", "same-origin");
web_add_header("Accept-Encoding", "identity");

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
		
} else {
lr_fail_trans_with_error("UC02_TR04_listen");	
lr_fail_trans_with_error("UC02_building");	
}

lr_end_transaction("UC02_TR04_listen", LR_AUTO);

lr_end_transaction("UC02_building", LR_AUTO);

	return 0;
}