Création du script job.sh
chmod effectué.

time ./job.sh :
real	0m0.371s
user	0m0.368s
sys	0m0.000s

/usr/bin/time ./job.sh :
0.34user
0.00system
0:00.35
elapsed 98%CPU (0avgtext+0avgdata 3128maxresident)k
0inputs+0outputs (0major+135minor)pagefaults 0swaps

Après multiplicaton par 6 : 

/usr/bin/time -v ./job.sh
        Command being timed: "./job.sh"
        User time (seconds): 0.36
        System time (seconds): 0.00
        Percent of CPU this job got: 99%
        Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.36
        Average shared text size (kbytes): 0
        Average unshared data size (kbytes): 0
        Average stack size (kbytes): 0
        Average total size (kbytes): 0
        Maximum resident set size (kbytes): 3168        Average resident set size (kby$
        Major (requiring I/O) page faults: 0
        Minor (reclaiming a frame) page faults: 141
        Voluntary context switches: 4
        Involuntary context switches: 2
        Swaps: 0

/usr/bin/time -f %c ./job.sh
6

Top : 
top - 14:32:05 up 24 min,  4 users,  load average: 0,40, 0,14, 0,18
Tasks: 183 total,   3 running, 180 sleeping,   0 stopped,   0 zombie
%Cpu0  :100,0 us,  0,0 sy,  0,0 ni,  0,0 id,  0,0 wa,  0,0 hi,  0,0 si,  0,0 st
%Cpu1  :  1,7 us,  1,3 sy,  0,0 ni, 97,0 id,  0,0 wa,  0,0 hi,  0,0 si,  0,0 st
%Cpu2  :  1,0 us,  0,7 sy,  0,0 ni, 98,3 id,  0,0 wa,  0,0 hi,  0,0 si,  0,0 st
%Cpu3  :100,0 us,  0,0 sy,  0,0 ni,  0,0 id,  0,0 wa,  0,0 hi,  0,0 si,  0,0 st
KiB Mem:   8149560 total,  1550188 used,  6599372 free,   138764 buffers
KiB Swap: 16779888 total,        0 used, 16779888 free.   689292 cached Mem

Avec 2 utilisations de while.sh


/usr/bin/time -f %c ./job.sh
12


nice /usr/bin/time -f %c ./job.sh
5

/usr/bin/time -f %c ./job2.sh
6
On a un pic d'utilisation du CPU0 à 13% alors qu'il était à 1%.

/usr/bin/time ./job10.sh18.25user 0.00system 0:18.29elapsed 99%CPU (0avgtext+0avgdata 3160maxresident)k
0inputs+0outputs (0major+1920minor)pagefaults 0swaps
On a la CPU0 qui monte à 100%.

Lors du rajout de &.
Les CPU 0, 1, 2 et 3 sont en marche et le temps d'execution est inférieur à 1 seconde (pour job10.sh)

1486562007
1486562007
1486562007
1486562007
1486562007
1486562007
1486562007
1486562007
1486562007
Donc le taux d'utilisation de la CPU est de 100% ? Car il n'y a aucuns qui terminent plus tard.

/usr/bin/time ./job10.sh
19.44user 0.00system 0:04.92elapsed 394%CPU (0avgtext+0avgdata 3164maxresident)k
0inputs+0outputs (0major+2013minor)pagefaults 0swaps


-Les appels au système
static ?


fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0              
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f5540997000
write(1, "abcd\n", 5)                   = 5                                        
read(0, "Coucou seb\n", 1024)           = 11                                           
write(1, "Coucou seb\n", 11)            = 11                                            
read(0, "Regarde ce que mon linux peut fa"..., 1024) = 36                                    
write(1, "Regarde ce que mon linux peut fa"..., 36) = 36                                           
read(0, "Regarde ce que mon linux peut fa"..., 1024) = 57                                            
write(1, "Regarde ce que mon linux peut fa"..., 57) = 57
read(0, Process 7591 detached

time cat /tmp/bidon | ./io

real	0m0.281s
user	0m0.216s
sys	0m0.052s

