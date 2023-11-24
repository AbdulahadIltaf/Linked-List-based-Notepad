#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
struct Node 
{

    char character;
    Node* before;
    Node* after;
    Node* below;
    Node* above;

    Node(char c)
    {
        character = c;
        before = NULL;
        after = NULL;
        below = NULL;
        above = NULL;
    }
};

struct Notepad2DLinkedList 
{

    Node* head;
    Node* cursor;
    Node * temporary;
    Node * temporary2;
    bool check;
    string x;

    Notepad2DLinkedList() 
    {
        head = NULL;  
        cursor = NULL;
        check = 0;
        temporary = NULL;
        temporary2 = NULL;
        
    }

bool isWordInDictionary(const string& x, const vector<string>& dictionary) 
{
    return find(dictionary.begin(), dictionary.end(), x) != dictionary.end();
}

void insertCharacter(char c) 
{
    Node* newNode = new Node(c);

    if (head == NULL)
    {
        head = newNode;
    }
    else if (check == 1) 
    {
        Node* currentLine = getCurrentLine();
        currentLine->below = newNode;
        newNode->above = currentLine;
        temporary2 = currentLine;
        check = 0;
        temporary->after = newNode;
        newNode->before = temporary;
        temporary = NULL;
        currentLine = NULL;
    } 
    else 
    {
        if (temporary2 != NULL){temporary2 = temporary2->after;}
        Node* currentLine = getCurrentLine();
        Node* lastChar = currentLine;
        while (lastChar->after != NULL) 
        {
            lastChar = lastChar->after;
        }
        
        lastChar->after = newNode;
        newNode->before = lastChar;

        newNode->above = temporary2;

        if (c == '\n')
        {
            check = true;
            temporary = newNode;
        }
        else
        {
            check = false;
        }
    }
    cursor = newNode;

    if (cursor->above != NULL)
    {
        cursor->above->below = cursor;
    }

}


void delete_Node()
{
if (cursor->above == NULL && cursor->before == NULL)
{
    Node* temp = cursor;
    while (temp->character != '\n' && temp->after != NULL)
    {
        temp->character = temp->after->character;
        temp = temp->after;
    }

    // Check if the loop ended due to finding '\n' or reaching the end
    if (temp->character == '\n')
    {
        temp->before->after = temp->after;
        if (temp->after != NULL)
        {
            temp->after->before = temp->before;
        }
        free(temp); // Assuming you want to free the memory of the removed node
    }
}

    else if (cursor->after == NULL)
    {
        cursor = cursor->before;
        delete cursor->after;
        cursor->after = NULL;

    }
    else
    {

    Node* temp = cursor;
    while (temp->character != '\n' && temp->after != NULL)
    {
        temp->character = temp->after->character;
        temp = temp->after;
    }

    // Check if the loop ended due to finding '\n' or reaching the end
    if (temp->character == '\n')
    {
        temp->before->after = temp->after;
        if (temp->after != NULL)
        {
            temp->after->before = temp->before;
        }
        free(temp); // Assuming you want to free the memory of the removed node
    }
    }

}

void look_into_dic(string xx) 
{
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t";
 int count[] = {0,0,0,0};
    vector<string> dictionary;

    ifstream file("dictionary.txt"); 
    string word;
    while (file >> word) 
    {
        dictionary.push_back(word);
    }

    char c[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
 string x;

 x = xx;
    //letter replaced

    for(int i=0;i<x.size();i++)
    {
        for (int j=0; j<26; j++)
        {
            x[i] = c[j];
                if (isWordInDictionary(x, dictionary)) 
            {
            cout << x <<" " ;
            count[0]++;
            if (count[0] == 2)
                break;
            }
        }
        
    }
    //letter omit
   
    x = xx;
    for(int i=0;i<x.size();i++)
    {
        string y = x.substr(0, i) + x.substr(i + 1);
        if (isWordInDictionary(y, dictionary)) 
        {
        cout << y <<" " ;
        count[1]++;
        if (count[1] == 2)
            break;
        }
    } 
    x = xx;
    //insert letter
    for (int i = 0; i <= x.size(); i++) 
    {
        for (char c = 'a'; c <= 'z'; c++) 
        {
            string y = x.substr(0, i) + c + x.substr(i);
            if (isWordInDictionary(y, dictionary)) 
            {
            cout << y <<" " ;
            count[2]++;
            if (count[2] == 2)
                break;
            }
        }
    }
    x = xx;
    //reverse letter
        for (int i = 0; i < x.size() - 1; i++) 
        {
        string combination = x;
        swap(combination[i], combination[i + 1]);
        if (isWordInDictionary(combination, dictionary)) 
        {
            cout << combination <<" " ;
            count[3]++;
            if (count[3] == 2)
                break;
            }
    }
}

void Move_Cursor()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwMode = 0;

    if (hStdin == INVALID_HANDLE_VALUE) 
    {
        cerr << "Error getting input handle" << endl;
        return ;
    }

    GetConsoleMode(hStdin, &fdwMode);
    SetConsoleMode(hStdin, fdwMode & (~ENABLE_LINE_INPUT) & (~ENABLE_ECHO_INPUT));

 while (true) 
 {
        if (_kbhit()) 
        {
            int key = _getch();
                if (head == NULL && key != 12)
                {
                    insertCharacter(char(key));
                }
                else if (key == 72 && cursor->above != nullptr) 
                { 
                    cursor = cursor->above;
                } else if (key == 80 && cursor->below != nullptr) 
                { 
                    cursor = cursor->below;
                } else if (key == 75 && cursor->before != nullptr) 
                { 
                    cursor = cursor->before;
                } else if (key == 77 && cursor->after != nullptr) 
                { 
                    cursor = cursor->after;
                } else if (((key >=65 && key <=90)||(key >=97 && key <=120)||(key == 32)||(key>=48 && key <=57))&&(cursor->after !=NULL)) { 
                    cursor->character = char(key);
                }else if (key == VK_BACK) { 
                    delete_Node();
                } else if (key == 19) { 
                    Save_File();
                }else if (key == 12) { 
                    Load_File();
                }
                else if (key == 27) { 
                    break; 
                }else if (cursor->after == NULL) { 
                    if (key == 13)
                    {
                        insertCharacter('\n');
                        goto here;
                    }
                    insertCharacter(char(key));
                    here:
                    if(key == 32)
                    {
                        x = "";
                        continue;
                    }
                    else
                    {
                        x += char(key);
                    }
                    look_into_dic(x);
        //              std::clock_t start = std::clock();
        // while ((std::clock() - start) / CLOCKS_PER_SEC < 0.01) {}
   
                }

                
          //  display();
            system("cls");
            display();
        }
    }
}




void display() 
{
    Node* currentLine = head;
        Node* current = head;
        while (current != NULL) 
        {
            if(cursor == current)
                cout << "\x1B[31m" << current->character << "\x1B[0m";
            else
                cout << current->character;

            current = current->after;
        }

    
}


