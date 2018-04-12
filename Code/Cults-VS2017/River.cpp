#include "River.h"


River::River(MapUtilities* controller)
{
	m_mapController = controller;
	generateRiver();
	correctRiver();
}


River::~River()
{
}

std::list<MapTile*> River::getRiverTiles()
{
	return m_river;
}

void River::generateRiver() {
	//split dist in two partitions, 60/40 or 70/30 split, create one quadratic bezier curve on the smaller partition and one cubic one on the larger one
	//get two points on different boundaries
	//partition distance in 2
	//get midpoint (slightly closer to one point than the other)
	//generate 2 bezier curves from each point to the midpoint
	//cubic bezier in the larger partition and a quadratic bezier curve in the smaller
	int minDistance = (m_mapController->getMapSize() / 1.25);
	std::vector<MapTile*> result;
	enum Edge { N, E, S, W };
	std::vector<Edge> boundaries = { N, E, S, W };
	Edge e1, e2;
	int index = m_mapController->getRandomNumber(0, (boundaries.size() - 1));
	std::vector<Edge>::iterator it = (boundaries.begin() + index);
	e1 = (*it);
	boundaries.erase(it);
	index = m_mapController->getRandomNumber(0, (boundaries.size() - 1));
	it = (boundaries.begin() + index);
	e2 = (*it);
	boundaries.erase(it);
	MapTile *start, *mid, *end;
	start = m_mapController->getRandomBoundaryTile(e1, 0);
	end = m_mapController->getRandomBoundaryTile(e2, m_mapController->getStartingPointShiftValue(e1, e2, start, minDistance));
	//decide if first half or second half is going to be bigger/cubic or smaller/quadratic bezier curve
	bool startIsQuadratic = (m_mapController->getRandomNumber(2, 3) == 2);
	//pick meeting point of both halfs
	int xHalfway = (start->getX() + end->getX()) / 2;
	int yHalfway = (start->getY() + end->getY()) / 2;
	int xPoint, yPoint;
	if (start->getX() < end->getX()) {
		xPoint = start->getX() + xHalfway;
	}
	else {
		xPoint = end->getX() + xHalfway;
	}
	if (xPoint >= m_mapController->getMapSize()) {
		xPoint = m_mapController->getMapSize() - 1;
	}
	else if (xPoint < 0) {
		xPoint = 0;
	}
	if (start->getY() < end->getY()) {
		yPoint = start->getY() + yHalfway;
	}
	else {
		yPoint = end->getY() + yHalfway;
	}
	if (yPoint >= m_mapController->getMapSize()) {
		yPoint = m_mapController->getMapSize() - 1;
	}
	else if (yPoint < 0) {
		yPoint = 0;
	}
	MapTile* midpoint = m_mapController->getRandomTileInRange(m_mapController->getTileAt(xPoint, yPoint), 10);
	//add points to vector and return it
	result = { start, midpoint, end };
	std::list<MapTile*> river1 = m_mapController->generateBezierCurve(start, midpoint, startIsQuadratic);
	std::list<MapTile*> river2 = m_mapController->generateBezierCurve(midpoint, end, (!startIsQuadratic));

	for (std::list<MapTile*>::iterator it = river1.begin(); it != river1.end(); ++it) {
		(*it)->setRiver(true);
	}
	for (std::list<MapTile*>::iterator it = river2.begin(); it != river2.end(); ++it) {
		(*it)->setRiver(true);
	}

	m_river.splice(m_river.end(), river1);
	m_river.splice(m_river.end(), river2);
}

//need a correct river function that iterates over m_river and 
//if any two points arent adjacent, connect via shortest path and insert in place in list
void River::correctRiver() {
	std::list<MapTile*>::iterator riverItr = m_river.begin();
	std::list<MapTile*>::iterator riverItrNext;
	for (riverItrNext = (m_river.begin()++); riverItrNext != m_river.end(); riverItrNext++) {
		if ((!(m_mapController->tilesAreAdjacent((*riverItr), (*riverItrNext)))) && (!((*riverItr) == (*riverItrNext)))) {
			std::list<MapTile*> path = m_mapController->aStar((*riverItr), (*riverItrNext));
			//want to erase itr and itr next since path includes both points
			//get itr to element after itrnext, erase points, insert path
			riverItrNext = m_river.erase(riverItrNext, riverItr);
			m_river.insert(riverItrNext, path.begin(), path.end());
			riverItr = riverItrNext;
			riverItr--;
		} else {
			riverItr++;
		}
	}
}