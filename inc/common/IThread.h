#ifndef ITHREAD_H
#define ITHREAD_H

#include <pthread.h>

namespace common
{

/**
 * Klasa ułatwiająca tworzenie wątków i zarządzanie nimi.
 * Jest oparta o possix threads.
 */
class IThread
{
public:
/**
 * Inicjalizuje wątek
 */
	IThread();
/**
 * Rozpoczyna działanie wątku
 */
	void run();
/**
 * Oczekuje na zakończenie działania wątku
 */
	void wait();
/**
 * Wirtualny destruktor umożliwia dziedziczenie. Należy uważać na runtime error 'pure virtual error called'
 */
	virtual ~IThread() { }
protected:
/**
 * Metoda wykonywana po wywołaniu metody run()
 */
	virtual void* start_routine() = 0;
private:
	pthread_t thread;
	static void* static_routine(void* arg);
};

}

#endif // ITHREAD_H
