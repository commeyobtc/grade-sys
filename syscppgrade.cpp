
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct StudentRecord
{
    string name;
    string indexNumber;
    int quizScore;
    int assignmentScore;
    int midSemScore;
    int endOfSemScore;
};

struct ScoreSummary
{
    int totalScore;
    double percentage;
    int remainingScore;
    double averagePerAssessment;
};

// checking for valid input and reading the score
int readScore(const string &label)
{
    int score;
    cout << "Enter " << label << ": ";

    while (true)
    {
        if (cin >> score)
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please enter a numeric value for " << label << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return score;
}
// taking student data from user input
StudentRecord collectStudentData()
{
    StudentRecord student;

    cout << "Enter student name: ";
    getline(cin, student.name);

    cout << "Enter index number: ";
    cin >> student.indexNumber;

    student.quizScore = readScore("Quiz score");
    student.assignmentScore = readScore("Assignment score");
    student.midSemScore = readScore("Mid-Semester score");
    student.endOfSemScore = readScore("End-of-Semester score");

    return student;
}

ScoreSummary calculateSummary(const StudentRecord &student)
{
    ScoreSummary summary;

    summary.totalScore = student.quizScore + student.assignmentScore +
                         student.midSemScore + student.endOfSemScore;

    summary.percentage = (summary.totalScore / 70.0);
    summary.remainingScore = 100 - summary.totalScore;
    summary.averagePerAssessment = summary.totalScore / 4.0;

    return summary;
}

// Displays the student's report card
void printReport(const StudentRecord &student, const ScoreSummary &summary)
{
    cout << "\n---------------------------------\n";
    cout << "         STUDENT REPORT          \n";
    cout << "---------------------------------\n";
    cout << "Student Name       : " << student.name << '\n';
    cout << "Index Number       : " << student.indexNumber << '\n';
    cout << "Total Score        : " << summary.totalScore << '\n';
    cout << "Percentage         : " << summary.percentage << "%\n";
    cout << "Remaining Score    : " << summary.remainingScore << '\n';
    cout << "Average per Assess.: " << summary.averagePerAssessment << '\n';
    cout << "---------------------------------\n";
}

int main()
{
    vector<StudentRecord> students;

    char addAnother = 'y';
    while (true)
    {
        StudentRecord student = collectStudentData();
        students.push_back(student);

        cout << "Add another student? (y/n): ";
        cin >> addAnother;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (addAnother == 'y' || addAnother == 'Y')
        {
            // will run again if user typed y/Y
        }
        else if (addAnother == 'n' || addAnother == 'N')
        {
            break; // exit if user  type n/N
        }
        else
        {
            cout << "please enter valid value : \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    //
    for (const StudentRecord &student : students)
    {
        ScoreSummary summary = calculateSummary(student);
        printReport(student, summary);
    }

    return 0;
}
