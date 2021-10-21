#include <fstream>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
int counter = 0;
struct item {
  int x;
  int y;
  int dir;
  item(int x, int y) : x(x), y(y), dir(0){};
  item(int x, int y, int dir) : x(x), y(y), dir(dir){};
};
class Solution {
public:
  Solution(bool (&maze)[17][17]) : maze(maze) {}

  void sol(int startPosX, int startPosY, int exitPosX, int exitPosY) {
    bool mark[17][17] = {{false}};
    counter = 0;
    std::stack<item> stackOfItem;
    item first(startPosX, startPosY);
    stackOfItem.push(first);
    mark[startPosX][startPosY] = 1;
    while (!stackOfItem.empty()) {
      item top = stackOfItem.top();
      stackOfItem.pop();
      int currentX = top.x, currentY = top.y, d = top.dir;
      while (d < 4) {
        int nextX = currentX;
        int nextY = currentY;
        getNextPath(d, nextX, nextY);
        if (nextX == exitPosX && nextY == exitPosY) {
          std::cout << counter++ << ':' << currentX << ',' << currentY
                    << std::endl;
          std::cout << counter++ << ':' << nextX << ',' << nextY << std::endl;
          std::cout << "successfully escaped!!" << std::endl;

          return;
        }
        if (!maze[nextX][nextY] && !mark[nextX][nextY]) {
          mark[nextX][nextY] = true;
          top.x = currentX;
          top.y = currentY;
          top.dir = d + 1;
          stackOfItem.push(top);
          currentX = nextX;
          currentY = nextY;
          d = 0;
          printStruct(top);
        } else {
          d++;
        }
      }
      printStruct(top);
    }
    std::cout << "Failed to escape." << std::endl;
    return;
  }

private:
  int counter;
  bool (&maze)[17][17];
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

  void printStruct(item tmp) {
    std::cout << counter++ << ':' << tmp.x << ',' << tmp.y << std::endl;
  }
};
class FileIO {
public:
  FileIO() { getFileName(); }
  bool maze[17][17] = {{false}};
  void getFileName() {
    std::cout << "enter filename : ";
    std::cin >> fileName;
  }
  void openAndConvert() {
    fileBuffer.open(fileName);
    if (fileBuffer.is_open()) {
      try {
        convertStringToBool();
      } catch (const std::length_error &e) {
        std::cout << e.what() << std::endl;
      }
      printMaze(maze);
    } else {
      std::cerr << "can't open file name : " << fileName << std::endl;
      fileBuffer.close();
      getFileName();
    }
    fileBuffer.close();
  }
  void convertStringToBool() {
    std::string stringBuffer;
    int x = 0;
    while (std::getline(fileBuffer, stringBuffer)) {
      if (stringBuffer.size() > 17) {
        throw std::length_error("line length is larger than 17 char");
        continue;
      }
      for (size_t i = 0; i < stringBuffer.size(); i++) {
        if (stringBuffer[i] == '1') {
          maze[x][i] = true;
        }
      }
      x++;
    }
  }
  void printMaze(bool (&maze)[17][17]) {
    for (int i = 0; i < 17; i++) {
      for (int j = 0; j < 17; j++) {
        std::cout << maze[i][j];
      }
      std::cout << std::endl;
    }
  }

private:
  std::string fileName;
  std::ifstream fileBuffer;
};
int main() {
  FileIO mazeFile;
  mazeFile.openAndConvert();
  while (true) {
    int startPosX, startPosY, exitPosX, exitPosY;
    std::cout << "enter start position : ";
    std::cin >> startPosX >> startPosY;
    if (startPosX == -1 && startPosY == -1) {
      std::cout << "end the code." << std::endl;
      return 0;
    }
    if (mazeFile.maze[startPosX][startPosY]) {
      std::cerr << "unvalid position" << std::endl;
      continue;
    }
    std::cout << "enter exit position : ";
    std::cin >> exitPosX >> exitPosY;
    if (startPosX == -1 && startPosY == -1) {
      std::cout << "end the code." << std::endl;
      return 0;
    }
    if (mazeFile.maze[exitPosX][exitPosY]) {
      std::cerr << "unvalid position" << std::endl;
      continue;
    }
    Solution sol(mazeFile.maze);
    sol.sol(startPosX, startPosY, exitPosX, exitPosY);
  }
  return 0;
}
