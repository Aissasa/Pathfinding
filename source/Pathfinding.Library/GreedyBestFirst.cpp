#include "pch.h"
#include "GreedyBestFirst.h"
#include "Heuristics.h"

using namespace std;

namespace Library
{
	const function<float(const Node& start, const Node& end)> GreedyBestFirst::heuristicFunc = Heuristics::ManhattanDistance;

	/****************************************************************************/
	deque<shared_ptr<Node>> GreedyBestFirst::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
	{
		set<shared_ptr<Node>> openNodes;

		auto currentNode = start;
		closedSet.insert(currentNode);

		bool endReached = false;

		while (!endReached)
		{
			for (auto neighbor : currentNode->Neighbors())
			{
				auto neighborSharedPtr = neighbor.lock();
				assert(neighborSharedPtr != nullptr);
				// if the neighbor is already visited, dont add it
				if (closedSet.find(neighborSharedPtr) != closedSet.end())
				{
					continue;
				}

				neighborSharedPtr->SetParent(currentNode);
				if (openNodes.find(neighborSharedPtr) == openNodes.end())
				{
					neighborSharedPtr->SetHeuristic(heuristicFunc(*neighborSharedPtr, *end));
					openNodes.insert(neighborSharedPtr);
				}
			}

			if (openNodes.empty())
			{
				break;
			}

			// set the lowest cost node
			float min = FLT_MAX;
			auto it = openNodes.begin();
			auto itMin = it;
			for (; it != openNodes.end(); ++it)
			{
				auto node = *it;
				if (node->TotalCost() < min )
				{
					min = node->TotalCost();
					itMin = it;
					currentNode = node;
				}
			}
			openNodes.erase(itMin);
			closedSet.insert(currentNode);

			if (currentNode == end)
			{
				endReached = true;
			}
		}

		// build the path
		deque<shared_ptr<Node>> path;
		if (endReached)
		{
			path.push_front(end);
			auto currentNodeInPath = end->Parent().lock();

			while (currentNodeInPath != start)
			{
				path.push_front(currentNodeInPath);
				currentNodeInPath = currentNodeInPath->Parent().lock();
			}

			path.push_front(currentNodeInPath);
		}

		return move(path);
	}
}
