## DataStructure_HW1

#### 執行環境：

* 電腦：MacBook Pro 15-inch, 2017
* 作業系統：macOS Big Sur 11.6
* CPU: i7-7700HQ
* RAM: 16GB

#### 程式編譯環境：

* 使用程式語言：C++

在 terminal 中使用g++

![截圖 2021-10-21 下午12.58.40](./截圖 2021-10-21 下午12.58.40.png)

編譯 argument 為 g++-11 -O2 -Wall -Wextra -std=gnu++17 -pedantic rat.cpp -o rat

![截圖 2021-10-21 下午1.10.19](./截圖 2021-10-21 下午1.10.19.png)



#### 遇到的問題

1. 一開始我用 stack of pointer to struct item 會使程式在執行 stack.pop() 時並沒有真正 delete struct item。
2. 如果 start position 或 exit position 在 barrier 上的話會有問題。
3. 如果 maze.txt 裡一行超過17個字元或超過17行的話程式會crash。

#### 解決辦法

1. 改用 stack of struct item。
2. 使用者輸入 position 時檢查，若輸入錯誤則重新輸入。
3. 在將 maze.txt 轉成 2d array 時，增加一個檢查長度以及行數的程式碼。
