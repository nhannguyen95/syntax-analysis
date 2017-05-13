#ifndef __utils__
#define __utils__

#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include "typdef.h"
#include "mtype.h"
#include "mhead.h"
using namespace std;

#define sz(a) int(a.size())
#define pb push_back
#define mp make_pair
#define fi first
#define se second

vector<string> splitAll(const string & s, const string & t) {
    vector<string> v;
    string s2(s);
    for (int p = 0; (p = (int)s2.find(t)) != s2.npos; ) {
        v.push_back(s2.substr(0, p));
        s2 = s2.substr(p + t.size());
    }
    v.push_back(s2);
    return v;
}

string trim(const string & s) {
    int f = 0;
    while(s[f] == ' ') f++;
    auto l = s.length() - 1;
    while(s[l] == ' ') l--;
    return s.substr(f, l - f + 1);
}

// s is trimed
vector<pair<string,int>> convertRightToArray(string s) {

    vector<pair<string,int>> v;
    int n = sz(s);
    
    // special case
    if (LENGTH_CHAR == 1) {
        for(int i = 0; i < n; i++) {
            if (islower(s[i]))
                v.pb(mp(s.substr(i,1), loai::kt));
            else v.pb(mp(s.substr(i,1), loai::sx));
        }
        return v;
    }
    
    int j = 0;
    for(int i = 0; i < n; i++) {
        char c = s[i];
        if (c == ' ') {
            j = i+1;
            continue;
        }
        if (islower(c)) {
            if ((i < n-1 && !islower(s[i+1]))
                || i == n-1) {
                v.push_back(mp(s.substr(j, i-j+1), 0));
                j = i + 1;
            }
        } else if (isupper(c)) {
            if ((i < n-1 && !isupper(s[i+1]))
                || i == n-1) {
                v.push_back(mp(s.substr(j, i-j+1), 1));
                j = i + 1;
            }
        } else {
            v.push_back(mp(s.substr(i, 1), 0));
            j = i + 1;
        }
    }
    
    return v;
}

// inp is trimed
vector<string> convertInputToArray(string & inp) {
    vector<string> v;
    int n = sz(inp);
    
    // special case
    if (LENGTH_CHAR == 1) {
        for(int i = 0; i < n; i++) {
            if (islower(inp[i])) v.pb(inp.substr(i,1));
            else v.pb(inp.substr(i,1));
        }
        return v;
    }
    
    int j = 0;
    for(int i = 0; i < n; i++) {
        char c = inp[i];

        if (islower(c)) {
            if ((i < n-1 && !islower(inp[i+1]))
                || i == n-1) {
                v.push_back(inp.substr(j, i-j+1));
                j = i + 1;
            }
        } else if (isupper(c)) {
            if ((i < n-1 && !isupper(inp[i+1]))
                || i == n-1) {
                v.push_back(inp.substr(j, i-j+1));
                j = i + 1;
            }
        } else {
            v.push_back(inp.substr(i, 1));
            j = i + 1;
        }
    }
    return v;
}

string vectorToString(const vector<pair<string, int>> &vt) {
    string s = "";
    for(auto t : vt) {
        if (t.fi.compare("$") == 0) continue;
        s = s + t.fi;
    }
    return trim(s);
}

void printVector(const vector<pair<string,int>> & vt, int j = 0) {
    for(int i = j; i < sz(vt); i++)
        cout << vt[i].fi;
}

void printVector(const vector<string> & vt, int j = 0, bool space = false) {
    for(int i = j; i < sz(vt); i++) {
        cout << vt[i];
        if (space && i < sz(vt)-1) cout << ' ';
    }
}

void printSpace(const int & n) {
    for(int i = 0; i < n; i++)
        cout << ' ';
}

void printTapSuyDanArr(TapSuyDanArr & tapSuyDanArr) {
    for(auto it : tapSuyDanArr) {
        for(auto it2 : it.se) {
            cout << '[' << it.fi << "] - ";
            for(auto it3 : it2)
                cout << '[' << it3.fi << ']';
            cout << '\n';
        }
    }
}

