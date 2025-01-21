#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MEMORY_SIZE 1024
#define SIMULATION_STEPS 2000  // Total steps: 1000 warmup + 1000 measurement
#define WARMUP_STEPS 1000     // First 1000 steps for warmup
#define MAX_JOBS 1024

typedef struct {
    int start;
    int size;
    int job_id;
} Partition;

typedef struct {
    Partition partitions[MAX_JOBS];
    int count;
} MemoryState;

typedef struct {
    double avg_fragmentation;
    double avg_hole_size;
    double avg_holes_examined;
    double highest_fragmentation;
    double lowest_fragmentation;
    double avg_jobs;
    int highest_jobs;
    int lowest_jobs;
    double avg_job_size;
    double avg_holes;
    int highest_holes;
    int lowest_holes;
    int max_partitions_in_row;
    int max_evictions;
} SimulationStats;

SimulationStats all_stats[3][3]; // [profile][policy]

int generate_job_size(int profile) {
    switch(profile) {
        case 1: return rand() % 1024 + 1;  
        case 2: return rand() % 100 + 1;   
        case 3: return rand() % 501 + 500; 
        default: return rand() % 1024 + 1;
    }
}

double calculate_fragmentation(MemoryState *state) {
    if (state->count == 0) return 0.0;
    
    int used_memory = 0;
    for (int i = 0; i < state->count; i++) {
        used_memory += state->partitions[i].size;
    }
    return 1.0 - ((double)used_memory / MEMORY_SIZE);
}

int find_hole(MemoryState *state, int size, int policy, int *holes_examined) {
    int best_start = -1;
    int best_size = policy == 1 ? INT_MAX : -1;
    *holes_examined = 0;

    int current_pos = 0;
    for (int i = 0; i <= state->count; i++) {
        int hole_start = current_pos;
        int hole_size;
        
        if (i == state->count) {
            hole_size = MEMORY_SIZE - current_pos;
        } else {
            hole_size = state->partitions[i].start - current_pos;
        }
        
        (*holes_examined)++;
        
        if (hole_size >= size) {
            switch(policy) {
                case 1: // Best fit
                    if (hole_size < best_size) {
                        best_start = hole_start;
                        best_size = hole_size;
                    }
                    break;
                case 2: // Worst fit
                    if (hole_size > best_size) {
                        best_start = hole_start;
                        best_size = hole_size;
                    }
                    break;
                case 3: // First fit
                    return hole_start;
            }
        }
        
        if (i < state->count) {
            current_pos = state->partitions[i].start + state->partitions[i].size;
        }
    }
    
    return best_start;
}

void add_partition(MemoryState *state, int start, int size, int job_id) {
    int insert_pos = 0;
    while (insert_pos < state->count && state->partitions[insert_pos].start < start) {
        insert_pos++;
    }
    
    for (int i = state->count; i > insert_pos; i--) {
        state->partitions[i] = state->partitions[i-1];
    }
    
    state->partitions[insert_pos].start = start;
    state->partitions[insert_pos].size = size;
    state->partitions[insert_pos].job_id = job_id;
    state->count++;
}

void remove_partition(MemoryState *state, int index) {
    for (int i = index; i < state->count - 1; i++) {
        state->partitions[i] = state->partitions[i+1];
    }
    state->count--;
}

void run_simulation(int profile, int policy) {
    MemoryState state = {0};
    SimulationStats stats = {0};
    stats.lowest_fragmentation = 1.0;
    stats.lowest_jobs = INT_MAX;
    stats.lowest_holes = INT_MAX;
    
    int current_job_id = 1;
    double total_fragmentation = 0;
    double total_hole_size = 0;
    int total_holes_examined = 0;
    int total_jobs = 0;
    int total_job_size = 0;
    int total_holes = 0;
    int total_requests = 0;
    int current_partitions_in_row = 0;
    
    for (int step = 0; step < SIMULATION_STEPS; step++) {
        int new_job_size = generate_job_size(profile);
        int holes_examined;
        int hole_pos = find_hole(&state, new_job_size, policy, &holes_examined);
        int evictions = 0;
        
        while (hole_pos == -1 && state.count > 0) {
            int to_remove = rand() % state.count;
            remove_partition(&state, to_remove);
            evictions++;
            hole_pos = find_hole(&state, new_job_size, policy, &holes_examined);
        }
        
        if (hole_pos != -1) {
            add_partition(&state, hole_pos, new_job_size, current_job_id++);
            current_partitions_in_row++;
            if (current_partitions_in_row > stats.max_partitions_in_row) {
                stats.max_partitions_in_row = current_partitions_in_row;
            }
        }
        
        if (evictions > 0) {
            if (evictions > stats.max_evictions) {
                stats.max_evictions = evictions;
            }
            current_partitions_in_row = 0;
        }
        
        if (step >= WARMUP_STEPS) {  // Only collect stats after 1000 warmup steps
            double frag = calculate_fragmentation(&state);
            total_fragmentation += frag;
            
            if (frag > stats.highest_fragmentation) stats.highest_fragmentation = frag;
            if (frag < stats.lowest_fragmentation) stats.lowest_fragmentation = frag;
            
            if (state.count > stats.highest_jobs) stats.highest_jobs = state.count;
            if (state.count < stats.lowest_jobs) stats.lowest_jobs = state.count;
            
            total_jobs += state.count;
            total_job_size += new_job_size;
            total_holes_examined += holes_examined;
            
            int holes = 0;
            int hole_size_sum = 0;
            int current_pos = 0;
            
            for (int i = 0; i <= state.count; i++) {
                if (i < state.count) {
                    int hole = state.partitions[i].start - current_pos;
                    if (hole > 0) {
                        holes++;
                        hole_size_sum += hole;
                    }
                    current_pos = state.partitions[i].start + state.partitions[i].size;
                } else if (current_pos < MEMORY_SIZE) {
                    holes++;
                    hole_size_sum += (MEMORY_SIZE - current_pos);
                }
            }
            
            if (holes > stats.highest_holes) stats.highest_holes = holes;
            if (holes < stats.lowest_holes) stats.lowest_holes = holes;
            total_holes += holes;
            total_hole_size += hole_size_sum;
            total_requests++;
        }
    }
    
    // Calculate averages based on exactly 1000 measurement steps
    stats.avg_fragmentation = total_fragmentation / 1000;
    stats.avg_hole_size = total_hole_size / (total_holes > 0 ? total_holes : 1);
    stats.avg_holes_examined = (double)total_holes_examined / total_requests;
    stats.avg_jobs = (double)total_jobs / 1000;
    stats.avg_job_size = (double)total_job_size / total_requests;
    stats.avg_holes = (double)total_holes / 1000;
    
    all_stats[profile-1][policy-1] = stats;
}

