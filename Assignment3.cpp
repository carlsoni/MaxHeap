// Assignment: ASU CSE310 HW#3 Fall 2022
// Name: Ian Carlson
// ASU ID: 1223065376   imcarls1
// ASU Email Address: imcarls1@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	This project is done through storing cars wthin a max heap, sorted
//				by their respective vin numbers. Through this we can perform specific 
//				operations such as insertion, deletion, searching, sorting, extraction
//				and modification of values within the heap. Note: this heap does not support
//				duplicates (cars with the same vin number).
//********************************************************************************

#include "MaxHeap.h"

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
	char input1 = 'Z';
	int vin, newVIN, tempIndex;
	string model, make;
    double price;
	int capacity, index = -1;   //array capacity and index
	bool success = false;

	// holder varibles for getting and moving values in the max heap
	Car * carArr;
    Car oneCar;

	// instantiate an empty Heap
	MaxHeap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{

			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer

				// initiates a max heap with a capacity given by the user
				heap1 = new MaxHeap(capacity);
				
				break;

			case 'D':	//delete the heap, call the destructor explicitly
				cout << "\nDelete the heap" << endl;
				
				// deletes heap
				delete heap1;
				
				//re-initialize it with capacity 5
				heap1 = new MaxHeap(5);
				break;

			case 'E':	//Extract the maximum node
				// checks to see if the heap has been initalized and has values presant 
				// if either of these are true, it spits out an error message
                if (heap1 == nullptr || heap1->getSize() < 1)
                    cout << "\nEmpty heap, can NOT extract max" << endl;
                else
                {
					// displays the list before and after the max node (which is at index 0)
					// is removed from the heap
                    cout << "\nBefore extract heap max operation:\n";
					heap1->printHeap();
					heap1->extractHeapMax();
					cout << "\nAfter extract heap max operation:\n";
					heap1->printHeap();
                }
				break;

			case 'F':	//Find a Car
				cout << "\nEnter the car VIN you want to search: ";
				cin >> vin;
				cin.ignore(20, '\n');	//flush the buffer

				// looks for a vin number within the heap
				// if it is found then it returns the index
				// otherwise it returns -1. Using this we send 
				// a message to the user on weither or not a car
				// with the specified vin exists in the heap 
				tempIndex = heap1->isFound(vin);
				if(tempIndex >= 0){
					cout << "\nCar with VIN: " << vin << " is found\n";
				}
				else{
					cout << "\nCar with VIN: " << vin << " is NOT found\n";
				}
				break;

			case 'I':	//Insert a Car
				cout << "\nEnter the car model: ";
				cin >> model;

				cout << "\nEnter the car make: ";
				cin >> make;

				cout << "\nEnter the car VIN: ";
				cin >> vin;
				cout << "\nEnter the car price: ";
				cin >> price;
				cin.ignore(20, '\n');	//flush the buffer

				// uses the find car method to see if a car with the inputed vin
				// already exists, if it does then the new car is not added and
				// an error message is displayed
				tempIndex = heap1->isFound(vin);
				if(tempIndex >= 0){
					cout << "\nDuplicated Car. Not added\n";
					cout << "\nCar \"" << model << " " << make << "\" is NOT added\n";
				}
				// otherwise, the new car is inserted and a success message is displayed
				else{
					success = heap1->heapInsert(vin, model, make, price);
					cout << "\nCar \"" << model << " " << make << "\" is added\n";
				}
				break;

			case 'K':	//increase the vin
				cout << "\nEnter the old car VIN you want to increase: ";
				cin >> vin;
				cout << "\nEnter the new car VIN: ";
				cin >> newVIN;
				cin.ignore(20, '\n');	//flush the buffer

				// compares the vins, if the old vin is greater then the new vin. The vin is not updated 
				// and an error message is displayed
				if(vin > newVIN){
					cout << "\nIncrease VIN error: new vin is smaller than current vin\n";
					break;
				}

				// does a search for the old vin, if it does not exist, the vin is not updated
				// and an error message is displayed
				tempIndex = heap1->isFound(vin);
				if(tempIndex < 0){
					cout << "\nThe old VIN you try to increase does not exist\n";
					break;
				}
				// checks to see if the new vin is already presant in the heap. If it is the vin is not updated
				// and an error message is displayed
				if(heap1->isFound(newVIN) >= 0){
					cout << "\nThe new VIN you entered already exist, increase VIN operation failed\n";
					break;
				}

				// prints the heap before the vin is increased
				cout << "\nBefore increase VIN operation:\n";
				heap1->printHeap();
				
				// sets a storage car's vin to the new vin
				oneCar.vin = newVIN;
				
				// pulls the car array into the driver class to gain acess to the values of the car at the old vin 
				carArr = heap1->getCarArr();

				// using the index returned when finding the old vin, we get the car at that index and copy 
				// over the make, model, and price
				oneCar.make = carArr[tempIndex].make;
				oneCar.model = carArr[tempIndex].model;
				oneCar.price = carArr[tempIndex].price;

				// we then call the increase vin function using the tempIndex int and the oneCar Car
				heap1->heapIncreaseVIN(tempIndex, oneCar);				

				// we then print out the newly modified heap
				cout << "\nCar with old VIN: " << vin << " is increased to new VIN: " << newVIN <<"\n\nAfter increase VIN operation: \n";
				heap1->printHeap();
				break;

			case 'M':	//get maximum node

				// checks to make sure the heap has been initalized and has at least one value in it 
				// if not, the process is not executed
				if (heap1 == nullptr || heap1->getSize() < 1)
                    cout << "Empty heap, can NOT get max node" << endl;
                else{
					// if the heap has values and is initalized, it takes the max value and prints it 
					oneCar = heap1->getHeapMax();
					cout << "\nThe maximum heap node is:\n";
					cout << left;
					cout << setw(8) << oneCar.vin
     				<< setw(12) << oneCar.model
     				<< setw(12) << oneCar.make
     				<< setw(8) << fixed << setprecision(2) << oneCar.price << endl;
				}
				break;

			case 'P':	//Print heap contents
				heap1->printHeap();
				break;

			case 'S':	//HeapSort
				cout << "\nHeap sort. Cars will be sorted in increasing order of their VINs" << endl;
				heapSort(heap1);

				break;

			case 'Q':	//Quit
				delete heap1;
				break;

			case '?':	//Display Menu
				printMenu();
				break;

			default:
				cout << "Unknown action\n";
				break;
		}
	} while (input1 != 'Q');
	return 0;
}

//*****************************************************
//Given a max heap, we want to sort it in increasing order according to Car VIN, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap)
{
    // creates an array of cars with the size being the size of the heap
	// and creates a storage varible for the size of the heap
	int size = oneMaxHeap->getSize();
	Car* newArr = new Car[size];
	
	// loops from the end of the array down to 0
	// each iteration it extacts the maximum varible from the heap and puts it into the array
	for(int i = size-1; i >= 0; i--){
		newArr[i] = oneMaxHeap->getHeapMax();
		oneMaxHeap->extractHeapMax();
	}
	
	// now it prints the information of the cars in the array from smallest vin to the largest vin
	for(int i = 0; i < size; i++){
		Car oneCar = newArr[i];
			cout << left;
			cout << setw(8) << oneCar.vin
     		<< setw(12) << oneCar.model
     		<< setw(12) << oneCar.make
     		<< setw(8) << fixed << setprecision(2) << oneCar.price << endl;
	}
}

//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a Car by VIN\n";
	cout << "I\t\tInsert a Car\n";
	cout << "K\t\tIncrease the VIN\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}