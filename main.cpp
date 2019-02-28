#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

//Choose a file to run the code. Make sure that the file is a test that contains questions, choices, and answers

double correct(string, queue <string> &, double);
double finalScore(double, int);

int main(int argc, const char * argv[]) {
    
    fstream file; //used to create file objects
    queue <string> questions; //queue that holds all the questions
    queue <string> choices; //queue that holds all the choices from a question
    queue <string> correct_answers; //queue that holds all correct answers
    queue <int> sub_choices; //queue that holds the number of choices from a question
    int choice_count = 0; //counts the amount of choices from a questions
    string grabber; //data that grabs the first character of the string
    int numQuestions = 0; //number of questions;
    string choice; //value that the user will enter
    double points = 0; //amount of points that the user holds
    
    //Exit program if the user enters more than one file (one parameter)
    try{
        if(argc > 2)
            throw 101;
    }catch(int num_err){
        cout <<"Error: " << num_err <<". There are too many files!\n" << endl;
        exit(0);
    }
    
    //Opens file
    file.open(argv[1], ios::in);
    //file.open("/Users/ninjagodivan/Documents/TextFiles/drivingtest.txt", ios::in);
    
    //Exit program if the user enters a non-existing file
    if(!file){
        cout <<"File does not exist!\n";
        exit(0);
    }
    
    //Extracts all questions, choices, and answers from the file
    while(getline(file, grabber)){
        
        char getFirstChar = grabber[0]; //gets the first character
        int is_now_int = atoi(&getFirstChar); //converts character to an integer
        
         //If the first character is a number, then the string is a question
         //Else if it's a capitalized character, then the string is an answer
         //Else, the string is a choice
    
        if(is_now_int != 0){
            questions.push(grabber); //Adds a questions
            numQuestions++; //Increases question count
        }
        else{
            if(isupper(getFirstChar)){
                sub_choices.push(choice_count); //Adds a total amount of choices in queue
                correct_answers.push(grabber); //Adds a correct answer
                choice_count = 0; //Resets to no choices
            }
            else if(islower(getFirstChar)){
                choices.push(grabber); //Adds a choice
                choice_count++; //Increases the amount of choice
            }
        }
    }
    
    //Closes the file
    file.close();
    
    cout <<"Warning: Make sure you use uppercase letters to answer!\n\n";
    
    //User selects the answer
    for(int i = 0; i < numQuestions; i++){
        
        cout << questions.front() << endl; //Displays question
        
        for(int j = 0; j < sub_choices.front(); j++){ //Displays choices from a question
            cout << choices.front() << endl;
            choices.pop();
        }
        
        sub_choices.pop();
        
        cout <<"Select answer: ";
        cin >> choice;
        
        points += correct(choice, correct_answers, points); //Adds points
        questions.pop();
        cout << endl;
    }
    
    //Displays final score
    cout <<"Your score is " << finalScore(points, numQuestions) <<"% (" << points <<"/" << numQuestions << ")\n";

    return 0;
}

double correct(string correct, queue <string> &correct_answers, double points){
    
    if(correct == correct_answers.front()){
        correct_answers.pop();
        return 1;
    }
    else{
        correct_answers.pop();
        return 0;
    }
}

double finalScore(double points, int numQuestions){return (points / numQuestions) * 100;}
