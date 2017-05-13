/*
 1. Phuong phap uu tien toan tu (p.128): inp1, inp2, inp3
 
 Usage: after reading input, add:
    computePriority();
    if (checkAcceptance()) cout << "YES";
    else cout << "NO";
 */

#ifndef __uutientoantu__
#define __uutientoantu__

#include "mhead.h"

void computeRule1() {
    
    for(auto it : suydanArr) {
        auto vps = it.se;
        for(auto vp : vps) {
            if (sz(vp) <= 1) continue;
            
            for(int i = 1; i < sz(vp); i++) {
                auto cur = vp[i];
                auto pre = vp[i-1];
                
                if (cur.se == loai::kt && pre.se == loai::kt) {
                    if (quanhe.count(mp(cur.fi, pre.fi)) != 0) {
                        if  (quanhe[mp(cur.fi, pre.fi)] != '=') exit(1);
                        else continue;
                    }
                    
                    quanhe[mp(cur.fi, pre.fi)] = '=';
                    quanhe[mp(pre.fi, cur.fi)] = '=';
                }
                
                if (i < 2) continue;
                
                auto pre2 = vp[i-2];
                if (cur.se == loai::kt && pre.se == loai::sx && pre2.se == loai::kt) {
                    if (quanhe.count(mp(cur.fi, pre2.fi)) != 0) {
                        if (quanhe[mp(cur.fi, pre2.fi)] != '=') exit(1);
                        else continue;
                    }
                    
                    quanhe[mp(cur.fi, pre2.fi)] = '=';
                    quanhe[mp(pre2.fi, cur.fi)] = '=';
                }
            }
        }
    }
}

void computeRule2_ByRec(const string & a, const string & B) {
    for(auto vp : suydanArr[B]) {
        auto dau = vp[0];
        if (dau.se == loai::kt) {
            if (quanhe.count(mp(a, dau.fi)) != 0) {
                if (quanhe[mp(a, dau.fi)] != '<') exit(1);
                else continue;
            }
            
            quanhe[mp(a, dau.fi)] = '<';
            quanhe[mp(dau.fi, a)] = '>';
        } else if (dau.se == loai::sx) {
            computeRule2_ByRec(a, dau.fi);
            
            if (sz(vp) < 2) continue;
            auto next = vp[1];
            if (next.se == loai::kt) {
                if (quanhe.count(mp(a, next.fi)) != 0) {
                    if (quanhe[mp(a, next.fi)] != '<') exit(1);
                    else continue;
                }
                
                quanhe[mp(a, next.fi)] = '<';
                quanhe[mp(next.fi, a)] = '>';
            }
        }
    }
}

void computeRule2() {
    for(auto it : suydanArr) {
        auto vps = it.se;
        for(auto vp : vps) {
            if (sz(vp) <= 1) continue;
            
            for(int i = 1; i < sz(vp); i++) {
                auto cur = vp[i];
                auto pre = vp[i-1];
                
                if (!(pre.se == loai::kt && cur.se == loai::sx)) continue;
                computeRule2_ByRec(pre.fi, cur.fi);
            }
        }
    }
}

void computeRule3_ByRec(const string & A, const string & b) {
    for(auto vp : suydanArr[A]) {
        auto n = sz(vp);
        auto cuoi = vp[n-1];
        if (cuoi.se == loai::kt) {
            if (quanhe.count(mp(b, cuoi.fi)) != 0) {
                if (quanhe[mp(b, cuoi.fi)] != '<') exit(1);
                else continue;
            }
            
            quanhe[mp(b, cuoi.fi)] = '<';
            quanhe[mp(cuoi.fi, b)] = '>';
        } else if (cuoi.se == loai::sx) {
            computeRule3_ByRec(cuoi.fi, b);
            
            if (n-2 < 0) continue;
            auto pre = vp[n-2];
            if (pre.se == loai::kt) {
                if (quanhe.count(mp(b, pre.fi)) != 0) {
                    if (quanhe[mp(b, pre.fi)] != '<') exit(1);
                    else continue;
                }
                
                quanhe[mp(b, pre.fi)] = '<';
                quanhe[mp(pre.fi, b)] = '>';
            }
        }
    }
}

void computeRule3() {
    for(auto it : suydanArr) {
        auto vps = it.se;
        for(auto vp : vps) {
            if (sz(vp) <= 1) continue;
            
            for(int i = 1; i < sz(vp); i++) {
                auto cur = vp[i];
                auto pre = vp[i-1];
                
                if (!(pre.se == loai::sx && cur.se == loai::kt)) continue;
                computeRule3_ByRec(pre.fi, cur.fi);
            }
        }
    }
}

// ya || yaC
void computeRule41_ByRec(const string & vt) {
    for(auto vp : suydanArr[vt]) {
        auto n = sz(vp);
        auto last = vp[n-1];
        if (last.se == loai::kt) {
            if (quanhe.count(mp("$", last.fi)) != 0) {
                if (quanhe[mp("$", last.fi)] != '<') exit(1);
                else continue;
            }
            quanhe[mp("$", last.fi)] = '<';
            quanhe[mp(last.fi, "$")] = '>';
        } else if (last.se == loai::sx) {
            computeRule41_ByRec(last.fi);
            if (n <= 1) continue;
            auto pre = vp[n-2];
            if (pre.se == loai::kt) {
                if (quanhe.count(mp("$", pre.fi)) != 0) {
                    if (quanhe[mp("$", pre.fi)] != '<') exit(1);
                    else continue;
                }
                quanhe[mp("$", pre.fi)] = '<';
                quanhe[mp(pre.fi, "$")] = '>';
            }
        }
    }
}

