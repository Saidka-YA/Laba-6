#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iomanip>

using namespace std;

int N, M;

int encode(vector<vector<int> >& board)
{
    int mask = 0;
    int pos = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (board[i][j] == 1)
            {
                mask |= (1 << pos);
            }

            pos++;
        }
    }
    return mask;
}

vector<vector<int>> decode(int mask)
{
    vector<vector<int>> board(N, vector<int>(M, 0));
    int pos = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            board[i][j] = (mask >> pos) & 1;
            pos++;
        }
    }
    return board;
}

int buildTarget(int edgeVal)
{
    vector<vector<int>> target(N, vector<int>(M, 0));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (i == 0 || i == N-1 || j == 0 || j == M-1)
            {
                target[i][j] = edgeVal;
            }
            else
            {
                target[i][j] = 1 - edgeVal;
            }
        }
    }
    return encode(target);
}

int bfs(int startMask, int targetMask)
{
    if (startMask == targetMask)
    {
        return 0;
    }

    unordered_map<int,int> visited;
    queue<int> q;

    visited[startMask] = 0;
    q.push(startMask);

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        int curDist = visited[cur];

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                for (int d = 0; d < 4; d++)
                {
                    int ni = i + dx[d];
                    int nj = j + dy[d];

                    if (ni < 0 || ni >= N || nj < 0 || nj >= M)
                    {
                        continue;
                    }

                    int pos1 = i  * M + j;
                    int pos2 = ni * M + nj;

                    int newMask = cur ^ (1 << pos1) ^ (1 << pos2);

                    if (newMask == targetMask)
                    {
                        return curDist + 1;
                    }

                    if (visited.count(newMask) == 0)
                    {
                        visited[newMask] = curDist + 1;
                        q.push(newMask);
                    }
                }
            }
        }
    }

    return -1;
}

int main()
{
    cout << "Введите N (от 2 до 4): ";

    while (!(cin >> N) || N < 2 || N > 4)
    {
        cout << "Ошибка: введите от 2 до 4\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Введите N (от 2 до 4): ";
    }

    cout << "Введите M (от 2 до 4): ";

    while (!(cin >> M) || M < 2 || M > 4)
    {
        cout << "Ошибка: введите от 2 до 4\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Введите M (от 2 до 4): ";
    }

    vector<vector<int>> board(N, vector<int>(M, 0));

    cout << "Введите доску (0 и 1):\n";

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            while (!(cin >> board[i][j]) || board[i][j] < 0 || board[i][j] > 1)
            {
                cout << "Ошибка: введите 0 или 1\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
    }

    cout << "\nВведённая доска:\n";

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << setw(3) << board[i][j];
        }
        cout << "\n";
    }

    int startMask = encode(board);
    int bestAnswer = 1000000;

    for (int edgeVal = 0; edgeVal < 2; edgeVal++)
    {
        int targetMask = buildTarget(edgeVal);

        vector<vector<int>> targetBoard = decode(targetMask);

        cout << "\nЦелевая рамка (края=" << edgeVal << ", внутри=" << (1 - edgeVal) << "):\n";

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                cout << setw(3) << targetBoard[i][j];
            }
            cout << "\n";
        }

        int result = bfs(startMask, targetMask);

        if (result == -1)
        {
            cout << "Невозможно достичь.\n";
        }
        else
        {
            cout << "Ходов: " << result << "\n";

            if (result < bestAnswer)
            {
                bestAnswer = result;
            }
        }
    }

    cout << "\n" << setw(30) << left << "Минимальное число ходов:" << bestAnswer << "\n";

    return 0;
}