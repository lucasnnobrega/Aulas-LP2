#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#define BUFFERSIZE 20

using namespace std;

int sharedBuffer[BUFFERSIZE] = {0};
Worker workers[BUFFERSIZE];

condition_message_variable{
	mutex cvMutex;
	mutex outgoingMessageMutex;
	int nextOutgoingMessage;
	condition_variable cv;
	public:
	int wait(){
		//Espere até que alguem o notifique. Quando acordado, capture o valor atual de nextOutgoingMessage
		//e desbloquei o semaforo associado a ela, efetivamente avisando aos sinalizadores que a mensagem
		//ja foi capturada e que o proximo sinalizador pode notificar a proxima pessoa.
		unique_lock<mutex> lck(cvMutex);
		int message;
		cv.wait(lck);
		message = currentMessage;
		messageMutex.unlock();
		return message;
	}
	int notify_one(int message){
		//Modifique o valor de nextOutgoingMessage e acorde um dos trabalhadores. Enquanto a ultima mensagem não foi
		//capturada por algum trabalhador, espere até que isso aconteca.
		//
		//WARNING: Implica que quando nao ha trabalhadores esperando e é feita a tentativa de notificar alguem, dormirá para sempre
		//TODO: Mudar o comportamento alertado. 
		lock_guard<mutex> guard(cvMutex);
		currentMessage.lock();
		currentMessage = message;
		cv.notify_one();
	}
};

class monitorInterface {
	mutex cvMutex;
	condition_message_variable okToConsume;
	condition_variable okToProduce;
	public:
	int requestSlot(){
		
	}
	int wakeConsumer(){

		
	}
};

int main(){

}
