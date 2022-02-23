#include "job.hpp"
#include<fstream>
#include<queue>
#include<unordered_map>
#include<climits>
#include<algorithm>

// abstract class for Job Scheduling algorithms
class JobScheduler {
protected:
    vector<Job> jobs;
    int jobsLeft;
    int totalWaitingTime;
    float avgWaitingTime;
    int totalTurnaroundTime;
    float avgTurnaroundTime;
public:
    // to parse the file and create vector of job profiles
    JobScheduler(string filename) {
        ifstream fin;
        fin.open(filename, ios::in);
        int num;
        totalTurnaroundTime = totalWaitingTime = jobsLeft = 0;
        while (fin >> num) {
            if (num == -1) {
                break;
            }
            else {    // new job starting
                vector<int> v = { num };
                fin >> num;
                if (num != -1)
                    v.push_back(num);
                while (fin >> num) {
                    if (num == -1) {
                        break;
                    }
                    else {
                        v.push_back(num);
                    }
                }
                Job J(v);
                jobs.push_back(J);
                ++jobsLeft;
            }
        }
    }
    // pure virtual function to schedule processes following the scheduling algorithms
    virtual void schedule() = 0;
    // to show results like average waiting and turnaround time
    void showAnalysis() {
        avgWaitingTime = totalWaitingTime * 1.0 / jobs.size();
        avgTurnaroundTime = totalTurnaroundTime * 1.0 / jobs.size();
        cout << "Average Turnaround Time = " << avgTurnaroundTime << "\n";
        cout << "Average Waiting Time = " << avgWaitingTime << "\n";
    }
};

// class for fcfs scheduling, inherited from JobScheduler class
class FCFS_Scheduler : public JobScheduler {
    queue<Job> ready_queue; // ready queue for CPU
    unordered_map<int, vector<Job>> block_queue; // block queue for i/o operations
    vector<pair<int, int>> ganttChart;  // to store the schedule
public:
    // sort the jobs based on arrival time
    FCFS_Scheduler(string filename) : JobScheduler(filename) {
        sort(jobs.begin(), jobs.end(), JobComparatorFCFS());
    }

    virtual void schedule() {
        int sz = jobs.size(), index = 0;
        for (int i = 0; i < sz; ++i) {  // push all the processes initially into the block queue
            block_queue[jobs[i].getArrivalTime()].push_back(jobs[i]);
            totalTurnaroundTime += jobs[i].getTotalTime();
            // cout << jobs[i].getJobId() << " -> " << jobs[i].getArrivalTime() << "\n";
        }
        int timeline = 0;
        bool cpuEmpty = true;
        Job currentJob; int nextTerminate = INT_MAX;
        while (jobsLeft > 0) {
            // process coming from block queue 
            for (Job j : block_queue[timeline]) {
                ready_queue.push(j);
            }
            if (timeline == nextTerminate) {
                cpuEmpty = true;
                if (currentJob.cpuLeft() == false)
                    --jobsLeft;
            }
            if (cpuEmpty) {
                if (!ready_queue.empty()) {
                    currentJob = ready_queue.front();
                    ready_queue.pop();
                    nextTerminate = timeline + currentJob.getCurrCPUTime();
                    ganttChart.push_back({ currentJob.getJobId(), timeline });
                    cpuEmpty = false;
                    currentJob.updateArrival(currentJob.getCurrCPUTime());
                    currentJob.incNextCPU();
                    if (currentJob.ioLeft()) {
                        currentJob.incNextIO();
                        if (currentJob.cpuLeft()) {
                            block_queue[timeline + currentJob.getNextArrivalTime()].push_back(currentJob);
                        }
                    }
                }
            }
            // cout << timeline << " " << ready_queue.size() << "\n";
            totalTurnaroundTime += ready_queue.size();
            totalWaitingTime += ready_queue.size();
            ++timeline;
        }
        cout << "Gantt Chart(FCFS): \n";
        for (pair<int, int> t : ganttChart) {
            cout << "{" << t.first << " @ " << t.second << "}\n";
        }
    }
    void showAnalysis() {
        cout << "Analysis for FCFS Scheduling Algorithm: \n";
        JobScheduler::showAnalysis();
    }
};

