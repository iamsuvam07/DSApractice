class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {

        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        vector<vector<int>> id(m, vector<int>(n, -1));

        int litterCount = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    id[i][j] = litterCount++;
                }
            }
        }

        if (litterCount == 0)
            return 0;

        int masks = 1 << litterCount;
        int fullMask = masks - 1;

        

        auto encode = [&](int r, int c, int e, int mask) {

            return (((r * n + c) * (energy + 1) + e) * masks + mask);
        };

        

int totalStates = m * n * (energy + 1) * masks;

        vector<char> visited(totalStates, 0);

queue<int> q;

        int start = encode(sr, sc, energy, 0);

 q.push(start);
        visited[start] = 1;

 int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};

int moves = 0;

        while (!q.empty()) {

int size = q.size();

     while (size--) {

 int state = q.front();
     q.pop();

  int mask = state % masks;
  state /= masks;

 int e = state % (energy + 1);
 state /= (energy + 1);

  int c = state % n;
 int r = state / n;

 if (mask == fullMask) {
 return moves;
 }

if (e == 0) {
     continue;
                }

 for (int d = 0; d < 4; d++) {

    int nr = r + dr[d];
int nc = c + dc[d];

    if (nr < 0 || nr >= m ||
nc < 0 || nc >= n) {
continue;
      }

   if (classroom[nr][nc] == 'X') {
  continue;
     }

     int ne;
 int newMask = mask;

    if (classroom[nr][nc] == 'R') {
                        ne = energy;
     }
else {
     ne = e - 1;
         }

 if (classroom[nr][nc] == 'L') {

int idx = id[nr][nc];

         newMask |= (1 << idx);
                    }

    int newState = encode(
                        nr,
                        nc,
                        ne,
                        newMask
                    );

                    if (!visited[newState]) {

                        visited[newState] = 1;

                        q.push(newState);
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};