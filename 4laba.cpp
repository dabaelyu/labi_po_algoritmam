// 1 ZAZDANIE --------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 1. Чтение входных данных
    int n, m;
    cin >> n >> m;

    // 2. Инициализация таблицы динамического программирования (DP)
    // dp[i][j] = 1, если позиция (i, j) выигрышна для текущего игрока
    // dp[i][j] = 0, если позиция (i, j) проигрышна для текущего игрока
    // Используем -1 для обозначения "еще не вычислено"
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    // 3. Установка базового случая
    // Если обе кучи пусты (0, 0), текущий игрок проигрывает
    dp[0][0] = 0;

    // 4. Заполнение таблицы DP
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            // Если позиция уже вычислена, пропускаем
            if (dp[i][j] != -1) continue;

            // Перебираем возможные ходы из позиции (i, j)
            bool can_lose_opponent = false;

            // Ход 1: Взять 1 камень из первой кучи -> (i-1, j)
            if (i > 0 && dp[i - 1][j] == 0) can_lose_opponent = true;
            // Ход 2: Взять 1 камень из второй кучи -> (i, j-1)
            if (j > 0 && dp[i][j - 1] == 0) can_lose_opponent = true;
            // Ход 3: Взять по 1 камню из обеих куч -> (i-1, j-1)
            if (i > 0 && j > 0 && dp[i - 1][j - 1] == 0) can_lose_opponent = true;

            // Если существует ход, приводящий оппонента в проигрышную позицию,
            // то текущая позиция (i, j) выигрышна.
            dp[i][j] = can_lose_opponent ? 1 : 0;
        }
    }

    // 5. Определение и вывод результата
    if (dp[n][m] == 1) {
        cout << "Win" << endl;
    } else {
        cout << "Lose" << endl;
    }

    // 6. Вывод таблицы DP
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            cout << dp[i][j];
            if (j < m) cout << " ";
        }
        cout << endl;
    }
    return 0;
}

// 2 ZAZDANIE --------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 1. Чтение входных данных
    int n, m;
    cin >> n >> m;

    // 2. Инициализация таблицы DP
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    
    // 3. Установка базового случая
    dp[0][0] = 0; // Позиция (0,0) - проигрышная

    // 4. Заполнение таблицы DP
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (dp[i][j] != -1) continue; // Уже вычислено

            bool can_lose_opponent = false;

            // Перебираем все возможные ходы из позиции (i, j)
            // Ход 1: (i-1, j)
            if (i > 0 && dp[i - 1][j] == 0) can_lose_opponent = true;
            // Ход 2: (i, j-1)
            if (j > 0 && dp[i][j - 1] == 0) can_lose_opponent = true;
            // Ход 3: (i-2, j), если i >= 2
            if (i >= 2 && dp[i - 2][j] == 0) can_lose_opponent = true;
            // Ход 4: (i, j-2), если j >= 2
            if (j >= 2 && dp[i][j - 2] == 0) can_lose_opponent = true;
            // Ход 5: (i-1, j-2), если i >= 1 и j >= 2
            if (i >= 1 && j >= 2 && dp[i - 1][j - 2] == 0) can_lose_opponent = true;
            // Ход 6: (i-2, j-1), если i >= 2 и j >= 1
            if (i >= 2 && j >= 1 && dp[i - 2][j - 1] == 0) can_lose_opponent = true;

            dp[i][j] = can_lose_opponent ? 1 : 0;
        }
    }

    // 5. Определение и вывод результата
    if (dp[n][m] == 1) {
        cout << "Win" << endl;
    } else {
        cout << "Lose" << endl;
    }

    // 6. Дополнительный вывод (если n, m <= 10)
    if (n <= 10 && m <= 10) {
        int winning_moves = 0;

        // Подсчет выигрышных ходов из начальной позиции (n, m)
        if (n > 0 && dp[n - 1][m] == 0) winning_moves++;
        if (m > 0 && dp[n][m - 1] == 0) winning_moves++;
        if (n >= 2 && dp[n - 2][m] == 0) winning_moves++;
        if (m >= 2 && dp[n][m - 2] == 0) winning_moves++;
        if (n > 0 && m >= 2 && dp[n - 1][m - 2] == 0) winning_moves++;
        if (n >= 2 && m > 0 && dp[n - 2][m - 1] == 0) winning_moves++;

        cout << winning_moves << endl;

        // Вывод таблицы DP
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                cout << dp[i][j];
                if (j < m) cout << " ";
            }
            cout << endl;
        }
    }
    return 0;
}

