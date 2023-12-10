#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // for sort
#include <vector>

using namespace std;

struct Course
{
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Organize data into a vector
vector<string> format(const string s, const string del = ",")
{
    vector<string> result;
    size_t start = 0, end = s.find(del);
    while( end != string::npos) 
    {
        result.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    result.push_back(s.substr(start, end - start));
    return result;
}

// Load file to grab each course and organize it into a vector
vector<Course> loadCoursesFile()
{
    ifstream fin("courses.txt", ios::in);
    vector<Course> courses;
    string line;

    while (getline(fin, line))
    {
        if(line == "-1") break;

        Course course;
        vector<string> info = format(line);

        course.courseNumber = info[0];
        course.name = info[1];

        for(int i = 2; i < info.size(); i++)
        {
            course.prerequisites.push_back(info[i]);
        }

        courses.push_back(course);
    }

    fin.close();
    return courses;
}

// Print out the course
void printCourse(Course course)
{
    cout << course.courseNumber << ", " << course.name << endl;
    cout << "Prerequisites: ";
    for (size_t i = 0; i < course.prerequisites.size(); ++i) {
        std::cout << course.prerequisites[i];
        
        // Print a comma after each prerequisite except for the last one
        if (i < course.prerequisites.size() - 1) {
            std::cout << ", ";
        }
    }
    cout << "\n\n";
}


// Sort and print out the course list
void printCourseList(vector<Course> courses)
{
    sort(courses.begin(), courses.end(), 
    [](const Course& a, const Course& b) { 
        return a.courseNumber < b.courseNumber; 
    });

    for(Course course: courses) 
    {
        printCourse(course);
    }
}

// Search for a course by course number
void searchCourse(const vector<Course> courses)
{
    string courseNumber;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;
    cout << endl;


    bool found = false;
    for (Course course: courses)
    {
        // Lowercase the course number to make it case insensitive
        string lowerCase = courseNumber;
        string lowerCase2 = course.courseNumber;
        transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(), ::tolower);
        transform(lowerCase2.begin(), lowerCase2.end(), lowerCase2.begin(), ::tolower);
        if (lowerCase2 == lowerCase)
        {
            printCourse(course);
            found = true;
            break;
        }
    }
    if(!found)
    {
        cout << "Course " << courseNumber << " not found." << endl;
    }
}

// Menu
int main()
{
    vector<Course> courses;

    cout << "Welcome to the course planner." << endl;
    cout << endl;

    while (true)
    {
        int input;
        cout << "\t 1. Load Data Structure." << endl;
        cout << "\t 2. Print Course List." << endl;
        cout << "\t 3. Print Course." << endl;
        cout << "\t 4. Exit" << endl;
        cout << endl;

        // Take in user input
        cout << "What would you like to do? ";
        cin >> input;
        cout << endl;
        if(input == 4)
        {
            break;
        }
        else if (input == 1) 
        {
            courses = loadCoursesFile();
        }
        else if (input == 2)
        {
            printCourseList(courses);
        }
        else if (input == 3)
        {
            searchCourse(courses);  
        }
        else
        {
            cout << input;
            cout << " is not a valid option." << endl;
        }
    }
    cout << "Thank you for using the course planner!" << endl;

    return 0;
}