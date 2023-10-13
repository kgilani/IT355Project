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

  //ERR58-CPP: Handle all exceptions thrown before main() begins executing
    try {
        //opening the file?
    } catch (const exception& e) {
        cerr << "Exception before or during main: " << e.what() << endl;
        return EXIT_FAILURE;
    }

static const char *intro = "Welcome to the Trivia Game\n";

/**
 * @brief Rules that are simply avoided in the program to be compliant.
 *
 * Rule: ERR50-CPP. Do not abruptly terminate the program.
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
     * @brief OOP57: Prefer special member functions and overloaded operators to C Standard Library functions.
     * While performing a copy, we are using an overloaded function as opposed to a C function like strcpy()
     * @brief OOP58: Copy operations must not mutate the source object.
     * Although there is a copy being made, the original source object (otherQuestion) is not altered in any way.
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

bool isValidName(string name)
{
    // STR52-CPP: Use valid references, pointers, and iterators to reference elements of a basic_string
    for (char c : name)
    {
        if (c != 'a' && c != 'b' && c != 'c')
        {
            // Do something with the invalid character
        }
    }
    return name; // Added return statement
}

//CTR50-CPP: Guarantee that container indices and iterators are within the valid range
//MSC51-CPP: Ensure your random number generator is properly seeded
//This function will number questions to be asked. Need to read questions from file
void numberQuestions() {
    vector<string> questions = {"Question 1", "Question 2", "Question 3"};
    
    // Use the random number generator to select a random index
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, questions.size() - 1);
    int index = distribution(gen);

    if (index < questions.size()) {
        cout << "Randomly selected question: " << questions[index] << endl;
    } else {
        cerr << "Invalid question index." << endl;
    }
}

//DCL52-CPP: Never qualify a reference type with const or volatile
void keepScore() {
    int score = 100;
    int& scoreRef = score;  // Reference to the score
    cout << "Current score: " << scoreRef << endl;
}

int main()
{
    // STR51-CPP: Do not attempt to create a std::string from a null pointer
    const char *hello = "Hello";
    string greeting;
    if (hello != nullptr)
    {
        greeting = hello;
    }
    else
    {
        std::cout << "Invalid string pointer."
                  << "\n";
    }

    string name;
    do
    {
        cout << "What is your name? ";
        // STR50-CPP: Guarantee that storage for strings has sufficient space for character data and the null terminator
        cin >> name;

        if (!isValidName(name))
        {
            cout << "Please correct your input. ";
        }
    } while (!isValidName(name));

    // STR53-CPP: Range check element access
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

    // FIO01-C: Be careful using functions that use file names for identification.
    //
    ifstream questionFile("triviaquestions.txt");

    if (!questionFile.is_open())
    { // Fixed the incorrect condition
        cerr << "Trouble opening the file.";
        return 1;
    }

    vector<Question> questions;
    string line;
    while (getline(questionFile, line))
    { // Fixed the getline usage
        questions.push_back(Question(line));
    }

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == nullptr)
    { // Fixed the assignment and condition
        cerr << "Error: Could not open output file" << endl;
        return 1;
    }
    // Write something to the output file here

     //ERR59-CPP: Do not throw an exception across execution boundaries
    checkOutFile(outputFile);
    
    
    //ERR56-CPP: Guarantee exception safety
    try {
        isValidName();  // Performing an operation that might throw an exception
    } catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }

   
    // Rule: MSC00-C: Compile cleanly at high warning levels
    //Ways to use?
    int a = 10;
    int b = 1; // Avoid division by zero
    float result = static_cast<float>(a) / b;
    cout << "Result: " << result << endl;


    // FIO51-CPP. Close files when they are no longer needed
    fclose(outputFile);

    return 0;
}
