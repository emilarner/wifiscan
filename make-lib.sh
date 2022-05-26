mkdir -p lib/unix
cd lib/unix
gcc -c ../../*.c
ar rcs libwifiscan.a *.o
rm *.o

echo "Static library compiled to lib/unix/wifiscan.a"