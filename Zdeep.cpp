#include "Zdeep.h"

void Zdeep::caldeep(int dep, GLubyte nowimage[800][800][3], GLubyte newimage[800][800][3]){
	int flag;
	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 800; j++) {
			flag = 0;
			for (int k = 0; k < 3; k++) {
				if (int(nowimage[i][j][k]) == 0) continue;
				else flag = 1;
			}
			if (flag==0||dep < deep[i][j]) continue;
			deep[i][j] = dep;
			//cout << i << " " << j << '\n';
			for (int k = 0; k < 3; k++) {
				newimage[i][j][k] = nowimage[i][j][k];
			}
		}
	}
}
