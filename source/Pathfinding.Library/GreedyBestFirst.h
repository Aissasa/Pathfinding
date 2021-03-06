#pragma once

#include "IPathFinder.h"

namespace Library
{
	class GreedyBestFirst final : public IPathFinder
	{
	public:

		GreedyBestFirst() = default;
		~GreedyBestFirst() = default;
		std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet) override;
	
	private:

		static const std::function<float(const Node& start, const Node& end)> kHeuristicFunc;
	};
}
