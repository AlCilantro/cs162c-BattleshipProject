/*
* Created by alexa on 5/25/2025.
*/
#ifndef  BATTLESHIP_H
#define  BATTLESHIP_H

#include <random>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
/*
* The code needed to display the board
*/
class  Board {
private:
    const int gridSize = 10;
    vector<vector<char>> grid;
    int totalShipCells = 0;
    int hitShipCells = 0;

public:
    Board();

    void displayBoard(bool revealShips = false) const;
    bool placeShip(int x, int y, int size, bool vertical);
    bool shoot(int x, int y);
    bool allShipsSunk() const;
};

Board::Board() {
    grid.resize(gridSize , vector<char>(gridSize, '~'));
}
void Board::displayBoard(bool revealShips) const {
    cout << "  ";
    for (int i = 0; i < gridSize; ++i) cout << i << " ";
    cout << endl;
    for (int y = 0; y < gridSize; ++y) {
        cout << y << " ";
        for (int x = 0; x < gridSize; ++x) {
            char cell = grid[y][x];
            if (cell == 'S' && !revealShips)
                cout << "~ ";
            else
                cout << cell << " ";
        }
        cout << endl;
    }
}

bool Board::placeShip(int x, int y, int size, bool vertical) {
        if (vertical) {
            if (y + size > gridSize) return false;
            for (int i = 0; i < size; ++i)
                if (grid[y + i][x] != '~') return false;
            for (int i = 0; i < size; ++i) {
                grid[y + i][x] = 'S';
                totalShipCells++;
            }
        } else {
            if (x + size > gridSize) return false;
            for (int i = 0; i < size; ++i)
                if (grid[y][x+i] != '~') return false;
            for (int i = 0; i < size; ++i) {
                grid[y][x+i] = 'S';
                totalShipCells++;
            }
        }
        return true;
    }

inline bool Board::shoot(int x, int y) {
    if (x < 0 || x >= gridSize || y < 0 || y >= gridSize)
        return false;
    if (grid[y][x] == 'S') {
        grid[y][x] = 'X';
        hitShipCells++;
        return true;
    } else if (grid[y][x] == '~') {
        grid[y][x] = 'O';
    }
    return false;
}

bool Board::allShipsSunk() const {
    return hitShipCells >= totalShipCells;
}
/*
 * To determine who goes first and who's turn it is.
 */
class  Coin {
public:
    enum class side {Heads, Tails};
    Coin();
    side flip();
    std::string getSide() const;

private:
    side currentSide;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;
};

inline Coin::Coin() : rng(random_device{}()), dist(0,1) {
    currentSide = (dist(rng) == 0 ) ? side::Heads : side::Tails;
}

inline Coin::side Coin::flip() {
    currentSide = (dist(rng) == 0) ? side::Heads : side::Tails;
    return currentSide;
}

inline string Coin::getSide() const {
    return(currentSide == side::Heads ? "Heads" : "Tails");
}
/*
 *  Ship placement placeholder.
 */
enum class sType {
    Carrier,
    Battleship,
    Cruiser,
    Destroyer
};

inline string getsType(sType t) {
    switch (t) {
        case sType::Carrier: return "Carrier";
        case sType::Battleship: return "Battleship";
        case sType::Cruiser: return "Cruiser";
        case sType::Destroyer: return "Destroyer";
    }
}

class Ship {
protected:
    string name;
    int size;
    bool isSunk;

public:
    Ship(const string& name , int size ) : name(name) , size(size), isSunk(false) {}
    virtual ~Ship() {}
    string getName() const {return name;}
    int getSize() const {return size;}
    bool getSunk() const {return isSunk;}
    void sink() {isSunk = true;}
};

class Carrier : public Ship {public: Carrier() : Ship("Carrier", 5) {}};
class Battleship: public Ship {public: Battleship() : Ship("Battleship", 4) {}};
class Cruiser : public Ship {public: Cruiser() : Ship("Cruiser", 3) {}};
class Destroyer : public Ship {public: Destroyer() : Ship("Destroyer", 2) {}};

class Player {
public:
    Board board;
    vector<Ship*> ships;

    Player(bool isUser = false) {
        ships.push_back(new Carrier());
        ships.push_back(new Battleship());
        ships.push_back(new Cruiser());
        ships.push_back(new Cruiser());
        ships.push_back(new Destroyer());

        if (isUser) {
            manualShipPlacement();
        }
        else
            randomShipPlacement();
    }

    ~Player() {
        for (Ship* s : ships)
            delete s;
    }

    void randomShipPlacement() {
        mt19937 rng(random_device{}());
        uniform_int_distribution<int> distXY(0, 9);
        uniform_int_distribution<int> distDir(0, 1);

        for (Ship* s : ships) {
            bool placed = false;
            while (!placed) {
                int x = distXY(rng);
                int y = distXY(rng);
                bool vertical = distDir(rng);
                placed = board.placeShip(x,y,s->getSize(), vertical);
            }
        }
    }

    bool takeTurn(Player& enemy) {
        int x, y;
        cout << "Enter target coordinates: (x,y): ";
        cin >> x >> y;
        bool hit = enemy.board.shoot(x,y);
        cout << (hit ? "Hit!\n" : "Not Hit!\n" );
        return enemy.board.allShipsSunk();
    }
    void manualShipPlacement() {
        cout << "Ship Placement\n";
        cout << "To place a ship, enter (x y) coordinates followed by a direction (v or h)" << endl;

        for (Ship* s : ships) {
            bool placed = false;
            while (!placed) {
                int x, y;
                char dir;

                cout << "\nPlacing your " << s->getName() << " (size: " << s->getSize() << ")\n";
                cout << "Enter your position: ";

                if (!(cin >> x >> y >> dir )) {
                    cout << "Invalid input, please try again.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }

                dir = tolower(dir);
                if (dir != 'v' && dir != 'h'){
                    cout << "invalid input, please try again.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }

                bool vertical = (dir == 'v');
                placed = board.placeShip(x,y,s->getSize(), vertical);

                if (!placed) {
                    cout << "Invalid input, please try again.\n";
                } else {
                    cout << s->getName() << " placed succefully.\n";
                }
                board.displayBoard(true);
            }
        }
        cout <<"All Ships Placed\n";
    }
};
class Game {
private:
    Player player;
    Player cpu;
    bool playerTurn;

public:
    Game(bool playerStarts) : player(true), cpu(false), playerTurn(playerStarts) {}

    void play() {
        cout << "\n Let the battle begin! \n";

        while (true) {
            if (playerTurn) {
                cout << "\n Your Turn:\n";
                cpu.board.displayBoard(false);
                if (player.takeTurn(cpu)) {
                    cout << " You win!\n";
                    break;
                }
            } else {
                cout << "\n CPU Turn:\n";
                int x = rand() % 10;
                int y = rand() % 10;
                bool hit = player.board.shoot(x, y);
                cout << "CPU fires at (" << x << ", " << y << "): " << (hit ? "Hit!" : "Miss.") << endl;
                if (player.board.allShipsSunk()) {
                    cout << " CPU wins!\n";
                    break;
                }
            }

            cout << "\n Current Boards:\n";
            cout << "Your Board:\n";
            player.board.displayBoard(true);
            cout << "\nCPU Board (Hits/Misses):\n";
            cpu.board.displayBoard(false);

            playerTurn = !playerTurn;
        }

        cout << "\n Game Over - Final Boards \n";
        cout << "Your Board:\n";
        player.board.displayBoard(true);
        cout << "\nCPU Board:\n";
        cpu.board.displayBoard(true);
    }
};

#endif //BATTLESHIP_H
