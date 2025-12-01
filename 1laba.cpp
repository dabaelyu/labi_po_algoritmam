#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <ctime>

class CourseFullError : public std::exception {
public:
    const char* what() const noexcept override { return "Course is full"; }
};

class Course {
protected:
    std::string __title, __instructor, __start_date, __end_date;
    int __max_students;
    std::vector<std::string> __students;

    int daysBetween(const std::string& s, const std::string& e) const {
        std::tm ts = {}, te = {};
        std::istringstream ss(s), se(e);
        ss >> ts.tm_year >> ts.tm_mon >> ts.tm_mday;
        se >> te.tm_year >> te.tm_mon >> te.tm_mday;
        ts.tm_year -= 1900; ts.tm_mon -= 1; te.tm_year -= 1900; te.tm_mon -= 1;
        double diff = std::difftime(std::mktime(&te), std::mktime(&ts));
        return static_cast<int>(diff / (60 * 60 * 24)) + 1;
    }

public:
    Course(const std::string& t, const std::string& i, const std::string& s, 
           const std::string& e, int m) : __title(t), __instructor(i), __start_date(s), 
           __end_date(e), __max_students(m) {}

    void addStudent(const std::string& name) {
        if (__students.size() >= __max_students) throw CourseFullError();
        __students.push_back(name);
    }

    double completionRate() const {
        return __max_students ? (double)__students.size() / __max_students * 100 : 0;
    }

    int durationDays() const { return daysBetween(__start_date, __end_date); }

    virtual std::string toString() const {
        std::ostringstream oss;
        oss << "Course: " << __title << ", Students: " << __students.size();
        return oss.str();
    }

    std::string getTitle() const { return __title; }
    std::vector<std::string> getStudents() const { return __students; }
    virtual ~Course() = default;
};

class ProgrammingCourse : public Course {
    std::string language;
public:
    ProgrammingCourse(const std::string& t, const std::string& i, const std::string& s, 
                      const std::string& e, int m, const std::string& l)
        : Course(t, i, s, e, m), language(l) {}
    
    std::string toString() const override {
        return Course::toString() + ", Language: " + language;
    }
};

class DesignCourse : public Course {
    std::string software;
public:
    DesignCourse(const std::string& t, const std::string& i, const std::string& s, 
                 const std::string& e, int m, const std::string& sw)
        : Course(t, i, s, e, m), software(sw) {}
    
    std::string toString() const override {
        return Course::toString() + ", Software: " + software;
    }
};

class ScienceCourse : public Course {
    std::string field;
public:
    ScienceCourse(const std::string& t, const std::string& i, const std::string& s, 
                  const std::string& e, int m, const std::string& f)
        : Course(t, i, s, e, m), field(f) {}
    
    std::string toString() const override {
        return Course::toString() + ", Field: " + field;
    }
};

class Platform {
    std::string name;
    std::vector<Course*> __courses;
public:
    Platform(const std::string& n) : name(n) {}

    void addCourse(Course* c) { __courses.push_back(c); }

    void removeCourse(const std::string& t) {
        auto it = std::find_if(__courses.begin(), __courses.end(),
                               [&t](Course* c) { return c->getTitle() == t; });
        if (it != __courses.end()) {
            delete *it;
            __courses.erase(it);
        }
    }

    Course* findCourse(const std::string& t) const {
        auto it = std::find_if(__courses.begin(), __courses.end(),
                               [&t](const Course* c) { return c->getTitle() == t; });
        return (it != __courses.end()) ? *it : nullptr;
    }

    std::vector<Course*> getAllCourses() const { return __courses; }

    std::vector<Course*> getMostPopular(int n = 3) const {
        auto sorted = __courses;
        std::sort(sorted.begin(), sorted.end(),
                  [](const Course* a, const Course* b) {
                      return a->getStudents().size() > b->getStudents().size();
                  });
        if (n > sorted.size()) n = sorted.size();
        return std::vector<Course*>(sorted.begin(), sorted.begin() + n);
    }

    ~Platform() { for (auto c : __courses) delete c; }
};

int main() {
    try {
        Platform platform("EduPlatform");
        platform.addCourse(new ProgrammingCourse("C++ Basics", "Dr. Smith", "2025-01-01", 
                                                 "2025-03-01", 50, "C++"));
        platform.addCourse(new DesignCourse("UI/UX", "Ms. Johnson", "2025-02-01", 
                                            "2025-04-01", 30, "Figma"));

        auto* course = platform.findCourse("C++ Basics");
        if (course) {
            course->addStudent("Alice");
            course->addStudent("Bob");
            std::cout << course->toString() << "\n";
        }

        std::cout << "\nMost popular:\n";
        for (auto c : platform.getMostPopular(2)) {
            std::cout << c->toString() << "\n";
        }

    } catch (const CourseFullError& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
