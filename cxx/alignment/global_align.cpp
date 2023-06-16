#include <iostream>
#include <string>
#include <vector>
using namespace std;


void init_mat(vector<vector<int> > & mat, int G){
    mat[0][0] = 0;
    for(int i=1; i<mat.size(); i++){
        mat[i][0] = mat[i-1][0] + G;
    }
    for(int i=1; i<mat[0].size(); i++){
        mat[0][i] = mat[0][i-1] + G;
    }
}


void calc_mat(vector<vector<int> > & mat, string& qseq, string& rseq, int M, int X, int G){
    for(int i=1; i<=qseq.size(); i++){
        for(int j=1; j<=rseq.size(); j++){
            mat[i][j] = max(mat[i-1][j-1]+(qseq[i-1]==rseq[j-1]?M:X), max(mat[i-1][j]+G, mat[i][j-1]+G));
        }
    }
}


void trace_align(vector<vector<int> > & mat, string& qseq, string& rseq, int M, int X, int G, string& align_qseq, string& align_rseq, string& align_status){
    int qlen = qseq.size(), rlen = rseq.size();
    int qcur = qseq.size(), rcur = rseq.size();
    while(qcur>0 || rcur>0){
        if(rcur>0 && mat[qcur][rcur] == mat[qcur][rcur-1]+G){
            align_qseq = "-"+align_qseq;
            align_status = "-"+align_status;
            align_rseq = rseq[rcur-1]+align_rseq;
            rcur--;
        }else if(qcur>0 && mat[qcur][rcur] == mat[qcur-1][rcur]+G){
            align_qseq = qseq[qcur-1]+align_qseq;
            align_status = "-"+align_status;
            align_rseq = "-"+align_rseq;
            qcur--;
        }else{
            align_qseq = qseq[qcur-1]+align_qseq;
            align_status = (qseq[qcur-1]==rseq[rcur-1]?"|":"*")+align_status;
            align_rseq = rseq[rcur-1]+align_rseq;
            qcur--;
            rcur--;
        }
    }
}


int main()
{
    string qseq, rseq;
    cin>>qseq>>rseq;
    int qlen = qseq.size(), rlen = rseq.size();
    vector<vector<int> > mat(qlen+1, vector<int>(rlen+1, 0));
    int M = 1, X = -3, G = -2;
    init_mat(mat, G);
    calc_mat(mat, qseq, rseq, M, X, G);
    string align_qseq, align_status, align_rseq;
    trace_align(mat, qseq, rseq, M, X, G, align_qseq, align_rseq, align_status);
    cout<<align_qseq<<endl;
    cout<<align_status<<endl;
    cout<<align_rseq<<endl;
    return 0;
}