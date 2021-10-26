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
  item(int x, int y) : x(x), y(y), dir(0){};  // struct `item` can be initialize with x,y and a optional dir
  item(int x, int y, int dir) : x(x), y(y), dir(dir){};
};
class Solution {
 public:
  const bool (&maze)[17][17];
  explicit Solution(const bool (&maze)[17][17]) : maze(maze) {}  // pass in a 2d array to initialize

  /**
   * this function is the main algo that will try all path in the maze
   * @param startPosX the starting position x
   * @param startPosY the starting position y
   * @param exitPosX the ending position x
   * @param exitPosY the ending position y
   */
  void sol(const int startPosX, const int startPosY, const int exitPosX, const int exitPosY) {
    bool mark[17][17] = {{false}};
    // create a 17x17 bool array and initialize
    // as false at all position
    // this 2d array `mark` indicates wheather the rat have been there or not
    counter = 0;                       // reset counter to 0
    std::stack<item> stackOfItem;      // create a stack of struct `item`
    item first(startPosX, startPosY);  // create a struct item with the starting x,y position
    stackOfItem.push(first);
    mark[startPosX][startPosY] = true;  // mark start position as true on the `mark` 2d array
    while (!stackOfItem.empty()) {  // when the stack is not empty which mean there are paths that we have not tried yet
      item top = stackOfItem.top();
      stackOfItem.pop();  // get the top item of the stack and delete it from the stack
      int currentX = top.x;
      int currentY = top.y;
      int d = top.dir;
      while (d <
             4) {  // when d is smaller thant 4, means that there are still directions that the rat has not tried yet
        int nextX = currentX;
        int nextY = currentY;
        getNextPath(d, nextX,
                    nextY);  // let var nextX and nextY be the next position the
                             // rat would go(depends on var d)
        if (nextX == exitPosX && nextY == exitPosY) {
          std::cout << counter << ':' << currentX << ','
                    << currentY  // if the next position is the exit position, print
                                 // out the current position and the exit position
                    << std::endl;
          counter++;
          std::cout << counter << ':' << exitPosX << ',' << exitPosY << std::endl;
          std::cout << "successfully escaped!!" << std::endl;

          return;
        }
        if (!maze[nextX][nextY] && !mark[nextX][nextY]) {  // if the maze have no barrier on (nextX,nextY)
                                                           // position and the rat have not been
                                                           // there(mark array is false)
          mark[nextX][nextY] = true;
          top.x = currentX;
          top.y = currentY;
          top.dir = d + 1;  // change struct item top with the current (x,y) and add 1 to
                            // the `dir` so that when we pop this item from the stack
                            // next time, we will try a different direction

          stackOfItem.push(top);  // push top back to the stack
          currentX = nextX;
          currentY = nextY;
          d = 0;             // reset current position as nextX,nextY
          printStruct(top);  // print current position when the rat is going to
                             // try out a new path
        } else {
          d++;  // try a different dir when the next (x,y) is not valid
        }
      }
      printStruct(top);  // print path when the rat is moving backwards(from it's
                         // last path)
    }
    std::cout << "Failed to escape." << std::endl;  // when the stack is empty indicates that there is no path to try
    return;
  }

 private:
  unsigned int counter;  // counter that counts the step of the rat
  /**
   * change the position according var dir
   * @param dir the direction of the next path
   * @param x the position x that will be changed to the next position
   * @param y the position y that will be changed to the next position
   */
  void getNextPath(const int dir, int &x,
                   int &y) const {  // change x,y depend on var "dir"
    switch (dir) {
      case 0:
        y++;
        break;
      case 1:
        x++;
        break;
      case 2:
        x--;
        break;
      case 3:
        y--;
        break;
      default:
        return;
    }
  }

  /**
   * print out the struct item whith the format of "counter:x,y\n"
   * @param tmp the struct item that will be printed out
   */
  void printStruct(const item &tmp) {
    std::cout << counter << ':' << tmp.x << ',' << tmp.y << std::endl;
    counter++;
  }
};
class FileIO {
 public:
  // std::string fileName;
  char fileName[256];
  std::ifstream fileBuffer;
  bool maze[17][17];
  FileIO() { getFileName(); }  // try to get the filename at initialization
  // create a 17x17 array and initialize as false at all position

