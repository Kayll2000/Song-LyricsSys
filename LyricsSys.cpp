/****************************************************************************************************************************
* @function:基于C++的歌词轮播系统
* @version:v1.0
* @author:chenjunlong
* @description:To achieve simple lyrics of the wheel broadcast function.
* @github:https://github.com/Kayll2000/Alumni-login-system.git
* @date:2023.05.12
* @lmodauthor:chenjunlong
* @lmoddate:2023.05.12
* @compile:Compile the environment is Dev-C++(Embarcadero Dev-C++)
*           FUCTION:
                    1、导入lyrics.txt歌词文件后，运行即能实现歌词轮播。

            BUGFIX:

            MODIFY:

        

*
****************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

// 逐字输出文字
void printCharByChar(string s, int delay) {
    for (int i = 0; i < s.size(); i++) {
        cout << s[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delay)); // 延时
    }
}

class Lyric {
private:
    string content; // 歌词内容
    int timestamp;  // 时间戳（单位：毫秒）
    int position;   // 显示位置（第几行）
public:
    Lyric(string content, int timestamp, int position) {
        this->content = content;
        this->timestamp = timestamp;
        this->position = position;
    }
    string getContent() { return content; }
    int getTimestamp() { return timestamp; }
    int getPosition() { return position; }
};

vector<Lyric> loadLyricsFromFile(string filename) {
    vector<Lyric> lyrics;
    ifstream fin(filename);
    if (!fin) {
        cout << "Failed to read file: " << filename << endl;
        return lyrics;
    }
    Lyric *p = NULL;
    int t = 0;//记录第几行
    string line;
    while (getline(fin, line)) {
        // 解析每一行歌词内容和时间戳
        // 将其转化为Lyric对象，加入到数组中

        //cout << "line " << t << "content:" << line << endl;
        p = new Lyric(line,200,t);
        lyrics.push_back(*p);
        t++;
    }
    fin.close();
    return lyrics;
}

int getCurrentTime() {
    auto now = chrono::system_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch());
    return (int)ms.count();
}

void showLyrics(vector<Lyric> lyrics, int currentTime) {
    for (Lyric lyric : lyrics) {
        if (lyric.getTimestamp() <= currentTime) {
            // 显示歌词内容到指定位置
            //this_thread::sleep_for(chrono::milliseconds(lyric.getTimestamp()));
            string s = lyric.getContent();
            printCharByChar(s, lyric.getTimestamp());
            cout << endl;
            //cout << lyric.getContent() << endl;
        }
   }
}
int main() {
    // 加载歌词文件
    vector<Lyric> lyrics = loadLyricsFromFile("lyrics.txt");
    if (lyrics.empty()) {
        return 0;
    }

    // 播放音乐
    int startTime = getCurrentTime();
    while (true) {
        int currentTime = getCurrentTime() - startTime;
        showLyrics(lyrics, currentTime);
        this_thread::sleep_for(chrono::milliseconds(1000)); // 控制帧率，每秒显示100帧
    }

    return 0;
}
