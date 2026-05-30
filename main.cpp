#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
typedef struct{
    string name;
    int id;
    double sub1,sub2,sub3;
    char grade;
}student;

void insertstudentdata(vector<student>& studentlist);
void searchstudent(vector<student>& studentlist);
void printrankinglist(vector<student>& studentlist);
double calculategrade(double sub1,double sub2,double sub3);
bool compareStudents(const student& a, const student& b);
void loadFromFile(vector<student>& studentlist);
void saveToFile(const vector<student>& studentlist);

int main(){
    vector<student> studentlist;
    loadFromFile(studentlist);
    int choice;
    do{
        cout<<"1.enter new student data"<<endl;
        cout<<"2.search for student grade"<<endl;
        cout<<"3.print rank list"<<endl;
        cout<<"4.exit"<<endl;
        cout<<"enter your choice "<<endl;
        cin>>choice;
        if (!(cin >> choice)) {
            cout << "\n[Error] Invalid input! Please enter a number (1-4)." << endl;
            cin.clear();           
            cin.ignore(10000, '\n'); 
            continue;
        }
        switch (choice)
        {
        case 1:
            insertstudentdata(studentlist);
            break;
        case 2:
            searchstudent(studentlist);
            break;
        case 3:
            printrankinglist(studentlist);
            break;
        case 4:
            saveToFile(studentlist);
            cout<<"data saved successfully"<<endl;
            break;
        default:
            cout<<"enter valid choice"<<endl;
            break;
        }
    }   while(choice != 4);
    return 0;
}

double calculategrade(double sub1,double sub2,double sub3){
    return (sub1+sub2+sub3)/3.0;
}

void insertstudentdata(vector<student>& studentlist){
    student temp;
    cout<<"enter the name of student"<<endl;
    cin.ignore();
    getline(cin,temp.name);
    cout<<"enter student id "<<endl;
    cin>>temp.id;
    cout<<"enter student marks in order subject 1 , subject 2 , subject 3"<<endl;
    cin>>temp.sub1>>temp.sub2>>temp.sub3;
    cin.ignore(10000, '\n');
    double x=calculategrade(temp.sub1,temp.sub2,temp.sub3);

    if(x>=85.00) temp.grade='A';
    else if(x>=65.00) temp.grade='B';
    else if(x>=45.00) temp.grade='C';
    else temp.grade='P';

    studentlist.push_back(temp);
}

void searchstudent(vector<student>& studentlist){
    cout<<"enter the id of student"<<endl;
    int temp;
    cin>>temp;
    bool found=false;
    for(const auto &student:studentlist){
        if(student.id == temp){
            found=true;
            cout<<"Name: "<<student.name<<"  | Student ID: "<<student.id<<" | Marks : "<<student.sub1<<","<<student.sub2<<","<<student.sub3<<" | Grade: "<<student.grade<<endl;
            break;
        }
    }
    if(!found){
        cout<<"there is no student in the list with given ID"<<endl;
    }
}

void printrankinglist(vector<student>& studentlist){
    if(studentlist.empty()){
        cout<<"the list is empty \n no student data "<<endl;
    }
    sort(studentlist.begin(),studentlist.end(),compareStudents);
    long long i=1;
    for(const auto &student:studentlist){
        double avg = calculategrade(student.sub1, student.sub2, student.sub3);
        cout<<" Rank:"<<i<<" | Name: "<<student.name<<"  | Student ID: "<<student.id<<" | Marks: "<<student.sub1<<","<<student.sub2<<","<<student.sub3<<" | Average: "<<avg<<" | Grade: "<<student.grade<<endl;
        i++;
    }
}

bool compareStudents(const student& a, const student& b){
    double avgA = (a.sub1 + a.sub2 + a.sub3) / 3.0;
    double avgB = (b.sub1 + b.sub2 + b.sub3) / 3.0;
    return avgA > avgB;
}

void saveToFile(const vector<student>& studentlist) {
    ofstream outFile("students_data.txt");

    if (!outFile) {
        cout << "Error: Could not save data to file!" << endl;
        return;
    }

    for (const auto& s : studentlist) {
        // Write all variables separated by commas
        outFile << s.name << "," 
                << s.id << "," 
                << s.sub1 << "," 
                << s.sub2 << "," 
                << s.sub3 << "," 
                << s.grade << "\n";
    }
    outFile.close();
}

void loadFromFile(vector<student>& studentlist) {
    ifstream inFile("students_data.txt");
    if (!inFile) {
        return;
    }

    student temp;
    char comma;

    while (getline(inFile, temp.name, ',')) {
        inFile >> temp.id >> comma
               >> temp.sub1 >> comma
               >> temp.sub2 >> comma
               >> temp.sub3 >> comma
               >> temp.grade;
        inFile.ignore();
        
        studentlist.push_back(temp);
    }
    inFile.close();
}
