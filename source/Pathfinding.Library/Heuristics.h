#pragma once

namespace Library
{
	class Node;

	class Heuristics final
	{
	public:
		Heuristics() = default;
		~Heuristics() = default;

		static float ManhattanDistance(const Node& start, const Node& end);

	};
}