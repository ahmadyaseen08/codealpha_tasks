#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
int main()
{
    int courses;
    string subject;
    float grade, creditHours;
    float totalCredits = 0;
    float totalGradePoints = 0;
    float previousCGPA, previousCredits;
    cout << "Enter Previous CGPA: ";
    cin >> previousCGPA;
    cout << "Enter Previous Total Credit Hours: ";
    cin >> previousCredits;
    cout << "Enter Number of Courses: ";
    cin >> courses;
    for(int i = 1; i <= courses; i++)
    {
        cout << "\nCourse " << i << endl;
        cout << "Enter Subject Name: ";
        cin >> subject;
        cout << "Enter Grade Point: ";
        cin >> grade;
        cout << "Enter Credit Hours: ";
        cin >> creditHours;
        float gradePoints = grade * creditHours;
        totalCredits = totalCredits + creditHours;
        totalGradePoints = totalGradePoints + gradePoints;
        cout << "Grade Points for " << subject << " = "
             << gradePoints << endl;
    }
    float semesterGPA = totalGradePoints / totalCredits;
    float previousGradePoints = previousCGPA * previousCredits;
    float overallCGPA =
    (previousGradePoints + totalGradePoints) /
    (previousCredits + totalCredits);
    cout << "\n========== RESULT ==========" << endl;
    cout << "Total Current Credits = "
         << totalCredits << endl;
    cout << "Semester GPA = "
         << semesterGPA << endl;
    cout << "Overall CGPA = "
         << overallCGPA << endl;
    getch();
    return 0;
}
