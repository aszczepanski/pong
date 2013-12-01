#ifndef DRAWER_H
#define DRAWER_H

#include <cstddef>

namespace common
{

class ICommunicator;
class SharedMemory;
class Camera;

/**
 * Klasa odpowiadająca za rysowanie poszczególnych elementów rozgrywki.
 * Drawer pobiera również dane od użytkownika, z myszki bądź kamery.
 * Wykorzystuje bibliotekę SFML.
 */

class Drawer
{

public:
/**
 * Konstuktor inicjalizujący odpowiednie referencje i wskaźnik
 * @param sharedMemory Referencja do obiektu pamięci współdzielonej między wątkami
 * @param communicator Referencja do komunikatora, który umożliwia wymianę danych z serwerem lub silnikiem gry
 * @param camera Wskaźnik do kamery, domyślnie Drawer korzysta z myszki
 */
	Drawer(common::SharedMemory& sharedMemory, ICommunicator& communicator, Camera* camera = NULL);
/**
 * Metoda rozpoczynająca rysowanie gry
 */
	void run();
/**
 * Metoda ustawiająca kamerę
 * @param camera Wskaźnik do kamery, jeśli NULL to ustawiane jest korzystanie z myszki
 */
	void setCamera(Camera* camera);

private:
	common::SharedMemory& sharedMemory;
	ICommunicator& communicator;
	Camera* camera;
};

}

#endif // DRAWER_h
