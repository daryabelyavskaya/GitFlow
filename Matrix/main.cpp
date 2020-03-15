#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

    void Print(std::vector<std::vector<double>> m,std::ostream& os) {
    for (std::vector<double> v1 : m) {
        for (float v2 : v1) {
            os << std::setw(15) << v2 << " ";
        }
        os << '\n';
    }
    }

    std::vector<std::vector<double >> First(std::vector<std::vector<double >> &m1, std::vector<std::vector<double >> &m2,std::ostream& f) {
    std:: vector<std::vector<double >> result;
    result.assign(m1.size(), std::vector<double >(m2[0].size()));
    auto start = std::chrono::high_resolution_clock::now();
    for (int k = 0; k < m1.size(); ++k) {
        for (int i = 0; i < m2[0].size(); ++i) {
            for (int j = 0; j < m1[0].size(); ++j) {
                result[k][i] += m1[k][j] * m2[j][i];
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    f << "Time(microseconds): " << time.count() << std::endl;
    return result;
    }

    void Second(std::vector<std::vector<double >> &m1, std::vector<std::vector<double >> &m2,std::vector<std::vector<double >> &result,
            int index_i,int index_j,int k)
    {
    for (int i = index_i * m1.size() / k; i < (index_i + 1) * m1.size()/k ; i++) {
        for (int j = index_j * m2[0].size() / k; j < (index_j + 1) * m2[0].size() / k; j++) {
            for (int l = 0; l < m1[0].size(); l++) {
                result[i][j] += m1[i][l] * m2[l][j];
            }
        }
    }
    }

    std:: vector<std::vector<double>> SecondParallel(std::vector<std::vector<double>> &m1,std::vector<std::vector<double>> &m2,int k,std::ostream&f) {
        std::vector<std::thread> threads(k);
        std::vector<std::vector<double>> result(m1.size(), std::vector<double>(m2[0].size(), 0));
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                threads[j] = std::thread(Second, std::ref(m1), std::ref(m2), std::ref(result), i,j,k);
                    threads[j].join();
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        f << "Time(microseconds): " << time.count() << std::endl;
        return result;
    }
    void Third( std::vector<std::vector<double>> &m1, std::vector<std::vector<double>> &m2,
                          std::vector<std::vector<double>> &result, int k, int index) {
    for (int i = 0; i < m1.size(); i++) {
        for (int j = 0; j < m1[0].size(); j++) {
            for (int s = index * m1[0].size() / k; s < (index + 1) * m1[0].size() / k; s++) {
                result[i][j] += m1[i][s] * m2[s][j];
            }
        }
    }
    }

    std::vector<std::vector<double>> ThirdParallel( std::vector<std::vector<double>> &m1,
                                                        std::vector<std::vector<double>> &m2, int k,std::ostream&f) {

    std::vector<std::vector<double>> result(m1.size(), std::vector<double>(m2[0].size(), 0));
    std::vector<std::thread> threads(k);
        auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++) {
        threads[i] = std::thread(Third, std::ref(m1), std::ref(m2), std::ref(result), k, i);
    }

    for (int j = 0; j < k; j++) {
        threads[j].join();
    }
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        f << "Time(microseconds): " << time.count() << std::endl;
    return result;
    }

    void Fourth(const std::vector<std::vector<double>> &m1, const std::vector<std::vector<double>> &m2,
                         std::vector<std::vector<double>> &result, int count, int i_index, int j_index, int k_index) {

    for (int i = i_index * m1.size() / count; i < (i_index + 1) * m1.size() / count; i++) {
        for (int j = j_index * m2[0].size() / count; j < (j_index + 1) * m2[0].size() / count; j++) {
            for (int k = k_index * m1[0].size() / count; k < (k_index + 1) * m1[0].size() / count; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    }

    std::vector<std::vector<double>> FourthParallel( std::vector<std::vector<double>> &m1,
                                                       std::vector<std::vector<double>> &m2, int count,std::ostream&f) {

    std::vector<std::vector<double>> result(m1.size(), std::vector<double>(m2[0].size(), 0));
    std::vector<std::thread> threads(count);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            for (int k = 0; k < count; k++) {
                threads[k] = std::thread(Fourth, std::ref(m1), std::ref(m2), std::ref(result), count, i, j, k);
            }
            for (int k = 0; k < count; k++) {
                threads[k].join();
            }
        }
    }
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        f << "Time(microseconds): " << time.count() << std::endl;
    return result;
    }

    int main() {
    int n,m,k,l;
    std::ifstream fin("input.txt");
    fin>>n>>m>>k>>l;
    std::ofstream fout("output.txt");
    if(m!=k) fout<<"Incorrect dimensions of matrices!";
    else {
        std::vector<std::vector<double >> m1(n, std::vector<double >(m, 0)), m2(k, std::vector<double >(l, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                fin >> m1[i][j];
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                fin >> m2[i][j];
        }
        //first
        std::vector<std::vector<double >> m3(n, std::vector<double >(l, 0));
        m3 = First(m1, m2,fout);
        Print(m3,fout);
        //second
        int count = 5;
        m3=SecondParallel(m1,m2,count,fout);
        Print(m3,fout);
        //third
        m3=ThirdParallel(m1,m2,count,fout);
        Print(m3,fout);
        //fourth
        m3=FourthParallel(m1,m2,count,fout);
        Print(m3,fout);
    }
    return 0;
    }
