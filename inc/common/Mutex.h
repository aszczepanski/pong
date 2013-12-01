#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

namespace common
{

/**
 * Klasa umożliwiająca zablokowanie dostępu do sekcji krytycznej. Wrapper na possix threads.
 */
class Mutex
{
public:
/**
 * Inicjalizuje zamek.
 */
	Mutex();
/**
 * Blokuje zamek
 */
	void lock();
/**
 * Odblokowuje zamek
 */
	void unlock();
/**
 * Zwalnia zasoby i niszczy zamek
 */
	~Mutex();
private:
	pthread_mutex_t mutex;
};

}

#endif // MUTEX_H
