/**
 * Student Score Calculator
 * ---------------------------------------------
 * Collects a student's assessment scores (Quiz, Assignment,
 * Mid-Semester, End-of-Semester) and computes:
 *   - Total score
 *   - Percentage
 *   - Remaining score (out of 100)
 *   - Average score per assessment
 */

#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// Struct to group related student data together
struct StudentRecord
{
    string name;
    string indexNumber;
    int quizScore;
    int assignmentScore;
    int midSemScore;
    int endOfSemScore;
};

// Struct to hold computed results
struct ScoreSummary
{
    int totalScore;
    double percentage;
    int remainingScore;
    double averagePerAssessment;
};

// Prompts the user for a labeled integer score and validates the input
int readScore(const string &label)
{
    int score;
    cout << "Enter " << label << ": ";
    while (!(cin >> score))
    {
        cout << "Invalid input. Please enter a numeric value for " << label << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return score;
}

// Gathers all student information from the user
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

// Calculates total, percentage, remaining, and average scores
ScoreSummary calculateSummary(const StudentRecord &student)
{
    ScoreSummary summary;

    summary.totalScore = student.quizScore + student.assignmentScore +
                         student.midSemScore + student.endOfSemScore;

    summary.percentage = (summary.totalScore * 100.0) / 100.0;
    summary.remainingScore = 100 - summary.totalScore;
    summary.averagePerAssessment = summary.totalScore / 4.0;

    return summary;
}

// Displays the student's results in a readable format
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
    vector<StudentRecord> students; // Temporary storage for all students entered

    char addAnother = 'y';
    while (addAnother == 'y' || addAnother == 'Y')
    {
        StudentRecord student = collectStudentData();
        students.push_back(student);

        cout << "Add another student? (y/n): ";
        cin >> addAnother;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline before next getline
    }

    // Print a report for every student stored in the vector
    for (const StudentRecord &student : students)
    {
        ScoreSummary summary = calculateSummary(student);
        printReport(student, summary);
    }

    return 0;
}