// class for round robin scheduling, inherited from JobScheduler class
class RoundRobin_Scheduler : public JobScheduler {
    queue<Job> ready_queue; // ready queue for CPU
    unordered_map<int, vector<Job>> block_queue; // block queue for i/o operations
    vector<pair<int, int>> ganttChart;  // to store the schedule
    int timeSlice;
public:
    // sort the jobs based on arrival time
    RoundRobin_Scheduler(string filename) : JobScheduler(filename) {
        sort(jobs.begin(), jobs.end(), JobComparatorFCFS());
        timeSlice = 25;
    }
    virtual void schedule() {
        int sz = jobs.size(), index = 0;
        for (int i = 0; i < sz; ++i) {  // push all the processes initially into the block queue
            block_queue[jobs[i].getArrivalTime()].push_back(jobs[i]);
            totalTurnaroundTime += jobs[i].getTotalTime();
            // cout << jobs[i].getJobId() << " -> " << jobs[i].getArrivalTime() << "\n";
        }
        int timeline = 0;
        bool cpuEmpty = true;
        Job currentJob; int nextTerminate = INT_MAX;
        while (jobsLeft > 0) {
            // process coming from block queue 
            for (Job j : block_queue[timeline]) {
                ready_queue.push(j);
            }
            if (timeline == nextTerminate) {
                cpuEmpty = true;
                if (currentJob.cpuLeft() == false)
                    --jobsLeft;
                else if (currentJob.getPreempt() == true && currentJob.getCurrCPUTime() > 0) {
                    currentJob.unsetPreempt();
                    ready_queue.push(currentJob);
                }
            }
            if (cpuEmpty) {
                if (!ready_queue.empty()) {
                    currentJob = ready_queue.front();
                    ready_queue.pop();
                    ganttChart.push_back({ currentJob.getJobId(), timeline });
                    cpuEmpty = false;
                    int val = min(currentJob.getCurrCPUTime(), timeSlice);
                    nextTerminate = timeline + val;
                    currentJob.updateArrival(val);
                    if (currentJob.getCurrCPUTime() == 0) {
                        currentJob.incNextCPU();
                        if (currentJob.ioLeft()) {
                            currentJob.incNextIO();
                            if (currentJob.cpuLeft()) {
                                block_queue[timeline + currentJob.getNextArrivalTime()].push_back(currentJob);
                            }
                        }
                    }
                    else {
                        currentJob.setPreempt();
                    }
                }
            }
            // cout << timeline << " " << ready_queue.size() << "\n";
            totalTurnaroundTime += ready_queue.size();
            totalWaitingTime += ready_queue.size();
            ++timeline;
        }
        cout << "Gantt Chart(Round Robin): \n";
        for (pair<int, int> t : ganttChart) {
            cout << "{" << t.first << " @ " << t.second << "}\n";
        }

    }
    void showAnalysis() {
        cout << "Analysis for Round Robin Scheduling Algorithm: \n";
        JobScheduler::showAnalysis();
    }
};

// class for priority based scheduling, inherited from JobScheduler class
class Priority_Scheduler : public JobScheduler {
    priority_queue<Job, vector<Job>, JobComparatorPriority> ready_queue; // ready queue for CPU
    unordered_map<int, vector<Job>> block_queue; // block queue for i/o operations
    vector<pair<int, int>> ganttChart;  // to store the schedule
    int timeSlice;
public:
    // sort the jobs based on arrival time
    Priority_Scheduler(string filename) : JobScheduler(filename) {
        sort(jobs.begin(), jobs.end(), JobComparatorFCFS());
        timeSlice = 25;
    }
    virtual void schedule() {
        int sz = jobs.size(), index = 0;
        for (int i = 0; i < sz; ++i) {  // push all the processes initially into the block queue
            block_queue[jobs[i].getArrivalTime()].push_back(jobs[i]);
            totalTurnaroundTime += jobs[i].getTotalTime();
            // cout << jobs[i].getJobId() << " -> " << jobs[i].getArrivalTime() << "\n";
        }
        int timeline = 0;
        bool cpuEmpty = true;
        Job currentJob; int nextTerminate = INT_MAX;
        while (jobsLeft > 0) {
            // process coming from block queue 
            for (Job j : block_queue[timeline]) {
                ready_queue.push(j);
            }
            if (timeline == nextTerminate) {
                cpuEmpty = true;
                if (currentJob.cpuLeft() == false)
                    --jobsLeft;
                else if (currentJob.getPreempt() == true && currentJob.getCurrCPUTime() > 0) {
                    currentJob.unsetPreempt();
                    ready_queue.push(currentJob);
                }
            }
            if (cpuEmpty) {
                if (!ready_queue.empty()) {
                    currentJob = ready_queue.top();
                    ready_queue.pop();
                    ganttChart.push_back({ currentJob.getJobId(), timeline });
                    cpuEmpty = false;
                    int val = min(currentJob.getCurrCPUTime(), timeSlice);
                    nextTerminate = timeline + val;
                    currentJob.updateArrival(val);
                    if (currentJob.getCurrCPUTime() == 0) {
                        currentJob.incNextCPU();
                        if (currentJob.ioLeft()) {
                            currentJob.incNextIO();
                            if (currentJob.cpuLeft()) {
                                block_queue[timeline + currentJob.getNextArrivalTime()].push_back(currentJob);
                            }
                        }
                    }
                    else {
                        currentJob.setPreempt();
                    }
                }
            }
            // cout << timeline << " " << ready_queue.size() << "\n";
            totalTurnaroundTime += ready_queue.size();
            totalWaitingTime += ready_queue.size();
            ++timeline;
        }
        cout << "Gantt Chart(Priority): \n";
        for (pair<int, int> t : ganttChart) {
            cout << "{" << t.first << " @ " << t.second << "}\n";
        }

    }
    void showAnalysis() {
        cout << "Analysis for Priority Based Scheduling Algorithm: \n";
        JobScheduler::showAnalysis();
    }
};


