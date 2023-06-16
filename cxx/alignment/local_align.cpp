#include <iostream>
#include <string>
#include <vector>
using namespace std;


void calc_mat(vector<vector<int> > & mat, string& qseq, string& rseq, int M, int X, int G, int& xmax, int& ymax, int& score_max){
    for(int i=1; i<=qseq.size(); i++){
        for(int j=1; j<=rseq.size(); j++){
            mat[i][j] = max(0, max(mat[i-1][j-1]+(qseq[i-1]==rseq[j-1]?M:X), max(mat[i-1][j]+G, mat[i][j-1]+G)));
            if(mat[i][j]>score_max){
                score_max = mat[i][j];
                xmax = i, ymax = j;
            }
        }
    }
}


void trace_align(vector<vector<int> > & mat, string& qseq, string& rseq, int M, int X, int G, string& align_qseq, string& align_rseq, string& align_status, int xmax, int ymax){
    int qlen = qseq.size(), rlen = rseq.size();
    int qcur = xmax, rcur = ymax;
    int qsuf = qlen, rsuf = rlen;
    
    while(mat[qcur][rcur] != 0){
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
    int xmax = 0, ymax = 0, score_max = 0;
    calc_mat(mat, qseq, rseq, M, X, G, xmax, ymax, score_max);
    string align_qseq, align_status, align_rseq;
    trace_align(mat, qseq, rseq, M, X, G, align_qseq, align_rseq, align_status, xmax, ymax);
    cout<<align_qseq<<endl;
    cout<<align_status<<endl;
    cout<<align_rseq<<endl;
    return 0;
}