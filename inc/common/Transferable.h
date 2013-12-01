#ifndef TRANSFERABLE_H
#define TRANSFERABLE_H

namespace common
{

/**
 * Interfejs klas możliwych do przesyłania między klientem i serwerem
 */
class Transferable
{
public:
/**
 * Dodaje odpowiednie wartości do tablicy wysyłanej do serwera
 * @param startPos pozycja w tablicy od której ma zacząć wprowadzanie danych
 */
	virtual void send(unsigned char*, int startPos) const = 0;
/**
 * Dodaje odpowiednie wartości do tablicy wysyłanej do serwera
 * @param startPos pozycja w tablicy od której ma zacząć odczytywanie danych
 */
	virtual void receive(unsigned char*, int startPos) = 0;

/**
 * Wirtualny destruktor umożliwia dziedziczenie
 */
	virtual ~Transferable() { }
};

}

#endif // TRANSFERABLE_H
