#include "pch.h"
#include "Dijkstra.h"
#include "Heuristics.h"

using namespace std;

namespace Library
{
	const function<float(const Node& start, const Node& end)> Dijkstra::kPathCostFunc = Heuristics::ManhattanDistance;
	const function<float(const Node& start, const Node& end)> Dijkstra::kHeuristicFunc = Heuristics::ZeroHeuristic;

	/****************************************************************************/
	Dijkstra::Dijkstra(const function<float(const Node& start, const Node& end)>& pathCostFunc, const function<float(const Node& start, const Node& end)>& heuristicFunc):
		AStar(pathCostFunc, heuristicFunc)
	{
	}
}
