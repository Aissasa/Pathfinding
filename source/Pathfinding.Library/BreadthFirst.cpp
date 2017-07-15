#include "pch.h"
#include "BreadthFirst.h"

using namespace std;

namespace Library
{
	/****************************************************************************/
	deque<shared_ptr<Node>> BreadthFirst::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
	{
		deque<shared_ptr<Node>> frontier;
		frontier.push_back(start);

		bool endReached = false;

		while (!endReached && !frontier.empty())
		{
			auto currentNode = frontier.front();
			frontier.pop_front();
			closedSet.insert(currentNode);

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
				frontier.push_back(neighborSharedPtr);
				
				// if the end is reached, then stop
				if (frontier.front() == end)
				{
					endReached = true;
					break;
				}
			}
		}

		// reutilize frontier queue as the path
		frontier.clear();
		if (endReached)
		{
			frontier = BuildPath(start, end);
		}

		return move(frontier);
	}
}
