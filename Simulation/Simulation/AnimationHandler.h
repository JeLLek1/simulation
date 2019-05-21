#pragma once
class AnimationHandler
{
private:
	//Ilo�� klatek ka�dej animacji
	static const unsigned int MAX_STEP = 5;
	//Aktualny krok animacji
	unsigned int currentStep;
	//Czas, potrzebny do przej�cia do kolejnej klatki
	float updateTime;
	//Ilo�� czasu, kt�ra min�a od ostatniej zmiany klatki
	float updateTimeLast;
public:
	//zwraca aktualn� klatk�
	unsigned int returnStep();
	//aktualizuje klatki animacji w zale�no�ci od czasu
	void update(const float dt);
	AnimationHandler(const float updateTime);
	~AnimationHandler();
};

