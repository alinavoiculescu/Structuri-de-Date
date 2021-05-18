#include <iostream>

using namespace std;


class MinMaxHeap
{
    int maxSize;
    float* Heap;
    int heapSize;

    void ReHeapUp(int, bool);
    void ReHeapDown(int, bool);
    bool Min(int);
    void Swap(int, int);
    void Resize();

public:
    //Constructor
    MinMaxHeap();

    //Copy constructor
    MinMaxHeap(const MinMaxHeap&);

    //Operator =
    MinMaxHeap& operator=(MinMaxHeap&);

    //Insert
    void Insert(float);

    //Find
    bool findMin(float&);
    bool findMax(float&);

    //Delete
    void deleteMin();
    void deleteMax();

    //Destructor
    ~MinMaxHeap();

    //Getter for size of HEAP
    int getSize();

    //Getter for HEAP
    void getHeap();
};

//Create HEAP from ARRAY
MinMaxHeap buildHeap(float futureHeap[], int futureHeapSize)
{
    MinMaxHeap H;

    for (int i = 0; i < futureHeapSize; i++)
        H.Insert(futureHeap[i]);

    return H;
}

void message();
void menu();

int main()
{
    menu();

    return 0;
}

MinMaxHeap::MinMaxHeap()
{
    maxSize = 100;
    Heap = new float[maxSize];
    heapSize = 0;
}

MinMaxHeap::MinMaxHeap(const MinMaxHeap& H)
{
    maxSize = H.maxSize;
    Heap = H.Heap;
    heapSize = H.heapSize;
}

MinMaxHeap& MinMaxHeap::operator=(MinMaxHeap& H)
{
    if (this != &H)
    {
        maxSize = H.maxSize;
        Heap = H.Heap;
        heapSize = H.heapSize;
    }
    return *this;
}

void MinMaxHeap::Insert(float value)
{
    if (heapSize == maxSize)
        Resize();

    Heap[heapSize] = value;

    if (heapSize)
    {
        bool Minlvl = Min(heapSize);
        int parent = (heapSize - 1) / 2;

        if (Minlvl)
        {
            if(Heap[parent] < Heap[heapSize])
            {
                Swap(parent, heapSize);
                ReHeapUp(parent, (!Minlvl));
            }
            else
                ReHeapUp(heapSize, Minlvl);
        }
        else
        {
            if (Heap[parent] > Heap[heapSize])
            {
                Swap(parent, heapSize);
                ReHeapUp(parent, (!Minlvl));
            }
            else
                ReHeapUp(heapSize, Minlvl);
        }
    }
    heapSize++;
}

bool MinMaxHeap::findMin(float& value)
{
    if (heapSize)
    {
        value = Heap[0];
        return true;
    }
    else
        return false;
}

bool MinMaxHeap::findMax(float& value)
{
    if (heapSize)
    {
        if (heapSize == 1)
            value = Heap[0];
        else if (heapSize == 2)
            value = Heap[1];
        else
            value = (Heap[1] < Heap[2] ? Heap[2] : Heap[1]);
        return true;
    }
    else
        return false;
}

void MinMaxHeap::deleteMin()
{
    if (heapSize == 0)
        return;
    heapSize--;
    Heap[0] = Heap[heapSize];
    if (heapSize != 0)
        ReHeapDown(0, true);
}

void MinMaxHeap::deleteMax()
{
    if (heapSize == 0)
        return;
    int maxIndex = 0;
    if (heapSize == 1)
        maxIndex = 0;
    else if (heapSize == 2)
        maxIndex = 1;
    else
        maxIndex = (Heap[1] < Heap[2] ? 2 : 1);
    heapSize--;
    Heap[maxIndex] = Heap[heapSize];
    if(heapSize)
        ReHeapDown(maxIndex, false);
}

MinMaxHeap::~MinMaxHeap()
{
    delete[] Heap;
    Heap = NULL;
}

int MinMaxHeap::getSize()
{
    return heapSize;
}

void MinMaxHeap::ReHeapUp(int index, bool Minlvl)
{
    int current = index;
    int parent = 0, grandpa = 0;
    bool OK = true;

    while(OK)
    {
        parent = (current - 1) / 2;
        if (parent - 1 < 0)
            OK = false;
        else
        {
            grandpa = (parent - 1) / 2;
            if (Minlvl ? Heap[current] < Heap[grandpa] : Heap[grandpa] < Heap[current])
            {
                Swap(current, grandpa);
                current = grandpa;
            }
            else
                OK = false;
        }
    }
}

