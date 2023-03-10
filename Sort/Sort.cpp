#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int GetRandom(int Min,int Max){
    return Min + (int)(rand()*(Max-Min+1.0)/(1.0+RAND_MAX));
}
void Input(int *&Array,int Amount){
    srand((unsigned int)time(NULL));
    Array = (int*)malloc(sizeof(int)*Amount);
    for(int i=0;i<Amount;i++){
        *(Array+i) = GetRandom(0,1000);
    }
}
void Output(int *Array,int Amount){
    for(int i=0;i<Amount;i++){
        printf("%d, ",*(Array+i));
    }
}
void Swap(int *Value1,int *Value2){
    int Temp = *Value1;
    *Value1 = *Value2;
    *Value2 = Temp;
}
void Bubble_Sort(int *Array,int Amount){
    for(int i=0;i<Amount-1;i++){
        for(int j=Amount-1;j>i;j--){
            if(*(Array+j)<*(Array+j-1)){
                int *Value1 = Array+j;
                int *Value2 = Array+j-1;
                Swap(Value1,Value2);
            }
        }
    }
}
void Selection_Soft(int *Array,int Amount){
    int Min = 0;
    for(int i=0;i<Amount-1;i++){
        Min = i;
        for(int j=i+1;j<Amount;j++){
            if(*(Array+Min)>*(Array+j)){
                Min=j;
            }
        }
        if(Min!=i){
            int *Value1 = Array+i;
            int *Value2 = Array+Min;
            Swap(Value1,Value2);
        }
    }
}
void Insertion_Sort(int *Array,int Amount){
    int Pin=0,Value;
    for(int i=1;i<Amount;i++){
        Value = *(Array+i);
        for(Pin=i;(Pin>0)&&(*(Array+Pin-1)>Value);Pin--){
            *(Array+Pin) = *(Array+Pin-1);
        }
        *(Array+Pin) = Value;
    }
}
void Interchange_Sort(int *Array,int Amount){
    for(int i=0;i<Amount-1;i++){
        for(int j=i+1;j<Amount;j++){
            if(*(Array+i)>*(Array+j)){
                int *Value1=Array+i;
                int *Value2=Array+j;
                Swap(Value1,Value2);
            }
        }
    }
}
void Quick_Soft(int *Array,int Left,int Right){
    if(Left>=Right){
        return;
    }
    int Pivot = *(Array+(Left+Right)/2);
    int i = Left,j = Right;
    do{
        while(*(Array+i)<Pivot){
            i++;
        }
        while(*(Array+j)>Pivot){
            j--;
        }
        if(i<=j){
            int *Value1=Array+i;
            int *Value2=Array+j;
            Swap(Value1,Value2);
            i++;
            j--;
        }
    }while(i<j);
    Quick_Soft(Array,Left,j);
    Quick_Soft(Array,i,Right);
}
void Merge_Run(int *Array,int Left,int Center,int Right){
    int *Temp = (int*)malloc(sizeof(int)*(Right-Left+1));
    int Pos = 0;
    int i = Left;
    int j = Center +1;
    while(!(i>Center&&j>Right)){
        if((i<=Center&&j<=Right&&*(Array+i)<*(Array+j))||j>Right){
            *(Temp+Pos++) = *(Array+i++);
        } else {
            *(Temp+Pos++) = *(Array+j++);
        }
    }
    for(i=0;i<Right-Left+1;i++){
        *(Array+Left+i) = *(Temp+i);
    }
}
void Merge_Soft(int *Array,int Left,int Right){
    if(Left>=Right) return;
    int Center = (Left+Right)/2;
    Merge_Soft(Array,Left,Center);
    Merge_Soft(Array,Center+1,Right);
    Merge_Run(Array,Left,Center,Right);
}
// H??m ????? duy tr?? t??nh ch???t c???a min heap cho m???t n??t v?? c??c con c???a n??
void Heapify(int *Array,int n,int i){
    // T??m ch??? s??? c???a n??t nh??? nh???t trong ba n??t: i (n??t cha) v?? hai con c???a n??
    int Smallest = i;// Gi??? s??? r???ng n??t cha l?? nh??? nh???t
    int Left = 2*i+1;// Ch??? s??? c???a con tr??i
    int Right = 2*i+2;// Ch??? s??? c???a con ph???i
    // So s??nh v???i con tr??i v?? c???p nh???t ch??? s??? nh??? nh???t n???u c???n
    if(Left<n&&*(Array+Left)<*(Array+Smallest)){
        Smallest = Left;
    }
    // So s??nh v???i con ph???i v?? c???p nh???t ch??? s??? nh??? nh???t n???u c???n
    if(Right<n&&*(Array+Right)<*(Array+Smallest)){
        Smallest = Right;
    }
    // N???u ch??? s??? nh??? nh???t kh??ng ph???i l?? i (n??t cha), ?????i ch??? v???i n?? v?? g???i h??m heapify cho n??t m???i ????
    if(Smallest!=i){
        Swap(Array+i,Array+Smallest);
        Heapify(Array,n,Smallest);
    }
}
// H??m ????? t???o m???t min heap t??? m???ng ban ?????u
void BuildHeap(int *Array,int n){
    for(int i =n/2-1;i>=0;i--){
        Heapify(Array,n,i);
    }
}
// H??m ????? s???p x???p c??c ph???n t??? c???a m???ng b???ng thu???t to??n heap sort
void HeapSort(int *Array,int n){
    BuildHeap(Array,n);
    // L???p l???i cho ?????n khi k??ch th?????c c???a heap l???n h??n 1:
    for(int i=n-1;i>0;i--){
        // ?????i ch??? ph???n t??? nh??? nh???t (??? g???c c???a heap) v???i ph???n t??? cu???i c??ng c???a heap
        Swap(Array+0,Array+i);
         // Gi???m k??ch th?????c c???a heap ??i 1
        n--;
        // G???i h??m heapify cho g???c c???a heap ????? duy tr?? t??nh ch???t c???a min heap
        Heapify(Array,n,0);
    }
}
void ShellSort(int *Array,int n){
    // S???p x???p c??c ph???n t??? ??? c??c kho???ng c??ch n/2, n/4, n/8, ...
    for(int Interval=n/2;Interval>0;Interval/=2){
        // Duy???t qua c??c ph???n t??? t??? v??? tr?? interval ?????n cu???i m???ng
        for(int i=Interval;i<n;i++){
            // L??u gi?? tr??? c???a ph???n t??? hi???n t???i v??o bi???n temp
            int Temp = *(Array+i);
            int j;
            for(j=i;j>=Interval&&*(Array+(j-Interval))>Temp;j-=Interval){
                *(Array+j) = *(Array+(j-Interval));
            }
            // G??n gi?? tr??? c???a temp v??o v??? tr?? th??ch h???p
            *(Array+j) = Temp;
        }
    }
}
// H??m t??m ki???m nh??? ph??n
int BinarySearch(int *Array,int Item,int Low,int High){
    if(High<=Low){
        return (Item>*(Array+Low))?(Low+1):Low;
    }
    int Mid = (Low+High)/2;
    if(Item==*(Array+Mid)){
        return Mid+1;
    }
    if(Item>*(Array+Mid)){
        return BinarySearch(Array,Item,Mid+1,High);
    }
    return BinarySearch(Array,Item,Low,Mid-1);
}
void BinSort(int *Array,int n){
    int i, Loc, j, k, Selected;
    for(i=1;i<n;++i){
        j=i-1;
        Selected = *(Array+i);
        // T??m v??? tr?? ch??n b???ng t??m ki???m nh??? ph??n
        Loc = BinarySearch(Array,Selected,0,j);
        // Chuy???n c??c ph???n t??? l???n h??n selected sang ph???i
        while(j>=Loc){
            *(Array+(j+1)) = *(Array+j);
            j--;
        }
        // Ch??n selected v??o v??? tr?? ???? t??m ???????c
        *(Array+(j+1)) = Selected;
    }
}
int Max(int Array[], int n) {
  int Max = Array[0];
  for (int i = 1; i < n; i++) {
    if (Array[i] > Max) {
      Max = Array[i];
    }
  }
  return Max;
}
// H??m s???p x???p Counting Sort
void CountingSort(int *Array, int n) {
    // T??m ph???n t??? l???n nh???t trong m???ng
    int k = Max(Array, n);
    // Kh???i t???o m???ng Count v???i k??ch th?????c k + 1 v?? g??n t???t c??? c??c ph???n t??? b???ng 0
    int Count[k + 1];
    for (int i = 0; i < k + 1; i++) {
        Count[i] = 0;
    }
    // ?????m s??? l???n xu???t hi???n c???a m???i ph???n t??? trong m???ng v?? l??u v??o m???ng Count
    for (int i = 0; i < n; i++) {
        Count[Array[i]]++;
    }
    // T??nh t??ch l??y c???a c??c gi?? tr??? trong m???ng Count
    for (int i =1 ;i < k +1 ;i++){
        Count[i]=Count[i]+Count[i-1];
    }
    // Kh???i t???o m???ng output v???i k??ch th?????c n v?? g??n t???t c??? c??c ph???n t??? b???ng -1
    int Output[n];
    for (int i=0;i<n;i++){
        Output[i]=-1;
    }
    // Duy???t t??? cu???i ?????n ?????u c???a m???ng ?????u v??o v?? ?????t c??c ph???n t??? v??o v??? tr?? th??ch h???p trong m???ng Output d???a v??o gi?? tr??? trong m???ng Count
    for (int i=n-1;i>=0;i--){
        Output[Count[Array[i]]-1]=Array[i];
        Count[Array[i]]--;
    }
    // Sao ch??p c??c ph???n t??? t??? m???ng Output sang l???i cho con tr??? Array
    for (int i=0;i<n;i++){
        *(Array+i)=Output[i];
    }
}
int main(){
    int Amount=0,*Array,Select=0;
    double Time_Run;
    clock_t Start,End;
    printf("T???ng h???p c??c thu???t to??n s???p x???p:\n");
    do{
        printf("\n\n");
        printf("1 - S???p x???p n???i b???t - Bubble Sort\n");
        printf("2 - S???p x???p ch???n - Selection Sort\n");
        printf("3 - S???p x???p ch??n - Insertion Sort\n");
        printf("4 - ?????i ch??? tr???c ti???p - Interchange Sort\n");
        printf("5 - S???p x???p nhanh - Quick Sort\n");
        printf("6 - S???p x???p tr???n - Merge Sort\n");
        printf("7 - S???p x???p vun ?????ng - Heap Sort\n");
        printf("8 - Shell Sort\n");
        printf("9 - Bin Sort\n");
        printf("10 - Counting Sort\n");
        printf("0 - K???t th??c ch????ng tr??nh\n");
        printf("\nCh???n thao t??c th???c hi???n ????? ch???y:\n");
        scanf("%d",&Select);
        if(Select!=0){
        printf("\nNh???p v??o s??? l?????ng ph???n t???:\n");
        scanf("%d",&Amount);
        Input(Array,Amount);
        }
        switch(Select){
            case 1:
                printf("\nM???ng ban ?????u:\n");
                Output(Array,Amount);
                printf("\nBubble Sort:\n");
                Start = clock();
                Bubble_Sort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nTh???i gian th???c thi l???nh: %fs",Time_Run);
                break;
            case 2:
                printf("\nM???ng ban ?????u:\n");
                Output(Array,Amount);
                printf("\nSelection Sort:\n");
                Start = clock();
                Selection_Soft(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nTh???i gian th???c thi l???nh: %fs",Time_Run);
                break;
            case 3:
                printf("\nM???ng ban ?????u:\n");
                Output(Array,Amount);
                printf("\nInsertion Sort:\n");
                Start = clock();
                Insertion_Sort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nTh???i gian th???c thi l???nh: %fs",Time_Run);
                break;
            case 4:
                printf("\nM???ng ban ?????u:\n");
                Output(Array,Amount);
                printf("\nInterchange Sort:\n");
                Start = clock();
                Interchange_Sort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nTh???i gian th???c thi l???nh: %fs",Time_Run);
                break;
            case 5:
                printf("\nM???ng ban ?????u:\n");
                Output(Array,Amount);
                printf("\nQuick Sort:\n");
                Start = clock();
                Quick_Soft(Array,0,Amount-1);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nTh???i gian th???c thi l???nh: %fs",Time_Run);
                break;
            case 6:
                printf("\nM???ng ban ?????u:\n");
                Output(Array,Amount);
                printf("\nMerge Sort:\n");
                Start = clock();
                Merge_Soft(Array,0,Amount-1);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nTh???i gian th???c thi l???nh: %fs",Time_Run);
                break;
            case 7:
                printf("\nM???ng ban ?????u:\n");
                Output(Array,Amount);
                printf("\nHeap Sort:\n");
                Start = clock();
                HeapSort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nTh???i gian th???c thi l???nh: %fs",Time_Run);
                break;
            case 8:
                printf("\nM???ng ban ?????u:\n");
                Output(Array,Amount);
                printf("\nShell Sort:\n");
                Start = clock();
                ShellSort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nTh???i gian th???c thi l???nh: %fs",Time_Run);
                break;
            case 9:
                printf("\nM???ng ban ?????u:\n");
                Output(Array,Amount);
                printf("\nShell Sort:\n");
                Start = clock();
                BinSort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nTh???i gian th???c thi l???nh: %fs",Time_Run);
                break;
            case 10:
                printf("\nM???ng ban ?????u:\n");
                Output(Array,Amount);
                printf("\nCounting Sort:\n");
                Start = clock();
                CountingSort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nTh???i gian th???c thi l???nh: %fs",Time_Run);
                break;
        }
        free(Array);
    }while(Select!=0);
}