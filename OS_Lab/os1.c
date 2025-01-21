#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MEM 1024
#define STEPS 2000
#define CASES 9

typedef struct {
    int sz;
    int dur;
} J;

int mem[MEM];
double tFrag, hFrag, lFrag;
int tHoleSz, tJobs, hJobs, lJobs;
int tHoles, hHoles, lHoles;
int tParts, evict, maxEvict;

void initMem() {
    for (int i = 0; i < MEM; i++) mem[i] = 0;

    tFrag = 0.0, hFrag = 0.0, lFrag = 1.0;
    hJobs = 0, lJobs = MEM, hHoles = 0, lHoles = MEM;
    tHoleSz = 0, tHoles = 0, tJobs = 0, tParts = 0, evict = 0, maxEvict = 0;
}

int genSz(int prof) {
    if (prof == 1) return rand() % 1024 + 1;
    else if (prof == 2) return rand() % 100 + 1;
    return rand() % 501 + 500;
}

int allocMem(int sz, int pol) {
    int bStart = -1, bSz = MEM + 1;
    int wStart = -1, wSz = -1;
    int fStart = -1, curStart = -1, curSz = 0;

    for (int i = 0; i <= MEM; i++) {
        if (i < MEM && mem[i] == 0) {
            if (curStart == -1) curStart = i;
            curSz++;
        } else {
            if (curSz >= sz) {
                if (pol == 1 && curSz < bSz) bStart = curStart, bSz = curSz;
                else if (pol == 2 && curSz > wSz) wStart = curStart, wSz = curSz;
                else if (pol == 3 && fStart == -1) fStart = curStart;
            }
            curStart = -1, curSz = 0;
        }
    }
    if (pol == 1) return bStart;
    if (pol == 2) return wStart;
    if (pol == 3) return fStart;
    return -1;
}

void freeMem(int start, int sz) {
    for (int i = start; i < start + sz; i++) mem[i] = 0;
}

void calcStats() {
    int holes = 0, holeSz = 0, curHole = 0;

    for (int i = 0; i < MEM; i++) {
        if (mem[i] == 1) {
            if (curHole > 0) holes++, holeSz += curHole, curHole = 0;
        } else curHole++;
    }

    if (curHole > 0) holes++, holeSz += curHole;

    double frag = (double)holeSz / MEM;
    tFrag += frag;
    if (frag > hFrag) hFrag = frag;
    if (frag < lFrag) lFrag = frag;

    int jobs = MEM - holeSz;
    tJobs += jobs;
    if (jobs > hJobs) hJobs = jobs;
    if (jobs < lJobs) lJobs = jobs;

    tHoleSz += holeSz, tHoles += holes;
}

void sim(int prof, int pol) {
    initMem();

    for (int t = 0; t < STEPS; t++) {
        J job;
        job.sz = genSz(prof);
        job.dur = rand() % 10 + 1;

        int start = allocMem(job.sz, pol);
        if (start != -1) {
            for (int i = start; i < start + job.sz; i++) mem[i] = 1;
            tParts++;
        } else {
            int e = 0;
            while (start == -1) {
                int rStart = rand() % MEM;
                if (mem[rStart] == 1) freeMem(rStart, job.sz), e++;
                start = allocMem(job.sz, pol);
            }
            if (e > maxEvict) maxEvict = e;
        }

        if (t >= 1000) calcStats();
    }
}

void writeRes(FILE *f, double res[CASES][7]) {
    fprintf(f, "Profile | Policy | AvgFrag | HiFrag | LoFrag | AvgJobs | HiJobs | LoJobs\n");
    fprintf(f, "--------|--------|---------|--------|--------|---------|--------|--------\n");

    for (int i = 0; i < CASES; i++) {
        fprintf(f, "   %d    |   %d    |   %.2f  |  %.2f  |  %.2f  |   %.2f  |   %d   |   %d\n",
                (i / 3) + 1, (i % 3) + 1,
                res[i][0], res[i][1], res[i][2],
                res[i][3], (int)res[i][4], (int)res[i][5]);
    }
}

int main() {
    FILE *f = fopen("summary.txt", "w");
    if (!f) {
        printf("Error opening file.\n");
        return 1;
    }

    srand(time(NULL));
    double res[CASES][7];

    for (int prof = 1; prof <= 3; prof++) {
        for (int pol = 1; pol <= 3; pol++) {
            int idx = (prof - 1) * 3 + (pol - 1);

            sim(prof, pol);

            res[idx][0] = tFrag / 1000;
            res[idx][1] = hFrag;
            res[idx][2] = lFrag;
            res[idx][3] = (double)tJobs / 1000;
            res[idx][4] = hJobs;
            res[idx][5] = lJobs;
        }
    }

    writeRes(f, res);
    fclose(f);
    printf("Simulation completed. Results saved in summary.txt.\n");
    return 0;
}
