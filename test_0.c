
??
void temp(){
    int a,b,c;
    c = a*b;
}
??
int main(){
    int i ;
    int a = 1,b = 1,tmp;

    // tmp = a + b;
    for (i = 0; i < 10;i=i+1){
        a = a + b;
        tmp = a;
        a = b;
        b = tmp;
    }
    
    // return 0;
}