void MinMaxHeap::ReHeapDown(int index, bool Minlvl)
{
    int leftChild = 0, rightChild = 0;
    int leftGrandChild = 0, rightGrandChild = 0; //cel mai din stg/drpt
    int wantedIndex = 0;
    bool OK = true;

    leftChild = index * 2 + 1;
    while (OK && leftChild < heapSize) //cat timp are un fiu in stg
    {
        wantedIndex = leftChild;
        rightChild = leftChild + 1;

        if (rightChild < heapSize && (Minlvl ? Heap[rightChild] < Heap[wantedIndex] : Heap[wantedIndex] < Heap[rightChild]))
            wantedIndex = rightChild;

        leftGrandChild = leftChild * 2 + 1;

        bool grandChild = false;

        if (leftGrandChild < heapSize)  //daca are nepotul din stg
        {
            rightGrandChild = leftGrandChild + 3;

            for (int i = leftGrandChild; i <= rightGrandChild; i++) //toti nepotii
                if (i < heapSize && (Minlvl ? Heap[i] < Heap[wantedIndex] : Heap[wantedIndex] < Heap[i]))
                {
                    wantedIndex = i;
                    grandChild = true;
                }
        }
        if (grandChild)
        {
            if (Minlvl ? Heap[wantedIndex] < Heap[index] : Heap[index] < Heap[wantedIndex])
            {
                Swap(wantedIndex, index);
                int parent = (wantedIndex - 1) / 2;
                if (Minlvl ? Heap[parent] < Heap[wantedIndex] : Heap[wantedIndex] < Heap[parent])
                    Swap(wantedIndex, parent);
                index = wantedIndex;
                leftChild = index * 2 + 1;
            }
            else
                OK = false;
        }
        else    //daca e copil
        {
            if (Minlvl ? Heap[wantedIndex] < Heap[index] : Heap[index] < Heap[wantedIndex])
                Swap(wantedIndex, index);
            OK = false;
        }
    }
}

bool MinMaxHeap::Min(int index)
{
    bool Min = true;
    int startMin = 2;
    int cmpIndex = 0;

    while (index > cmpIndex)
    {
        cmpIndex += startMin;
        startMin *= 2;
        Min = (!Min);
    }
    return Min;
}

void MinMaxHeap::Swap(int index1, int index2)
{
    float aux = Heap[index1];
    Heap[index1] = Heap[index2];
    Heap[index2] = aux;
}

void MinMaxHeap::Resize()
{
    float* auxHeap = Heap;
    maxSize *= 2;
    Heap = new float[maxSize];

    for (int i = 0; i < heapSize; i++)
        Heap[i] = auxHeap[i];

    delete[] auxHeap;
    auxHeap = NULL;
}

void MinMaxHeap::getHeap()
{
    for(int i = 0; i < heapSize; i++)
        cout<<Heap[i]<<" ";
}

void message()
{
    cout<<"1. Insert x"<<endl;
    cout<<"2. Delete min"<<endl;
    cout<<"3. Delete max"<<endl;
    cout<<"4. Print min"<<endl;
    cout<<"5. Print max"<<endl;
    cout<<"6. Print heap"<<endl;
    cout<<"0. Exit"<<endl<<endl<<endl;
}

void menu()
{
    cout<<"-----------------We need to BUILD A HEAP to start the program.-----------------"<<endl<<endl;
    MinMaxHeap H;


    int n;
    cout<<"---Number of values = ";
    cin>>n;
    float heap[n];
    if (n)
        cout<<endl<<"---Give us "<<n<<" values: ";
    for (int i = 0; i < n; i++)
        cin>>heap[i];
    int heapSize = sizeof(heap) / sizeof(heap[0]);
    MinMaxHeap H1 = buildHeap(heap, heapSize);
    H = H1;
    cout<<endl<<"---Your Min-Max Heap is: ";
    H.getHeap();
    cout<<endl<<endl;

    message();
    cout<<"---Your option: ";
    int option;
    cin>>option;

    while (option)
    {
        switch(option)
        {
        case 1:
            {
                float x;
                cout<<"---x = ";
                cin>>x;
                H.Insert(x);
                break;
            }
        case 2:
            {
                H.deleteMin();
                break;
            }
        case 3:
            {
                H.deleteMax();
                break;
            }
        case 4:
            {
                float y;
                H.findMin(y);
                cout<<"---Min = "<<y<<endl;
                break;
            }
        case 5:
            {
                float y;
                H.findMax(y);
                cout<<"---Max = "<<y<<endl;
                break;
            }
        case 6:
            {
                cout<<endl<<"---Your Min-Max Heap is: ";
                H.getHeap();
                cout<<endl;
                break;
            }
        }
        cout<<endl<<endl<<endl<<endl<<"Do you want another option?"<<endl<<endl<<endl<<endl;
        message();
        cin>>option;
    }
}
