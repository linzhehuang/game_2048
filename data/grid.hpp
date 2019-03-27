#ifndef GRID_HPP
#define GRID_HPP

#include "random.hpp"

class Grid {
public:
  	enum Direction {
    		DIRECT_UP = 1,
    		DIRECT_RIGHT = 2,
		DIRECT_DOWN = 3,
		DIRECT_LEFT = 4
	};
	Grid() {
                random = new Random();
                score = 0;
		memset(gridData,0,sizeof(int)*16);
	}
	//
  	int &GetData(int x,int y) {
		return gridData[x][y];
	}
  	void SetData(int x,int y,int data) {
		gridData[x][y] = data;
	}
        int GetScore() {
                return score;
        }
        void SetScore(int num) {
                score = num;
        }
	void ClearGridData() {
		memset(gridData,0,sizeof(int)*16);
	}
        void ClearScore() {
                score = 0;
        }
	//

	void MoveByDirection(Direction dir) {
		for(int i = 0;i < 4;i++) {
			switch(dir) {
			case DIRECT_UP:
				MoveLine(gridData[0][i],gridData[1][i],
					gridData[2][i],gridData[3][i]);
        			break;
			case DIRECT_RIGHT:
				MoveLine(gridData[i][3],gridData[i][2],
					gridData[i][1],gridData[i][0]);
        			break;
			case DIRECT_DOWN:
				MoveLine(gridData[3][i],gridData[2][i],
					gridData[1][i],gridData[0][i]);
				break;
			case DIRECT_LEFT:
				MoveLine(gridData[i][0],gridData[i][1],
					gridData[i][2],gridData[i][3]);
				break;
			}
  		}
	}
        void GenerateNewValue() {
                int newValue = GetNewValue();
                int x,y;
                while(true) {
                        x = random->GetRandomNum(0,3);
                        y = random->GetRandomNum(0,3);
                        if(gridData[x][y] == 0) {
                                gridData[x][y] = newValue;
                                break;
                        }
                }
        }
	bool IsEnd() {
		if(!IsStuff()) return false;
		//
		int i,j;
		for(i = 0;i < 4;i++) {
			for(j = 0;j < 3;j++)
 				if(gridData[i][j] == gridData[i][j+1])
					return false;
		}
		//
  		for(i = 0;i < 4;i++) {
			for(j = 0;j < 3;j++)
				if(gridData[j][i] == gridData[j+1][i])
					return false;
		}
  		return true;
	}
  	//
	void operator=(Grid src) {
		int i,j;
		for(i = 0;i < 4;i++)
    			for(j = 0;j < 4;j++)
				gridData[i][j] = src.gridData[i][j];
	}
	friend bool operator!=(Grid &l,Grid &r) {
		int i,j;
		for(i = 0;i < 4;i++)
    			for(j = 0;j < 4;j++)
      				if(l.gridData[i][j] != r.gridData[i][j])
        				return true;
  		return false;
	}
private:
        Random *random;
        int score;
	int gridData[4][4];
	void MoveLine(int &a,int &b,int &c,int &d) {
		int line[4] = {a,b,c,d},tmpLine[4] = {0};
  		int i = 0,count = 0;
		//
		for(i = 0;i < 4;i++) {
			if(line[i] != 0) {
				tmpLine[count] = line[i];
				count++;
			}
		}

		//Combine the element with same value.
		for(i = 0;i < 3;i++)
			if(tmpLine[i] == tmpLine[i+1]) {
                                score += tmpLine[i];
				tmpLine[i] += tmpLine[i+1];
				tmpLine[i+1] = 0;
		        }
		//
		count = 0;
		for(i = 0;i < 4;i++) {
			line[i] = 0;
			if(tmpLine[i] != 0) {
				line[count] = tmpLine[i];
				count++;
			}
		}
		//Return the values.
		a = line[0];
		b = line[1];
		c = line[2];
		d = line[3];
	}
	bool IsStuff() {
		for(int i = 0;i < 4;i++)
    			for(int j = 0;j < 4;j++)
      				if(gridData[i][j] == 0) return false;
		return true;
	}
        inline int GetNewValue() {
                return (random->GetRandomNum(1,10) == 1)?4:2;
        }
};

#endif