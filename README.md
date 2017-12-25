# ESP-01 SEMAPHORE

ESP-01 Wifi Semaphore

Red pin = GPIO2  
Green pin = GPIO0  

Usage:  
* change your ESP-01 name in auxiliar.ino on dweetThingName constant  
* create assids.ino file on same arduino project folder with following model:  
	```c
	
        const int COLS = 2;  
        const int ROWS = 3;  
        const char* WIFI_REPO[COLS][ROWS] = {  
        	{"SSID1", "SSID2", "SSID3"},  
        	{"PASSWORD1", "PASSWORD2", "PASSWORD3"}  
        };  
        	
	```    
* change SSID's with your own **SSID**s  
* Upload to ESP-01  
* Get your ESP-01 IP address: https://dweet.io/follow/your_dweetThingName  
* Interact with your ESP-01: http://your_ip_address/gpio/type_semaphore_status  
* Example: http://your_ip_address/gpio/green  
* Possible status: green, red and off  
