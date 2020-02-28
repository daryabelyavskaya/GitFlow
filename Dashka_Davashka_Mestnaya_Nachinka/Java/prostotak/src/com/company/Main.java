package com.company;
public class Main {

    public static void main(String[] args) {
	queue list= new queue(1);
	list.pop_back();
	assert(list.getCapacity()==1);
	list.push_back(4.3);
	assert(list.getSize()==1);
	list.push_front(8.9);
	assert(list.getSize()==3);
	list.Print_Queue();
	for(int i=0;i<5;i++)
	list.push_back((int)(Math.random()*10));
	list.Qsort();
		System.out.println("Sorted Queue");
		list.Print_Queue();
    }
}
