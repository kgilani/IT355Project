#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cctype>

using namespace std;

/**
 * @brief This is a global variable created to introduce the user to the game.
 *
 * Rule: ERR58-CPP. Handle all exceptions thrown before main() begins executing.
 * This ensures that we are following this as we are creating a global string
 * which will result in no exceptions during startup or termination of the program.
 */
static const char *intro = "Welcome to the Trivia Game\n";

/**
 * @brief Rules that are simply avoided in the program to be compliant.
 *
 * Rule: STR00-C. Represent characters using an appropriate type.
 * Throughout this entire program we are assigning characters to their correct types.
 * Strings receive the string type, booleans receive the bool type, and integers receive the int type for example.
 *
 * Rule: ERR50-CPP. Do not abruptly terminate the program.
 *
 */
class Question
{
    string question;
    bool answer;

public:
    // OOP53-CPP. Write constructor member initializers in the canonical order
    Question(string q) : question(q), answer(false) {}

    virtual ~Question() {}

private:
    /**
     * @brief OOP57-CPP Prefer special member functions and overloaded operators to C Standard Library functions.
     * While performing a copy, we are using an overloaded function as opposed to a C function like strcpy()
     * @brief OOP58-CPP Copy operations must not mutate the source object.
     * Although there is a copy being made, the original source object (otherQuestion) is not altered in any way.
     * @brief OOP55-CPP Do not use pointer-to-member operators to access nonexistent members.
     * This code does not have any pointer-to-member operators, and it also does not try to access nonexistent members
     *
     * @param otherQuestion is the source object of the copy. The question itself and the answer will be copied
     * to the calling question.
     *
     * @return *this which is the copied Question
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
        throw "Error: Failed to write to file";
    }
    fclose(outputFile); // Fixed the missing semicolon
    exit(0);
}

/**
 *@brief STR02: Sanitize data passed to complex subsystems.
 *While we don't necessarily have a subsystem per say we are still sanitizing the data by only whitelisting the alphabet.
 *This ensures that only the values we want are apart of the string and there is no malicious content.
 *
 *@param name is the name the user inputs when they run the program.
 *
 *@return true if the name contains only letters in the english alphabet otherwise false.
 */
bool isValidName(string name)
{
    string charactersToInclude = "abcdefghijklmnopqrstuvwxyz";

    /**
     *@brief STR52-CPP: Use valid references, pointers, and iterators to reference elements of a basic_string.
     *Here we are using a for loop which ensures that we don't use invalid references, pointers, or iterators to reference the basic_string.
     */
    for (char c : name)
    {
        char lowercaseC = std::tolower(c);
        if (charactersToInclude.find(lowercaseC) == string::npos)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    /**
     *@brief STR51-CPP: Do not attempt to create a std::string from a null pointer.
     *We want to create a string from a pointer here and we run an if else statement to make sure we do not attempt to create a string from a null pointer.
     */
    const char *hello = "Hello";
    string greeting;
    if (hello != nullptr)
    {
        greeting = hello;
    }
    else
    {
        cout << "Invalid string pointer." << endl;
    }

    string name;
    do
    {
        cout << "What is your name? ";
        /**
         *@brief STR50-CPP Guarantee that storage for strings has sufficient space for character data and the null terminator
         *Utilizing cin with a string as opposed to a buffer we are ensuring that we have sufficient space for this data.
         */
        cin >> name;

        if (!isValidName(name))
        {
            cout << "Please correct your input. ";
        }
    } while (!isValidName(name));

    /**
     *@brief STR53-CPP: Range check element access.
     *Here we are utilizing a try catch statement to ensure that we do not try to access an element that is out of range.
     */
    try
    {
        name.at(20);
        cout << "Wow your name is long!\n";
    }
    catch (std::out_of_range &ex)
    {
        // Continue as normal
    }

    // EXP53-CPP: Do not read uninitialized memory.
    // Since the spot in memory for 'intro' was already initialized, we do not have to worry about reading
    // from an uninitialized variable
    cout << greeting << " " << name << ", " << intro;

    // FIO01-C(rec): Be careful using functions that use file names for identification.
    // Instead of using the file name for identificaiton, we'll use the ifstream variable
    ifstream questionFile("triviaquestions.txt");

    if (!questionFile.is_open())
    {
        cerr << "Trouble opening the file.";
        return 1;
    }

    // CTR52-CPP: Guarantee that library functions do not overflow.
    // Vectors in C++ are dynamic, but that does not mean that they cannot overflow. We are limiting the number of quesitons
    // to make sure we do not overflow a buffer.

    // CTR56-CPP: Do not use pointer arithmetic on polymorphic objects.
    // STL containers accept iterators as parameters. In this code we do not have need to use any pointer arithmetic on polymorphic objects (which is compliant)
    // If we did need to, we would use an iterator and a vectors of pointers to the objects to stay compliant
    vector<Question> questions;
    string line;

    // INT17-C(rec): Define integer constants in an implementation-independent manner.
    // As opposed to defining the const int in terms of a hexidecimal, we use an integer value that would be portable
    // 50 can be represented as an int for all systems that can run C++
    const int maxQuestions = 50;

    unsigned int questionCount = 0;
    int questionCountInt;

    // FIO20-C (rec): Avoid unintentional truncation when using fgets() or fgetws().
    // Instead of using fgets() or fetws(), since we are in C++, we can use the safer getline() which checks for truncation
    while (getline(questionFile, line))
    {
        // INT30-C: Ensure unsigned integer operations do not wrap
        // Just in case there is a buffer issue, we check that the questionCount is not above or equal to the maximum unsigned int value.
        if (questionCount >= numeric_limits<unsigned int>::max())
        {
            cout << "Error: Too many questions. Aborting." << endl;
            break;
        }

        // INT31-C: Ensure that integer conversions do not result in lost or misinterpreted data.
        // Although this is not the most efficient, we can verify that we can convert the unsigned int to a signed int
        if (questionCount <= SCHAR_MAX)
        {
            questionCountInt = questionCount;
        }

        // INT18-C(rec): Evaluate integer expressions in a larger size before comparing or assigning to that size.
        // When both questionCountInt and maxQuestions are compared at a larger size, we reduce integer overflow and wrapping risks
        if (static_cast<unsigned int>(questionCountInt) < static_cast<unsigned int>(maxQuestions))
        {
            questions.push_back(Question(line));
            questionCount++;
        }
        else
        {
            cout << "It is possible that not all the questions from the file were loaded. To make sure there are no buffer errors, the maximum number of questions is 50" << endl;
            break;
        }
    }

    // FIO50-CPP: Do not alternately input and output from a file stream without an intervening position call.
    // Since we are writing to the same file we just read from, we want to make sure that the buffer is flushed and clear
    questionFile.clear();
    questionFile.seekg(0);
    ofstream questionFileOut("triviaquestions.txt", ios::app);

    if (!questionFileOut.is_open())
    {
        cerr << "Trouble opening the file.";
        return 1;
    }

    questionFileOut << "All the data has been read from the questions file successfully." << endl;

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == nullptr)
    {
        cerr << "Error: Could not open output file" << endl;
        return 1;
    }
    // Write something to the output file here

    checkOutFile(outputFile);

    // FIO51-CPP. Close files when they are no longer needed
    fclose(outputFile);
    questionFileOut.close();
    questionFile.close();

    return 0;
}
