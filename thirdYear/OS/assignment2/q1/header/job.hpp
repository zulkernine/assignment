#include<vector>
#include<iostream>

using namespace std;

// class to store details of a job, including their execution profiles
class Job {
private:
    int jobId;                  // job id
    int priority;               // priority (lesser value, higher priority)
    int arrivalTime;            // arrival time
    vector<int> cpuBursts;      // patches of cpu burst times, i.e. cpu burst(1), cpu burst(2), ...
    vector<int> ioBursts;       // patches of i/o burst times, i.e. i/o burst(1), i/o burst(2), ...
    int cntCPU;                 // total count of cpu bursts to occur
    int cntIO;                  // total count of i/o bursts to occur
    int nextCPU;                // index of next cpu burst to be performed
    int nextIO;                 // index of next i/o burst to be performed
    int nextArrivalTime;        // next arrival time for ready queue
    int totalTimeReqd;          // sum of all bursts
    bool preempt;               // to track flag for preemptive algorithms
    // the execution profile of the job is like: cpu burst(1), i/o burst(1), cpu burst(2), i/o burst(2), ...
public:
    Job() {                     // default constructor
        jobId = priority = arrivalTime = cntCPU = cntIO = nextCPU = nextIO = nextArrivalTime - 1;
    }
    Job(vector<int> execProfile) {  // paramaterized constructor with execution profile as the argument
        int sz = execProfile.size();
        // for (int i = 0; i < sz; ++i)
        //     cout << execProfile[i] << " ";
        // cout << "\n";
        jobId = execProfile[0];
        priority = execProfile[1];
        nextArrivalTime = arrivalTime = execProfile[2];
        cntCPU = cntIO = 0;
        totalTimeReqd = 0;
        preempt = false;
        for (int i = 3; i < sz; ++i) {
            if (i & 1) {        // for cpu bursts
                cpuBursts.push_back(execProfile[i]);
                ++cntCPU;
            }
            else {            // for i/o bursts
                ioBursts.push_back(execProfile[i]);
                ++cntIO;
            }
            totalTimeReqd += execProfile[i];
        }
        nextCPU = nextIO = 0;
        cout << "New Job Extracted - Job ID: " << jobId << ".\n"; // debug statement
    }
    // getter functions
    int getJobId()          { return jobId; }
    int getPriority()       { return priority; }
    int getArrivalTime()    { return arrivalTime; }
    int getCntCPU()         { return cntCPU; }
    int getCntIO()          { return cntIO; }
    int getNextCPU()        { return nextCPU; }
    int getNextIO()         { return nextIO; }
    int getCurrCPUTime()    { return cpuBursts[nextCPU]; }
    int getCurrIOTime()     { return ioBursts[nextIO]; }
    int getNextArrivalTime(){ return nextArrivalTime; }
    int getTotalTime()      { return totalTimeReqd; }
    int getPreempt()        { return preempt; }
    // setter functions
    void incNextCPU()       { if (nextCPU < cntCPU)   ++nextCPU; }
    void incNextIO()        { if (nextIO < cntIO)     ++nextIO; }
    void setPreempt()       { preempt = true; }
    void unsetPreempt()     { preempt = false; }
    void updateCPUTime(int dur) {
        cpuBursts[nextCPU] -= dur;
    }
    void updateArrival(int dur) {
        if (cpuBursts[nextCPU] == dur)
            nextArrivalTime = (cpuBursts[nextIO] + ioBursts[nextIO]);
        cpuBursts[nextCPU] -= dur;
    }
    // checker functions
    bool cpuLeft()          { return nextCPU < cntCPU; }
    bool ioLeft()           { return nextIO < cntIO; }

};


// comparator class for ordering jobs on the basis of arrival time
class JobComparatorFCFS {
public:
    bool operator()(Job& a, Job& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    }
};

// comparator class for ordering jobs on the basis of priority
class JobComparatorPriority {
public:
    bool operator()(Job& a, Job& b) {
        return a.getPriority() > b.getPriority();
    }
};


