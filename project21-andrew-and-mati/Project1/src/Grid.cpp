#include "Grid.h"
#include "..\include\Cell.h"

class NodeComparer;

class NodeComparer
{
public:
	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return ( t_n1->g_cost + t_n1->h_cost ) > ( t_n2->g_cost + t_n2->h_cost );
	}
};

struct compareIDS
{
	int cell;
	compareIDS(int t_cell) : cell(t_cell) {}

	bool operator()(int i) {
		return (i == cell);
	}
};

Cell* Grid::at(int t_index)
{
	int x = t_index % xAmountCells;
	int y = t_index / YAmountCells;

	return &cellGrid[x][y];
}

Grid::Grid()
{	
}

void Grid::setupGrid()
{
	if (!idFont.loadFromFile("./recources/FONTS/arial.ttf"))
	{
		std::cout << "Error with fonts" << std::endl;
	}

	for (int index = 0; index < TotalCells; index++)
	{
		int x = index % xAmountCells;
		int y = index / YAmountCells;

		at(index)->x = x;
		at(index)->y = y;
		at(index)->m_id = x + (y * xAmountCells);
		at(index)->cellBody.setFillColor(sf::Color::Transparent);
		at(index)->cellBody.setOutlineColor(sf::Color::Green);
		at(index)->cellBody.setOutlineThickness(0.5f);
		at(index)->cellBody.setSize(sf::Vector2f(640 / xAmountCells, 640 / YAmountCells));
		at(index)->cellBody.setPosition((640 / xAmountCells) * x, (640 / YAmountCells) * y);
		at(index)->idText.setPosition(cellGrid[x][y].cellBody.getPosition());
		at(index)->center = sf::Vector2f(at(index)->cellBody.getPosition().x + (at(index)->cellBody.getGlobalBounds().width / 2), at(index)->cellBody.getPosition().y + (at(index)->cellBody.getGlobalBounds().height / 2));
	}

	for (int index = 0; index < TotalCells; index++)
	{
		at(index)->idText.setFont(idFont);
		at(index)->idText.setString(std::to_string(at(index)->m_id));
		at(index)->idText.setCharacterSize(10);
	}
}

void Grid::showNeighbours()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash))
	{
		int id;

		std::cout << "Enter Cell ID to display their Neighbours ID" << std::endl;

		std::cin >> id;

		if (id < TotalCells && id > -1 )
		{
			std::cout << "Cell " << id << " has Neighbours: " << std::endl;

			for (int i = 0; i < at(id)->neighboursids.size(); i++)
			{
				std::cout << "Cell " << at(id)->neighboursids.at(i) << std::endl;
			}
		}

	}
}

void Grid::showAStar()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
	{
		int startID;
		int destID;

		std::cout << "Enter Cell ID start Pos: " << std::endl;
		std::cin >> startID;

		std::cout << "Enter Cell ID for a* destination: " << std::endl;
		std::cin >> destID;

		if (startID < TotalCells && destID < TotalCells && startID > -1 && destID > -1)
		{
			std::cout << "Starting a* on cell: " << startID << " , For cell: " << destID << std::endl;

			std::vector <int> path;

			aStar( at(startID), at(destID), &path);

			for (int cellID : path) 
			{
				std::cout << "A* Path: " << cellID << std::endl;
			}
		}
	}
}

Cell* Grid::GetIntersects(sf::Vector2f pos)
{
	for (int c = 0; c < TotalCells; c++)
	{
		Cell* cl = at(c);

		if (cl->cellBody.getGlobalBounds().contains(pos)) 
		{
			return cl;
		}
	}

	return nullptr;
}

void Grid::draw(sf::RenderWindow& m_window)
{
	for (int c = 0; c < TotalCells; c++)
	{
		m_window.draw(at(c)->cellBody);
		m_window.draw(at(c)->idText);
	}
}

void Grid::reset()
{
	for (int c = 0; c < TotalCells; c++)
	{
		at(c)->m_previousCellId = -1;
		at(c)->setMarked(false);
		at(c)->g_cost = 0;
		at(c)->h_cost = 0;
		at(c)->cellBody.setTexture(NULL);
		at(c)->cellBody.setFillColor(sf::Color::Transparent);
	}
}

int Grid::getCellPlayerIsIn(sf::Vector2f t_playerPos)
{
	for (int c = 0; c < TotalCells; c++)
	{
		if (at(c)->cellBody.getGlobalBounds().contains(t_playerPos))
		{
			return at(c)->m_id;
		}
	}
}


void Grid::findNeigbours(int t_pointX, int t_pointY)
{
	if (cellGrid[t_pointX][t_pointY].m_isPassable)
	{
		for (int direction = 0; direction < 9; direction++)
		{
			//skip middle cell and diagonal cells
			if (direction == 4) continue;

			int n_row = t_pointX + ((direction % 3) - 1); // Neighbor row
			int n_col = t_pointY + ((direction / 3) - 1); // Neighbor column

			// Check the bounds:
			if (n_row >= 0 && n_row < xAmountCells && n_col >= 0 && n_col < YAmountCells)
			{
				if (cellGrid[n_row][n_col].m_isPassable)
				{
					cellGrid[t_pointX][t_pointY].addNeighboursID(n_row + (n_col * xAmountCells));
				}
			}
		}
	}
}

