#include <iostream>
#include <thread>
#include "skCrypt.hpp"
#include "xorstr.hpp"
#include "protection.hpp"
#include "console.hpp"
#include "other.hpp"
#include "KeyAuth.hpp"
#include "api.h"
#include "driver.h"
#include "injector.h"
#include "drv_utils.h"
#include "cheat.h"
using namespace KeyAuth;
using namespace std;

std::string name = XorStr("AnkrWare").c_str();
std::string ownerid = XorStr("efqr11cAl4").c_str();
std::string secret = XorStr("2ade68f999c592c9cee8a22853ed0b47184871acee5c56d3b0996aa6e519bc07").c_str();
std::string version = XorStr("1.0").c_str();

api KeyAuthApp(name, ownerid, secret, version);


size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}
void download(std::string fileid, std::string output) {

	auto iv = encryption::sha256(encryption::iv_key());
	std::string data =
		XorStr("type=").c_str() + encryption::encode(XorStr("file").c_str()) +
		XorStr("&fileid=").c_str() + encryption::encrypt(fileid, secret, iv) +
		XorStr("&name=").c_str() + encryption::encode(name) +
		XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
		XorStr("&init_iv=").c_str() + iv;

	CURL* curl;
	FILE* fp;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(output.c_str(), "wb");
		curl_easy_setopt(curl, CURLOPT_URL, XorStr("https://keyauth.com/api/v3/").c_str());
		curl_easy_setopt(curl, CURLOPT_NOPROXY, XorStr("keyauth.com").c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, XorStr("KeyAuth").c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		curl_easy_setopt(curl, CURLOPT_PINNEDPUBLICKEY, XorStr("sha256//UjJQOuTpgenjm6zOasOClsM8Ua6m6IJ09jzwC6YYDh0=").c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
		fclose(fp);
	}
}
std::string tm_to_readable_time(tm ctx) {
	char buffer[25];

	strftime(buffer, sizeof(buffer), "%m/%d/%y", &ctx);

	return std::string(buffer);
}

void login()
{
	if (std::filesystem::exists("C:\\ProgramData\\" + name))
	{
		std::string key;
		std::ifstream InFile("C:\\ProgramData\\" + name, std::ios::in);
		std::getline(InFile, key);
		InFile.close();
		std::cout << skCrypt("\n\n Logging in with old License Key: ");
		std::cout << key;
		Sleep(1500);

		if (KeyAuthApp.login(key))
		{
		}
		else
		{
			std::string del = "C:\\ProgramData\\" + name;
			remove(del.c_str());
			goto A;
		}
	}
	else
	{
	A:
		std::cout << skCrypt("\n\n Please Enter License Key: ");
		bool authed = false;
		while (authed == false)
		{
			std::string serial;
			std::cin >> serial;
			if (KeyAuthApp.login(serial)) {
				std::ofstream OutFile("C:\\ProgramData\\" + name, std::ios::out);
				OutFile << serial;
				OutFile.close();
				authed = true;
			}
			else {
				Sleep(2500);
				system(skCrypt("CLS"));
				goto A;
			}
		}
	}
}


int main()
{
    thread dbg(loopDbg);
    MakeSexy();
    SetConsoleTitleA(random_string().c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); 
 //  closeProcesses();

    KeyAuthApp.init(); 
    system(skCrypt("CLS"));
    login();

    cout << skCrypt("\n\n Status Active: (Expires: ");
    cout << tm_to_readable_time(KeyAuthApp.user_data.expiry);
    cout << skCrypt(")\n ");

    cout << skCrypt("\n Loading driver...\n");
    start_driver();
    cout << skCrypt(" Driver Loaded!\n");

    cout << skCrypt(" Loading cheat!\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
    face_injecor_v2(skCrypt("UnrealWindow"));
    cout << skCrypt(" Cheat loaded!\n");
}

