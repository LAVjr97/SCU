make;
for file in file1.txt file2.txt file3.txt file4.txt file5.txt
do
    for buffer in 100 1000 10000 100000
    do
        echo "Step4 $file $buffer"
        time ./Step4 $file $buffer
        echo " "
    done
done
make clean;