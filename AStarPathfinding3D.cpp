#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

/* Settings */

const int MaxX = 3;
const int MaxY = 5;
const int MaxZ = 4;

// Map. 1 is open 0 is Blocked
bool map[MaxY][MaxX][MaxZ] = {
	{ { 1, 0, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 1, 1 } },
	{ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 1 } },
	{ { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 } },
	{ { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 0, 0, 0, 0 } },
	{ { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 } }
};

/* End of Settings */

class Point {
protected:
	// Calculates the distance between two points via the given coordinates
	double EuclideanDistance(Point p) {
		return sqrt(pow(this->X - p.X, 2) + pow(this->Y - p.Y, 2) + pow(this->Z - p.Z, 2));
	}

public:
	int X;
	int Y;
	int Z;

	Point(int X, int Y, int Z) {
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}
};

class Cell : public Point {
public:
	double DecidingFactor;
	Cell* parent;

	Cell(int X, int Y, int Z, Point Start, Point End, Cell* parent) : Point(X, Y, Z) {
		this->DecidingFactor = EuclideanDistance(Start) + EuclideanDistance(End);
		this->parent = parent;
		/*
				std::cout << this->X << ", " << this->Y << ", " << this->Z;
				if (parent)
					std::cout << " Child of " << this->parent->X << ", " << this->parent->Y << ", " << this->parent->Z << "  DF=" << this->DecidingFactor;
				std::cout << std::endl;*/
	}
};

bool operator<(Cell a, Cell b) {
	return a.DecidingFactor < b.DecidingFactor;
}

bool operator==(Point a, Point b) {
	return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
}

int main() {
	int heli = 0;
	std::cout << "Enter number of paths to find : ";
	std::cin >> heli;

	std::vector<std::tuple<Point, Point>> Paths;
	int x1, y1, z1;
	int x2, y2, z2;

	for (int h = 1; h <= heli; h++) {
		std::cout << "Enter Starting X, Y, Z for the Path #" << h << " : ";
		std::cin >> x1 >> y1 >> z1;
		std::cout << "Enter Destination X, Y, Z for the Path #" << h << " : ";
		std::cin >> x2 >> y2 >> z2;

		Paths.push_back(std::tuple<Point, Point>(Point(x1, y1, z1), Point(x2, y2, z2)));
	}

	for (int h = 0; h < heli; h++) {
		// Keep a record of Met cells. 0 is unmet 1 is met
		bool met[MaxY][MaxX][MaxZ] = {};

		// Determine Start and End Points
		Point Start = std::get<0>(Paths[h]);
		Point End = std::get<1>(Paths[h]);

		// Priority Queue to choose the cell with the smallest deciding factor
		std::priority_queue<Cell*> Q;

		// Put the starting cell up in queue
		// Starting cell has no parents. It is the root
		Q.push(new Cell(Start.X, Start.Y, Start.Z, Start, End, nullptr));

		// Found keeps the neighbor of the destination cell
		Cell* Found = nullptr;

		do {
			// Take the cell with the smallest deciding factor
			Cell* a = Q.top();
			Q.pop();

			// Meet it
			met[a->Y][a->X][a->Z] = 1;

			// Iterate through the meeting cell's neighbors
			for (int y = -1; y <= 1; y++) {
				if (Found) break; // no need to continue if we found the destination
				for (int x = -1; x <= 1; x++) {
					if (Found) break; // no need to continue if we found the destination
					for (int z = -1; z <= 1; z++) {
						// skip if the cell cell is invalid
						if (!a) continue;
						// skip self
						if (x == 0 && y == 0 && z == 0) continue;

						// Determine neighbor coords
						Point Neighbor = Point((a->X) + x, (a->Y) + y, (a->Z) + z);

						// skip if neighbor's coords are invalid (out of bound)
						if (Neighbor.X < 0 || Neighbor.X >= MaxX) continue;
						if (Neighbor.Y < 0 || Neighbor.Y >= MaxY) continue;
						if (Neighbor.Z < 0 || Neighbor.Z >= MaxZ) continue;

						// Skip if neighbor is blocked
						if (map[Neighbor.Y][Neighbor.X][Neighbor.Z] == 0) continue;
						// Skip if neighbor is already met
						if (met[Neighbor.Y][Neighbor.X][Neighbor.Z] == 1) continue;

						// Check if the neighbor is actually the destination
						if (Neighbor == End) {
							// If we have found the neighbor of the destination
							Found = a;
							// There is no need to continue
							break;
						}

						// "Meet" the neighbor
						met[Neighbor.Y][Neighbor.X][Neighbor.Z] = 1;
						// Creating a new cell calculates the deciding factor on refreshes the queue
						Q.push(new Cell(Neighbor.X, Neighbor.Y, Neighbor.Z, Start, End, a));
					}
				}
			}
		} while (!Q.empty() && !Found);

		// Check whether a path was found from Start to Destination
		if (Found) {
			std::cout << std::endl << "Path #" << h + 1 << " :" << std::endl << "(" << End.X << ", " << End.Y << ", " << End.Z << ")\t";
			while (Found)
			{
				std::cout << " <-- (" << Found->X << ", " << Found->Y << ", " << Found->Z << ")\t";
				Found = Found->parent;
			}
			std::cout << std::endl;
		}
	}

	return 0;
}