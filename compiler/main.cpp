/*
 Nguyen Thanh Nhan - 13PFIEV3
  1. Phuong phap uu tien toan tu (p.128): inp1, inp2, inp3(wrong)
  2. Phuong phap thu tu yeu (p.149): inp3, inp4
  3. Phuong phap simple LR (SLR) (p.168): inp5(E), inp6(A), inp7(S)
  4. Phuong phap Canonical LR (p.200): inp8(S), inp9(S), inp10(S)
 */

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <set>
#include "utils.h"
#include "typdef.h"

//#include "uutientoantu.h"
//#include "thutuyeu.h"
#include "simplelr.h"
//#include "canonicallr.h"
using namespace std;

map<string, vector<string>> suydanthuan;
map<string, string> suydannguoc;
TapSuyDanArr suydanArr;
map<pair<string, string>, char> quanhe;
vector<string> inpV;

int main() {
    
#define RELEASE
#ifdef RELEASE
    freopen("/Users/apple/Desktop/code/c-c++/compiler/compiler/input/inp5.txt", "r", stdin);
    freopen("/Users/apple/Desktop/code/c-c++/compiler/compiler/output/out.txt", "w", stdout);
#endif
    
    entryPoint("E");
    
    return 0;
}