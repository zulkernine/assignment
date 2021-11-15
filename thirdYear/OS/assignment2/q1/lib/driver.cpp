#include "../header/scheduler.hpp"

// class to run the simulation
class DriverProgramme {
    string filename;
public:
    DriverProgramme(string f) {
        filename = f;
    }
    void makeRandomProcess() {
        int sz = 30;
        string filename = "jobprofiles_random.txt";
        ofstream fout;
        fout.open(filename, ios::out);
        for (int i = 1; i <= sz; ++i) {
            fout << i << " ";
            int arrival = rand() % 100;
            fout << arrival << " ";
            int priority = rand() % 17;
            fout << priority << " ";
            int burstsz = 1 + rand() % 13;
            for (int j = 0; j < burstsz; ++j) {
                // cpu
                int exp = rand() % 7;
                fout << (1 << exp) << " ";
                // i/o
                exp = rand() % 7;
                fout << (1 << exp) << " ";
            }
            int last = rand() % 2;
            if (last) {
                int exp = rand() % 7;
                fout << (1 << exp) << " ";
            }
            fout << "-1 ";
        }
    }
    void run() {
        cout << "Test on randomly generated data? : (y/n)\n";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            filename = "jobprofiles_random.txt";
            makeRandomProcess();
        }
        FCFS_Scheduler F(filename);
        RoundRobin_Scheduler R(filename);
        Priority_Scheduler P(filename);
        F.schedule();
        R.schedule();
        P.schedule();
        F.showAnalysis();
        R.showAnalysis();
        P.showAnalysis();
    }
};


int main() {

    DriverProgramme R("jobprofiles.txt");
    R.run();

    return 0;
}

