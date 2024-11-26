#include <iostream> 
#include <string>
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <algorithm> 

using namespace std;

size_t WriteCallBack(void* contents, size_t size, size_t nmemb, string* userp){
	size_t totalsize = size * nmemb; 
	userp->append((char*)contents, totalsize);
	return totalsize; 


}

void getWeather(string city,string newCity){

	string apiKey = "cea1079d39470bd4ee199b298966b761";
	CURL* curl; 
	CURLcode res; 
	string readBuffer; 
	string Url = "https://api.openweathermap.org/data/2.5/weather?q=" + newCity + "&appid=" + apiKey + "&units=metric";



	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, Url.c_str()); 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);


	res = curl_easy_perform(curl);

	if (res != CURLE_OK){
		cout << "cURL eror: " << curl_easy_strerror(res) << endl;

	
	}else { 
		Json::Value jsonData;
		Json::CharReaderBuilder readerBuilder; 
		std::istringstream iss(readBuffer); 
		string errs; 
		if (Json::parseFromStream(readerBuilder, iss, &jsonData, &errs)){
			cout << "Weather in " << city << endl ; 
			cout << "Temperature: " << jsonData["main"]["temp"].asFloat() << "°C" << endl; 
			cout << "Weather: " << jsonData["weather"][0]["description"].asString() << endl; 
		
		}else {
			cout << "Json Error: " << errs << endl ;
		}
		
	
	}
}
string replaceSpace(string city){
	string newCity; 
	for (char c: city){
		if (c == ' '){
			newCity += "%20"; 

		}else {
			newCity += c; 
		}
		
	}
	return newCity; 

}

int main(){
	string city, newcity; 
	cout << "Please insert the city you would like to check: "; 
	getline(cin,city);
	newcity = replaceSpace(city); 
	getWeather(city,newcity); 
	return 0 ; 
}


