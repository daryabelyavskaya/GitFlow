package com.company;


public class queue{
    //ну не использовать же arraylist,все сама
    double []list;
    int capacity;
    int size=0;
    queue(int capacity1) {
        list = new double [capacity1];
        capacity = capacity1;
        size=0;

    }
    public double Get(int i){
        return list[i];
    }
   public  void Print_Queue(){
        for(int i=0;i<getSize();i++) {
            System.out.println(Get(i)+"\t");
        }
   }
    public void enlarge() {
        double [] list1 = new double [capacity];
        capacity = size * 2 + 1;
        for (int i = 0; i < size; i++)
            list1[i] = list[i];
        list=new double[capacity];
        for (int i = 0; i < size; i++)
        list[i] = list1[i];
    }

    public  int getSize()  {
            return size;
    }

    public int getCapacity()  {
        return capacity;
    }

    public void push_back(double a) {
        if (size >= capacity) enlarge();
        list[size]=a;
        size++;
    }
    public void push_front(double a) {
        if (size >= capacity) enlarge();
        double [] list2 = new double [capacity];
        for (int i = 0; i < size; i++)
            list2[i] = list[i];
        list=new double[capacity+1];
        list[0]=a;
        size++;
        for (int i = 1; i < size; i++)
            list[i] = list2[i-1];

    }

    void pop_back() {
        //здесь должно быть исключение красивое
        if (size == 0) System.out.println("Box is empty!");
        else
            size--;
    }
    public void Qsort(){
        int begin=0;
         int end=size-1;
         doSort(begin,end);
    }
    public void doSort(int begin,int end){
        int leftMarker = begin;
        int rightMarker = end;
        double curr = list[(leftMarker + rightMarker) / 2];
        do {

            while (list[leftMarker] < curr) {
                leftMarker++;
            }
            while (list[rightMarker] > curr) {
                rightMarker--;
            }
            if (leftMarker <= rightMarker) {

                if (leftMarker < rightMarker) {
                    double tmp = list[leftMarker];
                    list[leftMarker] = list[rightMarker];
                    list[rightMarker] = tmp;
                }

                leftMarker++;
                rightMarker--;
            }
        } while (leftMarker <= rightMarker);


        if (leftMarker < end) {
            doSort( leftMarker, end);
        }
        if (begin < rightMarker) {
            doSort(begin, rightMarker);
        }
    }
    public void pop_front() {
        if (size == 0) System.out.println("Box is empty!");
        else {
            for (int i = 0; i < size - 1; i++) {
                list[i] = list[i + 1];
            }
            size--;
        }
    };
















}
