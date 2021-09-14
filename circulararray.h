#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray();
    CircularArray(int _capacity);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T &operator[](int);
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}

//AGREGADO
template<class T>
T & CircularArray<T>::operator[](int iterator){
    return array[iterator];
}

template <class T>
int CircularArray<T>::size(){
    if(back<front)
        return capacity-((front-back)-1);
    else if(front==-1 && back==-1)
        return 0;
    else
        return (back-front)+1;
}

template<class T>
bool CircularArray<T>::is_empty(){
    return this->front == -1;
}

template<class T>
bool CircularArray<T>::is_full(){
    return next(back)==front;
}

template<class T>
void CircularArray<T>::push_back(T data){
    //Tal vez ponga un resize()
    if(front == -1 && back==-1)//si es vacío
        front=back=0;
    else if(is_full()==true)
        throw("it's full");
    else
        back = next(back);
    array[back]=data;
}

template<class T>
void CircularArray<T>::push_front(T data){
    if(front == -1 && back==-1)//si es vacío
        front=back=0;
    else if(is_full()==true)
        throw("it's full");
    else if(front==0 && back!=(capacity-1)){
            for(int i=back;i>=front;i--) {
                array[i + 1] = array[i];
            }
            back=next(back);}
            else front = prev(front);
    array[front]=data;
}

template<class T>
T CircularArray<T>::pop_front(){
    if(front==back) front = back=-1;
    else
        //for (int i = 0; i < size(); i++)array[i]=array[i+1];
        front=next(front);
}
template<class T>
T CircularArray<T>::pop_back(){
    if(front==back)front = back=-1;
    else
        back=prev(back);
}

template<class T>
void CircularArray<T>::insert(T data, int pos){
    if(is_full()==false){
        for(int i=back;i>=pos;i--){
            array[i+1]=array[i];
        }
        back=next(back);
        array[pos]=data;
    } else
        throw("it's full");
}

template<class T>
void CircularArray<T>::sort(){//SHELL SORT
    for(int jump=size()/2; jump>0; jump/=2){
        for(int i=jump; i<size();i++){
            int temp = array[i];
            int j;
            for(j=i;j>=jump && array[j-jump]>temp;j-=jump)
                array[j]=array[j-jump];

            array[j]=temp;
        }
    }

}

template<class T>
bool CircularArray<T>::is_sorted(){
    bool valor=true;
    for(int i=0;i<size()-1;i++){
        if(array[i]>array[i+1])
            valor=false;
    }
    return valor;
}

template<class T>
void CircularArray<T>::reverse(){
    int j=size()-1;
    for(int i=0;i<j;i++,j--){
        int temp=array[i];
        array[i]=array[j];
        array[j]=temp;
    }
}


template<class T>
void CircularArray<T>::clear(){
    front=back=-1;
}