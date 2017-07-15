#include "pch.h"
#include "IPathFinder.h"

using namespace std;

namespace Library
{
	/****************************************************************************/
	deque<shared_ptr<Node>> IPathFinder::FindPath(shared_ptr<Node> start, shared_ptr<Node> end)
	{
		set<shared_ptr<Node>> closedSet;
		return FindPath(start, end, closedSet);
	}

	/****************************************************************************/
	deque<shared_ptr<Node>> IPathFinder::BuildPath(const shared_ptr<Node>& start, const shared_ptr<Node>& end) const
	{
		deque<shared_ptr<Node>> path;
		path.push_front(end);
		auto currentNodeInPath = end->Parent().lock();

		while (currentNodeInPath != start)
		{
			path.push_front(currentNodeInPath);
			currentNodeInPath = currentNodeInPath->Parent().lock();
		}

		path.push_front(currentNodeInPath);

		return move(path);
	}
}
