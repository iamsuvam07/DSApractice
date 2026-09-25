class Solution {
public:
    string s;
    int pos = 0;

    set<string> parseExpression() {
        set<string> result = parseTerm();

        while (pos < s.size() && s[pos] == ',') {
            pos++;  // skip ','

            set<string> next = parseTerm();

            result.insert(next.begin(), next.end());
        }

        return result;
    }

    set<string> parseTerm() {
        set<string> result = {""};

        while (pos < s.size() && s[pos] != '}' && s[pos] != ',') {

            set<string> current;

            if (s[pos] == '{') {
                pos++;  

                current = parseExpression();

                pos++;  
            }
            else {
                string temp(1, s[pos]);
                pos++;

                current.insert(temp);
            }

            set<string> next;

            for (const string &a : result) {
                for (const string &b : current) {
                    next.insert(a + b);
                }
            }

            result = next;
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;

        set<string> ans = parseExpression();

        return vector<string>(ans.begin(), ans.end());
    }
};
    