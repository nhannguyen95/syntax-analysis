#ifndef __thutuyeu__
#define __thutuyeu__

/*
 2. Phuong phap thu tu yeu (p.149): inp3, inp4
 
 Usage: after reading input
    computeRelationship();
    buildSRTable();
    if (checkAcceptance()) cout << "YES";
    else cout << "NO";
 */

#include "mhead.h"

// alpha - xy - beta
void computeRule1() {
    for(auto it : suydanArr) {
        auto vps = it.se;
        for(auto vp : vps) {
            if (sz(vp) <= 1) continue;
            
            for(int i = 1; i < sz(vp); i++) {
                auto cur = vp[i];
                auto pre = vp[i-1];
                
                if (cur.se == loai::kt) {
                    if (quanhe.count(mp(pre.fi,cur.fi)) != 0) {
                        if (quanhe[mp(pre.fi,cur.fi)] != '=') exit(1);
                        else continue;
                    }
                    quanhe[mp(pre.fi, cur.fi)] = '=';
                    //                    quanhe[mp(cur.fi, pre.fi)] = '=';
                }
                
                else if (cur.se == loai::sx) {
                    if (quanhe.count(mp(pre.fi,cur.fi)) != 0) {
                        if (quanhe[mp(pre.fi,cur.fi)] != '<') exit(1);
                        else continue;
                    }
                    quanhe[mp(pre.fi,cur.fi)] = '<';
                    //                    quanhe[mp(cur.fi,pre.fi)] = '>';
                }
            }
        }
    }
}

void computeRule2_ByRec(const string & a, const string & B) {
    for(auto vp : suydanArr[B]) {
        auto dau = vp[0];
        
        if (quanhe.count(mp(a, dau.fi)) != 0) {
            if (quanhe[mp(a, dau.fi)] != '<') exit(1);
            else continue;
        }
        
        quanhe[mp(a, dau.fi)] = '<';
        //        quanhe[mp(dau.fi, a)] = '>';
        
        if (dau.se == loai::sx) computeRule2_ByRec(a, dau.fi);
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
                
                if (!(cur.se == loai::sx)) continue;
                computeRule2_ByRec(pre.fi, cur.fi);
            }
        }
    }
}

void findAllLastOf(const pair<string, int> & A, set<string> & s, set<pair<string,string>> & used) {
    if (A.se == loai::kt) return;
    for(auto vp : suydanArr[A.fi]) {
        string vpStr = vectorToString(vp);
        if (used.count(mp(A.fi, vpStr)) > 0) continue;
        used.insert(mp(A.fi, vpStr));
        auto x = vp.back();
        s.insert(x.fi);
        findAllLastOf(x, s, used);
    }
}

void findAllFirstOf(const pair<string, int> & B, set<string> & s, set<pair<string,string>> & used) {
    if (B.se == loai::kt) { s.insert(B.fi); return; }
    for(auto vp : suydanArr[B.fi]) {
        string vpStr = vectorToString(vp);
        if (used.count(mp(B.fi, vpStr)) > 0) continue;
        used.insert(mp(B.fi, vpStr));
        auto y = vp.front();
        s.insert(y.fi);
        findAllFirstOf(y, s, used);
    }
}

void computeRule3() {
    for(auto it : suydanArr) {
        auto vps = it.se;
        for(auto vp : vps) {
            if (sz(vp) <= 1) continue;
            
            for(int i = 1; i < sz(vp); i++) {
                auto pre = vp[i-1];
                auto cur = vp[i];
                
                if (!(pre.se == loai::sx)) continue;
                
                // find all last of pre
                set<string> allLastOfPre;
                set<pair<string,string>> used;
                findAllLastOf(pre, allLastOfPre, used);
                
                // find all first of cur
                set<string> allFirstOfCur;
                used.clear();
                findAllFirstOf(cur, allFirstOfCur, used);
                
                // pre > cur
                for(auto x : allLastOfPre)
                    for(auto y : allFirstOfCur) {
                        if (x.compare(y)==0) continue;
                        
                        if (quanhe.count(mp(x, y)) != 0) {
                            if (quanhe[mp(x, y)] != '>') exit(1);
                            else continue;
                        }
                        
                        quanhe[mp(x, y)] = '>';
                        //                        quanhe[mp(y, x)] = '<';
                    }
            }
        }
    }
}

void computeRule41_ByRec(const string & vt) {
    for(auto vp : suydanArr[vt]) {
        auto n = sz(vp);
        auto last = vp[n-1];
        if (quanhe.count(mp("$", last.fi)) != 0) {
            if (quanhe[mp("$", last.fi)] != '<') exit(1);
            else continue;
        }
        //        quanhe[mp("$", last.fi)] = '<';
        quanhe[mp(last.fi, "$")] = '>';
        
        if (last.se == loai::sx) computeRule41_ByRec(last.fi);
    }
}