void write_summary_file() {
    FILE *fp = fopen("summary.txt", "w");
    if (!fp) {
        printf("Error opening file for writing\n");
        return;
    }
    
    fprintf(fp, "Memory Management Simulation Summary\n");
    fprintf(fp, "===================================\n");
    fprintf(fp, "Configuration: 1000 warmup steps + 1000 measurement steps\n\n");
    
    const char *profiles[] = {"Any Sized Jobs (1-1024)", "Small Jobs (1-100)", "Large Jobs (500-1000)"};
    const char *policies[] = {"Best Fit", "Worst Fit", "First Fit"};
    
    for (int metric = 0; metric < 14; metric++) {
        switch(metric) {
            case 0: fprintf(fp, "\n1. Average Fragmentation:\n"); break;
            case 1: fprintf(fp, "\n2. Average Hole Size:\n"); break;
            case 2: fprintf(fp, "\n3. Average Holes Examined per Request:\n"); break;
            case 3: fprintf(fp, "\n4. Highest Fragmentation:\n"); break;
            case 4: fprintf(fp, "\n5. Lowest Fragmentation:\n"); break;
            case 5: fprintf(fp, "\n6. Average Number of Jobs:\n"); break;
            case 6: fprintf(fp, "\n7. Highest Number of Jobs:\n"); break;
            case 7: fprintf(fp, "\n8. Lowest Number of Jobs:\n"); break;
            case 8: fprintf(fp, "\n9. Average Job Size:\n"); break;
            case 9: fprintf(fp, "\n10. Average Number of Holes:\n"); break;
            case 10: fprintf(fp, "\n11. Highest Number of Holes:\n"); break;
            case 11: fprintf(fp, "\n12. Lowest Number of Holes:\n"); break;
            case 12: fprintf(fp, "\n13. Maximum Partitions in a Row:\n"); break;
            case 13: fprintf(fp, "\n14. Maximum Evictions for a Request:\n"); break;
        }
        
        fprintf(fp, "\n%-25s", "Profile/Policy");
        for (int policy = 0; policy < 3; policy++) {
            fprintf(fp, "%-15s", policies[policy]);
        }
        fprintf(fp, "\n");
        fprintf(fp, "----------------------------------------\n");
        
        for (int profile = 0; profile < 3; profile++) {
            fprintf(fp, "%-25s", profiles[profile]);
            for (int policy = 0; policy < 3; policy++) {
                switch(metric) {
                    case 0: fprintf(fp, "%-15.3f", all_stats[profile][policy].avg_fragmentation); break;
                    case 1: fprintf(fp, "%-15.3f", all_stats[profile][policy].avg_hole_size); break;
                    case 2: fprintf(fp, "%-15.3f", all_stats[profile][policy].avg_holes_examined); break;
                    case 3: fprintf(fp, "%-15.3f", all_stats[profile][policy].highest_fragmentation); break;
                    case 4: fprintf(fp, "%-15.3f", all_stats[profile][policy].lowest_fragmentation); break;
                    case 5: fprintf(fp, "%-15.3f", all_stats[profile][policy].avg_jobs); break;
                    case 6: fprintf(fp, "%-15d", all_stats[profile][policy].highest_jobs); break;
                    case 7: fprintf(fp, "%-15d", all_stats[profile][policy].lowest_jobs); break;
                    case 8: fprintf(fp, "%-15.3f", all_stats[profile][policy].avg_job_size); break;
                    case 9: fprintf(fp, "%-15.3f", all_stats[profile][policy].avg_holes); break;
                    case 10: fprintf(fp, "%-15d", all_stats[profile][policy].highest_holes); break;
                    case 11: fprintf(fp, "%-15d", all_stats[profile][policy].lowest_holes); break;
                    case 12: fprintf(fp, "%-15d", all_stats[profile][policy].max_partitions_in_row); break;
                    case 13: fprintf(fp, "%-15d", all_stats[profile][policy].max_evictions); break;
                }
            }
            fprintf(fp, "\n");
        }
    }
    
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <profile> <policy>\n", argv[0]);
        printf("Profiles: 1=Any sized jobs, 2=Small jobs, 3=Large jobs\n");
        printf("Policies: 1=Best fit, 2=Worst fit, 3=First fit\n");
        return 1;
    }

    int profile = atoi(argv[1]);
    int policy = atoi(argv[2]);

    if (profile < 1 || profile > 3 || policy < 1 || policy > 3) {
        printf("Invalid profile or policy number\n");
        printf("Profile must be 1-3 and policy must be 1-3\n");
        return 1;
    }

    srand(time(NULL));
    run_simulation(profile, policy);
    write_summary_file();
    printf("Simulation completed. Results written to summary.txt\n");

    return 0;
}