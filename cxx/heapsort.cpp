#include <iostream>
#include <vector>

using namespace std;


void printAll(vector<int> heap){
    for(auto h: heap){
        cout<<h<<" ";
    }
    cout<<endl;
}

void heapInsert(vector<int>& heap, int& heapSize, int n){
    heap.push_back(n);
    heapSize++;
    int idx = heapSize-1;
    while(idx){
        if(heap[idx]>heap[(idx-1)/2]){
            swap(heap[idx], heap[(idx-1)/2]);
        }else{
            break;
        }
        idx = (idx-1)/2;
    }
}


void heapify(vector<int>& heap, int heapSize){
    int idx = 0;
    int left = idx*2+1;
    while(left<heapSize){
        int largest = left+1<heapSize?heap[left]>heap[left+1]?left:left+1:left;
        largest = heap[idx]>heap[largest]?idx:largest;
        if(largest==idx){
            break;
        }
        swap(heap[idx], heap[largest]);
        idx = largest;
        left = idx*2+1;
    }
}


void heapSort(vector<int>& heap, int& heapSize){
    while(heapSize){
        swap(heap[0], heap[heapSize-1]);
        heapSize--;
        heapify(heap, heapSize);
    }
}


int main()
{
    vector<int> heap;
    int n, a;
    cin>>n;
    int heapSize = 0;
    while(n){
        cin>>a;
        heapInsert(heap, heapSize, a);
        --n;
    }
    heapSort(heap, heapSize);
    printAll(heap);
    return 0;
}