// ay || Cay
void computeRule42_ByRec(const string & vt) {
    for(auto vp : suydanArr[vt]) {
        auto first = vp[0];
        if (first.se == loai::kt) {
            if (quanhe.count(mp("$", first.fi)) != 0) {
                if (quanhe[mp("$", first.fi)] != '<') exit(1);
                else continue;
            }
            quanhe[mp("$", first.fi)] = '<';
            quanhe[mp(first.fi, "$")] = '>';
        } else if (first.se == loai::sx) {
            computeRule42_ByRec(first.fi);
            if (sz(vp) <= 1) continue;
            auto next = vp[1];
            if (next.se == loai::kt) {
                if (quanhe.count(mp("$", next.fi)) != 0) {
                    if (quanhe[mp("$", next.fi)] != '<') exit(1);
                    else continue;
                }
                quanhe[mp("$", next.fi)] = '<';
                quanhe[mp(next.fi, "$")] = '>';
            }
            
        }
    }
}

void computeRule4() {
    computeRule41_ByRec("S");
    computeRule42_ByRec("S");
}

void computePriority() {
    
    computeRule1();
    computeRule2();
    computeRule3();
    computeRule4();
    
    /* Debug */
    cout << '\n';
    cout << "Compute priority\n";
    for(auto it : quanhe) {
        cout << '[' << it.fi.fi << "] [" << it.fi.se << "] " << it.se << '\n';
    }
    /* Debug ending */
}

string kihieuketthucgandinhstacknhat(const vector<pair<string,int>> & vt) {
    int n = sz(vt);
    for(int i = n-1; i >= 0; i--) {
        auto p = vt[i];
        if (p.fi.compare(" ")!= 0 && p.se == loai::kt)
            return p.fi;
    }
    
    return "$";
}

char getRel(const string & a, const string & b) {
    auto p = mp(a, b);
    if (quanhe.count(p) == 0) return '?';
    return quanhe[p];
}

void rutgonstack(vector<pair<string,int>> &vt) {
    int n = sz(vt);
    int i;
    for(i = n-1; i >= 0; i--) {
        auto p = vt[i];
        if (p.se != loai::kt) continue;
        if (p.fi.compare(" ") == 0) continue;
        
        int j = i - 1;
        while(vt[j].fi.compare(" ") == 0 || vt[j].se != loai::kt) j--;
        
        if (getRel(vt[j].fi, p.fi) == '<') {
            i = j + 1;
            while(vt[i].fi.compare(" ") == 0) i++;
            break;
        }
    }
    
    int cntSpace = 0;
    while(vt[sz(vt)-1].fi.compare(" ") == 0) {
        vt.pop_back();
        cntSpace++;
    }
    
    string s = "";
    while(sz(vt)-1 >= i) {
        s = vt[sz(vt)-1].fi + s;
        vt.pop_back();
    }
    vt.pb(mp(suydannguoc[s], loai::sx));
    for(int j = 0; j < cntSpace; j++)
        vt.pb(mp(" ", loai::kt));
    
    num_gap_space_0 += (sz(s) - sz(suydannguoc[s]));
    
    printSpace(num_gap_space_1);
    cout << "R/g " << suydannguoc[s] << '-' << s << '\n';
}

bool checkAcceptance() {
    
    cout << "\nDetail steps\n";
    
    bool kq = false;
    vector<pair<string,int>> vt; vt.pb(mp("$", loai::kt));
    inpV.push_back("$");
    int j = 0;
    int step = 0;
    while(1) {
        
        /* Debug */
        cout << step << '.';
        if (step < 10) printSpace(2);
        else if (step < 100) printSpace(1);
        printVector(vt);
        printSpace(num_gap_space_0);
        printVector(inpV, j);
        step++;
        /* Debug ending */
        
        
        if (vectorToString(vt).compare("S") == 0 && j==sz(inpV)-1 && inpV[j].compare("$")==0) {
            kq = true;
            printSpace(3*num_gap_space_1+num_gap_space_2-1);
            cout << "Accepted!\n";
            break;
        } else {
            // a & b != " "
            string a = kihieuketthucgandinhstacknhat(vt);
            string b = inpV[j];
            char qhe = getRel(a, b);
            
            /* Debug */
            printSpace(num_gap_space_1);
            printSpace(num_gap_space_2-sz(a)); cout << a;
            cout << ' ' << qhe << ' ';
            cout << b; printSpace(num_gap_space_2-sz(b));
            /* Debug ending */
            
            if (qhe == '>') {
                rutgonstack(vt);
            } else {
                if (qhe == '<' || qhe == '=') {
                    vt.pb(mp(inpV[j++], loai::kt));
                    while(inpV[j].compare(" ") == 0)
                        vt.pb(mp(inpV[j++], loai::kt));
                    
                    /* Debug */
                    printSpace(num_gap_space_1);
                    cout << "D/c\n";
                    /* Debug ending */
                } else {
                    kq = false;
                    printSpace(num_gap_space_1);
                    cout << "Rejected!\n";
                    break;
                }
            }
        }
    }
    
    cout << '\n';
    
    return kq;
}

void entryPoint() {
    convertInputToMapArray();
    computePriority();
    if (checkAcceptance()) cout << "YES";
    else cout << "NO";
}

#endif