#include <fstream>
#include <iostream>
#include <stack>
int counter = 0;
struct item {
  int x;
  int y;
  int dir;
  item(int x, int y) : x(x), y(y), dir(0){};
  item(int x, int y, int dir) : x(x), y(y), dir(dir){};
};
void convertCharToInt(std::ifstream &fileBuffer, int (&maze)[17][17]);
void printMaze(int (&maze)[17][17]);
bool sol(int (&maze)[17][17], int startPosX, int startPosY, int exitPosX,
         int exitPosY);
bool getNextPath(int &startX, int &startY, int &endX, int &endY);
void print(item tmp);
int main() {
  // std::string fileName = "maze.txt";
  std::string fileName;
  std::cout << "enter filename : ";
  std::cin >> fileName;
  std::ifstream fileBuffer;
  fileBuffer.open(fileName);
  int maze[17][17] = {{0}};
  if (fileBuffer.is_open()) {
    convertCharToInt(fileBuffer, maze);
    printMaze(maze);
    int startPosX, startPosY, exitPosX, exitPosY;
    std::cout << "enter start position : ";
    std::cin >> startPosX >> startPosY;
    if (maze[startPosX][startPosY]) {
      std::cerr << "unvalid position" << std::endl;
      return 1;
    }
    std::cout << "enter exit position : ";
    std::cin >> exitPosX >> exitPosY;
    if (maze[exitPosX][exitPosY]) {
      std::cerr << "unvalid position" << std::endl;
      return 1;
    }

    std::cout << sol(maze, startPosX, startPosY, exitPosX, exitPosY)
              << std::endl;
  } else {
    std::cerr << "can't open file name" << fileName << std::endl;
    return 1;
  }
  return 0;
}
void convertCharToInt(std::ifstream &fileBuffer, int (&maze)[17][17]) {
  char buffer[18] = {0};
  int x = 0;
  while (fileBuffer.getline(buffer, sizeof(buffer))) {
    // fileBuffer.getline(buffer, sizeof(buffer));
    for (int i = 0; i < 17; i++) {
      if (buffer[i] == '1') {
        maze[x][i] = 1;
      }
    }
    x++;
  }
  fileBuffer.close();
}
void printMaze(int (&maze)[17][17]) {
  for (int i = 0; i < 17; i++) {
    for (int j = 0; j < 17; j++) {
      std::cout << maze[i][j];
    }
    std::cout << std::endl;
  }
}
bool getNextPath(int dir, int &x, int &y) {
  switch (dir) {
  case 0:
    y++;
    return true;
  case 1:
    x++;
    return true;
  case 2:
    x--;
    return true;
  case 3:
    y--;
    return true;
  default:
    return false;
  }
}
bool sol(int (&maze)[17][17], int startPosX, int startPosY, int exitPosX,
         int exitPosY) {
  int mark[17][17] = {{0}};
  std::stack<item> stack;
  item first(startPosX, startPosY);
  stack.push(first);
  mark[startPosX][startPosY] = 1;
  while (!stack.empty()) {
    item top = stack.top();
    stack.pop();
    int i = top.x, j = top.y, d = top.dir;
    while (d < 4) {
      int nextX = i;
      int nextY = j;
      getNextPath(d, nextX, nextY);
      if (nextX == exitPosX && nextY == exitPosY) {
        std::cout << counter++ << ':' << i << ',' << j << std::endl;
        std::cout << counter++ << ':' << nextX << ',' << nextY << std::endl;

        return true;
      }
      if (!maze[nextX][nextY] && !mark[nextX][nextY]) {
        mark[nextX][nextY] = 1;
        top.x = i;
        top.y = j;
        top.dir = d + 1;
        stack.push(top);
        i = nextX;
        j = nextY;
        d = 0;
        print(top);
      } else {
        d++;
      }
    }
    print(top);
  }
  return false;
}
void print(item tmp) {
  std::cout << counter++ << ':' << tmp.x << ',' << tmp.y << std::endl;
}
