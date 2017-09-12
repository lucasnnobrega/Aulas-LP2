#include "helper.h"
#include <thread>

int main(){
	std::string a("Vinicius");
	std::string b("Misael");


	Helpers::sync_cout << a << b << Helpers::endl;
	
}
