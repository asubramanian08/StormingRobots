#include <iostream>
#include <string>
using namespace std;

//ch rev. q3
void iqoute(int x) {
	cout << '"' << x << '"';
}
void iqoute(double x) {
	cout << '"' << x << '"';
}
void iqoute(string x) {
	cout << '"' << x << '"';
}
//general version
template <class T> void iquote(T x) {
	cout << '"' << x << '"';
}

//ch rev. q4
struct box
{
	char maker[40];
	float height;
	float width;
	float length;
	float volume;
};
void displayBox(box& x) {
	cout << "The maker is: " << x.maker << endl;
	cout << "The height is: " << x.height << endl;
	cout << "The width is: " << x.width << endl;
	cout << "The length is: " << x.length << endl;
	cout << "The volume is: " << x.volume << endl;
}
void setVol(box& x) {
	x.volume = x.height * x.width * x.length;
}

//ch rev. q6 (answers commented below)
/* a: defaul arguments
   double mass(double density, double volume = 1.0);
   b: function overloading
   void repeat(int rep, const char* str);
   void repeat(const char* str);
   c: function overloading / if option: templates
   int average(int x, int y);
   double average(double x, double y);
   d: neither writer can change -> can't do this
   */

//ch rev q7
template <class T> T larger(T x, T y) {
	return x > y ? x : y;
}

//ch rev q8
template <> box larger<box>(box x, box y) {
	return x.volume > y.volume ? x : y;
}

//pro. ex. q3
void cap_str(string& str) {
	unsigned int strLen = str.length();
	for (unsigned int i = 0; i < strLen; i++)
		str[i] = toupper(str[i]);
}

//pro. ex. q5
#define ARR_LEN 5
template<class T>T max5(const T arr[ARR_LEN]) {
	T greatest;
	if (ARR_LEN != 0) {
		greatest = arr[0];
		for (unsigned int i = 1; i < ARR_LEN; i++)
			greatest = __max(arr[i], greatest);
	}
	return greatest;
}

//pro. ex. q6
template<class T>T maxn(const T arr[], unsigned int n_el) {
	T greatest;
	if (n_el != 0) {
		greatest = arr[0];
		for (unsigned int i = 1; i < n_el; i++)
			greatest = __max(arr[i], greatest);
	}
	return greatest;
}
template<> char* maxn<char*>(char* const arr[], unsigned int n_el) {
	if (n_el == 0)
		return NULL;
	char* longest = arr[0];
	unsigned int lngt_len = strlen(longest), curr_len;
	for (unsigned int i = 1; i < n_el; i++) {
		curr_len = strlen(arr[i]);
		if (lngt_len < curr_len) {
			lngt_len = curr_len;
			longest = arr[i];
		}
	};
	return longest;
}

int main(void) {
	//pro. ex. q3
	/*string str;
	while (true) {
		cout << "Enter a string to capitolize " << "(q to quit): ";
		cin >> str;
		if (str.compare("q") != 0) {
			cap_str(str);
			cout << str << endl;
		}
		else {
			cout << "Quit recognized" << endl;
			break;
		}
	}
	cout << "String capitolization game complete!" << endl << endl;

	//pro. ex. q5 testing
	cout << "Starting integer's program" << endl;
	int* arr_int = new int[ARR_LEN];
	for (unsigned int i = 0; i < ARR_LEN; i++) {
		cout << "Enter number " << (i + 1) << " in the array(integer): ";
		cin >> arr_int[i];
	}
	cout << "The program for integers returned " << max5(arr_int) << endl;
	delete[] arr_int;
	cout << "Starting double's program" << endl;
	double* arr_doub = new double[ARR_LEN];
	for (unsigned int i = 0; i < ARR_LEN; i++) {
		cout << "Enter number " << (i + 1) << " in the array(double): ";
		cin >> arr_doub[i];
	}
	cout << "The program for doubles returned " << max5(arr_doub) << endl;
	delete[] arr_doub;
	cout << "Greatest in array of size " << ARR_LEN << " (max5) test complete!" << endl << endl;
	*/
	//pro. ex. q6
#define INT_ARR_LEN 6
#define DOUB_ARR_LEN 4
#define STR_ARR_LEN 5
#define MAX_STR 100
	/*cout << "Starting integer's program" << endl;
	int* int_arr = new int[INT_ARR_LEN];
	for (unsigned int i = 0; i < INT_ARR_LEN; i++) {
		cout << "Enter number " << (i + 1) << " in the array(integer): ";
		cin >> int_arr[i];
	}
	cout << "The program for integers returned " << maxn(int_arr, INT_ARR_LEN) << endl;
	delete[] int_arr;
	cout << "Starting double's program" << endl;
	double* doub_arr = new double[DOUB_ARR_LEN];
	for (unsigned int i = 0; i < DOUB_ARR_LEN; i++) {
		cout << "Enter number " << (i + 1) << " in the array(double): ";
		cin >> doub_arr[i];
	}
	cout << "The program for doubles returned " << maxn(doub_arr, DOUB_ARR_LEN) << endl;
	delete[] doub_arr;*/
	cout << "Starting string's program" << endl;
	char** str_arr = new char*[STR_ARR_LEN];
	unsigned int strLen;
	for (unsigned int i = 0; i < STR_ARR_LEN; i++) {
		cout << "Enter number " << (i + 1) << " in the array(string): ";
		str_arr[i] = new char[MAX_STR];
		cin.getline(str_arr[i], MAX_STR, '\n');
 	}
	cout << "The program for strings returned " << maxn(str_arr, STR_ARR_LEN) << endl;
	for (unsigned int i = 0; i < STR_ARR_LEN; i++)
		delete[] str_arr[i];
	delete[] str_arr;
	cout << "Greatest in array of size n (maxn) test complete!" << endl << endl;

	return 0;
}