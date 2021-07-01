// 10727124 劉宇廷

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std ;

typedef char Str [1000] ;     // cstr	
int N ;     // 資料總比數 

struct Item {
	int schoolid ;     // 排序使用 
	string schoolname ;
	string departmentname ;
	string dayornight ;
	string level ;
	int students ;
	int teachers ;
	int graduaters ;
};

struct BinaryTree {
	int height ;     // 樹高
	Item data ;
	BinaryTree *leftChildPtr ;
	BinaryTree *rightChildPtr ;	
	BinaryTree *parent ;
};

void SetData( Str cStr, Item &temp ) {     // 從整行字串中擷取所需資料
	string buffer, cut ;
	int tabN = 0 ;
	int indexOfTab = 0 ;
	int i = 0 ;
	
	buffer.assign( cStr ) ;     // cstr to string 
	
	while ( tabN < 10 ) {
		indexOfTab = buffer.find_first_of( '\t', i ) ;

		if ( tabN == 0 ) {
			cut = buffer.substr( 0, indexOfTab ) ;
			temp.schoolid = atoi( cut.c_str() ) ;
		}
		else if ( tabN == 1 ) {
			temp.schoolname = buffer.substr( i, indexOfTab-i ) ;
		}
		else if ( tabN == 3 ) {
			temp.departmentname = buffer.substr( i, indexOfTab-i ) ;
		}
		else if ( tabN == 4 ) {
			temp.dayornight = buffer.substr( i, indexOfTab-i ) ;
		}
		else if ( tabN == 5 ) {
			temp.level = buffer.substr( i, indexOfTab-i ) ;
		}
		else if ( tabN == 6 ) {
			cut = buffer.substr( i, indexOfTab-i ) ;
			temp.students = atoi( cut.c_str() ) ;
		}
		else if ( tabN == 7 ) {
			cut = buffer.substr( i, indexOfTab-i ) ;
			temp.teachers = atoi( cut.c_str() ) ;
		}
		else if ( tabN == 8 ) {
			cut = buffer.substr( i, indexOfTab-i ) ;
			temp.graduaters = atoi( cut.c_str() ) ;
		}
		i = indexOfTab+1 ;
		tabN++ ;
    }
}

bool ReadFile( string filename, vector<Item> &list ) {
	FILE *infile = fopen( filename.c_str(), "r" ) ;

	if ( infile == NULL ) {
    	cout << endl << filename << " does not exist!\n\n" ;
    	return false ;
  	}
  	else {
    	Str tempstr ;
    	Item tempItem ;

    	fscanf( infile, "%[^\n]%*c", &tempstr ) ;     // 標題 
    	fscanf( infile, "%[^\n]%*c", &tempstr ) ;     // 標題 
    	fscanf( infile, "%[^\n]%*c", &tempstr ) ;     // 標題 

    	for ( int i = 1; fscanf( infile, "%[^\n]%*c", &tempstr ) != EOF ; i++ ){
      		SetData( tempstr, tempItem ) ;
      		list.push_back( tempItem ) ;
      		N = i;
    	}
  	}
  	return true ;
}

void Swap( Item &a, Item &b ) {
  	Item temp ;

  	temp.schoolid = a.schoolid ;
 	a.schoolid = b.schoolid ;
 	b.schoolid = temp.schoolid ;
  
 	temp.schoolname = a.schoolname ;
 	a.schoolname = b.schoolname ;
	b.schoolname = temp.schoolname ;
  
 	temp.departmentname = a.departmentname ;
	a.departmentname = b.departmentname ;
 	b.departmentname = temp.departmentname ;
  
	temp.dayornight = a.dayornight ;
	a.dayornight = b.dayornight ;
 	b.dayornight = temp.dayornight ;
  
 	temp.level = a.level ;
 	a.level = b.level ;
	b.level = temp.level ;
  
	temp.students = a.students ;
	a.students = b.students ;
	b.students = temp.students ;
  
  	temp.teachers = a.teachers ;
  	a.teachers = b.teachers ;
  	b.teachers = temp.teachers ;

	temp.graduaters = a.graduaters ;
  	a.graduaters = b.graduaters ;
  	b.graduaters = temp.graduaters ;
}

void SelectSort( vector<Item> &list ) {
	int max ;
  	for( int i = 0 ; i < N-1 ; i++ ){
    	max = i ;
    	for( int j = i + 1 ; j < N  ; j++ ){
      		if ( list[j].schoolid < list[max].schoolid ){
      			max = j ;
      		}
    	}
    	Swap( list[i], list[max] ) ;
  	}
}

