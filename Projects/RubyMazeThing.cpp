#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Cell : public RectangleShape {
   public:
    bool north = false;
    bool east = false;
    bool west = false;
    bool south = false;
    bool visited = false;

    void Reset() {
        this->setFillColor(Color::White);
        this->visited = false;
        this->north = false;
        this->east = false;
        this->west = false;
        this->south = false;
        this->visited = false;
    }
};

class Button : public RectangleShape {
   public:
};

void printGridDetails(vector<Cell> Grid, int Size) {
    for (int i = 0; i < Size * Size; i++) {
        int x = i % Size;
        int y = i / Size;
        cout << "Grid ID - " << i << " visited - " << Grid[i].visited << ", x - " << x << ", y - " << y << ", north - " << Grid[i].north << ", east - " << Grid[i].east << ", west - " << Grid[i].west << ", south - " << Grid[i].south << endl;
    }
}

Vector2i returnCoordinates(int ID, int Size) {
    Vector2i result;
    result.x = ID / Size;
    result.y = ID % Size;
    return result;
}

int returnID(int x, int y, int size) {
    return size * y + x;
}

void setNeighbours(vector<Cell> &Grid, int size) {
    for (int i = 0; i < size * size; i++) {
        if (Grid[i].visited) {
            Vector2i northID = returnCoordinates(i - size, size);
            Vector2i southID = returnCoordinates(i + size, size);
            Vector2i eastID = returnCoordinates(i - 1, size);
            Vector2i westID = returnCoordinates(i + 1, size);

            if (((northID.x < size) && (northID.x >= 0)) && ((northID.y < size) && (northID.y >= 0))) {
                if (Grid[returnID(northID.x, northID.y, size)].visited) {
                    Grid[i].north = true;
                }
            }
            if (((southID.x < size) && (southID.x >= 0)) && ((southID.y < size) && (southID.y >= 0))) {
                if (Grid[returnID(southID.x, southID.y, size)].visited) {
                    Grid[i].south = true;
                }
            }
            if (((eastID.x < size) && (eastID.x >= 0)) && ((eastID.y < size) && (eastID.y >= 0))) {
                if (Grid[returnID(eastID.x, eastID.y, size)].visited) {
                    Grid[i].east = true;
                }
            }
            if (((westID.x < size) && (westID.x >= 0)) && ((westID.y < size) && (westID.y >= 0))) {
                if (Grid[returnID(westID.x, westID.y, size)].visited) {
                    Grid[i].west = true;
                }
            }
        }
    }
}

int main() {
    RenderWindow mainWindow(VideoMode(600, 800), "Ruby Maze Thing", Style::Close);

    // Grid Generation
    int xPos = 45;
    int yPos = 100;
    int size = 10;
    int cellSize = 50;
    int padding = 1;
    vector<Cell> Grid(size * size);
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int ID = returnID(x, y, size);
            Grid[ID].setFillColor(Color::White);
            Grid[ID].setPosition(Vector2f(xPos, yPos));
            Grid[ID].setSize(Vector2f(cellSize, cellSize));
            xPos += cellSize + padding;
        }
        xPos = 45;
        yPos += cellSize + padding;
    }

    int noButtons = 3;
    vector<Button> Buttons(noButtons);

    Font font;
    if (!font.loadFromFile("Projects\\Fonts\\PlayfairDisplay-Regular.ttf")) {
        cout << "Font Failed to load" << endl;
    }

    Text buttonText[noButtons];

    for (int i = 0; i < noButtons; i++) {
        // Button stuff
        Buttons[i].setFillColor(Color::Black);
        Buttons[i].setOutlineThickness(1);
        Buttons[i].setOutlineColor(Color(170, 169, 173, 255));
        Buttons[i].setSize(Vector2f(150, 50));

        // Button text stuff
        buttonText[i].setFont(font);
        buttonText[i].setCharacterSize(20);
        buttonText[i].setFillColor(Color::White);
    }
    // Positioning Buttons
    Buttons[0].setPosition(Vector2f(50, 690));
    Buttons[1].setPosition(Vector2f(300, 690));
    Buttons[2].setPosition(Vector2f(50, 0));
    // Positioning Text
    buttonText[0].setPosition(Vector2f(50, 690));
    buttonText[1].setPosition(Vector2f(300, 690));
    buttonText[2].setPosition(Vector2f(50, 0));
    buttonText[0].setString("set neighbours");
    buttonText[1].setString("reset");
    buttonText[2].setString("Output");

    Event gameEvent;
    while (mainWindow.isOpen()) {
        while (mainWindow.pollEvent(gameEvent)) {
            if (gameEvent.type == gameEvent.Closed) {
                mainWindow.close();
            }
        }

        // User Clicks then do stuff
        if (Mouse::isButtonPressed(Mouse::Left)) {
            // Checks if button clicks grid
            for (int i = 0; i < size * size; i++) {
                if ((Grid[i].getGlobalBounds().contains(Vector2f(Mouse::getPosition(mainWindow).x, Mouse::getPosition(mainWindow).y))) && !Grid[i].visited) {
                    Grid[i].visited = true;
                    Grid[i].setFillColor(Color(255, 165, 0, 255));  // Orange
                }
            }
            // Checks if button clicks a button
            if (Buttons[1].getGlobalBounds().contains(Vector2f(Mouse::getPosition(mainWindow).x, Mouse::getPosition(mainWindow).y))) {
                for (int i = 0; i < size * size; i++) {
                    Grid[i].Reset();
                }
            }
            // Checks if button clicks a button
            if (Buttons[0].getGlobalBounds().contains(Vector2f(Mouse::getPosition(mainWindow).x, Mouse::getPosition(mainWindow).y))) {
                setNeighbours(Grid, size);
            }
            // Checks if button clicks a button
            if (Buttons[2].getGlobalBounds().contains(Vector2f(Mouse::getPosition(mainWindow).x, Mouse::getPosition(mainWindow).y))) {
                printGridDetails(Grid, size);
            }
        }

        // Remove a Cell
        if (Mouse::isButtonPressed(Mouse::Right)) {
            for (int i = 0; i < size * size; i++) {
                if ((Grid[i].getGlobalBounds().contains(Vector2f(Mouse::getPosition(mainWindow).x, Mouse::getPosition(mainWindow).y))) && Grid[i].visited) {
                    Grid[i].visited = false;
                    Grid[i].setFillColor(Color(255, 255, 255, 255));  // white
                }
            }
        }

        mainWindow.clear(Color::Black);
        for (int i = 0; i < size * size; i++) {
            mainWindow.draw(Grid[i]);
        }
        for (int i = 0; i < noButtons; i++) {
            mainWindow.draw(Buttons[i]);
            mainWindow.draw(buttonText[i]);
        }
        mainWindow.display();
    }

    return 0;
}