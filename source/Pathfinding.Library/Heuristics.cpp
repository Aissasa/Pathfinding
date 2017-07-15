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
}