void Grid::update()
{
	showNeighbours();
	showAStar();
}

void Grid::aStar(Cell* t_start, Cell* t_dest, std::vector<int>* m_path)
{
	Cell* myStart = t_start;
	Cell* goal = t_dest;

	std::priority_queue<Cell*, std::vector<Cell*>, NodeComparer> pq;

	for (int index = 0; index < TotalCells; index++)
	{
		Cell* node = at(index);
		node->h_cost = sqrt(abs((t_dest->x - node->x) * (t_dest->x - node->x) + (t_dest->y - node->y) * (t_dest->y - node->y)));;
		node->g_cost = std::numeric_limits<int>::max() / 4;
	}

	myStart->g_cost = 0;

	pq.push(myStart);
	pq.top()->setMarked(true);

	//std::cout << "visited : " << t_start->m_id << std::endl;

	while (!pq.empty() && pq.top() != goal)
	{
		Cell* top = pq.top();

		for (int cellID : top->neighboursids)
		{
			Cell* child = at(cellID);

			//std::cout << "visited : " << cellID << std::endl;

			int weight = 1;
			int childCost = pq.top()->g_cost + child->weight;

			if (child != at(pq.top()->m_previousCellId))
			{
				if (childCost < child->g_cost)
				{
					child->g_cost = childCost;
					child->m_previousCellId = pq.top()->m_id;
				}
				if (!child->isMarked())
				{
					pq.push(child);
					child->setMarked(true);
				}
			}
		}
		pq.pop();
	}

	Cell* currentInPath = t_dest;
	
	if (m_path->empty())
	{
		m_path->push_back(currentInPath->m_id);

		while (currentInPath->m_previousCellId != -1)
		{
			m_path->push_back(currentInPath->m_id);
			currentInPath = at(currentInPath->m_previousCellId);
		}
	}
}

//void Grid::setupGrid(std::vector<Wall*>& t_globalWalls)
//{
//	sf::Vector2f pos(0, 0);
//	idFont.loadFromFile("ART/FONTS/ariblk.ttf");
//	int counter = 0;
//
//	int column = 0;
//	for (int row = 0; row < 11; row++)
//	{
//
//		if (row % 10 == 0 && row != 0)
//		{
//			column++;
//			std::cout << std::endl;
//			row = 0;
//			pos.y += cellGrid[row][column].cellBody.getSize().y;
//			pos.x = 0;
//		}
// 
//		cellGrid[row][column].cellBody.setPosition(sf::Vector2f(pos));
//		cellGrid[row][column].idText.setPosition(cellGrid[row][column].cellBody.getPosition());
//
//		pos.x += cellGrid[row][column].cellBody.getSize().x;
// 
//		cellGrid[row][column].m_id = row + column * 10;
//		std::cout << cellGrid[row][column].m_id << ", ";
//		cellGrid[row][column].idText.setFont(idFont);
//		cellGrid[row][column].neighboursDisplayText.setFont(idFont);
//		cellGrid[row][column].idText.setString(std::to_string(cellGrid[row][column].m_id));
//
//		// List all neighbors:
//		for (int direction = 0; direction < 9; direction++) {
//			if (direction == 4) { direction++; }; // Skip 4, this is ourself.
//
//			int n_row = row + ((direction % 3) - 1); // Neighbor row
//			int n_col = column + ((direction / 3) - 1); // Neighbor column
//
//			// Check the bounds:
//			if (n_row >= 0 && n_row < 10 && n_col >= 0 && n_col < 10) {
//
//				// A valid neighbor:
//				cellGrid[row][column].neighbours.push_back(&cellGrid[n_row][n_col]);
//				cellGrid[row][column].neighboursText += (std::to_string(n_col) + std::to_string(n_row) + "\n");
//
//				cellGrid[row][column].neighboursDisplayText.setPosition(cellGrid[row][column].cellBody.getPosition() + sf::Vector2f(250,0));
//				cellGrid[row][column].neighboursDisplayText.setString(cellGrid[row][column].neighboursText); 
//			}
//		}
// 
//		cellGrid[row][column].markImpassable(t_globalWalls);
//
//
//		if (row == 9 && column == 9)
//		{
//			std::cout << std::endl;
//			break;
//		}
//
//	}
//
//	for (int i = 0; i < 12; i++)
//	{
//		at(cellsThatShouldBePassable[i]).m_isPassable = true;
//		at(cellsThatShouldBePassable[i]).cellBody.setFillColor(sf::Color(0, 255, 0, 130));
//	}
//}
