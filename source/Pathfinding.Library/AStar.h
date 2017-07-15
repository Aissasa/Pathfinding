#pragma once

#include "IPathFinder.h"

namespace Library
{
	class AStar : public IPathFinder
	{
	public:

		AStar(const std::function<float(const Node& start, const Node& end)>& pathCostFunc = kPathCostFunc, const std::function<float(const Node& start, const Node& end)>& heuristicFunc = kHeuristicFunc);
		virtual ~AStar() = default;
		std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet) override;

	protected:

		std::function<float(const Node& start, const Node& end)> mPathCostFunc;
		std::function<float(const Node& start, const Node& end)> mHeuristicFunc;

	private:

		static const std::function<float(const Node& start, const Node& end)> kPathCostFunc;
		static const std::function<float(const Node& start, const Node& end)> kHeuristicFunc;
	};
}