#include "./sync_printer.h"
#include <vector>
#include <chrono>
#include <thread>

int main(){
	std::vector<std::thread*> t(100);
	int cnt = 0;
	for(int e = 0; e < 100; e++){
		t[e] = new std::thread([&cnt](){
			while(1){
				sync_cout << "Aaaaaa " << cnt++ << " funcionando " << " isso wtf" << sync_endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}				
		});
	}
	for(int e = 0; e < 100; e++){
		t[e]->join();
	}
	sync_cout << "Aaaaaa " << cnt++ << " funcionando " << " isso wtf" << sync_endl;
}
