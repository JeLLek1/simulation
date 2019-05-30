#include "pch.h"
#include <vector>
#include <queue>

#include "ManAi.h"


sf::Vector2u ManAi::getNextStep(sf::Vector2u currenPos)
{
	if (!this->destination.empty())
	{
		sf::Vector2u temp = this->destination.front();
		this->destination.pop_front();
		return temp;
	}
	else return currenPos;
}

bool ManAi::dijkstraPath(ObjectType objectType, Map* map, sf::Vector2u start, sf::Vector2u end, bool seatchToEnd)
{
	this->clearDestination();
	//Tablica z wag� przej�cia do danego punktu
	std::vector<int> weight;
	//-1 to punkty, kt�re nie zosta�y na razie odwiedzone
	weight.resize(map->mapWidth() * map->mapHeight(), -1);
	//kolejka punkt�w, kt�re nale�y sprawdzi� w danej kolejno�ci
	std::queue<sf::Vector2u> tileToCheck;
	//Sprawdzamy od punktu startowego, kt�rego waga doj�cia samego do siebie jest r�wna 0
	weight[map->cordToTabPos(start)] = 0;
	tileToCheck.push(start);
	//Tablica przesuni�cia do s�siednich kratek
	sf::Vector2u helper[4] = { sf::Vector2u(1,0), sf::Vector2u(0,1), sf::Vector2u(-1,0), sf::Vector2u(0,-1) };
	while (tileToCheck.size() > 0) {
		for (int i = 0; i < 4; i++) {
			//Punk kt�ry sprawdzamy na oko�o pierwszego punktu w kolejce
			sf::Vector2u temp = tileToCheck.front() + helper[i];
			//Wystarzy sprawdzi� tylko czy jest mniejsze od szeroko�ci (wysoko�ci mapy), bo jak mniejsze od 0 to uint si� przepe�ni
			if (temp.x<map->mapWidth() && temp.y<map->mapHeight() && weight[map->cordToTabPos(temp)]==-1) {
				if (!map->returnTile(temp)->returnCollision() && (!seatchToEnd || ((temp.x != end.x || temp.y != end.y) && seatchToEnd))) {
					//Dodajemy ten punkt na koniec kolejki
					tileToCheck.push(temp);
					//Ustawiamy jego warto�� na mapie o jeden wy�szy ni� wcze�niejszego
					weight[map->cordToTabPos(temp)] = weight[map->cordToTabPos(tileToCheck.front())] + 1;
				}
				//je�li dotarli�my do szukanego punktu
				else if ((map->returnTile(temp)->returnObjectType() == objectType && !seatchToEnd) || ((temp.x == end.x && temp.y == end.y) && seatchToEnd)) {
					weight[map->cordToTabPos(temp)] = weight[map->cordToTabPos(tileToCheck.front())] + 1;
					
					this->destination.push_front(temp);
					//Dopuki nie wr�cimy od punktu doj�cia do punktu startu
					while (weight[map->cordToTabPos(this->destination.front())]!=1) {

						temp = this->destination.front();
						int j = -1;
						do 
						{
							j++;
						} 
						while (temp.x > map->mapWidth() - 1 || temp.y > map->mapHeight()-1 || weight[map->cordToTabPos(temp + helper[j])] != weight[map->cordToTabPos(temp)]-1);
						this->destination.push_front(this->destination.front() + helper[j]);
					}
					return true;
				}
			}
		}
		//Po wykonaniu wszystkich operacji na punkcie usuwamy go z kolejki
		tileToCheck.pop();
	}
	return false;
}

void ManAi::clearDestination()
{
	this->destination.clear();
}

ManAi::ManAi()
{

}


ManAi::~ManAi()
{
}
