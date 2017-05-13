#ifndef __simplelr__
#define __simplelr__

#include "mhead.h"
#include "utils.h"

string LAUNCHING;

TapSuyDanArr vpGiaTo;
vector<ThucThe> I;
map<pair<int, string>, int> gotoClosureTable;
map<int, pair<int, string>> gotoClosureTable_reversed; // for debug
map<pair<int, string>, string> action_tb;
map<pair<int, string>, int> goto_tb;
map<string, set<string>> follows;

bool notContain(const string & vt,
                const string & vp,
                TapSuyDanArr & closureSet) {
    for(auto vpArr : closureSet[vt]) {
        string vpStr = vectorToString(vpArr);
        if (vpStr.compare(vp) == 0) return false;
    }
    return true;
}

void add(TapSuyDanArr & closureSet,
         string vt, vector<pair<string,int>> vpArr) {
    
    if (notContain(vt, vectorToString(vpArr), closureSet)) {
        closureSet[vt].pb(vpArr);
        
        for(int i = 1; i < vpArr.size(); i++) {
            string pkt = vpArr[i-1].fi;
            string ckt = vpArr[i].fi;
            int ctype = vpArr[i].se;
            if (pkt.compare(".") == 0 && ctype == loai::sx) {
                
                for(auto vpArr2 : vpGiaTo[ckt]) {
                    auto t = vpArr2;
                    t.insert(t.begin(), mp(".", loai::kt));
//                    string vpStr = vectorToString(vpArr2);
//                    vpStr = '.' + vpStr;
                    
//                    add(closureSet, ckt, convertRightToArray(vpStr));
                    add(closureSet, ckt, t);
                }
            }
        }
    }
}

TapSuyDanArr closure(TapSuyDanArr tapSuyDanArr) {
    TapSuyDanArr res;
    
    for(auto _ : tapSuyDanArr) {
        string vt = _.fi;
        for(auto vpArr : tapSuyDanArr[vt])
            add(res, vt, vpArr);
    }
        
    return res;
}

// -1 : true
// 0-n: false
int notContain(TapSuyDanArr & param) {
    for(int i = 0; i < I.size(); i++)
        if (sosanhTapSuyDanArr(param, I[i].fi))
            return i;
    return -1;
}

void buildArtifactFrom(int _i) {
    
    ThucThe tti = I[_i];
//    TapSuyDanArr _suydanArr = tti.se;
    map<string, TapSuyDanArr> params;
    
    for(auto _ : tti.se) {
        string vt = _.fi;
        for(auto vpArr : _.se) {
            
            for(int i = 0; i < vpArr.size()-1; i++) {
                string ckt = vpArr[i].fi;
                string nkt = vpArr[i+1].fi;
                if (ckt.compare(".") == 0) {
                    auto vpArr_clone (vpArr);
                    
                    // swap
                    swap(vpArr_clone[i], vpArr_clone[i+1]);
                    
                    if (notContain(vt, vectorToString(vpArr_clone), params[nkt]))
                        params[nkt][vt].pb(vpArr_clone);
                    break;
                }
            }
        }
    }
    
    for(auto _ : params) {
        int i = notContain(_.se);
        if (i == -1) {
            I.pb(mp(_.se, closure(_.se)));
            gotoClosureTable[mp(_i, _.fi)] = (int)I.size() - 1;
            gotoClosureTable_reversed[(int)I.size()-1] = mp(_i, _.fi);
        } else {
            gotoClosureTable[mp(_i, _.fi)] = i;
//            gotoClosureTable_reversed[i] = mp(_i, _.fi);
        }
    }
}

void computeLR0() {
    
    vpGiaTo = suydanArr;
    vpGiaTo[LAUNCHING + "'"].pb(convertRightToArray(LAUNCHING));
    
    /* Debug */
    cout << "\nVan pham gia to\n";
    for(auto it : vpGiaTo) {
        for(auto it2 : vpGiaTo[it.fi]) {
            cout << '[' << it.fi << "] - ";
            for(auto it3 : it2)
                cout << '[' << it3.fi << ']';
            cout << '\n';
        }
    }
    /* Debug ending */
    
    ThucThe i0;
    TapSuyDanArr & param0 = i0.fi;
    TapSuyDanArr & closure0 = i0.se;
    
    param0[LAUNCHING + "'"].pb(convertRightToArray("." + LAUNCHING));
    closure0 = closure(param0);
    I.pb(i0);
    
    
    int j = 0;
    while(j<I.size()) {
        /* Debug */
        if (gotoClosureTable_reversed.count(j) != 0)
            printf("\nI%d = goto(%d, %s)\n", j,
                   gotoClosureTable_reversed[j].fi,
                   gotoClosureTable_reversed[j].se.c_str());
        else printf("\nI%d = goto(null)\n", j);
        
        printTapSuyDanArr(I[j].se);
        /* Debug ending */
        
        buildArtifactFrom(j++);
    }
}

