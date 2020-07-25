#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct word_reader : std::ctype<char> {
	word_reader(std::string const& delims) : std::ctype<char>(get_table(delims)) {}
	static std::ctype_base::mask const* get_table(std::string const& delims) {
		static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());

		for (char ch : delims)
			rc[ch] = std::ctype_base::space;
		return &rc[0];
	}
};

class Date {
private:
	int day = -1;
	int month = -1;
	int year = -1;
public:
	Date() {
		setDay();
		setMonth();
		setYear();
	}

	void setDay() {
		cout << "Enter day: " << endl;
		while (day <= 0 || day > 31) {
			cin >> this->day;
		}
	}
	void setMonth() {
		cout << "Enter month: " << endl;
		while (month <= 0 || month > 12) {
			cin >> this->month;
		}
	}
	void setYear() {
		cout << "Enter year: " << endl;
		while (year <= 0 || year > 2020) {
			cin >> this->year;
		}
	}

	int getDay() { return this->day; }
	int getMonth() { return this->month; }
	int getYear() { return this->year; }

	friend std::ostream& operator<<(std::ostream& out, Date& date)
	{
		out << date.getDay() << "." << date.getMonth() << "." << date.getYear();
		return out;
	}

	virtual ~Date() { /*cout << "Object Date is destroyed!" << endl;*/ };
};

class SchoolBook {
private:
	string title;
	vector<string> authors;
	int edition = -1;
	int ISBN = -1;
	int numberOfCopies = -1;
	double priceInLeva = 0.0;
	string authorization;
	Date* releaseDate;
	Date* authorizationDate;
public:
	SchoolBook() {
		setTitle();
		setAuthors();
		setEdition();
		setISBN();
		setNumberOfCopies();
		setPriceInLeva();
		setAuthorization();
		setReleaseDate();
	}

	void setTitle() {
		cout << "Enter title: " << endl;
		cin >> this->title;
	}
	void setAuthors() {
		string author;
		cout << "Enter authors. Enter * when you are done: " << endl;
		while (cin >> author && author != "*") {
			authors.push_back(author);
		}
	}
	void setEdition() {
		cout << "Enter edition: " << endl;
		while (edition <= 0) {
			cin >> this->edition;
		}
	}
	void setISBN() {
		cout << "Enter ISBN: " << endl;
		while (ISBN <= 0) {
			cin >> this->ISBN;
		}
	}
	void setNumberOfCopies() {
		cout << "Enter Number of copies: " << endl;
		while (numberOfCopies <= 0) {
			cin >> this->numberOfCopies;
		}
	}
	void setPriceInLeva() {
		cout << "Enter Price of Book in Leva: " << endl;
		while (priceInLeva <= 0.0) {
			cin >> this->priceInLeva;
		}
	}
	void setAuthorization() {
		cout << "Enter authorization(true or false): " << endl;
		while (cin >> this->authorization) {
			if (authorization == "false") {
				break;
			}
			else if (authorization == "true") {
				setAuthorizationDate();
				break;
			}
		}
	}
	void setReleaseDate() {
		cout << "Enter Release Date:" << endl;
		this->releaseDate = new Date();
	}
	void setAuthorizationDate() {
		cout << "Enter Authorization Date:" << endl;
		this->authorizationDate = new Date();
	}

	string getTitle() { return this->title; }
	vector<string> getAuthors() { return this->authors; }
	int getEdition() { return this->edition; }
	int getISBN() { return this->ISBN; }
	int getNumberOfCopies() { return this->numberOfCopies; }
	double getPriceInLeva() { return this->priceInLeva; }
	string getAuthorization() { return this->authorization; }
	Date* getReleaseDate() { return this->releaseDate; }
	Date* getAuthorizationDate() { return this->authorizationDate; }

	friend void writeSchoolBookInFile(const SchoolBook& schoolBook);
	friend void readSchoolBooksFromFile();
	friend void selectSchoolBooks();
	friend void purchaseBooks(ifstream& myFile, vector<string> books);

