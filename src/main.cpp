#include <bits/stdc++.h>
using namespace std;

static bool is_digit(char c){return c>='0'&&c<='9';}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    {
        ostringstream oss;
        oss << cin.rdbuf();
        s = oss.str();
    }

    // Collect comment contents: block /* */ and line //
    vector<string> comments;
    // Block comments
    for(size_t i=0;i+1<s.size();){
        if(s[i]=='/' && s[i+1]=='*'){
            size_t j = i+2;
            while(j+1<s.size() && !(s[j]=='*' && s[j+1]=='/')) ++j;
            if(j+1<s.size()){
                comments.emplace_back(s.substr(i+2, j-(i+2)));
                i = j+2;
            } else break;
        } else if(s[i]=='/' && s[i+1]=='/'){
            size_t j = i+2;
            while(j<s.size() && s[j]!='\n' && s[j]!='\r') ++j;
            comments.emplace_back(s.substr(i+2, j-(i+2)));
            i = j;
        } else {
            ++i;
        }
    }

    auto extract_with_keywords = [](const string &t)->optional<long long>{
        string low = t;
        for(char &c: low) c = tolower((unsigned char)c);
        const vector<string> keys = {"return value", "ret value", "return:", "ret:", "answer", "output", "ret"};
        for(const string &k: keys){
            size_t p = low.find(k);
            if(p!=string::npos){
                size_t q = p + k.size();
                while(q<low.size() && !(low[q]=='-'||low[q]=='+'||is_digit(low[q]))) ++q;
                bool neg=false; if(q<low.size() && (low[q]=='-'||low[q]=='+')){ neg = (low[q]=='-'); ++q; }
                if(q<low.size() && is_digit(low[q])){
                    long long val=0;
                    while(q<low.size() && is_digit(low[q])){ val = val*10 + (low[q]-'0'); ++q; }
                    return neg? -val : val;
                }
            }
        }
        return nullopt;
    };

    // Try keyworded extraction first
    for(const string &cmt: comments){
        if(auto v = extract_with_keywords(cmt); v.has_value()){ cout << *v; return 0; }
    }

    // Fallback: first integer in any comment
    for(const string &cmt: comments){
        size_t i=0;
        while(i<cmt.size() && !is_digit(cmt[i]) && cmt[i]!='-' && cmt[i]!='+') ++i;
        bool neg=false; if(i<cmt.size() && (cmt[i]=='-'||cmt[i]=='+')){ neg=(cmt[i]=='-'); ++i; }
        if(i<cmt.size() && is_digit(cmt[i])){
            long long val=0;
            while(i<cmt.size() && is_digit(cmt[i])){ val = val*10 + (cmt[i]-'0'); ++i; }
            cout << (neg? -val : val);
            return 0;
        }
    }

    // Last resort: search entire input for an integer
    {
        size_t i=0;
        while(i<s.size() && !is_digit(s[i]) && s[i]!='-' && s[i]!='+') ++i;
        bool neg=false; if(i<s.size() && (s[i]=='-'||s[i]=='+')){ neg=(s[i]=='-'); ++i; }
        if(i<s.size() && is_digit(s[i])){
            long long val=0;
            while(i<s.size() && is_digit(s[i])){ val = val*10 + (s[i]-'0'); ++i; }
            cout << (neg? -val : val);
            return 0;
        }
    }

    cout << 0;
    return 0;
}
