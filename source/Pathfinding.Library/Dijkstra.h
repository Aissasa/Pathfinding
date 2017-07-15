#pragma once

#include "AStar.h"

namespace Library
{
	class Dijkstra final : public AStar
	{
	public:

		Dijkstra(const std::function<float(const Node& start, const Node& end)>& pathCostFunc = kPathCostFunc, const std::function<float(const Node& start, const Node& end)>& heuristicFunc = kHeuristicFunc);
		~Dijkstra() = default;

	private:

		static const std::function<float(const Node& start, const Node& end)> kPathCostFunc;
		static const std::function<float(const Node& start, const Node& end)> kHeuristicFunc;
	};
}