	friend std::ostream& operator<<(std::ostream& out, SchoolBook schoolBook) {
		out << schoolBook.getTitle() << ", " << schoolBook.getEdition() << ", " << schoolBook.getISBN()
			<< ", " << schoolBook.getReleaseDate()->getDay() << "." << schoolBook.getReleaseDate()->getMonth() << "." << schoolBook.getReleaseDate()->getYear()
			<< ", " << schoolBook.getNumberOfCopies() << ", " << schoolBook.getAuthorization() << ", " << schoolBook.getAuthorizationDate() << schoolBook.getPriceInLeva()
			<< endl;
		return out;
	}
	virtual ~SchoolBook() { /*cout << "Object SchoolBook is destroyed!" << endl;*/ };
};

class BookDistributor {
private:
	string name;
	string address;
	string phoneNumber;
public:
	BookDistributor() {
		setName();
		setAddress();
		setPhoneNumber();
	}
	void setName() {
		cout << "Enter name of Book distributor: " << endl;
		cin >> this->name;
	}
	void setAddress() {
		cout << "Enter address: " << endl;
		cin >> this->address;
	}
	void setPhoneNumber() {
		cout << "Enter phone number starts with '0'(10 digits): " << endl;
		while (cin >> this->phoneNumber) {
			if (phoneNumber.size() == 10 && phoneNumber.rfind("0", 0) == 0) {
				break;
			}
		}
	}

	string getName() { return this->name; }
	string getAddress() { return this->address; }
	string getPhoneNumber() { return this->phoneNumber; }

	friend void writeBookDistributorInFile(const BookDistributor& bookDistributor);
	friend void readBookDistributorsFromFile();
	friend void selectDistributor();

	friend std::ostream& operator<<(std::ostream& out, BookDistributor& bookDistributor) {
		out << bookDistributor.getName() << ", " << bookDistributor.getAddress() << ", " << bookDistributor.getPhoneNumber() << endl;
		return out;
	}
	virtual ~BookDistributor() { /*cout << "Object BookDistributor is destroyed!" << endl;*/ };
};

void writeSchoolBookInFile(const SchoolBook& schoolBook) {
	ofstream ofStreamWriter1("SchoolBooks.txt", std::ios_base::app);

	ofStreamWriter1 << "Title: " << schoolBook.title
		<< ", Edition: " << schoolBook.edition << ", ISBN: " << schoolBook.ISBN
		<< ", Release Date: " << schoolBook.releaseDate->getDay() << "." << schoolBook.releaseDate->getMonth() << "." << schoolBook.releaseDate->getYear()
		<< ", Copies: " << schoolBook.numberOfCopies << ", Authorization: " << schoolBook.authorization;
	if (schoolBook.authorization == "true") {
		ofStreamWriter1 << ", Authorization Date: "
			<< schoolBook.authorizationDate->getDay() << "." << schoolBook.authorizationDate->getMonth() << "." << schoolBook.authorizationDate->getYear();
	}
	ofStreamWriter1 << ", Price in Leva: " << schoolBook.priceInLeva << endl;
	ofStreamWriter1.close();
}

void purchaseBooks(ifstream& myfile, vector<string> books) {
	ofstream ofStreamWriter2("Orders.txt", std::ios_base::app);
	string fileLine, book;
	vector<string> vect;
	double finalPrice = 0;
	int flag = 0;

	for (auto elem : books) {
		while (getline(myfile, fileLine)) {
			istringstream streamLineSchoolBook(fileLine);
			streamLineSchoolBook.imbue(std::locale(std::locale(), new word_reader(" ,:")));
			while (streamLineSchoolBook >> book) {
				if (book == elem) {
					ofStreamWriter2 << "Book: " << fileLine << endl;
					flag = 1;

					stringstream ss(fileLine);
					for (string i; ss >> i;) {
						vect.push_back(i);
						if (ss.peek() == ',' || ss.peek() == ':' || ss.peek() == ' ')
							ss.ignore();
					}
					finalPrice += atof(vect[vect.size() - 1].c_str());
				}
			}
		}
		myfile.clear();
		myfile.seekg(0, myfile.beg);
	}
	if (flag == 0) {
		ofStreamWriter2 << "Book: no Book selected" << endl;
	}
	else {
		ofStreamWriter2 << "Final price of Order: " << finalPrice << endl;
	}
	ofStreamWriter2.close();
}

