#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <stack>
#include <stdexcept>
#include <string>
struct item {
  int x;
  int y;
  int dir;
  item(int x, int y)
      : x(x), y(y),
        dir(0){}; // struct item can be initialize with x,y and a optional dir
  item(int x, int y, int dir) : x(x), y(y), dir(dir){};
};
class Solution {
public:
  explicit Solution(std::array<std::array<bool, 17>, 17> &maze)
      : maze(maze) {} // pass in a 2d array to initialize

  void sol(int startPosX, int startPosY, int exitPosX, int exitPosY) {
    std::array<std::array<bool, 17>, 17> mark = {{false}};
    // create a 17x17 bool array and initialize
    // as false at all position
    // this indicates wheather the rat have been there or not
    counter = 0;
    std::stack<item> stackOfItem;     // create a stack of struct item
    item first(startPosX, startPosY); // create a struct item with x,y position
    stackOfItem.push(first);
    mark.at(startPosX).at(startPosY) =
        true; // mark start position as true on the mark 2d array
    while (!stackOfItem.empty()) {
      item top = stackOfItem.top();
      stackOfItem
          .pop(); // get the top item of the stack and delete it from the stack
      int currentX = top.x;
      int currentY = top.y;
      int d = top.dir;
      while (d < 4) {
        int nextX = currentX;
        int nextY = currentY;
        getNextPath(d, nextX,
                    nextY); // let var nextX and nextY be the next position the
                            // rat would go(depends on var d)
        if (nextX == exitPosX && nextY == exitPosY) {
          std::cout
              << counter << ':' << currentX << ','
              << currentY // if the next position is the exit position, print
                          // out the current position and the exit position
              << std::endl;
          counter++;
          std::cout << counter << ':' << exitPosX << ',' << exitPosY
                    << std::endl;
          std::cout << "successfully escaped!!" << std::endl;

          return;
        }
        if (!maze.at(nextX).at(nextY) &&
            !mark.at(nextX).at(
                nextY)) { // if the maze have no wall on nextX,nextY
                          // position and the rat have not been
                          // there(mark array is false)
          mark.at(nextX).at(nextY) = true;
          top.x = currentX;
          top.y = currentY;
          top.dir =
              d + 1; // change struct item top with the current x,y and add 1 to
                     // the var dir so that when we pop this item from the stack
                     // next time, we will try a different dir
          stackOfItem.push(top); // push top back to the stack
          currentX = nextX;
          currentY = nextY;
          d = 0;            // reset current x,y as nextX,nextY
          printStruct(top); // print current position when the rat is going to
                            // try out a new path
        } else {
          d++; // try a different dir
        }
      }
      printStruct(top); // print path when the rat is moving backwards(from it's
                        // last path)
    }
    std::cout << "Failed to escape." << std::endl;
    return;
  }

  int counter = 0;
  std::array<std::array<bool, 17>, 17> maze;
  bool getNextPath(int dir, int &x,
                   int &y) const { // change x,y depend on var "dir"
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
    std::cout << counter << ':' << tmp.x << ',' << tmp.y << std::endl;
    counter++;
  }
};
class FileIO {
public:
  FileIO() { getFileName(); } // try to get the filename at initialize
  // create a 17x17 array and initialize as false at all position
  std::array<std::array<bool, 17>, 17> maze = {{false}};

  void openAndConvert() {
    fileBuffer.open(fileName);
    if (fileBuffer.is_open()) {
      try {
        convertStringToBool(); // convert the txt file to a 2d array of bool
      } catch (const std::length_error &e) {
        std::cerr << e.what() << std::endl;
      }
      printMaze();
    } else {
      std::cerr << "can't open file name : " << fileName << std::endl;
      fileBuffer
          .close(); // if can not open file get a new filename and try again
      getFileName();
      openAndConvert();
    }
    fileBuffer.close();
  }

  void getFileName() {
    std::cout << "enter filename : ";
    std::cin >> fileName;
    if (std::cin.eof()) {
      throw std::invalid_argument("EOF entered");
    }
  }
  void convertStringToBool() {
    std::string stringBuffer;
    int row = 0;
    while (std::getline(fileBuffer, stringBuffer)) {
      if (row > 17) {
        throw std::length_error(
            "row length is larger than 17"); // throw error when row is larger
                                             // than 17
      }
      if (stringBuffer.size() > 17) {
        throw std::length_error(
            "line length is larger than 17 char"); // throw error when line
                                                   // length is larger than 17
      }
      for (size_t i = 0; i < stringBuffer.size(); i++) {
        if (stringBuffer.at(i) ==
            '1') { // if the char at position i in the line
                   // is '1' then change maze[row][i] to true
          // maze[row][i] = true;
          maze.at(row).at(i) = true;
        }
      }
      row++;
    }
  }
  void printMaze() const {
    for (int i = 0; i < 17; i++) {
      for (int j = 0; j < 17; j++) {
        std::cout << maze.at(i).at(j);
      }
      std::cout << std::endl;
    }
  }
  std::string fileName;
  std::ifstream fileBuffer;
};
int main() {
  FileIO mazeFile;
  mazeFile.openAndConvert(); // open the file and try to convert it to 2d array
                             // of bool
  while (!std::cin.eof()) {
    int startPosX;
    int startPosY;
    int exitPosX;
    int exitPosY;
    std::cout << "enter start position : ";
    std::cin >> startPosX >> startPosY;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "enter invalid" << std::endl;
      continue;
    }
    if (startPosX == -1 &&
        startPosY == -1) { // quit program when entered "-1 -1"
      std::cout << "end the code." << std::endl;
      break;
    }
    if (mazeFile.maze.at(startPosX).at(
            startPosY)) { // check the entered position is valid or
                          // not e.g can not start from a wall
      std::cerr << "unvalid position" << std::endl;
      continue;
    }
    std::cout << "enter exit position : ";
    std::cin >> exitPosX >> exitPosY;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "enter invalid" << std::endl;
      continue;
    }

    if (exitPosX == -1 && exitPosY == -1) { // quit program when entered "-1 -1"
      std::cout << "end the code." << std::endl;
      break;
    }
    if (mazeFile.maze.at(exitPosX).at(
            exitPosY)) { // check the entered position is valid
                         // or not e.g can not end at a wall
      std::cerr << "unvalid position" << std::endl;
      continue;
    }
    Solution sol(mazeFile.maze); // pass in the maze to solution object
    sol.sol(startPosX, startPosY, exitPosX,
            exitPosY); // try the entered positions
  }
  return 0;
}