void PrintFile( vector<Item> list, int n ) {	
	for ( int i = 0 ; i < n ; i++ ) {
		cout << "[" << i+1 << "]" << "\t" ;
		cout << list[i].schoolname << "\t" ;
		cout << list[i].departmentname << "\t" ;
		cout << list[i].dayornight << "\t" ;
		cout << list[i].level << "\t" ;
		cout << list[i].students << "\t" ;
		cout << list[i].teachers << "\t" ;
		cout << list[i].graduaters << endl ;
	}
}

void SetBinaryTreeByGraduaters( BinaryTree *&tree, vector<Item> list ) {
	BinaryTree *temp ;
	BinaryTree *pre ;
	int height = 0 ;
    
	int i = 0 ;
	while ( i < N ) {
		int j = 1 ;
		if ( tree == NULL ) {
			tree = new BinaryTree ;
			tree->leftChildPtr = NULL ;
			tree->rightChildPtr = NULL ;
			tree->parent = NULL ;
			
			Swap( tree->data, list[i] ) ;
			tree->height = j ;
		}
		else {
			temp = tree  ;
			
			while ( temp->leftChildPtr != NULL || temp->rightChildPtr != NULL ) {     // find position
				if ( list[i].graduaters < temp->data.graduaters && temp->leftChildPtr != NULL ) {
					temp = temp->leftChildPtr ;
					j++ ;
				}
				else if ( list[i].graduaters >= temp->data.graduaters && temp->rightChildPtr != NULL ) {
					temp = temp->rightChildPtr ;
					j++ ;
				}
				else {
					break ;     // found
				}
			}

			pre = temp ;

			if ( list[i].graduaters < temp->data.graduaters ) {     // insert list[i]
				temp->leftChildPtr = new BinaryTree ;
				temp = temp->leftChildPtr ;
				temp->leftChildPtr = NULL ;
				temp->rightChildPtr = NULL ;
				temp->parent = pre ;
				
				Swap( temp->data, list[i] ) ;
				j++ ;
				tree->height = j ;
			}
			else if ( list[i].graduaters >= temp->data.graduaters ) {
				temp->rightChildPtr = new BinaryTree ;
				temp = temp->rightChildPtr ;
				temp->leftChildPtr = NULL ;
				temp->rightChildPtr = NULL ;
				temp->parent = pre ;

				Swap( temp->data, list[i] ) ;
				j++ ;
				tree->height = j ;
			}
		}
		
		if ( j > height ) {
		  height = j ;
		}

		i++ ;
	}
	tree->height = height ;
}

void SearchByGraduaters( int graduaters, BinaryTree *tree, vector<Item> &temp  ) {
	if ( tree != NULL ) {
		if ( tree->data.graduaters <= graduaters ) {
			temp.push_back( tree->data ) ;
		}
		SearchByGraduaters( graduaters, tree->leftChildPtr, temp ) ;
		SearchByGraduaters( graduaters, tree->rightChildPtr, temp ) ;
	}
}

void PrintTitle() {
	cout << "*** University Graduate Information System ***" << endl ;
  	cout << "* 0. Quit                                    *" << endl ;
  	cout << "* 1. Create Binary Search Trees              *" << endl ;
  	cout << "* 2. Removal by Number of Graduates          *" << endl ;
  	cout << "**********************************************" << endl ;
  	cout << "Input a command(0, 1, 2): " ;
}

void Find( BinaryTree *tree, int graduaters, BinaryTree *&temp ) {
	if ( tree != NULL ) {
		if ( tree->data.graduaters <= graduaters ) {
			temp = tree ;
		}
		
		Find( tree->leftChildPtr, graduaters, temp ) ;
		Find( tree->rightChildPtr, graduaters, temp ) ;
	}
}

