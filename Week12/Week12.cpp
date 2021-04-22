// Week12.cpp : Defines the entry point for the console application.
//   some change.... I wna tto change something....

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <algorithm>  //sort

using std::cout;
using std::endl;
using std::ostream;
using std::accumulate;

using namespace std;


//
// What are containers ? Data structures to manage in different way
// collection of objects
//
// If you did not take CSC223 - Data Structures and Algorithms : // http://scanftree.com/Data_Structure/
//
//
// Reference: http://www.cplusplus.com/reference/stl/
//
// Sequential vs Associative Containers ?
//
// How will you access the objects has you are doing the processing ?
//
// Sequential : how to select p. 327 
//
// vector by default, unless you have specific requirements to will be better served by another cointainer
//
// lots of small objects + memory constraint = don't use list or forward_list
//
// random access: vector or deque
//
// insert or delete in the 'middle'-> list or forward_list
//
// insert or delete at the front or back -> deque
//
//
class Shape {

public:
	int x; //1
	long l; //2
	float f; //3

	int * ptrInt; //4
	long * ptrLong; //5
	float * ptrFloat; //6
	//byte* ptrByte; //7

	string name; //8
	string * ptrDescription; //9
	//byte* ptrImage; //10

	Shape(int value) : x(value) { 
		
		x = 1;
		l = 2;
		f = 1.2;

		ptrInt = new int(1);
		ptrLong = new long( 2l);
		ptrFloat = new float( 1.2 );
		//ptrByte = new byte();

		name = "myname";
		ptrDescription = new string( "a dynamic description" );
		//ptrImage = new byte[1000];
	}

	virtual ~Shape(){
		delete ptrInt;
		delete ptrLong;
		delete ptrFloat;

		delete ptrDescription;
		//delete ptrImage;
	}
};

class Rectangle : public Shape {

public:
	int y;

};

class Square : public Shape {

public:
	int y;

	Square(int value) : y(value), Shape(value) { ; }
};

bool compareShape(const Shape * sh1, const Shape * sh2) {
	return sh1->name.compare(sh2->name);
}

class Movie;

class Person {

private:
	string  id; 
	vector<Movie *> movies;

public:
	Person( string str ) {
		id = str;
	}
	string  getId() 
	{
		return id;
	}

	//...you should do the rule of 3 !!!
	virtual ~Person(){
	}

	void addMovie( Movie * p ) {
		movies.push_back( p );
	}

};

class Movie {

private:
	string  id; 
	double  score = 0.0;
	int     year;
	vector<Person *> persons;

public:
	Movie( string str ) {
		id = str;
		//you should receive more informatio..year, ....
	}
	string  getId() 
	{
		return id;
	}

	double setScore(double pscore ) {
		this->score = pscore;
	}

	void addPerson( Person * p ) {
		persons.push_back( p );
	}
	//...you should do the rule of 3 !!!
	virtual ~Movie(){
	}
};

map<string, Person *> mapPersons;

map<string, Movie *> mapMovies;

void loadMovie(istream & is) {
	char buf[255]; //a literal must end by a binary zero '\0'
	while( is.getline(buf, 255) ){ //read data from file object and put it into string.
		string str( buf );
		Movie * m = new Movie( str );
		mapMovies.insert( pair<string, Movie *> (m->getId(), m ) );
	}
}

void loadPerson(istream & is) {
	char buf[255]; //a literal must end by a binary zero '\0'
	while( is.getline(buf, 255) ){ //read data from file object and put it into string.
		string str( buf );
		Person * p = new Person( str );
		mapPersons.insert( pair<string, Person *> (p->getId(), p ) );
	}
}

void loadPrincipal(istream & is) {
	char buf[255]; //a literal must end by a binary zero '\0'
	while( is.getline(buf, 255) ){ //read data from file object and put it into string.
		string str( buf );

		//...hard code lenght...for demo purpose only
		string mId = str.substr(0,1); 
		string pId = str.substr(2,3);

		auto itFindPerson = mapPersons.find( pId );

		string str1 = itFindPerson->first; //1st component of the pair
		Person * p = itFindPerson->second; //2nd component of the pair

		auto itFindMovie = mapMovies.find( mId );

		string str2 = itFindMovie->first; //1st component of the pair
		Movie * m = itFindMovie->second; //2nd component of the pair

		if ( p != nullptr && m != nullptr ) {
			p->addMovie( m );
			m->addPerson( p );
		}

	}
}



void loadDataSet() 
{

	//open the movie file (see week6)....it will be an istream
	string testMovieData(  "1\n2\n" );
	istringstream isMovie( testMovieData );
	
	loadMovie( isMovie );

	string testPersonData(  "100\n200\n" );
	istringstream isPerson( testPersonData );
	
	loadPerson( isPerson );

	//...loading the rating file, and calculate each movie score!!!
	//...

	//...loading the principal file
	//...
	string testPrincipalData(  "1,100\n1,200\n2,100\n" );
	istringstream isPrincipal( testPrincipalData );
	
	loadPrincipal( isPrincipal );
	//calculate each Person score...be careful with infinite reference !!!

	//output the result 
	//in the correct sorting order
}