void computeRule1() {
    for(int i = 0; i < I.size(); i++) {
        for(auto _ : I[i].se) {
            for(auto vpArr : _.se) {
                for(int j = 1; j < vpArr.size(); j++) {
                    string pkt = vpArr[j-1].fi;
                    string ckt = vpArr[j].fi;
                    int ctype = vpArr[j].se;
                    if (pkt.compare(".") == 0 && ctype == loai::kt
                        && gotoClosureTable[mp(i,ckt)] != 0) {
                        action_tb[mp(i,ckt)] =
                        "S" + to_string(gotoClosureTable[mp(i,ckt)]);
                        break;
                    }
                }
            }
        }
    }
}

void computeRule2() {
    for(int i = 0; i < I.size(); i++) {
        for(auto _ : I[i].se) {
            for(auto vpArr : _.se) {
                for(int j = 1; j < vpArr.size(); j++) {
                    string pkt = vpArr[j-1].fi;
                    string ckt = vpArr[j].fi;
                    int ctype = vpArr[j].se;
                    if (pkt.compare(".") == 0 && ctype == loai::sx
                        && gotoClosureTable[mp(i,ckt)] != 0) {
                        goto_tb[mp(i,ckt)] = gotoClosureTable[mp(i,ckt)];
                        break;
                    }
                }
            }
        }
    }
}

void computeRule3() {
    for(int i = 0; i < I.size(); i++) {
        for(auto _ : I[i].se) {
            for(auto vpArr : _.se) {
                string vt = _.fi;
                string vp = vectorToString(vpArr);
                
                if (vt.compare(LAUNCHING + "'") == 0
                    && vp.compare(LAUNCHING + ".") == 0) {
                    action_tb[mp(i,"$")] = "accept";
                    return;
                }
            }
        }
    }
}

//void follow(const string & S, const string & A, set<string> & follows) {
//    for(auto vpArr : suydanArr[S]) {
//        for(int i = 0; i < vpArr.size() - 1; i++) {
//            string ckt = vpArr[i].fi;
//            string nkt = vpArr[i+1].fi;
//            int ctype = vpArr[i].se;
//            int ntype = vpArr[i+1].se;
//            
//            if (ckt.compare(A) == 0 && ntype == loai::kt)
//                if (ntype == loai::kt) follows.insert(nkt);
//            
//            if (ntype == loai::sx)
//                follow(ckt, A, follows);
//        }
//        if (vpArr.back().fi.compare(A) == 0)
//            follows.insert("$");
//    }
//}

void computeRule4() {
    for(int i = 0; i < I.size(); i++) {
        for(auto _ : I[i].se) {
            for(auto vpArr : _.se) {
                string vt = _.fi;
                string vp = vectorToString(vpArr);
                if (vt.compare(LAUNCHING+"'") != 0
                    && vp.back() == '.') {

                    for(string fl : follows[vt])
                        action_tb[mp(i,fl)] = 'R' + vp.substr(0, vp.size()-1);
                    
//                    cout << "follow(" << vt << "): ";
//                    for(string fl : follows) cout << fl << ' ';
//                    cout << '\n';
                }
            }
        }
    }
}

void buildSLRTable() {
    computeRule1();
    computeRule2();
    computeRule3();
    computeRule4();
    
    /* Debug */
    cout << "\nAction table\n";
    for(auto _ : action_tb)
        cout << _.fi.fi << ' ' << _.fi.se << ' ' << _.se << '\n';
    /* Debug ending */
    
    /* Debug */
    cout << "\nGoto table\n";
    for(auto _ : goto_tb)
        cout << _.fi.fi << ' ' << _.fi.se << ' ' << _.se << '\n';
    cout << '\n';
    /* Debug ending */
}

string getAction(int i, const string & x) {
    if (action_tb.count(mp(i,x)) == 0) return "";
    return action_tb[mp(i,x)];
}

void push_stack(vector<string> & st, string s) {
    if (sz(st) == 0) st.pb(s);
    else if (isnumber(s)) st.pb(s);
    else {
        string t = st.back();
        if (isnumber(t)) st.pb(s);
        else {
            st.pop_back();
            t += s;
            st.pb(t);
        }
    }
}