    Node* getCurrentLine() 
    {
        Node* currentLine = head;
        while (currentLine->below != NULL) 
        {
            currentLine = currentLine->below;
        }
        return currentLine;
    }

void Save_File()
{
    ofstream of;
    	// opening file using ofstream
	of.open("Geeks for Geeks.txt", ios::app);
	if (!of)
		cout << "No such file found";
	else {

        Node * temp = head;
        while(temp != NULL)
        {
            of << temp->character;
            temp = temp->after;
        }

		cout << "Data appended successfully\n";
		of.close();
		string word;
        }
}


void Load_File()
{
    ifstream f;
    f.open("Geeks for Geeks.txt");

    if (!f.is_open()) {
        cerr << "Unable to open the file." << endl;
        return ;  // Return an error code
    }

    char charact;
    while (f.get(charact)) {
        insertCharacter(charact);
    }

    f.close();
}

~Notepad2DLinkedList()
{
    cursor = head;
    head = head->after;

    while (head != NULL)
    {
        delete cursor;
        cursor = head;
        head = head->after;
        
    }
    cursor = NULL;
    head = NULL;
    
}

};

int main() {

    cout << "\n\n\n\n\t\t\t\t\t\t\tMAIN-MENU\n";
    cout << "\n\t\t\t\t\tsave -> ctrl + S\n";
    cout << "\n\t\t\t\t\tload -> ctrl + L\n";
    cout << "\n\t\t\t\t\tOther -> type\n";
    cout << "\n\t\t\t\t\tQuit -> ECS\n";

    Notepad2DLinkedList notepad;
    notepad.Move_Cursor();


    
    
    



    return 0;
}
