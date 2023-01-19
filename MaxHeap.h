// Assignment: ASU CSE310 HW#3 Fall 2022
// Your Name: Ian Carlson
// ASU ID: 1223065376      imcarls1
// ASU Email address: imcarls1@asu.edu
// Description: Header class that stores the varibles and the functions of this implementation
//				of a max heap. Fuctions include creation, insertion, deletion, getters for parent and
//				children index's, getters for the size and capacity. It also includes modification
// 				functions such as heapify, increase vin, and extracting the max value.  
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Each Car will have a unique vin
struct Car
{
	string model, make;
	int vin;        //Vehicle Identification Number
	double price;
};

//class MaxHeap represents a max heap that contains Car objects. The underline data structure
//is a one dimensional array of Cars.
class MaxHeap
{
    private:
    struct Car* carArr;	//an array of Cars
	struct Car* tempArr;
    int capacity, size;

	public:
    MaxHeap(int capacity);
    ~MaxHeap();

	Car* getCarArr();
	int getSize();
	int getCapacity();
	int isFound(int aVin);
	bool heapIncreaseVIN(int index, Car oneCarWithNewVIN);
	bool heapInsert(int vin, string model, string make, double price);
	void heapify(int index);
	Car getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity)
{
 	// initiates the heap with capacity set as a use specified capacity
	this->capacity = capacity;
	carArr = new Car[capacity];
	size = 0;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
	// prints the number cars that were presant in the heap, then deletes the heap
	int carCount = size;
	cout << "\nThe number of deleted cars is: " << carCount << endl;
	carCount = 0;
	carArr = NULL;
}

// getter for the heap
Car* MaxHeap::getCarArr(){
	return carArr;
}

// getter for the size
int MaxHeap::getSize(){
	return size;
}

// getter for the capacity
int MaxHeap:: getCapacity(){
	return capacity;
}


// searches the heap for a given vin number. If it is found the index of the location
// of the vin number is returned, otherwise it returns -1
int MaxHeap::isFound(int aVin){
	bool found = false;
	int i;
	// loops the heap using a linear search, this process will stop when the vin is found
	// or when it reaches the end of the heap
	for(i = 0; i < size; ++i){
		if(carArr[i].vin == aVin){
			found = true;
			break;
		}
	}
	// returns either the index or -1
	if(found){
		return i;
	}
	else{
		return -1;
	}
	
}
//****************************************************
//increase the Car's VIN located at the specific index
bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN)
{
	// checks and compares the index's, if the vin of the index is 
	// greater then the new index, then is spits an error message
	if (carArr[index].vin > oneCarWithNewVIN.vin)
    {
        cout << "\nIncrease VIN error: index out of range" << endl;
        return false;
    }

	// sets the car at the heap at the old index to the new car object
	carArr[index] = oneCarWithNewVIN;
	
	// iterates until the new vin is less then the vins of both the parents 
	while(index > 0 && carArr[ parent(index)].vin < carArr[index].vin){
		
		// switches the current car with its parent
		Car temp;
		temp = carArr[index];
		carArr[index] = carArr[parent(index)];
		carArr[parent(index)] = temp;

		// updates the index
		index = parent(index);
	}
    return true;

}

// inserts a car object into the heap
bool MaxHeap::heapInsert(int vin, string model, string make, double price){
	// creates the new car and assigns its values
	Car newCar;
	newCar.vin = vin;
	newCar.model = model;
	newCar.make = make;
	newCar.price = price;

	// creates a dummy car with a vin being the lowest unsigned int
	struct Car* dummyCar = new (struct Car);
	dummyCar->vin = -10000;
	
	// checks if the size is equal to the capacity 
	// if so then we double the size of the heap by creating a new heap
	// with the capacity of capactiy * 2
	// it is then copied back into the original heap
	if(size == capacity){
		capacity = capacity * 2;

		cout << "\nReach the capacity limit, double the capacity now.\n\nThe new capacity now is "
		<< capacity << "\n";

		
		tempArr = new Car[capacity];
		for(int i = 0; i < size; i++){
			tempArr[i] = carArr[i];
		}
		carArr = tempArr;
	}
	// the size is increased by 1
	++size;

	// the dummy car is added at the end of the heap and increase vin is called with
	// the paramaters being the index of the dummy car and the newCar that we want to add
	carArr[size - 1] = *dummyCar;
	heapIncreaseVIN(size - 1,newCar);

	return true;

}

// peforms swaping operations recursivly until the max heap properties are met, mainly getting the largest value of the 
// parent, the left, and the right node
void MaxHeap::heapify(int index){
	// sets the values of l and r using the index as the parent and setting the largest var to 0
	int l = leftChild(index);
	int r = rightChild(index);
	int largest = 0;
	// makes sure l is in the heap and if the vin is larger then the parents
	// otherwise it sets the largest to the parent index
	if(l < size && carArr[l].vin > carArr[index].vin){
		largest = l;
	}
	else{
		largest = index;
	}
	// it then checks if r is in the heap and if the vin at r is larger then the vin at largest
	if( r < size && carArr[r].vin > carArr[largest].vin){
		largest = r;
	}
	// it then checks if the largest is the parent index
	// if it is not then it swaps the largest with the parent index and calls itself
	// recurivly with largest being the index
	if(largest != index){
		Car temp = carArr[index];
		carArr[index] = carArr[largest];
		carArr[largest] = temp;
		heapify(largest);
	}
}

// gets the largest value of the heap, which will always be at index 0
Car MaxHeap::getHeapMax(){
	return carArr[0];
}

// removes the largest value in the heap, value at index 0
void MaxHeap::extractHeapMax(){
	// makes sure there is at least one value within the heap
	// otherwise it prints an error message
	if(size < 1){
		cout << "Error, heap underflow";
	}
	// gets the max element in the heap (would usually be retuned, good practice)
	Car max = carArr[0];
	
	// sets the value of the root node to the largest value in the heap
	// the size is the decremented and heapify is called 
	carArr[0] = carArr[size - 1];
	size--;
	heapify(0);

}

// gets the left child index of a given node
int MaxHeap::leftChild(int parentIndex){
	return (parentIndex * 2) + 1;
}

// gets the right child index of a given node
int MaxHeap::rightChild(int parentIndex){
	return (parentIndex * 2) + 2;
}

// gets the parent index of a given node
int MaxHeap::parent(int childIndex){
	return (childIndex - 1) / 2;
}


// void function to print the heap
void MaxHeap:: printHeap(){
	
	// makes sure the heap has at least on element within the heap, if it does not
	// it displays an error message. Otherwise the heap is iterated through printing out the values of
	// model, make, vin, and price for each car 
	if(size == 0){
		cout << "\nEmpty heap, no elements\n";
	}
	else{
		cout << "\nHeap capacity = " << capacity << "\n\nHeap size = " << size << "\n\n";

		for (int i = 0; i < size; i++)
		{
			Car oneCar = carArr[i];
			cout << left;
			cout << setw(8) << oneCar.vin
     		<< setw(12) << oneCar.model
     		<< setw(12) << oneCar.make
     		<< setw(8) << fixed << setprecision(2) << oneCar.price << endl;
		}	
	}
}