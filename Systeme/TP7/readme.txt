cc memoire_logique.c -static -o memoire_logique

1. Avec -static
PID = 1597
adresse de une_globale  =   6b7a40
adresse de une_locale   = 7ffdd9a8780c
adresse de alloc        = 7f84f78ac010
adresse de une_fonction =   400f8e
adresse de printf       =   4079a0
00400000-004b5000 r-xp 00000000 00:2a 29611822                           /amuhome/c16017548/l3-info-luminy/Systeme/TP7/memoire_logique
006b4000-006b6000 rw-p 000b4000 00:2a 29611822                           /amuhome/c16017548/l3-info-luminy/Systeme/TP7/memoire_logique
006b6000-006b9000 rw-p 00000000 00:00 0 
01fb5000-01fd8000 rw-p 00000000 00:00 0                                  [heap]
7f84f78ab000-7f84f82ad000 rw-p 00000000 00:00 0 
7ffdd9a68000-7ffdd9a89000 rw-p 00000000 00:00 0                          [stack]
7ffdd9ae9000-7ffdd9aeb000 r-xp 00000000 00:00 0                          [vdso]
7ffdd9aeb000-7ffdd9aed000 r--p 00000000 00:00 0                          [vvar]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]

2. Sans -static
PID = 1677
adresse de une_globale  =   600c40
adresse de une_locale   = 7fff524228bc
adresse de alloc        = 7effb8032010
adresse de une_fonction =   400676
adresse de printf       =   400520
00400000-00401000 r-xp 00000000 00:2a 29611819                           /amuhome/c16017548/l3-info-luminy/Systeme/TP7/memoire_logique
00600000-00601000 rw-p 00000000 00:2a 29611819                           /amuhome/c16017548/l3-info-luminy/Systeme/TP7/memoire_logique
7effb8032000-7effb8a33000 rw-p 00000000 00:00 0 
7effb8a33000-7effb8bd5000 r-xp 00000000 08:02 508242                     /lib/x86_64-linux-gnu/libc-2.19.so
7effb8bd5000-7effb8dd4000 ---p 001a2000 08:02 508242                     /lib/x86_64-linux-gnu/libc-2.19.so
7effb8dd4000-7effb8dd8000 r--p 001a1000 08:02 508242                     /lib/x86_64-linux-gnu/libc-2.19.so
7effb8dd8000-7effb8dda000 rw-p 001a5000 08:02 508242                     /lib/x86_64-linux-gnu/libc-2.19.so
7effb8dda000-7effb8dde000 rw-p 00000000 00:00 0 
7effb8dde000-7effb8dfe000 r-xp 00000000 08:02 508225                     /lib/x86_64-linux-gnu/ld-2.19.so
7effb8fbf000-7effb8fc2000 rw-p 00000000 00:00 0 
7effb8ffb000-7effb8ffe000 rw-p 00000000 00:00 0 
7effb8ffe000-7effb8fff000 r--p 00020000 08:02 508225                     /lib/x86_64-linux-gnu/ld-2.19.so
7effb8fff000-7effb9000000 rw-p 00021000 08:02 508225                     /lib/x86_64-linux-gnu/ld-2.19.so
7effb9000000-7effb9001000 rw-p 00000000 00:00 0 
7fff52404000-7fff52425000 rw-p 00000000 00:00 0                          [stack]
7fff5252c000-7fff5252e000 r-xp 00000000 00:00 0                          [vdso]
7fff5252e000-7fff52530000 r--p 00000000 00:00 0                          [vvar]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]

3. Avec allocation dynamique

PID = 1838
adresse de une_globale  =   6b7a88
adresse de une_locale   = 7ffe31cd4808
adresse de alloc        = 7f4e69361010
adresse de une_fonction =   400f8e
adresse de printf       =   407a00
00400000-004b5000 r-xp 00000000 00:2a 29611819                           /amuhome/c16017548/l3-info-luminy/Systeme/TP7/memoire_logique
006b4000-006b6000 rw-p 000b4000 00:2a 29611819                           /amuhome/c16017548/l3-info-luminy/Systeme/TP7/memoire_logique
006b6000-006b9000 rw-p 00000000 00:00 0 
009ce000-009f1000 rw-p 00000000 00:00 0                                  [heap]
7f4e69360000-7f4e69d62000 rw-p 00000000 00:00 0 
7ffe31cb5000-7ffe31cd6000 rw-p 00000000 00:00 0                          [stack]
7ffe31d6f000-7ffe31d71000 r-xp 00000000 00:00 0                          [vdso]
7ffe31d71000-7ffe31d73000 r--p 00000000 00:00 0                          [vvar]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
>INPUT>>a
00400000-004b5000 r-xp 00000000 00:2a 29611819                           /amuhome/c16017548/l3-info-luminy/Systeme/TP7/memoire_logique
006b4000-006b6000 rw-p 000b4000 00:2a 29611819                           /amuhome/c16017548/l3-info-luminy/Systeme/TP7/memoire_logique
006b6000-006b9000 rw-p 00000000 00:00 0 
009ce000-009f1000 rw-p 00000000 00:00 0                                  [heap]
7f4deff5e000-7f4e69d62000 rw-p 00000000 00:00 0 
7ffe31cb5000-7ffe31cd6000 rw-p 00000000 00:00 0                          [stack]
7ffe31d6f000-7ffe31d71000 r-xp 00000000 00:00 0                          [vdso]
7ffe31d71000-7ffe31d73000 r--p 00000000 00:00 0                          [vvar]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]

1>7f4e69360000
2>7f4deff5e000
2 est plus petit que 1 dans la mémoire et donc la plage est plus grande (1 et 2 sont des pointeurs sur début)



