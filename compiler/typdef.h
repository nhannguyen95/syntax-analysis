
#ifndef __typdef__
#define __typdef__

#include <cstring>
#include <vector>
#include <map>
using namespace std;

typedef map<string, vector<vector<pair<string,int>>>> TapSuyDanArr;
typedef pair<TapSuyDanArr, TapSuyDanArr> ThucThe;

typedef map<string,
            vector<
                    pair<
                          vector<pair<string,int>>,
                          string
                        >
                  >
           > TapSuyDanArrCnnl;
typedef pair<TapSuyDanArrCnnl, TapSuyDanArrCnnl> ThucTheCnnl;

static int LENGTH_CHAR = 0;

#endif
