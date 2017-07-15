#include "pch.h"
#include "Heuristics.h"
#include "Node.h"

namespace Library
{
	/**********************************************************************/
	float Heuristics::ManhattanDistance(const Node& start, const Node& end)
	{
		return static_cast<float>(abs(start.Location().X() - end.Location().X()) + abs(start.Location().Y() - end.Location().Y()));
	}

	/**********************************************************************/
	float Heuristics::ZeroHeuristic(const Node & start, const Node & end)
	{
		UNREFERENCED_PARAMETER(start);
		UNREFERENCED_PARAMETER(end);
		return 0.0f;
	}
}