void printTapSuyDanArrCnnl(TapSuyDanArrCnnl & tapSuyDanArrCnnl) {
    for(auto it : tapSuyDanArrCnnl) {
        for(auto it2 : it.se) {
            cout << '[' << it.fi << "] - ";
            for(auto it3 : it2.fi)
                cout << '[' << it3.fi << ']';
            cout << ", " << it2.se << '\n';
        }
    }
}

bool sosanhStringVector(vector<string> v1,
                        vector<string> v2) {
    if (v1.size() != v2.size()) return false;
    
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    
    for(int i = 0; i < v1.size(); i++)
        if (v1[i].compare(v2[i]) != 0) return false;
    
    return true;
}

bool sosanhTapSuyDanArr(TapSuyDanArr & s1, TapSuyDanArr & s2) {
    if (s1.size() != s2.size()) return false;
    
    for(auto it : s1) {
        string vt = it.fi;
        if (s2.count(vt) == 0) return false;
        if (it.se.size() != s2[vt].size()) return false;
        
        vector<string> suydan_str_1;
        vector<string> suydan_str_2;
        for(int i = 0; i < it.se.size(); i++) {
            auto vpArr1 = it.se[i];
            auto vpArr2 = s2[vt][i];
            suydan_str_1.pb(vectorToString(vpArr1));
            suydan_str_2.pb(vectorToString(vpArr2));
        }
        
        if (!sosanhStringVector(suydan_str_1, suydan_str_2))
            return false;
    }
    
    return true;
}

bool sosanhTapSuyDanArrCnnl(TapSuyDanArrCnnl & s1, TapSuyDanArrCnnl & s2) {
    if (s1.size() != s2.size()) return false;
    
    for(auto it : s1) {
        string vt = it.fi;
        if (s2.count(vt) == 0) return false;
        if (it.se.size() != s2[vt].size()) return false;
        
        vector<string> suydan_str_1;
        vector<string> suydan_str_2;
        for(int i = 0; i < it.se.size(); i++) {
            auto vpArr1 = it.se[i];
            auto vpArr2 = s2[vt][i];
            suydan_str_1.pb(vectorToString(vpArr1.first)+vpArr1.se);
            suydan_str_2.pb(vectorToString(vpArr2.first)+vpArr2.se);
        }
        
        if (!sosanhStringVector(suydan_str_1, suydan_str_2))
            return false;
    }
    
    return true;
}

bool isnumber(const string & s) {
    for(int i = 0; i < sz(s); i++)
        if (!isdigit(s[i])) return false;
    return true;
}

void convertInputToMapArray() {
    
    cout << "Input:\n";
    
    string line;
    string inp;
    while (getline(cin, line)) {
        if (line.compare("") == 0) continue;
        line = trim(line);
        
        // phân chia dấu -
        vector<string> v1 = splitAll(line, "-");
        v1[0] = trim(v1[0]);
        v1[1] = trim(v1[1]);
        if (v1[0].compare("x") == 0) {
            inp = v1[1];
            cout << inp << '\n';
            continue;
        }
        suydanArr[v1[0]] = vector<vector<pair<string,int>>>();
        suydanthuan[v1[0]] = vector<string>();
        
        cout << line << '\n';
        
        // phân chia dấu |
        vector<string> v2 = splitAll(v1[1], "|");
        for(auto s : v2) {
            string vp = trim(s);
            suydanArr[v1[0]].push_back(convertRightToArray(vp));
            suydanthuan[v1[0]].push_back(vp);
            suydannguoc[vp] = v1[0];
        }
    }
    inpV = convertInputToArray(inp);
    
    /* Debug */
    cout << "\nConvert to map array\n";
    printTapSuyDanArr(suydanArr);
    for(auto it : inpV)
        cout << '[' << it << ']';
    cout << '\n';
    /* Debug ending */
}

#endif
