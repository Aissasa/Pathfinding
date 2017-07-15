#include "pch.h"
#include "AStar.h"
#include "Heuristics.h"

using namespace std;

namespace Library
{
	const function<float(const Node& start, const Node& end)> AStar::kPathCostFunc = Heuristics::ManhattanDistance;
	const function<float(const Node& start, const Node& end)> AStar::kHeuristicFunc = Heuristics::ManhattanDistance;

	/****************************************************************************/
	AStar::AStar(const function<float(const Node& start, const Node& end)>& pathCostFunc, const function<float(const Node& start, const Node& end)>& heuristicFunc) :
		mPathCostFunc(pathCostFunc), mHeuristicFunc(heuristicFunc)
	{
	}

	/****************************************************************************/
	deque<shared_ptr<Node>> AStar::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
	{
		set<shared_ptr<Node>> openSet;

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

				// compute path cost
				float newPathCost = currentNode->PathCost() + mPathCostFunc(*currentNode, *neighborSharedPtr);

				bool isNodeInOpenSet = openSet.find(neighborSharedPtr) != openSet.end();

				if (newPathCost < neighborSharedPtr->PathCost() || !isNodeInOpenSet)
				{
					neighborSharedPtr->SetParent(currentNode);
					neighborSharedPtr->SetPathCost(newPathCost);
					neighborSharedPtr->SetHeuristic(mHeuristicFunc(*neighborSharedPtr, *end));

					// add it if it's not in the open set
					if (!isNodeInOpenSet)
					{
						openSet.insert(neighborSharedPtr);
					}
				}
			}

			if (openSet.empty())
			{
				break;
			}

			// set the lowest cost node
			float min = FLT_MAX;
			auto it = openSet.begin();
			auto itMin = it;
			for (; it != openSet.end(); ++it)
			{
				auto node = *it;
				if (node->TotalCost() < min)
				{
					min = node->TotalCost();
					itMin = it;
					currentNode = node;
				}
			}
			openSet.erase(itMin);
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
			path = BuildPath(start, end);
		}

		return move(path);
	}
}