int main()
{
	loadDataSet() ;


	//C++ is a typed language, each container is defined
	//to manage a specific type. With objects, you can have a container
	//specified for a superclass, but any of its subclasses can be 
	//manage by the containers
	vector<Shape *>  shapes;

	shapes.push_back(new Square(1) );
	shapes.push_back(new Square(2));
	shapes.push_back(new Square(3));

	vector <Shape> shapesFilled{ new Square(1),new Square(2) };

	//iterator, how to 
	//
	//begin -> is on the 1st element
	//end   -> is passed the last element
	//
	// [begin, end)
	//
	// containers are based on Template
	//
	//
	vector<Shape *>::iterator it; //to declare an iterator
	it = shapes.begin(); //1st element
	it = shapes.end();   //after the last element

	--it;  // ++ and -- operator, to move forward and backward
	cout << (*it)->x << endl;

	for (vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
		cout << ' ' << (*it)->x;
	}

	//to initialize with preset values
	const vector<string> MONTHS = { "january", "february", "march", "april" };

	//array vs vector
	//
	//fixed length, like native array
	//
	//but array are objects, which function and operator
	const array<int, 4> DAYS = { 31, 28, 31, 30 };

	array<int, 4> working_days;

	working_days = DAYS;

	//csc319b 
	vector<Shape *>  moreShapes;

	//will assign to moreShapes, the value from shapes (Shape *)
	//but starting at the 2nd item (the ++)
	moreShapes.assign(++(shapes.begin()), shapes.end());

	//swap, transfer from one container to another
	//
	swap(shapes, moreShapes);


	//container, supports <, >, ==
	//compares the value contains in the container, using the 
	//operator defines in the contained object

	//push_back vs push_front : at the end (last element), or before the 1st element

	//insert, at a specific location

	Shape * s = shapes.at(0); //vector starts at 0, can throw out_of_range exception

	//pop_back -> remove the 'top' element from the vector
	//pop_front -> remove the 1st element from the vector

	// adding or removing from a container, if there is an iterator
	// active on the container, it invalidates the iterator

	//it is possible to change the size of a container, with resize
	//but not for array
	//
	// if it is smaller, excess items are discarded
	// bigger,a second parameter to resize allow to set the default value
	moreShapes.resize(5);

	//why for vector and string, there is a size and a capacity ?
	//
	// optimizing memory management !
	//
	// a string keep has an internal buffer 
	// when you append a char, a new buffer needs to be allocated and then
	//recopied, a lot of memory management, new allocation and delete
	char * buffer = "0"; //2 chars !

	char * newbuffer = new char[3];
	memcpy(newbuffer, buffer, 2);
	newbuffer[1] = '1';
	newbuffer[2] = '\0';
	delete buffer;
	buffer = newbuffer;
	//if the buffer is preset to a larger buffer, it many not need to reallocate
	//the buffer
	//
	//capacity:  current size it can manages, otherwise it will grow the buffer
	//size: the current usage of the buffer

	//string: some functions will allocate new instance of the string
	//substring
	//
	//insert, erase, assign, append - manage by using the internal buffer
	//
	//some function allows to conver between string and native type stod:string to double
	//
	//http://www.cplusplus.com/reference/string/ section: Convert from strings
	//
	//adaptors : that allows container to be used like another container
	//http://en.cppreference.com/w/cpp/container/queue

	//associative container
	//
	// a key -> object
	//
	// StudentId -> object

	Square * mysquare = new Square(1);
	mysquare->name = "my square";

	//map : unique, multi-map : duplicate
	map<string, Shape *> myShapes;

	//pair: object to identify the key and the object it is mapping to
	myShapes.insert(pair<string, Shape *>(mysquare->name, mysquare));

	auto itFind = myShapes.find( mysquare->name );

	string str = itFind->first; //1st component of the pair
	Shape * findMyShape = itFind->second; //2nd component of the pair
	Square * findMySquare = (Square *) findMyShape; //not a good idea...
	cout << findMyShape->name << endl;
	//csc319a

	//some associative container requires a comparator to manage
	//to store the object it is mapping in a specific order
	//see compareShape

	//unordered associate containers -> based on a hash function and ==
	//
	//define your own custom hashing function p. 446

	//algorithms : common algo on container, sort, find
	//http://en.cppreference.com/w/cpp/algorithm

	int sum = accumulate(DAYS.begin(), DAYS.end(), 0); //will add all the value 
 
	//lambda 
	//
	//code as object that you can execute
	//
	//compareShape has a lambda, to sort shapes
	//
	// the last argument, is the lambda expression
	stable_sort(shapes.begin(), shapes.end(),
				[](const Shape * sh1, const Shape * sh2) 
				{ return sh1->name.compare(sh2->name); });
	
	return 0;

}