void selectSchoolBooks() {
	string input;
	vector<string> books;
	ifstream myfile;
	myfile.open("SchoolBooks.txt");

	cout << "--------------------" << endl;

	cout << "Enter SchoolBooks you want to buy. Enter * when you are done: " << endl;
	while (cin >> input && input != "*") {
		books.push_back(input);
	}

	if (myfile.is_open()) {
		purchaseBooks(myfile, books);
	}
	else {
		perror("Error open");
		exit(0);
	}
	myfile.close();
}

void readSchoolBooksFromFile() {
	string fileLine;
	ifstream myfile;
	myfile.open("SchoolBooks.txt");

	cout << "--------------------" << endl;

	if (myfile.is_open()) {
		while (getline(myfile, fileLine)) {
			cout << fileLine << endl;
		}
	}
	else {
		perror("Error open");
		exit(0);
	}
	myfile.close();
	selectSchoolBooks();
}

void writeBookDistributorInFile(const BookDistributor& bookDistributor) {
	ofstream ofStreamWriter2("BookDistributors.txt", std::ios_base::app);

	ofStreamWriter2 << "Distributor: " << bookDistributor.name << ", Address: " << bookDistributor.address << ", Phone number: " << bookDistributor.phoneNumber << endl;
	ofStreamWriter2.close();
}

void saveBookDistributor(ifstream& myfile, string input) {
	ofstream ofStreamWriter2("Orders.txt", std::ios_base::app);
	string fileLine, distributor;
	int flag = 0;

	while (getline(myfile, fileLine)) {
		istringstream streamLineDistributor(fileLine);
		locale s = streamLineDistributor.imbue(std::locale(std::locale(), new word_reader(" ,:")));
		while (streamLineDistributor >> distributor) {
			if (distributor == input) {
				ofStreamWriter2 << "Order: " << endl << fileLine << endl;
				flag = 1;
			}
		}
	}

	if (flag == 0) {
		ofStreamWriter2 << "Order: " << endl << "Distributor: no Distributor selected." << endl;
	}
	ofStreamWriter2.close();
}

void selectDistributor() {
	string input;
	ifstream myfile;
	myfile.open("BookDistributors.txt");

	cout << "--------------------" << endl;

	cout << "Enter Book Distributor: " << endl;
	cin >> input;

	if (myfile.is_open()) {
		while (!myfile.eof()) {
			saveBookDistributor(myfile, input);
		}
	}
	else {
		perror("Error open");
		exit(0);
	}
	myfile.close();
}

void readBookDistributorsFromFile() {
	string fileLine;
	ifstream myfile;
	myfile.open("BookDistributors.txt");

	cout << "--------------------" << endl;

	if (myfile.is_open()) {
		while (getline(myfile, fileLine)) {
			cout << fileLine << endl;
		}
	}
	else {
		perror("Error open");
		exit(0);
	}
	myfile.close();
	selectDistributor();
}

int main() {
	string option;

	printf("Welcome!\n");
	for (;;) {
		cout << "---------------------------------\n";
		cout << "Option 1: Add new School Book\n";
		cout << "Option 2: Add new Book Distributor\n";
		cout << "Option 3: Select Distributor and Purchase books\n";
		cout << "Option 0: Exit\n";
		cout << "\nChoose an option: ";

		cin >> option;

		if (option == "1") {
			SchoolBook schoolBook;
			writeSchoolBookInFile(schoolBook);
			//cout << schoolBook;
		}
		else if (option == "2") {
			BookDistributor bookDistributor;
			writeBookDistributorInFile(bookDistributor);
			//cout << bookDistributor;
		}
		else if (option == "3") {
			readBookDistributorsFromFile();
			readSchoolBooksFromFile();
		}
		else if (option == "0") {
			exit(0);
		}
		else {
			printf("Incorrect input! Try again!\n");
		}
	}
	return 0;
}