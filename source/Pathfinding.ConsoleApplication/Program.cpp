#include "pch.h"
#include "BreadthFirst.h"
#include "GreedyBestFirst.h"
#include "AStar.h"
#include "Dijkstra.h"

using namespace std;
using namespace Library;

/****************************************************************************/
void DisplayGraph(const Graph& graph, const int32_t width, const int32_t height, const shared_ptr<Node>& start, const shared_ptr<Node>& end,
				  const set<shared_ptr<Node>>& path, const set<shared_ptr<Node>>& visitedNodes)
{
	assert(width > 0 && height > 0);

	auto& nodes = graph.Nodes();
	string str;
	for (int32_t y = 0; y < height; ++y)
	{
		for (int32_t x = 0; x < width; ++x)
		{
			Point currentPoint(x, y);
			auto& currentNode = nodes.at(currentPoint);

			switch (currentNode->Type())
			{
				case NodeType::Normal:
				{
					str = "- ";
					break;
				}

				case NodeType::Wall:
				{
					str = "| ";
					break;
				}

				default:;
			}

			if (visitedNodes.find(currentNode) != visitedNodes.end())
			{
				//str = "V ";
			}

			if (path.find(currentNode) != path.end())
			{
				str = "X ";
			}

			if (currentNode == end)
			{
				str = "E ";
			}

			if (currentNode == start)
			{
				str = "S ";
			}

			cout << str;

			if (x == width - 1)
			{
				cout << endl << endl;
			}
		}
	}
}

/****************************************************************************/
set<shared_ptr<Node>> BuildPath(deque<shared_ptr<Node>>& path)
{
	set<shared_ptr<Node>> pathSet;
	while (!path.empty())
	{
		pathSet.insert(path.front());
		path.pop_front();
	}

	return move(pathSet);
}

/****************************************************************************/
int main(int argc, char* argv[])
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	int32_t width, height;
	auto grid = GridHelper::LoadGridFromFile("Grid.grid", width, height);

	Point start;
	Point end;

	while (true)
	{
		int32_t x1, y1, x2, y2;
		cout << "Enter a valid start point coordinates:" << endl;
		cout << "X: ";
		cin >> x1;
		cout << "Y: ";
		cin >> y1;

		Point s(x1, y1);

		if (!grid.Contains(s) || grid.At(s)->Type() == NodeType::Wall)
		{
			cout << endl << "This point is not valid!" << endl << endl;
			continue;
		}
		start = s;

		cout << endl <<"Enter a valid end point coordinates:" << endl;
		cout << "X: ";
		cin >> x2;
		cout << "Y: ";
		cin >> y2;

		Point e(x2, y2);

		if (!grid.Contains(e) || grid.At(e)->Type() == NodeType::Wall || s.X() == e.X() && e.Y() == s.Y())
		{
			cout << endl << "This point is not valid!" << endl << endl;
			continue;
		}
		end = e;

		break;
	}

	auto startNode = grid.At(start);
	auto endNode = grid.At(end);
	set<shared_ptr<Node>> visitedNodes;
	StopWatch sw;

	/******************************* Breadth First *************************************/
	cout << endl << "****************************************************************************" << endl;
	cout << "Breadth First algorithm:" << endl << endl;

	BreadthFirst breadthFirst;

	sw.Restart();
	deque<shared_ptr<Node>> path = breadthFirst.FindPath(startNode, endNode, visitedNodes);
	sw.Stop();
	auto elapsed = sw.Elapsed();
	set<shared_ptr<Node>> pathSet = BuildPath(path);

	DisplayGraph(grid, width, height, startNode, endNode, pathSet, visitedNodes);

	cout << "Breadth first took " << elapsed.count() << " microseconds.";
	if (pathSet.empty())
	{
		cout << " No path was found!";
	}
	
	cout << endl << "Number of visited nodes: " << visitedNodes.size() << endl;
	cout << "Path length: " << pathSet.size() << endl;
	cout << endl;


	/******************************* Greedy Best First *************************************/
	cout << "********************************************************************************" << endl;
	cout << "Greedy Best First algorithm:" << endl << endl;

	grid.Reset();
	GreedyBestFirst greedyBestFirst;
	visitedNodes.clear();

	sw.Restart();
	path = greedyBestFirst.FindPath(startNode, endNode, visitedNodes);
	sw.Stop();
	elapsed = sw.Elapsed();
	pathSet = BuildPath(path);

	DisplayGraph(grid, width, height, startNode, endNode, pathSet, visitedNodes);

	cout << "Greedy Best first took " << elapsed.count() << " microseconds.";
	if (pathSet.empty())
	{
		cout << " No path was found!";
	}

	cout << endl << "Number of visited nodes: " << visitedNodes.size() << endl;
	cout << "Path length: " << pathSet.size() << endl;
	cout << endl;


	/******************************* Dijkstra *************************************/
	cout << "********************************************************************************" << endl;
	cout << "Dijkstra algorithm:" << endl << endl;

	grid.Reset();
	Dijkstra dijkstra;
	visitedNodes.clear();

	sw.Restart();
	path = dijkstra.FindPath(startNode, endNode, visitedNodes);
	sw.Stop();
	elapsed = sw.Elapsed();
	pathSet = BuildPath(path);

	DisplayGraph(grid, width, height, startNode, endNode, pathSet, visitedNodes);

	cout << "Dijkstra took " << elapsed.count() << " microseconds.";
	if (pathSet.empty())
	{
		cout << " No path was found!";
	}

	cout << endl << "Number of visited nodes: " << visitedNodes.size() << endl;
	cout << "Path length: " << pathSet.size() << endl;
	cout << endl;


	/******************************* A Star *************************************/
	cout << "********************************************************************************" << endl;
	cout << "A* algorithm:" << endl << endl;

	grid.Reset();
	AStar aStar;
	visitedNodes.clear();

	sw.Restart();
	path = aStar.FindPath(startNode, endNode, visitedNodes);
	sw.Stop();
	elapsed = sw.Elapsed();
	pathSet = BuildPath(path);

	DisplayGraph(grid, width, height, startNode, endNode, pathSet, visitedNodes);

	cout << "A* took " << elapsed.count() << " microseconds.";
	if (pathSet.empty())
	{
		cout << " No path was found!";
	}

	cout << endl << "Number of visited nodes: " << visitedNodes.size() << endl;
	cout << "Path length: " << pathSet.size() << endl;
	cout << endl;



	cout << "Press Enter to Exit: ";
	cin.get();
	cin.get();

	return 0;
}
