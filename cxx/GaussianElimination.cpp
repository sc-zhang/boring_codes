#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void disp(vector<vector<double> > A, vector<double> b)
{
    cout << "======calc======\n";
    for (int row = 0; row < A.size(); ++row)
    {
        for (int col = 0; col < A[row].size(); ++col)
        {
            cout << A[row][col] << "\t";
        }
        cout << b[row] << "\n";
    }
}

void disp(vector<double> res)
{
    cout << "=====result=====\n";
    if (res.empty())
    {
        cout << "Cannot solve\n";
    }
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << "\n";
    }
}

vector<double> GaussianElimination(vector<vector<double> > &A, vector<double> &b)
{
    int n = b.size();
    vector<double> res(n);
    for (int col = 0; col < n - 1; ++col)
    {
        double max_v = 0;
        int max_row = 0;
        // search max col value
        for (int row = col; row < n; ++row)
        {
            if (fabs(A[row][col]) > max_v)
            {
                max_v = fabs(A[row][col]);
                max_row = row;
            }
        }
        // swap current row and row with max col value
        if (max_row != col)
        {
            swap(A[max_row], A[col]);
            swap(b[max_row], b[col]);
        }
        if (A[col][col] == 0)
        {
            return res;
        }
        // elimination
        for (int row = col + 1; row < n; ++row)
        {
            double ratio = A[row][col] / A[col][col];
            for (int ncol = col; ncol < n; ++ncol)
            {
                A[row][ncol] -= ratio * A[col][ncol];
            }
            b[row] -= ratio * b[col];
            disp(A, b);
        }
    }
    // back calc
    res[n - 1] = b[n - 1] / A[n - 1][n - 1];
    for (int i = n - 2; i >= 0; --i)
    {
        double dec = 0;
        for (int j = i + 1; j < n; ++j)
        {
            dec += A[i][j] * res[j];
        }
        res[i] = (b[i] - dec) / A[i][i];
    }
    return res;
}

int main()
{
    int n;
    vector<vector<double> > A;
    vector<double> b;
    cin >> n;
    int i = 0;
    double num = 0.0;
    while (i < n)
    {
        vector<double> tmp;
        for (int j = 0; j < n; ++j)
        {
            cin >> num;
            tmp.push_back(num);
        }
        cin >> num;
        b.push_back(num);
        A.push_back(tmp);
        ++i;
    }
    vector<double> res = GaussianElimination(A, b);
    disp(res);
    return 0;
}
