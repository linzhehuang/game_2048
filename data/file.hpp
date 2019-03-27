#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include "grid.hpp"
using namespace std;

class File {
public:
        File() {
                currentPath = ExtractFilePath(Application->ExeName);
                dataFile = currentPath + "data.db";
        }
        AnsiString GetCurrentPath() {
                return currentPath;
        }
        void SaveDataFile(Grid &grid) {
                ofstream outfile(dataFile.c_str(),ios::out);
                if(!outfile) {
                        ShowMessage("存档出错！");
                        return;
                }
                for(int i = 0;i < 4;i++) {
                        for(int j = 0;j < 4;j++) {
                                outfile << grid.GetData(i,j) << endl;
                        }
                }
                outfile << grid.GetScore() << endl;
                outfile.close();
        }
        void ReadDataFile(Grid &grid) {
                ifstream infile(dataFile.c_str(),ios::in);
                if(!infile) {
                        ShowMessage("存档文件不存在!");
                        return;
                }
                string buff;
                int count = 0;
                while(getline(infile,buff)) {
                        int num = AnsiString(buff.c_str()).ToInt();
                        if(count == 16) {
                                grid.SetScore(num);
                        }
                        else {
                                grid.SetData(count/4,count%4,num);
                        }
                        count++;
                }
                infile.close();
        }
private:
        AnsiString currentPath;
        AnsiString dataFile;
};

#endif
