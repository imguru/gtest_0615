
라이브러리를 빌드하는 방법
1. 정적 라이브러리 - libgtest.a   -> 권장
2. 동적 라이브러리 - libgtest.so

# libgtest.a 를 만드는 방법.
```
$ cd googletest/googlemock/scripts/
$ ./fuse_gmock_files.py ~/chansik.yun
$ cd ~/chansik.yun
$ g++ gmock-gtest-all.cc -c -I.
$ g++ ./googletest/googlemock/src/gmock_main.cc -c -I.
$ ar rcv libgtest.a gmock-gtest-all.o gmock_main.o

```
