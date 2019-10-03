#include <iostream>
#include <vector>
using  namespace std;

template <typename Iter,typename T>
bool binary_search(Iter beg,Iter end, T&& val) {//默认升序
    Iter beg_=beg;//保存表首
    if (end <= beg) {
        cout << "The index was not correct!" << endl;
        return false;
    }
    Iter i;
    bool find= false;
    while(beg<end-1) {
        i=beg+(end-beg)/2;
        if(val==(*i)||(*beg)==val||(*end)==val){
            find= true;
            break;
        }
        if(val>(*i)){
            beg=i;
            continue;
        }
        else if(val<(*i)) {
            end=i;
            continue;
        }
    }
    if(find==false){
        cout<<"The value doesn't exist!"<<endl;
    }
    if(find== true){
        if((*beg)==val)
            i=beg;
        else if((*end)==val)
            i=end;
        cout<<"The value("<<val<<") is one the position of "<<i-beg_+1<<endl;
    }
    return find;
}
//return ture if val is in*[beg,end)
//Used like :binary.begin(),vec.end(),666);




int main() {
    int value[]={0,1,3,4,6,7,8,12,13,16,18,18,19,30,35,60,70,99,99,100};
    vector <int> array(value,value+ sizeof(value)/ sizeof(int));
    vector <int>::iterator beg=array.begin();

    vector <int>::iterator end=array.end()-1;//end 代表最后一个元素的后一个位置

    int val=18;
    cout<<binary_search( beg, end, val);


    return 0;
}
