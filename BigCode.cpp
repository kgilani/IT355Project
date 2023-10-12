#include "BigCode.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>

using namespace std;

/**
 *@brief This is a global variable created to introduce the user to the game.
 *
 *Rule: ERR58-CPP. Handle all exceptions thrown before main() begins executing.
 *This ensures that we are following this as we are creating a global string
 *which will result no exceptions during startup or termination of the program
 */
static const char *intro = "Welcome to the Trivia Game\n";

/**
 *@brief Rules that are simply avoided in the program to be compliant.
 *
 *Rule: ERR50-CPP. Do not abruptly terminate the program.
 *
 */
class Question
{
    string question;
    bool anwser;

public:
    // OOP53-CPP. Write constructor member initializers in the canonical order
    Question(string q) : question(q), anwser() virtual ~Question() { deleteQuestion(); }

protected:
private:
    /**
     *@brief OOP57: Prefer special member functions and overloaded operators to C Standard Library functions.
     *while performing a copy, we are using an overloaded function as opposed to a C function like strcpy()
     *@brief OOP58: Copy operations must not mutate the source object.
     *Altough there is a copy being made, the original source object (otherQuestion)is not altered in any way
     *
     *@param otherQuestion is the source object of the copy. The question itself and the answer will be copied
     *to the calling question
     *
     *@return *this which is the copied Question
     */
    Question &operator=(const Question &otherQuestion)
    {
        if (this != &otherQuestion)
        {
            question = otherQuestion.question;
            answer = otherQuestion.answer;
        }
        return *this;
    }
};

// MSC53-CPP. Do not return from a function declared [[noreturn]]
[[noreturn]] void checkOutFile(FILE *outputFile)
{
    // ERR01-C Use ferror() rather than errno to check for FILE stream errors
    if (ferror(outputFile))
    {
        throw "Error: Failed to write to file" fclose(outputFile)
    }
    exit(0);
}

string checkName(string name)
{
    string output;

    // STR52-CPP: Use valid references, pointers, and iterators to reference elements of a basic_string
    for (char c : name)
    {
        if (c != "a", "b", "c")
    }
}

int main()
{
    // STR50-CPP: Guarantee that storage for strings has sufficient space for character data and the null terminator
    string name;
    cout << "What is your name? ";
    cin >> name;
    checkName(name);

    // EXP53-CPP: Do not read uninitialized memory.
    // Since the spot in memory for 'intro' was already initialized, we do not have to worry about reading
    // from an uninitialized variable
    cout << "Hello " << name << ", " << intro;

    // FIO01-C: Be careful using functions that use file names for identification.
    //
    ifstream questionFile("triviaquestions.txt");

    if (!"triviaquestions.txt".is_open())
    {
        cerr << "Trouble opening the file." return (1);
    }

    vector<Question> questions;
    while (!questionFile.eof())
    {
        Question questions;

        // FIO20-C: Avoid unintentional truncation when using fgets() or fgetws().
        // Luckily, C++ was prepared for issues that C wasn't prepared for. Although, we could use fgets()
        // and check for trunctation, we can simply use C++'s getline() which is much safer and checks
        // truncation for us
        questionFile.getline();
    }

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile = nullptr)
    {
        cerr << "Error: Could not open output file" << endl;
        return 1;
    }
    // write something to output file here

    checkOutFile(outputFile);

    // FIO51-CPP. Close files when they are no longer needed
    fclose(outputFile);

    return 0;
}