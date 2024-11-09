#ifndef PUNTAJE_H
#define PUNTAJE_H


class Puntaje
{
public:
	Puntaje();
	bool grabarEnDisco();
	bool leerDeDisco();
	void setPuntaje(int);
	int getPuntaje();
private:
	int puntajeMax;
};

#endif // PUNTAJE_H