  /**
   * tries to open the file with the filename that was been retrieved when initializing the class object
   */
  void openAndConvert() {
    fileBuffer.open(fileName);
    if (fileBuffer.is_open()) {
      try {
        convertStringToBool();  // convert the txt file to a 2d array of bool
      } catch (const std::length_error &e) {
        std::cerr << e.what() << std::endl;  // if there was exceptions during the process output it to std error;
      } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
      }
    } else {
      std::cerr << "can't open file name : " << fileName << std::endl;
      fileBuffer.close();  // if can not open file get a new filename and try again
      getFileName();
      openAndConvert();
    }
    fileBuffer.close();
  }
  /**
   * print the 17x17 maze
   */
  void printMaze() const {
    for (int i = 0; i < 17; i++) {
      for (int j = 0; j < 17; j++) {
        std::cout << maze[i][j];
      }
      std::cout << std::endl;
    }
  }

 private:
  /**
   * tries to get the file name
   * @throws throw an exception when user enter EOF
   */
  void getFileName() {
    std::cout << "enter filename : ";
    std::cin >> fileName;
    if (std::cin.fail()) {
      throw std::invalid_argument("entered invalid input");
    }
  }
  /**
   * convert the file to 2d array line by line
   * @throws  when the line is more than 17 char, throw an exception
   * @throws when there more than 17 lines, throw an exception
   * @throws when the maze file contains invalid char
   */
  void convertStringToBool() {
    std::string stringBuffer;
    int row = 0;
    while (std::getline(fileBuffer, stringBuffer)) {
      if (row > 17) {
        throw std::length_error("row length is larger than 17");  // throw error when row is larger
                                                                  // than 17
      }
      if (stringBuffer.size() > 17) {
        throw std::length_error("line length is larger than 17 char");  // throw error when line
                                                                        // length is larger than 17
      }
      for (size_t i = 0; i < stringBuffer.size(); i++) {
        if (stringBuffer.at(i) == '1') {  // if the char at position i in the line
                                          // is '1' then change maze[row][i] to true
          maze[row][i] = true;
        } else if (stringBuffer.at(i) == '0') {
          maze[row][i] = false;
        } else {
          throw std::invalid_argument("the maze file has some problems");  // throw error when there are not '1' or '0'
        }
      }
      row++;
    }
  }
};
int main() {
  FileIO mazeFile;
  mazeFile.openAndConvert();  // open the file and try to convert it to 2d array
                              // of bool
  mazeFile.printMaze();
  bool(&maze)[17][17] = mazeFile.maze;
  Solution sol(maze);  // pass in the maze to solution object

  while (!std::cin.eof()) {
    int startPosX;
    int startPosY;
    int exitPosX;
    int exitPosY;
    std::cout << "enter start position : ";
    std::cin >> startPosX >> startPosY;
    if (std::cin.fail()) {  // if user enter a invalid value e.g "a b" or "1.1 2.2" clear the input buffer
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "invalid input" << std::endl;
      continue;
    }
    if (startPosX == -1 && startPosY == -1) {  // quit program when entered "-1 -1"
      std::cout << "end the code." << std::endl;
      return 0;
    }
    if (maze[startPosX][startPosY]) {  // check the entered position is valid or
                                       // not e.g can not start from a barrier
      std::cerr << "invalid position" << std::endl;
      continue;
    }
    std::cout << "enter exit position : ";
    std::cin >> exitPosX >> exitPosY;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "invalid input" << std::endl;
      continue;
    }

    if (exitPosX == -1 && exitPosY == -1) {  // quit program when entered "-1 -1"
      std::cout << "end the code." << std::endl;
      return 0;
    }
    if (maze[startPosX][startPosY]) {  // check the entered position is valid
                                       // or not e.g can not end at a barrier
      std::cerr << "invalid position" << std::endl;
      continue;
    }
    sol.sol(startPosX, startPosY, exitPosX,
            exitPosY);  // try the entered positions
  }
  return 0;
}
