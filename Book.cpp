// Donghui feng, Tianhao Shen, Site Wei
// CPSC 131
// 09-05-2020
// Project 0 Group 21

#include "Book.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

// give the definition of member function
std::string Book::isbn() const { return _isbn; }
std::string Book::title() const { return _title; }
std::string Book::author() const { return _author; }

double Book::price() const { return _price; }

// initial the strings in constructors when creat an object
Book::Book(std::string_view title, std::string_view author,
           std::string_view isbn, double price) {
  _title = title;
  _author = author;
  _isbn = isbn;
  _price = price;
}

// get the value and change the object value to it.
void Book::isbn(std::string_view newIsbn) { _isbn = newIsbn; }

void Book::title(std::string_view newTitle) { _title = newTitle; }

void Book::author(std::string_view newAuthor) { _author = newAuthor; }

void Book::price(double newPrice) { _price = newPrice; }

// overload the stream in operator to read the file use char common to separate
// the txt.
std::istream& operator>>(std::istream& stream, Book& book) {
  Book PickBook;

  char delim1 = ',';
  stream >> std::quoted(PickBook._isbn) >> delim1 >>
      std::quoted(PickBook._title) >> delim1 >> std::quoted(PickBook._author) >>
      delim1 >> PickBook._price;

  if (stream) book = std::move(PickBook);

  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Book& book) {
  const std::string delim2 = ", ";
  stream << std::quoted(book.isbn()) << delim2 << std::quoted(book.title())
         << delim2 << std::quoted(book.author()) << delim2 << book.price();

  return stream;
}

// overload the operator
bool operator==(const Book& lhs, const Book& rhs) {
  if constexpr ((false)) {
    return !(lhs < rhs) && !(rhs < lhs);
  } else {
    return lhs._isbn == rhs._isbn && lhs._title == rhs._title &&
           lhs._author == rhs._author &&
           std::abs(lhs._price - rhs._price) < 1E-4;
  }
}

bool operator<(const Book& lhs, const Book& rhs) {
  if (auto result = lhs._isbn.compare(rhs._isbn); result != 0)
    return result < 0;
  if (auto result = lhs._author.compare(rhs._author); result != 0)
    return result < 0;
  if (auto result = lhs._title.compare(rhs._title); result != 0)
    return result < 0;

  if (std::abs(lhs._price - rhs._price) >= 1E-4) return lhs._price < rhs._price;

  return false;
}

bool operator!=(const Book& lhs, const Book& rhs) { return !(lhs == rhs); }

bool operator<=(const Book& lhs, const Book& rhs) {
  return !(rhs < lhs);  // make a reverse to prevent function call itself
}

bool operator>(const Book& lhs, const Book& rhs) {
  return (rhs < lhs);  // make a reverse > to < to prevent function call itself
}

bool operator>=(const Book& lhs, const Book& rhs) { return !(lhs < rhs); }
