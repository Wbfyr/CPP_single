#include "solute.h"

void solute::add(vector<string> vari, vector<double> coeff)
{
    // 增加矩阵的变元，同时将之前的矩阵的每行增加若干个0
    for (int i = 0; i < vari.size(); i++)
    {
        bool flag = false;
        for (vector<string>::iterator it = vari_table.begin(); it != vari_table.end(); it++)
        {
            if (vari[i] == *it)
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            vari_table.push_back(vari[i]);
            for (int j = 0; j < matrix.size(); j++)
            {
                matrix[j].insert(matrix[j].end()--, 0);
            }
        }
    }
    // 根据变元列表，增加新行
    vector<double> new_row;
    for (auto p : vari_table)
    {
        bool flag = false;
        for (int i = 0; i < vari.size(); i++)
        {
            if (p == vari[i])
            {
                flag = true;
                new_row.push_back(coeff[i]);
                break;
            }
        }
        if (!flag)
        {
            new_row.push_back(0);
        }
    }
    new_row.push_back(coeff[coeff.size() - 1]);
    matrix.push_back(new_row);
}

vector<vector<double>> solute::get_matrix()
{
    return matrix;
}

map<string, double> solute::get_solution()
{
    // 高斯消元，转为上三角
    vector<vector<double>> matrix_copy = matrix;
    int row = matrix.size();
    int line = vari_table.size();
    if (row < line)
    {
        throw runtime_error("error2");
    }
    for (int i = 0; i < line; i++)
    {

        if (matrix_copy[i][i] != 0)
        {
            for (int j = i; j < line + 1; j++)
            {
                matrix_copy[i][j] /= matrix_copy[i][i];
            }
            for (int j = i + 1; j < row; j++)
            {
                if (matrix_copy[j][i] == 0)
                {
                    continue;
                }
                else
                {
                    for (int k = i; k < line + 1; k++)
                    {
                        matrix_copy[j][k] = matrix_copy[j][k] - matrix_copy[j][i] * matrix_copy[i][k];
                    }
                }
            }
        }
        else
        {
            for (int j = i + 1; j < row; j++)
            {
                if (matrix_copy[j][i] != 0)
                {
                    vector<double> temp = matrix_copy[j];
                    matrix_copy[j] = matrix_copy[i];
                    matrix_copy[i] = temp;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < row; i++)
    {
        if (matrix_copy[i][line - 1] == 0)
        {
            if (matrix_copy[i][line] != 0)
            {
                throw runtime_error("error1");
            }
        }
    }
    for (int i = 0; i < line; i++)
    {
        if (matrix_copy[i][i] == 0)
        {
            throw runtime_error("error2");
        }
    }
    // 唯一解求解
    for (int i = line - 1; i >= 0; i++)
    {
        for (int j = 0; j < i; j++)
        {
            matrix_copy[j][line] = matrix_copy[j][line] - matrix_copy[j][i] * matrix_copy[i][line];
            matrix_copy[j][i] = 0;
        }
    }
    map<string, double> result;
    for (int i = 0; i < line; i++)
    {
        result[vari_table[i]] = matrix_copy[i][line];
    }
    return result;
}