// 3 ZAZDANIE --------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    // 1. Чтение входных данных
    int N, K;
    cin >> N >> K;

    vector<int> x(N);
    for (int i = 0; i < N; i++) {
        cin >> x[i];
    }

    // 2. Сортировка координат
    // Сортируем, чтобы "ближайший слева" означал x[i-1] для x[i]
    sort(x.begin(), x.end());

    // 3. Инициализация DP
    // dp[i] - минимальная стоимость подключения первых i+1 компьютеров (0..i)
    vector<long long> dp(N, LLONG_MAX);

    // 4. Установка базового случая
    // Первый (0-й) компьютер можно подключить только напрямую
    dp[0] = K;

    // 5. Заполнение таблицы DP
    for (int i = 1; i < N; i++) {
        // Вариант 1: i-й компьютер подключается напрямую
        // Стоимость = (стоимость подключения первых i) + K
        dp[i] = dp[i - 1] + K;

        // Вариант 2: i-й компьютер подключается через кабель
        // Это означает, что он является частью "цепочки" кабелей,
        // начинающейся от какого-то компьютера prev, подключенного напрямую.
        // Перебираем все возможные позиции "базового" подключения prev (от i-1 до 0)
        long long cableCost = 0;
        for (int prev = i - 1; prev >= 0; prev--) {
            // Вычисляем стоимость цепочки кабелей от prev+1 до i
            // Каждый компьютер k (где prev+1 <= k <= i) подключается к k-1
            cableCost = 0;
            for (int k = prev + 1; k <= i; k++) {
                if (k > 0) { // Убедимся, что k-1 существует
                    long long dist = x[k] - x[k - 1];
                    cableCost += dist * dist;
                }
            }

            // Вычисляем общую стоимость для стратегии:
            // - Подключить первые prev компьютеров (стоимость dp[prev-1])
            // - Подключить prev-й компьютер напрямую (стоимость K)
            // - Подключить остальные от prev+1 до i цепочкой (стоимость cableCost)
            long long prevCost = (prev == 0) ? K : dp[prev - 1] + K;
            
            // Обновляем dp[i], если текущая стратегия дешевле
            dp[i] = min(dp[i], prevCost + cableCost);
        }

        // Вариант 3: Все компьютеры от 0 до i подключены одной цепочкой
        // Только 0-й подключается напрямую, остальные через кабели
        cableCost = 0;
        for (int k = 1; k <= i; k++) {
            long long dist = x[k] - x[k - 1];
            cableCost += dist * dist;
        }
        // Обновляем dp[i], если эта стратегия дешевле
        dp[i] = min(dp[i], K + cableCost);
    }

    // 6. Вывод результата
    // dp[N-1] содержит минимальную стоимость подключения всех N компьютеров
    cout << dp[N - 1] << endl;

    return 0;
}

// 4 ZAZDANIE --------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

int main() {
    // 1. Чтение входных данных
    int N;
    cin >> N;

    // 2. Проверка базовых случаев
    if (N == 1) {
        cout << 3 << endl; // A, B, C
        return 0;
    }
    if (N == 2) {
        cout << 9 << endl; // AA, AB, AC, BA, BB, BC, CA, CB, CC
        return 0;
    }

    // 3. Инициализация DP
    // Используем 2D массивы для оптимизации памяти, т.к. dp[i] зависит только от dp[i-1]
    // dp[j][k] - количество строк длины i, где j - тип (A/B/C) предпоследнего символа, k - типа последнего
    vector<vector<long long>> prev(3, vector<long long>(3, 1)); // prev = dp[2]
    vector<vector<long long>> curr(3, vector<long long>(3));

    // 4. Цикл по длине строки от 3 до N
    for (int i = 3; i <= N; ++i) {
        // Обнуляем текущий слой
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                curr[j][k] = 0;
            }
        }

        // Заполняем текущий слой dp[i] на основе предыдущего dp[i-1]
        for (int last = 0; last < 3; ++last) { // last = тип символа на позиции i
            for (int prev_last = 0; prev_last < 3; ++prev_last) { // prev_last = тип символа на позиции i-1
                // Перебираем тип символа на позиции i-2 (prev_prev)
                for (int prev_prev = 0; prev_prev < 3; ++prev_prev) {
                    // Проверяем правило: первый и третий в тройке не должны совпадать
                    // Тройка: prev_prev (на позиции i-2), prev_last (i-1), last (i)
                    // Условие: prev_prev != last
                    if (prev_prev != last) {
                        // Добавляем количество строк длины i-1, оканчивающихся на prev_prev, prev_last
                        // к количеству строк длины i, оканчивающихся на prev_last, last
                        curr[prev_last][last] = (curr[prev_last][last] + prev[prev_prev][prev_last]) % MOD;
                    }
                }
            }
        }
        // Переходим к следующей итерации, prev становится curr
        prev = curr;
    }

    // 5. Вычисление итогового результата
    // Суммируем все dp[N][j][k]
    long long res = 0;
    for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) {
            res = (res + prev[j][k]) % MOD;
        }
    }

    // 6. Вывод результата
    cout << res << endl;
    return 0;
}