//void firstOf(const pair<string, int> & B, set<string> & s, set<pair<string,string>> & used) {
//    if (B.se == loai::kt) { s.insert(B.fi); return; }
//    for(auto vp : suydanArr[B.fi]) {
//        string vpStr = vectorToString(vp);
//        if (used.count(mp(B.fi, vpStr)) > 0) continue;
//        used.insert(mp(B.fi, vpStr));
//        auto y = vp.front();
//        firstOf(y, s, used);
//    }
//}

void computeFollow(const string & B) {
    if (follows.count(B) > 0 && B.compare(LAUNCHING) != 0) return;
    
    for(auto _ : suydanArr) {
        string A = _.fi;
        for(auto vpArr : _.se) {
            if (A.compare(B) != 0 && vpArr.back().fi.compare(B) == 0) {
                computeFollow(A);
                for(string flA : follows[A])
                    follows[B].insert(flA);
            }
            
            for(int i = 0; i < sz(vpArr) - 1; i++) {
                string ckt = vpArr[i].fi;
                string nkt = vpArr[i+1].fi;
                int ntype = vpArr[i+1].se;
                if (ckt.compare(B) == 0 && ntype == loai::kt)
                    follows[B].insert(nkt);
            }
        }
    }
}

void computeFirstFollow() {

    // follow
    follows[LAUNCHING].insert("$");
    for(auto _ : suydanArr)
        computeFollow(_.fi);
    
    /* debug */
    cout << "\nFollow\n";
    for(auto _ :follows) {
        cout << _.fi << ": ";
        for(auto _2 : _.se) cout << _2 << ' ';
        cout << '\n';
    }
    /* debug ending */
}


bool checkAcceptance() {
    
    cout << "\nDetail steps\n";
    
    bool kq = true;
    vector<string> st;
    push_stack(st, "$");
    push_stack(st, "0");
    inpV.push_back("$");
    int j = 0;
    int step = 0;
    while(1) {
        
        // push space to stack vt
        while(inpV[j].compare(" ") == 0) {
            j++;
            num_gap_space_0++;
        }
//            push_stack(st, inpV[j++]);
        
        /* Debug */
        cout << step << '.';
        if (step < 10) printSpace(2);
        else if (step < 100) printSpace(1);
        printVector(st,0,true);
//        num_gap_space_0 -= (sz(st) - 1);
        printSpace(num_gap_space_0 - sz(st) + 1);
        printVector(inpV, j);
        step++;
        /* End debug */
        
        // now inpV[j] != space
        int i = stoi(st.back());
        string x = inpV[j];
        
        // compare x ~ inpV[j]
        string hdong = getAction(i,x);
        
        /* Debug */
        printSpace(num_gap_space_1);
        printSpace(num_gap_space_2-sz(to_string(i))); cout << to_string(i);
        cout << ' ' << hdong << ' ';
        cout << inpV[j]; printSpace(num_gap_space_2-sz(inpV[j]));
        /* Debug ending */
        
        if (hdong.compare("") == 0) {
            printSpace(num_gap_space_1);
            cout << "Rejected!\n";
            kq = false;
            break;
        } else if (hdong.compare("accept") == 0) {
            printSpace(num_gap_space_1);
            cout << "Accepted!\n";
            break;
        } else if (hdong[0] == 'S') {
            push_stack(st, inpV[j++]);
            push_stack(st, hdong.substr(1, hdong.size()-1));
            num_gap_space_0 -= (sz(hdong)-1);
            printSpace(num_gap_space_1);
            cout << "D/c\n";
        } else if (hdong[0] == 'R') {
            string vp = hdong.substr(1, hdong.size()-1);
            string vt = suydannguoc[vp];
            auto vpArr = convertRightToArray(vp);
            int cnt = 1;
            while(cnt <= 2*sz(vpArr)) {
                num_gap_space_0 += sz(st.back());
                st.pop_back();
                cnt++;
            }
            int i_minus_r = stoi(st.back());
            push_stack(st, vt);
            push_stack(st, to_string(goto_tb[mp(i_minus_r, vt)]));
            num_gap_space_0 -= (sz(vt) + sz(to_string(goto_tb[mp(i_minus_r, vt)])));
            cout << '\n';
        }
    }
    
    cout << '\n';
    
    return kq;

}

void entryPoint(string _launching) {
    LAUNCHING = _launching;
    
    convertInputToMapArray();
    
    computeLR0();
    computeFirstFollow();
    buildSLRTable();
    num_gap_space_0 = 30;
    if (checkAcceptance()) cout << "YES";
    else cout << "NO";
}

#endif 
