#pragma once
class AnimationHandler
{
private:
	//Iloœæ klatek ka¿dej animacji
	static const unsigned int MAX_STEP = 5;
	//Aktualny krok animacji
	unsigned int currentStep;
	//Czas, potrzebny do przejœcia do kolejnej klatki
	float updateTime;
	//Iloœæ czasu, która minê³a od ostatniej zmiany klatki
	float updateTimeLast;
public:
	//zwraca aktualn¹ klatkê
	unsigned int returnStep();
	//aktualizuje klatki animacji w zale¿noœci od czasu
	void update(const float dt);
	AnimationHandler(const float updateTime);
	~AnimationHandler();
};

