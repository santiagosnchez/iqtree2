//
//  progress.hpp
//  alignment
//
//  Created by James Barbetti on 28/7/20.
//

#ifndef progress_h
#define progress_h

#include <string>       //for std::string
#include <fstream>      //for std::fstream
#include "timeutil.h"

class progress_display {
public:
    explicit progress_display ( double workToDo, const char* doingWhat=""
                              , const char* verb="", const char* unitName="");
    ~progress_display();
    progress_display& operator += (double incrementalWork);
    progress_display& operator ++ ();
    progress_display& operator =  (double workDoneNow);
    progress_display& incrementBy (double increment);
    progress_display& hide ();
    progress_display& show ();
    progress_display& done ();
    void setTaskDescription  (const  char* newDescription);
    void setTaskDescription  (const  std::string& newDescription);
    void setWorkRemaining    (double newEstimate);
    void setIsEstimateABound (bool   isEstimateAnUpperBound);
    void reportProgress      (double time, double cpu, bool newline);
    static void setProgressDisplay(bool displayIt);
    static bool getProgressDisplay();
protected:
    double startTime;
    double startCPUTime;
    double totalWorkToDo;
    double workDone;             //Amount of work done so far
    std::string taskDescription; //A description of the task
    bool        isDone;          //True if the task has been completed
    std::string workVerb;        //A past tense verb (e.g. sorted)
    std::string workUnitName;    //A singular noun   (e.g. row)
    double lastReportedWork;     //Last reported work done
    double lastReportedTime;     //Last reported wall-clock time
    double lastReportedCPUTime;  //Last reported CPU time
    bool   atMost;               //Estimate of work to do is an upper bound
    int    hidden;               //How many more times has hide() been called than show()
    std::fstream termout;        //Terminal output stream (not standard output!)
};


#endif /* progress_hpp */
