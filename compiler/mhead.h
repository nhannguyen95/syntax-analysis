#ifndef head_h
#define head_h

#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include "mtype.h"
#include "typdef.h"
using namespace std;

#define sz(a) int(a.size())
#define mp make_pair
#define fi first
#define se second
#define pb push_back

extern map<string, vector<string>> suydanthuan;
extern map<string, string> suydannguoc;
extern map<string, vector<vector<pair<string,int>>>> suydanArr;
extern map<pair<string, string>, char> quanhe;
extern vector<string> inpV;

static int num_gap_space_0 = 14;
static int num_gap_space_1 = 10;
static int num_gap_space_2 = 6;

#endif
