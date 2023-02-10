#include "BeeSwarm.h"
#define startDistrictsAmount 20

void BeeSwarm::foragerCycle(int districtNum, int foragerAmount)
{
	int neighbourSuccessIndex = -1;
	auto trySwitchColors = [this, districtNum, &neighbourSuccessIndex](int vertexNum)
	{
		int chosenVertexColor = districts[districtNum].getVertices()[vertexNum].colour;
		int neighbourColor;
		bool successChosen = false;
		bool successNeighbour = false;
		for (auto neighbour : districts[districtNum].getVertices()[vertexNum].neighbours)
		{
			neighbourColor = districts[districtNum].getVertices()[neighbour].colour;
			districts[districtNum].changeColour(neighbour, -1);
			successChosen = districts[districtNum].changeColour(vertexNum, neighbourColor);
			successNeighbour = districts[districtNum].changeColour(neighbour, chosenVertexColor);
			if (successChosen && successNeighbour)
			{
				neighbourSuccessIndex = neighbour;
				break;
			}
			else
			{
				districts[districtNum].changeColour(neighbour, -1);
				districts[districtNum].changeColour(neighbour, neighbourColor);
				districts[districtNum].changeColour(vertexNum, -1);
				districts[districtNum].changeColour(vertexNum, chosenVertexColor);
			}
		}
	};
	auto tryReduceColorAmount = [this, districtNum](int vertexNum, int neigbour)
	{
		for (auto color : districts[districtNum].getUsedColors())
		{
			if (districts[districtNum].changeColour(vertexNum, color)) 
			{
				districts[districtNum].redefineUsedColors();
				break;
			}
		}
		for (auto color : districts[districtNum].getUsedColors())
		{
			if (districts[districtNum].changeColour(neigbour, color))
			{
				districts[districtNum].redefineUsedColors();
				break;
			}
		}
	};
	queue<int> chosenVertices;
	for (int vertexDegree = districts[districtNum].getMaxDegree(); vertexDegree > 0 && foragerAmount > 0; vertexDegree--)
	{
		for (int i = 0; i < districts[districtNum].getDegree—onformity()[vertexDegree].size() && foragerAmount > 0; i++)
		{
			chosenVertices.push(districts[districtNum].getDegree—onformity()[vertexDegree][i]);
			foragerAmount--;
		}
	}
	while (!chosenVertices.empty())
	{
		trySwitchColors(chosenVertices.front());
		if (neighbourSuccessIndex != -1)
		{
			tryReduceColorAmount(chosenVertices.front(), neighbourSuccessIndex);
			neighbourSuccessIndex = -1;
		}
		chosenVertices.pop();
	}
}

queue<Graph> BeeSwarm::scoutCycle()
{
	queue<Graph> scoutedDistricts;
	auto comparator = [](Graph left, Graph right)
	{
		return left.getChromaticNum() < right.getChromaticNum();
	};
	int randomScouts = (scouts / 3 > 0) ? (scouts / 3) : 1;
	int eliteScouts = scouts - randomScouts;
	sort(districts.begin(), districts.end(), comparator);
	for (int i = 0; i < eliteScouts && i < districts.size(); i++)
	{
		scoutedDistricts.push(districts[i]);
	}
	if (eliteScouts >= districts.size())
		return scoutedDistricts;
	else
	{
		for (int i = 0; i < randomScouts && i < districts.size() - eliteScouts; i++)
		{
			int randDistrictNum = rand() % (districts.size() - eliteScouts - 1) + eliteScouts - 1;
			scoutedDistricts.push(districts[randDistrictNum]);
		}
	}
	return scoutedDistricts;
}

BeeSwarm::BeeSwarm(int iterationsLimit, int scouts, int foragers) :
	iterationsLimit(iterationsLimit),
	scouts(scouts),
	foragers(foragers) {}

Graph BeeSwarm::colourGraph(Graph inputGraph)
{
	auto comparator = [](Graph left, Graph right)
	{
		return left.getChromaticNum() < right.getChromaticNum();
	};
	GreedyColorer greedy;
	for (int i = 0; i < startDistrictsAmount; i++)
	{
		districts.push_back(greedy.greedyColoring(inputGraph));
	}
	foragersForDistrict = inputGraph.getMaxDegree();
	Graph bestResult = *min_element(districts.begin(), districts.end(), comparator);
	queue<Graph> scoutedDistricts;
	while (iterationsLimit-- != 0)
	{
		scoutedDistricts = scoutCycle();
		int freeForagers = foragers;
		for (int i = 0; i < scouts && i < districts.size(); i++)
		{
			freeForagers -= foragersForDistrict;
			if (foragers >= 0)
				foragerCycle(i, foragersForDistrict);
			else
				foragerCycle(i, foragersForDistrict + freeForagers);
		}
		for (auto district : districts)
		{
			if (district.getChromaticNum() < bestResult.getChromaticNum())
				bestResult = district;
		}
	}
	return bestResult;
}
