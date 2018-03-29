# OpenJ9 JVMTI JIT Issue demo

To build and run on Ubuntu-based build container:

```bash
apt-get install gradle g++ cmake
cd jitfaildemo
mkdir build
cd build
cmake ../agent
make
cd ..
JAVA_HOME=/path/to/built-openj9-jdk gradle run
cat jit.log.* | grep BManyFields
```

It's also possible to do a `gradle jar` and then run the app using:

```bash
JAVA_HOME=/path/to/built-openj9-jdk /path/to/built-openj9-jdk/bin/java -agentpath:build/libJitFailAgent.so '-Xjit:count=0,verbose={compileStart|compileEnd},vlog=jit.log' -jar build/libs/jitfaildemo-1.0.0-SNAPSHOT.jar
```

