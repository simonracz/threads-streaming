# Code for the processes, threads, coroutines video

# Main Results
```
+-----------------------+-------------+-----------+------------+
| New Threads Created   | Hello World | Blocking  | Coroutines |
+-----------------------+-------------+-----------+------------+
| Python                |           0 |         0 |          4 |
| Go                    |          ~4 |        ~8 |         ~9 |
| Java (openjdk 17)     |          16 |        26 |          - |
| Rust (reqwest, tokio) |           0 |         6 |        ~34 |
+-----------------------+-------------+-----------+------------+
```

# Build
```
make
# For Rust projects
cargo build --release
```

# Python
```
pipenv install
pipenv shell
strace -f python ./py_hello.py 2>&1 | grep clone
strace -f python ./py_domains.py 2>&1 | grep clone
strace -f python ./py_domains_co.py 2>&1 | grep clone
```

# Go
```
strace -f ./go_hello 2>&1 | grep clone
strace -f ./go_domains 2>&1 | grep clone
strace -f ./go_domains_co 2>&1 | grep clone
```

# Java
```
strace -f java JavaHello 2>&1 | grep clone
strace -f java JavaDomains 2>&1 | grep clone
```

# Rust
```
strace -f ./rust_hello 2>&1 | grep clone
cd domains
cargo build --release
strace -f ./targets/release/domains 2>&1 | grep clone
cd domains_co
cargo build --release
strace -f ./targets/release/domains_co 2>&1 | grep clone
```

# Debugging Thread Names
```
# CTRL + Z to stop the process (Maybe insert some sleeps before as well)
ps H -C <prg_name> -o 'pid tid cmd comm'
```

For Rust e.g.
```
ps H -C domains -o 'pid tid cmd comm'
```

```
  PID   TID CMD                         COMMAND
 2784  2784 ./domains                   domains
 2784  2785 ./domains                   reqwest-interna
 2784  2786 ./domains                   tokio-runtime-w
```

```
ps H -C domains_co -o 'pid tid cmd comm'
```
```
  PID   TID CMD                         COMMAND
 5327  5327 ./domains_co                domains_co
 5327  5328 ./domains_co                tokio-runtime-w
...the same tokio-runtime-ws for 34 times!
```

For Java e.g.
```
ps H -C 'java JavaDomains' -o 'pid tid cmd comm'
```
```
PID   TID CMD                         COMMAND
 6378  6378 java JavaDomains            java
 6378  6379 java JavaDomains            java
 6378  6380 java JavaDomains            GC Thread#0
 6378  6381 java JavaDomains            G1 Main Marker
 6378  6382 java JavaDomains            G1 Conc#0
 6378  6383 java JavaDomains            G1 Refine#0
 6378  6384 java JavaDomains            G1 Service
 6378  6385 java JavaDomains            VM Thread
 6378  6386 java JavaDomains            Reference Handl
 6378  6387 java JavaDomains            Finalizer
 6378  6388 java JavaDomains            Signal Dispatch
 6378  6389 java JavaDomains            Service Thread
 6378  6390 java JavaDomains            Monitor Deflati
 6378  6391 java JavaDomains            C2 CompilerThre
 6378  6392 java JavaDomains            C1 CompilerThre
 6378  6393 java JavaDomains            Sweeper thread
 6378  6394 java JavaDomains            Notification Th
 6378  6395 java JavaDomains            VM Periodic Tas
 6378  6396 java JavaDomains            Common-Cleaner
 6378  6397 java JavaDomains            C1 CompilerThre
 6378  6398 java JavaDomains            C1 CompilerThre
 6378  6399 java JavaDomains            C2 CompilerThre
```

The Python and Go threads were not named. (They have the default parent's cmd as name.)
