#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

   string word_secret = "WATERMELON";
   map<char,bool> kick;
   vector<char> wrong_guess;

bool letter_exists(char guess){
    for(char letter : word_secret){
        if(guess == letter){
            return true;
        }
    }
    return false;
}

bool did_not_right(){
    for(char letter : word_secret){
        if(!kick[letter]){
            return true;
        }
    }
    return false;
}

bool did_not_hang(){
    return wrong_guess.size() < 5;
}

void print_header(){
    cout << "******************************" << endl;
    cout << "********** HANGMAN ***********" << endl;
    cout << "******************************" << endl;
    cout << endl;
}

void print_wrongs(){
    cout << "Wrong guess: ";
    for(char letter : wrong_guess){
        cout << letter << " ";
    }
    cout << endl;
}

void print_word(){
    for(char letter : word_secret){
            if(kick[letter]){
                cout << letter << " ";           
            }else{
                cout << "_ ";
            }
        }
        cout << endl;
}

void kicks(){
    cout << "Your guess: ";
    char guess;
    cin >> guess;

    kick[guess] = true;

    if(letter_exists(guess)){
        cout << "You're right! Your guess is in the word" << endl;
    }else{
        cout << "Poutzz. Your guess isn't in the word!" << endl;
        wrong_guess.push_back(guess);
    }
    cout << endl;
}

vector<string> read_file(){
    ifstream  arquivo;
    arquivo.open("words.txt");

    if(arquivo.is_open()){
        int number_of_words;
        arquivo >> number_of_words;
        

        vector <string> words_of_file;

        for(int i = 0; i<number_of_words; i++){
            string word_read;
            arquivo >> word_read;
            words_of_file.push_back(word_read);
        }
        arquivo.close();
        return words_of_file;
    }else{
        cout << "Unable to access the word bank\n" << endl;
        exit(0);
    }

}

void draw_word(){
        vector<string> words = read_file();

        srand(time(NULL));
        int raffled_index = rand()%words.size();
        word_secret = words[raffled_index];
    }

void save_file(vector<string> new_list){
    ofstream arquivo;
    arquivo.open("words.txt");
    if(arquivo.is_open()){
        arquivo << new_list.size() << endl;

        for(string word : new_list){
            arquivo << word << endl;
        }
        arquivo.close();
    }else{
        cout << "Unable to access the word bank\n" << endl;
        exit(0);
    }
}

void add_word(){
    cout << "Enter the new word using capital letters: " << endl;
    string new_word;
    cin >> new_word;

    vector<string> word_list = read_file();
    word_list.push_back(new_word);

    save_file(word_list);
}

int main(){

    print_header();

    read_file();

    draw_word();

    while(did_not_right() && did_not_hang()){

        print_wrongs();

        print_word();

        kicks();
    }

    cout << endl;
    cout << "End Game!" << endl;
    cout << "The word secret was: " << word_secret << endl;

    if(did_not_right()){
        cout << "You're lost! Try again! " << endl;
    }else{
        cout << "Congratulations! You're right word secret! " << endl;
        cout << "Do you want to add a new word to the bank? (s/n)" << endl;
        char answer; 
        cin >> answer;
        if(answer == 's'){
            add_word();
        }
    }
}