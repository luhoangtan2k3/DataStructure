#include<stdio.h>
#include<stdlib.h>
typedef int DataType;
struct Node{
    DataType Key;
    Node *Left;
    Node *Right;
};
typedef struct Node* Tree;
// Tạo rỗng cây
void MakeNullTree(Tree &T){
    T = NULL;
}
// Kiểm tra cây có rỗng hay không
bool EmptyTree(Tree T){
    return T==NULL;
}
// Cây không có con(vô sinh)
bool Infertility(Tree T){
    return !EmptyTree(T)&&T->Left==NULL&&T->Right==NULL;
}
// Cây có 2 con
bool HaveTwoChild(Tree T){
    return !EmptyTree(T)&&T->Left!=NULL&&T->Right!=NULL;
}
// Cây có 1 con
bool HaveOneChild(Tree T){
    return !Infertility(T)&&!HaveTwoChild(T);
}
// Trả về con trái của cây
Tree LeftChild(Tree T){
    if(!EmptyTree(T)){
        return T->Left;
    }else return NULL;
}
// Trả về con phải của cây
Tree RightChild(Tree T){
    if(!EmptyTree(T)){
        return T->Right;
    }else return NULL;
}
// Trả về giá trị lớn nhất của 2 giá trị
int Max(int Value1,int Value2){
    return (Value1>Value2)?Value1:Value2;
}
// Trả về chiều cao của cây
int TreeHeight(Tree T){
    int Height = 0;
    if(!EmptyTree(T)){
        if(Infertility(T)){
            Height = 0;
        }else{
            Height = Max(TreeHeight(LeftChild(T)),TreeHeight(RightChild(T)))+1;
        }
    }
    return Height;
}
// Hàm thêm lần lượt các node vào cây
void CreateNode(Tree &T,DataType Value){
    if(EmptyTree(T)){
        Node *NODE = new Node;
        NODE->Key = Value;
        NODE->Left = NULL;
        NODE->Right = NULL;
        T = NODE;
    }else{
        //Value bé hơn T thêm vào bên trái của cây và ngược lại thêm vào bên phải.
        if(Value<T->Key){
            CreateNode(T->Left,Value);
        }else if(Value>T->Key){
            CreateNode(T->Right,Value);
        }
    }
}
// Duyệt tiền thứ tự
void NLR(Tree T){
    if(!EmptyTree(T)){
        printf("%d ",T->Key);
        NLR(T->Left);
        NLR(T->Right);
    }
}
// Duyệt trung thứ tự
void LNR(Tree T){
    if(!EmptyTree(T)){
        LNR(T->Left);
        printf("%d ",T->Key);
        LNR(T->Right);
    }
}
// Duyệt hậu thứ tự
void LRN(Tree T){
    if(!EmptyTree(T)){
        LRN(T->Left);
        LRN(T->Right);
        printf("%d ",T->Key);
    }
}
// Tổng số lượng node trong cây
int AmountNode(Tree T){
    if(EmptyTree(T)){
        return 0;
    } else return AmountNode(T->Left)+AmountNode(T->Right)+1;
}
// Tìm kiếm và trả về node được chỉ định
Tree SearchNode(DataType Value,Tree T){
    while(T!=NULL&&T->Key!=Value){
        if(Value<T->Key){
            T = T->Left;
        }else{
            T = T->Right;
        }
    }
    return T;
}
// Trả về kết quả tìm kiếm của SearchNode
void ResuftSearch(Tree T,DataType Value){
    if(SearchNode(Value,T)!=NULL){
        printf("Tìm thấy Node có giá trị = %d\n",Value);
    }else{
        printf("Không tìm thấy Node nào trong cây!!!\n");
    }
}
// Danh sách các node có đủ 2 con
void ListTwoChildren(Tree T){
    if(!EmptyTree(T)){
        if(T->Left!=NULL&&T->Right!=NULL){
            printf("%d ",T->Key);
        }
        ListTwoChildren(T->Left);
        ListTwoChildren(T->Right);
    }
}
// Danh sách các node chỉ có 1 con
void ListOneChildren(Tree T){
    if(!EmptyTree(T)){
        if((T->Left!=NULL&&T->Right==NULL)||(T->Left==NULL&&T->Right!=NULL)){
            printf("%d ",T->Key);
        }
        ListOneChildren(T->Left);
        ListOneChildren(T->Right);
    }
}
// Danh sách các node vô sinh,hiếm muộn
void ListInfertility(Tree T){
    if(!EmptyTree(T)){
        if(T->Left==NULL&&T->Right==NULL){
            printf("%d ",T->Key);
        }
        ListInfertility(T->Left);
        ListInfertility(T->Right);
    }
}
// Node có giá trị lớn nhất trong cây
void NodeMax(Tree T){
    if(!EmptyTree(T)){
        if(T->Right==NULL){
            printf("Giá trị lớn nhất = %d\n",T->Key);
        }
        NodeMax(T->Right);
    }
}
// Node có giá trị bé nhất trong cây
void NodeMin(Tree T){
    if(!EmptyTree(T)){
        if(T->Left==NULL){
            printf("Giá trị nhỏ nhất = %d\n",T->Key);
        }
        NodeMin(T->Left);
    }
}
// Xóa node lá trong cây nhị phân tìm kiếm
void DeleteNodeLeaf(Tree &Root,Tree &Parent){
    if(Root->Key<Parent->Key){
        Parent->Left = NULL;
    }else{
        Parent->Right = NULL;
    }
    printf("Node đã đc xóa khỏi cây nhị phân\n");
    delete Root;
}
// Xóa node có 1 con trong cây nhị phân tìm kiếm
void DeleteNodeOneChild(Tree &Root,Tree &Parent){
    if(Root->Left!=NULL&&Root->Right==NULL){
        if(Root->Key<Parent->Key){
            Parent->Left = Root->Left;
        }else{
            Parent->Right = Root->Left;
        }
    }else if(Root->Left==NULL&&Root->Right!=NULL){
        if(Root->Key<Parent->Key){
            Parent->Left = Root->Right;
        }else{
            Parent->Right = Root->Right;
        }
    }
    printf("Node đã đc xóa khỏi cây nhị phân\n");
    delete Root;
}
// Xóa node có 2 con trong cây nhị phân tìm kiếm
void DeleteNodeTwoChild(Tree &Root,Tree &Parent){
    Parent = Root;
    Tree Replace = Root->Right;
    while(Replace->Left!=NULL){
        Parent = Replace;
        Replace = Replace->Left;
    }
    Root->Key = Replace->Key;
    if(Replace->Left==NULL&&Replace->Right==NULL){
        DeleteNodeLeaf(Replace,Parent);
    }else{
        DeleteNodeOneChild(Replace,Parent);
    }
}
// Xóa node bất kỳ trong cây nhị phân tìm kiếm
void DeleteNode(Tree &T,DataType Value){
    if(!EmptyTree(T)){
        Tree Root = T;
        Tree Parent = NULL;
        while(Root!=NULL&&Root->Key!=Value){
            Parent = Root;
            if(Value<Root->Key){
                Root = Root->Left;
            }else{
                Root = Root->Right;
            }
        }
        if(Root!=NULL){
            if(Infertility(Root)){
                DeleteNodeLeaf(Root,Parent);
            }else if(HaveOneChild(Root)){
                DeleteNodeOneChild(Root,Parent);
            }else{
                DeleteNodeTwoChild(Root,Parent);
            }
        }else{
            printf("Không tồn tại!!!\n");
        }
    }
}
// Lưu các giá trị của node vào mảng 1 chiều
DataType Array[100],Run=0;// Biến Global
void SaveinArray(Tree T){
    if(T!=NULL){
        SaveinArray(T->Left);
        Array[Run++] = T->Key;
        SaveinArray(T->Right);
    }
}
// Trả về node đứng sau node được chỉ định
Tree GetNext(DataType Value,Tree T){
    for(int i=0;i<Run-1;i++){
        if(Array[i]==Value){
            return SearchNode(Array[i+1],T);
        }
    }
    return NULL;
}
// Hàm tạo cây tìm kiếm nhị phân hoàn chỉnh
void CreateTree(Tree &T){
    DataType Amount,Value;
    printf("Nhập vào số lượng Node\n");
    scanf("%d",&Amount);
    printf("Các Node nhập vào là: ");
    for(int i=0;i<Amount;i++){
        scanf("%d",&Value);
        CreateNode(T,Value);
    }
}
// Hàm xuất tiền,trung,hậu thứ tự của cây
void PrintfTree(Tree T){
    printf("Duyệt tiền thứ tự\n");
    printf("Các giá trị của cây:");
    NLR(T);
    printf("\n");
    printf("Duyệt trung thứ tự\n");
    printf("Các giá trị của cây:");
    LNR(T);
    printf("\n");
    printf("Duyệt hậu thứ tự\n");
    printf("Các giá trị của cây:");
    LRN(T);
    printf("\n");
}