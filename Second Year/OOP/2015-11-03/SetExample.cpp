#include<iostream>

using namespace std;

const int MaxSize=100;
class Set{
	int len;
	char members[MaxSize];
	int find(char ch); //eleman bulma
public:
	Set(){len = 0;}
	int getLength() {return len;}

	void showSet();
	bool isMember(char ch);

	Set operator+(char ch);
	Set operator-(char ch);

	Set operator+(Set ch);
	Set operator-(Set ch);
};

void Set::showSet(){
    for(int i=0;i<len;i++){
        cout<<members[i]<<"\t";
    }
    cout<<endl;
}

int Set::find(char ch){
    for(int i=0;i<len;i++)
        if(members[i] == ch)
            return i;
    return -1;
}

bool Set::isMember(char ch){
    for(int i=0;i<len;i++){
        if(members[i]==ch)
            return true;
    }
    return false;
}



Set Set::operator+(char ch){
    if(!isMember(ch)){
        if(len == MaxSize-1)
            cout<<"Daha Eklenmez"<<endl;
        else{
            members[len++]=ch;
        }
    }
    return *this;
}


Set Set::operator-(char ch){
    if(isMember(ch)){
        int index = find(ch);
        char tmp;
        for(int i = index; i<len-1;i++){
            members[i] = members[i+1];
        }
        members[len-1] = '\0';
        len--;
    }
    return *this;
}



Set Set::operator+(Set s){
    for(int i =0 ; i<s.len;i++){
        *this = *this + s.members[i];
    }
}
Set Set::operator-(Set s){
    for(int i =0 ; i<s.len;i++){
        *this = *this - s.members[i];
    }
}

int main (){

    Set x;
    x = x+ '1';
    x = x+ 'a';
    x.showSet();
    x = x - '1';
    x.showSet();
}