void computeRule42_ByRec(const string & vt) {
    for(auto vp : suydanArr[vt]) {
        auto first = vp[0];
        if (quanhe.count(mp("$", first.fi)) != 0) {
            if (quanhe[mp("$", first.fi)] != '<') exit(1);
            else continue;
        }
        //        quanhe[mp("$", first.fi)] = '<';
        quanhe[mp(first.fi, "$")] = '>';
        
        if (first.se == loai::sx) computeRule42_ByRec(first.fi);
    }
}

void computeRule4() {
    computeRule41_ByRec("S");
    computeRule42_ByRec("S");
}

void computeRelationship() {
    
    computeRule1();
    computeRule2();
    computeRule3();
    computeRule4();
    
    /* Debug */
    cout << '\n';
    cout << "Compute relationship\n";
    for(auto it : quanhe) {
        cout << '[' << it.fi.fi << "] [" << it.fi.se << "] " << it.se << '\n';
    }
    /* Debug ending */
}

map<pair<string, string>, string> SRTable;
void buildSRTable() {
    for(auto qhe : quanhe) {
        string x = qhe.fi.fi;
        string y = qhe.fi.se;
        if (qhe.se == '<' || qhe.se == '=') {
            SRTable[mp(x,y)] = "S";
            if (qhe.se == '<') SRTable[mp(y,x)] = "R";
        } else if (qhe.se == '>') {
            SRTable[mp(x,y)] = "R";
            SRTable[mp(y,x)] = "S";
        }
    }
    SRTable[mp("S","$")] = "R*";
    //    SRTable[mp("$","S")] = "R*";
    
    /* Debug */
    cout << '\n';
    cout << "SR Table\n";
    for(auto p : SRTable) {
        cout << p.fi.fi << ' ' << p.fi.se << ' ' << p.se << '\n';
    }
    /* Debug ending */
}

string getRel(const string & a, const string & b) {
    auto p = mp(a, b);
    if (SRTable.count(p) == 0) return "?";
    return SRTable[p];
}

string laykihieukhacrongodinhstack(const vector<string> & st) {
    for(int i = st.size()-1;; i--)
        if (st[i].compare(" ") != 0) return st[i];
}

pair<string, int> layvephaidainhatodinhstack(const vector<string> & st, int & nSp) {
    pair<string, int> ans;
    ans.fi = "";
    ans.se = -1;
    
    int i = st.size()-1;
    string s = "";
    while(st[i].compare(" ") == 0) { i--; nSp++; }
    for(;i >= 0; i--) {
        s = st[i] + s;
        if (suydannguoc.count(s)) {
            ans.fi = s;
            ans.se = i;
        }
    }
    
    num_gap_space_0 += (sz(ans.fi) - sz(suydannguoc[ans.fi]));
    
    return ans;
}

bool checkAcceptance() {
    
    cout << "\nDetail steps\n";
    
    bool kq = true;
    vector<string> st; st.pb("$");
    inpV.push_back("$");
    int j = 0;
    int step = 0;
    while(1) {
        
        // push space to stack vt
        while(inpV[j].compare(" ") == 0)
            st.pb(inpV[j++]);
        
        /* Debug */
        cout << step << '.';
        if (step < 10) printSpace(2);
        else if (step < 100) printSpace(1);
        printVector(st);
        printSpace(num_gap_space_0);
        printVector(inpV, j);
        step++;
        /* End debug */
        
        // now inpV[j] != space
        string x = laykihieukhacrongodinhstack(st);
        
        // compare x ~ inpV[j]
        string qhe = getRel(x, inpV[j]);
        
        /* Debug */
        printSpace(num_gap_space_1);
        printSpace(num_gap_space_2-sz(x)); cout << x;
        cout << ' ' << qhe << ' ';
        cout << inpV[j]; printSpace(num_gap_space_2-sz(inpV[j]));
        /* Debug ending */
        
        if (qhe.compare("R*") == 0) {
            printSpace(num_gap_space_1);
            cout << "Accepted!\n";
            break;
        } else if (qhe.compare("?") == 0) {
            printSpace(num_gap_space_1);
            cout << "Rejected!\n";
            kq = false;
            break;
        } else if (qhe.compare("S") == 0) {
            st.pb(inpV[j++]);
            printSpace(num_gap_space_1);
            cout << "D/c\n";
        } else if (qhe.compare("R") == 0) {
            int nSp = 0;
            pair<string, int> p = layvephaidainhatodinhstack(st, nSp);
            if (p.se == -1) {
                printSpace(num_gap_space_1);
                cout << "Rejected!\n";
                kq = false;
                break;
            }
            else {
                
                while(st.size() > p.se) st.pop_back();
                st.pb(suydannguoc[p.fi]);
                while(nSp--) st.pb(" ");
                
                printSpace(num_gap_space_1);
                cout << "R/g " << suydannguoc[p.fi] << '-' << p.fi << '\n';
            }
        }
    }
    
    cout << '\n';
    
    return kq;
}

void entryPoint() {
    convertInputToMapArray();
    computeRelationship();
    buildSRTable();
    if (checkAcceptance()) cout << "YES";
    else cout << "NO";
}


#endif
