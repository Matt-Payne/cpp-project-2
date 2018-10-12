#include "../includes_usr/fileIO.h"
using namespace std;
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../includes_usr/constants.h"
#include "string.h"
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
using namespace std;
#include "../includes_usr/datastructures.h"
#include <sstream>
#include <cctype>
#include "../includes_usr/fileIO.h"
#include "../includes_usr/library.h"
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */

std::vector<string> saveBookLine;
std::vector<string> savePatronLine;
int loadBooks(std::vector<book> &books, const char* filename)
{	std::ifstream myfile;



	myfile.open(filename);
	if (!myfile){
		return COULD_NOT_OPEN_FILE;
	}

	if (myfile.peek() == std::ifstream::traits_type::eof()){
		return NO_BOOKS_IN_LIBRARY;
	}




	if (myfile){
		books.clear();
		while (!myfile.eof()){
				string line = "";
				book newBook;
				getline(myfile,line);
				//just save entire line
				saveBookLine.push_back(line);
				//newBook = line;
				// pull data from line and put into newBook
				string user (1,line[0]);
				stringstream geek(user);
				int x = 0;
				geek >> x;
				// book id
				newBook.book_id = x;
				bool checker = false;
				string tempTitle = "";
				for(int i = 0;i<line.size();i++){
					if(line[i] == '"' && checker == true){
						break;
					}
					if (checker == true){
						tempTitle = tempTitle + line[i];
					}
					if (line[i] == '"'){
						checker = true;
					}

				}
				newBook.title = tempTitle;
				checker = false;


				//loop to get author
				string tempAuthor = "";
				for(int i = 3;i < line.size();i++){
					if (checker == true && line[i-1] == '"'){
						while(line[i] != '"'){
							if(line[i] == '"'){
								checker = false;
								break;
							}
						tempAuthor  = tempAuthor + line[i];
							i++;
						}
					}
					if (line[0]==','){
						 checker = true;
					}
				}
				newBook.author = tempAuthor;

				//newBook.state = false;


				if (newBook.title != ""){
				books.push_back(newBook);
				}

			}

			return SUCCESS;
		} else {
			return COULD_NOT_OPEN_FILE;
		}



}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
	{ std::ofstream myfile;



	myfile.open(filename);
	if (!myfile){
		return COULD_NOT_OPEN_FILE;
	}



// later issue
//		if (myfile){
//			for (int i = 0; i < books.size();i++){
//				string build = "";
//				build = build + to_string(books[i].book_id);
//				build = build + to_string(',"');
//				build = build + books[i].title;
//				build = build + to_string('","');
//				build = build + books[i].author;
//				build = build + to_string('",1,-2');
//				myfile <<build + "\n";
//
//			}
//
//				return SUCCESS;
//			} else {
//				return COULD_NOT_OPEN_FILE;
//			}
	saveBookLine.pop_back();
	if (myfile){
				for (int i = 0; i < saveBookLine.size();i++){

					myfile << saveBookLine[i];
					if (saveBookLine.size() > i){
						myfile << "\n";
					}

				}

					return SUCCESS;
				} else {
					return COULD_NOT_OPEN_FILE;
				}



}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{	std::ifstream myfile;



	myfile.open(filename);
	if (!myfile){
		return COULD_NOT_OPEN_FILE;
	}

	if (myfile.peek() == std::ifstream::traits_type::eof()){
		return NO_PATRONS_IN_LIBRARY;
	}

	//std::fstream& myfile;
	patrons.clear();



	if (myfile){
		patrons.clear();
		while (!myfile.eof()){
			string line = "";
			patron newPatron;
			getline(myfile,line);
			savePatronLine.push_back(line);
			if (line != ""){
				string user (1,line[0]);
				stringstream geek(user);
				int x = 0;
				geek >> x;
				newPatron.patron_id = x;

				//get the name in
				int i = 2;
				string temp = "";
				while(line[i] != ','){
					temp  = temp + line[i];
					i++;
				}
				newPatron.name = temp;

				// read in num of books checked out
				string pow (1,line.back());
				stringstream mine(pow);
				int num = 0;
				mine >> num;

				newPatron.number_books_checked_out = num;


				patrons.push_back(newPatron);
			}

		}

		return SUCCESS;
	} else {
		return COULD_NOT_OPEN_FILE;
	}
	return SUCCESS;

}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{ std::ofstream myfile;



myfile.open(filename);
if (!myfile){
	return COULD_NOT_OPEN_FILE;
}



// later issue
//		if (myfile){
//			for (int i = 0; i < books.size();i++){
//				string build = "";
//				build = build + to_string(books[i].book_id);
//				build = build + to_string(',"');
//				build = build + books[i].title;
//				build = build + to_string('","');
//				build = build + books[i].author;
//				build = build + to_string('",1,-2');
//				myfile <<build + "\n";
//
//			}
//
//				return SUCCESS;
//			} else {
//				return COULD_NOT_OPEN_FILE;
//			}
	savePatronLine.pop_back();
	if (myfile){
			for (int i = 0; i < savePatronLine.size();i++){

				myfile << patrons[i].patron_id;
				myfile << ',';
				myfile << patrons[i].name;
				myfile << ',';
				myfile << patrons[i].number_books_checked_out;
				myfile << "\n";

			}

				return SUCCESS;
			} else {
				return COULD_NOT_OPEN_FILE;
			}
	return SUCCESS;


}
