#ifdef _MSC_VER 

#define _CRT_SECURE_NO_DEPRECATE

#else

#endif

#include "wordlist.h"
#include<iostream>
#include<cstring>

#define MAX_LENGTH 20 
// sorry if this isn't allowed

using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;

void swap(char*& a, char*& b) {
    char* temp = a;
    a = b;
    b = temp;
}


WordList::WordList(const int max_words)
{
    if (max_words < 1) { // checks if user wants 0 words
        m_list = nullptr;
        m_count = 0;
        m_max = max_words;
    }

    else { // Otherwise
        m_count = 0;
        m_max = max_words;
        m_list = new char* [m_max]; // allocate amount of memory user wants
        for (unsigned int i = 0; i < m_max; i++)
            m_list[i] = new char[MAX_LENGTH];
    }
}

WordList::~WordList() {


    for (unsigned int i = 0; i < m_max; i++) { delete[] m_list[i]; }

}

int WordList::add(const char word[]) { // double check for return values 

    if (word == "") return -1;

    else if (m_list == nullptr) {

        m_list = new char* [m_max + 1];
        for (unsigned int i = 0; i < m_max + 1; i++)
            m_list[i] = new char[MAX_LENGTH];

        strcpy(m_list[m_count], word);

        m_max++;
        m_count++;

        return 2;
    }
    else if (m_count == m_max) {

        char** templist = new char* [m_max + 1]; // temporary list for words with enought mem
        for (unsigned int i = 0; i < m_max + 1; i++)
            templist[i] = new char[MAX_LENGTH];

        for (unsigned int i = 0; i < this->m_count; i++) { // stores all current words to templist
            templist[i] = m_list[i];
        }

        strcpy(templist[m_count], word); // copies new word to last element of temp list

        m_list = new char* [m_max + 1]; // creates new list with enough memory

        for (unsigned int i = 0; i < this->m_max + 1; i++) { // stores all current words to templist
            m_list[i] = templist[i];
        }

        m_max++;
        m_count++;

        return 1;
    }
    else { // otherwise there's space left
        strcpy(this->m_list[m_count], word); // adds word to next available space
        m_count++;
        return 0;
    }

}

WordList::WordList(const WordList& temp)
    :m_count(temp.m_count), m_max(temp.m_max) // shallow copy of non pointer member variables
{
    m_list = new char* [m_max]; // allocates memory for new list
    for (unsigned int i = 0; i < m_max; ++i)
        m_list[i] = new char[MAX_LENGTH]; // sets all allocated memory to have 20 bytes of memory for chars

    for (unsigned int i = 0; i < m_count; i++) { //gives new list the value of list in parameter
        for (unsigned int j = 0; j < strlen(m_list[i]); j++)
            m_list[i][j] = temp.m_list[i][j]; // copies all chars individually
    }

}

int	WordList::print() const {

    int wordcount = 0;
    if (m_list == nullptr) return -1;
    else { // prints list of words

        for (unsigned int i = 0; i < m_count; i++) {
            std::cout << m_list[i] << " ";
            if (i == m_count - 1) {
                std::cout << std::endl;
            }
            wordcount++;
        }
    }

    return wordcount; // returns amount of words in list.
}

int WordList::count() const { return m_count; } // returns amount of words in list

int WordList::remove(const char word[]) {

    int words_removed = 0;

    if (m_list == nullptr) { return -1; } // checks if list was set as nullptr
    else { // Otherwise

        for (unsigned int i = 0; i < m_count; i++) {

            if (strcmp(m_list[i], word) == 0) { //check if current index in loop is equal to the word specified in parameter
                delete[] m_list[i]; // delete the value in current index
                words_removed++;
                for (unsigned int j = i; j < m_count; j++) { // move all the values after it to its own value - 1
                    m_list[j] = m_list[j + 1];
                }m_count--; m_list[m_count] = nullptr; // accounts for removed word
            }
        }
    }

    return words_removed;

}

char* WordList::at(const int index) const {

    if (index > m_count || index < 0) {
        std::cout << "index > m_count: " << std::endl; // prints word at specified index
        return nullptr;
    }
    else return m_list[index];

}

int WordList::append(const WordList* src_list) {

    if (src_list->m_list == nullptr) { return 0; }

    unsigned int available_space = (m_max - m_count);
    unsigned int needed_space = src_list->m_count;
    char** temp_ptr = m_list;

    if (available_space < needed_space) { // if more space is needed


        char** templist = new char* [m_max + (needed_space - available_space)]; // temporary list for words with enought mem

        for (unsigned int i = 0; i < this->m_count; i++) { // stores all current words to templist
            templist[i] = m_list[i];
        }

        for (unsigned int i = this->m_count, j = 0; i < m_max + (needed_space - available_space); i++, j++) { // stores all of the 2nd list's words in templist
            templist[i] = src_list->m_list[j];
        }

        for (unsigned int i = 0; i < src_list->m_count; i++)
            src_list->m_list[i] = nullptr;

        this->m_list = new char* [m_max + (needed_space - available_space)]; // creates new list with enough memory

        for (unsigned int i = 0; i < m_max + (needed_space - available_space); i++) { // stores all current words to templist
            this->m_list[i] = templist[i];
        }

        m_max += needed_space;
        m_count += needed_space;
    }
    else if (available_space >= needed_space) { // if there's space


        for (unsigned int i = (m_count), j = 0; j < src_list->m_count; i++, j++) {
            (m_list[i] = (src_list->m_list[j]));
        }
        m_count += src_list->m_count;

        for (unsigned int i = 0; i < src_list->m_count; i++)
            src_list->m_list[i] = nullptr;
    }

    if (temp_ptr == nullptr) { return -1; }
    else
        return src_list->m_count;

}

int WordList::search(const char word[]) const {
    if (m_list == nullptr) { return -1; }
    else {
        for (unsigned int i = 0; i < m_count; i++) {
            if (strcmp(m_list[i], word) == 0) {
                return i;
            }
        }
        return -1;
    }
}

int WordList::sort() {

    if (m_list == nullptr) { return -1; } // checks if m_list is equal to nullptr returns -1 if it is
    else if (m_count == 1) { return 1; } //  checks if there's only one word
    else {
        int sorted = 0;
        while (!sorted) { // while not sorted
            sorted = 1;
            for (unsigned int i = 0, j = 0; i < m_count - 1; ) {
                if ((toupper(m_list[i][j])) == toupper(m_list[i + 1][j])) { // if the chars are equal
                    j++;
                }
                else if ((toupper(m_list[i][j])) < toupper(m_list[i + 1][j])) { // if chars are in order
                    i++; j = 0;
                }

                else if ((toupper(m_list[i][j])) > toupper(m_list[i + 1][j])) // if chars aren't in order
                {
                    swap(m_list[i], m_list[i + 1]);
                    i++;
                    j = 0;
                    sorted = 0;
                }

            }
        }
    }
    return 0;
}

WordList& WordList::operator=(const WordList& other) {

    m_count = other.m_count;
    m_max = other.m_max;

    if (this == &other) return *this;
    else {
        m_list = new char* [m_max]; // allocates memory for new list
        for (unsigned int i = 0; i < m_max; ++i)
            m_list[i] = new char[MAX_LENGTH]; // sets all allocated memory to have 20 bytes of memory for chars

        for (unsigned int i = 0; i < m_count; i++) { //gives new list the value of list in parameter
            for (unsigned int j = 0; j < strlen(m_list[i]); j++)
                m_list[i][j] = other.m_list[i][j]; // copies all chars individually
        }

        return *this;
    }
}

//int WordList::max() const { return m_max; } // returns amount of memory allocated for