void DeleteTree( BinaryTree *&tree, int graduaters ) {
	BinaryTree *temp = NULL ;
	Find( tree, graduaters, temp ) ;

	while ( temp != NULL ) {
		
		if ( temp->leftChildPtr == NULL && temp->rightChildPtr == NULL ) {     // N0
			temp->parent->leftChildPtr = NULL ;
			temp->parent->rightChildPtr = NULL ;
			delete temp ;
		}
		else if ( temp->leftChildPtr != NULL && temp->rightChildPtr == NULL ) {     // N1-left
			if ( temp->parent == NULL ) {
				tree = temp->leftChildPtr ;
				tree->parent = NULL ;
				delete temp ;
			}
			else if ( temp->parent->data.graduaters < temp->data.graduaters ) {
				temp->parent->rightChildPtr = temp->leftChildPtr ;
				temp->leftChildPtr->parent = temp->parent ;
				delete temp ;			
			}
			else if ( temp->parent->data.graduaters > temp->data.graduaters ) {
				temp->parent->leftChildPtr = temp->leftChildPtr ;
				temp->leftChildPtr->parent = temp->parent ;
				delete temp ;
			}
		}
		else if ( temp->leftChildPtr == NULL && temp->rightChildPtr != NULL ) {     // N1-left
			if ( temp->parent == NULL ) {
				tree = temp->rightChildPtr ;
				tree->parent = NULL ;
				delete temp ;
			}
			else if ( temp->parent->data.graduaters < temp->data.graduaters ) {
				temp->parent->rightChildPtr = temp->rightChildPtr ;
				temp->rightChildPtr->parent = temp->parent ;
				delete temp ;			
			}
			else if ( temp->parent->data.graduaters > temp->data.graduaters ) {
				temp->parent->leftChildPtr = temp->rightChildPtr ;
				temp->rightChildPtr->parent = temp->parent ;
				delete temp ;
			}
		}
		else if ( temp->leftChildPtr != NULL && temp->rightChildPtr != NULL ) {     // N2
			BinaryTree *found = temp->rightChildPtr ;
			
			while ( found->leftChildPtr != NULL ) {
				found = found->leftChildPtr ;
			}
			
			Swap( temp->data, found->data ) ;
			
			if ( found->rightChildPtr != NULL ) {
				found->parent->leftChildPtr = found->rightChildPtr ;
				found->rightChildPtr->parent = found->parent ;
				delete found ;
			}
			else {
				delete found ;
			}
		}
		
		temp = NULL ;
		Find( tree, graduaters, temp ) ;
	}
}

int Max( int a, int b ) {
	if ( a >= b ) {
		return a ;
	}
	else {
		return b ;
	}
}

int Count( BinaryTree *tree ) {
	if ( tree == NULL ) {
		return 0 ;
	}
	else {
		return 1 + Max( Count( tree->leftChildPtr ), Count( tree->rightChildPtr ) ) ; 
	}
}

int main() {
	string command ;
	vector<Item> list ;     // 原始資料 
	vector<Item> temp ;
	BinaryTree *tree ;

	PrintTitle() ;
	cin >> command ;

	while ( command != "0" ){
		if ( command == "1" ) {
			free( tree ) ;
			list.clear() ;
			temp.clear() ;

			cout << endl << "Input a file number: " ;
			string filenum ;
			cin >> filenum ;
			string filename = "input" + filenum + ".txt" ;

			if ( ReadFile( filename, list ) ) {
				temp = list ;
				SelectSort( temp ) ;     // 依schoolid排序後的資料
				cout << endl ;
				PrintFile( temp, N ) ;
				cout << endl ;

				tree = NULL ;
				SetBinaryTreeByGraduaters( tree, list ) ;
				cout << "Tree height <Number of graduates> = " << tree->height << endl << endl ;
				list.clear() ;
			}
		}
		else if ( command == "2" ) {
			temp.clear() ;
			
			if ( tree == NULL ) {
				cout << "\nPlease choose command 1 first!\n\n" ;
			}
			else {
				cout << "\nInput the number of graduate: " ;
				string search ;
				cin >> search ;

				int graduaters =  atoi( search.c_str() ) ;
				if ( search != "0" ) {
					if ( graduaters == 0 ) {     // 特殊符號 
						cout << "\n### The input string " << search << " is not a decimal number! ###\n" ;
						temp.clear() ;
					}
					else {
						SearchByGraduaters( graduaters, tree, temp ) ;
					}					
				}
				else {     // 畢業人數=0
					SearchByGraduaters( graduaters, tree, temp ) ;
				}
				
				if ( temp.empty() ) {
					cout << "\nThere is no match!\n\n" ;
				}
				else {
					cout << "\nDelete records:\n" ;
					PrintFile( temp, temp.size() ) ;
					temp.clear() ;
					cout << endl ;
				}
				
				DeleteTree( tree, graduaters ) ;     // ***N過大時 appcrash*** 
				int x = Count( tree ) ;
				cout << "Tree heights <Number of graduates> = " << x << endl << endl ;
			}
		}
		else {
			cout << endl << "Command does not exit!\n\n" ;
		}
		
		PrintTitle() ;
		cin >> command ;
	}
}
