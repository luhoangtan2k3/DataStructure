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
// Hàm để duy trì tính chất của min heap cho một nút và các con của nó
void Heapify(int *Array,int n,int i){
    // Tìm chỉ số của nút nhỏ nhất trong ba nút: i (nút cha) và hai con của nó
    int Smallest = i;// Giả sử rằng nút cha là nhỏ nhất
    int Left = 2*i+1;// Chỉ số của con trái
    int Right = 2*i+2;// Chỉ số của con phải
    // So sánh với con trái và cập nhật chỉ số nhỏ nhất nếu cần
    if(Left<n&&*(Array+Left)<*(Array+Smallest)){
        Smallest = Left;
    }
    // So sánh với con phải và cập nhật chỉ số nhỏ nhất nếu cần
    if(Right<n&&*(Array+Right)<*(Array+Smallest)){
        Smallest = Right;
    }
    // Nếu chỉ số nhỏ nhất không phải là i (nút cha), đổi chỗ với nó và gọi hàm heapify cho nút mới đó
    if(Smallest!=i){
        Swap(Array+i,Array+Smallest);
        Heapify(Array,n,Smallest);
    }
}
// Hàm để tạo một min heap từ mảng ban đầu
void BuildHeap(int *Array,int n){
    for(int i =n/2-1;i>=0;i--){
        Heapify(Array,n,i);
    }
}
// Hàm để sắp xếp các phần tử của mảng bằng thuật toán heap sort
void HeapSort(int *Array,int n){
    BuildHeap(Array,n);
    // Lặp lại cho đến khi kích thước của heap lớn hơn 1:
    for(int i=n-1;i>0;i--){
        // Đổi chỗ phần tử nhỏ nhất (ở gốc của heap) với phần tử cuối cùng của heap
        Swap(Array+0,Array+i);
         // Giảm kích thước của heap đi 1
        n--;
        // Gọi hàm heapify cho gốc của heap để duy trì tính chất của min heap
        Heapify(Array,n,0);
    }
}
void ShellSort(int *Array,int n){
    // Sắp xếp các phần tử ở các khoảng cách n/2, n/4, n/8, ...
    for(int Interval=n/2;Interval>0;Interval/=2){
        // Duyệt qua các phần tử từ vị trí interval đến cuối mảng
        for(int i=Interval;i<n;i++){
            // Lưu giá trị của phần tử hiện tại vào biến temp
            int Temp = *(Array+i);
            int j;
            for(j=i;j>=Interval&&*(Array+(j-Interval))>Temp;j-=Interval){
                *(Array+j) = *(Array+(j-Interval));
            }
            // Gán giá trị của temp vào vị trí thích hợp
            *(Array+j) = Temp;
        }
    }
}
// Hàm tìm kiếm nhị phân
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
        // Tìm vị trí chèn bằng tìm kiếm nhị phân
        Loc = BinarySearch(Array,Selected,0,j);
        // Chuyển các phần tử lớn hơn selected sang phải
        while(j>=Loc){
            *(Array+(j+1)) = *(Array+j);
            j--;
        }
        // Chèn selected vào vị trí đã tìm được
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
// Hàm sắp xếp Counting Sort
void CountingSort(int *Array, int n) {
    // Tìm phần tử lớn nhất trong mảng
    int k = Max(Array, n);
    // Khởi tạo mảng Count với kích thước k + 1 và gán tất cả các phần tử bằng 0
    int Count[k + 1];
    for (int i = 0; i < k + 1; i++) {
        Count[i] = 0;
    }
    // Đếm số lần xuất hiện của mỗi phần tử trong mảng và lưu vào mảng Count
    for (int i = 0; i < n; i++) {
        Count[Array[i]]++;
    }
    // Tính tích lũy của các giá trị trong mảng Count
    for (int i =1 ;i < k +1 ;i++){
        Count[i]=Count[i]+Count[i-1];
    }
    // Khởi tạo mảng output với kích thước n và gán tất cả các phần tử bằng -1
    int Output[n];
    for (int i=0;i<n;i++){
        Output[i]=-1;
    }
    // Duyệt từ cuối đến đầu của mảng đầu vào và đặt các phần tử vào vị trí thích hợp trong mảng Output dựa vào giá trị trong mảng Count
    for (int i=n-1;i>=0;i--){
        Output[Count[Array[i]]-1]=Array[i];
        Count[Array[i]]--;
    }
    // Sao chép các phần tử từ mảng Output sang lại cho con trỏ Array
    for (int i=0;i<n;i++){
        *(Array+i)=Output[i];
    }
}
int main(){
    int Amount=0,*Array,Select=0;
    double Time_Run;
    clock_t Start,End;
    printf("Tổng hợp các thuật toán sắp xếp:\n");
    do{
        printf("\n\n");
        printf("1 - Sắp xếp nổi bọt - Bubble Sort\n");
        printf("2 - Sắp xếp chọn - Selection Sort\n");
        printf("3 - Sắp xếp chèn - Insertion Sort\n");
        printf("4 - Đổi chỗ trực tiếp - Interchange Sort\n");
        printf("5 - Sắp xếp nhanh - Quick Sort\n");
        printf("6 - Sắp xếp trộn - Merge Sort\n");
        printf("7 - Sắp xếp vun đống - Heap Sort\n");
        printf("8 - Shell Sort\n");
        printf("9 - Bin Sort\n");
        printf("10 - Counting Sort\n");
        printf("0 - Kết thúc chương trình\n");
        printf("\nChọn thao tác thực hiện để chạy:\n");
        scanf("%d",&Select);
        if(Select!=0){
        printf("\nNhập vào số lượng phần tử:\n");
        scanf("%d",&Amount);
        Input(Array,Amount);
        }
        switch(Select){
            case 1:
                printf("\nMảng ban đầu:\n");
                Output(Array,Amount);
                printf("\nBubble Sort:\n");
                Start = clock();
                Bubble_Sort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nThời gian thực thi lệnh: %fs",Time_Run);
                break;
            case 2:
                printf("\nMảng ban đầu:\n");
                Output(Array,Amount);
                printf("\nSelection Sort:\n");
                Start = clock();
                Selection_Soft(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nThời gian thực thi lệnh: %fs",Time_Run);
                break;
            case 3:
                printf("\nMảng ban đầu:\n");
                Output(Array,Amount);
                printf("\nInsertion Sort:\n");
                Start = clock();
                Insertion_Sort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nThời gian thực thi lệnh: %fs",Time_Run);
                break;
            case 4:
                printf("\nMảng ban đầu:\n");
                Output(Array,Amount);
                printf("\nInterchange Sort:\n");
                Start = clock();
                Interchange_Sort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nThời gian thực thi lệnh: %fs",Time_Run);
                break;
            case 5:
                printf("\nMảng ban đầu:\n");
                Output(Array,Amount);
                printf("\nQuick Sort:\n");
                Start = clock();
                Quick_Soft(Array,0,Amount-1);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nThời gian thực thi lệnh: %fs",Time_Run);
                break;
            case 6:
                printf("\nMảng ban đầu:\n");
                Output(Array,Amount);
                printf("\nMerge Sort:\n");
                Start = clock();
                Merge_Soft(Array,0,Amount-1);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nThời gian thực thi lệnh: %fs",Time_Run);
                break;
            case 7:
                printf("\nMảng ban đầu:\n");
                Output(Array,Amount);
                printf("\nHeap Sort:\n");
                Start = clock();
                HeapSort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nThời gian thực thi lệnh: %fs",Time_Run);
                break;
            case 8:
                printf("\nMảng ban đầu:\n");
                Output(Array,Amount);
                printf("\nShell Sort:\n");
                Start = clock();
                ShellSort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nThời gian thực thi lệnh: %fs",Time_Run);
                break;
            case 9:
                printf("\nMảng ban đầu:\n");
                Output(Array,Amount);
                printf("\nShell Sort:\n");
                Start = clock();
                BinSort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nThời gian thực thi lệnh: %fs",Time_Run);
                break;
            case 10:
                printf("\nMảng ban đầu:\n");
                Output(Array,Amount);
                printf("\nCounting Sort:\n");
                Start = clock();
                CountingSort(Array,Amount);
                End = clock();
                Output(Array,Amount);
                Time_Run = (double)(End - Start) / CLOCKS_PER_SEC;
                printf("\nThời gian thực thi lệnh: %fs",Time_Run);
                break;
        }
        free(Array);
    }while(Select!=0);
}